#!/bin/bash

# model: monodomain, emg on biceps geometry (0D,1D,3D)
# same cellml model as in OpenCMISS
# run fibers_emg with opendihu using avx-512 on pcsgs05
# potentially also with OpenMP and GPU

# Set $OPENDIHU_HOME and $OPENCMISS_HOME accordingly!
dir=$(pwd)

# 1. run opendihu fibers_emg example
example_dir=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_emg
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input

# create own directory where the simulation is run and all output files are written
cd $dir
mkdir -p opendihu_run && cd opendihu_run

# run example
# 9x9 fibers with 1481 nodes each
# run on gpu: double, 1 fiber
#$example_dir/build_release/fast_fibers_shorten_emg_crank_nicolson \
#  $example_dir/settings_fibers_emg.py ../opendihu_variables.py \
#  --optimization_type="gpu" --scenario_name="gpu-double-1fiber" | tee log_gpu-double-1fiber.txt

# run on gpu: float, all fibers, does not work

# run with vc, strong scaling: number of processes ∈ {1,2,4,8,12,18}
for nproc in 1 2 4 8 12 18; do

(sleep 15; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_${nproc}_ws.txt sleep 30) &

mpirun -n $nproc $example_dir/build_release/fast_fibers_shorten_emg_crank_nicolson \
  $example_dir/settings_fibers_emg.py ../opendihu_variables.py \
  --enable_weak_scaling \
  --optimization_type="vc" \
  --scenario_name="vc-$nproc-ws" | tee log_${nproc}_ws.txt


(sleep 15; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_${nproc}_opt.txt sleep 15) &

mpirun -n $nproc $example_dir/build_release/fast_fibers_shorten_emg_crank_nicolson \
  $example_dir/settings_fibers_emg.py ../opendihu_variables.py \
  --optimization_type="vc" \
  --scenario_name="vc-$nproc-opt" | tee log_${nproc}_opt.txt

done

