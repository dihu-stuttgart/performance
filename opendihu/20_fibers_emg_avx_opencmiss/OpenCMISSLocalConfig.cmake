###############################
# OpenCMISS local configuration
###############################
#
# This file can be used to change the build parameters and component settings and
# is created for each choice of toolchain and MPI.
#
# For a complete description of all options, refer to
# 
# http://opencmiss.org/documentation/cmake/docs/config
# 
# or the <manage>/Config/OpenCMISSDefaultConfig.cmake script.
#
# The exemplatory values used in this file are initialized to already 
# be the opposite of the default values, if applicable.

######################
# SDK INSTALLATIONS
######################
#set(OPENCMISS_SDK_INSTALL_DIR ~/software/opencmiss/install)
#set(OPENCMISS_SDK_INSTALL_DIR_FORCE ~/software/opencmiss/install/x86_64_linux/gnu-4.8.4/openmpi_release/static/release)

##################
# GENERAL SETTINGS
##################

#set(OC_CREATE_LOGS NO)
#set(OC_CONFIG_LOG_TO_SCREEN YES)
#set(OPENCMISS_INSTALL_ROOT "/data/scratch/maierbn/opencmiss/install")
#set(BUILD_PRECISION sdcz)
#set(INT_TYPE int64)
#set(BUILD_TESTS OFF)
#set(PARALLEL_BUILDS OFF)
#set(BLA_VENDOR Intel10_64lp)
#set(DISABLE_GIT YES)
#set(OC_USE_ARCHITECTURE_PATH NO)
#set(OC_PYTHON_BINDINGS_USE_VIRTUALENV YES)

###############
# BUILD CONTROL
###############
#set(BUILD_SHARED_LIBS YES)
#set(CMAKE_BUILD_TYPE DEBUG)
#set(MPI_BUILD_TYPE DEBUG)
#set(OC_WARN_ALL NO)
#set(OC_CHECK_ALL NO)
#set(OC_MULTITHREADING ON)

#########################
# COMPONENT CONFIGURATION
########################
#set(IRON_SHARED NO)
#set(ZINC_SHARED NO)
#set(OC_DEPENDENCIES_ONLY YES)
#set(OC_COMPONENTS_SYSTEM NONE)
#set(OC_BUILD_ZINC_TESTS YES)
#set(OC_SYSTEM_BLAS OFF)
set(OC_SYSTEM_BZIP2 ON)
set(OC_SYSTEM_CELLML ON)
set(OC_SYSTEM_CLANG ON)
set(OC_SYSTEM_CSIM ON)
#set(OC_SYSTEM_FIELDML-API ON)
#set(OC_SYSTEM_FREETYPE OFF)
set(OC_SYSTEM_FTGL ON)
set(OC_SYSTEM_GDCM-ABI ON)
set(OC_SYSTEM_GLEW ON)
set(OC_SYSTEM_GTEST ON)
set(OC_SYSTEM_HDF5 ON)
set(OC_SYSTEM_HYPRE ON)
set(OC_SYSTEM_IMAGEMAGICK ON)
set(OC_SYSTEM_IRON ON)
set(OC_SYSTEM_ITK ON)
#set(OC_SYSTEM_JPEG OFF)
#set(OC_SYSTEM_LAPACK OFF)
set(OC_SYSTEM_LIBCELLML ON)
#set(OC_SYSTEM_LIBXML2 OFF)
set(OC_SYSTEM_LLVM ON)
set(OC_SYSTEM_MUMPS ON)
set(OC_SYSTEM_NETGEN ON)
set(OC_SYSTEM_OPTPP ON)
set(OC_SYSTEM_PARMETIS ON)
set(OC_SYSTEM_PASTIX ON)
set(OC_SYSTEM_PETSC ON)
set(OC_SYSTEM_PLAPACK ON)
set(OC_SYSTEM_PNG ON)
set(OC_SYSTEM_PTSCOTCH ON)
set(OC_SYSTEM_SCALAPACK ON)
set(OC_SYSTEM_SCOTCH ON)
set(OC_SYSTEM_SLEPC ON)
set(OC_SYSTEM_SOWING ON)
set(OC_SYSTEM_SUITESPARSE ON)
set(OC_SYSTEM_SUNDIALS ON)
set(OC_SYSTEM_SUPERLU ON)
set(OC_SYSTEM_SUPERLU_DIST ON)
set(OC_SYSTEM_SZIP ON)
set(OC_SYSTEM_TIFF ON)
set(OC_SYSTEM_ZINC ON)
set(OC_SYSTEM_ZLIB ON)


