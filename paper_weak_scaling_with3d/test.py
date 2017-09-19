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
os.environ['OPENCMISS_SCE_FILE'] = 'weak_scaling_multi.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(nproc,x,y,z,xi1,ax): # nnodes = number of nodes, nproc = number of processes
  
  ode = 1
  msolver = 1
  precond = 1
  
  j = "-j2"
#  if p > 12:
#    j = "-j2"  # hyperthreading
#  else:
#    j = "-j1"  # no hyperthreading

  command = "aprun -n {nproc} -N 48 {j} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x} y={y} z={z} xi1={xi1} ax={ax} "\
            "ODESolverId={ode} MonodomainSolverId={msolver} MonodomainPreconditionerId={mprecond}"\
            .format(nproc=int(nproc), j=j, x=int(x), y=int(y), z=int(z), xi1=int(xi1), ax=int(ax), ode=ode, msolver=msolver, mprecond=mprecond)

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
subprocess.check_call(cmd, shell=True)



n_start = 1   # size of smallest problem to begin with
last_total = 0

ax = 1        # number of elements in x-direction in atom (non-decomposable block of elements)
ode = 1       # 1 explicit Euler, 2 BDF
msolver = 1   # 1 SOLVER_DIRECT_LU, 2 SOLVER_ITERATIVE_GMRES, 3 SOLVER_ITERATIVE_CONJUGATE_GRADIENT, 4 SOLVER_ITERATIVE_CONJGRAD_SQUARED
mprecond = 1   # 1 NO_PRECONDITIONER, 2 JACOBI_PRECONDITIONER, 3 BLOCK_JACOBI_PRECONDITIONER, 4 SOR_PRECONDITIONER, 5 INCOMPLETE_CHOLESKY_PRECONDITIONER, 6 INCOMPLETE_LU_PRECONDITIONER, 7 ADDITIVE_SCHWARZ_PRECONDITIONER

xi1 = 20

initial_x = 12
initial_y = 2
initial_z = 8

initial_x = 5
initial_y = 2
initial_z = 2

a = 1
if len(sys.argv) > 1:
	a = int(sys.argv[1]);
print "number of nodes a = ",a

#for p in range(1,13)+range(12,25,2):
for p in [a*48]:

  
  for fibres_undivided in [True, False]:
    
    ax = 1
    ay = 1
    az = 1
    
    # total number of elements expected for factor p
    total = initial_x*initial_y*initial_z*p

    # compute x,y,z such that x*y*z is close to total and the relation between x,y,z is close to the relation of initial_x, initial_y, initial_z
    c1 = 10   # weighting factor for error to total number of elements
    c2 = 1    # weighting factor for error to relation between x,y,z and initial_x,initial_y,initial_z
    c3 = 10   # weighting factor for error to used number of processes
    
    factor = p ** (1./3)    # factor how the optimal value of x,y,z should be w.r.t initial_x,initial_y,initial_z (but would be non-integer)
    
    best = [0,0,0,0]
    best_badness = 100000000
    
    # loop over all possible combinations for x,y,z and find the best according to an error (badness)
    for x in range(int(0.5*initial_x*factor), int(2*initial_x*factor)):
      for y in range(int(0.5*initial_y*factor), int(2*initial_y*factor)):
        for z in range(int(0.5*initial_z*factor), int(2*initial_z*factor)):
          
          
          if fibres_undivided:
            ax = x
          
          # compute relative error to desired total number
          error_total = 1.0 - float(x*y*z) / total
          
          # compute relative errors to desired relations
          error_x = 1.0 - float(x) / (initial_x*factor)
          error_y = 1.0 - float(y) / (initial_y*factor)
          error_z = 1.0 - float(z) / (initial_z*factor)
          
          # compute relative error to number of processes
          used_number_of_processes = domain_decomposition.number_of_processes(p,x,y,z,ax,ay,az)
          error_p = 1.0 - float(used_number_of_processes) / p
          
          # compute badness value as weighted sum of squared errors
          badness = c1 * error_total**2 + c2 * (error_x**2 + error_y**2 + error_z**2) + c3 * error_p**2

          # if badness is the lowest so far, store values
          if badness < best_badness:
            best_badness = badness
            best = [used_number_of_processes,x,y,z]
            
            # debugging output
            if False:
              print "p={}({}),{},{},{}={},  ideal: {},{},{}={}, error x{},y{},z{},t{},p{}, badness: {}+{}+{}={}".format(\
                p, used_number_of_processes,\
                x,y,z,x*y*z,\
                initial_x*factor,initial_y*factor,initial_z*factor,total,\
                error_x,error_y,error_z,error_total,error_p,\
                c1*error_total**2, c2 * (error_x**2 + error_y**2 + error_z*2),c3*error_p**2,badness)

    # use found values
    [used_number_of_processes,x,y,z] = best
    if fibres_undivided:
      ax = x
    
    error_p = 1.0 - float(used_number_of_processes) / p
    
    
    print "p =",p," (used:",used_number_of_processes,"), x,y,z=[",x,y,z,"] badness: ",best_badness,", error nel: ",1.0 - float(x*y*z) / total,", error p:",error_p
#    print "p = {} (used: {}), [x,y,z]=[{},{},{}], badness: {}, error nel: {}, error p: {}".\
#    format(p,used_number_of_processes, x,y,z, best_badness,1.0 - float(x*y*z) / total, error_p)
  
  
    check_exit()
    run(used_number_of_processes,x,y,z,xi1,ax)
    
