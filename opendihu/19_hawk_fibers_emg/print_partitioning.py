#!/usr/bin/env python
# -*- coding: utf-8 -*-

# parallel weak scaling

import sys
import numpy as np
import subprocess
import datetime
import time
import os

"""
7x7fibers.bin                49
15x15fibers.bin             225
29x29fibers.bin             841
43x43fibers.bin           1.849
85x85fibers.bin           7.225
295x295fibers.bin        87.025
393x393fibers.bin       154.449
435x435fibers.bin       189.225
533x533fibers.bin       284.089
785x785fibers.bin       616.225
"""

def run(x,y,z,n_fibers_per_dimension):
  print("partitioning {:2d}*{:2d}*{:2d}={:5d}  {:3d}^2={:6d} fibers, fibers/rank: {:5f}, need {:4d} nodes".format(x,y,z,x*y*z, n_fibers_per_dimension, n_fibers_per_dimension**2, float(n_fibers_per_dimension**2)/(x*y*z), int(np.ceil((x*y*z)/64.))))

import datetime
now = datetime.datetime.now()
print(now.strftime("%d/%m/%Y %H:%M:%S"))

# hawk
partitionings = [ 
  [2,  2,  1,   7], 
  [3,  3,  2,  13],
  [4,  4,  4,  25],
  [6,  6,  4,  37],
  [7,  8,  8,  67], 
  [12, 12, 8,  109],
  [15, 15, 16, 187],
  [22, 22, 16, 277],
  [24, 24, 32, 427],
  [29, 29, 32, 523],
  [40, 40, 32, 523],
]

for partitioning in partitionings:
  
  n_ranks = partitioning[0] * partitioning[1] * partitioning[2]
  n_nodes = int(np.ceil(n_ranks/24.))
 
  run(partitioning[0], partitioning[1], partitioning[2], partitioning[3])
  
"""
old hazelhen: 
partitioning  2* 2* 1=    4    7^2=    49 fibers, fibers/rank: 12.250000, need    1 nodes
partitioning  3* 3* 2=   18   15^2=   225 fibers, fibers/rank: 12.500000, need    1 nodes
partitioning  4* 5* 4=   80   29^2=   841 fibers, fibers/rank: 10.512500, need    4 nodes
partitioning  5* 6* 6=  180   43^2=  1849 fibers, fibers/rank: 10.272222, need    8 nodes
partitioning  7* 8*12=  672   85^2=  7225 fibers, fibers/rank: 10.751488, need   28 nodes
partitioning 19*19*24= 8664  295^2= 87025 fibers, fibers/rank: 10.044437, need  361 nodes
partitioning 25*25*24=15000  393^2=154449 fibers, fibers/rank: 10.296600, need  625 nodes
partitioning 27*27*24=17496  435^2=189225 fibers, fibers/rank: 10.815329, need  729 nodes
partitioning 34*34*24=27744  533^2=284089 fibers, fibers/rank: 10.239655, need 1156 nodes

new hazelhen:
partitioning  2* 2* 1=    4    7^2=    49 fibers, fibers/rank: 12.250000, need    1 nodes
partitioning  3* 3* 2=   18   13^2=   169 fibers, fibers/rank: 9.388889, need    1 nodes
partitioning  4* 4* 4=   64   25^2=   625 fibers, fibers/rank: 9.765625, need    3 nodes
partitioning  5* 5* 6=  150   37^2=  1369 fibers, fibers/rank: 9.126667, need    7 nodes
partitioning  7* 8* 8=  448   67^2=  4489 fibers, fibers/rank: 10.020089, need   19 nodes
partitioning 10*10*12= 1200  109^2= 11881 fibers, fibers/rank: 9.900833, need   50 nodes
partitioning 17*17*12= 3468  187^2= 34969 fibers, fibers/rank: 10.083333, need  145 nodes
partitioning 18*18*24= 7776  277^2= 76729 fibers, fibers/rank: 9.867413, need  324 nodes
partitioning 27*27*24=17496  427^2=182329 fibers, fibers/rank: 10.421182, need  729 nodes
partitioning 34*34*24=27744  523^2=273529 fibers, fibers/rank: 9.859033, need 1156 nodes
partitioning 46*46*24=50784  523^2=273529 fibers, fibers/rank: 5.386125, need 2116 nodes

hawk:
partitioning  2* 2* 1=    4    7^2=    49 fibers, fibers/rank: 12.250000, need    1 nodes
partitioning  3* 3* 2=   18   13^2=   169 fibers, fibers/rank: 9.388889, need    1 nodes
partitioning  4* 4* 4=   64   25^2=   625 fibers, fibers/rank: 9.765625, need    1 nodes
partitioning  6* 6* 4=  144   37^2=  1369 fibers, fibers/rank: 9.506944, need    3 nodes
partitioning  7* 8* 8=  448   67^2=  4489 fibers, fibers/rank: 10.020089, need    7 nodes
partitioning 12*12* 8= 1152  109^2= 11881 fibers, fibers/rank: 10.313368, need   18 nodes
partitioning 15*15*16= 3600  187^2= 34969 fibers, fibers/rank: 9.713611, need   57 nodes
partitioning 22*22*16= 7744  277^2= 76729 fibers, fibers/rank: 9.908187, need  121 nodes
partitioning 24*24*32=18432  427^2=182329 fibers, fibers/rank: 9.891981, need  288 nodes
partitioning 29*29*32=26912  523^2=273529 fibers, fibers/rank: 10.163830, need  421 nodes
partitioning 40*40*32=51200  523^2=273529 fibers, fibers/rank: 5.342363, need  800 nodes
"""
