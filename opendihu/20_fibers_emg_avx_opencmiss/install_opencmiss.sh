#!/bin/bash
# This script performs all necessary steps to build and install and the cuboid example.
# Our versions of OpenCMISS iron and the iron-examples are used (stored under github.com/cbm-software).
# The difference between our version and the official version is that our version supports the strang splitting and runs in parallel whereas the official OpenCMISS only has Godunov splitting.
#
# Copy this script to an empty directory and execute it, OpenCMISS will be installed there.

dir=$(pwd)
unset OPENCMISS_SDK_DIR
unset OPENCMISS_INSTALL_DIR 

# checkout manage repo
git clone git@github.com:OpenCMISS/manage.git

# clone our iron
mkdir -p src
cd src
git clone git@github.com:cbm-software/iron.git

cd $dir/manage
git checkout v1.2

# create build directory
mkdir -p build && cd build
#rm -rf *

# add local config
cp $dir/OpenCMISSLocalConfig.cmake .
CC=gcc CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_Fortran_FLAGS=-fallow-argument-mismatch -j 4 -DCC=gcc ..

# build
make -j 

# fix error in sowing CMakeLists.txt
cd $dir/src/dependencies/sowing
sed -i.bak 's+sys/time.h time.h+"sys/time.h;time.h"+g' CMakeLists.txt
cd $dir/manage/build

# continue build
make -j

make install

# clone examples
cd $dir/src
git clone git@github.com:cbm-software/iron-examples.git
cd iron-examples
git checkout stable

# set install dir
export OPENCMISS_INSTALL_DIR=$dir/install
export OPENCMISS_SDK_DIR=$dir/install

cd $dir/src/iron-examples/cuboid/build_release 
CC=gcc CXX=g++ cmake -DCMAKE_BUILD_TYPE=RELEASE -DOpenCMISS_DIR=$dir/install -j8 ..
make

echo "OpenCMISS and the cuboid example have been built, now run it in the following directory:"
echo "cd src/iron-examples/cuboid/build_release/Fortran"

cd $dir
