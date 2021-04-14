#!/bin/bash

# model: transisotropic hyperelasticity with mooney rivlin
# As a prerequisite, compile the program under $example_dir two times with USE_VECTORIZED_FE_MATRIX_ASSEMBLY set to False and True
# Save the programs as 3d_hyperelasticity_normal and 3d_hyperelasticity_vc.

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

  # run example with analytic jacobian, not vectorized
  mpirun -n $nranks $example_dir/build_release/3d_hyperelasticity_normal \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz --scenario_name="${nx}_${ny}_${nz}_not_vectorized"
  
  # run example with analytic jacobian
  echo mpirun -n $nranks $example_dir/build_release/3d_hyperelasticity_vc \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz --scenario_name="${nx}_${ny}_${nz}_vectorized"
    
  break

done
