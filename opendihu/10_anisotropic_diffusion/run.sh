# to be run in build_release directory
#

example_dir=$OPENDIHU_HOME/examples/diffusion/anisotropic_diffusion
example_binary=anisotropic_diffusion3d
scenario_name=study_dt_dx

current_dir=$(pwd)

# compile example
cd $example_dir
scons
cd $current_dir

# compute reference solution
cd $current_dir/$scenario_name
pwd

dt=1e-3
dx=1e-1
$example_dir/build_release/${example_binary} settings.py $scenario_name ${dt} ${dx}

# copy reference solution
cd out
cp $(ls -t out_diffusion3d*.py | head -1) ../reference_solution.py
return

for dt in 4e-2 2e-2 1e-2; do
for dx in 3.2 1.6 8e-1 4e-1 2e-1 1e-1 5e-2; do

cd $current_dir/$scenario_name

echo "Scenario $scenario_name, dt: $dt, dx: $dx"
rm out/*

# parameters: [<scenario_name> [<dt> [<dx>]]]
$example_dir/build_release/${example_binary} settings.py $scenario_name ${dt} ${dx}

cd out
python3 ../../evaluate.py $scenario_name ${dt} ${dx}

done
done
