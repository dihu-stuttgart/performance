#!/bin/bash

export EXAMPLE_DIR=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_fat_emg
export pyod=$OPENDIHU_HOME/dependencies/python/install/bin/python3

# generate fat mesh
# usage: ./create_fat_layer.py [<fibers input file> [<output file of fat tissue> [<thickness in cm> [<y_size>]]]]
#$OPENDIHU_HOME/dependencies/python/install/bin/python3 \
#   $OPENDIHU_HOME/scripts/create_fat_layer.py \
#   $OPENDIHU_HOME/examples/electrophysiology/input/left_biceps_brachii_37x37fibers.bin \
#   $OPENDIHU_HOME/examples/electrophysiology/input/left_biceps_brachii_37x37fibers_thin_fat.bin \
#   0.2 3

# generate fiber distribution
mkdir -p fiber_distribution
#$pyod $OPENDIHU_HOME/scripts/generate_fiber_distribution.py fiber_distribution/MU_fibre_distribution_37x37_20c.txt 20 3 1 37 1.1

# simulation with only the MU 1 activated
mpirun -n 27 $EXAMPLE_DIR/build_release/fibers_fat_emg \
  $EXAMPLE_DIR/settings_fibers_fat_emg.py 20mus_activate_one_mu.py 1 \
  --fiber_distribution_file=fiber_distribution/MU_fibre_distribution_37x37_20c.txt

# simulation with only the MU 20 activated
mpirun -n 27 $EXAMPLE_DIR/build_release/fibers_fat_emg \
  $EXAMPLE_DIR/settings_fibers_fat_emg.py 20mus_activate_one_mu.py 20 \
  --fiber_distribution_file=fiber_distribution/MU_fibre_distribution_37x37_20c.txt
