example_dir=$OPENDIHU_HOME/examples/electrophysiology/multidomain/multidomain_with_fat

killall -9 multidomain_shorten_with_fat

for preconditioner in euclid bjacobi sor pilut none; do
#for preconditioner in boomeramg; do
#for preconditioner in bjacobi sor; do
#for preconditioner in bjacobi; do
for symmetric in " " "--use_symmetric_preconditioner_matrix"; do
#for symmetric in " -sub_ksp_type preonly -sub_pc_type ilu"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type gamg"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type hypre -sub_pc_hypre_type euclid"; do

killall -9 multidomain_shorten_with_fat; sleep 1

# ------------
# experiment 1
# 12 ranks
mpirun -n 12 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study_resolution.py \
--n_subdomains 2 1 3 \
--multidomain_preconditioner_type $preconditioner \
--sampling_stride_x 1      \
--sampling_stride_y 1      \
--sampling_stride_z 32     \
--dt_0D             5e-4   \
--dt_multidomain    5e-4   \
--dt_splitting      5e-4   \
--scenario_name="s1$symmetric"   \
$symmetric 

killall -9 multidomain_shorten_with_fat; sleep 1

# 24 ranks
mpirun -n 24 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study_resolution.py \
--n_subdomains 4 1 6 \
--multidomain_preconditioner_type $preconditioner \
--sampling_stride_x 1       \
--sampling_stride_y 1       \
--sampling_stride_z 16      \
--dt_0D             5e-4    \
--dt_multidomain    5e-4    \
--dt_splitting      5e-4    \
--scenario_name="s1$symmetric"    \
$symmetric 

killall -9 multidomain_shorten_with_fat; sleep 1

# 48 ranks
mpirun -n 48 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study_resolution.py \
--n_subdomains 6 1 8 \
--multidomain_preconditioner_type $preconditioner \
--sampling_stride_x 1      \
--sampling_stride_y 1      \
--sampling_stride_z 8      \
--dt_0D             5e-4   \
--dt_multidomain    5e-4   \
--dt_splitting      5e-4   \
--scenario_name="s1$symmetric"   \
$symmetric 

killall -9 multidomain_shorten_with_fat; sleep 1
done
done
