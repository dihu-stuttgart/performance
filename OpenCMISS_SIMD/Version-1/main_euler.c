#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "numerics.h"
//printf("text and %f oder %d \n",<double>,<int>);
/*
 * https://stackoverflow.com/questions/29292818/how-to-vectorize-my-loop-with-g
 * https://stackoverflow.com/questions/2005473/rules-for-using-the-restrict-keyword-in-c
 * http://hpac.rwth-aachen.de/teaching/sem-accg-16/slides/08.Schmitz-GGC_Autovec.pdf
 * file:///home/kraemer/Downloads/Compiler_Optimization_and_Vectorization.pdf
 * */

// at office, tried to compile with:
// gcc -lm -O2 -march=native -ftree-vectorize -msse2 -fopt-info-vec-all (--std=c99, bei gcc version 4.9) -Wall -o default.exe RHS_routine.h RHS_routine.c numerics.h numerics.c main.c
// at home
// 
// for test.c: gcc -O2 -ftree-vectorize -msse2 -fopt-info-vec-all test.c
//
 int main(int argc,char **argv)
{  
   //char str[80];
   //strcpy(str, argv[0]);
   int NumberOfCells=2000;
   if(argc==2){  NumberOfCells = atoi(argv[1]);}
   int Nstates = 57;
   //##for OpenCMISS Algorithm#########################################################################   
   double intermediate[NumberOfCells];
   double state[NumberOfCells*57], rate[NumberOfCells*57];
   double parameters[NumberOfCells*2];
   /*double* intmd_ptr=intermediate;
   double* state_ptr=state;
   double* prmtr_ptr=parameters;
   double* rate_ptr=rate;*/
   //int* ptr=NULL;
   //##################################################################################################
   //##for AVX/SSE Algorithm###########################################################################
   double state0[NumberOfCells], state1[NumberOfCells], state2[NumberOfCells], state3[NumberOfCells], state4[NumberOfCells], state5[NumberOfCells], state6[NumberOfCells], state7[NumberOfCells], state8[NumberOfCells], state9[NumberOfCells], state10[NumberOfCells],state11[NumberOfCells],state12[NumberOfCells],state13[NumberOfCells],state14[NumberOfCells],state15[NumberOfCells],state16[NumberOfCells],state17[NumberOfCells],state18[NumberOfCells],state19[NumberOfCells],
          state20[NumberOfCells],state21[NumberOfCells],state22[NumberOfCells],state23[NumberOfCells],state24[NumberOfCells],state25[NumberOfCells],state26[NumberOfCells],state27[NumberOfCells],state28[NumberOfCells],state29[NumberOfCells],state30[NumberOfCells],state31[NumberOfCells],state32[NumberOfCells],state33[NumberOfCells],state34[NumberOfCells],state35[NumberOfCells],state36[NumberOfCells],state37[NumberOfCells],state38[NumberOfCells],state39[NumberOfCells],
          state40[NumberOfCells],state41[NumberOfCells],state42[NumberOfCells],state43[NumberOfCells],state44[NumberOfCells],state45[NumberOfCells],state46[NumberOfCells],state47[NumberOfCells],state48[NumberOfCells],state49[NumberOfCells],state50[NumberOfCells],state51[NumberOfCells],state52[NumberOfCells],state53[NumberOfCells],state54[NumberOfCells],state55[NumberOfCells],state56[NumberOfCells];            // 56 + one extra fake state
   double rate0[NumberOfCells], rate1[NumberOfCells], rate2[NumberOfCells], rate3[NumberOfCells], rate4[NumberOfCells], rate5[NumberOfCells], rate6[NumberOfCells], rate7[NumberOfCells], rate8[NumberOfCells], rate9[NumberOfCells], rate10[NumberOfCells],rate11[NumberOfCells],rate12[NumberOfCells],rate13[NumberOfCells],rate14[NumberOfCells],rate15[NumberOfCells],rate16[NumberOfCells],rate17[NumberOfCells],rate18[NumberOfCells],rate19[NumberOfCells],
          rate20[NumberOfCells],rate21[NumberOfCells],rate22[NumberOfCells],rate23[NumberOfCells],rate24[NumberOfCells],rate25[NumberOfCells],rate26[NumberOfCells],rate27[NumberOfCells],rate28[NumberOfCells],rate29[NumberOfCells],rate30[NumberOfCells],rate31[NumberOfCells],rate32[NumberOfCells],rate33[NumberOfCells],rate34[NumberOfCells],rate35[NumberOfCells],rate36[NumberOfCells],rate37[NumberOfCells],rate38[NumberOfCells],rate39[NumberOfCells],
          rate40[NumberOfCells],rate41[NumberOfCells],rate42[NumberOfCells],rate43[NumberOfCells],rate44[NumberOfCells],rate45[NumberOfCells],rate46[NumberOfCells],rate47[NumberOfCells],rate48[NumberOfCells],rate49[NumberOfCells],rate50[NumberOfCells],rate51[NumberOfCells],rate52[NumberOfCells],rate53[NumberOfCells],rate54[NumberOfCells],rate55[NumberOfCells],rate56[NumberOfCells];            // 56 + one extra fake rate
   double parameter0[NumberOfCells],parameter1[NumberOfCells];        // (I_{stim},l_s) \in R^2_+
   double intermediate0[NumberOfCells];
   //##################################################################################################
   //for measure of time for simulation------------
   clock_t start, end;
   double cpu_time_used_AVX,cpu_time_used;
   //---------------------------------------
   double dt_1D=1.0;
   int K=100;
   int ii;

   //Err = setintptr(ptr);
   //###OpenCMISS Algorithm########################################################################
   initVectorsShorten(state,parameters,rate,NumberOfCells);//+(ii-1)*Nstates,parameters+(ii-1)*2);
   //##AVX/SSE Algorithm###########################################################################
   initVectorsForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9,
                      state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                      state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,
                      state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                      state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,
                      state50,state51,state52,state53,state54,state55,state56,
                      parameter0, parameter1, NumberOfCells);
   
   //##AVX/SSE Algorithm#########################################################################
   //timeing
   start = clock();
   forwardEulerForAVX(dt_1D,K,
                      state0, state1, state2, state3, state4, state5, state6, state7, state8, state9,
                      state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                      state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,
                      state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                      state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,
                      state50,state51,state52,state53,state54,state55,state56,
                      rate0, rate1, rate2, rate3, rate4, rate5, rate6, rate7, rate8, rate9,
                      rate10,rate11,rate12,rate13,rate14,rate15,rate16,rate17,rate18,rate19,
                      rate20,rate21,rate22,rate23,rate24,rate25,rate26,rate27,rate28,rate29,
                      rate30,rate31,rate32,rate33,rate34,rate35,rate36,rate37,rate38,rate39,
                      rate40,rate41,rate42,rate43,rate44,rate45,rate46,rate47,rate48,rate49,
                      rate50,rate51,rate52,rate53,rate54,rate55,rate56,
                      intermediate0, parameter0,  parameter1, NumberOfCells);
   //timeing
   end = clock();
   cpu_time_used_AVX = ((double) (end - start)) / CLOCKS_PER_SEC;
   //printf("CPU time [s] using SSE/AVX routines: %f \n",cpu_time_used);
   //##################################################################################################
   //##OpenCMISS Algorithm###########################################################################   
   //timeing
   start = clock();
   for(ii=1;ii<=NumberOfCells;ii++){
      forwardEuler(dt_1D, K, state+(ii-1)*Nstates, rate+(ii-1)*Nstates, intermediate+(ii-1), parameters+(ii-1)*2, Nstates);
   }
   //timeing
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   //printf("CPU time[s] with OpenCMISS routines: %f \n",cpu_time_used);
   //################################################################################################## 
   printf("%s %d %f %f \n",argv[0],NumberOfCells,cpu_time_used_AVX,cpu_time_used);
   //test_restrict(state0,state1,state2,NumberOfCells*Nstates);
   return 0;
 }
 


  
