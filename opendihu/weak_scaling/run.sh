#!/bin/bash


# PRGENV has to be either "gnu" or "cray"
export OMP_NUM_THREADS=1
export OPENDIHU_HOME=/lustre/cray/ws8/ws/icbbnmai-opendihu/opendihu-${PRGENV}
export EXAMPLE_HOME=$OPENDIHU_HOME/examples/electrophysiology/fibers_emg
export SETTINGS_FILE=$EXAMPLE_HOME/settings_fibers_emg.py

echo "PBS_NUM_NODES=$PBS_NUM_NODES"

if [ "$PBS_NUM_NODES" -eq "1" ]; then
NP=24
SCENARIO_NAME=${PRGENV}_24
X=2
Y=3
Z=4
FIBER_FILE=../../input/43x43fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "6" ]; then
NP=125
SCENARIO_NAME=${PRGENV}_125
X=5
Y=5
Z=5
FIBER_FILE=../../input/85x85fibers.bin
fi


if [ "$PBS_NUM_NODES" -eq "8" ]; then
NP=192
SCENARIO_NAME=${PRGENV}_192
X=3
Y=4
Z=16
FIBER_FILE=../../input/43x43fibers.bin
CPU_BINDING_FILE="yes"
fi


if [ "$PBS_NUM_NODES" -eq "10" ]; then
NP=240
SCENARIO_NAME=${PRGENV}_240
X=8
Y=6
Z=5
FIBER_FILE=../../input/85x85fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "43" ]; then 
NP=1024
SCENARIO_NAME=${PRGENV}_1024
X=16
Y=16
Z=4
FIBER_FILE=../../input/295x295fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "417" ]; then
NP=10000
SCENARIO_NAME=${PRGENV}_1e4
X=25
Y=25
Z=16
FIBER_FILE=../../input/393x393fibers.bin
CPU_BINDING_FILE=yes
#533x533fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "2091" ]; then
NP=50176
SCENARIO_NAME=${PRGENV}_5e4
X=56
Y=56
Z=16
FIBER_FILE=../../input/533x533fibers.bin
fi
 
#  --cpu-binding-file ./$CPU_BINDING_FILE \
#--cp ./$CPU_BINDING_FILE \
if [[ ! -z "$CPU_BINDING_FILE" ]]; then
  echo "aprun --cpu-binding $($OPENDIHU_HOME/scripts/generate_cpu_list.py $X $Y $Z) --pes-per-node 24 -n $NP $EXAMPLE_HOME/build_release/fibers_emg $SETTINGS_FILE --scenario_name $SCENARIO_NAME --n_subdomains $X $Y $Z --fiber_file $FIBER_FILE"
  aprun \
  --cpu-binding $($OPENDIHU_HOME/scripts/generate_cpu_list.py $X $Y $Z) \
  --pes-per-node 24 \
  -n $NP \
  $EXAMPLE_HOME/build_release/fibers_emg $SETTINGS_FILE \
    --scenario_name $SCENARIO_NAME \
    --n_subdomains $X $Y $Z \
    --fiber_file $FIBER_FILE
else
  echo "aprun --pes-per-node 24 -n $NP $EXAMPLE_HOME/build_release/fibers_emg $SETTINGS_FILE --scenario_name $SCENARIO_NAME --n_subdomains $X $Y $Z --fiber_file $FIBER_FILE"
  aprun \
  --pes-per-node 24 \
  -n $NP \
  $EXAMPLE_HOME/build_release/fibers_emg $SETTINGS_FILE \
    --scenario_name $SCENARIO_NAME \
    --n_subdomains $X $Y $Z \
    --fiber_file $FIBER_FILE

fi
