#!/usr/bin/env python
# -*- coding: utf-8 -*-

# parallel weak scaling

import sys
import numpy as np
import subprocess
import datetime
import time
import os

n_available_nodes = 10000000
if len(sys.argv) > 1:
  n_available_nodes = (int)(sys.argv[1])

emg_solver_type = None
if len(sys.argv) > 2:
  emg_solver_type = sys.argv[2]

print("n_available_nodes: {}".format(n_available_nodes))

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
  global emg_solver_type 
  opendihu_home = os.environ.get("OPENDIHU_HOME")
  if opendihu_home == "":
    print("Error! $OPENDIHU_HOME is not set!")
    return
    
  pes_per_node = min(24,x*y*z)
  example_home = os.path.join(opendihu_home, "examples/electrophysiology/fibers_emg")
  settings_file = os.path.join(example_home, "settings_fibers_emg.py")

  scenario_name = "weak_scaling_{}_{}_{}".format(x,y,z)

  fiber_file = "../../input/{n}x{n}fibers.bin".format(n=n_fibers_per_dimension)
  #firing_times_file = "../../input/MU_firing_times_immediately.txt"
  firing_times_file = "../../input/MU_firing_times_real.txt"
  if emg_solver_type is None:
    emg_solver_type = "gmres"
  else:
    scenario_name += "_"

  sleep_duration = (int)(n_available_nodes % 10);

  command = "sleep {DURATION}; export MPICH_RANK_REORDER_METHOD=3; echo $({OPENDIHU_HOME}/scripts/generate_cpu_list.py {X} {Y} {Z}) > MPICH_RANK_ORDER; echo '{n_available_nodes} available compute nodes';\
  aprun \
  --pes-per-node {N} \
  -n {NP} \
  {EXAMPLE_HOME}/build_release/fibers_emg {SETTINGS_FILE} \
    --scenario_name {SCENARIO_NAME} \
    --n_subdomains {X} {Y} {Z} \
    --fiber_file {FIBER_FILE} \
    --emg_solver_type {EMG_SOLVER_TYPE} \
    --emg_initial_guess_nonzero \
    --firing_times_file {FIRING_TIMES_FILE} \
    --end_time 1.0 \
    --disable_firing_output \
".format(OPENDIHU_HOME=opendihu_home, X=x, Y=y, Z=z, NP=x*y*z, N=pes_per_node, EXAMPLE_HOME=example_home, SETTINGS_FILE=settings_file, SCENARIO_NAME=scenario_name, FIBER_FILE=fiber_file, n_available_nodes=n_available_nodes, FIRING_TIMES_FILE=firing_times_file, EMG_SOLVER_TYPE=emg_solver_type, DURATION=sleep_duration)

  print("partitioning {:2d}*{:2d}*{:2d}={:5d}  {:3d}^2={:6d} fibers, fibers/rank: {:5f}, need {:4d} nodes".format(x,y,z,x*y*z, n_fibers_per_dimension, n_fibers_per_dimension**2, float(n_fibers_per_dimension**2)/(x*y*z), int(np.ceil((x*y*z)/24.))))
  #return

  #print(command); return 
  print(command)

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

import datetime
now = datetime.datetime.now()
print(" ======= run.py =======") 
print(now.strftime("%d/%m/%Y %H:%M:%S"))

# old
partitionings = [
  [2,  2,  1,    7],
  [3,  3,  2,   15],
  [4,  5,  4,   29],
  [5,  6,  6,   43],
  [7,  8,  12,  85],
  [19, 19, 24, 295],
  [25, 25, 24, 393],
  [27, 27, 24, 435],
  [34, 34, 24, 533],
]

# new
partitionings = [ 
  [2,  2,  1,   7], 
  [3,  3,  2,  13],
  [4,  4,  4,  25],
  [5,  5,  6,  37],
  [7,  8,  8,  67], 
  [10, 10, 12, 109],
  [17, 17, 12, 187],
  [18, 18, 24, 277],
  [27, 27, 24, 427],
  [34, 34, 24, 523],
]



#partitioning = partitionings[1]
#run(partitioning[0], partitioning[1], partitioning[2], partitioning[3])
#quit()

for partitioning in partitionings:
  
  n_ranks = partitioning[0] * partitioning[1] * partitioning[2]
  n_nodes = int(np.ceil(n_ranks/24.))
 
  if n_available_nodes > 3 and n_nodes < n_available_nodes:
    continue 
  if n_nodes > n_available_nodes:
    break
  run(partitioning[0], partitioning[1], partitioning[2], partitioning[3])
  
"""
old: 
partitioning  2* 2* 1=    4    7^2=    49 fibers, fibers/rank: 12.250000, need    1 nodes
partitioning  3* 3* 2=   18   15^2=   225 fibers, fibers/rank: 12.500000, need    1 nodes
partitioning  4* 5* 4=   80   29^2=   841 fibers, fibers/rank: 10.512500, need    4 nodes
partitioning  5* 6* 6=  180   43^2=  1849 fibers, fibers/rank: 10.272222, need    8 nodes
partitioning  7* 8*12=  672   85^2=  7225 fibers, fibers/rank: 10.751488, need   28 nodes
partitioning 19*19*24= 8664  295^2= 87025 fibers, fibers/rank: 10.044437, need  361 nodes
partitioning 25*25*24=15000  393^2=154449 fibers, fibers/rank: 10.296600, need  625 nodes
partitioning 27*27*24=17496  435^2=189225 fibers, fibers/rank: 10.815329, need  729 nodes
partitioning 34*34*24=27744  533^2=284089 fibers, fibers/rank: 10.239655, need 1156 nodes

new:
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

"""
