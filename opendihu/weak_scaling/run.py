#!/usr/bin/env python
# -*- coding: utf-8 -*-

# parallel weak scaling

import sys
import numpy as np
#import matplotlib.pyplot as plt
import subprocess
import datetime
import time
import os
import domain_decomposition

# set environment variable
os.environ['OPENCMISS_SCE_FILE'] = 'paper.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(nproc,x,y,z,px,py,pz,ex,ey,ez): # nnodes = number of nodes, nproc = number of processes
  
  #(used_number_of_processes, subdomain_shape) = domain_decomposition.number_of_processes(nproc,x,y,z,ax,ay,az)
  #print "Number of subdomains: ",used_number_of_processes, ", shape of subdomain: ", subdomain_shape

  ode = 1
  msolver = 2
  precond = 1
  
  j = "-j1"  # no hyperthreading
#  if p > 12:
#    j = "-j2"  # hyperthreading
#  else:
#    j = "-j1"  # no hyperthreading

  command = "aprun -n {nproc} -N {ppn} {j} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x} y={y} z={z} px={px} py={py} pz={pz} ex={ex} ey={ey} ez={ez} "\
            "ODESolverId={ode} MonodomainSolverId={msolver} MonodomainPreconditionerId={mprecond}"\
            .format(nproc=int(nproc), ppn=24, j=j, x=int(x), y=int(y), z=int(z), px=int(px), py=int(py), pz=int(pz), ex=int(ex), ey=int(ey), ez=int(ez), ode=ode, msolver=msolver, mprecond=mprecond)

  #print command; return 
  print command

  # execute command
  try:
    with open('log.txt','ab') as log:
      log.write("\n\n\n-------- new command ------------------------------------------\n")
      log.write(command+"\n")
      log.write("start: "+datetime.datetime.now().strftime("%d.%m.%Y %H:%M:%S")+"\n")

    subprocess.check_call(command, shell=True)

    with open('log.txt','ab') as log:
      log.write("end:   "+datetime.datetime.now().strftime("%d.%m.%Y %H:%M:%S")+"\n\n")
  except subprocess.CalledProcessError as exc:
    with open('log.txt', 'ab') as log:
      log.write('Command failed, return code: '+str(exc.returncode)+"\n")
  else:
    with open('log.txt', 'ab') as log:
      log.write("Command successful\n")

    pass
  
# load modules
cmd = "module restore /lustre/cray/ws8/ws/icbbnmai-iron/manage/build_release/gcc49.module_snapshot"
try:
  subprocess.check_call(cmd, shell=True)
except:
  print "not on hazel hen!"



n_start = 1   # size of smallest problem to begin with
last_total = 0

ax = 1        # number of elements in x-direction in atom (non-decomposable block of elements)
ode = 1       # 1 explicit Euler, 2 BDF
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
mprecond = 1   # 1 NO_PRECONDITIONER, 2 JACOBI_PRECONDITIONER, 3 BLOCK_JACOBI_PRECONDITIONER, 4 SOR_PRECONDITIONER, 5 INCOMPLETE_CHOLESKY_PRECONDITIONER, 6 INCOMPLETE_LU_PRECONDITIONER, 7 ADDITIVE_SCHWARZ_PRECONDITIONER

nodes = 0

if len(sys.argv) > 1:
  nodes = int(sys.argv[1])
print "nodes = ",nodes

if nodes == 0 or nodes == 1:
  run(1*24, 2,12,8, 1,6,4, 2,2,2)   # pillars
  run(1*24, 2,12,8, 1,6,4, 2,2,2)   # cubes

if nodes == 0 or nodes == 2:
  run(2*24, 4,12,8, 1,6,8, 4,2,1)   # pillars
  run(2*24, 4,12,8, 2,6,4, 2,2,2)   # cubes

if nodes == 0 or nodes == 4:
  run(4*24, 4,12,16, 1,12,8, 4,1,2)   # pillars
  run(4*24, 4,12,16, 2,6,8, 2,2,2)   # cubes

if nodes == 0 or nodes == 8:
  run(8*24, 4,24,16, 1,12,16, 4,2,1)   # pillars
  run(8*24, 4,24,16, 2,12,8, 2,2,2)   # cubes

if nodes == 0 or nodes == 16:
  run(16*24, 8,24,16, 1,24,16, 8,1,1)   # pillars
  run(16*24, 8,24,16, 4,12,8, 2,2,2)   # cubes

if nodes == 0 or nodes == 32:
  run(32*24, 8,24,32, 1,24,32, 8,1,1)   # pillars
  run(32*24, 8,24,32, 4,12,16, 2,2,2)   # cubes

if nodes == 0 or nodes == 64:
  run(64*24, 8,48,32, 1,48,32, 8,1,1)   # pillars
  run(64*24, 8,48,32, 4,24,16, 2,2,2)   # cubes

