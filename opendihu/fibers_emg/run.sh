#!/bin/bash

export OMP_NUM_THREADS=1
export OPENDIHU_HOME=/lustre/cray/ws8/ws/icbbnmai-opendihu/opendihu-gnu
export EXAMPLE_HOME=$OPENDIHU_HOME/examples/electrophysiology/fibers_emg

echo "PBS_NUM_NODES=$PBS_NUM_NODES"

if [ "$PBS_NUM_NODES" -eq "1" ]; then
#aprun --pes-per-node 24 -n 24 $EXAMPLE_HOME/build_release/fibers_emg settings43.py fibers43_cg 2 3 4 cg ../../input/43x43fibers.bin
aprun --pes-per-node 24 -n 24 $EXAMPLE_HOME/build_release/fibers_emg settings43.py fibers43_lu 2 3 4 lu ../../input/43x43fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "6" ]; then
aprun --pes-per-node 24 -n 125 $EXAMPLE_HOME/build_release/fibers_emg settings85.py fibers85 5 5 5 cg ../../input/85x85fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "10" ]; then
aprun --pes-per-node 24 -n 240 $EXAMPLE_HOME/build_release/fibers_emg settings85.py fibers85+ 8 6 5 cg ../../input/85x85fibers.bin
fi

if [ "$PBS_NUM_NODES" -eq "43" ]; then 
aprun --pes-per-node 24 -n 1024 $EXAMPLE_HOME/build_release/fibers_emg settings533.py fibers533 16 16 4 cg ../../input/533x533fibers.bin
fi

 
