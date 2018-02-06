echo "This is build_and_run_all_small.sh from directory:"
pwd
echo "--------------------------------------------------"
cd ../OpenCMISS-version
echo "changed directory to:"
pwd
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-1
echo "changed directory to:"
pwd
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-3
echo "changed directory to:"
pwd
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-4
echo "changed directory to:"
pwd
build_complex.sh
#&& build_complex2.sh
cd -
run_test1.sh && run_test2.sh
