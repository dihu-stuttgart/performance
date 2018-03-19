gcc -O3 -msse2 -lm RHS_routine.c numerics.c main.c -o sse2_off_main.exe &&
gcc -O3 -msse3 -lm RHS_routine.c numerics.c main.c -o sse3_off_main.exe &&
gcc -O3 -mavx -lm RHS_routine.c numerics.c main.c -o avx_off_main.exe &&
gcc -O3 -mavx2 -lm RHS_routine.c numerics.c main.c -o avx2_off_main.exe 