#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
#import matplotlib.pyplot as plt
import subprocess
import datetime
import time
import os

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

def run(ode,dt):   
  command = "mkdir -p {ode}_{dt} && cd {ode}_{dt} && $OPENCMISS_REL_DIR/cuboid ../$OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR ODESolverId={ode} ODETimeStep={dt} && cd -"\
  .format(ode=int(ode), dt=dt)

  #print command
  try:
    print command
    subprocess.check_call(command, shell=True)
  except:
    pass
    
f = 1
a = 1
ode = 1       # 1 explicit Euler, 2 BDF, 5  Improved Euler (Heun)
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
precond = 1   # 1 NO_PRECONDITIONER, 2 JACOBI_PRECONDITIONER, 3 BLOCK_JACOBI_PRECONDITIONER, 4 SOR_PRECONDITIONER, 5 INCOMPLETE_CHOLESKY_PRECONDITIONER, 6 INCOMPLETE_LU_PRECONDITIONER, 7 ADDITIVE_SCHWARZ_PRECONDITIONER


# standard time step 1e-4
# reference time step 1e-5

for dt_0D in [1e-5, 1e-4, 1e-3, 1e-2]:
  for ode in [1,5]:
    run(ode,dt_0D)
