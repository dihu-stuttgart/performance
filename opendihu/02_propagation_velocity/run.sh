# to be run in build_release directory
#
# execute:
#   cd build_release
#   . ../run.sh
#   cd ..
#   ./plot_propagation_velocity.py

# arguments of the simulation programs:
# <n_processes_per_fiber> <n_fibers> <n_nodes_per_fiber> <scenario_name>

workdir=$(pwd)

for n_nodes in $(seq 20 20 600); do
#for n_nodes in $(seq 280 40 1000); do

# shorten model
rm -rf out
mpirun -n 8 ./cuboid_shorten ../settings_cuboid.py 1 1 $n_nodes shorten
cd out
python3 ../../evaluate.py shorten
cd $workdir

# hodgkin huxley model
rm -rf out
mpirun -n 8 ./cuboid_hodgkin_huxley ../settings_cuboid.py 1 1 $n_nodes hodgkin_huxley
cd out
python3 ../../evaluate.py hodgkin_huxley
cd $workdir

done
#n_nodes=100
#./cuboid_shorten ../settings_cuboid.py 1 1 $n_nodes nodes_$n_nodes shorten
#./cuboid_hodgkin_huxley ../settings_cuboid.py 1 1 $n_nodes nodes_$n_nodes hodgkin_huxley

