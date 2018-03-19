 int forwardEuler(double timeSpan, int Ksteps, double* states, double* rates, double* OUTfromRHS, double* INtoRHS, int NumberOfCells, clock_t * restrict handle_array, double * restrict portions_array, int* max_kB_ptr);
 
 int improvedEuler(double timeSpan, int Ksteps, double* states, double* rates, double* OUTfromRHS, double* INtoRHS, int NumberOfCells, clock_t * restrict handle_array, double * restrict portions_array, int* max_kB_ptr);
 
 int initVectorsShorten(double* state, double* parameters, double* rate, int N);

 int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y);