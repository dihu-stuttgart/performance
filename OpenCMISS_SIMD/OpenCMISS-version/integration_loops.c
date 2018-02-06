#include <time.h>   // clock(), clock_t
#include "integration_loops.h"
#include "numerics.h"

int expEuler_all(double dt_1D, int K, int NumberOfCells, int Nstates,
                 double * restrict state, double * restrict rate, double * restrict intermediate, double * restrict parameters,
                 clock_t * restrict handle_ptr, double * restrict portion_ptr, int* max_kB_ptr)
{
   int cell_idx;
#pragma GCC ivdep
   for(cell_idx = 1; cell_idx <= NumberOfCells; cell_idx++){
      forwardEuler(dt_1D, K, state + (cell_idx - 1) * Nstates, rate + (cell_idx - 1) * Nstates,
                               intermediate + (cell_idx - 1), parameters + (cell_idx - 1) * 2, Nstates,
                                                                     handle_ptr, portion_ptr, max_kB_ptr);
      }
   return 0;
}   



int Heun_all(double dt_1D, int K, int NumberOfCells, int Nstates,
             double * restrict state, double * restrict rate, double * restrict intermediate, double * restrict parameters,
             clock_t * restrict handle_ptr, double * restrict portion_ptr, int* max_kB_ptr)
{
  int cell_idx;
#pragma GCC ivdep
  for(cell_idx = 1; cell_idx <= NumberOfCells; cell_idx++){
      improvedEuler(dt_1D, K, state + (cell_idx - 1) * Nstates, rate + (cell_idx - 1) * Nstates,
                               intermediate + (cell_idx - 1), parameters + (cell_idx - 1) * 2, Nstates,
                                                                     handle_ptr, portion_ptr, max_kB_ptr);
      }
   return 0;
}