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

def run(p,x,y,z,xi1,ax,ode,msolver,mprecond):
  
  command = "mpirun -n {p} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x} y={y} z={z} xi1={xi1} ax={ax} "\
            "ODESolverId={ode} MonodomainSolverId={msolver} MonodomainPreconditionerId={mprecond}"\
            .format(p=int(p), x=int(x), y=int(y), z=int(z), xi1=int(xi1), ax=int(ax), ode=ode, msolver=msolver, mprecond=mprecond)

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

for pp in [2, 4, 8, 16, 32]:          # 2*number fibre subdivisions 
  for n in range(n_start,1000):
  #for pp in [16]:
    total = pp**(n+1)

    if total > 65536:
      break

    x = pp
    xi1 = total/pp
    
    y = 1
    z = 1

    total = x*y*z
    ax = 1
    #print "n=",n,",x=",x,",y=",y,",z=",z,",ax=",ax,",total=",total
    check_exit()
    run(pp,x,y,z,xi1,ax,ode,msolver,mprecond)
  
