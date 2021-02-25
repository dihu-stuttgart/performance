#!/usr/bin/bash

example_dir=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_emg
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input
work_dir=$(pwd)

module purge
module load cuda-10.2 argon-tesla/gcc/10.2-openmp-custom openmpi/3.1.6-gcc-10.2
module list

# strong scaling: number of processes ∈ {1,2,4,8,12,18}

# run with vc
for nproc in 1 2 4 8 12 18; do

mpirun -n $nproc $example_dir/build_release/fast_fibers_emg \
  $example_dir/settings_fibers_emg.py \
  $work_dir/hodgkin_huxley_gpu.py \
  --optimization_type="vc" \
  --scenario_name="vc-$nproc" | tee logs/log_vc_$nproc.txt
done

module purge
module load cuda-10.2 argon-tesla/gcc/11-20210110-openmp openmpi/3.1.6-gcc-11
module list

# run on gpu
for nproc in 1 2 4 8 12 18; do

mpirun -n $nproc $example_dir/build_release/fast_fibers_emg \
  $example_dir/settings_fibers_emg.py \
  $work_dir/hodgkin_huxley_gpu.py \
  --optimization_type="gpu" \
  --scenario_name="gpu-$nproc" | tee logs/log_gpu_$nproc.txt

done
