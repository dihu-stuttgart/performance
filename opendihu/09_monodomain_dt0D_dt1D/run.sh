# to be run in build_release directory
#

# hodgkin_huxley
example_dir=$OPENDIHU_HOME/examples/electrophysiology/monodomain/hodgkin_huxley
example_binary=hodgkin_huxley_strang
scenario_name=hodgkin_huxley

# hodgkin_huxley-razumova
#example_dir=$OPENDIHU_HOME/examples/electrophysiology/monodomain/hodgkin_huxley-razumova
#example_binary=monodomain
#scenario_name=hodgkin_huxley-razumova

# hodgkin-huxley_shorten_ocallaghan_davidson_soboleva_2007
#example_dir=$OPENDIHU_HOME/examples/electrophysiology/monodomain/hodgkin-huxley_shorten_ocallaghan_davidson_soboleva_2007
#example_binary=monodomain
#scenario_name=hodgkin-huxley_shorten_ocallaghan_davidson_soboleva_2007

# new_slow_TK_2014_12_08
#example_dir=$OPENDIHU_HOME/examples/electrophysiology/monodomain/new_slow_TK_2014_12_08
#example_binary=shorten_implicit
#scenario_name=new_slow_TK_2014_12_08

# shorten_ocallaghan_davidson_soboleva_2007
#example_dir=$OPENDIHU_HOME/examples/electrophysiology/monodomain/shorten_ocallaghan_davidson_soboleva_2007
#example_binary=shorten_implicit
#scenario_name=shorten_ocallaghan_davidson_soboleva_2007

current_dir=$(pwd)

# compile example
cd $example_dir
scons
cd $current_dir

# compute reference solution
cd $current_dir/$scenario_name
dt_0D=1e-6
dt_1D=1e-6
$example_dir/build_release/${example_binary} settings_${scenario_name}.py $scenario_name ${dt_0D} ${dt_1D}

# copy reference solution
cd out
cp $(ls -t cellml*.py | head -1) ../reference_solution.py

for dt_0D in 1e-1 5.62341325190349e-2 3.162277660168379e-2 1e-2 5.62341325190349e-3 3.162277660168379e-3 1e-3 5.62341325190349e-4 3.162277660168379e-4 1e-4 5.6234132519e-5 3.1622776601e-5 1.77827941003892e-5 1e-5 5.62341325190349e-6 3.162277660168379e-6 1.778279410e-6 1e-6 5.62341325190349e-7 3.162277660168379e-7 1.778279410e-7 1e-7; do
for dt_1D in 1e-1 5.62341325190349e-2 3.162277660168379e-2 1e-2 5.62341325190349e-3 3.162277660168379e-3 1e-3 5.62341325190349e-4 3.162277660168379e-4 1e-4 5.6234132519e-5 3.1622776601e-5 1.77827941003892e-5 1e-5 5.62341325190349e-6 3.162277660168379e-6 1.778279410e-6 1e-6 5.62341325190349e-7 3.162277660168379e-7 1.778279410e-7 1e-7; do

cd $current_dir/$scenario_name

echo "Scenario $scenario_name, dt_0D: $dt_0D, dt_1D: $dt_1D"

# hodgkin huxley model
# parameters: [<scenario_name> [<dt_0D> [<dt_1D>]]]
$example_dir/build_release/${example_binary} settings_${scenario_name}.py $scenario_name ${dt_0D} ${dt_1D}

cd out
python3 ../../evaluate.py $scenario_name ${dt_0D} ${dt_1D}

done
done
