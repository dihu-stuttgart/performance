#include <stdio.h>  // printf()
#include <string.h> // strcpy()
#include <stdlib.h> // atoi()
#include <sys/time.h> 
#include <time.h>   // clock(), clock_t
#include "numerics.h"

/* Command usage:
 * $ main.exe 5 0 1000 
 * Order important: arguments can be left away, starting from the right side. for example $ main.exe 5 but not $ main.exe 0 1000
 * 
 * Compile as:
 * $ gcc -O3 -mXXX -lm RHS_routine.c numerics.c main.c -o XXXmain.exe,
 * where XXX is the SSE/AVX version.
 * 
 * programme executing K steps (arg1) of Euler or Heun method (specified by arg2). Using a certain number of cells (arg3).
 * prints name of programme, arguments and runtime information. The runtime information is split afterwards in different parts.
 * 
 * output format
 * name K 5 0 1000 total_runtime loop1 loop2 loop3 ...
 */

 int main(int argc,char **argv)
{
   //##### Get input arguments ########################################################################
   // name of programme: 
   char *name;
   name = malloc(sizeof(char)*64);
   //char name[64];
   char dot[] = ".";
   int len;
   strcpy(name, argv[0]);
   len = (int) strcspn(name, dot); // type casting:'size_t' --> 'int'.
   // default values:
   int K = 5;                    // the number of steps for the numerical integration
   int T = 0;                    // the type of integration. 0:explicit Euler, 1:Heun (also called improved Euler)
   int NumberOfCells = 2000;     // the number of cells. proportional to effort and memory usage of programme. 
   // get command line arguments if there are some. 
   if(argc > 1){ K = atoi(argv[1]);}
   if(argc > 2){ T = atoi(argv[2]);}
   if(argc > 3){ NumberOfCells = atoi(argv[3]);}
   //##################################################################################################
   // to measure the time for the simulation. Total time, and specifivc portions of it.
   struct timeval *tv0, *tv1;
   struct timezone *tz=NULL;
   tv0 = malloc(sizeof(struct timeval));
   tv1 = malloc(sizeof(struct timeval));
   clock_t start, end;
   int NumberOfPortions = 5, idx;
   clock_t *handle;
   handle = malloc(sizeof(clock_t)*NumberOfPortions);
   //clock_t handle[NumberOfPortions]; //(Does not have to be initialized.)
   double cpu_time_used = 0, *cpu_time_portions;
   cpu_time_portions = malloc(sizeof(double)*NumberOfPortions);
   for(idx=0;idx<NumberOfPortions;idx++){cpu_time_portions[idx]=0.0;}
   /*
    *  cpu_time_used:         total runtime
    *  cpu_time_portions[0]:  time to do the whole integration    (Thus, [0] includes [2], but not [1])
    *  cpu_time_portions[1]:  time to compute L_hs after numerical integration
    *  cpu_time_portions[2]:  time to actualize states (plus COPY if T==1)            (Is part of [0].)
    *  cpu_time_portions[3]:  time to set up the constants for the RHS evaluations
    *  cpu_time_portions[4]:  time to evaluate rates       (excludes set up of constants, RHS=[3]+[4])
    */
   //##################################################################################################
   // fix parameters (no need to be examined)
   const double dt_1D = 0.1;
   //## for AVX/SSE Algorithm #########################################################################
/*   double state0[NumberOfCells], state1[NumberOfCells], state2[NumberOfCells], state3[NumberOfCells], state4[NumberOfCells], state5[NumberOfCells], state6[NumberOfCells], state7[NumberOfCells], state8[NumberOfCells], state9[NumberOfCells], state10[NumberOfCells],state11[NumberOfCells],state12[NumberOfCells],state13[NumberOfCells],state14[NumberOfCells],state15[NumberOfCells],state16[NumberOfCells],state17[NumberOfCells],state18[NumberOfCells],state19[NumberOfCells],
          state20[NumberOfCells],state21[NumberOfCells],state22[NumberOfCells],state23[NumberOfCells],state24[NumberOfCells],state25[NumberOfCells],state26[NumberOfCells],state27[NumberOfCells],state28[NumberOfCells],state29[NumberOfCells],state30[NumberOfCells],state31[NumberOfCells],state32[NumberOfCells],state33[NumberOfCells],state34[NumberOfCells],state35[NumberOfCells],state36[NumberOfCells],state37[NumberOfCells],state38[NumberOfCells],state39[NumberOfCells],
          state40[NumberOfCells],state41[NumberOfCells],state42[NumberOfCells],state43[NumberOfCells],state44[NumberOfCells],state45[NumberOfCells],state46[NumberOfCells],state47[NumberOfCells],state48[NumberOfCells],state49[NumberOfCells],state50[NumberOfCells],state51[NumberOfCells],state52[NumberOfCells],state53[NumberOfCells],state54[NumberOfCells],state55[NumberOfCells],state56[NumberOfCells];            // 56 + one extra fake state
   double rate0[NumberOfCells], rate1[NumberOfCells], rate2[NumberOfCells], rate3[NumberOfCells], rate4[NumberOfCells], rate5[NumberOfCells], rate6[NumberOfCells], rate7[NumberOfCells], rate8[NumberOfCells], rate9[NumberOfCells], rate10[NumberOfCells],rate11[NumberOfCells],rate12[NumberOfCells],rate13[NumberOfCells],rate14[NumberOfCells],rate15[NumberOfCells],rate16[NumberOfCells],rate17[NumberOfCells],rate18[NumberOfCells],rate19[NumberOfCells],
          rate20[NumberOfCells],rate21[NumberOfCells],rate22[NumberOfCells],rate23[NumberOfCells],rate24[NumberOfCells],rate25[NumberOfCells],rate26[NumberOfCells],rate27[NumberOfCells],rate28[NumberOfCells],rate29[NumberOfCells],rate30[NumberOfCells],rate31[NumberOfCells],rate32[NumberOfCells],rate33[NumberOfCells],rate34[NumberOfCells],rate35[NumberOfCells],rate36[NumberOfCells],rate37[NumberOfCells],rate38[NumberOfCells],rate39[NumberOfCells],
          rate40[NumberOfCells],rate41[NumberOfCells],rate42[NumberOfCells],rate43[NumberOfCells],rate44[NumberOfCells],rate45[NumberOfCells],rate46[NumberOfCells],rate47[NumberOfCells],rate48[NumberOfCells],rate49[NumberOfCells],rate50[NumberOfCells],rate51[NumberOfCells],rate52[NumberOfCells],rate53[NumberOfCells],rate54[NumberOfCells],rate55[NumberOfCells],rate56[NumberOfCells];            // 56 + one extra fake rate
   double parameter0[NumberOfCells],parameter1[NumberOfCells];
   double intermediate0[NumberOfCells];*/
   double *state0, *state1, *state2, *state3, *state4, *state5, *state6, *state7, *state8, *state9, *state10,*state11,*state12,*state13,*state14,*state15,*state16,*state17,*state18,*state19,
          *state20,*state21,*state22,*state23,*state24,*state25,*state26,*state27,*state28,*state29,*state30,*state31,*state32,*state33,*state34,*state35,*state36,*state37,*state38,*state39,
          *state40,*state41,*state42,*state43,*state44,*state45,*state46,*state47,*state48,*state49,*state50,*state51,*state52,*state53,*state54,*state55,*state56;            // 56 + one extra fake *state
   double *rate0, *rate1, *rate2, *rate3, *rate4, *rate5, *rate6, *rate7, *rate8, *rate9, *rate10,*rate11,*rate12,*rate13,*rate14,*rate15,*rate16,*rate17,*rate18,*rate19,
          *rate20,*rate21,*rate22,*rate23,*rate24,*rate25,*rate26,*rate27,*rate28,*rate29,*rate30,*rate31,*rate32,*rate33,*rate34,*rate35,*rate36,*rate37,*rate38,*rate39,
          *rate40,*rate41,*rate42,*rate43,*rate44,*rate45,*rate46,*rate47,*rate48,*rate49,*rate50,*rate51,*rate52,*rate53,*rate54,*rate55,*rate56;            // 56 + one extra fake *rate
   double *parameter0,*parameter1;
   double *intermediate0;
   state0 = malloc(sizeof(double)*NumberOfCells);
state1 = malloc(sizeof(double)*NumberOfCells);
state2 = malloc(sizeof(double)*NumberOfCells);
state3 = malloc(sizeof(double)*NumberOfCells);
state4 = malloc(sizeof(double)*NumberOfCells);
state5 = malloc(sizeof(double)*NumberOfCells);
state6 = malloc(sizeof(double)*NumberOfCells);
state7 = malloc(sizeof(double)*NumberOfCells);
state8 = malloc(sizeof(double)*NumberOfCells);
state9 = malloc(sizeof(double)*NumberOfCells);
state10 = malloc(sizeof(double)*NumberOfCells);
state11 = malloc(sizeof(double)*NumberOfCells);
state12 = malloc(sizeof(double)*NumberOfCells);
state13 = malloc(sizeof(double)*NumberOfCells);
state14 = malloc(sizeof(double)*NumberOfCells);
state15 = malloc(sizeof(double)*NumberOfCells);
state16 = malloc(sizeof(double)*NumberOfCells);
state17 = malloc(sizeof(double)*NumberOfCells);
state18 = malloc(sizeof(double)*NumberOfCells);
state19 = malloc(sizeof(double)*NumberOfCells);
state20 = malloc(sizeof(double)*NumberOfCells);
state21 = malloc(sizeof(double)*NumberOfCells);
state22 = malloc(sizeof(double)*NumberOfCells);
state23 = malloc(sizeof(double)*NumberOfCells);
state24 = malloc(sizeof(double)*NumberOfCells);
state25 = malloc(sizeof(double)*NumberOfCells);
state26 = malloc(sizeof(double)*NumberOfCells);
state27 = malloc(sizeof(double)*NumberOfCells);
state28 = malloc(sizeof(double)*NumberOfCells);
state29 = malloc(sizeof(double)*NumberOfCells);
state30 = malloc(sizeof(double)*NumberOfCells);
state31 = malloc(sizeof(double)*NumberOfCells);
state32 = malloc(sizeof(double)*NumberOfCells);
state33 = malloc(sizeof(double)*NumberOfCells);
state34 = malloc(sizeof(double)*NumberOfCells);
state35 = malloc(sizeof(double)*NumberOfCells);
state36 = malloc(sizeof(double)*NumberOfCells);
state37 = malloc(sizeof(double)*NumberOfCells);
state38 = malloc(sizeof(double)*NumberOfCells);
state39 = malloc(sizeof(double)*NumberOfCells);
state40 = malloc(sizeof(double)*NumberOfCells);
state41 = malloc(sizeof(double)*NumberOfCells);
state42 = malloc(sizeof(double)*NumberOfCells);
state43 = malloc(sizeof(double)*NumberOfCells);
state44 = malloc(sizeof(double)*NumberOfCells);
state45 = malloc(sizeof(double)*NumberOfCells);
state46 = malloc(sizeof(double)*NumberOfCells);
state47 = malloc(sizeof(double)*NumberOfCells);
state48 = malloc(sizeof(double)*NumberOfCells);
state49 = malloc(sizeof(double)*NumberOfCells);
state50 = malloc(sizeof(double)*NumberOfCells);
state51 = malloc(sizeof(double)*NumberOfCells);
state52 = malloc(sizeof(double)*NumberOfCells);
state53 = malloc(sizeof(double)*NumberOfCells);
state54 = malloc(sizeof(double)*NumberOfCells);
state55 = malloc(sizeof(double)*NumberOfCells);
state56 = malloc(sizeof(double)*NumberOfCells);
rate0 = malloc(sizeof(double)*NumberOfCells);
rate1 = malloc(sizeof(double)*NumberOfCells);
rate2 = malloc(sizeof(double)*NumberOfCells);
rate3 = malloc(sizeof(double)*NumberOfCells);
rate4 = malloc(sizeof(double)*NumberOfCells);
rate5 = malloc(sizeof(double)*NumberOfCells);
rate6 = malloc(sizeof(double)*NumberOfCells);
rate7 = malloc(sizeof(double)*NumberOfCells);
rate8 = malloc(sizeof(double)*NumberOfCells);
rate9 = malloc(sizeof(double)*NumberOfCells);
rate10 = malloc(sizeof(double)*NumberOfCells);
rate11 = malloc(sizeof(double)*NumberOfCells);
rate12 = malloc(sizeof(double)*NumberOfCells);
rate13 = malloc(sizeof(double)*NumberOfCells);
rate14 = malloc(sizeof(double)*NumberOfCells);
rate15 = malloc(sizeof(double)*NumberOfCells);
rate16 = malloc(sizeof(double)*NumberOfCells);
rate17 = malloc(sizeof(double)*NumberOfCells);
rate18 = malloc(sizeof(double)*NumberOfCells);
rate19 = malloc(sizeof(double)*NumberOfCells);
rate20 = malloc(sizeof(double)*NumberOfCells);
rate21 = malloc(sizeof(double)*NumberOfCells);
rate22 = malloc(sizeof(double)*NumberOfCells);
rate23 = malloc(sizeof(double)*NumberOfCells);
rate24 = malloc(sizeof(double)*NumberOfCells);
rate25 = malloc(sizeof(double)*NumberOfCells);
rate26 = malloc(sizeof(double)*NumberOfCells);
rate27 = malloc(sizeof(double)*NumberOfCells);
rate28 = malloc(sizeof(double)*NumberOfCells);
rate29 = malloc(sizeof(double)*NumberOfCells);
rate30 = malloc(sizeof(double)*NumberOfCells);
rate31 = malloc(sizeof(double)*NumberOfCells);
rate32 = malloc(sizeof(double)*NumberOfCells);
rate33 = malloc(sizeof(double)*NumberOfCells);
rate34 = malloc(sizeof(double)*NumberOfCells);
rate35 = malloc(sizeof(double)*NumberOfCells);
rate36 = malloc(sizeof(double)*NumberOfCells);
rate37 = malloc(sizeof(double)*NumberOfCells);
rate38 = malloc(sizeof(double)*NumberOfCells);
rate39 = malloc(sizeof(double)*NumberOfCells);
rate40 = malloc(sizeof(double)*NumberOfCells);
rate41 = malloc(sizeof(double)*NumberOfCells);
rate42 = malloc(sizeof(double)*NumberOfCells);
rate43 = malloc(sizeof(double)*NumberOfCells);
rate44 = malloc(sizeof(double)*NumberOfCells);
rate45 = malloc(sizeof(double)*NumberOfCells);
rate46 = malloc(sizeof(double)*NumberOfCells);
rate47 = malloc(sizeof(double)*NumberOfCells);
rate48 = malloc(sizeof(double)*NumberOfCells);
rate49 = malloc(sizeof(double)*NumberOfCells);
rate50 = malloc(sizeof(double)*NumberOfCells);
rate51 = malloc(sizeof(double)*NumberOfCells);
rate52 = malloc(sizeof(double)*NumberOfCells);
rate53 = malloc(sizeof(double)*NumberOfCells);
rate54 = malloc(sizeof(double)*NumberOfCells);
rate55 = malloc(sizeof(double)*NumberOfCells);
rate56 = malloc(sizeof(double)*NumberOfCells);
parameter0 = malloc(sizeof(double)*NumberOfCells);
parameter1 = malloc(sizeof(double)*NumberOfCells);
intermediate0 = malloc(sizeof(double)*NumberOfCells);
   //##################################################################################################
   //## AVX/SSE Algorithm #############################################################################
   //###### not part of time measurement (not important) ##############################################
   initVectorsForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9,
                      state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                      state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,
                      state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                      state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,
                      state50,state51,state52,state53,state54,state55,state56,
                      parameter0, parameter1, NumberOfCells);
   //###### measured (important) part #################################################################
   if(T == 0){
      gettimeofday(tv0,tz);
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
                      intermediate0,parameter0,parameter1,NumberOfCells,handle,cpu_time_portions);
      end = clock();
      gettimeofday(tv1,tz);
      timeval_subtract(tv0, tv1, tv0);
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      //## print output ##
      printf("%.*s %d %d %d total: %f integration: %.17g thereof_state_evolution: %.17g evaluate_L_hs %.17g RHS_setup %.17g RHS_rate_evaluation %.17g elapsed_time: %ld.%06ld \n",
              len, argv[0],
              K,
              T,
              NumberOfCells,
              cpu_time_used,
              cpu_time_portions[0],
              cpu_time_portions[2], // swapped [2] and [1], cause [2] in [0] but [1] not in [0]
              cpu_time_portions[1],
              cpu_time_portions[3],
              cpu_time_portions[4],
              tv0->tv_sec,
              tv0->tv_usec);
   }
   else if(T == 1){
      gettimeofday(tv0,tz);
      start = clock();
     improvedEulerForAVX(dt_1D,K,
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
                      intermediate0, parameter0,parameter1,NumberOfCells,handle,cpu_time_portions);
      end = clock();
      gettimeofday(tv1,tz);
      timeval_subtract(tv0, tv1, tv0);
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      //## print output ##
      printf("%.*s %d %d %d total: %f integration: %.17g thereof_state_evolution: %.17g evaluate_L_hs %.17g RHS_setup %.17g RHS_rate_evaluation %.17g elapsed_time: %ld.%06ld \n",
              len, argv[0],
              K,
              T,
              NumberOfCells,
              cpu_time_used,
              cpu_time_portions[0],
              cpu_time_portions[2], // swapped [2] and [1], cause [2] in [0] but [1] not in [0]
              cpu_time_portions[1],
              cpu_time_portions[3],
              cpu_time_portions[4],
              tv0->tv_sec,
              tv0->tv_usec);
   }
   else{ printf("Invalid argument list: arg2 interpreted as integration type. Valid: 0 or 1.\n");}
   //## OpenCMISS Algorithm (end) #####################################################################
   //##################################################################################################
   return 0;
 }