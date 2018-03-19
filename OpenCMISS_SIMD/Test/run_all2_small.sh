echo "Removing old .dat2-files in directory:" 
pwd
rm -f *.dat2
echo ""
echo "Starting measurements for test 2: runtime(NumberOfCells): loop vectorization on/off"
for N in {1,2,4,6,8}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..99}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..99}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {10..90..10}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..79}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..79}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {100..900..100}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..59}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..59}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..59}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..59}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..59}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..59}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {1000..9000..1000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..39}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..39}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..39}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..39}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..39}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..39}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {10000..90000..10000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..19}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..19}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {100000..900000..100000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..9}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..9}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..9}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..9}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..9}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..9}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {1000000..3000000..1000000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  for Messungsgenauigkeit in {0..1}
  do
    nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..1}
  do
    nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..1}
  do
    #nohup ../Version-3/V1Test.exe 2 1 $N >> V-3_V1.dat2 2>/dev/null
    #nohup ../Version-3/V0Test.exe 2 1 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..1}
  do
    nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..1}
  do
    nohup ../OpenCMISS-version/V1Test.exe 2 1 $N >> OCV_V1.dat2 2>/dev/null
  done
  for Messungsgenauigkeit in {0..1}
  do
    nohup ../OpenCMISS-version/V0Test.exe 2 1 $N >> OCV_V0.dat2 2>/dev/null
  done
done
for N in {4000000..6000000..1000000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
  nohup ../Version-1/V1Test.exe 2 1 $N >> V-1_V1.dat2 2>/dev/null
  nohup ../Version-1/V0Test.exe 2 1 $N >> V-1_V0.dat2 2>/dev/null
  nohup ../Version-4/V1Test.exe 2 1 $N >> V-4_V1.dat2 2>/dev/null
  nohup ../Version-4/V0Test.exe 2 1 $N >> V-4_V0.dat2 2>/dev/null
done
wait
echo "Done."
echo "Substitute all '0's by '1e-06'."
sed -i 's/etup 0 /etup 1e-06 /g' V-1_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-1_V1.dat2
#sed -i 's/etup 0 /etup 1e-06 /g' V-3_V0.dat2
#sed -i 's/etup 0 /etup 1e-06 /g' V-3_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-4_V0.dat2
sed -i 's/etup 0 /etup 1e-06 /g' V-4_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' OCV_V1.dat2
sed -i 's/etup 0 /etup 1e-06 /g' OCV_V0.dat2
# also in state evolution
sed -i 's/lution: 0 /lution: 2e-06 /g' V-1_V0.dat2
sed -i 's/lution: 0 /lution: 2e-06 /g' V-1_V1.dat2
#sed -i 's/lution: 0 /lution: 2e-06 /g' V-3_V0.dat2
#sed -i 's/lution: 0 /lution: 2e-06 /g' V-3_V1.dat2
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
