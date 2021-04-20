#!/bin/bash

# model: monodomain, emg on biceps geometry and on fat layer (0D,1D,3D)
# run fibers_fat_emg

dir=$(pwd)

example_dir=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_fat_emg
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input

# run example
mpirun -n 64 $example_dir/build_release/fibers_fat_emg \
  $example_dir/settings_fibers_fat_emg.py $dir/20mus.py
