cp -f OCV_V0.dat1 Grafiken_all_Tests/Data/OCV_V0.dat1
cp -f OCV_V0.dat2 Grafiken_all_Tests/Data/OCV_V0.dat2 
cp -f OCV_V1.dat1 Grafiken_all_Tests/Data/OCV_V1.dat1
cp -f OCV_V1.dat2 Grafiken_all_Tests/Data/OCV_V1.dat2
cp -f V-1_V0.dat1 Grafiken_all_Tests/Data/V-1_V0.dat1
cp -f V-1_V0.dat2 Grafiken_all_Tests/Data/V-1_V0.dat2
cp -f V-1_V1.dat1 Grafiken_all_Tests/Data/V-1_V1.dat1
cp -f V-1_V1.dat2 Grafiken_all_Tests/Data/V-1_V1.dat2
cp -f V-4_V0.dat1 Grafiken_all_Tests/Data/V-4_V0.dat1
cp -f V-4_V0.dat2 Grafiken_all_Tests/Data/V-4_V0.dat2
cp -f V-4_V1.dat1 Grafiken_all_Tests/Data/V-4_V1.dat1
cp -f V-4_V1.dat2 Grafiken_all_Tests/Data/V-4_V1.dat2

cp -f OCV_V1.dat1 Grafiken_Test_T1_Only/Data/OCV_V1.dat1
cp -f OCV_V1.dat2 Grafiken_Test_T1_Only/Data/OCV_V1.dat2
cp -f V-1_V1.dat1 Grafiken_Test_T1_Only/Data/V-1_V1.dat1
cp -f V-1_V1.dat2 Grafiken_Test_T1_Only/Data/V-1_V1.dat2
cp -f V-4_V1.dat1 Grafiken_Test_T1_Only/Data/V-4_V1.dat1
cp -f V-4_V1.dat2 Grafiken_Test_T1_Only/Data/V-4_V1.dat2

cd Grafiken_Test_T1_Only
vis.sh
echo "renaming into [12]_X_<meaning>.eps"
mv -f Result_Test1_1.eps 1_1_TimeSpentInKernels_T1.eps
mv -f Result_Test1_2.eps 1_2_RuntimePercentageOfKernels_T1.eps
mv -f Result_Test1_3.eps 1_3_RuntimePerCell_T1.eps 
mv -f Result_Test1_3b.eps 1_3b_TimePerCell_T1.eps 
mv -f Result_Test1_4.eps 1_4_PerformanceDecoded_T1.eps
mv -f Result_Test1_5.eps 1_5_MemoryConsumption_Euler_T1.eps
mv -f Result_Test2_1.eps 2_1_TimeSpentInKernels_T1.eps
mv -f Result_Test2_2.eps 2_2_RuntimePercentageOfKernels_T1.eps
mv -f Result_Test2_3.eps 2_3_RuntimePerCell_T1.eps
mv -f Result_Test2_3b.eps 2_3b_TimePerCell_T1.eps
mv -f Result_Test2_4.eps 2_4_PerformanceDecoded_T1.eps
mv -f Result_Test2_5.eps 2_5_MemoryConsumption_Heun_T1.eps
mv -f Result_Test12_5.eps 12_5_MemoryConsumption_all_T1.eps
cd -
cd Grafiken_all_Tests
vis.sh
echo "renaming into [12]_X_<meaning>.eps"
mv -f Result_Test1_1.eps 1_1_TimeSpentInKernels.eps
mv -f Result_Test1_2.eps 1_2_RuntimePercentageOfKernels.eps
mv -f Result_Test1_3.eps 1_3_RuntimePerCell.eps 
mv -f Result_Test1_3b.eps 1_3b_TimePerCell.eps 
mv -f Result_Test1_4.eps 1_4_PerformanceDecoded.eps
mv -f Result_Test1_5.eps 1_5_MemoryConsumption_Euler.eps
mv -f Result_Test2_1.eps 2_1_TimeSpentInKernels.eps
mv -f Result_Test2_2.eps 2_2_RuntimePercentageOfKernels.eps
mv -f Result_Test2_3.eps 2_3_RuntimePerCell.eps
mv -f Result_Test2_3b.eps 2_3b_TimePerCell.eps
mv -f Result_Test2_4.eps 2_4_PerformanceDecoded.eps
mv -f Result_Test2_5.eps 2_5_MemoryConsumption_Heun.eps
mv -f Result_Test12_5.eps 12_5_MemoryConsumption_all.eps
cd -