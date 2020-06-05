#!/usr/bin/env python
# -*- coding: utf-8 -*-

# arguments: <scenario_name> <dt> <dx>

import numpy as np
import scipy.integrate
import sys,os

import py_reader    # reader utility for opendihu *.py files

# output in a readable format
import pprint 
pp = pprint.PrettyPrinter()

scenario_name = ""
if len(sys.argv) > 1:
  scenario_name = sys.argv[1]
if len(sys.argv) > 2:
  dt = float(sys.argv[2])
if len(sys.argv) > 3:
  dx = float(sys.argv[3])

# ---------
# load log
logfile = "../logs/log.csv"
with open(logfile,"r") as f:
  lines = f.read().split("\n")

lines = list(filter(None, lines))

# parse dt
last_line_entries = lines[-1].split(";")
#print("last_line_entries: {}".format(last_line_entries))

# durationSolve_linearSolver
# linearSolver_preconditionerType
# linearSolver_solverType
# nIterations_linearSolver
# nDofs

duration_solve = (float)(last_line_entries[29])
duration_total = (float)(last_line_entries[35])
preconditioner_type = last_line_entries[40]
solver_type = last_line_entries[41]
dt_log = (float)(last_line_entries[37])
n_iterations = (int)(last_line_entries[48])

print("dx: {}, dt: {}={}, n_iterations: {}, solver_type: {}, preconditioner_type: {}, duration_total: {}, duration_solve: {}".format(dx, dt, dt_log, n_iterations, solver_type, preconditioner_type, duration_total, duration_solve))



# ---------
# load reference solution
filename = "../reference_solution.py"
data = py_reader.load_data([filename])
dataset_reference = data[0]

# get time of reference solution
time_reference_solution = dataset_reference["currentTime"]

reference_solution_field_variable = None
for field_variable in dataset_reference["data"]:
  if field_variable["name"] == "solution":
    reference_solution_field_variable = field_variable
    break

# ---------
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
  
if abs(time_reference_solution - current_time) > 1e-5:
  print("Error, time does not match. Reference solution: t={}, simulation output: t={}".format(time_reference_solution, current_time))
  
# ---------
# compute error
relative_errors = []
# loop over components and compute error  
for component_reference,component in zip(reference_solution_field_variable["components"], solution_field_variable["components"]):
  name_component = component["name"]
  name_reference = component_reference["name"]
  
  if name_component != name_reference:
    print("Error, component names do not match. Reference solution: {}, simulation output: {}".format(name_reference, name_component))
    
  nx_reference,ny_reference,nz_reference = dataset_reference["nElements"]
  mx_reference,my_reference,mz_reference = nx_reference+1,ny_reference+1,nz_reference+1
  
  nx,ny,nz = dataset["nElements"]
  mx,my,mz = nx+1,ny+1,nz+1
  
  values = component["values"]
  values_reference = component_reference["values"]
  
  print("mx,my,mz: ", mx,my,mz,", ref: ",mx_reference,my_reference,mz_reference,"=",mx_reference*my_reference*mz_reference,len(values_reference))
  
  # evaluate the reference field at the coordinates of the simulation result, to be able to compare the simulation result with the finer-grid reference values
  values_reference_interpolated = np.zeros(mx*my*mz)
  
  # loop over points in simulation result
  for k in range(mz):
    for j in range(my):
      for i in range(mx):
        
        # determine indices in grid of reference solution
        i_reference = int((float(i)/nx) * nx_reference)
        j_reference = int((float(j)/ny) * ny_reference)
        k_reference = int((float(k)/nz) * nz_reference)
        
        i_reference_next = min(i_reference, mx_reference+1)
        j_reference_next = min(j_reference, my_reference+1)
        k_reference_next = min(k_reference, mz_reference+1)
        
        alpha_x = ((float(i)/nx) * nx_reference) - i_reference
        alpha_y = ((float(j)/ny) * ny_reference) - j_reference
        alpha_z = ((float(k)/nz) * nz_reference) - k_reference
        
        # get 8 corner points
        v0 = values_reference[k_reference     *mx_reference*my_reference + j_reference     *mx_reference + i_reference]
        v1 = values_reference[k_reference     *mx_reference*my_reference + j_reference     *mx_reference + i_reference_next]
        v2 = values_reference[k_reference     *mx_reference*my_reference + j_reference_next*mx_reference + i_reference]
        v3 = values_reference[k_reference     *mx_reference*my_reference + j_reference_next*mx_reference + i_reference_next]
        v4 = values_reference[k_reference_next*mx_reference*my_reference + j_reference     *mx_reference + i_reference]
        v5 = values_reference[k_reference_next*mx_reference*my_reference + j_reference     *mx_reference + i_reference_next]
        v6 = values_reference[k_reference_next*mx_reference*my_reference + j_reference_next*mx_reference + i_reference]
        v7 = values_reference[k_reference_next*mx_reference*my_reference + j_reference_next*mx_reference + i_reference_next]
        
        #print("at ({},{},{})/({},{},{}), point in reference grid: ({},{},{})/({},{},{}), alphas: ({},{},{})".format(i,j,k,mx,my,mz,i_reference,j_reference,k_reference,mx_reference,my_reference,mz_reference,alpha_x,alpha_y,alpha_z))
        
        # get value in reference
        value_reference_interpolated = \
            (1-alpha_x)*(1-alpha_y)*(1-alpha_z) * v0  \
          + alpha_x    *(1-alpha_y)*(1-alpha_z) * v1  \
          + (1-alpha_x)*alpha_y    *(1-alpha_z) * v2  \
          + alpha_x    *alpha_y    *(1-alpha_z) * v3  \
          + (1-alpha_x)*(1-alpha_y)*alpha_z     * v4  \
          + alpha_x    *(1-alpha_y)*alpha_z     * v5  \
          + (1-alpha_x)*alpha_y    *alpha_z     * v6  \
          + alpha_x    *alpha_y    *alpha_z     * v7
  
        values_reference_interpolated[k*mx*my + j*mx + i] = value_reference_interpolated
  
  rms_relative_error = np.linalg.norm((values - values_reference_interpolated) / values_reference_interpolated) / np.sqrt(values_reference.size)
  print("component {} has rms {}".format(name_component,rms_relative_error))
  
  relative_errors.append(rms_relative_error)

mean_relative_error = np.mean(relative_errors)
median_relative_error = np.median(relative_errors)

print("total mean rms relative error: {}".format(mean_relative_error))
print("total median rms relative error: {}".format(median_relative_error))

filename = "../result_{}.csv".format(scenario_name)
# write header
if not os.path.isfile(filename):
  with open(filename, "w") as f:
    f.write("# scenario_name;dt;dx;solver_type;preconditioner_type;n_iterations;duration_solve;duration_total;mean_relative_error;median_relative_error\n")

# append line
with open(filename, "a") as f:
  f.write("{};{};{};{};{};{};{};{};{};{}\n".format(scenario_name,dt,dx,solver_type,preconditioner_type,n_iterations,duration_solve,duration_total,mean_relative_error,median_relative_error))
  
