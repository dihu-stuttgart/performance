for N in {10000..90000..10000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
    nohup ../Version-1/V1Test.exe 5 0 $N >> V-1_V1.dat2 2>/dev/null
    nohup ../Version-1/V0Test.exe 5 0 $N >> V-1_V0.dat2 2>/dev/null
    nohup ../Version-2/V1Test.exe 5 0 $N >> V-2_V1.dat2 2>/dev/null
    nohup ../Version-2/V0Test.exe 5 0 $N >> V-2_V0.dat2 2>/dev/null
    nohup ../Version-3/V1Test.exe 5 0 $N >> V-3_V1.dat2 2>/dev/null
    nohup ../Version-3/V0Test.exe 5 0 $N >> V-3_V0.dat2 2>/dev/null
    nohup ../OpenCMISS-version/V1Test.exe 5 0 $N >> OCV_V1.dat2 2>/dev/null
    nohup ../OpenCMISS-version/V0Test.exe 5 0 $N >> OCV_V0.dat2 2>/dev/null
done
wait
echo "Done."
echo "Substitute all '0's by '1e-06'."
sed -i 's/ 0 / 1e-06 /g' V-1_V0.dat2
sed -i 's/ 0 / 1e-06 /g' V-1_V1.dat2
sed -i 's/ 0 / 1e-06 /g' V-2_V0.dat2
sed -i 's/ 0 / 1e-06 /g' V-2_V1.dat2
sed -i 's/ 0 / 1e-06 /g' V-3_V0.dat2
sed -i 's/ 0 / 1e-06 /g' V-3_V1.dat2
sed -i 's/ 0 / 1e-06 /g' OCV_V1.dat2
sed -i 's/ 0 / 1e-06 /g' OCV_V0.dat2
echo "Visualizing measurements:"
gnuplot vis2_1.g
gnuplot vis2_2.g
gnuplot vis2_3.g
echo "Saved graphs as 'Result_Test2_1.png' and 'Result_Test2_2.png'."