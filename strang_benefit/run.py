#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
#import matplotlib.pyplot as plt
import subprocess
import datetime
import time
import os

# For this to work you have to set the environment variables
# $OPENCMISS_INPUT_DIR to a directory containing all input files
# $OPENCMISS_SCE_FILE to the actual scenario file (is done in this script)

# set environment variable
os.environ['OPENCMISS_SCE_FILE'] = 'standard.sce'


# executes cuboid
def run(xi1,ode,msolver,splitting,ode_n_steps,pde_n_steps,scenario_name):
  """
  xi1: number of 1D elements per 3D element per fibre
  ode: ode solver type, 1=euler, 5=heun
  msolver: diffusion linear solver,  1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
  splitting: 0=Godunov splitting, 1=Strang splitting
  ode_n_steps: number of ODE time steps per 1D time step
  pde_time_step: time step for diffusion problem (1D time step)
  scenario_name: will be written to timing data to distinguish in plot script
  """
  
  print "xi1={0}".format(int(xi1))
  command = "$OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR xi1={} ODESolverId={} MonodomainSolverId={} SplittingType={} OdeNSteps={} PdeNSteps={} ScenarioName={}"\
  .format(int(xi1), int(ode), int(msolver), int(splitting), int(ode_n_steps), int(pde_n_steps), scenario_name)

  #print command
  try:
    print command
    subprocess.check_call(command, shell=True)
  except:
    pass


ode = 1       # 1 explicit Euler, 5 Heun
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
splitting = 0  # 0=Godunov splitting, 1=Strang splitting
ode_n_steps = 5   
pde_time_step = 0.0005

# loop over runs
previous_xi1 = 0
for n in range(21,121):
  # compute value for xi (number of 1D elements per 3D element per fibre)
  xi1 = np.round(1.5**n)

  # assert that value is different from last run
  if (xi1 == previous_xi1):
    continue
  previous_xi1 = xi1
  
  # run with godunov splitting
  ode = 1
  splitting = 0
  ode_n_steps = 1
  pde_n_steps = 724
#  pde_time_step = 0.0005
  run(xi1,ode,msolver,splitting,ode_n_steps,pde_n_steps,"1st_order")
  
  run(xi1,ode,2,splitting,ode_n_steps,pde_n_steps,"1st_order_gmres")
  
  # run with strang splitting
  ode = 5
  splitting = 1
  ode_n_steps = 1
  pde_n_steps = 128
#  pde_time_step = 0.0025
  run(xi1,ode,msolver,splitting,ode_n_steps,pde_n_steps,"2nd_order")
