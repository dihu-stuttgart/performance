#!/bin/bash 
# weak scaling
date
module add shared openmpi

echo "OPENCMISS_REL_DIR=$OPENCMISS_REL_DIR, OPENCMISS_INPUT_DIR=$OPENCMISS_INPUT_DIR"

. ~/.bashrc

# Pause, when the time is between 7h and 21h
function check_exit()
{
   return # check disabled!
   while true; do
      HOUR=$(date +%H)
      echo "Current time: $(date)"

      if [ $HOUR -ge 7 ] && [ $HOUR -le 20 ] ; then    # wait if 7 <= hour <= 20
         echo "Don't run program because it is between 7 and 20."
         sleep 1h
      else
         echo "OK"
         break
      fi
   done
}

echo "weak scaling, Test GMRES vs. CG+ILU"

# 1 2 1 = GMRES, no precond.
# 1 3 6 = CG, ILU

while true; do
  check_exit
#  mpiexec -n 1 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 8 1 1 1     1 2 1
  #mpiexec -n 1 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 8 1 1 1     1 3 6  OutputTimeStepStride=100
  check_exit
#  mpiexec -n 2 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 8 2 1 1     1 2 1
  mpiexec -n 2 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 8 2 1 1     1 3 6 OutputTimeStepStride=100
  exit
  check_exit
#  mpiexec -n 4 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 16 2 1 1    1 2 1
  mpiexec -n 4 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 3 16 2 1 1    1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 8 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 2 1 1    1 2 1
  mpiexec -n 8 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 2 1 1    1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 12 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 3 1 1   1 2 1
  mpiexec -n 12 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 3 1 1   1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 16 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 4 1 1   1 2 1
  mpiexec -n 16 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 16 4 1 1   1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 24 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 24 4 1 1   1 2 1
  mpiexec -n 24 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 24 4 1 1   1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 32 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 32 4 1 1   1 2 1
  mpiexec -n 32 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 6 32 4 1 1   1 3 6 OutputTimeStepStride=100
  check_exit
#  mpiexec -n 64 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 12 32 4 1 1  1 2 1
  mpiexec -n 64 $OPENCMISS_REL_DIR/cuboid $OPENCMISS_INPUT_DIR 12 32 4 1 1  1 3 6 OutputTimeStepStride=100
  check_exit
done
