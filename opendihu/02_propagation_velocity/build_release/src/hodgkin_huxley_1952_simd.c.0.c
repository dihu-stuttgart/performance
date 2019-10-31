#include <math.h>
/*
   There are a total of 9 entries in the algebraic variable array.
   There are a total of 4 entries in each of the rate and state variable arrays.
   There are a total of 9 entries in the constant variable array.
 */
/*
 * VOI is time in component environment (millisecond).
 * STATES[0] is V in component membrane (millivolt).
 * CONSTANTS[0] is E_R in component membrane (millivolt).
 * CONSTANTS[1] is Cm in component membrane (microF_per_cm2).
 * ALGEBRAIC[0] is i_Na in component sodium_channel (microA_per_cm2).
 * ALGEBRAIC[4] is i_K in component potassium_channel (microA_per_cm2).
 * ALGEBRAIC[8] is i_L in component leakage_current (microA_per_cm2).
 * CONSTANTS[2] is i_Stim in component membrane (microA_per_cm2).
 * CONSTANTS[3] is g_Na in component sodium_channel (milliS_per_cm2).
 * CONSTANTS[6] is E_Na in component sodium_channel (millivolt).
 * STATES[1] is m in component sodium_channel_m_gate (dimensionless).
 * STATES[2] is h in component sodium_channel_h_gate (dimensionless).
 * ALGEBRAIC[1] is alpha_m in component sodium_channel_m_gate (per_millisecond).
 * ALGEBRAIC[5] is beta_m in component sodium_channel_m_gate (per_millisecond).
 * ALGEBRAIC[2] is alpha_h in component sodium_channel_h_gate (per_millisecond).
 * ALGEBRAIC[6] is beta_h in component sodium_channel_h_gate (per_millisecond).
 * CONSTANTS[4] is g_K in component potassium_channel (milliS_per_cm2).
 * CONSTANTS[7] is E_K in component potassium_channel (millivolt).
 * STATES[3] is n in component potassium_channel_n_gate (dimensionless).
 * ALGEBRAIC[3] is alpha_n in component potassium_channel_n_gate (per_millisecond).
 * ALGEBRAIC[7] is beta_n in component potassium_channel_n_gate (per_millisecond).
 * CONSTANTS[5] is g_L in component leakage_current (milliS_per_cm2).
 * CONSTANTS[8] is E_L in component leakage_current (millivolt).
 * RATES[0] is d/dt V in component membrane (millivolt).
 * RATES[1] is d/dt m in component sodium_channel_m_gate (dimensionless).
 * RATES[2] is d/dt h in component sodium_channel_h_gate (dimensionless).
 * RATES[3] is d/dt n in component potassium_channel_n_gate (dimensionless).
 */
void initConsts(double* CONSTANTS, double* RATES, double *STATES)
{
STATES[0] = -75;
CONSTANTS[0] = -75;
CONSTANTS[1] = 1;
CONSTANTS[2] = 0;
CONSTANTS[3] = 120;
STATES[1] = 0.05;
STATES[2] = 0.6;
CONSTANTS[4] = 36;
STATES[3] = 0.325;
CONSTANTS[5] = 0.3;
CONSTANTS[6] = CONSTANTS[0]+115.000;
CONSTANTS[7] = CONSTANTS[0] - 12.0000;
CONSTANTS[8] = CONSTANTS[0]+10.6130;
}

/* This function was created by opendihu at 2019/8/26 17:08:21.
 * It is designed for 960 instances of the CellML problem. */
void computeCellMLRightHandSide(void *context, double t, double *states, double *rates, double *intermediates, double *parameters)
{
  double VOI = t;   /* current simulation time */

  /* define constants */
  double CONSTANTS[9];
  CONSTANTS[0] = -75;
  CONSTANTS[1] = 1;
  CONSTANTS[2] = 0;
  CONSTANTS[3] = 120;
  CONSTANTS[4] = 36;
  CONSTANTS[5] = 0.3;
  CONSTANTS[6] = CONSTANTS[0]+115.000;
  CONSTANTS[7] = CONSTANTS[0] - 12.0000;
  CONSTANTS[8] = CONSTANTS[0]+10.6130;

  double ALGEBRAIC[8640];    /* 9 per instance * 960 instances */ 

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[960+i] = ( - 0.100000*(states[0+i]+50.0000))/(exp(- (states[0+i]+50.0000)/10.0000) - 1.00000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[4800+i] =  4.00000*exp(- (states[0+i]+75.0000)/18.0000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    rates[960+i] =  ALGEBRAIC[960+i]*(1.00000 - states[960+i]) -  ALGEBRAIC[4800+i]*states[960+i];
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[1920+i] =  0.0700000*exp(- (states[0+i]+75.0000)/20.0000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[5760+i] = 1.00000/(exp(- (states[0+i]+45.0000)/10.0000)+1.00000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    rates[1920+i] =  ALGEBRAIC[1920+i]*(1.00000 - states[1920+i]) -  ALGEBRAIC[5760+i]*states[1920+i];
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[2880+i] = ( - 0.0100000*(states[0+i]+65.0000))/(exp(- (states[0+i]+65.0000)/10.0000) - 1.00000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[6720+i] =  0.125000*exp((states[0+i]+75.0000)/80.0000);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    rates[2880+i] =  ALGEBRAIC[2880+i]*(1.00000 - states[2880+i]) -  ALGEBRAIC[6720+i]*states[2880+i];
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[0+i] =  CONSTANTS[3]*pow(states[960+i], 3.00000)*states[1920+i]*(states[0+i] - CONSTANTS[6]);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[3840+i] =  CONSTANTS[4]*pow(states[2880+i], 4.00000)*(states[0+i] - CONSTANTS[7]);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    ALGEBRAIC[7680+i] =  CONSTANTS[5]*(states[0+i] - CONSTANTS[8]);
  }

#ifndef TEST_WITHOUT_PRAGMAS
  #pragma omp for simd
#endif
  for (int i = 0; i < 960; i++)
  {
    rates[0+i] = - (- parameters[0+i]+ALGEBRAIC[0+i]+ALGEBRAIC[3840+i]+ALGEBRAIC[7680+i])/CONSTANTS[1];
  }
}

