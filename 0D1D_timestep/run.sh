
for n in 1 2 3 4 6 8 12 16 24 32 48 64 96 128 192 256 384 512 1024 2048 4096 8192 16384 32768 65536; do
  ./run_for_single_1D.py ${n} & 
done
