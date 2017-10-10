#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from threading import Thread
from time import sleep
import sys
import subprocess

def check_exit():
  
  return    # disable time check
  
  now = datetime.datetime.now()
  if now.hour >= 7 and now.hour < 20:  # wait if 7 <= hour <= 20
    print "Don't run program because it is between 7 and 20."
    time.sleep(60*60)
  else:
    print "OK"

def run(splitting_type,n_0D,n_1D):   
  # splitting_type: 0 = Godunov splitting, 1 = Strang splitting

  command = "python ./single.py {splitting_type} {n_0D} {n_1D} "\
  .format(splitting_type=splitting_type, n_0D=n_0D, n_1D=n_1D)

  #print command
  try:
    print command
    subprocess.check_call(command, shell=True)
  except:
    pass


n_1D = 10 
if len(sys.argv) > 1:
  n_1D = int(sys.argv[1])
print "n_1D=",n_1D

#for n_1D in [2**n for n in range(50)]:
#  threads = []
if True:
  #for n_0D in [int(np.round(2**n)) for n in range(10)]:
  for n_0D in [1,2]:
    for splitting_type in [0, 1]:
      run(splitting_type,n_0D,n_1D)

#      thread = Thread(target = run, args = (splitting_type,n_0D,n_1D))
#      thread.start()
#      threads.append(thread)

#  for thread in threads:
#    thread.join()

