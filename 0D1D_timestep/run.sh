i=0
last_n=-1
while [ $i -lt 33 ]; do
  n=$(python -c "import numpy as np; print int(np.sqrt(2)**($i))")
  if [ "$last_n" -ne "$n" ]; then
    echo $n
    ./run_for_single_1D.py ${n} & 
  fi
  last_n=$n
  let i+=1
done
