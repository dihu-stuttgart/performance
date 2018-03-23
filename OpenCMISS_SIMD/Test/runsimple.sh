#for N in {10000..20000..500}
#do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
#echo $N
#    nohup ../Version-1/V1Test.exe 5 0 $N >> V-1.tdat1 2>/dev/null
#    nohup ../Version-1/V1Test.exe 5 0 $N >> V-1.tdat1 2>/dev/null
#    nohup ../Version-3/V1Test.exe 5 1 $N >> V-3.tdat2 2>/dev/null
#    nohup ../Version-3/V1Test.exe 5 1 $N >> V-3.tdat2 2>/dev/null
#
#done
for N in {2550000..3000000..50000}
do  # nohup -> unterdrückt output bis alle fertig sind (zwischendrin mal in /dev/null)
echo $N
    nohup ../OpenCMISS-version/V1Test.exe 5 0 $N >> OCV.tdat1 2>/dev/null
   # nohup ../OpenCMISS-version/V1Test.exe 5 1 $N >> OCV.tdat2 2>/dev/null
done