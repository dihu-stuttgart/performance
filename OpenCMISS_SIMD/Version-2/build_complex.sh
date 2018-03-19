echo 'Building "V1Test.exe"...'
echo 'vectorized rhs:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c RHS_routine.c
echo ''
echo 'vectorized numerics:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c numerics.c
echo ''
echo 'main:'
gcc -O3 -mavx -fopt-info-vec -lm -Wall -c main.c
echo ''
echo 'link all:'
gcc -lm RHS_routine.o numerics.o main.o -o V1Test.exe
echo 'Build done.'
echo ''
echo 'Building "V0Test.exe"...'
echo 'non-vectorized rhs:'
gcc -O3 -fno-tree-vectorize -lm -Wall -c RHS_routine.c
echo ''
echo 'non-vectorized numerics:'
gcc -O3 -fno-tree-vectorize -lm -Wall -c numerics.c
echo ''
echo 'link all:'
gcc -lm RHS_routine.o numerics.o main.o -o V0Test.exe
echo 'Build done.'