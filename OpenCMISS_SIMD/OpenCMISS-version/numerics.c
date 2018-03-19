// #include "numerics.h" // no internal linking
#include <time.h> // to use time handle and clock() function
#include <stdlib.h>  // sonst Fehler: "error: dereferencing pointer to incomplete type ‘struct timeval’ \n   if (x->tv_usec < y->tv_usec) {"
#include "memory.h"
#include "RHS_routine.h"
 
 int forwardEuler(double timeSpan, int Ksteps, double* states, double* rates, double* OUTfromRHS, double* INtoRHS, int NumberOfStates, clock_t * restrict handle_array, double * restrict portions_array, int* max_kB_ptr){
   double dt_0D;
   int k;
   int ii;  
   int actualUsedRAM;
   
   if (Ksteps == 0){
     dt_0D = timeSpan /5;
   }
   else{
     dt_0D = timeSpan / Ksteps;
   }
   handle_array[0]=clock();
   for(k=1; k<=Ksteps; k++){
     OC_CellML_RHS_routine(states, rates, OUTfromRHS, INtoRHS, handle_array, portions_array,max_kB_ptr);
     handle_array[1]=clock();
#pragma GCC ivdep   
     for(ii=0; ii<NumberOfStates; ii++){
       states[ii] = states[ii] + dt_0D * rates[ii];
     }
     states[28]=0.0; //not necessary
     handle_array[2]=clock();
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
   }
   handle_array[1]=clock();
   // to compute rates again for output at t=dt_1D
   OC_CellML_RHS_routine(states, rates, OUTfromRHS, INtoRHS, handle_array, portions_array,max_kB_ptr);
   handle_array[2]=clock();
   // time to integrate
   portions_array[0] += ((double) (handle_array[1]-handle_array[0])) / CLOCKS_PER_SEC;
   // time to evaluate L_hs
   portions_array[1] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
  
   actualUsedRAM=getValue();
   if(actualUsedRAM > *max_kB_ptr){*max_kB_ptr = actualUsedRAM;}
   
   handle_array[7] = clock();// time to get value (memory consumption)
   portions_array[7] += ((double) (handle_array[7] - handle_array[2])) / CLOCKS_PER_SEC;
   
   return 0;
 }
 int improvedEuler(double timeSpan, int Ksteps, double* states, double* rates, double* OUTfromRHS, double* INtoRHS, int NumberOfStates, clock_t * restrict handle_array, double * restrict portions_array, int* max_kB_ptr){
   // tell integrator function that rhs-function exists:
   //int OC_CellML_RHS_routine();
   double dt_0D;
   double *statesCopy/*[NumberOfStates]*/, *rates2/*[NumberOfStates]*/;//, rates_shifted_old[NumberOfStates];//, rates_alt[NumberOfStates];
   
   handle_array[0] = clock();
   
   statesCopy =  malloc(sizeof(double)*NumberOfStates);
   rates2 =  malloc(sizeof(double)*NumberOfStates);
   
   handle_array[1] = clock(); // time for malloc
   portions_array[5] += ((double) (handle_array[1]-handle_array[0])) / CLOCKS_PER_SEC;
   
   int k;
   int state;
   int actualUsedRAM;
   
   if (Ksteps == 0){
     dt_0D = timeSpan /5;
   }
   else{
     dt_0D = timeSpan / Ksteps;
   }
   
   handle_array[0]=clock();
   for(k=1; k<=Ksteps; k++){
     handle_array[1]=clock();
// #pragma GCC ivdep // not vectorized      
     for (state=0;state<NumberOfStates;state++){
       statesCopy[state]=states[state];
     }
     handle_array[2]=clock(); // time to copy
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
     
     OC_CellML_RHS_routine(states, rates, OUTfromRHS, INtoRHS, handle_array, portions_array,max_kB_ptr);
     
     handle_array[1]=clock();
#pragma GCC ivdep
     for(state=0; state<NumberOfStates; state++){
       states[state] = states[state] + dt_0D * rates[state];
     }
     handle_array[2]=clock(); // time to evolve states
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
     
     OC_CellML_RHS_routine(states, rates2, OUTfromRHS, INtoRHS, handle_array, portions_array,max_kB_ptr); // same I_stim and l_s
     
     handle_array[1]=clock();
#pragma GCC ivdep
     for(state=0; state<NumberOfStates; state++){
       states[state] = statesCopy[state] + dt_0D * (rates[state]+rates2[state])/2.0;
     }
     states[28]=0.0; //not necessary
     handle_array[2]=clock(); // time to evolve states
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
   }
   handle_array[1]=clock();
   // to compute rates again for output at t=dt_1D
   OC_CellML_RHS_routine(states, rates, OUTfromRHS, INtoRHS, handle_array, portions_array,max_kB_ptr);
   handle_array[2]=clock();
   // time to integrate
   portions_array[0] += ((double) (handle_array[1]-handle_array[0])) / CLOCKS_PER_SEC;
   // time to evaluate L_hs
   portions_array[1] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
   
   actualUsedRAM=getValue();
   if(actualUsedRAM > *max_kB_ptr){*max_kB_ptr=actualUsedRAM;}
   
   handle_array[7] = clock();// time to get value (memory consumption)
   portions_array[7] += ((double) (handle_array[7] - handle_array[2])) / CLOCKS_PER_SEC;
   
   return 0;
 }
 
 int initVectorsShorten(double* state, double* parameters, double* rate, int N){
  int cell,state_idx;
  for(cell=1;cell<=N;cell++){
  state[(cell-1)*57+0]=-79.974; // -82.265452 in Shorten et al.
  state[(cell-1)*57+1]=-80.2;
  state[(cell-1)*57+2]=5.9;
  state[(cell-1)*57+3]=150.9;
  state[(cell-1)*57+4]=5.9;
  state[(cell-1)*57+5]=12.7;
  state[(cell-1)*57+6]=133.0;
  state[(cell-1)*57+7]=133.0;
  state[(cell-1)*57+8]=0.009466;
  state[(cell-1)*57+9]=0.9952;
  state[(cell-1)*57+10]=0.0358;
  state[(cell-1)*57+11]=0.4981;
  state[(cell-1)*57+12]=0.581;
  state[(cell-1)*57+13]=0.009466;
  state[(cell-1)*57+14]=0.9952;
  state[(cell-1)*57+15]=0.0358;
  state[(cell-1)*57+16]=0.4981;
  state[(cell-1)*57+17]=0.581;
  state[(cell-1)*57+18]=0.0; //O_0
  state[(cell-1)*57+19]=0.0;
  state[(cell-1)*57+20]=0.0;
  state[(cell-1)*57+21]=0.0;
  state[(cell-1)*57+22]=0.0; //O_4
  state[(cell-1)*57+23]=1.0;
  state[(cell-1)*57+24]=0.0;
  state[(cell-1)*57+25]=0.0;
  state[(cell-1)*57+26]=0.0;
  state[(cell-1)*57+27]=0.0;
  state[(cell-1)*57+28]=0.0; // dummy assignment
  state[(cell-1)*57+29]=0.1;
  state[(cell-1)*57+30]=1500.0;
  state[(cell-1)*57+31]=0.1;
  state[(cell-1)*57+32]=1500.0;
  state[(cell-1)*57+33]=25;
  state[(cell-1)*57+34]=615;
  state[(cell-1)*57+35]=615;
  state[(cell-1)*57+36]=811;
  state[(cell-1)*57+37]=811;
  state[(cell-1)*57+38]=16900.0;
  state[(cell-1)*57+39]=16900.0;
  state[(cell-1)*57+40]=0.4;
  state[(cell-1)*57+41]=0.4;
  state[(cell-1)*57+42]=7200.0;
  state[(cell-1)*57+43]=7200.0;
  state[(cell-1)*57+44]=799.6;
  state[(cell-1)*57+45]=799.6;
  state[(cell-1)*57+46]=1000.0;
  state[(cell-1)*57+47]=1000.0;
  state[(cell-1)*57+48]=3.0;
  state[(cell-1)*57+49]=0.8;
  state[(cell-1)*57+50]=1.2;
  state[(cell-1)*57+51]=3.0;
  state[(cell-1)*57+52]=0.3;
  state[(cell-1)*57+53]=0.23;
  state[(cell-1)*57+54]=0.23;
  state[(cell-1)*57+55]=0.23;
  state[(cell-1)*57+56]=0.23;
  
  parameters[(cell-1)*2]=1200.0;
  parameters[(cell-1)*2+1]=1.0;
  
  for(state_idx=0;state_idx<=56;state_idx++){rate[(cell-1)*57+state_idx]=0;}
  }
  
  return 0;
 }

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}