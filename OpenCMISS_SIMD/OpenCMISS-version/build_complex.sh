echo 'Building "V1Test.exe"...'
echo 'rhs:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c memory.c RHS_routine.c
echo ''
echo 'vectorized numerics:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c numerics.c
echo ''
echo 'integration_loops:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c integration_loops.c
echo ''
echo 'main:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c main.c
echo ''
echo 'link all:'
gcc memory.o RHS_routine.o numerics.o integration_loops.o main.o -o V1Test.exe -lm 
echo 'Build done.'
echo ''
echo 'Building "V0Test.exe"...'
echo 'non-vectorized numerics:'
gcc -O3 -fno-tree-vectorize -fopt-info-vec -lm -Wall -c numerics.c
echo ''
echo 'link all:'
gcc memory.o RHS_routine.o numerics.o integration_loops.o main.o -o V0Test.exe -lm
echo 'Build done.'
