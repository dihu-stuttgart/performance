#include <stdio.h>  // printf()
#include <string.h> // strcpy()
#include <stdlib.h> // atoi()
#include <sys/time.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <time.h>   // clock(), clock_t
#include "integration_loops.h"
#include "numerics.h"

/*
 * https://stackoverflow.com/questions/29292818/how-to-vectorize-my-loop-with-g
 * https://stackoverflow.com/questions/2005473/rules-for-using-the-restrict-keyword-in-c
 * http://hpac.rwth-aachen.de/teaching/sem-accg-16/slides/08.Schmitz-GGC_Autovec.pdf
 * file:///home/kraemer/Downloads/Compiler_Optimization_and_Vectorization.pdf
 * */


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
   // fix parameters (no need to be examined)
   int Nstates = 57;
   const double dt_1D = 0.1;
   //## for OpenCMISS Algorithm #######################################################################   
   double *intermediate;//[NumberOfCells];
   double *state/*[NumberOfCells*57]*/, *rate/*[NumberOfCells*57]*/;
   double *parameters/*[NumberOfCells*2]*/;
   intermediate =  malloc(sizeof(double)*NumberOfCells);
   state =  malloc(sizeof(double)*NumberOfCells*57);
   rate =  malloc(sizeof(double)*NumberOfCells*57);
   parameters =  malloc(sizeof(double)*NumberOfCells*2);
   int cell_idx;
   //##################################################################################################
   // to measure the time for the simulation. Total time, and specifivc portions of it.
   struct timeval *tv0, *tv1;
   struct timezone *tz=NULL;
   tv0 = malloc(sizeof(struct timeval));
   tv1 = malloc(sizeof(struct timeval));
   clock_t start, end;
   int NumberOfPortions = 8;
   clock_t *handle;//[NumberOfPortions]; //(Does not have to be initialized.)
   handle = malloc(sizeof(clock_t)*(NumberOfPortions));
   double cpu_time_used = 0, *cpu_time_portions;//[NumberOfPortions];
   cpu_time_portions = malloc(sizeof(double)*NumberOfPortions);
   for(cell_idx=0;cell_idx<NumberOfPortions;cell_idx++){cpu_time_portions[cell_idx]=0.0;}
   //##################################################################################################
   /* to measure maximum of used physical memory (by this process) and
    * to get total physical memory (RAM), both in kB.
    */
   struct sysinfo memInfo;
   sysinfo (&memInfo);
   long long totalPhysMem = memInfo.totalram;
   long long freePhysMem = memInfo.freeram;
   //Multiply in next statement to avoid int overflow on right hand side...
   totalPhysMem *= memInfo.mem_unit;
   int max_kB = 0;
   //##################################################################################################
   //## OpenCMISS Algorithm ###########################################################################
   //###### not part of time measurement (not important) ##############################################
   initVectorsShorten(state,parameters,rate,NumberOfCells);
   //###### measured (important) part #################################################################
   if(T == 0){
      gettimeofday(tv0,tz);
      start = clock();
      expEuler_all(dt_1D,K,NumberOfCells,Nstates,state,rate,intermediate,parameters,handle,cpu_time_portions,&max_kB);
      /*
      for(cell_idx = 1; cell_idx <= NumberOfCells; cell_idx++){
      forwardEuler(dt_1D, K, state + (cell_idx - 1) * Nstates, rate + (cell_idx - 1) * Nstates,
                               intermediate + (cell_idx - 1), parameters + (cell_idx - 1) * 2, Nstates,
                                                                     handle, cpu_time_portions);
      }*/
      end = clock();
      gettimeofday(tv1,tz);
      timeval_subtract(tv0, tv1, tv0);
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      //## print output ##
      printf("%.*s %d T%d %d total: %f integration: %.17g thereof_state_evolution: %.17g evaluate_L_hs %.17g RHS_setup %.17g RHS_rate_evaluation %.17g elapsed_time: %ld.%06ld totalRAM_[kB]: %lld freeBeforeMALLOC_[kB]: %lld used_[kB]: %d rhs_malloc: %.17g ttrMemRhs %.17g ttrMemNum %.17g \n",
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
              tv0->tv_usec,
              totalPhysMem/1000,
              freePhysMem/1000,
              max_kB,
              cpu_time_portions[5],
              cpu_time_portions[6],/*time to read memory consumption, spent in rhs*/
              cpu_time_portions[7]/*time to read memory consumption, spent in numerics*/);
   }
   else if(T == 1){
      gettimeofday(tv0,tz);
      start = clock();
      Heun_all(dt_1D,K,NumberOfCells,Nstates,state,rate,intermediate,parameters,handle,cpu_time_portions,&max_kB);
      /*for(cell_idx = 1; cell_idx <= NumberOfCells; cell_idx++){
      improvedEuler(dt_1D, K, state + (cell_idx - 1) * Nstates, rate + (cell_idx - 1) * Nstates,
                               intermediate + (cell_idx - 1), parameters + (cell_idx - 1) * 2, Nstates,
                                                                     handle, cpu_time_portions);
      }*/
      end = clock();
      gettimeofday(tv1,tz);
      timeval_subtract(tv0, tv1, tv0);
      cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
      //## print output ##
      printf("%.*s %d T%d %d total: %f integration: %.17g thereof_state_evolution: %.17g evaluate_L_hs %.17g RHS_setup %.17g RHS_rate_evaluation %.17g elapsed_time: %ld.%06ld totalRAM_[kB]: %lld freeBeforeMALLOC_[kB]: %lld used_[kB]: %d rhs_malloc: %.17g ttrMemRhs %.17g ttrMemNum %.17g \n",
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
              tv0->tv_usec,
              totalPhysMem/1000,
              freePhysMem/1000,
              max_kB,
              cpu_time_portions[5],
              cpu_time_portions[6],/*time to read memory consumption, spent in rhs*/
              cpu_time_portions[7]/*time to read memory consumption, spent in numerics*/);
   }
   else{ printf("Invalid argument list: arg2 interpreted as integration type. Valid: 0 or 1.\n");}
   //## OpenCMISS Algorithm (end) #####################################################################
   //##################################################################################################
   return 0;
 }
 

/*int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
  /* Perform the carry for the later subtraction by updating y. */
/*  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
*/
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
/*  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
/*  return x->tv_sec < y->tv_sec;
}*/
