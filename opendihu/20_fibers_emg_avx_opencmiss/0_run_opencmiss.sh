#!/bin/bash

# model: monodomain, emg on biceps geometry (0D,1D,3D)
# same cellml model as in OpenCMISS
# run fibers_emg with opendihu using avx-512 on pcsgs05
# potentially also with OpenMP and GPU

# Set $OPENDIHU_HOME and $OPENCMISS_HOME accordingly!
export OPENCMISS_HOME=/data/scratch/maierbn/opencmiss/
dir=$(pwd)

# 2. run opencmiss cuboid example
cuboid_dir=$OPENCMISS_HOME/src/iron-examples/cuboid/build_release/Fortran

# create own directory where the simulation is run and all output files are written
cd $dir
mkdir -p opencmiss_run && cd opencmiss_run && rm -rf *

# run example
# (3*3) x (3*3) fibers, (2*740)+1 nodes in fiber direction (x direction in opencmiss)


(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_01.txt sleep 60) &
mpirun -n 1  $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_01.txt

(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_02.txt sleep 60) &
mpirun -n 2  $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_02.txt

(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_04.txt sleep 60) &
mpirun -n 4  $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_04.txt

(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_08.txt sleep 60) &
mpirun -n 8  $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_08.txt

(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_12.txt sleep 60) &
mpirun -n 12 $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_12.txt

(sleep 90; perf stat -a -e task-clock,cycles,instructions,branches,branch-misses -e cache-references,cache-misses -e LLC-loads,LLC-load-misses,LLC-stores,LLC-store-misses -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,L1-dcache-store-misses -e r5301d1,r5302d1,r5304d1,r5308d1,r5310d1,r5320d1,r5380d1,r5301c7,r5302c7,r5304c7,r5308c7,r5310c7,r5320c7,r5340c7,r5380c7 -o perf_18.txt sleep 60) &
mpirun -n 18 $cuboid_dir/cuboid ../opencmiss_settings.sce ../opencmiss_input | tee log_18.txt


cd $dir


