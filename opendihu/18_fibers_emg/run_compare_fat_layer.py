#!/bin/bash

export EXAMPLE_DIR=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_emg
export EXAMPLE_FAT_DIR=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_fat_emg
export pyod=$OPENDIHU_HOME/dependencies/python/install/bin/python3

# generate fat mesh
# usage: ./create_fat_layer.py [<fibers input file> [<output file of fat tissue> [<thickness in cm> [<y_size>]]]]
#$OPENDIHU_HOME/dependencies/python/install/bin/python3 \
#   $OPENDIHU_HOME/scripts/create_fat_layer.py \
#   $OPENDIHU_HOME/examples/electrophysiology/input/left_biceps_brachii_37x37fibers.bin \
#   $OPENDIHU_HOME/examples/electrophysiology/input/left_biceps_brachii_37x37fibers_thin_fat.bin \
#   0.2 3

# generate fiber distribution  -> already created by run_single_MUs.py
#mkdir -p fiber_distribution
#$pyod $OPENDIHU_HOME/scripts/generate_fiber_distribution.py fiber_distribution/MU_fibre_distribution_37x37_20c.txt 20 3 1 37 1.1

# simulation without fat layer
mpirun -n 27 $EXAMPLE_DIR/build_release/fast_fibers_emg \
  $EXAMPLE_DIR/settings_fibers_emg.py $EXAMPLE_FAT_DIR/variables/20mus_fat_comparison.py \
  --fiber_distribution_file=fiber_distribution/MU_fibre_distribution_37x37_20c.txt \
  --scenario_name="no_fat"

# simulation with thick fat layer
#mpirun -n 27 $EXAMPLE_FAT_DIR/build_release/fibers_fat_emg \
#  $EXAMPLE_FAT_DIR/settings_fibers_fat_emg.py $EXAMPLE_FAT_DIR/variables/20mus_fat_comparison.py \
#  --fiber_distribution_file=fiber_distribution/MU_fibre_distribution_37x37_20c.txt \
#  --scenario_name="thick_fat"

# simulation with thin fat layer
#mpirun -n 27 $EXAMPLE_FAT_DIR/build_release/fibers_fat_emg \
#  $EXAMPLE_FAT_DIR/settings_fibers_fat_emg.py $EXAMPLE_FAT_DIR/variables/20mus_fat_comparison.py \
#  --fiber_distribution_file=fiber_distribution/MU_fibre_distribution_37x37_20c.txt \
#  --fat_mesh_file=$OPENDIHU_HOME/examples/electrophysiology/input/left_biceps_brachii_37x37fibers_thin_fat.bin \
#  --scenario_name="thin_fat"
