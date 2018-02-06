echo 'Building "V1Test2.exe"...'
echo 'rhs:'
gcc -O2 -mavx -fopt-info-vec -lm -Wall -c RHS_routine.c
echo ''
echo 'vectorized numerics:'
gcc -O2 -mavx -fopt-info-vec -lm -Wall -c numerics.c
echo ''
echo 'integration_loops:'
gcc -O1 -mavx -fopt-info-vec -lm -Wall -c integration_loops.c
echo ''
echo 'main:'
gcc -O1 -mavx -fopt-info-vec -lm -Wall -c main.c
echo ''
echo 'link all:'
gcc -lm RHS_routine.o numerics.o integration_loops.o main.o -o V1Test2.exe
echo 'Build done.'
echo ''
echo 'Building "V0Test2.exe"...'
echo 'non-vectorized numerics:'
gcc -O2 -fno-tree-vectorize -fopt-info-vec -lm -Wall -c numerics.c
echo ''
echo 'link all:'
gcc -lm RHS_routine.o numerics.o integration_loops.o main.o -o V0Test2.exe
echo 'Build done.'