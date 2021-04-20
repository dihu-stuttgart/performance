#!/bin/bash

#partitioning  2* 2* 1=    4    7^2=    49 fibers, fibers/rank: 12.250000, need    1 nodes
#partitioning  3* 3* 2=   18   13^2=   169 fibers, fibers/rank: 9.388889, need    1 nodes
#partitioning  4* 4* 4=   64   25^2=   625 fibers, fibers/rank: 9.765625, need    1 nodes
#partitioning  6* 6* 4=  144   37^2=  1369 fibers, fibers/rank: 9.506944, need    3 nodes
#partitioning  7* 8* 8=  448   67^2=  4489 fibers, fibers/rank: 10.020089, need    7 nodes
#partitioning 12*12* 8= 1152  109^2= 11881 fibers, fibers/rank: 10.313368, need   18 nodes
#partitioning 15*15*16= 3600  187^2= 34969 fibers, fibers/rank: 9.713611, need   57 nodes
#partitioning 22*22*16= 7744  277^2= 76729 fibers, fibers/rank: 9.908187, need  121 nodes
#partitioning 24*24*32=18432  427^2=182329 fibers, fibers/rank: 9.891981, need  288 nodes
#partitioning 29*29*32=26912  523^2=273529 fibers, fibers/rank: 10.163830, need  421 nodes
#partitioning 40*40*32=51200  523^2=273529 fibers, fibers/rank: 5.342363, need  800 nodes

echo only listing:
for partitioning in \
"[2,2,1,7,40]" \
"[3,3,2,13,22]" \
"[4,4,4,25,11]" \
"[6,6,4,37,8]" \
"[7,8,8,67,4]" \
"[12,12,8,109,3]" \
"[15,15,16,187,2]" \
"[22,22,16,277,1]" \
"[24,24,32,427,1]" \
"[29,29,32,523,1]" \
"[40,40,32,523,1]"; do
  export n_nodes=`python3 - << EOF
import numpy as np
n = (int)(np.ceil(($partitioning[0] * $partitioning[1] * $partitioning[2])/64.))
if n > 128:
  n = 2**(np.ceil(np.log(n)/np.log(2)))
print((int)(n))
EOF
`
echo $partitioning n_nodes: $n_nodes
done

echo now submitting

for partitioning in \
"[24,24,32,427,1]" \
"[29,29,32,523,1]"; do

 stride=1  # a stride of 2 is given in the jobscript by mpiprocs=64

  # compute number of compute nodes
  export n_nodes=`python3 - << EOF
import numpy as np
n = (int)(np.ceil(($partitioning[0] * $partitioning[1] * $partitioning[2])/64.))
if n > 128:
  n = 2**(np.ceil(np.log(n)/np.log(2)))
print((int)(n))
EOF
`
  # determine n_processes and name of job
  export n_processes=`python3 -c "print($partitioning[0] * $partitioning[1] * $partitioning[2])"`
  export name=`python3 -c "print(\"{}x{}x{}\".format($partitioning[0],$partitioning[1],$partitioning[2]))"`
  export filename="jobscripts/jobscript_${partitioning}_${n_nodes}_nodes.pbs"
  echo "${name}, [${partitioning}] n_nodes=[${n_nodes}], file ${filename}"
  mkdir -p jobscripts

  # replace numbers in template jobscript.pbs file
  sed "s/-N name/-N $name/; s/select=1/select=${n_nodes}/; s/<ncpus>/${n_processes}/; s/\[x,x,x,x\]/${partitioning}/; s/stride=x/stride=${stride}/ " jobscript.pbs > ${filename}

  # submit job to queue
  
  echo qsub ${arg} ${filename}
  j=`qsub ${arg} ${filename}`
  last_job_id=`echo $j | awk 'match($0,/[0-9]+/){print substr($0, RSTART, RLENGTH)}'`

  arg="-W depend=afterany:${last_job_id}"
done

