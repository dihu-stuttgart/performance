#!/bin/bash

export EXAMPLE_DIR=$OPENDIHU_HOME/examples/electrophysiology/fibers/fibers_emg
export pyod=$OPENDIHU_HOME/dependencies/python/install/bin/python3

# generate fiber distribution files
mkdir -p fiber_distribution

#for partitioning in \
#"[2,2,1,7]" \
#"[3,3,2,13]" \
#"[4,4,4,25]" \
#"[6,6,4,37]" \
#"[7,8,8,67]" \
#"[12,12,8,109]" \
#"[15,15,16,187]" \
#"[22,22,16,277]" \

for partitioning in \
"[29,29,32,523]"; do

  # filename of fiber distribution file 
  export nfibers=`python3 -c "print($partitioning[3])"`
  export filename=MU_fibre_distribution_${nfibers}x${nfibers}_100mus.txt

  echo "*=*=====================*=*"
  echo $pyod $OPENDIHU_HOME/scripts/generate_fiber_distribution.py fiber_distribution/$filename 100 3 1 $nfibers 1.02
  time $pyod $OPENDIHU_HOME/scripts/generate_fiber_distribution.py fiber_distribution/$filename 100 3 1 $nfibers 1.02
done

