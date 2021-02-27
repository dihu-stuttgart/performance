Testing different solvers for bidomain (EMG):

PBS_NODEFILE=${NEW_PBS_NODEFILE} mpirun -np $XYZ omplace -vv -c 0-127:2 \
${EXAMPLE_HOME}/build_release/fast_fibers_emg \
     ${EXAMPLE_HOME}/settings_fibers_emg.py --dt_0D 1e-3 --dt_1D 2e-3 --dt_splitting 2e-3 --dt_3D 1.0 --end_time 100.0 \
    --scenario_name hawk_weak_scaling_debug \
    --n_subdomains $X $Y $Z \
    --fiber_file   input/left_biceps_brachii_${F}x${F}fibers.bin \
    --emg_solver_type cg \
    --emg_preconditioner_type gamg \
    --emg_initial_guess_nonzero \
    --firing_times_file input/MU_firing_times_immediately.txt \
    --disable_firing_output \
    --enable_weak_scaling \
    --fiber_distribution_file input/MU_fibre_distribution_3780.txt \
    --cellml_file input/hodgkin_huxley_1952.c \
    --emg_solver_abstol 1e-5 \
    --emg_solver_reltol 1e-5

scenario with 448 ranks (7 Hawk nodes), 67^2=  4489 fibers

all with --emg_initial_guess_nonzero:
--emg_solver_type cg --emg_preconditioner_type none: Total user time: 1:43.77 min
--emg_solver_type cg --emg_preconditioner_type gamg: Total user time: 1:42.77 min
--emg_solver_type cg --emg_preconditioner_type boomeramg: terminates, no error messageMPT ERROR: MPI_COMM_WORLD rank 389 has terminated without calling MPI_Finalize()
--emg_solver_type cg --emg_preconditioner_type euclid: terminates, no error messageMPT ERROR: MPI_COMM_WORLD rank 389 has terminated without calling MPI_Finalize()
--emg_solver_type gmres --emg_preconditioner_type none: Total user time: 1:45.42 min

without --emg_initial_guess_nonzero:
--emg_solver_type gmres --emg_preconditioner_type none: Total user time: 1:54.25 min
--emg_solver_type cg --emg_preconditioner_type none: Total user time: 1:43.84 min
