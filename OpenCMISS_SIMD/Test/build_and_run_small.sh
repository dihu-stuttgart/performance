cd ../OpenCMISS-version
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-1
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-3
build_complex.sh
#&& build_complex2.sh
cd -
cd ../Version-4
build_complex.sh
#&& build_complex2.sh
cd -
run_test1_small.sh && run_test2_small.sh