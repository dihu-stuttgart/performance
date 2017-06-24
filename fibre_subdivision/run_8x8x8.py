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

  #print command; return
  try:
    subprocess.check_call(command, shell=True)
  except:
    pass


x = 8
y = 8
z = 8
p = 64        # 4*4*4 = 64

# fibre on 1 process
ax = 8
run(p,x,y,z,ax)

# fibre on 2 processes
ax = 4
run(p,x,y,z,ax)

# fibre on 4 processes
ax = 2
run(p,x,y,z,ax)
