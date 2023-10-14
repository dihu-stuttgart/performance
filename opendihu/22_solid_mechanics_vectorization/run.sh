#!/bin/bash

# model: transisotropic hyperelasticity with mooney rivlin

dir=$(pwd)

example_dir=$OPENDIHU_HOME/examples/solid_mechanics/mooney_rivlin_transiso/
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input

# run examples
# weak scaling with approximately 8 elements per process
for n_elements in \
  "[2,1,4,1]" \
  "[2,2,4,2]" \
  "[2,2,6,3]" \
  "[2,2,8,4]" \
  "[2,3,8,6]" \
  "[3,4,8,12]" \
  "[4,4,8,16]" \
  "[3,4,16,24]" \
  "[2,2,72,36]" \
  "[2,2,108,54]" \
  "[1,3,192,72]" \
  "[4,4,48,96]" \
  "[4,4,64,128]" \
  "[2,4,144,144]" \
  "[2,4,192,192]" \
  "[2,4,256,256]";
do

  # extract numbers of elements
  export nx=`python -c "print($n_elements[0])"`
  export ny=`python -c "print($n_elements[1])"`
  export nz=`python -c "print($n_elements[2])"`
  export nranks=`python -c "print($n_elements[3])"`
  export oversubscribe=`python -c "print('--oversubscribe' if (int)($n_elements[3]) > 128 else '')"` 

  # run example with analytic jacobian, not vectorized
  mpirun $oversubscribe -n $nranks $example_dir/build_release/3d_hyperelasticity \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz \
    --use_analytic_jacobian=True --use_numeric_jacobian=False --scenario_name="analytic_jacobian" --file_output=false --njacobi=2
  
  # run example with numeric jacobian
  mpirun $oversubscribe -n $nranks $example_dir/build_release/3d_hyperelasticity \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz \
    --use_analytic_jacobian=False --use_numeric_jacobian=True --scenario_name="numeric_jacobian" --file_output=false --njacobi=2
    

done
