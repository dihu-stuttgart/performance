gcc -O3 -msse2 -lm RHS_routine.c numerics.c main.c -o sse2_on_main.exe &&
gcc -O3 -msse3 -lm RHS_routine.c numerics.c main.c -o sse3_on_main.exe &&
gcc -O3 -mavx -lm RHS_routine.c numerics.c main.c -o avx_on_main.exe &&
gcc -O3 -mavx2 -lm RHS_routine.c numerics.c main.c -o avx2_on_main.exe 