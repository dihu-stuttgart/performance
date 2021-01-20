
# argon-tesla2, last process has optimization_type=gpu, rest has optimization_type=vc
# machine is not completely empty, some ML, but on GPU 2, we use GPU 1
# built using gcc 11, 7x7 fibers

module purge
module load cuda-10.2 argon-tesla/gcc/11-20201227-openmp argon-tesla/openmpi/4.0.5-gcc11
module list

export EXAMPLE_DIR=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_emg

# with one process GPU
# manually adjust the following in settings_fibers_emg.py (line ~272)
# "optimizationType":                       "gpu" if rank_no == n_ranks-1 else "vc",

#mpirun -n 27 $EXAMPLE_DIR/build_release/fast_fibers_shorten_emg $EXAMPLE_DIR/settings_fibers_emg.py shorten.py --n_subdomains 3 3 3 --end_time 10 --scenario_name tesla2-gpu-hybrid

# pure CPU, use standard settings
mpirun -n 27 $EXAMPLE_DIR/build_release/fast_fibers_shorten_emg $EXAMPLE_DIR/settings_fibers_emg.py shorten.py --n_subdomains 3 3 3 --end_time 10 --scenario_name tesla2-cpu


