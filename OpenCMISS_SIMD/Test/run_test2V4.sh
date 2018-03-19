echo "Removing old V-4_V*.dat2-files" 
rm -f V-4_V1.dat2 V-4_V0.dat2

echo "Starting measurements for test 2: runtime(NumberOfCells): loop vectorization on/off"
for N in {2..8..2}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
done
for N in {10..90..10}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
done
for N in {100..900..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..49}
  do
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
done
for N in {1000..9000..1000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
done
for N in {10000..90000..20000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
done
for N in {100000..900000..400000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
done
for N in {1000000..9000000..1000000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
done
wait
echo "Done."
echo "Substitute all '0's by '1e-06'."
sed -i 's/etup 0 /etup 1e-06 /g' V-1_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-1_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-2_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-2_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-3_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-3_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-4_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-4_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' OCV_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' OCV_V0.dat2
# also in state evolution
sed -i 's/lution: 0 /lution: 2e-06 /g' V-1_V0.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-1_V1.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-2_V0.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-2_V1.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-3_V0.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-3_V1.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-4_V0.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-4_V1.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' OCV_V1.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' OCV_V0.dat2
echo "Visualizing measurements:"
gnuplot vis2_1.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis2_2.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis2_3.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis2_3b.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis2_4.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis2_5.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
gnuplot vis12_5.g  &> mumpitz && cat mumpitz | grep -v "0.dat"
rm -rf mumpitz
echo "Saved graphs as 'Result_Test2_X.eps'."