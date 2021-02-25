example_dir=$OPENDIHU_HOME/examples/electrophysiology/multidomain/multidomain_with_fat

killall -9 multidomain_shorten_with_fat

##for preconditioner in euclid bjacobi sor pilut none; do
#for preconditioner in boomeramg; do
#for preconditioner in bjacobi sor; do
#for preconditioner in bjacobi; do
##for symmetric in " " "--use_symmetric_preconditioner_matrix"; do
#for symmetric in " -sub_ksp_type preonly -sub_pc_type ilu"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type gamg"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type hypre -sub_pc_hypre_type euclid"; do

preconditioner=euclid
symmetric=" "


#valgrind --tool=memcheck --log-file=valgrind-log-%p.txt --suppressions=$OPENDIHU_HOME/dependencies/python/src/Python-3.6.5/Misc/valgrind-python.supp \

killall -9 multidomain_shorten_with_fat; sleep 1

# ------------
# experiment 2
# 2 ranks
mpirun -n 2 \
$example_dir/build_release_with_debug_info/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study_big.py \
--multidomain_preconditioner_type $preconditioner \
--sampling_stride_x 2     \
--sampling_stride_y 2     \
--sampling_stride_z 32    \
--dt_0D             4e-4  \
--dt_multidomain    4e-4  \
--dt_splitting      4e-4  \
--scenario_name="s2$symmetric" \
$symmetric

killall -9 multidomain_shorten_with_fat; sleep 1
if false; then
# 64 ranks
mpirun -n 64 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study_big.py \
--multidomain_preconditioner_type $preconditioner \
--sampling_stride_x 1    \
--sampling_stride_y 1    \
--sampling_stride_z 16   \
--dt_0D             1e-4 \
--dt_multidomain    1e-4 \
--dt_splitting      1e-4 \
--scenario_name="s2$symmetric" \
$symmetric 

killall -9 multidomain_shorten_with_fat; sleep 1
# 2048 ranks

fi

#done
#done