set(OC_USE_BLAS OFF)
set(OC_USE_BZIP2 OFF)
#set(OC_USE_CELLML OFF)
#set(OC_USE_CLANG ON)
#set(OC_USE_CSIM ON)
set(OC_USE_FREETYPE OFF)
set(OC_USE_FTGL OFF)
set(OC_USE_GDCM-ABI OFF)
set(OC_USE_GLEW OFF)
set(OC_USE_GTEST OFF)
set(OC_USE_HDF5 OFF)
#set(OC_USE_HYPRE OFF)
set(OC_USE_IMAGEMAGICK OFF)
#set(OC_USE_IRON OFF)
set(OC_USE_ITK OFF)
set(OC_USE_JPEG OFF)
set(OC_USE_LAPACK OFF)
#set(OC_USE_LIBCELLML OFF)
#set(OC_USE_LLVM ON)
#set(OC_USE_MUMPS OFF)
set(OC_USE_NETGEN OFF)
set(OC_USE_OPTPP OFF)
#set(OC_USE_PARMETIS OFF)
#set(OC_USE_PASTIX OFF)
#set(OC_USE_PETSC OFF)
set(OC_USE_PLAPACK OFF)
set(OC_USE_PNG OFF)
#set(OC_USE_PTSCOTCH OFF)
#set(OC_USE_SCALAPACK OFF)
#set(OC_USE_SCOTCH ON)
set(OC_USE_SLEPC OFF)
#set(OC_USE_SOWING OFF)
#set(OC_USE_SUITESPARSE OFF)
#set(OC_USE_SUNDIALS OFF)
#set(OC_USE_SUPERLU OFF)
#set(OC_USE_SUPERLU_DIST OFF)
set(OC_USE_SZIP OFF)
set(OC_USE_TIFF OFF)
set(OC_USE_ZINC OFF)
set(OC_USE_ZLIB OFF)


#######################
# COMPONENT INTERACTION
#######################
#set(CELLML_USE_CSIM YES)

#set(MUMPS_WITH_SCOTCH YES)
#set(MUMPS_WITH_PTSCOTCH NO)
#set(MUMPS_WITH_METIS YES)
#set(MUMPS_WITH_PARMETIS NO)

#set(SUNDIALS_WITH_LAPACK NO)

#set(SCOTCH_USE_THREADS NO)
#set(SCOTCH_WITH_ZLIB NO)
#set(SCOTCH_WITH_BZIP2 NO)

#set(SUPERLU_DIST_WITH_PARMETIS NO)

#set(PASTIX_USE_THREADS NO)
#set(PASTIX_USE_METIS NO)
#set(PASTIX_USE_PTSCOTCH NO)

#set(HDF5_WITH_MPI YES)
#set(HDF5_WITH_SZIP NO)
#set(HDF5_WITH_ZLIB NO)

#set(FIELDML-API_WITH_HDF5 NO)
#set(FIELDML-API_WITH_JAVA_BINDINGS NO)
#set(FIELDML-API_WITH_FORTRAN_BINDINGS NO)

#set(IRON_WITH_CELLML NO)
#set(IRON_WITH_FIELDML NO)
#set(IRON_WITH_HYPRE NO)
#set(IRON_WITH_SUNDIALS NO)
#set(IRON_WITH_MUMPS NO)
#set(IRON_WITH_SCALAPACK NO)
#set(IRON_WITH_PETSC NO)
#set(IRON_WITH_C_BINDINGS NO)
set(IRON_WITH_Python_BINDINGS NO)

#set(ZINC_WITH_Python_BINDINGS NO)

#set(LIBXML2_WITH_ZLIB NO)