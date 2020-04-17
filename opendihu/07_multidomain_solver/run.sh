example_dir=$OPENDIHU_HOME/examples/electrophysiology/multidomain_with_fat

killall -9 multidomain_with_fat

for preconditioner in boomeramg euclid bjacobi pilut none; do
#for preconditioner in boomeramg; do
for symmetric in " " "--use_symmetric_preconditioner_matrix"; do

# 2 MUs
mpirun -n 12 \
$example_dir/build_release/multidomain_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 2 1 6 \
--multidomain_preconditioner_type $preconditioner \
$symmetric

killall -9 multidomain_with_fat; sleep 1

# 6 MUs
mpirun -n 36 \
$example_dir/build_release/multidomain_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 4 1 9 \
--multidomain_preconditioner_type $preconditioner \
$symmetric
  
killall -9 multidomain_with_fat; sleep 1

# 10 MUs
mpirun -n 60 \
$example_dir/build_release/multidomain_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 6 1 10 \
--multidomain_preconditioner_type $preconditioner \
$symmetric

killall -9 multidomain_with_fat; sleep 1

# 12 MUs
mpirun -n 72 \
$example_dir/build_release/multidomain_with_fat \
$example_dir/settings_multidomain_with_fat.py solver_study.py \
--n_subdomains 6 1 12 \
--multidomain_preconditioner_type $preconditioner \
$symmetric

killall -9 multidomain_with_fat; sleep 1

done
done

