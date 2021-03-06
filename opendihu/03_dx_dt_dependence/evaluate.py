#!/usr/bin/env python
# -*- coding: utf-8 -*-

# compute propagation velocity of files in current folder
# arguments: <scenario_name>

import numpy as np
import scipy.integrate
import sys,os

import py_reader    # reader utility for opendihu *.py files

# output in a readable format
import pprint 
pp = pprint.PrettyPrinter()

max_threshold = 25.0

scenario_name = ""
if len(sys.argv) > 1:
  scenario_name = sys.argv[1]
  if "shorten" in scenario_name:
    max_threshold = 0.0

# load log
logfile = "../logs/log.csv"
with open(logfile,"r") as f:
  lines = f.read().split("\n")

lines = list(filter(None, lines))

# parse dt
last_line_entries = lines[-1].split(";")
#print("last_line_entries: {}".format(last_line_entries))
dt = (float)(last_line_entries[37])
print("parsed dt: {}".format(dt))


# get all input data in current directory
ls = os.listdir(".")

# sort files by number in file name
files = sorted(ls)

# extract files
py_files = []
for file in files:
  if ".py" in file:
    py_files.append(file)

# load all files
#print("files: {}".format(py_files))
data = py_reader.load_data(py_files)

entries = []
n_points = 0

# loop over data files and output in readable formatting
for dataset in data:
  current_time = dataset["currentTime"]
  if current_time < 1.0:
    continue
  
  solution = py_reader.get_values(dataset, "solution", "0")
  n_points = len(solution)
  center = n_points/2
  
  max_vm = max(solution)
  
  pos0 = None
  pos1 = None
  max_threshold_indices = [i for i, value in enumerate(solution) if value >= max_threshold]
  
  if max_threshold_indices:
    pos0 = max_threshold_indices[0]
    pos1 = max_threshold_indices[-1]
  
    distance = 0.5*((center-pos0) + (pos1-center))
    entries.append((current_time, distance))
  
    print("t: {}, max vm: {}, stimulus at {}, {} from center: ({},{}), distance:{}".format(current_time, max_vm, pos0, pos1, center-pos0, center-pos1, distance))
  else:
    
    print("t: {}, max vm: {}, no stimulus".format(current_time, max_vm))
   
print(entries)
 
fiber_length_cm = 4.0
if entries:
  velocity = (entries[-1][1] - entries[0][1]) / (entries[-1][0] - entries[0][0])  # Δdistance / Δt
  velocity /= (n_points/fiber_length_cm)          # convert velocity from elements/ms to cm/ms
  print("{}, nodes/cm: {}, propagation velocity: {}, ({}/{})".format(scenario_name,  n_points/fiber_length_cm, velocity, (entries[-1][1] - entries[0][1]), (entries[-1][0] - entries[0][0])))
  
  # write to file
  # scenario_name; n elements per cm; propagation velocity in cm per ms; dt
  with open("../result.csv","a") as f:
    f.write("{};{};{};{}\n".format(scenario_name,n_points/fiber_length_cm,velocity,dt))
    #pp.pprint(dataset)

  # read last velocity
  last_velocity = -1
  try:
    with open("../last_velocity","r") as f:
      last_velocity = (float)(f.read())
  except:
    print("could not open last_velocity file")

  # store last velocity
  with open("../last_velocity","w") as f:
    f.write(str(velocity))

  if abs(last_velocity) < 1e-8:
    last_velocity = -1.0

  if last_velocity >= 0:
    difference = abs(velocity - last_velocity)
    print("dt: {}, last_velocity: {}, current_velocity: {}, difference: {}".format(dt, last_velocity, velocity, difference))
    
    # scenario_name; n elements per cm; propagation velocity in cm/ms; convergence error; dt
    if difference < 1e-3:
      with open("../resulting_dt","a") as f:
        f.write("{};{};{};{};{}\n".format(scenario_name,n_points/fiber_length_cm,velocity,difference,dt))
      print("error is small enough, done with scenario {}!\n\n".format(scenario_name))
      exit(0)  # 0 means converged

else:
  print("dt: {}, {}, nodes/cm: {}, no stimulus".format(dt, scenario_name, n_points/fiber_length_cm))
  
print("no convergence")
exit(-1)
