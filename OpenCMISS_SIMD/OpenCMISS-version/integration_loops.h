int expEuler_all(double dt_1D, int K, int NumberOfCells, int Nstates,
                 double * restrict state, double * restrict rate, double * restrict intermediate, double * restrict parameters,
                 clock_t * restrict handle_ptr, double * restrict portion_ptr, int* max_kB_ptr);

int Heun_all(double dt_1D, int K, int NumberOfCells, int Nstates,
             double * restrict state, double * restrict rate, double * restrict intermediate, double * restrict parameters,
             clock_t * restrict handle_ptr, double * restrict portion_ptr, int* max_kB_ptr);