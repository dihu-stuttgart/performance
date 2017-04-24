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
os.environ['OPENCMISS_SCE_FILE'] = 'small.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(x,y,z,f,a,ode,msolver,mprecond):   
  print "x={0}, y={1}, z={2}, n={3}, total={4}".format(int(x),int(y),int(z),int(n),x*y*z)
  command = "$OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR {0} {1} {2} {3} {4} {5} {6} {7}"\
  .format(int(x),int(y),int(z),int(f),int(a), int(ode), int(msolver), int(mprecond))

  #print command
  try:
    subprocess.check_call(command, shell=True)
  except:
    pass


n_start = 1   # size of smallest problem to begin with
last_total = 0
f = 1
a = 1
ode = 1       # 1 explicit Euler, 2 BDF
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
precond = 1   # 1 NO_PRECONDITIONER, 2 JACOBI_PRECONDITIONER, 3 BLOCK_JACOBI_PRECONDITIONER, 4 SOR_PRECONDITIONER, 5 INCOMPLETE_CHOLESKY_PRECONDITIONER, 6 INCOMPLETE_LU_PRECONDITIONER, 7 ADDITIVE_SCHWARZ_PRECONDITIONER

for n in range(n_start,1000):
  x = np.round(n**(1./3))
  y = np.round((n/x)**(1./2))
  z = np.round(n/x/y)
  total = x*y*z
  
  if total == last_total:
    continue
 
  last_total = total

  # CG
  precond = 1
  for msolver in [1, 2, 4]:
    check_exit()
    run(x,y,z,f,a,ode,msolver,precond)

  # CG with different preconditioners
  msolver = 3
  
  for precond in range(1,8):
    check_exit()
    run(x,y,z,f,a,ode,msolver,precond)

  
