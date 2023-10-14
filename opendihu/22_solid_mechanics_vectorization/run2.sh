#!/bin/bash

# model: transisotropic hyperelasticity with mooney rivlin
# As a prerequisite, compile the program under $example_dir two times with USE_VECTORIZED_FE_MATRIX_ASSEMBLY set to False and True
# Save the programs as 3d_hyperelasticity_normal and 3d_hyperelasticity_vc.

dir=$(pwd)

example_dir=$OPENDIHU_HOME/examples/solid_mechanics/mooney_rivlin_transiso/
input_dir=$OPENDIHU_HOME/examples/electrophysiology/input

# run examples

for n_elements in \
  "[4,2,8,1]" \
  "[4,4,8,2]" \
  "[4,4,12,3]" \
  "[4,4,16,4]" \
  "[4,6,16,6]" \
  "[6,8,16,12]" \
  "[8,8,16,16]" \
  "[6,8,32,24]" \
  "[4,9,64,36]" \
  "[8,6,72,54]" \
  "[8,16,48,96]" \
  "[8,16,64,128]" \
  "[8,16,72,144]" \
  "[8,16,96,192]" \
  "[8,16,128,256]"
do
  # extract numbers of elements
  export nx=`python -c "print($n_elements[0])"`
  export ny=`python -c "print($n_elements[1])"`
  export nz=`python -c "print($n_elements[2])"`
  export nranks=`python -c "print($n_elements[3])"`
  export oversubscribe=`python -c "print('--oversubscribe' if (int)($n_elements[3]) > 128 else '')"`

  # run example with analytic jacobian, not vectorized
  mpirun $oversubscribe -n $nranks $example_dir/build_release/3d_hyperelasticity_normal \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz --scenario_name="not_vectorized" --file_output=False --njacobi=1
  
  # run example with analytic jacobian, vectorized
  mpirun $oversubscribe -n $nranks $example_dir/build_release/3d_hyperelasticity_vc \
    $example_dir/settings_3d_box.py --nx $nx --ny $ny --nz $nz --scenario_name="vectorized" --file_output=False --njacobi=1
    

done
