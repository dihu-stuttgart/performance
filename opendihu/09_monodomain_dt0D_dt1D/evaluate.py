#!/usr/bin/env python
# -*- coding: utf-8 -*-

# arguments: <scenario_name> <dt_0D> <dt_1D>

import numpy as np
import scipy.integrate
import sys,os

import py_reader    # reader utility for opendihu *.py files

# output in a readable format
import pprint 
pp = pprint.PrettyPrinter()

exit_value=0
scenario_name = ""
if len(sys.argv) > 1:
  scenario_name = sys.argv[1]
if len(sys.argv) > 2:
  dt_0D = float(sys.argv[2])
if len(sys.argv) > 3:
  dt_1D = float(sys.argv[3])
if len(sys.argv) > 4:
  exit_value = int(sys.argv[4])

print("exit_value: {}".format(exit_value))

# load reference solution
filename = "../reference_solution.py"
data = py_reader.load_data([filename])
dataset = data[0]

# get time of reference solution
time_reference_solution = dataset["currentTime"]

reference_solution_field_variable = None
for field_variable in dataset["data"]:
  if field_variable["name"] == "solution":
    reference_solution_field_variable = field_variable
    break

print("\nreference data, file \"{}\"".format(filename))
for field_variable in dataset["data"]:
  print("  field variable \"{}\"".format(field_variable["name"]))
  for component in field_variable["components"]:
    print("    component \"{}\"".format(component["name"]))

# load simulation output
# get all input data in current directory
ls = os.listdir(".")

# sort files by number in file name
files = sorted(ls)

# extract python files
py_files = []
for file in files:
  if ".py" in file:
    py_files.append(file)

# only use last file
py_files = [py_files[-1]]

# load data in files
data = py_reader.load_data(py_files)
dataset = data[0]
current_time = dataset["currentTime"]

# determine solution field variable
solution_field_variable = None

# loop over field variables
for field_variable in dataset["data"]:
  if field_variable["name"] == "solution":
    solution_field_variable = field_variable
    break
  
print("\nsolution data, file \"{}\"".format(py_files[0]))
for field_variable in dataset["data"]:
  print("  field variable \"{}\"".format(field_variable["name"]))
  for component in field_variable["components"]:
    print("    component \"{}\"".format(component["name"]))

if abs(time_reference_solution - current_time) > 1e-5:
  print("Error, time does not match. Reference solution: t={}, simulation output: t={}".format(time_reference_solution, current_time))
  
relative_errors = []
# loop over components and compute error  
for component,component_reference in zip(reference_solution_field_variable["components"], solution_field_variable["components"]):
  name_component = component["name"]
  name_reference = component_reference["name"]
  
  if name_component != name_reference:
    print("Error, component names do not match. Reference solution: {}, simulation output: {}".format(name_reference, name_component))
    
  values = component["values"]
  values_reference = component_reference["values"]
  
  rms_relative_error = np.linalg.norm((values - values_reference) / values_reference) / np.sqrt(values_reference.size)
  print("{} has rms {}".format(name_component,rms_relative_error))
  
  relative_errors.append(rms_relative_error)

mean_relative_error = np.nanmean(relative_errors)
median_relative_error = np.nanmedian(relative_errors)

if exit_value != 0:
  mean_relative_error = np.nan
  median_relative_error = np.nan
  print("set to nan")

print("total mean rms relative error: {}".format(mean_relative_error))
print("total median rms relative error: {}".format(median_relative_error))

with open("../result.csv", "a") as f:
  f.write("{};{};{};{};{}\n".format(scenario_name,dt_0D,dt_1D,mean_relative_error,median_relative_error))
  
