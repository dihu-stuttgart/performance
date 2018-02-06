 # compilieren, dass auf neuestem Stand
echo "Removing old .dat-files" 
rm -f *.dat 
#make -j 4
echo "Starting measurement: runtime(NumberOfCells): loop vectorization on/off" 
for N in {100..2500..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
  for Messungsgenauigkeit in {0..10}
  do
    nohup sse2_off_main.exe 5 0 $N >> sse2_off.dat 2>/dev/null
    nohup sse2_on_main.exe 5 0 $N >> sse2_on.dat 2>/dev/null
  done
done
wait
echo "25%" 
for N in {100..2500..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
  for Messungsgenauigkeit in {0..10}
  do
    nohup sse3_off_main.exe 5 0 $N >> sse3_off.dat 2>/dev/null
    nohup sse3_on_main.exe 5 0 $N >> sse3_on.dat 2>/dev/null
  done
done
wait
echo "50%" 
for N in {100..2500..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
  for Messungsgenauigkeit in {0..10}
  do
    nohup avx_off_main.exe 5 0 $N >> avx_off.dat 2>/dev/null
    nohup avx_on_main.exe 5 0 $N >> avx_on.dat 2>/dev/null
  done
done
wait
echo "75%" 
for N in {100..2500..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
  for Messungsgenauigkeit in {0..10}
  do
    nohup avx2_off_main.exe 5 0 $N >> avx2_off.dat 2>/dev/null
    nohup avx2_on_main.exe 5 0 $N >> avx2_on.dat 2>/dev/null
  done
done
wait
echo "100%. Done."
echo "Visualizing measurements:"
gnuplot visualize_on-off.g
echo "Saved graph as 'Results_on-off.png'."