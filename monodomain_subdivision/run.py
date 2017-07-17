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
os.environ['OPENCMISS_SCE_FILE'] = 'divided.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(p,x,y,z,xi1,ax,ay,az,ode,msolver,mprecond):
  
  command = "mpirun -n {p} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x} y={y} z={z} xi1={xi1} ax={ax} ay={ay} az={az} "\
            "ODESolverId={ode} MonodomainSolverId={msolver} MonodomainPreconditionerId={mprecond}"\
            .format(p=int(p), x=int(x), y=int(y), z=int(z), xi1=int(xi1), ax=int(ax), ay=int(ay), az=int(az), ode=ode, msolver=msolver, mprecond=mprecond)

  print command; return
  
  # execute command
  try:
    subprocess.check_call(command, shell=True)
  except:
    pass

n_start = 1   # size of smallest problem to begin with
last_total = 0

ax = 1        # number of elements in x-direction in atom (non-decomposable block of elements)
ode = 1       # 1 explicit Euler, 2 BDF
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
mprecond = 1   # 1 NO_PRECONDITIONER, 2 JACOBI_PRECONDITIONER, 3 BLOCK_JACOBI_PRECONDITIONER, 4 SOR_PRECONDITIONER, 5 INCOMPLETE_CHOLESKY_PRECONDITIONER, 6 INCOMPLETE_LU_PRECONDITIONER, 7 ADDITIVE_SCHWARZ_PRECONDITIONER

n_processes = 64

x = n_processes
y = 8
z = 8
xi1 = 2

n_processes = 64
portion_per_process = x*y*z / n_processes

#for k in [1, 2, 4, 8, 16, 32, 64]:
for k in range(1,11000):
  
  
  ax = float(x)/k
  area = float(portion_per_process)/ax
  if abs(area-int(area)) > 1e-5 or abs(ax-int(ax)) > 1e-5:
    continue
  
  a = int(np.sqrt(area))
  area = int(area)
  
  best = 1
  for i in range(1,a+1):
    j = float(area)/i
    if abs(int(j) - j) < 1e-5:
      if i>best:
        best=i
  
  ay = area / best
  az = best
    
  check_exit()
  run(n_processes,x,y,z,xi1,ax,ay,az,ode,msolver,mprecond)
  
