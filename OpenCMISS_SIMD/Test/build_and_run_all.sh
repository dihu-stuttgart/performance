cd ../OpenCMISS-version
build_complex.sh && build_complex2.sh
cd -
cd ../Version-1
build_complex.sh && build_complex2.sh
cd -
cd ../Version-3
build_complex.sh && build_complex2.sh
cd -
cd ../Version-4
build_complex.sh && build_complex2.sh
cd -
run_all.sh && run_all2.sh
# uns T1 (vectorized), T0 (non-vectorized), both as Euler and Heun. Very expensive.