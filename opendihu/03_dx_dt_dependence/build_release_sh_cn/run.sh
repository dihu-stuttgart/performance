#!/bin/bash
# to be run in build_release directory
#
# execute 

#  <n_processes_per_fiber> <n_fibers> <n_nodes_per_fiber_per_cm> <dt_1D> <scenario_name>

cwd=$(pwd)

#for n_nodes in $(seq 20 20 600); do
for n_nodes in $(seq 20 20 240); do

rm -f last_velocity
#for dt in 1e-3 5.62341325190349e-4 3.162277660168379e-4 1e-4 5.6234132519e-5 3.1622776601e-5 1.77827941003892e-5 1e-5 5.62341325190349e-6 3.162277660168379e-6 1.778279410e-6 1e-6 5.62341325190349e-7 3.162277660168379e-7 1.778279410e-7 1e-7; do
for dt in 1e-4 6.812920690579613e-5 4.641588833612778e-5 3.1622776601683795e-5 2.154434690031884e-5 1.4677992676220695e-5 1e-5 6.812920690579613e-6 4.641588833612778e-6 3.162277660168379884e-5 1.4677992676220695e-5 1e-5 6.812920690579613e-6 4.641588833612778e-6 3.1622776601683795e-6 2.154434690031884e-6 1.4677992676220695e-6 1e-6; do

cd $cwd

# hodgkin huxley model
rm -rf out
./cuboid_shorten_cn ../settings_cuboid.py 1 1 $n_nodes $dt shorten_crank_nicolson | tee -a out.txt
cd out
python3 ../../evaluate.py shorten_crank_nicolson && break # break if evaluate is 1

done
done
#n_nodes=100
#./cuboid_shorten ../settings_cuboid.py 1 1 $n_nodes nodes_$n_nodes shorten
#./cuboid_shorten ../settings_cuboid.py 1 1 $n_nodes nodes_$n_nodes shorten

