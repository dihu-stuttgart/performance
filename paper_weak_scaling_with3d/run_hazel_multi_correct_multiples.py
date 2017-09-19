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

def run(nproc,pretended_p,x,y,z,ax,ay,az): # nnodes = number of nodes, nproc = number of processes, pretended_p = number of proc. to start domain decomposition with
  
  (used_number_of_processes, subdomain_shape) = domain_decomposition.number_of_processes(nproc,x,y,z,ax,ay,az)
  print "Number of subdomains: ",used_number_of_processes, ", shape of subdomain: ", subdomain_shape

  ode = 1
  msolver = 1
  precond = 1
  
  j = "-j1"  # no hyperthreading
#  if p > 12:
#    j = "-j2"  # hyperthreading
#  else:
#    j = "-j1"  # no hyperthreading

  command = "aprun -n {nproc} -N {ppn} {j} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x} y={y} z={z} ax={ax} ay={ay} az={az} "\
            "PretendedNumberOfDomains={pretended_p} ODESolverId={ode} MonodomainSolverId={msolver} MonodomainPreconditionerId={mprecond}"\
            .format(nproc=int(nproc), ppn=24, j=j, x=int(x), y=int(y), z=int(z), ax=int(ax), ay=int(ay), az=int(az), pretended_p=pretended_p, ode=ode, msolver=msolver, mprecond=mprecond)

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

# total 12288
initial_x = 32
initial_y = 24
initial_z = 16
ax_cubic = 8
f = 1

initial_x = 2
initial_y = 12
initial_z = 8
ax_cubic = 2
f = 0.5

a = 1
if len(sys.argv) > 1:
  a = int(sys.argv[1]);

# compute factor to inital element numbers in coordinate directions
factor = int(np.round(a**(1./3)))
number = int(np.log(factor)/np.log(2))
print "number of nodes a = ",a, ", factor = ", factor, ", number ", number

# compute number of elements
ex = initial_x * factor
ey = initial_y * factor
ez = initial_z * factor

# cubic domains
ax = ax_cubic
ay = ax_cubic
az = ax_cubic
run(a*24,a*24,ex,ey,ez,ax,ay,az)
    
# pillar-like domains
ax = ex
if number == 0:
  ay = int(4*f)
  az = int(4*f)
elif number == 1:
  ay = int(4*f)
  az = int(2*f)
elif number == 2:
  ay = int(2*f)
  az = int(2*f)
elif number == 3:
  ay = 2
  az = 1
elif number == 4:
  ay = 1
  az = 1
run(a*24,a*24,ex,ey,ez,ax,ay,az)
