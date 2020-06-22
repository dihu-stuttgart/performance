example_dir=$OPENDIHU_HOME/examples/electrophysiology/multidomain_with_fat

# run on neon

killall -9 multidomain_shorten_with_fat

for preconditioner in boomeramg euclid bjacobi sor pilut none; do
#for preconditioner in boomeramg; do
#for preconditioner in bjacobi sor; do
#for preconditioner in bjacobi; do
for symmetric in " " "--use_symmetric_preconditioner_matrix"; do
#for symmetric in " -sub_ksp_type preonly -sub_pc_type ilu"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type gamg"; do
#for symmetric in " -sub_ksp_type cg -sub_pc_type hypre -sub_pc_hypre_type euclid"; do

killall -9 multidomain_shorten_with_fat; sleep 1

# 4 MUs
mpirun -n 24 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 4 1 6 \
--multidomain_preconditioner_type $preconditioner \
$symmetric -ksp_view -sub_pc_hypre_boomeramg_strong_threshold 0.7

killall -9 multidomain_shorten_with_fat; sleep 1

# 8 MUs
mpirun -n 48 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 6 1 8 \
--multidomain_preconditioner_type $preconditioner \
$symmetric -ksp_view

killall -9 multidomain_shorten_with_fat; sleep 1

# 6 MUs
mpirun -n 36 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 4 1 9 \
--multidomain_preconditioner_type $preconditioner \
$symmetric -ksp_view
  
killall -9 multidomain_shorten_with_fat; sleep 1

# 10 MUs
mpirun -n 60 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 6 1 10 \
--multidomain_preconditioner_type $preconditioner \
$symmetric -ksp_view

killall -9 multidomain_shorten_with_fat; sleep 1

# 12 MUs
mpirun -n 72 \
$example_dir/build_release/multidomain_shorten_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 6 1 12 \
--multidomain_preconditioner_type $preconditioner \
$symmetric -ksp_view

killall -9 multidomain_shorten_with_fat; sleep 1

done
done
