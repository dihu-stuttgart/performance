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
os.environ['OPENCMISS_SCE_FILE'] = 'subdivision.sce'

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(p,x,y,z,ax):
  command = "mpirun -n {p} $OPENCMISS_REL_DIR/cuboid $OPENCMISS_SCE_FILE $OPENCMISS_INPUT_DIR x={x}, y={y}, z={z}, ax={ax}".\
    format(p=int(p), x=int(x), y=int(y), z=int(z), ax=int(ax))

  print command; return
  try:
    subprocess.check_call(command, shell=True)
  except:
    pass


n_start = 1   # size of smallest problem to begin with
last_total = -1
for n in range(n_start,14):
  x = int(np.round(1.2**n)/2) * 2
  y = x
  z = x
  total = x*y*z
  
  if total == last_total or total == 0:
    continue
 
  last_total = total

  p = total/8

  print "n=",n,",x=",x,",y=",y,",z=",z,",total=",total,",p=",p
  check_exit()
  
  # no subdivision
  xa = x
  run(p,x,y,z,xa)
  
  # fibre on 2 processes
  xa = np.ceil(x/2.)
  run(p,x,y,z,xa)

  # fibre on 4 processes
  xa = np.ceil(x/4.)
  run(p,x,y,z,xa)
  
  # fibre on 8 processes
  xa = np.ceil(x/8.)
  run(p,x,y,z,xa)
