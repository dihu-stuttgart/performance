#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import subprocess
import datetime
import time
import os
import socket
import csv
import compute_error
import exnode_reader

# set environment variable
os.environ['OPENCMISS_SCE_FILE'] = 'standard.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(splitting_type,n_0D,n_1D):   
  # splitting_type: 0 = Godunov splitting, 1 = Strang splitting
  folder = "{}_{}_{}".format(splitting_type,n_0D,n_1D)

  elasticity_timestep = 0.1
  ode_nsteps = n_0D
  pde_nsteps = n_1D

  #command = "mkdir -p {folder} && cd {folder} && $OPENCMISS_REL_DIR/cuboid ../$OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR ODENSteps={ode_nsteps} PDETimeStep={pde_timestep} SplittingType={splitting_type} ODESolverId={ode_solver_id} && cd -"\
  command = "mkdir -p {folder} && cd {folder} && $OPENCMISS_REL_DIR/cuboid ../$OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR ODENSteps={ode_nsteps} PDENSteps={pde_nsteps} SplittingType={splitting_type} ODESolverId={ode_solver_id} && cd -"\
  .format(folder=folder, ode_nsteps=int(ode_nsteps), pde_nsteps=pde_nsteps, splitting_type=splitting_type, ode_solver_id=1 if splitting_type==0 else 5)

  #print command
  try:
    print command
    subprocess.check_call(command, shell=True)
  except:
    pass

  time.sleep(0.5)

  # read in computational times
  report_filename = folder+"/duration.00000.csv"
  data = []
  with open(report_filename) as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    for row in reader:
      if len(row) > 0:
        if '#' not in row[0]:
          data.append(row)
    data = data[-1]
    duration_0D = data[36]
    duration_1D = data[37]
    duration_0D_solve = data[43]
    duration_1D_solve = data[47]
    duration_total = data[15]

  # compute error
  reference_folder = "1_1000_10000"
  error = compute_error.compute_error(reference_folder, folder)
 
  # write to file
  output_report = "error.csv"
  with open(output_report, "ab") as f:
    f.write("{date};{hostname};{splitting_type};{n_0D};{n_1D};{error};{duration_0D};{duration_1D};{duration_0D_solve};{duration_1D_solve};{duration_total}\n".\
            format(date=time.strftime("%d.%m.%Y %H:%M:%S"), hostname=socket.gethostname(), splitting_type=splitting_type, \
            n_0D=n_0D, n_1D=n_1D, error=error, \
            duration_0D=duration_0D, duration_1D=duration_1D, duration_0D_solve=duration_0D_solve, duration_1D_solve=duration_1D_solve, duration_total=duration_total))
 
if len(sys.argv) > 3:
  splitting_type = int(sys.argv[1])
  n_0D = int(sys.argv[2])
  n_1D = int(sys.argv[3])
  print "Godunov," if splitting_type==0 else "Strang, ", " 0D", n_0D, ", 1D", n_1D

  run(splitting_type,n_0D,n_1D)
