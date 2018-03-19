echo "This is build_and_run_all_small.sh from directory:"
pwd
echo "--------------------------------------------------"
cd ../OpenCMISS-version
echo "changed directory to:"
pwd
build_complex.sh
# && build_complex2.sh
cd -
cd ../Version-1
echo "changed directory to:"
pwd
build_complex.sh
# && build_complex2.sh
#cd -
#cd ../Version-3
#echo "changed directory to:"
#pwd
#build_complex.sh
# && build_complex2.sh
cd -
cd ../Version-4
echo "changed directory to:"
pwd
build_complex.sh
# && build_complex2.sh
cd -
run_all_small.sh && run_all2_small.sh
# uns T1 (vectorized), T0 (non-vectorized), both as Euler and Heun. Very expensive.
boil_data.sh
vis.sh
cp_draw_rename.sh
