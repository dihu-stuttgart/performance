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
os.environ['OPENCMISS_SCE_FILE'] = 'TConv.sce'


# executes cuboid
def run(xi1,ode,msolver,splitting,ode_n_steps,pde_time_step,output_stride,scenario_name):
  """
  xi1: number of 1D elements per 3D element per fibre
  ode: ode solver type, 1=euler, 5=heun
  msolver: diffusion linear solver,  1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
  splitting: 0=Godunov splitting, 1=Strang splitting
  ode_n_steps: number of ODE time steps per 1D time step
  pde_time_step: time step for diffusion problem (1D time step)
  scenario_name: will be written to timing data to distinguish in plot script
  """
  command = "$OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR xi1={} ODESolverId={} MonodomainSolverId={} UseStrangSplitting={} OdeNSteps={} PDETimeStep={} \
             OutputTimeStepStride={}\
             && mkdir -p results/TConv_{}_{}/TConv_{}\
             && mv *.ex* results/TConv_{}_{}/TConv_{}".format(int(xi1), int(ode), int(msolver), splitting, int(ode_n_steps), pde_time_step,int(output_stride),int(xi1),scenario_name,pde_time_step,int(xi1),scenario_name,pde_time_step)

  try:
    print command
    subprocess.check_call(command, shell=True)
  except:
    pass

xi1=16
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
#timesteps=[0.000001,0.0001,0.0002,0.0005,0.001,0.002,0.005]
#strides=[100000,1000,500,200,100,50,20]
timesteps=[0.002,0.001,0.0005,0.0002,0.0001,0.000001]
strides=[1,1,1,1,1,1,1]

# loop over runs
for n in range(1):

  # run with godunov splitting
  ode = 1 # 1 explicit Euler
  use_strang_splitting = 'F' # Godunov splitting
  ode_n_steps = 5
  pde_time_step = timesteps[n]
  output_stride=strides[n]
  #run(xi1,ode,msolver,use_strang_splitting,ode_n_steps,pde_time_step,output_stride,"1st_order")
  
  # run with strang splitting
  ode = 5 #Heun
  use_strang_splitting = 'T' # Strang splitting
  ode_n_steps = 2
  pde_time_step = timesteps[n]
  output_stride=strides[n]
  run(xi1,ode,msolver,use_strang_splitting,ode_n_steps,pde_time_step,output_stride,"2nd_order")
