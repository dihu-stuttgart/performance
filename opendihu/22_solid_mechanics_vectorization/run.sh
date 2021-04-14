#!/bin/bash

# model: transisotropic hyperelasticity with mooney rivlin

dir=$(pwd)

example_dir=$OPENDIHU_HOME/examples/solid_mechanics/mooney_rivlin_transiso/
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input

# run examples

for n_elements in \
  "[1,1,1,1]" \
  "[1,1,2,2]" \
  "[2,1,2,2]" \
  "[2,2,2,2]"
do

  # extract numbers of elements
  export nx=`python -c "print($n_elements[0])"`
  export ny=`python -c "print($n_elements[1])"`
  export nz=`python -c "print($n_elements[2])"`
  export nranks=`python -c "print($n_elements[3])"`

  # run example with analytic jacobian
  mpirun -n $nranks $example_dir/build_release/3d_hyperelasticity \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz \
    --use_analytic_jacobian=True --use_numeric_jacobian=False --scenario_name="${nx}_${ny}_${nz}_analytic"
  
  # run example with numeric jacobian
  echo mpirun -n $nranks $example_dir/build_release/3d_hyperelasticity \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz \
    --use_analytic_jacobian=False --use_numeric_jacobian=True --scenario_name="${nx}_${ny}_${nz}_numeric" -snes_compare_explicit_draw
    
  break

done
