typedef double real;
#include <cmath>
#include <omp.h>
#include <iostream>
#include <vector>

#pragma omp declare target
/*
   There are a total of 71 entries in the algebraic variable array.
   There are a total of 57 entries in each of the rate and state variable arrays.
   There are a total of 112 entries in the constant variable array.
 */
/*
 * VOI is time in component cell (millisecond).
 * CONSTANTS[0] is C_m in component wal_environment (microF_per_cm2).
 * CONSTANTS[1] is gam in component wal_environment (dimensionless).
 * CONSTANTS[2] is R_a in component wal_environment (ohm_cm2).
 * CONSTANTS[3] is tsi in component wal_environment (centi_metre).
 * CONSTANTS[4] is tsi2 in component wal_environment (centi_metre).
 * CONSTANTS[5] is tsi3 in component wal_environment (centi_metre).
 * CONSTANTS[6] is FF in component wal_environment (C_per_mol).
 * CONSTANTS[7] is tau_K in component wal_environment (millisecond).
 * CONSTANTS[8] is tau_Na in component wal_environment (millisecond).
 * CONSTANTS[9] is f_T in component wal_environment (dimensionless).
 * CONSTANTS[10] is tau_K2 in component wal_environment (millisecond).
 * CONSTANTS[11] is tau_Na2 in component wal_environment (millisecond).
 * CONSTANTS[12] is I_K_rest in component wal_environment (microA_per_cm2).
 * CONSTANTS[13] is I_Na_rest in component wal_environment (microA_per_cm2).
 * CONSTANTS[14] is alpha_h_bar in component wal_environment (per_millisecond).
 * CONSTANTS[15] is alpha_m_bar in component wal_environment (per_millisecond_per_millivolt).
 * CONSTANTS[16] is alpha_n_bar in component wal_environment (per_millisecond_per_millivolt).
 * CONSTANTS[17] is beta_h_bar in component wal_environment (per_millisecond).
 * CONSTANTS[18] is beta_m_bar in component wal_environment (per_millisecond).
 * CONSTANTS[19] is beta_n_bar in component wal_environment (per_millisecond).
 * CONSTANTS[20] is V_m in component wal_environment (millivolt).
 * CONSTANTS[21] is V_n in component wal_environment (millivolt).
 * CONSTANTS[22] is V_h in component wal_environment (millivolt).
 * CONSTANTS[23] is V_a in component wal_environment (millivolt).
 * CONSTANTS[24] is V_S_inf in component wal_environment (millivolt).
 * CONSTANTS[25] is V_h_K_inf in component wal_environment (millivolt).
 * CONSTANTS[26] is A_a in component wal_environment (millivolt).
 * CONSTANTS[27] is A_S_inf in component wal_environment (millivolt).
 * CONSTANTS[28] is A_h_K_inf in component wal_environment (millivolt).
 * CONSTANTS[29] is K_alpha_h in component wal_environment (millivolt).
 * CONSTANTS[30] is K_beta_h in component wal_environment (millivolt).
 * CONSTANTS[31] is K_alpha_m in component wal_environment (millivolt).
 * CONSTANTS[32] is K_alpha_n in component wal_environment (millivolt).
 * CONSTANTS[33] is K_beta_m in component wal_environment (millivolt).
 * CONSTANTS[34] is K_beta_n in component wal_environment (millivolt).
 * CONSTANTS[35] is RR in component wal_environment (milliJ_per_degreeK_per_mol).
 * CONSTANTS[36] is TT in component wal_environment (degreeK).
 * CONSTANTS[37] is g_Cl_bar in component wal_environment (milliS_per_cm2).
 * CONSTANTS[38] is g_K_bar in component wal_environment (milliS_per_cm2).
 * CONSTANTS[39] is g_Na_bar in component wal_environment (milliS_per_cm2).
 * CONSTANTS[40] is G_K in component wal_environment (milliS_per_cm2).
 * CONSTANTS[41] is del in component wal_environment (dimensionless).
 * CONSTANTS[42] is K_K in component wal_environment (milliM2).
 * CONSTANTS[43] is K_S in component wal_environment (milliM2).
 * CONSTANTS[44] is K_m_K in component wal_environment (milliM).
 * CONSTANTS[45] is K_m_Na in component wal_environment (milliM).
 * CONSTANTS[46] is S_i in component wal_environment (milliM).
 * CONSTANTS[47] is J_NaK_bar in component wal_environment (micro_mol_per_cm2_per_second).
 * CONSTANTS[48] is V_tau in component wal_environment (millivolt).
 * ALGEBRAIC[0] is I_T in component wal_environment (microA_per_cm2).
 * STATES[0] is vS in component wal_environment (millivolt).
 * STATES[1] is vT in component wal_environment (millivolt).
 * ALGEBRAIC[51] is I_ionic_s in component wal_environment (microA_per_cm2).
 * ALGEBRAIC[70] is I_ionic_t in component wal_environment (microA_per_cm2).
 * STATES[2] is K_t in component wal_environment (milliM).
 * STATES[3] is K_i in component wal_environment (milliM).
 * STATES[4] is K_e in component wal_environment (milliM).
 * STATES[5] is Na_i in component wal_environment (milliM).
 * STATES[6] is Na_t in component wal_environment (milliM).
 * STATES[7] is Na_e in component wal_environment (milliM).
 * ALGEBRAIC[14] is E_K in component wal_environment (millivolt).
 * ALGEBRAIC[26] is E_K_t in component wal_environment (millivolt).
 * ALGEBRAIC[27] is Cl_i in component wal_environment (milliM).
 * ALGEBRAIC[28] is Cl_o in component wal_environment (milliM).
 * ALGEBRAIC[29] is Cl_i_t in component wal_environment (milliM).
 * ALGEBRAIC[30] is Cl_o_t in component wal_environment (milliM).
 * ALGEBRAIC[31] is J_K in component wal_environment (milliV_milliM).
 * ALGEBRAIC[32] is J_K_t in component wal_environment (milliV_milliM).
 * CONSTANTS[49] is eta_Cl in component wal_environment (dimensionless).
 * CONSTANTS[50] is eta_IR in component wal_environment (dimensionless).
 * CONSTANTS[51] is eta_DR in component wal_environment (dimensionless).
 * CONSTANTS[52] is eta_Na in component wal_environment (dimensionless).
 * CONSTANTS[53] is eta_NaK in component wal_environment (dimensionless).
 * ALGEBRAIC[36] is I_Cl in component sarco_Cl_channel (microA_per_cm2).
 * ALGEBRAIC[41] is I_IR in component sarco_IR_channel (microA_per_cm2).
 * ALGEBRAIC[43] is I_DR in component sarco_DR_channel (microA_per_cm2).
 * ALGEBRAIC[46] is I_Na in component sarco_Na_channel (microA_per_cm2).
 * ALGEBRAIC[50] is I_NaK in component sarco_NaK_channel (microA_per_cm2).
 * ALGEBRAIC[55] is I_Cl_t in component t_Cl_channel (microA_per_cm2).
 * ALGEBRAIC[60] is I_IR_t in component t_IR_channel (microA_per_cm2).
 * ALGEBRAIC[62] is I_DR_t in component t_DR_channel (microA_per_cm2).
 * ALGEBRAIC[65] is I_Na_t in component t_Na_channel (microA_per_cm2).
 * ALGEBRAIC[69] is I_NaK_t in component t_NaK_channel (microA_per_cm2).
 * CONSTANTS[54] is I_HH in component wal_environment (microA_per_cm2).
 * ALGEBRAIC[33] is a in component sarco_Cl_channel (dimensionless).
 * ALGEBRAIC[34] is J_Cl in component sarco_Cl_channel (milliV_milliM).
 * ALGEBRAIC[35] is g_Cl in component sarco_Cl_channel (milliS_per_cm2).
 * ALGEBRAIC[37] is K_R in component sarco_IR_channel (milliM).
 * ALGEBRAIC[38] is g_IR_bar in component sarco_IR_channel (milliS_per_cm2).
 * ALGEBRAIC[39] is y in component sarco_IR_channel (dimensionless).
 * ALGEBRAIC[40] is g_IR in component sarco_IR_channel (milliS_per_cm2).
 * ALGEBRAIC[1] is alpha_n in component sarco_DR_channel (per_millisecond).
 * ALGEBRAIC[15] is beta_n in component sarco_DR_channel (per_millisecond).
 * ALGEBRAIC[2] is h_K_inf in component sarco_DR_channel (dimensionless).
 * ALGEBRAIC[16] is tau_h_K in component sarco_DR_channel (millisecond).
 * STATES[8] is n in component sarco_DR_channel (dimensionless).
 * STATES[9] is h_K in component sarco_DR_channel (dimensionless).
 * ALGEBRAIC[42] is g_DR in component sarco_DR_channel (milliS_per_cm2).
 * ALGEBRAIC[3] is alpha_h in component sarco_Na_channel (per_millisecond).
 * ALGEBRAIC[17] is beta_h in component sarco_Na_channel (per_millisecond).
 * ALGEBRAIC[4] is alpha_m in component sarco_Na_channel (per_millisecond).
 * ALGEBRAIC[18] is beta_m in component sarco_Na_channel (per_millisecond).
 * ALGEBRAIC[5] is S_inf in component sarco_Na_channel (dimensionless).
 * ALGEBRAIC[19] is tau_S in component sarco_Na_channel (millisecond).
 * STATES[10] is m in component sarco_Na_channel (dimensionless).
 * STATES[11] is h in component sarco_Na_channel (dimensionless).
 * STATES[12] is S in component sarco_Na_channel (dimensionless).
 * ALGEBRAIC[45] is g_Na in component sarco_Na_channel (milliS_per_cm2).
 * ALGEBRAIC[44] is J_Na in component sarco_Na_channel (milliV_milliM).
 * ALGEBRAIC[47] is sig in component sarco_NaK_channel (dimensionless).
 * ALGEBRAIC[48] is f1 in component sarco_NaK_channel (dimensionless).
 * ALGEBRAIC[49] is I_NaK_bar in component sarco_NaK_channel (microA_per_cm2).
 * ALGEBRAIC[52] is a_t in component t_Cl_channel (dimensionless).
 * ALGEBRAIC[53] is J_Cl_t in component t_Cl_channel (milliV_milliM).
 * ALGEBRAIC[54] is g_Cl_t in component t_Cl_channel (milliS_per_cm2).
 * ALGEBRAIC[56] is K_R_t in component t_IR_channel (milliM).
 * ALGEBRAIC[57] is g_IR_bar_t in component t_IR_channel (milliS_per_cm2).
 * ALGEBRAIC[58] is y_t in component t_IR_channel (dimensionless).
 * ALGEBRAIC[59] is g_IR_t in component t_IR_channel (milliS_per_cm2).
 * ALGEBRAIC[6] is alpha_n_t in component t_DR_channel (per_millisecond).
 * ALGEBRAIC[20] is beta_n_t in component t_DR_channel (per_millisecond).
 * ALGEBRAIC[7] is h_K_inf_t in component t_DR_channel (dimensionless).
 * ALGEBRAIC[21] is tau_h_K_t in component t_DR_channel (millisecond).
 * STATES[13] is n_t in component t_DR_channel (dimensionless).
 * STATES[14] is h_K_t in component t_DR_channel (dimensionless).
 * ALGEBRAIC[61] is g_DR_t in component t_DR_channel (milliS_per_cm2).
 * ALGEBRAIC[8] is alpha_h_t in component t_Na_channel (per_millisecond).
 * ALGEBRAIC[22] is beta_h_t in component t_Na_channel (per_millisecond).
 * ALGEBRAIC[9] is alpha_m_t in component t_Na_channel (per_millisecond).
 * ALGEBRAIC[23] is beta_m_t in component t_Na_channel (per_millisecond).
 * ALGEBRAIC[10] is S_inf_t in component t_Na_channel (dimensionless).
 * ALGEBRAIC[24] is tau_S_t in component t_Na_channel (millisecond).
 * STATES[15] is m_t in component t_Na_channel (dimensionless).
 * STATES[16] is h_t in component t_Na_channel (dimensionless).
 * STATES[17] is S_t in component t_Na_channel (dimensionless).
 * ALGEBRAIC[64] is g_Na_t in component t_Na_channel (milliS_per_cm2).
 * ALGEBRAIC[63] is J_Na_t in component t_Na_channel (milliV_milliM).
 * ALGEBRAIC[66] is sig_t in component t_NaK_channel (dimensionless).
 * ALGEBRAIC[67] is f1_t in component t_NaK_channel (dimensionless).
 * ALGEBRAIC[68] is I_NaK_bar_t in component t_NaK_channel (microA_per_cm2).
 * STATES[18] is O_0 in component sternrios (dimensionless).
 * STATES[19] is O_1 in component sternrios (dimensionless).
 * STATES[20] is O_2 in component sternrios (dimensionless).
 * STATES[21] is O_3 in component sternrios (dimensionless).
 * STATES[22] is O_4 in component sternrios (dimensionless).
 * CONSTANTS[55] is k_L in component sternrios (per_millisecond).
 * CONSTANTS[56] is k_Lm in component sternrios (per_millisecond).
 * CONSTANTS[57] is f in component sternrios (dimensionless).
 * CONSTANTS[58] is alpha1 in component sternrios (per_millisecond).
 * CONSTANTS[59] is K in component sternrios (millivolt).
 * CONSTANTS[60] is Vbar in component sternrios (millivolt).
 * STATES[23] is C_0 in component sternrios (dimensionless).
 * STATES[24] is C_1 in component sternrios (dimensionless).
 * STATES[25] is C_2 in component sternrios (dimensionless).
 * STATES[26] is C_3 in component sternrios (dimensionless).
 * STATES[27] is C_4 in component sternrios (dimensionless).
 * ALGEBRAIC[11] is k_C in component sternrios (per_millisecond).
 * ALGEBRAIC[25] is k_Cm in component sternrios (per_millisecond).
 * CONSTANTS[61] is nu_SR in component razumova (micromolar_per_millisecond_micrometre3).
 * CONSTANTS[62] is K_SR in component razumova (micromolar).
 * CONSTANTS[63] is L_e in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[64] is tau_R in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[65] is tau_SR_R in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[66] is L_S_0 in component razumova (micrometre).
 * CONSTANTS[67] is L_S in component razumova (micrometre).
 * CONSTANTS[68] is R_R in component razumova (micrometre).
 * CONSTANTS[106] is V_o in component razumova (micrometre3).
 * CONSTANTS[108] is V_1 in component razumova (micrometre3).
 * CONSTANTS[109] is V_2 in component razumova (micrometre3).
 * CONSTANTS[107] is V_SR in component razumova (micrometre3).
 * CONSTANTS[110] is V_SR1 in component razumova (micrometre3).
 * CONSTANTS[111] is V_SR2 in component razumova (micrometre3).
 * CONSTANTS[69] is k_T_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[70] is k_T_off in component razumova (per_millisecond).
 * CONSTANTS[71] is T_tot_0 in component razumova (micromolar).
 * CONSTANTS[72] is k_P_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[73] is k_P_off in component razumova (per_millisecond).
 * CONSTANTS[74] is P_tot in component razumova (micromolar).
 * CONSTANTS[75] is k_Mg_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[76] is k_Mg_off in component razumova (per_millisecond).
 * CONSTANTS[77] is k_Cs_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[78] is k_Cs_off in component razumova (per_millisecond).
 * CONSTANTS[79] is Cs_tot in component razumova (micromolar).
 * CONSTANTS[80] is k_CATP_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[81] is k_CATP_off in component razumova (per_millisecond).
 * CONSTANTS[82] is k_MATP_on in component razumova (per_micromolar_per_millisecond).
 * CONSTANTS[83] is k_MATP_off in component razumova (per_millisecond).
 * CONSTANTS[84] is tau_ATP in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[85] is tau_Mg in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[86] is k_0_on in component razumova (per_millisecond).
 * CONSTANTS[87] is k_0_off in component razumova (per_millisecond).
 * CONSTANTS[88] is k_Ca_on in component razumova (per_millisecond).
 * CONSTANTS[89] is k_Ca_off in component razumova (per_millisecond).
 * CONSTANTS[90] is f_o in component razumova (per_millisecond).
 * CONSTANTS[91] is f_p in component razumova (per_millisecond).
 * CONSTANTS[92] is h_o in component razumova (per_millisecond).
 * CONSTANTS[93] is h_p in component razumova (per_millisecond).
 * CONSTANTS[94] is g_o in component razumova (per_millisecond).
 * CONSTANTS[95] is b_p in component razumova (per_millisecond).
 * CONSTANTS[96] is k_p in component razumova (micrometre3_per_millisecond).
 * CONSTANTS[97] is A_p in component razumova (per_milliM3_per_millisecond).
 * CONSTANTS[98] is B_p in component razumova (per_milliM2_per_millisecond).
 * CONSTANTS[99] is PP in component razumova (milliM2).
 * CONSTANTS[100] is x_0 in component razumova (micrometre).
 * CONSTANTS[101] is x_1 in component razumova (micrometre).
 * CONSTANTS[102] is x_2 in component razumova (micrometre).
 * CONSTANTS[103] is eta in component razumova (micrometre).
 * ALGEBRAIC[12] is stress in component razumova (dimensionless).
 * STATES[28] is dummy in component razumova (newton_millisecond_per_m2).
 * CONSTANTS[104] is zeta in component razumova (micrometre).
 * ALGEBRAIC[13] is T_0 in component razumova (micromolar).
 * STATES[29] is Ca_1 in component razumova (micromolar).
 * STATES[30] is Ca_SR1 in component razumova (micromolar).
 * STATES[31] is Ca_2 in component razumova (micromolar).
 * STATES[32] is Ca_SR2 in component razumova (micromolar).
 * STATES[33] is Ca_T_2 in component razumova (micromolar).
 * STATES[34] is Ca_P1 in component razumova (micromolar).
 * STATES[35] is Ca_P2 in component razumova (micromolar).
 * STATES[36] is Mg_P1 in component razumova (micromolar).
 * STATES[37] is Mg_P2 in component razumova (micromolar).
 * STATES[38] is Ca_Cs1 in component razumova (micromolar).
 * STATES[39] is Ca_Cs2 in component razumova (micromolar).
 * STATES[40] is Ca_ATP1 in component razumova (micromolar).
 * STATES[41] is Ca_ATP2 in component razumova (micromolar).
 * STATES[42] is Mg_ATP1 in component razumova (micromolar).
 * STATES[43] is Mg_ATP2 in component razumova (micromolar).
 * STATES[44] is ATP1 in component razumova (micromolar).
 * STATES[45] is ATP2 in component razumova (micromolar).
 * STATES[46] is Mg1 in component razumova (micromolar).
 * STATES[47] is Mg2 in component razumova (micromolar).
 * STATES[48] is Ca_CaT2 in component razumova (micromolar).
 * STATES[49] is D_0 in component razumova (micromolar).
 * STATES[50] is D_1 in component razumova (micromolar).
 * STATES[51] is D_2 in component razumova (micromolar).
 * STATES[52] is A_1 in component razumova (micromolar).
 * STATES[53] is A_2 in component razumova (micromolar).
 * STATES[54] is P in component razumova (milliM).
 * STATES[55] is P_SR in component razumova (milliM).
 * STATES[56] is P_C_SR in component razumova (milliM).
 * CONSTANTS[105] is i2 in component razumova (micrometre3_per_millisecond).
 * RATES[0] is d/dt vS in component wal_environment (millivolt).
 * RATES[1] is d/dt vT in component wal_environment (millivolt).
 * RATES[3] is d/dt K_i in component wal_environment (milliM).
 * RATES[2] is d/dt K_t in component wal_environment (milliM).
 * RATES[4] is d/dt K_e in component wal_environment (milliM).
 * RATES[5] is d/dt Na_i in component wal_environment (milliM).
 * RATES[6] is d/dt Na_t in component wal_environment (milliM).
 * RATES[7] is d/dt Na_e in component wal_environment (milliM).
 * RATES[8] is d/dt n in component sarco_DR_channel (dimensionless).
 * RATES[9] is d/dt h_K in component sarco_DR_channel (dimensionless).
 * RATES[10] is d/dt m in component sarco_Na_channel (dimensionless).
 * RATES[11] is d/dt h in component sarco_Na_channel (dimensionless).
 * RATES[12] is d/dt S in component sarco_Na_channel (dimensionless).
 * RATES[13] is d/dt n_t in component t_DR_channel (dimensionless).
 * RATES[14] is d/dt h_K_t in component t_DR_channel (dimensionless).
 * RATES[15] is d/dt m_t in component t_Na_channel (dimensionless).
 * RATES[16] is d/dt h_t in component t_Na_channel (dimensionless).
 * RATES[17] is d/dt S_t in component t_Na_channel (dimensionless).
 * RATES[23] is d/dt C_0 in component sternrios (dimensionless).
 * RATES[18] is d/dt O_0 in component sternrios (dimensionless).
 * RATES[24] is d/dt C_1 in component sternrios (dimensionless).
 * RATES[19] is d/dt O_1 in component sternrios (dimensionless).
 * RATES[25] is d/dt C_2 in component sternrios (dimensionless).
 * RATES[20] is d/dt O_2 in component sternrios (dimensionless).
 * RATES[26] is d/dt C_3 in component sternrios (dimensionless).
 * RATES[21] is d/dt O_3 in component sternrios (dimensionless).
 * RATES[27] is d/dt C_4 in component sternrios (dimensionless).
 * RATES[22] is d/dt O_4 in component sternrios (dimensionless).
 * RATES[29] is d/dt Ca_1 in component razumova (micromolar).
 * RATES[30] is d/dt Ca_SR1 in component razumova (micromolar).
 * RATES[31] is d/dt Ca_2 in component razumova (micromolar).
 * RATES[32] is d/dt Ca_SR2 in component razumova (micromolar).
 * RATES[33] is d/dt Ca_T_2 in component razumova (micromolar).
 * RATES[34] is d/dt Ca_P1 in component razumova (micromolar).
 * RATES[35] is d/dt Ca_P2 in component razumova (micromolar).
 * RATES[36] is d/dt Mg_P1 in component razumova (micromolar).
 * RATES[37] is d/dt Mg_P2 in component razumova (micromolar).
 * RATES[38] is d/dt Ca_Cs1 in component razumova (micromolar).
 * RATES[39] is d/dt Ca_Cs2 in component razumova (micromolar).
 * RATES[40] is d/dt Ca_ATP1 in component razumova (micromolar).
 * RATES[41] is d/dt Ca_ATP2 in component razumova (micromolar).
 * RATES[42] is d/dt Mg_ATP1 in component razumova (micromolar).
 * RATES[43] is d/dt Mg_ATP2 in component razumova (micromolar).
 * RATES[44] is d/dt ATP1 in component razumova (micromolar).
 * RATES[45] is d/dt ATP2 in component razumova (micromolar).
 * RATES[46] is d/dt Mg1 in component razumova (micromolar).
 * RATES[47] is d/dt Mg2 in component razumova (micromolar).
 * RATES[48] is d/dt Ca_CaT2 in component razumova (micromolar).
 * RATES[49] is d/dt D_0 in component razumova (micromolar).
 * RATES[50] is d/dt D_1 in component razumova (micromolar).
 * RATES[51] is d/dt D_2 in component razumova (micromolar).
 * RATES[52] is d/dt A_1 in component razumova (micromolar).
 * RATES[53] is d/dt A_2 in component razumova (micromolar).
 * RATES[54] is d/dt P in component razumova (milliM).
 * RATES[55] is d/dt P_SR in component razumova (milliM).
 * RATES[56] is d/dt P_C_SR in component razumova (milliM).
 * RATES[28] is d/dt dummy in component razumova (newton_millisecond_per_m2).
 */


real log(real x)
{
  // Taylor expansion of the log function around x=1
  // note: std::log does not work on GPU!
  real t = x-1;
  real t2 = t*t;
  return t - 0.5*t2 + 1./3*t2*t - 0.25*t2*t2;
}

/* This file was created by opendihu at 2021/1/19 16:13:16.
 * It is designed for the FastMonodomainSolver and contains code for offloading to GPU.
  */

// helper functions
real exponential(real x);
real pow2(real x);
real pow3(real x);
real pow4(real x);
real powReciprocal1(real x);

real exponential(real x)
{
  //return Vc::exp(x);
  // it was determined the x is always in the range [-12,+12]

  // exp(x) = lim n→∞ (1 + x/n)^n, we set n=1024
  x = 1.0 + x / 1024.;
  for (int i = 0; i < 10; i++)
  {
    x *= x;
  }
  return x;

  // relative error of this implementation:
  // x    rel error
  // 0    0
  // 1    0.00048784455634225593
  // 3    0.0043763626896140342
  // 5    0.012093715791500804
  // 9    0.038557535762274039
  // 12   0.067389808619653505
}

real pow2(real x)
{
  return x*x;
}
real pow3(real x)
{
  return x*(pow2(x));
}

real pow4(real x)
{
  return pow2(pow2(x));
}

real powReciprocal1(real x)
{
  return 1./(x);
}


#pragma omp end declare target
    
// global size constants
const int nInstancesPerFiber = 1481;
const int nElementsOnFiber = 1480;
const int nFibersToCompute = 24;
const long long nInstancesToCompute = 35544;  // = nInstancesPerFiber*nFibersToCompute;
const int nStates = 57;
const int firingEventsNRows = 2;
const int firingEventsNColumns = 100;
const int frequencyJitterNColumns = 100;
const int nStatesTotal = 2026008;  // = nInstancesToCompute*nStates;
const int nParametersTotal = 71088;  // = nInstancesToCompute*2;
const int nElementLengths = 35520;  // = nElementsOnFiber*nFibersToCompute;
const int nFiringEvents = 200;  // = firingEventsNRows*firingEventsNColumns;
const int nFrequencyJitter = 2400;  // = nFibersToCompute*frequencyJitterNColumns;
const int nAlgebraicsForTransferIndices = 0;
const int nAlgebraicsForTransfer = 0;  // = nInstancesToCompute*nAlgebraicsForTransferIndices;
const int nStatesForTransferIndices = 1;
const int nStatesForTransfer = 35544;  // = nInstancesToCompute*nStatesForTransferIndices;


// the following code is generated by FastMonodomainSolver for offloading to GPU
// global variables to be stored on the target device
#pragma omp declare target
real states[nStatesTotal]                                     __attribute__ ((aligned (64)));             // including state 0 which is stored in vmValues
real statesOneInstance[nStates]                               __attribute__ ((aligned (64)));
int statesForTransferIndices[nStatesForTransferIndices]       __attribute__ ((aligned (64)));
char firingEvents[nFiringEvents]                              __attribute__ ((aligned (64)));
real setSpecificStatesFrequencyJitter[nFrequencyJitter]       __attribute__ ((aligned (64)));
char fiberIsCurrentlyStimulated[nFibersToCompute]             __attribute__ ((aligned (64)));
int motorUnitNo[nFibersToCompute]                             __attribute__ ((aligned (64)));
int fiberStimulationPointIndex[nFibersToCompute]              __attribute__ ((aligned (64)));
real lastStimulationCheckTime[nFibersToCompute]               __attribute__ ((aligned (64)));
real setSpecificStatesCallFrequency[nFibersToCompute]         __attribute__ ((aligned (64)));
real setSpecificStatesRepeatAfterFirstCall[nFibersToCompute]  __attribute__ ((aligned (64)));
real setSpecificStatesCallEnableBegin[nFibersToCompute]       __attribute__ ((aligned (64)));
real currentJitter[nFibersToCompute]                          __attribute__ ((aligned (64)));
int jitterIndex[nFibersToCompute]                             __attribute__ ((aligned (64)));

real vmValues[nInstancesToCompute]                            __attribute__ ((aligned (64)));

#pragma omp end declare target


#ifdef __cplusplus
extern "C"
#endif
void initializeArrays(const double *statesOneInstanceParameter, const int *algebraicsForTransferIndicesParameter, const int *statesForTransferIndicesParameter,
                      const char *firingEventsParameter, const double *setSpecificStatesFrequencyJitterParameter, const int *motorUnitNoParameter,
                      const int *fiberStimulationPointIndexParameter, const double *lastStimulationCheckTimeParameter,
                      const double *setSpecificStatesCallFrequencyParameter, const double *setSpecificStatesRepeatAfterFirstCallParameter,
                      const double *setSpecificStatesCallEnableBeginParameter)
{
  for (int i = 0; i < nStates; i++)
    statesOneInstance[i] = statesOneInstanceParameter[i];



  for (int i = 0; i < nStatesForTransferIndices; i++)
    statesForTransferIndices[i] = statesForTransferIndicesParameter[i];

  for (int i = 0; i < nFiringEvents; i++)
    firingEvents[i] = firingEventsParameter[i];

  for (int i = 0; i < nFrequencyJitter; i++)
    setSpecificStatesFrequencyJitter[i] = setSpecificStatesFrequencyJitterParameter[i];

  for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
  {
    motorUnitNo[fiberNo] = motorUnitNoParameter[fiberNo];
    fiberStimulationPointIndex[fiberNo] = fiberStimulationPointIndexParameter[fiberNo];
    lastStimulationCheckTime[fiberNo] = lastStimulationCheckTimeParameter[fiberNo];
    setSpecificStatesCallFrequency[fiberNo] = setSpecificStatesCallFrequencyParameter[fiberNo];
    setSpecificStatesRepeatAfterFirstCall[fiberNo] = setSpecificStatesRepeatAfterFirstCallParameter[fiberNo];
    setSpecificStatesCallEnableBegin[fiberNo] = setSpecificStatesCallEnableBeginParameter[fiberNo];
  }

  // set variables to zero
  for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
  {
    fiberIsCurrentlyStimulated[fiberNo] = 0;
    currentJitter[fiberNo] = 0;
    jitterIndex[fiberNo] = 0;
  }

  // initialize vmValues
  const double state0 = statesOneInstance[0];
  for (int instanceToComputeNo = 0; instanceToComputeNo < nInstancesToCompute; instanceToComputeNo++)
  {
    vmValues[instanceToComputeNo] = state0;
  }


  // map values to target
  #pragma omp target update to(states[:nStatesTotal], statesOneInstance[:nStates], \
    statesForTransferIndices[:nStatesForTransferIndices], \
    firingEvents[:nFiringEvents], setSpecificStatesFrequencyJitter[:nFrequencyJitter], \
    motorUnitNo[:nFibersToCompute], fiberStimulationPointIndex[:nFibersToCompute], \
    lastStimulationCheckTime[:nFibersToCompute], setSpecificStatesCallFrequency[:nFibersToCompute], \
    setSpecificStatesRepeatAfterFirstCall[:nFibersToCompute], setSpecificStatesCallEnableBegin[:nFibersToCompute], \
    currentJitter[:nFibersToCompute], jitterIndex[:nFibersToCompute], vmValues[:nInstancesToCompute])
  
  // initialize states
  #pragma omp target
  {
    // copy given values to variables on target
    for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
    {
      for (int instanceNo = 0; instanceNo < nInstancesPerFiber; instanceNo++)
      {
        int instanceToComputeNo = fiberNo*nInstancesPerFiber + instanceNo;

        // The entries in states[0] to states[1*nInstancesToCompute - 1] are not used.
        // State zero is stored in vmValues instead.
        for (int stateNo = 1; stateNo < nStates; stateNo++)
        {
          states[stateNo*nInstancesToCompute + instanceToComputeNo] = statesOneInstance[stateNo];
        }
      }
    }
  }
}

// compute the total monodomain equation
#ifdef __cplusplus
extern "C"
#endif
void computeMonodomain(const float *parameters,
                       double *algebraicsForTransfer, double *statesForTransfer, const float *elementLengths,
                       double startTime, double timeStepWidthSplitting, int nTimeStepsSplitting, double dt0D, int nTimeSteps0D, double dt1D, int nTimeSteps1D,
                       double prefactor, double valueForStimulatedPoint)
{


  // map data to and from GPU
  #pragma omp target data map(to: parameters[:nParametersTotal], elementLengths[:nElementLengths]) \
       map(from: statesForTransfer[:nStatesForTransfer])
  {

  // loop over splitting time steps
  #pragma omp target teams


  for (int timeStepNo = 0; timeStepNo < nTimeStepsSplitting; timeStepNo++)
  {
    // perform Strang splitting
    real currentTimeSplitting = startTime + timeStepNo * timeStepWidthSplitting;

    // compute midTimeSplitting once per step to reuse it. [currentTime, midTimeSplitting=currentTime+0.5*timeStepWidth, currentTime+timeStepWidth]
    real midTimeSplitting = currentTimeSplitting + 0.5 * timeStepWidthSplitting;
    bool storeAlgebraicsForTransferSplitting = false;   // do not store the computed algebraics values in the algebraicsForTransfer vector for communication, because this is the first 0D computation and they will be changed in the second 0D computation

    // perform Strang splitting:
    // 0D: [currentTimeSplitting, currentTimeSplitting + dt0D*nTimeSteps0D]
    // 1D: [currentTimeSplitting, currentTimeSplitting + dt1D*nTimeSteps1D]
    // 0D: [midTimeSplitting,     midTimeSplitting + dt0D*nTimeSteps0D]

    // advance 0D in [currentTimeSplitting, currentTimeSplitting + dt0D*nTimeSteps0D]
    // ------------------------------------------------------------

    // loop over fibers that will be computed on this rank
    #pragma omp distribute parallel for simd collapse(2)
    for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
    {
      // loop over instances to compute here
      for (int instanceNo = 0; instanceNo < nInstancesPerFiber; instanceNo++)
      {
        int instanceToComputeNo = fiberNo*nInstancesPerFiber + instanceNo;    // index of instance over all fibers

        // determine if current point is at center of fiber
        int fiberCenterIndex = fiberStimulationPointIndex[fiberNo];
        bool currentPointIsInCenter = fabs(fiberCenterIndex - instanceNo) < 4;

        // loop over 0D timesteps
        for (int timeStepNo = 0; timeStepNo < nTimeSteps0D; timeStepNo++)
        {
          real currentTime = currentTimeSplitting + timeStepNo * dt0D;

          // determine if fiber gets stimulated
          // check if current point will be stimulated
          bool stimulateCurrentPoint = false;
          if (currentPointIsInCenter)
          {
            // check if time has come to call setSpecificStates
            bool checkStimulation = false;

            if (currentTime >= lastStimulationCheckTime[fiberNo] + 1./(setSpecificStatesCallFrequency[fiberNo]+currentJitter[fiberNo])
                && currentTime >= setSpecificStatesCallEnableBegin[fiberNo]-1e-13)
            {
              checkStimulation = true;

              // if current stimulation is over
              if (setSpecificStatesRepeatAfterFirstCall[fiberNo] != 0
                  && currentTime - (lastStimulationCheckTime[fiberNo] + 1./(setSpecificStatesCallFrequency[fiberNo] + currentJitter[fiberNo])) > setSpecificStatesRepeatAfterFirstCall[fiberNo])
              {
                // advance time of last call to specificStates
                lastStimulationCheckTime[fiberNo] += 1./(setSpecificStatesCallFrequency[fiberNo] + currentJitter[fiberNo]);

                // compute new jitter value
                real jitterFactor = 0.0;
                if (frequencyJitterNColumns > 0)
                  jitterFactor = setSpecificStatesFrequencyJitter[fiberNo*frequencyJitterNColumns + jitterIndex[fiberNo] % frequencyJitterNColumns];
                currentJitter[fiberNo] = jitterFactor * setSpecificStatesCallFrequency[fiberNo];

                jitterIndex[fiberNo]++;

                checkStimulation = false;
              }
            }

            // instead of calling setSpecificStates, directly determine whether to stimulate from the firingEvents file
            int firingEventsTimeStepNo = int(currentTime * setSpecificStatesCallFrequency[fiberNo] + 0.5);
            int firingEventsIndex = (firingEventsTimeStepNo % firingEventsNRows)*firingEventsNColumns + (motorUnitNo[fiberNo] % firingEventsNColumns);
            // firingEvents_[timeStepNo*nMotorUnits + motorUnitNo[fiberNo]]

            stimulateCurrentPoint = checkStimulation && firingEvents[firingEventsIndex];
            fiberIsCurrentlyStimulated[fiberNo] = stimulateCurrentPoint? 1: 0;

            // output to console
            if (stimulateCurrentPoint && fiberCenterIndex == instanceNo)
            {
              if (omp_is_initial_device())
                printf("t: %f, stimulate fiber %d (local no.), MU %d (computation on CPU)\n", currentTime, fiberNo, motorUnitNo[fiberNo]);
              else
                printf("t: %f, stimulate fiber %d (local no.), MU %d (computation on GPU)\n", currentTime, fiberNo, motorUnitNo[fiberNo]);
            }
          }
          const bool storeAlgebraicsForTransfer = false;

          
          // CellML define constants
          const real constant0 = 0.58;
          const real constant1 = 2.79;
          const real constant2 = 150;
          const real constant3 = 0.000001;
          const real constant4 = 0.0025;
          const real constant5 = 0.0005;
          const real constant6 = 96485;
          const real constant7 = 559;
          const real constant8 = 559;
          const real constant9 = 0.00174;
          const real constant10 = 40229.885;
          const real constant11 = 40229.885;
          const real constant12 = 0.34;
          const real constant13 = -0.43;
          const real constant14 = 0.0081;
          const real constant15 = 0.288;
          const real constant16 = 0.0131;
          const real constant17 = 4.38;
          const real constant18 = 1.38;
          const real constant19 = 0.067;
          const real constant20 = -46;
          const real constant21 = -40;
          const real constant22 = -45;
          const real constant23 = 70;
          const real constant24 = -68;
          const real constant25 = -40;
          const real constant26 = 150;
          const real constant27 = 7.1;
          const real constant28 = 7.5;
          const real constant29 = 14.7;
          const real constant30 = 9;
          const real constant31 = 10;
          const real constant32 = 7;
          const real constant33 = 18;
          const real constant34 = 40;
          const real constant35 = 8314.41;
          const real constant36 = 293;
          const real constant37 = 3.275;
          const real constant38 = 10.8;
          const real constant39 = 134;
          const real constant40 = 1.85;
          const real constant41 = 0.4;
          const real constant42 = 950;
          const real constant43 = 1;
          const real constant44 = 1;
          const real constant45 = 13;
          const real constant46 = 10;
          const real constant47 = 0.0001656;
          const real constant48 = 70;
          const real constant49 = 0.1;
          const real constant50 = 1.0;
          const real constant51 = 0.45;
          const real constant52 = 0.1;
          const real constant53 = 0.1;
          const real constant54 = 0.0;
          const real constant55 = 0.002;
          const real constant56 = 1000;
          const real constant57 = 0.2;
          const real constant58 = 0.2;
          const real constant59 = 4.5;
          const real constant60 = -20;
          const real constant61 = 2.4375;
          const real constant62 = 1;
          const real constant63 = 0.00004;
          const real constant64 = 0.75;
          const real constant65 = 0.75;
          const real constant66 = 1.0;
          const real constant67 = 1.0;
          const real constant68 = 0.5;
          const real constant69 = 0.0885;
          const real constant70 = 0.115;
          const real constant71 = 140;
          const real constant72 = 0;
          const real constant73 = 0;
          const real constant74 = 1500;
          const real constant75 = 0;
          const real constant76 = 0;
          const real constant77 = 0.000004;
          const real constant78 = 0.005;
          const real constant79 = 31000;
          const real constant80 = 0.15;
          const real constant81 = 30;
          const real constant82 = 0.0015;
          const real constant83 = 0.15;
          const real constant84 = 0.375;
          const real constant85 = 1.5;
          const real constant86 = 0;
          const real constant87 = 0.15;
          const real constant88 = 0.15;
          const real constant89 = 0.05;
          const real constant90 = 0.5;
          const real constant91 = 5;
          const real constant92 = 0.08;
          const real constant93 = 0.06;
          const real constant94 = 0.04;
          const real constant95 = 0.00000394;
          const real constant96 = 0.00000362;
          const real constant97 = 1;
          const real constant98 = 0.0001;
          const real constant99 = 6;
          const real constant100 = 0.05;
          const real constant101 = 0.0;
          const real constant102 = 0.05;
          const real constant103 = 0.000107;
          const real constant104 = 0.0021;
          const real constant105 = 60;
          const real constant106 =  0.950000*constant66* 3.14159265358979*pow(constant68, 2.00000);
          const real constant107 =  0.0500000*constant66* 3.14159265358979*pow(constant68, 2.00000);
          const real constant108 =  0.0100000*constant106;
          const real constant109 =  0.990000*constant106;
          const real constant110 =  0.0100000*constant107;
          const real constant111 =  0.990000*constant107;

          // compute new rates, rhs(y_n)
          const real rate29 = (((( ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108) -  constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant108))+ constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108))+ - constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant108))+- ( ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo]))+- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo]);
          const real rate30 = ((( - ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110)+ constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant110))+ - constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110))+ - constant65*((states[1066320+instanceToComputeNo] - states[1137408+instanceToComputeNo])/constant110))+- ( ( constant77*states[1066320+instanceToComputeNo])*(constant79 - states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo]);
          const real rate32 = ((( constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant111)+ - constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant111))+ constant65*((states[1066320+instanceToComputeNo]+- states[1137408+instanceToComputeNo])/constant111))+- ( ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo])) -  (1000.00/1.00000)*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real rate34 =  ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo];
          const real rate35 =  ( constant72*states[1101864+instanceToComputeNo])*((constant74+- states[1244040+instanceToComputeNo])+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo];
          const real rate36 =  ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo];
          const real rate37 =  ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo];
          const real rate38 =  ( constant77*states[1066320+instanceToComputeNo])*(constant79+- states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo];
          const real rate39 =  ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo];
          const real rate40 = ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+ - constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant108);
          const real rate41 = ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+ constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant109);
          const real rate42 = ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo])+ - constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant108);
          const real rate43 = ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo])+ constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant109);
          const real rate44 = (- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant108);
          const real rate45 = (- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant109);
          const real rate46 = (- ( ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant108);
          const real rate47 = (- ( ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant109);
          const real rate48 = (( ( constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo]+ - constant70*states[1706112+instanceToComputeNo])+ - constant88*states[1706112+instanceToComputeNo])+ constant89*states[1812744+instanceToComputeNo];
          const real rate50 = (((( constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo]+ - constant70*states[1777200+instanceToComputeNo])+ constant86*states[1172952+instanceToComputeNo])+ - constant87*states[1777200+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1777200+instanceToComputeNo])+ constant70*states[1812744+instanceToComputeNo];
          const real rate51 = ((((( constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo]+ - constant70*states[1812744+instanceToComputeNo])+ constant88*states[1706112+instanceToComputeNo])+ - constant89*states[1812744+instanceToComputeNo])+ - constant90*states[1812744+instanceToComputeNo])+ constant91*states[1848288+instanceToComputeNo])+ constant94*states[1883832+instanceToComputeNo];
          const real rate52 = (( constant90*states[1812744+instanceToComputeNo]+ - constant91*states[1848288+instanceToComputeNo])+ constant93*states[1883832+instanceToComputeNo])+ - constant92*states[1848288+instanceToComputeNo];
          const real rate53 = ( - constant93*states[1883832+instanceToComputeNo]+ constant92*states[1848288+instanceToComputeNo])+ - constant94*states[1883832+instanceToComputeNo];
          const real rate54 =  (0.00100000/1.00000)*( constant92*states[1848288+instanceToComputeNo] -  constant93*states[1883832+instanceToComputeNo])+ -1.00000*constant95*states[1919376+instanceToComputeNo]+ -1.00000*constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant109);
          const real rate55 =  constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant111) -  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real rate56 =  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real algebraic13 = (constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo]>0.00000 ? constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo] : 0.00000);
          const real rate31 = (((( - constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant109)+ constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant109))+ constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant109))+- ((((((( constant69*states[1101864+instanceToComputeNo]*algebraic13+ - constant70*states[1172952+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1172952+instanceToComputeNo])+ - constant70*states[1706112+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo])+ - constant70*states[1777200+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo])+ - constant70*states[1812744+instanceToComputeNo]))+- ( ( constant72*states[1101864+instanceToComputeNo])*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo]))+- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo]);
          const real rate33 = (((( ( constant69*states[1101864+instanceToComputeNo])*algebraic13+ - constant70*states[1172952+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo])+ constant70*states[1706112+instanceToComputeNo])+ - constant86*states[1172952+instanceToComputeNo])+ constant87*states[1777200+instanceToComputeNo];
          const real rate49 = (( ( - constant69*states[1101864+instanceToComputeNo])*states[1741656+instanceToComputeNo]+ constant70*states[1777200+instanceToComputeNo])+ constant86*algebraic13)+ - constant87*states[1741656+instanceToComputeNo];
          const real algebraic12 =  ((( (states[1848288+instanceToComputeNo]/constant71)*constant101+ (states[1883832+instanceToComputeNo]/constant71)*constant102) - constant103)/constant104)*(parameters[35544+instanceToComputeNo]>=0.635000&&parameters[35544+instanceToComputeNo]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[35544+instanceToComputeNo] - 0.635000) : parameters[35544+instanceToComputeNo]>0.850000&&parameters[35544+instanceToComputeNo]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[35544+instanceToComputeNo] - 0.850000) : parameters[35544+instanceToComputeNo]>1.17000&&parameters[35544+instanceToComputeNo]<=1.25500 ? 1.00000 : parameters[35544+instanceToComputeNo]>1.25500&&parameters[35544+instanceToComputeNo]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[35544+instanceToComputeNo] - 1.25500) : 0.00000);
          const real rate28 = algebraic12;
          const real algebraic1 =  constant16*((vmValues[instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((vmValues[instanceToComputeNo] - constant21)/constant32))));
          const real algebraic15 =  constant19*exponential(- ((vmValues[instanceToComputeNo] - constant21)/constant34));
          const real rate8 =  algebraic1*(1.00000 - states[284352+instanceToComputeNo]) -  algebraic15*states[284352+instanceToComputeNo];
          const real algebraic2 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant25)/constant28));
          const real algebraic16 =  1000.00*exponential(- ((vmValues[instanceToComputeNo]+40.0000)/25.7500));
          const real rate9 = (algebraic2 - states[319896+instanceToComputeNo])/algebraic16;
          const real algebraic4 =  constant15*((vmValues[instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((vmValues[instanceToComputeNo] - constant20)/constant31))));
          const real algebraic18 =  constant18*exponential(- ((vmValues[instanceToComputeNo] - constant20)/constant33));
          const real rate10 =  algebraic4*(1.00000 - states[355440+instanceToComputeNo]) -  algebraic18*states[355440+instanceToComputeNo];
          const real algebraic3 =  constant14*exponential(- ((vmValues[instanceToComputeNo] - constant22)/constant29));
          const real algebraic17 = constant17/(1.00000+exponential(- ((vmValues[instanceToComputeNo] - constant22)/constant30)));
          const real rate11 =  algebraic3*(1.00000 - states[390984+instanceToComputeNo]) -  algebraic17*states[390984+instanceToComputeNo];
          const real algebraic5 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant24)/constant27));
          const real algebraic19 = 8571.00/(0.200000+ 5.65000*pow2((vmValues[instanceToComputeNo]+constant48)/100.000));
          const real rate12 = (algebraic5 - states[426528+instanceToComputeNo])/algebraic19;
          const real algebraic6 =  constant16*((states[35544+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant32))));
          const real algebraic20 =  constant19*exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant34));
          const real rate13 =  algebraic6*(1.00000 - states[462072+instanceToComputeNo]) -  algebraic20*states[462072+instanceToComputeNo];
          const real algebraic7 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant25)/constant28));
          const real algebraic21 =  1.00000*exponential(- ((states[35544+instanceToComputeNo]+40.0000)/25.7500));
          const real rate14 = (algebraic7 - states[497616+instanceToComputeNo])/algebraic21;
          const real algebraic9 =  constant15*((states[35544+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant31))));
          const real algebraic23 =  constant18*exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant33));
          const real rate15 =  algebraic9*(1.00000 - states[533160+instanceToComputeNo]) -  algebraic23*states[533160+instanceToComputeNo];
          const real algebraic8 =  constant14*exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant29));
          const real algebraic22 = constant17/(1.00000+exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant30)));
          const real rate16 =  algebraic8*(1.00000 - states[568704+instanceToComputeNo]) -  algebraic22*states[568704+instanceToComputeNo];
          const real algebraic10 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant24)/constant27));
          const real algebraic24 = 8571.00/(0.200000+ 5.65000*pow2((states[35544+instanceToComputeNo]+constant48)/100.000));
          const real rate17 = (algebraic10 - states[604248+instanceToComputeNo])/algebraic24;
          const real algebraic11 =  0.500000*constant58*exponential((states[35544+instanceToComputeNo] - constant60)/( 8.00000*constant59));
          const real algebraic25 =  0.500000*constant58*exponential((constant60 - states[35544+instanceToComputeNo])/( 8.00000*constant59));
          const real rate23 =  - constant55*states[817512+instanceToComputeNo]+ constant56*states[639792+instanceToComputeNo]+ -4.00000*algebraic11*states[817512+instanceToComputeNo]+ algebraic25*states[853056+instanceToComputeNo];
          const real rate18 =  constant55*states[817512+instanceToComputeNo]+ - constant56*states[639792+instanceToComputeNo]+( -4.00000*algebraic11*states[639792+instanceToComputeNo])/constant57+ constant57*algebraic25*states[675336+instanceToComputeNo];
          const real rate24 =  4.00000*algebraic11*states[817512+instanceToComputeNo]+ - algebraic25*states[853056+instanceToComputeNo]+( - constant55*states[853056+instanceToComputeNo])/constant57+ constant57*constant56*states[675336+instanceToComputeNo]+ -3.00000*algebraic11*states[853056+instanceToComputeNo]+ 2.00000*algebraic25*states[888600+instanceToComputeNo];
          const real rate19 = ( constant55*states[853056+instanceToComputeNo])/constant57+ - constant56*constant57*states[675336+instanceToComputeNo]+( 4.00000*algebraic11*states[639792+instanceToComputeNo])/constant57+ - constant57*algebraic25*states[675336+instanceToComputeNo]+( -3.00000*algebraic11*states[675336+instanceToComputeNo])/constant57+ 2.00000*constant57*algebraic25*states[710880+instanceToComputeNo];
          const real rate25 =  3.00000*algebraic11*states[853056+instanceToComputeNo]+ -2.00000*algebraic25*states[888600+instanceToComputeNo]+( - constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ pow2(constant57)*constant56*states[710880+instanceToComputeNo]+ -2.00000*algebraic11*states[888600+instanceToComputeNo]+ 3.00000*algebraic25*states[924144+instanceToComputeNo];
          const real rate20 = ( 3.00000*algebraic11*states[675336+instanceToComputeNo])/constant57+ -2.00000*constant57*algebraic25*states[710880+instanceToComputeNo]+( constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ - constant56*pow2(constant57)*states[710880+instanceToComputeNo]+( -2.00000*algebraic11*states[710880+instanceToComputeNo])/constant57+ 3.00000*constant57*algebraic25*states[746424+instanceToComputeNo];
          const real rate26 =  2.00000*algebraic11*states[888600+instanceToComputeNo]+ -3.00000*algebraic25*states[924144+instanceToComputeNo]+( - constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ constant56*pow3(constant57)*states[746424+instanceToComputeNo]+ - algebraic11*states[924144+instanceToComputeNo]+ 4.00000*algebraic25*states[959688+instanceToComputeNo];
          const real rate21 = ( constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ - constant56*pow3(constant57)*states[746424+instanceToComputeNo]+( 2.00000*algebraic11*states[710880+instanceToComputeNo])/constant57+ -3.00000*algebraic25*constant57*states[746424+instanceToComputeNo]+( - algebraic11*states[746424+instanceToComputeNo])/constant57+ 4.00000*constant57*algebraic25*states[781968+instanceToComputeNo];
          const real rate27 =  algebraic11*states[924144+instanceToComputeNo]+ -4.00000*algebraic25*states[959688+instanceToComputeNo]+( - constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real rate22 = ( algebraic11*states[746424+instanceToComputeNo])/constant57+ -4.00000*constant57*algebraic25*states[781968+instanceToComputeNo]+( constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ - constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real algebraic31 =  vmValues[instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[142176+instanceToComputeNo]*exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic14 =  (( constant35*constant36)/constant6)*log(states[142176+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real algebraic37 =  states[142176+instanceToComputeNo]*exponential( ( - constant41*algebraic14)*(constant6/( constant35*constant36)));
          const real algebraic38 =  constant40*(pow2(algebraic37)/(constant42+pow2(algebraic37)));
          const real algebraic39 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(algebraic37)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*vmValues[instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real algebraic40 =  algebraic38*algebraic39;
          const real algebraic41 =  algebraic40*(algebraic31>0.00000 ? 1.00000 : 0.00000)*(algebraic31/50.0000);
          const real algebraic42 =  ( constant38*pow4(states[284352+instanceToComputeNo]))*states[319896+instanceToComputeNo];
          const real algebraic43 =  algebraic42*(algebraic31/50.0000);
          const real algebraic47 =  (1.00000/7.00000)*(exponential(states[248808+instanceToComputeNo]/67.3000) - 1.00000);
          const real algebraic48 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*vmValues[instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*algebraic47*exponential(- ( vmValues[instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real algebraic49 =  constant6*(constant47/( pow2(1.00000+constant44/states[142176+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real algebraic50 =  algebraic49*algebraic48;
          const real rate4 = (algebraic41+algebraic43+constant12+ - 2.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant10;
          const real algebraic45 =  ( ( constant39*pow3(states[355440+instanceToComputeNo]))*states[390984+instanceToComputeNo])*states[426528+instanceToComputeNo];
          const real algebraic44 =  vmValues[instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[248808+instanceToComputeNo]*exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic46 =  algebraic45*(algebraic44/75.0000);
          const real rate7 = (algebraic46+constant13+ 3.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant11;
          const real algebraic0 =  (1000.00/1.00000)*((vmValues[instanceToComputeNo] - states[35544+instanceToComputeNo])/constant2);
          const real algebraic27 = 156.500/(5.00000+exponential(( - constant6*algebraic14)/( constant35*constant36)));
          const real algebraic28 = 156.500 -  5.00000*algebraic27;
          const real algebraic34 =  vmValues[instanceToComputeNo]*((algebraic27 -  algebraic28*exponential(( constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic33 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant23)/constant26));
          const real algebraic35 =  constant37*pow4(algebraic33);
          const real algebraic36 =  algebraic35*(algebraic34/45.0000);
          const real algebraic51 = algebraic36+algebraic41+algebraic43+algebraic46+algebraic50+- parameters[0+instanceToComputeNo];
          const real rate0 = - ((algebraic51+algebraic0)/constant0);
          const real algebraic32 =  states[35544+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[71088+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic26 =  (( constant35*constant36)/constant6)*log(states[71088+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real algebraic56 =  states[71088+instanceToComputeNo]*exponential( ( - constant41*algebraic26)*(constant6/( constant35*constant36)));
          const real algebraic57 =  constant40*(pow2(algebraic56)/(constant42+pow2(algebraic56)));
          const real algebraic58 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(algebraic56)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[35544+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real algebraic59 =  algebraic57*algebraic58;
          const real algebraic60 =  constant50*algebraic59*(algebraic32/50.0000);
          const real algebraic61 =  ( constant38*pow4(states[462072+instanceToComputeNo]))*states[497616+instanceToComputeNo];
          const real algebraic62 =  constant51*algebraic61*(algebraic32/50.0000);
          const real algebraic66 =  (1.00000/7.00000)*(exponential(states[213264+instanceToComputeNo]/67.3000) - 1.00000);
          const real algebraic67 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*algebraic66*exponential(- ( states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real algebraic68 =  constant6*(constant47/( pow2(1.00000+constant44/states[71088+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real algebraic69 =  constant53*algebraic68*algebraic67;
          const real rate3 =  - constant9*((algebraic60+algebraic62+constant12+ - 2.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (algebraic41+algebraic43+constant12+ -2.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real rate2 = (algebraic60+algebraic62+constant12+ - 2.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant7;
          const real algebraic64 =  ( ( constant39*pow3(states[533160+instanceToComputeNo]))*states[568704+instanceToComputeNo])*states[604248+instanceToComputeNo];
          const real algebraic63 =  states[35544+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[213264+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic65 =  constant52*algebraic64*(algebraic63/75.0000);
          const real rate5 =  - constant9*((algebraic65+constant13+ 3.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (algebraic46+constant13+ 3.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real rate6 = (algebraic65+constant13+ 3.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant8;
          const real algebraic29 = 156.500/(5.00000+exponential(( - constant6*algebraic26)/( constant35*constant36)));
          const real algebraic30 = 156.500 -  5.00000*algebraic29;
          const real algebraic53 =  states[35544+instanceToComputeNo]*((algebraic29 -  algebraic30*exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic52 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant23)/constant26));
          const real algebraic54 =  constant37*pow4(algebraic52);
          const real algebraic55 =  constant49*algebraic54*(algebraic53/45.0000);
          const real algebraic70 = algebraic55+algebraic60+algebraic62+algebraic65+algebraic69;
          const real rate1 = - ((algebraic70 - algebraic0/constant1)/constant0);

          // algebraic step
          // compute y* = y_n + dt*rhs(y_n), y_n = state, rhs(y_n) = rate, y* = intermediateState
          states[0+instanceToComputeNo] = vmValues[instanceToComputeNo] + dt0D*rate0;
          states[35544+instanceToComputeNo] = states[35544+instanceToComputeNo] + dt0D*rate1;
          states[71088+instanceToComputeNo] = states[71088+instanceToComputeNo] + dt0D*rate2;
          states[106632+instanceToComputeNo] = states[106632+instanceToComputeNo] + dt0D*rate3;
          states[142176+instanceToComputeNo] = states[142176+instanceToComputeNo] + dt0D*rate4;
          states[177720+instanceToComputeNo] = states[177720+instanceToComputeNo] + dt0D*rate5;
          states[213264+instanceToComputeNo] = states[213264+instanceToComputeNo] + dt0D*rate6;
          states[248808+instanceToComputeNo] = states[248808+instanceToComputeNo] + dt0D*rate7;
          states[284352+instanceToComputeNo] = states[284352+instanceToComputeNo] + dt0D*rate8;
          states[319896+instanceToComputeNo] = states[319896+instanceToComputeNo] + dt0D*rate9;
          states[355440+instanceToComputeNo] = states[355440+instanceToComputeNo] + dt0D*rate10;
          states[390984+instanceToComputeNo] = states[390984+instanceToComputeNo] + dt0D*rate11;
          states[426528+instanceToComputeNo] = states[426528+instanceToComputeNo] + dt0D*rate12;
          states[462072+instanceToComputeNo] = states[462072+instanceToComputeNo] + dt0D*rate13;
          states[497616+instanceToComputeNo] = states[497616+instanceToComputeNo] + dt0D*rate14;
          states[533160+instanceToComputeNo] = states[533160+instanceToComputeNo] + dt0D*rate15;
          states[568704+instanceToComputeNo] = states[568704+instanceToComputeNo] + dt0D*rate16;
          states[604248+instanceToComputeNo] = states[604248+instanceToComputeNo] + dt0D*rate17;
          states[639792+instanceToComputeNo] = states[639792+instanceToComputeNo] + dt0D*rate18;
          states[675336+instanceToComputeNo] = states[675336+instanceToComputeNo] + dt0D*rate19;
          states[710880+instanceToComputeNo] = states[710880+instanceToComputeNo] + dt0D*rate20;
          states[746424+instanceToComputeNo] = states[746424+instanceToComputeNo] + dt0D*rate21;
          states[781968+instanceToComputeNo] = states[781968+instanceToComputeNo] + dt0D*rate22;
          states[817512+instanceToComputeNo] = states[817512+instanceToComputeNo] + dt0D*rate23;
          states[853056+instanceToComputeNo] = states[853056+instanceToComputeNo] + dt0D*rate24;
          states[888600+instanceToComputeNo] = states[888600+instanceToComputeNo] + dt0D*rate25;
          states[924144+instanceToComputeNo] = states[924144+instanceToComputeNo] + dt0D*rate26;
          states[959688+instanceToComputeNo] = states[959688+instanceToComputeNo] + dt0D*rate27;
          states[995232+instanceToComputeNo] = states[995232+instanceToComputeNo] + dt0D*rate28;
          states[1030776+instanceToComputeNo] = states[1030776+instanceToComputeNo] + dt0D*rate29;
          states[1066320+instanceToComputeNo] = states[1066320+instanceToComputeNo] + dt0D*rate30;
          states[1101864+instanceToComputeNo] = states[1101864+instanceToComputeNo] + dt0D*rate31;
          states[1137408+instanceToComputeNo] = states[1137408+instanceToComputeNo] + dt0D*rate32;
          states[1172952+instanceToComputeNo] = states[1172952+instanceToComputeNo] + dt0D*rate33;
          states[1208496+instanceToComputeNo] = states[1208496+instanceToComputeNo] + dt0D*rate34;
          states[1244040+instanceToComputeNo] = states[1244040+instanceToComputeNo] + dt0D*rate35;
          states[1279584+instanceToComputeNo] = states[1279584+instanceToComputeNo] + dt0D*rate36;
          states[1315128+instanceToComputeNo] = states[1315128+instanceToComputeNo] + dt0D*rate37;
          states[1350672+instanceToComputeNo] = states[1350672+instanceToComputeNo] + dt0D*rate38;
          states[1386216+instanceToComputeNo] = states[1386216+instanceToComputeNo] + dt0D*rate39;
          states[1421760+instanceToComputeNo] = states[1421760+instanceToComputeNo] + dt0D*rate40;
          states[1457304+instanceToComputeNo] = states[1457304+instanceToComputeNo] + dt0D*rate41;
          states[1492848+instanceToComputeNo] = states[1492848+instanceToComputeNo] + dt0D*rate42;
          states[1528392+instanceToComputeNo] = states[1528392+instanceToComputeNo] + dt0D*rate43;
          states[1563936+instanceToComputeNo] = states[1563936+instanceToComputeNo] + dt0D*rate44;
          states[1599480+instanceToComputeNo] = states[1599480+instanceToComputeNo] + dt0D*rate45;
          states[1635024+instanceToComputeNo] = states[1635024+instanceToComputeNo] + dt0D*rate46;
          states[1670568+instanceToComputeNo] = states[1670568+instanceToComputeNo] + dt0D*rate47;
          states[1706112+instanceToComputeNo] = states[1706112+instanceToComputeNo] + dt0D*rate48;
          states[1741656+instanceToComputeNo] = states[1741656+instanceToComputeNo] + dt0D*rate49;
          states[1777200+instanceToComputeNo] = states[1777200+instanceToComputeNo] + dt0D*rate50;
          states[1812744+instanceToComputeNo] = states[1812744+instanceToComputeNo] + dt0D*rate51;
          states[1848288+instanceToComputeNo] = states[1848288+instanceToComputeNo] + dt0D*rate52;
          states[1883832+instanceToComputeNo] = states[1883832+instanceToComputeNo] + dt0D*rate53;
          states[1919376+instanceToComputeNo] = states[1919376+instanceToComputeNo] + dt0D*rate54;
          states[1954920+instanceToComputeNo] = states[1954920+instanceToComputeNo] + dt0D*rate55;
          states[1990464+instanceToComputeNo] = states[1990464+instanceToComputeNo] + dt0D*rate56;


          // if stimulation, set value of Vm (state0)
          if (stimulateCurrentPoint)
          {
            states[0+instanceToComputeNo] = valueForStimulatedPoint;
          }
          // compute new rates, rhs(y*)
          const real intermediateRate29 = (((( ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108) -  constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant108))+ constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108))+ - constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant108))+- ( ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo]))+- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo]);
          const real intermediateRate30 = ((( - ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110)+ constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant110))+ - constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110))+ - constant65*((states[1066320+instanceToComputeNo] - states[1137408+instanceToComputeNo])/constant110))+- ( ( constant77*states[1066320+instanceToComputeNo])*(constant79 - states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo]);
          const real intermediateRate32 = ((( constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant111)+ - constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant111))+ constant65*((states[1066320+instanceToComputeNo]+- states[1137408+instanceToComputeNo])/constant111))+- ( ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo])) -  (1000.00/1.00000)*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateRate34 =  ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo];
          const real intermediateRate35 =  ( constant72*states[1101864+instanceToComputeNo])*((constant74+- states[1244040+instanceToComputeNo])+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo];
          const real intermediateRate36 =  ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo];
          const real intermediateRate37 =  ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo];
          const real intermediateRate38 =  ( constant77*states[1066320+instanceToComputeNo])*(constant79+- states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo];
          const real intermediateRate39 =  ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo];
          const real intermediateRate40 = ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+ - constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant108);
          const real intermediateRate41 = ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+ constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant109);
          const real intermediateRate42 = ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo])+ - constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant108);
          const real intermediateRate43 = ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo])+ constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant109);
          const real intermediateRate44 = (- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant108);
          const real intermediateRate45 = (- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant109);
          const real intermediateRate46 = (- ( ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant108);
          const real intermediateRate47 = (- ( ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant109);
          const real intermediateRate48 = (( ( constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo]+ - constant70*states[1706112+instanceToComputeNo])+ - constant88*states[1706112+instanceToComputeNo])+ constant89*states[1812744+instanceToComputeNo];
          const real intermediateRate50 = (((( constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo]+ - constant70*states[1777200+instanceToComputeNo])+ constant86*states[1172952+instanceToComputeNo])+ - constant87*states[1777200+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1777200+instanceToComputeNo])+ constant70*states[1812744+instanceToComputeNo];
          const real intermediateRate51 = ((((( constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo]+ - constant70*states[1812744+instanceToComputeNo])+ constant88*states[1706112+instanceToComputeNo])+ - constant89*states[1812744+instanceToComputeNo])+ - constant90*states[1812744+instanceToComputeNo])+ constant91*states[1848288+instanceToComputeNo])+ constant94*states[1883832+instanceToComputeNo];
          const real intermediateRate52 = (( constant90*states[1812744+instanceToComputeNo]+ - constant91*states[1848288+instanceToComputeNo])+ constant93*states[1883832+instanceToComputeNo])+ - constant92*states[1848288+instanceToComputeNo];
          const real intermediateRate53 = ( - constant93*states[1883832+instanceToComputeNo]+ constant92*states[1848288+instanceToComputeNo])+ - constant94*states[1883832+instanceToComputeNo];
          const real intermediateRate54 =  (0.00100000/1.00000)*( constant92*states[1848288+instanceToComputeNo] -  constant93*states[1883832+instanceToComputeNo])+ -1.00000*constant95*states[1919376+instanceToComputeNo]+ -1.00000*constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant109);
          const real intermediateRate55 =  constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant111) -  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateRate56 =  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateAlgebraic13 = (constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo]>0.00000 ? constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo] : 0.00000);
          const real intermediateRate31 = (((( - constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant109)+ constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant109))+ constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant109))+- ((((((( constant69*states[1101864+instanceToComputeNo]*intermediateAlgebraic13+ - constant70*states[1172952+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1172952+instanceToComputeNo])+ - constant70*states[1706112+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo])+ - constant70*states[1777200+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo])+ - constant70*states[1812744+instanceToComputeNo]))+- ( ( constant72*states[1101864+instanceToComputeNo])*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo]))+- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo]);
          const real intermediateRate33 = (((( ( constant69*states[1101864+instanceToComputeNo])*intermediateAlgebraic13+ - constant70*states[1172952+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo])+ constant70*states[1706112+instanceToComputeNo])+ - constant86*states[1172952+instanceToComputeNo])+ constant87*states[1777200+instanceToComputeNo];
          const real intermediateRate49 = (( ( - constant69*states[1101864+instanceToComputeNo])*states[1741656+instanceToComputeNo]+ constant70*states[1777200+instanceToComputeNo])+ constant86*intermediateAlgebraic13)+ - constant87*states[1741656+instanceToComputeNo];
          const real intermediateAlgebraic12 =  ((( (states[1848288+instanceToComputeNo]/constant71)*constant101+ (states[1883832+instanceToComputeNo]/constant71)*constant102) - constant103)/constant104)*(parameters[35544+instanceToComputeNo]>=0.635000&&parameters[35544+instanceToComputeNo]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[35544+instanceToComputeNo] - 0.635000) : parameters[35544+instanceToComputeNo]>0.850000&&parameters[35544+instanceToComputeNo]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[35544+instanceToComputeNo] - 0.850000) : parameters[35544+instanceToComputeNo]>1.17000&&parameters[35544+instanceToComputeNo]<=1.25500 ? 1.00000 : parameters[35544+instanceToComputeNo]>1.25500&&parameters[35544+instanceToComputeNo]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[35544+instanceToComputeNo] - 1.25500) : 0.00000);
          const real intermediateRate28 = intermediateAlgebraic12;
          const real intermediateAlgebraic1 =  constant16*((states[0+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[0+instanceToComputeNo] - constant21)/constant32))));
          const real intermediateAlgebraic15 =  constant19*exponential(- ((states[0+instanceToComputeNo] - constant21)/constant34));
          const real intermediateRate8 =  intermediateAlgebraic1*(1.00000 - states[284352+instanceToComputeNo]) -  intermediateAlgebraic15*states[284352+instanceToComputeNo];
          const real intermediateAlgebraic2 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant25)/constant28));
          const real intermediateAlgebraic16 =  1000.00*exponential(- ((states[0+instanceToComputeNo]+40.0000)/25.7500));
          const real intermediateRate9 = (intermediateAlgebraic2 - states[319896+instanceToComputeNo])/intermediateAlgebraic16;
          const real intermediateAlgebraic4 =  constant15*((states[0+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[0+instanceToComputeNo] - constant20)/constant31))));
          const real intermediateAlgebraic18 =  constant18*exponential(- ((states[0+instanceToComputeNo] - constant20)/constant33));
          const real intermediateRate10 =  intermediateAlgebraic4*(1.00000 - states[355440+instanceToComputeNo]) -  intermediateAlgebraic18*states[355440+instanceToComputeNo];
          const real intermediateAlgebraic3 =  constant14*exponential(- ((states[0+instanceToComputeNo] - constant22)/constant29));
          const real intermediateAlgebraic17 = constant17/(1.00000+exponential(- ((states[0+instanceToComputeNo] - constant22)/constant30)));
          const real intermediateRate11 =  intermediateAlgebraic3*(1.00000 - states[390984+instanceToComputeNo]) -  intermediateAlgebraic17*states[390984+instanceToComputeNo];
          const real intermediateAlgebraic5 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant24)/constant27));
          const real intermediateAlgebraic19 = 8571.00/(0.200000+ 5.65000*pow2((states[0+instanceToComputeNo]+constant48)/100.000));
          const real intermediateRate12 = (intermediateAlgebraic5 - states[426528+instanceToComputeNo])/intermediateAlgebraic19;
          const real intermediateAlgebraic6 =  constant16*((states[35544+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant32))));
          const real intermediateAlgebraic20 =  constant19*exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant34));
          const real intermediateRate13 =  intermediateAlgebraic6*(1.00000 - states[462072+instanceToComputeNo]) -  intermediateAlgebraic20*states[462072+instanceToComputeNo];
          const real intermediateAlgebraic7 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant25)/constant28));
          const real intermediateAlgebraic21 =  1.00000*exponential(- ((states[35544+instanceToComputeNo]+40.0000)/25.7500));
          const real intermediateRate14 = (intermediateAlgebraic7 - states[497616+instanceToComputeNo])/intermediateAlgebraic21;
          const real intermediateAlgebraic9 =  constant15*((states[35544+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant31))));
          const real intermediateAlgebraic23 =  constant18*exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant33));
          const real intermediateRate15 =  intermediateAlgebraic9*(1.00000 - states[533160+instanceToComputeNo]) -  intermediateAlgebraic23*states[533160+instanceToComputeNo];
          const real intermediateAlgebraic8 =  constant14*exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant29));
          const real intermediateAlgebraic22 = constant17/(1.00000+exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant30)));
          const real intermediateRate16 =  intermediateAlgebraic8*(1.00000 - states[568704+instanceToComputeNo]) -  intermediateAlgebraic22*states[568704+instanceToComputeNo];
          const real intermediateAlgebraic10 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant24)/constant27));
          const real intermediateAlgebraic24 = 8571.00/(0.200000+ 5.65000*pow2((states[35544+instanceToComputeNo]+constant48)/100.000));
          const real intermediateRate17 = (intermediateAlgebraic10 - states[604248+instanceToComputeNo])/intermediateAlgebraic24;
          const real intermediateAlgebraic11 =  0.500000*constant58*exponential((states[35544+instanceToComputeNo] - constant60)/( 8.00000*constant59));
          const real intermediateAlgebraic25 =  0.500000*constant58*exponential((constant60 - states[35544+instanceToComputeNo])/( 8.00000*constant59));
          const real intermediateRate23 =  - constant55*states[817512+instanceToComputeNo]+ constant56*states[639792+instanceToComputeNo]+ -4.00000*intermediateAlgebraic11*states[817512+instanceToComputeNo]+ intermediateAlgebraic25*states[853056+instanceToComputeNo];
          const real intermediateRate18 =  constant55*states[817512+instanceToComputeNo]+ - constant56*states[639792+instanceToComputeNo]+( -4.00000*intermediateAlgebraic11*states[639792+instanceToComputeNo])/constant57+ constant57*intermediateAlgebraic25*states[675336+instanceToComputeNo];
          const real intermediateRate24 =  4.00000*intermediateAlgebraic11*states[817512+instanceToComputeNo]+ - intermediateAlgebraic25*states[853056+instanceToComputeNo]+( - constant55*states[853056+instanceToComputeNo])/constant57+ constant57*constant56*states[675336+instanceToComputeNo]+ -3.00000*intermediateAlgebraic11*states[853056+instanceToComputeNo]+ 2.00000*intermediateAlgebraic25*states[888600+instanceToComputeNo];
          const real intermediateRate19 = ( constant55*states[853056+instanceToComputeNo])/constant57+ - constant56*constant57*states[675336+instanceToComputeNo]+( 4.00000*intermediateAlgebraic11*states[639792+instanceToComputeNo])/constant57+ - constant57*intermediateAlgebraic25*states[675336+instanceToComputeNo]+( -3.00000*intermediateAlgebraic11*states[675336+instanceToComputeNo])/constant57+ 2.00000*constant57*intermediateAlgebraic25*states[710880+instanceToComputeNo];
          const real intermediateRate25 =  3.00000*intermediateAlgebraic11*states[853056+instanceToComputeNo]+ -2.00000*intermediateAlgebraic25*states[888600+instanceToComputeNo]+( - constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ pow2(constant57)*constant56*states[710880+instanceToComputeNo]+ -2.00000*intermediateAlgebraic11*states[888600+instanceToComputeNo]+ 3.00000*intermediateAlgebraic25*states[924144+instanceToComputeNo];
          const real intermediateRate20 = ( 3.00000*intermediateAlgebraic11*states[675336+instanceToComputeNo])/constant57+ -2.00000*constant57*intermediateAlgebraic25*states[710880+instanceToComputeNo]+( constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ - constant56*pow2(constant57)*states[710880+instanceToComputeNo]+( -2.00000*intermediateAlgebraic11*states[710880+instanceToComputeNo])/constant57+ 3.00000*constant57*intermediateAlgebraic25*states[746424+instanceToComputeNo];
          const real intermediateRate26 =  2.00000*intermediateAlgebraic11*states[888600+instanceToComputeNo]+ -3.00000*intermediateAlgebraic25*states[924144+instanceToComputeNo]+( - constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ constant56*pow3(constant57)*states[746424+instanceToComputeNo]+ - intermediateAlgebraic11*states[924144+instanceToComputeNo]+ 4.00000*intermediateAlgebraic25*states[959688+instanceToComputeNo];
          const real intermediateRate21 = ( constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ - constant56*pow3(constant57)*states[746424+instanceToComputeNo]+( 2.00000*intermediateAlgebraic11*states[710880+instanceToComputeNo])/constant57+ -3.00000*intermediateAlgebraic25*constant57*states[746424+instanceToComputeNo]+( - intermediateAlgebraic11*states[746424+instanceToComputeNo])/constant57+ 4.00000*constant57*intermediateAlgebraic25*states[781968+instanceToComputeNo];
          const real intermediateRate27 =  intermediateAlgebraic11*states[924144+instanceToComputeNo]+ -4.00000*intermediateAlgebraic25*states[959688+instanceToComputeNo]+( - constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real intermediateRate22 = ( intermediateAlgebraic11*states[746424+instanceToComputeNo])/constant57+ -4.00000*constant57*intermediateAlgebraic25*states[781968+instanceToComputeNo]+( constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ - constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real intermediateAlgebraic31 =  states[0+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[142176+instanceToComputeNo]*exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic14 =  (( constant35*constant36)/constant6)*log(states[142176+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real intermediateAlgebraic37 =  states[142176+instanceToComputeNo]*exponential( ( - constant41*intermediateAlgebraic14)*(constant6/( constant35*constant36)));
          const real intermediateAlgebraic38 =  constant40*(pow2(intermediateAlgebraic37)/(constant42+pow2(intermediateAlgebraic37)));
          const real intermediateAlgebraic39 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(intermediateAlgebraic37)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[0+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real intermediateAlgebraic40 =  intermediateAlgebraic38*intermediateAlgebraic39;
          const real intermediateAlgebraic41 =  intermediateAlgebraic40*(intermediateAlgebraic31>0.00000 ? 1.00000 : 0.00000)*(intermediateAlgebraic31/50.0000);
          const real intermediateAlgebraic42 =  ( constant38*pow4(states[284352+instanceToComputeNo]))*states[319896+instanceToComputeNo];
          const real intermediateAlgebraic43 =  intermediateAlgebraic42*(intermediateAlgebraic31/50.0000);
          const real intermediateAlgebraic47 =  (1.00000/7.00000)*(exponential(states[248808+instanceToComputeNo]/67.3000) - 1.00000);
          const real intermediateAlgebraic48 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[0+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*intermediateAlgebraic47*exponential(- ( states[0+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real intermediateAlgebraic49 =  constant6*(constant47/( pow2(1.00000+constant44/states[142176+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real intermediateAlgebraic50 =  intermediateAlgebraic49*intermediateAlgebraic48;
          const real intermediateRate4 = (intermediateAlgebraic41+intermediateAlgebraic43+constant12+ - 2.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant10;
          const real intermediateAlgebraic45 =  ( ( constant39*pow3(states[355440+instanceToComputeNo]))*states[390984+instanceToComputeNo])*states[426528+instanceToComputeNo];
          const real intermediateAlgebraic44 =  states[0+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[248808+instanceToComputeNo]*exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic46 =  intermediateAlgebraic45*(intermediateAlgebraic44/75.0000);
          const real intermediateRate7 = (intermediateAlgebraic46+constant13+ 3.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant11;
          const real intermediateAlgebraic0 =  (1000.00/1.00000)*((states[0+instanceToComputeNo] - states[35544+instanceToComputeNo])/constant2);
          const real intermediateAlgebraic27 = 156.500/(5.00000+exponential(( - constant6*intermediateAlgebraic14)/( constant35*constant36)));
          const real intermediateAlgebraic28 = 156.500 -  5.00000*intermediateAlgebraic27;
          const real intermediateAlgebraic34 =  states[0+instanceToComputeNo]*((intermediateAlgebraic27 -  intermediateAlgebraic28*exponential(( constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic33 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant23)/constant26));
          const real intermediateAlgebraic35 =  constant37*pow4(intermediateAlgebraic33);
          const real intermediateAlgebraic36 =  intermediateAlgebraic35*(intermediateAlgebraic34/45.0000);
          const real intermediateAlgebraic51 = intermediateAlgebraic36+intermediateAlgebraic41+intermediateAlgebraic43+intermediateAlgebraic46+intermediateAlgebraic50+- parameters[0+instanceToComputeNo];
          const real intermediateRate0 = - ((intermediateAlgebraic51+intermediateAlgebraic0)/constant0);
          const real intermediateAlgebraic32 =  states[35544+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[71088+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic26 =  (( constant35*constant36)/constant6)*log(states[71088+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real intermediateAlgebraic56 =  states[71088+instanceToComputeNo]*exponential( ( - constant41*intermediateAlgebraic26)*(constant6/( constant35*constant36)));
          const real intermediateAlgebraic57 =  constant40*(pow2(intermediateAlgebraic56)/(constant42+pow2(intermediateAlgebraic56)));
          const real intermediateAlgebraic58 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(intermediateAlgebraic56)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[35544+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real intermediateAlgebraic59 =  intermediateAlgebraic57*intermediateAlgebraic58;
          const real intermediateAlgebraic60 =  constant50*intermediateAlgebraic59*(intermediateAlgebraic32/50.0000);
          const real intermediateAlgebraic61 =  ( constant38*pow4(states[462072+instanceToComputeNo]))*states[497616+instanceToComputeNo];
          const real intermediateAlgebraic62 =  constant51*intermediateAlgebraic61*(intermediateAlgebraic32/50.0000);
          const real intermediateAlgebraic66 =  (1.00000/7.00000)*(exponential(states[213264+instanceToComputeNo]/67.3000) - 1.00000);
          const real intermediateAlgebraic67 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*intermediateAlgebraic66*exponential(- ( states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real intermediateAlgebraic68 =  constant6*(constant47/( pow2(1.00000+constant44/states[71088+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real intermediateAlgebraic69 =  constant53*intermediateAlgebraic68*intermediateAlgebraic67;
          const real intermediateRate3 =  - constant9*((intermediateAlgebraic60+intermediateAlgebraic62+constant12+ - 2.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (intermediateAlgebraic41+intermediateAlgebraic43+constant12+ -2.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real intermediateRate2 = (intermediateAlgebraic60+intermediateAlgebraic62+constant12+ - 2.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant7;
          const real intermediateAlgebraic64 =  ( ( constant39*pow3(states[533160+instanceToComputeNo]))*states[568704+instanceToComputeNo])*states[604248+instanceToComputeNo];
          const real intermediateAlgebraic63 =  states[35544+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[213264+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic65 =  constant52*intermediateAlgebraic64*(intermediateAlgebraic63/75.0000);
          const real intermediateRate5 =  - constant9*((intermediateAlgebraic65+constant13+ 3.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (intermediateAlgebraic46+constant13+ 3.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real intermediateRate6 = (intermediateAlgebraic65+constant13+ 3.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant8;
          const real intermediateAlgebraic29 = 156.500/(5.00000+exponential(( - constant6*intermediateAlgebraic26)/( constant35*constant36)));
          const real intermediateAlgebraic30 = 156.500 -  5.00000*intermediateAlgebraic29;
          const real intermediateAlgebraic53 =  states[35544+instanceToComputeNo]*((intermediateAlgebraic29 -  intermediateAlgebraic30*exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic52 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant23)/constant26));
          const real intermediateAlgebraic54 =  constant37*pow4(intermediateAlgebraic52);
          const real intermediateAlgebraic55 =  constant49*intermediateAlgebraic54*(intermediateAlgebraic53/45.0000);
          const real intermediateAlgebraic70 = intermediateAlgebraic55+intermediateAlgebraic60+intermediateAlgebraic62+intermediateAlgebraic65+intermediateAlgebraic69;
          const real intermediateRate1 = - ((intermediateAlgebraic70 - intermediateAlgebraic0/constant1)/constant0);

          // final step
          // y_n+1 = y_n + 0.5*[rhs(y_n) + rhs(y*)]
          vmValues[instanceToComputeNo] += 0.5*dt0D*(rate0 + intermediateRate0);
          states[35544+instanceToComputeNo] += 0.5*dt0D*(rate1 + intermediateRate1);
          states[71088+instanceToComputeNo] += 0.5*dt0D*(rate2 + intermediateRate2);
          states[106632+instanceToComputeNo] += 0.5*dt0D*(rate3 + intermediateRate3);
          states[142176+instanceToComputeNo] += 0.5*dt0D*(rate4 + intermediateRate4);
          states[177720+instanceToComputeNo] += 0.5*dt0D*(rate5 + intermediateRate5);
          states[213264+instanceToComputeNo] += 0.5*dt0D*(rate6 + intermediateRate6);
          states[248808+instanceToComputeNo] += 0.5*dt0D*(rate7 + intermediateRate7);
          states[284352+instanceToComputeNo] += 0.5*dt0D*(rate8 + intermediateRate8);
          states[319896+instanceToComputeNo] += 0.5*dt0D*(rate9 + intermediateRate9);
          states[355440+instanceToComputeNo] += 0.5*dt0D*(rate10 + intermediateRate10);
          states[390984+instanceToComputeNo] += 0.5*dt0D*(rate11 + intermediateRate11);
          states[426528+instanceToComputeNo] += 0.5*dt0D*(rate12 + intermediateRate12);
          states[462072+instanceToComputeNo] += 0.5*dt0D*(rate13 + intermediateRate13);
          states[497616+instanceToComputeNo] += 0.5*dt0D*(rate14 + intermediateRate14);
          states[533160+instanceToComputeNo] += 0.5*dt0D*(rate15 + intermediateRate15);
          states[568704+instanceToComputeNo] += 0.5*dt0D*(rate16 + intermediateRate16);
          states[604248+instanceToComputeNo] += 0.5*dt0D*(rate17 + intermediateRate17);
          states[639792+instanceToComputeNo] += 0.5*dt0D*(rate18 + intermediateRate18);
          states[675336+instanceToComputeNo] += 0.5*dt0D*(rate19 + intermediateRate19);
          states[710880+instanceToComputeNo] += 0.5*dt0D*(rate20 + intermediateRate20);
          states[746424+instanceToComputeNo] += 0.5*dt0D*(rate21 + intermediateRate21);
          states[781968+instanceToComputeNo] += 0.5*dt0D*(rate22 + intermediateRate22);
          states[817512+instanceToComputeNo] += 0.5*dt0D*(rate23 + intermediateRate23);
          states[853056+instanceToComputeNo] += 0.5*dt0D*(rate24 + intermediateRate24);
          states[888600+instanceToComputeNo] += 0.5*dt0D*(rate25 + intermediateRate25);
          states[924144+instanceToComputeNo] += 0.5*dt0D*(rate26 + intermediateRate26);
          states[959688+instanceToComputeNo] += 0.5*dt0D*(rate27 + intermediateRate27);
          states[995232+instanceToComputeNo] += 0.5*dt0D*(rate28 + intermediateRate28);
          states[1030776+instanceToComputeNo] += 0.5*dt0D*(rate29 + intermediateRate29);
          states[1066320+instanceToComputeNo] += 0.5*dt0D*(rate30 + intermediateRate30);
          states[1101864+instanceToComputeNo] += 0.5*dt0D*(rate31 + intermediateRate31);
          states[1137408+instanceToComputeNo] += 0.5*dt0D*(rate32 + intermediateRate32);
          states[1172952+instanceToComputeNo] += 0.5*dt0D*(rate33 + intermediateRate33);
          states[1208496+instanceToComputeNo] += 0.5*dt0D*(rate34 + intermediateRate34);
          states[1244040+instanceToComputeNo] += 0.5*dt0D*(rate35 + intermediateRate35);
          states[1279584+instanceToComputeNo] += 0.5*dt0D*(rate36 + intermediateRate36);
          states[1315128+instanceToComputeNo] += 0.5*dt0D*(rate37 + intermediateRate37);
          states[1350672+instanceToComputeNo] += 0.5*dt0D*(rate38 + intermediateRate38);
          states[1386216+instanceToComputeNo] += 0.5*dt0D*(rate39 + intermediateRate39);
          states[1421760+instanceToComputeNo] += 0.5*dt0D*(rate40 + intermediateRate40);
          states[1457304+instanceToComputeNo] += 0.5*dt0D*(rate41 + intermediateRate41);
          states[1492848+instanceToComputeNo] += 0.5*dt0D*(rate42 + intermediateRate42);
          states[1528392+instanceToComputeNo] += 0.5*dt0D*(rate43 + intermediateRate43);
          states[1563936+instanceToComputeNo] += 0.5*dt0D*(rate44 + intermediateRate44);
          states[1599480+instanceToComputeNo] += 0.5*dt0D*(rate45 + intermediateRate45);
          states[1635024+instanceToComputeNo] += 0.5*dt0D*(rate46 + intermediateRate46);
          states[1670568+instanceToComputeNo] += 0.5*dt0D*(rate47 + intermediateRate47);
          states[1706112+instanceToComputeNo] += 0.5*dt0D*(rate48 + intermediateRate48);
          states[1741656+instanceToComputeNo] += 0.5*dt0D*(rate49 + intermediateRate49);
          states[1777200+instanceToComputeNo] += 0.5*dt0D*(rate50 + intermediateRate50);
          states[1812744+instanceToComputeNo] += 0.5*dt0D*(rate51 + intermediateRate51);
          states[1848288+instanceToComputeNo] += 0.5*dt0D*(rate52 + intermediateRate52);
          states[1883832+instanceToComputeNo] += 0.5*dt0D*(rate53 + intermediateRate53);
          states[1919376+instanceToComputeNo] += 0.5*dt0D*(rate54 + intermediateRate54);
          states[1954920+instanceToComputeNo] += 0.5*dt0D*(rate55 + intermediateRate55);
          states[1990464+instanceToComputeNo] += 0.5*dt0D*(rate56 + intermediateRate56);

          if (stimulateCurrentPoint)
          {
            vmValues[instanceToComputeNo] = valueForStimulatedPoint;
          }  
  
          // store algebraics for transfer
          if (storeAlgebraicsForTransfer)
          {
            
            for (int i = 0; i < nStatesForTransferIndices; i++)
            {
              const int stateIndex = statesForTransferIndices[i];

              switch (stateIndex)
              {
                case 0:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = vmValues[instanceToComputeNo];
                  break;
                case 1:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[35544+instanceToComputeNo];
                  break;
                case 2:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[71088+instanceToComputeNo];
                  break;
                case 3:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[106632+instanceToComputeNo];
                  break;
                case 4:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[142176+instanceToComputeNo];
                  break;
                case 5:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[177720+instanceToComputeNo];
                  break;
                case 6:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[213264+instanceToComputeNo];
                  break;
                case 7:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[248808+instanceToComputeNo];
                  break;
                case 8:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[284352+instanceToComputeNo];
                  break;
                case 9:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[319896+instanceToComputeNo];
                  break;
                case 10:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[355440+instanceToComputeNo];
                  break;
                case 11:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[390984+instanceToComputeNo];
                  break;
                case 12:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[426528+instanceToComputeNo];
                  break;
                case 13:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[462072+instanceToComputeNo];
                  break;
                case 14:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[497616+instanceToComputeNo];
                  break;
                case 15:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[533160+instanceToComputeNo];
                  break;
                case 16:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[568704+instanceToComputeNo];
                  break;
                case 17:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[604248+instanceToComputeNo];
                  break;
                case 18:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[639792+instanceToComputeNo];
                  break;
                case 19:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[675336+instanceToComputeNo];
                  break;
                case 20:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[710880+instanceToComputeNo];
                  break;
                case 21:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[746424+instanceToComputeNo];
                  break;
                case 22:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[781968+instanceToComputeNo];
                  break;
                case 23:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[817512+instanceToComputeNo];
                  break;
                case 24:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[853056+instanceToComputeNo];
                  break;
                case 25:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[888600+instanceToComputeNo];
                  break;
                case 26:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[924144+instanceToComputeNo];
                  break;
                case 27:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[959688+instanceToComputeNo];
                  break;
                case 28:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[995232+instanceToComputeNo];
                  break;
                case 29:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1030776+instanceToComputeNo];
                  break;
                case 30:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1066320+instanceToComputeNo];
                  break;
                case 31:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1101864+instanceToComputeNo];
                  break;
                case 32:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1137408+instanceToComputeNo];
                  break;
                case 33:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1172952+instanceToComputeNo];
                  break;
                case 34:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1208496+instanceToComputeNo];
                  break;
                case 35:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1244040+instanceToComputeNo];
                  break;
                case 36:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1279584+instanceToComputeNo];
                  break;
                case 37:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1315128+instanceToComputeNo];
                  break;
                case 38:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1350672+instanceToComputeNo];
                  break;
                case 39:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1386216+instanceToComputeNo];
                  break;
                case 40:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1421760+instanceToComputeNo];
                  break;
                case 41:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1457304+instanceToComputeNo];
                  break;
                case 42:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1492848+instanceToComputeNo];
                  break;
                case 43:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1528392+instanceToComputeNo];
                  break;
                case 44:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1563936+instanceToComputeNo];
                  break;
                case 45:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1599480+instanceToComputeNo];
                  break;
                case 46:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1635024+instanceToComputeNo];
                  break;
                case 47:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1670568+instanceToComputeNo];
                  break;
                case 48:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1706112+instanceToComputeNo];
                  break;
                case 49:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1741656+instanceToComputeNo];
                  break;
                case 50:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1777200+instanceToComputeNo];
                  break;
                case 51:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1812744+instanceToComputeNo];
                  break;
                case 52:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1848288+instanceToComputeNo];
                  break;
                case 53:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1883832+instanceToComputeNo];
                  break;
                case 54:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1919376+instanceToComputeNo];
                  break;
                case 55:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1954920+instanceToComputeNo];
                  break;
                case 56:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1990464+instanceToComputeNo];
                  break;

              }
            }              
          }
        }  // loop over 0D timesteps
      }  // loop over instances
    }  // loop over fibers

    // advance 1D in [currentTimeSplitting, currentTimeSplitting + dt1D*nTimeSteps1D]
    // ------------------------------------------------------------

    // Implicit Euler step:
    // (K - 1/dt*M) u^{n+1} = -1/dt*M u^{n})
    // Crank-Nicolson step:
    // (1/2*K - 1/dt*M) u^{n+1} = (-1/2*K -1/dt*M) u^{n})

    // stencil K: 1/h*[_-1_  1  ]*prefactor
    // stencil M:   h*[_1/3_ 1/6]
    const real dt = dt1D;

    // loop over fibers
    #pragma omp distribute parallel for
    for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
    {

      const int nValues = nInstancesPerFiber;

      // [ b c     ] [x]   [d]
      // [ a b c   ] [x] = [d]
      // [   a b c ] [x]   [d]
      // [     a b ] [x]   [d]

      // Thomas algorithm
      // forward substitution
      // c'_0 = c_0 / b_0
      // c'_i = c_i / (b_i - c'_{i-1}*a_i)

      // d'_0 = d_0 / b_0
      // d'_i = (d_i - d'_{i-1}*a_i) / (b_i - c'_{i-1}*a_i)

      // backward substitution
      // x_n = d'_n
      // x_i = d'_i - c'_i * x_{i+1}

      // helper buffers c', d' for Thomas algorithm
      real cIntermediate[nInstancesPerFiber-1];
      real dIntermediate[nInstancesPerFiber];

      // perform forward substitution
      // loop over entries / rows of matrices, this is equal to the instances of the current fiber
      for (int valueNo = 0; valueNo < nValues; valueNo++)
      {
        int instanceToComputeNo = fiberNo*nInstancesPerFiber + valueNo;

        real a = 0;
        real b = 0;
        real c = 0;
        real d = 0;

        real u_previous = 0;
        real u_center = 0;
        real u_next = 0;

        u_center = vmValues[instanceToComputeNo];  // state 0 of the current instance

        // contribution from left element
        if (valueNo > 0)
        {
          u_previous = vmValues[instanceToComputeNo - 1];  // state 0 of the left instance

          // stencil K: 1/h*[1   _-1_ ]*prefactor
          // stencil M:   h*[1/6 _1/3_]

          real h_left = elementLengths[fiberNo*nElementsOnFiber + valueNo-1];
          real k_left = 1./h_left*(1) * prefactor;
          real m_left = h_left*1./6;

          a = (k_left - 1/dt*m_left);   // formula for implicit Euler

          real k_right = 1./h_left*(-1) * prefactor;
          real m_right = h_left*1./3;

          b += (k_right - 1/dt*m_right);     // formula for implicit Euler
          d += (-1/dt*m_left) * u_previous + (-1/dt*m_right) * u_center;

        }

        // contribution from right element
        if (valueNo < nValues-1)
        {
          u_next = vmValues[instanceToComputeNo + 1];  // state 0 of the right instance

          // stencil K: 1/h*[_-1_  1  ]*prefactor
          // stencil M:   h*[_1/3_ 1/6]

          real h_right = elementLengths[fiberNo*nElementsOnFiber + valueNo];
          real k_right = 1./h_right*(1) * prefactor;
          real m_right = h_right*1./6;

          c = (k_right - 1/dt*m_right);     // formula for implicit Euler


          real k_left = 1./h_right*(-1) * prefactor;
          real m_left = h_right*1./3;

          b += (k_left - 1/dt*m_left);
          d += (-1/dt*m_left) * u_center + (-1/dt*m_right) * u_next;     // formula for implicit Euler

        }

        if (valueNo == 0)
        {
          // c'_0 = c_0 / b_0
          cIntermediate[valueNo] = c / b;

          // d'_0 = d_0 / b_0
          dIntermediate[valueNo] = d / b;
        }
        else
        {
          if (valueNo != nValues-1)
          {
            // c'_i = c_i / (b_i - c'_{i-1}*a_i)
            cIntermediate[valueNo] = c / (b - cIntermediate[valueNo-1]*a);
          }

          // d'_i = (d_i - d'_{i-1}*a_i) / (b_i - c'_{i-1}*a_i)
          dIntermediate[valueNo] = (d - dIntermediate[valueNo-1]*a) / (b - cIntermediate[valueNo-1]*a);
        }
      }

      // perform backward substitution
      // x_n = d'_n
      vmValues[nValues-1] = dIntermediate[nValues-1];  // state 0 of the point (nValues-1)

      real previousValue = dIntermediate[nValues-1];

      // loop over entries / rows of matrices
      for (int valueNo = nValues-2; valueNo >= 0; valueNo--)
      {
        int instanceToComputeNo = fiberNo*nInstancesPerFiber + valueNo;

        // x_i = d'_i - c'_i * x_{i+1}
        real resultValue = dIntermediate[valueNo] - cIntermediate[valueNo] * previousValue;
        vmValues[instanceToComputeNo] = resultValue;

        previousValue = resultValue;
      }
    }

    // advance 0D in [midTimeSplitting,     midTimeSplitting + dt0D*nTimeSteps0D]
    // ------------------------------------------------------------
    // in the last timestep, store the computed algebraics values in the algebraicsForTransfer vector for communication
    storeAlgebraicsForTransferSplitting = timeStepNo == nTimeStepsSplitting-1;

    // loop over fibers that will be computed on this rank

    #pragma omp distribute parallel for simd collapse(2)
    for (int fiberNo = 0; fiberNo < nFibersToCompute; fiberNo++)
    {
      // loop over instances to compute here
      for (int instanceNo = 0; instanceNo < nInstancesPerFiber; instanceNo++)
      {
        int instanceToComputeNo = fiberNo*nInstancesPerFiber + instanceNo;    // index of instance over all fibers

        // determine if current point is at center of fiber
        int fiberCenterIndex = fiberStimulationPointIndex[fiberNo];
        bool currentPointIsInCenter = fabs(fiberCenterIndex - instanceNo) < 4;

        // loop over 0D timesteps
        for (int timeStepNo = 0; timeStepNo < nTimeSteps0D; timeStepNo++)
        {
          real currentTime = midTimeSplitting + timeStepNo * dt0D;

          // determine if fiber gets stimulated
          // check if current point will be stimulated
          bool stimulateCurrentPoint = false;
          if (currentPointIsInCenter)
          {
            // check if time has come to call setSpecificStates
            bool checkStimulation = false;

            if (currentTime >= lastStimulationCheckTime[fiberNo] + 1./(setSpecificStatesCallFrequency[fiberNo]+currentJitter[fiberNo])
                && currentTime >= setSpecificStatesCallEnableBegin[fiberNo]-1e-13)
            {
              checkStimulation = true;

              // if current stimulation is over
              if (setSpecificStatesRepeatAfterFirstCall[fiberNo] != 0
                  && currentTime - (lastStimulationCheckTime[fiberNo] + 1./(setSpecificStatesCallFrequency[fiberNo] + currentJitter[fiberNo])) > setSpecificStatesRepeatAfterFirstCall[fiberNo])
              {
                // advance time of last call to specificStates
                lastStimulationCheckTime[fiberNo] += 1./(setSpecificStatesCallFrequency[fiberNo] + currentJitter[fiberNo]);

                // compute new jitter value
                real jitterFactor = 0.0;
                if (frequencyJitterNColumns > 0)
                  jitterFactor = setSpecificStatesFrequencyJitter[fiberNo*frequencyJitterNColumns + jitterIndex[fiberNo] % frequencyJitterNColumns];
                currentJitter[fiberNo] = jitterFactor * setSpecificStatesCallFrequency[fiberNo];

                jitterIndex[fiberNo]++;

                checkStimulation = false;
              }
            }

            // instead of calling setSpecificStates, directly determine whether to stimulate from the firingEvents file
            int firingEventsTimeStepNo = int(currentTime * setSpecificStatesCallFrequency[fiberNo] + 0.5);
            int firingEventsIndex = (firingEventsTimeStepNo % firingEventsNRows)*firingEventsNColumns + (motorUnitNo[fiberNo] % firingEventsNColumns);
            // firingEvents_[timeStepNo*nMotorUnits + motorUnitNo[fiberNo]]

            stimulateCurrentPoint = checkStimulation && firingEvents[firingEventsIndex];
            fiberIsCurrentlyStimulated[fiberNo] = stimulateCurrentPoint? 1: 0;
          }
          const bool storeAlgebraicsForTransfer = storeAlgebraicsForTransferSplitting && timeStepNo == nTimeSteps0D-1;

          
          // CellML define constants
          const real constant0 = 0.58;
          const real constant1 = 2.79;
          const real constant2 = 150;
          const real constant3 = 0.000001;
          const real constant4 = 0.0025;
          const real constant5 = 0.0005;
          const real constant6 = 96485;
          const real constant7 = 559;
          const real constant8 = 559;
          const real constant9 = 0.00174;
          const real constant10 = 40229.885;
          const real constant11 = 40229.885;
          const real constant12 = 0.34;
          const real constant13 = -0.43;
          const real constant14 = 0.0081;
          const real constant15 = 0.288;
          const real constant16 = 0.0131;
          const real constant17 = 4.38;
          const real constant18 = 1.38;
          const real constant19 = 0.067;
          const real constant20 = -46;
          const real constant21 = -40;
          const real constant22 = -45;
          const real constant23 = 70;
          const real constant24 = -68;
          const real constant25 = -40;
          const real constant26 = 150;
          const real constant27 = 7.1;
          const real constant28 = 7.5;
          const real constant29 = 14.7;
          const real constant30 = 9;
          const real constant31 = 10;
          const real constant32 = 7;
          const real constant33 = 18;
          const real constant34 = 40;
          const real constant35 = 8314.41;
          const real constant36 = 293;
          const real constant37 = 3.275;
          const real constant38 = 10.8;
          const real constant39 = 134;
          const real constant40 = 1.85;
          const real constant41 = 0.4;
          const real constant42 = 950;
          const real constant43 = 1;
          const real constant44 = 1;
          const real constant45 = 13;
          const real constant46 = 10;
          const real constant47 = 0.0001656;
          const real constant48 = 70;
          const real constant49 = 0.1;
          const real constant50 = 1.0;
          const real constant51 = 0.45;
          const real constant52 = 0.1;
          const real constant53 = 0.1;
          const real constant54 = 0.0;
          const real constant55 = 0.002;
          const real constant56 = 1000;
          const real constant57 = 0.2;
          const real constant58 = 0.2;
          const real constant59 = 4.5;
          const real constant60 = -20;
          const real constant61 = 2.4375;
          const real constant62 = 1;
          const real constant63 = 0.00004;
          const real constant64 = 0.75;
          const real constant65 = 0.75;
          const real constant66 = 1.0;
          const real constant67 = 1.0;
          const real constant68 = 0.5;
          const real constant69 = 0.0885;
          const real constant70 = 0.115;
          const real constant71 = 140;
          const real constant72 = 0;
          const real constant73 = 0;
          const real constant74 = 1500;
          const real constant75 = 0;
          const real constant76 = 0;
          const real constant77 = 0.000004;
          const real constant78 = 0.005;
          const real constant79 = 31000;
          const real constant80 = 0.15;
          const real constant81 = 30;
          const real constant82 = 0.0015;
          const real constant83 = 0.15;
          const real constant84 = 0.375;
          const real constant85 = 1.5;
          const real constant86 = 0;
          const real constant87 = 0.15;
          const real constant88 = 0.15;
          const real constant89 = 0.05;
          const real constant90 = 0.5;
          const real constant91 = 5;
          const real constant92 = 0.08;
          const real constant93 = 0.06;
          const real constant94 = 0.04;
          const real constant95 = 0.00000394;
          const real constant96 = 0.00000362;
          const real constant97 = 1;
          const real constant98 = 0.0001;
          const real constant99 = 6;
          const real constant100 = 0.05;
          const real constant101 = 0.0;
          const real constant102 = 0.05;
          const real constant103 = 0.000107;
          const real constant104 = 0.0021;
          const real constant105 = 60;
          const real constant106 =  0.950000*constant66* 3.14159265358979*pow(constant68, 2.00000);
          const real constant107 =  0.0500000*constant66* 3.14159265358979*pow(constant68, 2.00000);
          const real constant108 =  0.0100000*constant106;
          const real constant109 =  0.990000*constant106;
          const real constant110 =  0.0100000*constant107;
          const real constant111 =  0.990000*constant107;

          // compute new rates, rhs(y_n)
          const real rate29 = (((( ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108) -  constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant108))+ constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108))+ - constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant108))+- ( ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo]))+- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo]);
          const real rate30 = ((( - ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110)+ constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant110))+ - constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110))+ - constant65*((states[1066320+instanceToComputeNo] - states[1137408+instanceToComputeNo])/constant110))+- ( ( constant77*states[1066320+instanceToComputeNo])*(constant79 - states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo]);
          const real rate32 = ((( constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant111)+ - constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant111))+ constant65*((states[1066320+instanceToComputeNo]+- states[1137408+instanceToComputeNo])/constant111))+- ( ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo])) -  (1000.00/1.00000)*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real rate34 =  ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo];
          const real rate35 =  ( constant72*states[1101864+instanceToComputeNo])*((constant74+- states[1244040+instanceToComputeNo])+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo];
          const real rate36 =  ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo];
          const real rate37 =  ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo];
          const real rate38 =  ( constant77*states[1066320+instanceToComputeNo])*(constant79+- states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo];
          const real rate39 =  ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo];
          const real rate40 = ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+ - constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant108);
          const real rate41 = ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+ constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant109);
          const real rate42 = ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo])+ - constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant108);
          const real rate43 = ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo])+ constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant109);
          const real rate44 = (- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant108);
          const real rate45 = (- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant109);
          const real rate46 = (- ( ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant108);
          const real rate47 = (- ( ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant109);
          const real rate48 = (( ( constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo]+ - constant70*states[1706112+instanceToComputeNo])+ - constant88*states[1706112+instanceToComputeNo])+ constant89*states[1812744+instanceToComputeNo];
          const real rate50 = (((( constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo]+ - constant70*states[1777200+instanceToComputeNo])+ constant86*states[1172952+instanceToComputeNo])+ - constant87*states[1777200+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1777200+instanceToComputeNo])+ constant70*states[1812744+instanceToComputeNo];
          const real rate51 = ((((( constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo]+ - constant70*states[1812744+instanceToComputeNo])+ constant88*states[1706112+instanceToComputeNo])+ - constant89*states[1812744+instanceToComputeNo])+ - constant90*states[1812744+instanceToComputeNo])+ constant91*states[1848288+instanceToComputeNo])+ constant94*states[1883832+instanceToComputeNo];
          const real rate52 = (( constant90*states[1812744+instanceToComputeNo]+ - constant91*states[1848288+instanceToComputeNo])+ constant93*states[1883832+instanceToComputeNo])+ - constant92*states[1848288+instanceToComputeNo];
          const real rate53 = ( - constant93*states[1883832+instanceToComputeNo]+ constant92*states[1848288+instanceToComputeNo])+ - constant94*states[1883832+instanceToComputeNo];
          const real rate54 =  (0.00100000/1.00000)*( constant92*states[1848288+instanceToComputeNo] -  constant93*states[1883832+instanceToComputeNo])+ -1.00000*constant95*states[1919376+instanceToComputeNo]+ -1.00000*constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant109);
          const real rate55 =  constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant111) -  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real rate56 =  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real algebraic13 = (constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo]>0.00000 ? constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo] : 0.00000);
          const real rate31 = (((( - constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant109)+ constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant109))+ constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant109))+- ((((((( constant69*states[1101864+instanceToComputeNo]*algebraic13+ - constant70*states[1172952+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1172952+instanceToComputeNo])+ - constant70*states[1706112+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo])+ - constant70*states[1777200+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo])+ - constant70*states[1812744+instanceToComputeNo]))+- ( ( constant72*states[1101864+instanceToComputeNo])*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo]))+- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo]);
          const real rate33 = (((( ( constant69*states[1101864+instanceToComputeNo])*algebraic13+ - constant70*states[1172952+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo])+ constant70*states[1706112+instanceToComputeNo])+ - constant86*states[1172952+instanceToComputeNo])+ constant87*states[1777200+instanceToComputeNo];
          const real rate49 = (( ( - constant69*states[1101864+instanceToComputeNo])*states[1741656+instanceToComputeNo]+ constant70*states[1777200+instanceToComputeNo])+ constant86*algebraic13)+ - constant87*states[1741656+instanceToComputeNo];
          const real algebraic12 =  ((( (states[1848288+instanceToComputeNo]/constant71)*constant101+ (states[1883832+instanceToComputeNo]/constant71)*constant102) - constant103)/constant104)*(parameters[35544+instanceToComputeNo]>=0.635000&&parameters[35544+instanceToComputeNo]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[35544+instanceToComputeNo] - 0.635000) : parameters[35544+instanceToComputeNo]>0.850000&&parameters[35544+instanceToComputeNo]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[35544+instanceToComputeNo] - 0.850000) : parameters[35544+instanceToComputeNo]>1.17000&&parameters[35544+instanceToComputeNo]<=1.25500 ? 1.00000 : parameters[35544+instanceToComputeNo]>1.25500&&parameters[35544+instanceToComputeNo]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[35544+instanceToComputeNo] - 1.25500) : 0.00000);
          const real rate28 = algebraic12;
          const real algebraic1 =  constant16*((vmValues[instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((vmValues[instanceToComputeNo] - constant21)/constant32))));
          const real algebraic15 =  constant19*exponential(- ((vmValues[instanceToComputeNo] - constant21)/constant34));
          const real rate8 =  algebraic1*(1.00000 - states[284352+instanceToComputeNo]) -  algebraic15*states[284352+instanceToComputeNo];
          const real algebraic2 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant25)/constant28));
          const real algebraic16 =  1000.00*exponential(- ((vmValues[instanceToComputeNo]+40.0000)/25.7500));
          const real rate9 = (algebraic2 - states[319896+instanceToComputeNo])/algebraic16;
          const real algebraic4 =  constant15*((vmValues[instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((vmValues[instanceToComputeNo] - constant20)/constant31))));
          const real algebraic18 =  constant18*exponential(- ((vmValues[instanceToComputeNo] - constant20)/constant33));
          const real rate10 =  algebraic4*(1.00000 - states[355440+instanceToComputeNo]) -  algebraic18*states[355440+instanceToComputeNo];
          const real algebraic3 =  constant14*exponential(- ((vmValues[instanceToComputeNo] - constant22)/constant29));
          const real algebraic17 = constant17/(1.00000+exponential(- ((vmValues[instanceToComputeNo] - constant22)/constant30)));
          const real rate11 =  algebraic3*(1.00000 - states[390984+instanceToComputeNo]) -  algebraic17*states[390984+instanceToComputeNo];
          const real algebraic5 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant24)/constant27));
          const real algebraic19 = 8571.00/(0.200000+ 5.65000*pow2((vmValues[instanceToComputeNo]+constant48)/100.000));
          const real rate12 = (algebraic5 - states[426528+instanceToComputeNo])/algebraic19;
          const real algebraic6 =  constant16*((states[35544+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant32))));
          const real algebraic20 =  constant19*exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant34));
          const real rate13 =  algebraic6*(1.00000 - states[462072+instanceToComputeNo]) -  algebraic20*states[462072+instanceToComputeNo];
          const real algebraic7 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant25)/constant28));
          const real algebraic21 =  1.00000*exponential(- ((states[35544+instanceToComputeNo]+40.0000)/25.7500));
          const real rate14 = (algebraic7 - states[497616+instanceToComputeNo])/algebraic21;
          const real algebraic9 =  constant15*((states[35544+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant31))));
          const real algebraic23 =  constant18*exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant33));
          const real rate15 =  algebraic9*(1.00000 - states[533160+instanceToComputeNo]) -  algebraic23*states[533160+instanceToComputeNo];
          const real algebraic8 =  constant14*exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant29));
          const real algebraic22 = constant17/(1.00000+exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant30)));
          const real rate16 =  algebraic8*(1.00000 - states[568704+instanceToComputeNo]) -  algebraic22*states[568704+instanceToComputeNo];
          const real algebraic10 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant24)/constant27));
          const real algebraic24 = 8571.00/(0.200000+ 5.65000*pow2((states[35544+instanceToComputeNo]+constant48)/100.000));
          const real rate17 = (algebraic10 - states[604248+instanceToComputeNo])/algebraic24;
          const real algebraic11 =  0.500000*constant58*exponential((states[35544+instanceToComputeNo] - constant60)/( 8.00000*constant59));
          const real algebraic25 =  0.500000*constant58*exponential((constant60 - states[35544+instanceToComputeNo])/( 8.00000*constant59));
          const real rate23 =  - constant55*states[817512+instanceToComputeNo]+ constant56*states[639792+instanceToComputeNo]+ -4.00000*algebraic11*states[817512+instanceToComputeNo]+ algebraic25*states[853056+instanceToComputeNo];
          const real rate18 =  constant55*states[817512+instanceToComputeNo]+ - constant56*states[639792+instanceToComputeNo]+( -4.00000*algebraic11*states[639792+instanceToComputeNo])/constant57+ constant57*algebraic25*states[675336+instanceToComputeNo];
          const real rate24 =  4.00000*algebraic11*states[817512+instanceToComputeNo]+ - algebraic25*states[853056+instanceToComputeNo]+( - constant55*states[853056+instanceToComputeNo])/constant57+ constant57*constant56*states[675336+instanceToComputeNo]+ -3.00000*algebraic11*states[853056+instanceToComputeNo]+ 2.00000*algebraic25*states[888600+instanceToComputeNo];
          const real rate19 = ( constant55*states[853056+instanceToComputeNo])/constant57+ - constant56*constant57*states[675336+instanceToComputeNo]+( 4.00000*algebraic11*states[639792+instanceToComputeNo])/constant57+ - constant57*algebraic25*states[675336+instanceToComputeNo]+( -3.00000*algebraic11*states[675336+instanceToComputeNo])/constant57+ 2.00000*constant57*algebraic25*states[710880+instanceToComputeNo];
          const real rate25 =  3.00000*algebraic11*states[853056+instanceToComputeNo]+ -2.00000*algebraic25*states[888600+instanceToComputeNo]+( - constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ pow2(constant57)*constant56*states[710880+instanceToComputeNo]+ -2.00000*algebraic11*states[888600+instanceToComputeNo]+ 3.00000*algebraic25*states[924144+instanceToComputeNo];
          const real rate20 = ( 3.00000*algebraic11*states[675336+instanceToComputeNo])/constant57+ -2.00000*constant57*algebraic25*states[710880+instanceToComputeNo]+( constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ - constant56*pow2(constant57)*states[710880+instanceToComputeNo]+( -2.00000*algebraic11*states[710880+instanceToComputeNo])/constant57+ 3.00000*constant57*algebraic25*states[746424+instanceToComputeNo];
          const real rate26 =  2.00000*algebraic11*states[888600+instanceToComputeNo]+ -3.00000*algebraic25*states[924144+instanceToComputeNo]+( - constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ constant56*pow3(constant57)*states[746424+instanceToComputeNo]+ - algebraic11*states[924144+instanceToComputeNo]+ 4.00000*algebraic25*states[959688+instanceToComputeNo];
          const real rate21 = ( constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ - constant56*pow3(constant57)*states[746424+instanceToComputeNo]+( 2.00000*algebraic11*states[710880+instanceToComputeNo])/constant57+ -3.00000*algebraic25*constant57*states[746424+instanceToComputeNo]+( - algebraic11*states[746424+instanceToComputeNo])/constant57+ 4.00000*constant57*algebraic25*states[781968+instanceToComputeNo];
          const real rate27 =  algebraic11*states[924144+instanceToComputeNo]+ -4.00000*algebraic25*states[959688+instanceToComputeNo]+( - constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real rate22 = ( algebraic11*states[746424+instanceToComputeNo])/constant57+ -4.00000*constant57*algebraic25*states[781968+instanceToComputeNo]+( constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ - constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real algebraic31 =  vmValues[instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[142176+instanceToComputeNo]*exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic14 =  (( constant35*constant36)/constant6)*log(states[142176+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real algebraic37 =  states[142176+instanceToComputeNo]*exponential( ( - constant41*algebraic14)*(constant6/( constant35*constant36)));
          const real algebraic38 =  constant40*(pow2(algebraic37)/(constant42+pow2(algebraic37)));
          const real algebraic39 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(algebraic37)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*vmValues[instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real algebraic40 =  algebraic38*algebraic39;
          const real algebraic41 =  algebraic40*(algebraic31>0.00000 ? 1.00000 : 0.00000)*(algebraic31/50.0000);
          const real algebraic42 =  ( constant38*pow4(states[284352+instanceToComputeNo]))*states[319896+instanceToComputeNo];
          const real algebraic43 =  algebraic42*(algebraic31/50.0000);
          const real algebraic47 =  (1.00000/7.00000)*(exponential(states[248808+instanceToComputeNo]/67.3000) - 1.00000);
          const real algebraic48 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*vmValues[instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*algebraic47*exponential(- ( vmValues[instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real algebraic49 =  constant6*(constant47/( pow2(1.00000+constant44/states[142176+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real algebraic50 =  algebraic49*algebraic48;
          const real rate4 = (algebraic41+algebraic43+constant12+ - 2.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant10;
          const real algebraic45 =  ( ( constant39*pow3(states[355440+instanceToComputeNo]))*states[390984+instanceToComputeNo])*states[426528+instanceToComputeNo];
          const real algebraic44 =  vmValues[instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[248808+instanceToComputeNo]*exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic46 =  algebraic45*(algebraic44/75.0000);
          const real rate7 = (algebraic46+constant13+ 3.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant11;
          const real algebraic0 =  (1000.00/1.00000)*((vmValues[instanceToComputeNo] - states[35544+instanceToComputeNo])/constant2);
          const real algebraic27 = 156.500/(5.00000+exponential(( - constant6*algebraic14)/( constant35*constant36)));
          const real algebraic28 = 156.500 -  5.00000*algebraic27;
          const real algebraic34 =  vmValues[instanceToComputeNo]*((algebraic27 -  algebraic28*exponential(( constant6*vmValues[instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*vmValues[instanceToComputeNo])/( constant35*constant36))));
          const real algebraic33 = 1.00000/(1.00000+exponential((vmValues[instanceToComputeNo] - constant23)/constant26));
          const real algebraic35 =  constant37*pow4(algebraic33);
          const real algebraic36 =  algebraic35*(algebraic34/45.0000);
          const real algebraic51 = algebraic36+algebraic41+algebraic43+algebraic46+algebraic50+- parameters[0+instanceToComputeNo];
          const real rate0 = - ((algebraic51+algebraic0)/constant0);
          const real algebraic32 =  states[35544+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[71088+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic26 =  (( constant35*constant36)/constant6)*log(states[71088+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real algebraic56 =  states[71088+instanceToComputeNo]*exponential( ( - constant41*algebraic26)*(constant6/( constant35*constant36)));
          const real algebraic57 =  constant40*(pow2(algebraic56)/(constant42+pow2(algebraic56)));
          const real algebraic58 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(algebraic56)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[35544+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real algebraic59 =  algebraic57*algebraic58;
          const real algebraic60 =  constant50*algebraic59*(algebraic32/50.0000);
          const real algebraic61 =  ( constant38*pow4(states[462072+instanceToComputeNo]))*states[497616+instanceToComputeNo];
          const real algebraic62 =  constant51*algebraic61*(algebraic32/50.0000);
          const real algebraic66 =  (1.00000/7.00000)*(exponential(states[213264+instanceToComputeNo]/67.3000) - 1.00000);
          const real algebraic67 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*algebraic66*exponential(- ( states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real algebraic68 =  constant6*(constant47/( pow2(1.00000+constant44/states[71088+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real algebraic69 =  constant53*algebraic68*algebraic67;
          const real rate3 =  - constant9*((algebraic60+algebraic62+constant12+ - 2.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (algebraic41+algebraic43+constant12+ -2.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real rate2 = (algebraic60+algebraic62+constant12+ - 2.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant7;
          const real algebraic64 =  ( ( constant39*pow3(states[533160+instanceToComputeNo]))*states[568704+instanceToComputeNo])*states[604248+instanceToComputeNo];
          const real algebraic63 =  states[35544+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[213264+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic65 =  constant52*algebraic64*(algebraic63/75.0000);
          const real rate5 =  - constant9*((algebraic65+constant13+ 3.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (algebraic46+constant13+ 3.00000*algebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real rate6 = (algebraic65+constant13+ 3.00000*algebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant8;
          const real algebraic29 = 156.500/(5.00000+exponential(( - constant6*algebraic26)/( constant35*constant36)));
          const real algebraic30 = 156.500 -  5.00000*algebraic29;
          const real algebraic53 =  states[35544+instanceToComputeNo]*((algebraic29 -  algebraic30*exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real algebraic52 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant23)/constant26));
          const real algebraic54 =  constant37*pow4(algebraic52);
          const real algebraic55 =  constant49*algebraic54*(algebraic53/45.0000);
          const real algebraic70 = algebraic55+algebraic60+algebraic62+algebraic65+algebraic69;
          const real rate1 = - ((algebraic70 - algebraic0/constant1)/constant0);

          // algebraic step
          // compute y* = y_n + dt*rhs(y_n), y_n = state, rhs(y_n) = rate, y* = intermediateState
          states[0+instanceToComputeNo] = vmValues[instanceToComputeNo] + dt0D*rate0;
          states[35544+instanceToComputeNo] = states[35544+instanceToComputeNo] + dt0D*rate1;
          states[71088+instanceToComputeNo] = states[71088+instanceToComputeNo] + dt0D*rate2;
          states[106632+instanceToComputeNo] = states[106632+instanceToComputeNo] + dt0D*rate3;
          states[142176+instanceToComputeNo] = states[142176+instanceToComputeNo] + dt0D*rate4;
          states[177720+instanceToComputeNo] = states[177720+instanceToComputeNo] + dt0D*rate5;
          states[213264+instanceToComputeNo] = states[213264+instanceToComputeNo] + dt0D*rate6;
          states[248808+instanceToComputeNo] = states[248808+instanceToComputeNo] + dt0D*rate7;
          states[284352+instanceToComputeNo] = states[284352+instanceToComputeNo] + dt0D*rate8;
          states[319896+instanceToComputeNo] = states[319896+instanceToComputeNo] + dt0D*rate9;
          states[355440+instanceToComputeNo] = states[355440+instanceToComputeNo] + dt0D*rate10;
          states[390984+instanceToComputeNo] = states[390984+instanceToComputeNo] + dt0D*rate11;
          states[426528+instanceToComputeNo] = states[426528+instanceToComputeNo] + dt0D*rate12;
          states[462072+instanceToComputeNo] = states[462072+instanceToComputeNo] + dt0D*rate13;
          states[497616+instanceToComputeNo] = states[497616+instanceToComputeNo] + dt0D*rate14;
          states[533160+instanceToComputeNo] = states[533160+instanceToComputeNo] + dt0D*rate15;
          states[568704+instanceToComputeNo] = states[568704+instanceToComputeNo] + dt0D*rate16;
          states[604248+instanceToComputeNo] = states[604248+instanceToComputeNo] + dt0D*rate17;
          states[639792+instanceToComputeNo] = states[639792+instanceToComputeNo] + dt0D*rate18;
          states[675336+instanceToComputeNo] = states[675336+instanceToComputeNo] + dt0D*rate19;
          states[710880+instanceToComputeNo] = states[710880+instanceToComputeNo] + dt0D*rate20;
          states[746424+instanceToComputeNo] = states[746424+instanceToComputeNo] + dt0D*rate21;
          states[781968+instanceToComputeNo] = states[781968+instanceToComputeNo] + dt0D*rate22;
          states[817512+instanceToComputeNo] = states[817512+instanceToComputeNo] + dt0D*rate23;
          states[853056+instanceToComputeNo] = states[853056+instanceToComputeNo] + dt0D*rate24;
          states[888600+instanceToComputeNo] = states[888600+instanceToComputeNo] + dt0D*rate25;
          states[924144+instanceToComputeNo] = states[924144+instanceToComputeNo] + dt0D*rate26;
          states[959688+instanceToComputeNo] = states[959688+instanceToComputeNo] + dt0D*rate27;
          states[995232+instanceToComputeNo] = states[995232+instanceToComputeNo] + dt0D*rate28;
          states[1030776+instanceToComputeNo] = states[1030776+instanceToComputeNo] + dt0D*rate29;
          states[1066320+instanceToComputeNo] = states[1066320+instanceToComputeNo] + dt0D*rate30;
          states[1101864+instanceToComputeNo] = states[1101864+instanceToComputeNo] + dt0D*rate31;
          states[1137408+instanceToComputeNo] = states[1137408+instanceToComputeNo] + dt0D*rate32;
          states[1172952+instanceToComputeNo] = states[1172952+instanceToComputeNo] + dt0D*rate33;
          states[1208496+instanceToComputeNo] = states[1208496+instanceToComputeNo] + dt0D*rate34;
          states[1244040+instanceToComputeNo] = states[1244040+instanceToComputeNo] + dt0D*rate35;
          states[1279584+instanceToComputeNo] = states[1279584+instanceToComputeNo] + dt0D*rate36;
          states[1315128+instanceToComputeNo] = states[1315128+instanceToComputeNo] + dt0D*rate37;
          states[1350672+instanceToComputeNo] = states[1350672+instanceToComputeNo] + dt0D*rate38;
          states[1386216+instanceToComputeNo] = states[1386216+instanceToComputeNo] + dt0D*rate39;
          states[1421760+instanceToComputeNo] = states[1421760+instanceToComputeNo] + dt0D*rate40;
          states[1457304+instanceToComputeNo] = states[1457304+instanceToComputeNo] + dt0D*rate41;
          states[1492848+instanceToComputeNo] = states[1492848+instanceToComputeNo] + dt0D*rate42;
          states[1528392+instanceToComputeNo] = states[1528392+instanceToComputeNo] + dt0D*rate43;
          states[1563936+instanceToComputeNo] = states[1563936+instanceToComputeNo] + dt0D*rate44;
          states[1599480+instanceToComputeNo] = states[1599480+instanceToComputeNo] + dt0D*rate45;
          states[1635024+instanceToComputeNo] = states[1635024+instanceToComputeNo] + dt0D*rate46;
          states[1670568+instanceToComputeNo] = states[1670568+instanceToComputeNo] + dt0D*rate47;
          states[1706112+instanceToComputeNo] = states[1706112+instanceToComputeNo] + dt0D*rate48;
          states[1741656+instanceToComputeNo] = states[1741656+instanceToComputeNo] + dt0D*rate49;
          states[1777200+instanceToComputeNo] = states[1777200+instanceToComputeNo] + dt0D*rate50;
          states[1812744+instanceToComputeNo] = states[1812744+instanceToComputeNo] + dt0D*rate51;
          states[1848288+instanceToComputeNo] = states[1848288+instanceToComputeNo] + dt0D*rate52;
          states[1883832+instanceToComputeNo] = states[1883832+instanceToComputeNo] + dt0D*rate53;
          states[1919376+instanceToComputeNo] = states[1919376+instanceToComputeNo] + dt0D*rate54;
          states[1954920+instanceToComputeNo] = states[1954920+instanceToComputeNo] + dt0D*rate55;
          states[1990464+instanceToComputeNo] = states[1990464+instanceToComputeNo] + dt0D*rate56;


          // if stimulation, set value of Vm (state0)
          if (stimulateCurrentPoint)
          {
            states[0+instanceToComputeNo] = valueForStimulatedPoint;
          }
          // compute new rates, rhs(y*)
          const real intermediateRate29 = (((( ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108) -  constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant108))+ constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant108))+ - constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant108))+- ( ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo]))+- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo]);
          const real intermediateRate30 = ((( - ( constant105*(states[639792+instanceToComputeNo]+states[675336+instanceToComputeNo]+states[710880+instanceToComputeNo]+states[746424+instanceToComputeNo]+states[781968+instanceToComputeNo]))*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110)+ constant61*((states[1030776+instanceToComputeNo]/(states[1030776+instanceToComputeNo]+constant62))/constant110))+ - constant63*((states[1066320+instanceToComputeNo] - states[1030776+instanceToComputeNo])/constant110))+ - constant65*((states[1066320+instanceToComputeNo] - states[1137408+instanceToComputeNo])/constant110))+- ( ( constant77*states[1066320+instanceToComputeNo])*(constant79 - states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo]);
          const real intermediateRate32 = ((( constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant111)+ - constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant111))+ constant65*((states[1066320+instanceToComputeNo]+- states[1137408+instanceToComputeNo])/constant111))+- ( ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo])) -  (1000.00/1.00000)*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateRate34 =  ( constant72*states[1030776+instanceToComputeNo])*((constant74+- states[1208496+instanceToComputeNo])+- states[1279584+instanceToComputeNo])+ - constant73*states[1208496+instanceToComputeNo];
          const real intermediateRate35 =  ( constant72*states[1101864+instanceToComputeNo])*((constant74+- states[1244040+instanceToComputeNo])+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo];
          const real intermediateRate36 =  ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo];
          const real intermediateRate37 =  ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo];
          const real intermediateRate38 =  ( constant77*states[1066320+instanceToComputeNo])*(constant79+- states[1350672+instanceToComputeNo])+ - constant78*states[1350672+instanceToComputeNo];
          const real intermediateRate39 =  ( constant77*states[1137408+instanceToComputeNo])*(constant79+- states[1386216+instanceToComputeNo])+ - constant78*states[1386216+instanceToComputeNo];
          const real intermediateRate40 = ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+ - constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant108);
          const real intermediateRate41 = ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+ constant84*((states[1421760+instanceToComputeNo]+- states[1457304+instanceToComputeNo])/constant109);
          const real intermediateRate42 = ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo])+ - constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant108);
          const real intermediateRate43 = ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo])+ constant84*((states[1492848+instanceToComputeNo]+- states[1528392+instanceToComputeNo])/constant109);
          const real intermediateRate44 = (- ( ( constant80*states[1030776+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant81*states[1421760+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant108);
          const real intermediateRate45 = (- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant84*((states[1563936+instanceToComputeNo]+- states[1599480+instanceToComputeNo])/constant109);
          const real intermediateRate46 = (- ( ( constant75*(constant74+- states[1208496+instanceToComputeNo]+- states[1279584+instanceToComputeNo]))*states[1635024+instanceToComputeNo]+ - constant76*states[1279584+instanceToComputeNo])+- ( ( constant82*states[1635024+instanceToComputeNo])*states[1563936+instanceToComputeNo]+ - constant83*states[1492848+instanceToComputeNo]))+ - constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant108);
          const real intermediateRate47 = (- ( ( constant75*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo]))*states[1670568+instanceToComputeNo]+ - constant76*states[1315128+instanceToComputeNo])+- ( ( constant82*states[1670568+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant83*states[1528392+instanceToComputeNo]))+ constant85*((states[1635024+instanceToComputeNo]+- states[1670568+instanceToComputeNo])/constant109);
          const real intermediateRate48 = (( ( constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo]+ - constant70*states[1706112+instanceToComputeNo])+ - constant88*states[1706112+instanceToComputeNo])+ constant89*states[1812744+instanceToComputeNo];
          const real intermediateRate50 = (((( constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo]+ - constant70*states[1777200+instanceToComputeNo])+ constant86*states[1172952+instanceToComputeNo])+ - constant87*states[1777200+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1777200+instanceToComputeNo])+ constant70*states[1812744+instanceToComputeNo];
          const real intermediateRate51 = ((((( constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo]+ - constant70*states[1812744+instanceToComputeNo])+ constant88*states[1706112+instanceToComputeNo])+ - constant89*states[1812744+instanceToComputeNo])+ - constant90*states[1812744+instanceToComputeNo])+ constant91*states[1848288+instanceToComputeNo])+ constant94*states[1883832+instanceToComputeNo];
          const real intermediateRate52 = (( constant90*states[1812744+instanceToComputeNo]+ - constant91*states[1848288+instanceToComputeNo])+ constant93*states[1883832+instanceToComputeNo])+ - constant92*states[1848288+instanceToComputeNo];
          const real intermediateRate53 = ( - constant93*states[1883832+instanceToComputeNo]+ constant92*states[1848288+instanceToComputeNo])+ - constant94*states[1883832+instanceToComputeNo];
          const real intermediateRate54 =  (0.00100000/1.00000)*( constant92*states[1848288+instanceToComputeNo] -  constant93*states[1883832+instanceToComputeNo])+ -1.00000*constant95*states[1919376+instanceToComputeNo]+ -1.00000*constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant109);
          const real intermediateRate55 =  constant96*((states[1919376+instanceToComputeNo] - states[1954920+instanceToComputeNo])/constant111) -  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateRate56 =  1.00000*( constant97*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99)*( states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo] - constant99>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[1954920+instanceToComputeNo]*states[1137408+instanceToComputeNo] -  constant98*states[1990464+instanceToComputeNo]*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo])*(constant99 -  states[1954920+instanceToComputeNo]*(0.00100000/1.00000)*states[1137408+instanceToComputeNo]>0.00000 ? 1.00000 : 0.00000));
          const real intermediateAlgebraic13 = (constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo]>0.00000 ? constant71+- states[1172952+instanceToComputeNo]+- states[1706112+instanceToComputeNo]+- states[1741656+instanceToComputeNo]+- states[1777200+instanceToComputeNo]+- states[1812744+instanceToComputeNo]+- states[1848288+instanceToComputeNo]+- states[1883832+instanceToComputeNo] : 0.00000);
          const real intermediateRate31 = (((( - constant61*((states[1101864+instanceToComputeNo]/(states[1101864+instanceToComputeNo]+constant62))/constant109)+ constant63*((states[1137408+instanceToComputeNo]+- states[1101864+instanceToComputeNo])/constant109))+ constant64*((states[1030776+instanceToComputeNo] - states[1101864+instanceToComputeNo])/constant109))+- ((((((( constant69*states[1101864+instanceToComputeNo]*intermediateAlgebraic13+ - constant70*states[1172952+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1172952+instanceToComputeNo])+ - constant70*states[1706112+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1741656+instanceToComputeNo])+ - constant70*states[1777200+instanceToComputeNo])+ constant69*states[1101864+instanceToComputeNo]*states[1777200+instanceToComputeNo])+ - constant70*states[1812744+instanceToComputeNo]))+- ( ( constant72*states[1101864+instanceToComputeNo])*(constant74+- states[1244040+instanceToComputeNo]+- states[1315128+instanceToComputeNo])+ - constant73*states[1244040+instanceToComputeNo]))+- ( ( constant80*states[1101864+instanceToComputeNo])*states[1599480+instanceToComputeNo]+ - constant81*states[1457304+instanceToComputeNo]);
          const real intermediateRate33 = (((( ( constant69*states[1101864+instanceToComputeNo])*intermediateAlgebraic13+ - constant70*states[1172952+instanceToComputeNo])+ ( - constant69*states[1101864+instanceToComputeNo])*states[1172952+instanceToComputeNo])+ constant70*states[1706112+instanceToComputeNo])+ - constant86*states[1172952+instanceToComputeNo])+ constant87*states[1777200+instanceToComputeNo];
          const real intermediateRate49 = (( ( - constant69*states[1101864+instanceToComputeNo])*states[1741656+instanceToComputeNo]+ constant70*states[1777200+instanceToComputeNo])+ constant86*intermediateAlgebraic13)+ - constant87*states[1741656+instanceToComputeNo];
          const real intermediateAlgebraic12 =  ((( (states[1848288+instanceToComputeNo]/constant71)*constant101+ (states[1883832+instanceToComputeNo]/constant71)*constant102) - constant103)/constant104)*(parameters[35544+instanceToComputeNo]>=0.635000&&parameters[35544+instanceToComputeNo]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[35544+instanceToComputeNo] - 0.635000) : parameters[35544+instanceToComputeNo]>0.850000&&parameters[35544+instanceToComputeNo]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[35544+instanceToComputeNo] - 0.850000) : parameters[35544+instanceToComputeNo]>1.17000&&parameters[35544+instanceToComputeNo]<=1.25500 ? 1.00000 : parameters[35544+instanceToComputeNo]>1.25500&&parameters[35544+instanceToComputeNo]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[35544+instanceToComputeNo] - 1.25500) : 0.00000);
          const real intermediateRate28 = intermediateAlgebraic12;
          const real intermediateAlgebraic1 =  constant16*((states[0+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[0+instanceToComputeNo] - constant21)/constant32))));
          const real intermediateAlgebraic15 =  constant19*exponential(- ((states[0+instanceToComputeNo] - constant21)/constant34));
          const real intermediateRate8 =  intermediateAlgebraic1*(1.00000 - states[284352+instanceToComputeNo]) -  intermediateAlgebraic15*states[284352+instanceToComputeNo];
          const real intermediateAlgebraic2 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant25)/constant28));
          const real intermediateAlgebraic16 =  1000.00*exponential(- ((states[0+instanceToComputeNo]+40.0000)/25.7500));
          const real intermediateRate9 = (intermediateAlgebraic2 - states[319896+instanceToComputeNo])/intermediateAlgebraic16;
          const real intermediateAlgebraic4 =  constant15*((states[0+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[0+instanceToComputeNo] - constant20)/constant31))));
          const real intermediateAlgebraic18 =  constant18*exponential(- ((states[0+instanceToComputeNo] - constant20)/constant33));
          const real intermediateRate10 =  intermediateAlgebraic4*(1.00000 - states[355440+instanceToComputeNo]) -  intermediateAlgebraic18*states[355440+instanceToComputeNo];
          const real intermediateAlgebraic3 =  constant14*exponential(- ((states[0+instanceToComputeNo] - constant22)/constant29));
          const real intermediateAlgebraic17 = constant17/(1.00000+exponential(- ((states[0+instanceToComputeNo] - constant22)/constant30)));
          const real intermediateRate11 =  intermediateAlgebraic3*(1.00000 - states[390984+instanceToComputeNo]) -  intermediateAlgebraic17*states[390984+instanceToComputeNo];
          const real intermediateAlgebraic5 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant24)/constant27));
          const real intermediateAlgebraic19 = 8571.00/(0.200000+ 5.65000*pow2((states[0+instanceToComputeNo]+constant48)/100.000));
          const real intermediateRate12 = (intermediateAlgebraic5 - states[426528+instanceToComputeNo])/intermediateAlgebraic19;
          const real intermediateAlgebraic6 =  constant16*((states[35544+instanceToComputeNo] - constant21)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant32))));
          const real intermediateAlgebraic20 =  constant19*exponential(- ((states[35544+instanceToComputeNo] - constant21)/constant34));
          const real intermediateRate13 =  intermediateAlgebraic6*(1.00000 - states[462072+instanceToComputeNo]) -  intermediateAlgebraic20*states[462072+instanceToComputeNo];
          const real intermediateAlgebraic7 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant25)/constant28));
          const real intermediateAlgebraic21 =  1.00000*exponential(- ((states[35544+instanceToComputeNo]+40.0000)/25.7500));
          const real intermediateRate14 = (intermediateAlgebraic7 - states[497616+instanceToComputeNo])/intermediateAlgebraic21;
          const real intermediateAlgebraic9 =  constant15*((states[35544+instanceToComputeNo] - constant20)/(1.00000 - exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant31))));
          const real intermediateAlgebraic23 =  constant18*exponential(- ((states[35544+instanceToComputeNo] - constant20)/constant33));
          const real intermediateRate15 =  intermediateAlgebraic9*(1.00000 - states[533160+instanceToComputeNo]) -  intermediateAlgebraic23*states[533160+instanceToComputeNo];
          const real intermediateAlgebraic8 =  constant14*exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant29));
          const real intermediateAlgebraic22 = constant17/(1.00000+exponential(- ((states[35544+instanceToComputeNo] - constant22)/constant30)));
          const real intermediateRate16 =  intermediateAlgebraic8*(1.00000 - states[568704+instanceToComputeNo]) -  intermediateAlgebraic22*states[568704+instanceToComputeNo];
          const real intermediateAlgebraic10 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant24)/constant27));
          const real intermediateAlgebraic24 = 8571.00/(0.200000+ 5.65000*pow2((states[35544+instanceToComputeNo]+constant48)/100.000));
          const real intermediateRate17 = (intermediateAlgebraic10 - states[604248+instanceToComputeNo])/intermediateAlgebraic24;
          const real intermediateAlgebraic11 =  0.500000*constant58*exponential((states[35544+instanceToComputeNo] - constant60)/( 8.00000*constant59));
          const real intermediateAlgebraic25 =  0.500000*constant58*exponential((constant60 - states[35544+instanceToComputeNo])/( 8.00000*constant59));
          const real intermediateRate23 =  - constant55*states[817512+instanceToComputeNo]+ constant56*states[639792+instanceToComputeNo]+ -4.00000*intermediateAlgebraic11*states[817512+instanceToComputeNo]+ intermediateAlgebraic25*states[853056+instanceToComputeNo];
          const real intermediateRate18 =  constant55*states[817512+instanceToComputeNo]+ - constant56*states[639792+instanceToComputeNo]+( -4.00000*intermediateAlgebraic11*states[639792+instanceToComputeNo])/constant57+ constant57*intermediateAlgebraic25*states[675336+instanceToComputeNo];
          const real intermediateRate24 =  4.00000*intermediateAlgebraic11*states[817512+instanceToComputeNo]+ - intermediateAlgebraic25*states[853056+instanceToComputeNo]+( - constant55*states[853056+instanceToComputeNo])/constant57+ constant57*constant56*states[675336+instanceToComputeNo]+ -3.00000*intermediateAlgebraic11*states[853056+instanceToComputeNo]+ 2.00000*intermediateAlgebraic25*states[888600+instanceToComputeNo];
          const real intermediateRate19 = ( constant55*states[853056+instanceToComputeNo])/constant57+ - constant56*constant57*states[675336+instanceToComputeNo]+( 4.00000*intermediateAlgebraic11*states[639792+instanceToComputeNo])/constant57+ - constant57*intermediateAlgebraic25*states[675336+instanceToComputeNo]+( -3.00000*intermediateAlgebraic11*states[675336+instanceToComputeNo])/constant57+ 2.00000*constant57*intermediateAlgebraic25*states[710880+instanceToComputeNo];
          const real intermediateRate25 =  3.00000*intermediateAlgebraic11*states[853056+instanceToComputeNo]+ -2.00000*intermediateAlgebraic25*states[888600+instanceToComputeNo]+( - constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ pow2(constant57)*constant56*states[710880+instanceToComputeNo]+ -2.00000*intermediateAlgebraic11*states[888600+instanceToComputeNo]+ 3.00000*intermediateAlgebraic25*states[924144+instanceToComputeNo];
          const real intermediateRate20 = ( 3.00000*intermediateAlgebraic11*states[675336+instanceToComputeNo])/constant57+ -2.00000*constant57*intermediateAlgebraic25*states[710880+instanceToComputeNo]+( constant55*states[888600+instanceToComputeNo])/pow2(constant57)+ - constant56*pow2(constant57)*states[710880+instanceToComputeNo]+( -2.00000*intermediateAlgebraic11*states[710880+instanceToComputeNo])/constant57+ 3.00000*constant57*intermediateAlgebraic25*states[746424+instanceToComputeNo];
          const real intermediateRate26 =  2.00000*intermediateAlgebraic11*states[888600+instanceToComputeNo]+ -3.00000*intermediateAlgebraic25*states[924144+instanceToComputeNo]+( - constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ constant56*pow3(constant57)*states[746424+instanceToComputeNo]+ - intermediateAlgebraic11*states[924144+instanceToComputeNo]+ 4.00000*intermediateAlgebraic25*states[959688+instanceToComputeNo];
          const real intermediateRate21 = ( constant55*states[924144+instanceToComputeNo])/pow3(constant57)+ - constant56*pow3(constant57)*states[746424+instanceToComputeNo]+( 2.00000*intermediateAlgebraic11*states[710880+instanceToComputeNo])/constant57+ -3.00000*intermediateAlgebraic25*constant57*states[746424+instanceToComputeNo]+( - intermediateAlgebraic11*states[746424+instanceToComputeNo])/constant57+ 4.00000*constant57*intermediateAlgebraic25*states[781968+instanceToComputeNo];
          const real intermediateRate27 =  intermediateAlgebraic11*states[924144+instanceToComputeNo]+ -4.00000*intermediateAlgebraic25*states[959688+instanceToComputeNo]+( - constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real intermediateRate22 = ( intermediateAlgebraic11*states[746424+instanceToComputeNo])/constant57+ -4.00000*constant57*intermediateAlgebraic25*states[781968+instanceToComputeNo]+( constant55*states[959688+instanceToComputeNo])/pow4(constant57)+ - constant56*pow4(constant57)*states[781968+instanceToComputeNo];
          const real intermediateAlgebraic31 =  states[0+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[142176+instanceToComputeNo]*exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic14 =  (( constant35*constant36)/constant6)*log(states[142176+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real intermediateAlgebraic37 =  states[142176+instanceToComputeNo]*exponential( ( - constant41*intermediateAlgebraic14)*(constant6/( constant35*constant36)));
          const real intermediateAlgebraic38 =  constant40*(pow2(intermediateAlgebraic37)/(constant42+pow2(intermediateAlgebraic37)));
          const real intermediateAlgebraic39 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(intermediateAlgebraic37)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[0+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real intermediateAlgebraic40 =  intermediateAlgebraic38*intermediateAlgebraic39;
          const real intermediateAlgebraic41 =  intermediateAlgebraic40*(intermediateAlgebraic31>0.00000 ? 1.00000 : 0.00000)*(intermediateAlgebraic31/50.0000);
          const real intermediateAlgebraic42 =  ( constant38*pow4(states[284352+instanceToComputeNo]))*states[319896+instanceToComputeNo];
          const real intermediateAlgebraic43 =  intermediateAlgebraic42*(intermediateAlgebraic31/50.0000);
          const real intermediateAlgebraic47 =  (1.00000/7.00000)*(exponential(states[248808+instanceToComputeNo]/67.3000) - 1.00000);
          const real intermediateAlgebraic48 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[0+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*intermediateAlgebraic47*exponential(- ( states[0+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real intermediateAlgebraic49 =  constant6*(constant47/( pow2(1.00000+constant44/states[142176+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real intermediateAlgebraic50 =  intermediateAlgebraic49*intermediateAlgebraic48;
          const real intermediateRate4 = (intermediateAlgebraic41+intermediateAlgebraic43+constant12+ - 2.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant10;
          const real intermediateAlgebraic45 =  ( ( constant39*pow3(states[355440+instanceToComputeNo]))*states[390984+instanceToComputeNo])*states[426528+instanceToComputeNo];
          const real intermediateAlgebraic44 =  states[0+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[248808+instanceToComputeNo]*exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic46 =  intermediateAlgebraic45*(intermediateAlgebraic44/75.0000);
          const real intermediateRate7 = (intermediateAlgebraic46+constant13+ 3.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant5)+(states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant11;
          const real intermediateAlgebraic0 =  (1000.00/1.00000)*((states[0+instanceToComputeNo] - states[35544+instanceToComputeNo])/constant2);
          const real intermediateAlgebraic27 = 156.500/(5.00000+exponential(( - constant6*intermediateAlgebraic14)/( constant35*constant36)));
          const real intermediateAlgebraic28 = 156.500 -  5.00000*intermediateAlgebraic27;
          const real intermediateAlgebraic34 =  states[0+instanceToComputeNo]*((intermediateAlgebraic27 -  intermediateAlgebraic28*exponential(( constant6*states[0+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[0+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic33 = 1.00000/(1.00000+exponential((states[0+instanceToComputeNo] - constant23)/constant26));
          const real intermediateAlgebraic35 =  constant37*pow4(intermediateAlgebraic33);
          const real intermediateAlgebraic36 =  intermediateAlgebraic35*(intermediateAlgebraic34/45.0000);
          const real intermediateAlgebraic51 = intermediateAlgebraic36+intermediateAlgebraic41+intermediateAlgebraic43+intermediateAlgebraic46+intermediateAlgebraic50+- parameters[0+instanceToComputeNo];
          const real intermediateRate0 = - ((intermediateAlgebraic51+intermediateAlgebraic0)/constant0);
          const real intermediateAlgebraic32 =  states[35544+instanceToComputeNo]*((states[106632+instanceToComputeNo] -  states[71088+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic26 =  (( constant35*constant36)/constant6)*log(states[71088+instanceToComputeNo]/states[106632+instanceToComputeNo]);
          const real intermediateAlgebraic56 =  states[71088+instanceToComputeNo]*exponential( ( - constant41*intermediateAlgebraic26)*(constant6/( constant35*constant36)));
          const real intermediateAlgebraic57 =  constant40*(pow2(intermediateAlgebraic56)/(constant42+pow2(intermediateAlgebraic56)));
          const real intermediateAlgebraic58 = 1.00000 - powReciprocal1(1.00000+( constant43*(1.00000+pow2(intermediateAlgebraic56)/constant42))/( pow2(constant46)*exponential(( 2.00000*(1.00000 - constant41)*states[35544+instanceToComputeNo]*constant6)/( constant35*constant36))));
          const real intermediateAlgebraic59 =  intermediateAlgebraic57*intermediateAlgebraic58;
          const real intermediateAlgebraic60 =  constant50*intermediateAlgebraic59*(intermediateAlgebraic32/50.0000);
          const real intermediateAlgebraic61 =  ( constant38*pow4(states[462072+instanceToComputeNo]))*states[497616+instanceToComputeNo];
          const real intermediateAlgebraic62 =  constant51*intermediateAlgebraic61*(intermediateAlgebraic32/50.0000);
          const real intermediateAlgebraic66 =  (1.00000/7.00000)*(exponential(states[213264+instanceToComputeNo]/67.3000) - 1.00000);
          const real intermediateAlgebraic67 = powReciprocal1(1.00000+ 0.120000*exponential( -0.100000*states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))+ 0.0400000*intermediateAlgebraic66*exponential(- ( states[35544+instanceToComputeNo]*(constant6/( constant35*constant36)))));
          const real intermediateAlgebraic68 =  constant6*(constant47/( pow2(1.00000+constant44/states[71088+instanceToComputeNo])*pow3(1.00000+constant45/states[177720+instanceToComputeNo])));
          const real intermediateAlgebraic69 =  constant53*intermediateAlgebraic68*intermediateAlgebraic67;
          const real intermediateRate3 =  - constant9*((intermediateAlgebraic60+intermediateAlgebraic62+constant12+ - 2.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (intermediateAlgebraic41+intermediateAlgebraic43+constant12+ -2.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real intermediateRate2 = (intermediateAlgebraic60+intermediateAlgebraic62+constant12+ - 2.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[71088+instanceToComputeNo] - states[142176+instanceToComputeNo])/constant7;
          const real intermediateAlgebraic64 =  ( ( constant39*pow3(states[533160+instanceToComputeNo]))*states[568704+instanceToComputeNo])*states[604248+instanceToComputeNo];
          const real intermediateAlgebraic63 =  states[35544+instanceToComputeNo]*((states[177720+instanceToComputeNo] -  states[213264+instanceToComputeNo]*exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( -1.00000*constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic65 =  constant52*intermediateAlgebraic64*(intermediateAlgebraic63/75.0000);
          const real intermediateRate5 =  - constant9*((intermediateAlgebraic65+constant13+ 3.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3)) - (intermediateAlgebraic46+constant13+ 3.00000*intermediateAlgebraic50)/( (1000.00/1.00000)*constant6*constant4);
          const real intermediateRate6 = (intermediateAlgebraic65+constant13+ 3.00000*intermediateAlgebraic69)/( (1000.00/1.00000)*constant6*constant3) - (states[213264+instanceToComputeNo] - states[248808+instanceToComputeNo])/constant8;
          const real intermediateAlgebraic29 = 156.500/(5.00000+exponential(( - constant6*intermediateAlgebraic26)/( constant35*constant36)));
          const real intermediateAlgebraic30 = 156.500 -  5.00000*intermediateAlgebraic29;
          const real intermediateAlgebraic53 =  states[35544+instanceToComputeNo]*((intermediateAlgebraic29 -  intermediateAlgebraic30*exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36)))/(1.00000 - exponential(( constant6*states[35544+instanceToComputeNo])/( constant35*constant36))));
          const real intermediateAlgebraic52 = 1.00000/(1.00000+exponential((states[35544+instanceToComputeNo] - constant23)/constant26));
          const real intermediateAlgebraic54 =  constant37*pow4(intermediateAlgebraic52);
          const real intermediateAlgebraic55 =  constant49*intermediateAlgebraic54*(intermediateAlgebraic53/45.0000);
          const real intermediateAlgebraic70 = intermediateAlgebraic55+intermediateAlgebraic60+intermediateAlgebraic62+intermediateAlgebraic65+intermediateAlgebraic69;
          const real intermediateRate1 = - ((intermediateAlgebraic70 - intermediateAlgebraic0/constant1)/constant0);

          // final step
          // y_n+1 = y_n + 0.5*[rhs(y_n) + rhs(y*)]
          vmValues[instanceToComputeNo] += 0.5*dt0D*(rate0 + intermediateRate0);
          states[35544+instanceToComputeNo] += 0.5*dt0D*(rate1 + intermediateRate1);
          states[71088+instanceToComputeNo] += 0.5*dt0D*(rate2 + intermediateRate2);
          states[106632+instanceToComputeNo] += 0.5*dt0D*(rate3 + intermediateRate3);
          states[142176+instanceToComputeNo] += 0.5*dt0D*(rate4 + intermediateRate4);
          states[177720+instanceToComputeNo] += 0.5*dt0D*(rate5 + intermediateRate5);
          states[213264+instanceToComputeNo] += 0.5*dt0D*(rate6 + intermediateRate6);
          states[248808+instanceToComputeNo] += 0.5*dt0D*(rate7 + intermediateRate7);
          states[284352+instanceToComputeNo] += 0.5*dt0D*(rate8 + intermediateRate8);
          states[319896+instanceToComputeNo] += 0.5*dt0D*(rate9 + intermediateRate9);
          states[355440+instanceToComputeNo] += 0.5*dt0D*(rate10 + intermediateRate10);
          states[390984+instanceToComputeNo] += 0.5*dt0D*(rate11 + intermediateRate11);
          states[426528+instanceToComputeNo] += 0.5*dt0D*(rate12 + intermediateRate12);
          states[462072+instanceToComputeNo] += 0.5*dt0D*(rate13 + intermediateRate13);
          states[497616+instanceToComputeNo] += 0.5*dt0D*(rate14 + intermediateRate14);
          states[533160+instanceToComputeNo] += 0.5*dt0D*(rate15 + intermediateRate15);
          states[568704+instanceToComputeNo] += 0.5*dt0D*(rate16 + intermediateRate16);
          states[604248+instanceToComputeNo] += 0.5*dt0D*(rate17 + intermediateRate17);
          states[639792+instanceToComputeNo] += 0.5*dt0D*(rate18 + intermediateRate18);
          states[675336+instanceToComputeNo] += 0.5*dt0D*(rate19 + intermediateRate19);
          states[710880+instanceToComputeNo] += 0.5*dt0D*(rate20 + intermediateRate20);
          states[746424+instanceToComputeNo] += 0.5*dt0D*(rate21 + intermediateRate21);
          states[781968+instanceToComputeNo] += 0.5*dt0D*(rate22 + intermediateRate22);
          states[817512+instanceToComputeNo] += 0.5*dt0D*(rate23 + intermediateRate23);
          states[853056+instanceToComputeNo] += 0.5*dt0D*(rate24 + intermediateRate24);
          states[888600+instanceToComputeNo] += 0.5*dt0D*(rate25 + intermediateRate25);
          states[924144+instanceToComputeNo] += 0.5*dt0D*(rate26 + intermediateRate26);
          states[959688+instanceToComputeNo] += 0.5*dt0D*(rate27 + intermediateRate27);
          states[995232+instanceToComputeNo] += 0.5*dt0D*(rate28 + intermediateRate28);
          states[1030776+instanceToComputeNo] += 0.5*dt0D*(rate29 + intermediateRate29);
          states[1066320+instanceToComputeNo] += 0.5*dt0D*(rate30 + intermediateRate30);
          states[1101864+instanceToComputeNo] += 0.5*dt0D*(rate31 + intermediateRate31);
          states[1137408+instanceToComputeNo] += 0.5*dt0D*(rate32 + intermediateRate32);
          states[1172952+instanceToComputeNo] += 0.5*dt0D*(rate33 + intermediateRate33);
          states[1208496+instanceToComputeNo] += 0.5*dt0D*(rate34 + intermediateRate34);
          states[1244040+instanceToComputeNo] += 0.5*dt0D*(rate35 + intermediateRate35);
          states[1279584+instanceToComputeNo] += 0.5*dt0D*(rate36 + intermediateRate36);
          states[1315128+instanceToComputeNo] += 0.5*dt0D*(rate37 + intermediateRate37);
          states[1350672+instanceToComputeNo] += 0.5*dt0D*(rate38 + intermediateRate38);
          states[1386216+instanceToComputeNo] += 0.5*dt0D*(rate39 + intermediateRate39);
          states[1421760+instanceToComputeNo] += 0.5*dt0D*(rate40 + intermediateRate40);
          states[1457304+instanceToComputeNo] += 0.5*dt0D*(rate41 + intermediateRate41);
          states[1492848+instanceToComputeNo] += 0.5*dt0D*(rate42 + intermediateRate42);
          states[1528392+instanceToComputeNo] += 0.5*dt0D*(rate43 + intermediateRate43);
          states[1563936+instanceToComputeNo] += 0.5*dt0D*(rate44 + intermediateRate44);
          states[1599480+instanceToComputeNo] += 0.5*dt0D*(rate45 + intermediateRate45);
          states[1635024+instanceToComputeNo] += 0.5*dt0D*(rate46 + intermediateRate46);
          states[1670568+instanceToComputeNo] += 0.5*dt0D*(rate47 + intermediateRate47);
          states[1706112+instanceToComputeNo] += 0.5*dt0D*(rate48 + intermediateRate48);
          states[1741656+instanceToComputeNo] += 0.5*dt0D*(rate49 + intermediateRate49);
          states[1777200+instanceToComputeNo] += 0.5*dt0D*(rate50 + intermediateRate50);
          states[1812744+instanceToComputeNo] += 0.5*dt0D*(rate51 + intermediateRate51);
          states[1848288+instanceToComputeNo] += 0.5*dt0D*(rate52 + intermediateRate52);
          states[1883832+instanceToComputeNo] += 0.5*dt0D*(rate53 + intermediateRate53);
          states[1919376+instanceToComputeNo] += 0.5*dt0D*(rate54 + intermediateRate54);
          states[1954920+instanceToComputeNo] += 0.5*dt0D*(rate55 + intermediateRate55);
          states[1990464+instanceToComputeNo] += 0.5*dt0D*(rate56 + intermediateRate56);

          if (stimulateCurrentPoint)
          {
            vmValues[instanceToComputeNo] = valueForStimulatedPoint;
          }  
  
          // store algebraics for transfer
          if (storeAlgebraicsForTransfer)
          {
            
            for (int i = 0; i < nStatesForTransferIndices; i++)
            {
              const int stateIndex = statesForTransferIndices[i];

              switch (stateIndex)
              {
                case 0:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = vmValues[instanceToComputeNo];
                  break;
                case 1:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[35544+instanceToComputeNo];
                  break;
                case 2:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[71088+instanceToComputeNo];
                  break;
                case 3:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[106632+instanceToComputeNo];
                  break;
                case 4:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[142176+instanceToComputeNo];
                  break;
                case 5:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[177720+instanceToComputeNo];
                  break;
                case 6:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[213264+instanceToComputeNo];
                  break;
                case 7:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[248808+instanceToComputeNo];
                  break;
                case 8:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[284352+instanceToComputeNo];
                  break;
                case 9:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[319896+instanceToComputeNo];
                  break;
                case 10:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[355440+instanceToComputeNo];
                  break;
                case 11:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[390984+instanceToComputeNo];
                  break;
                case 12:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[426528+instanceToComputeNo];
                  break;
                case 13:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[462072+instanceToComputeNo];
                  break;
                case 14:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[497616+instanceToComputeNo];
                  break;
                case 15:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[533160+instanceToComputeNo];
                  break;
                case 16:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[568704+instanceToComputeNo];
                  break;
                case 17:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[604248+instanceToComputeNo];
                  break;
                case 18:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[639792+instanceToComputeNo];
                  break;
                case 19:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[675336+instanceToComputeNo];
                  break;
                case 20:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[710880+instanceToComputeNo];
                  break;
                case 21:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[746424+instanceToComputeNo];
                  break;
                case 22:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[781968+instanceToComputeNo];
                  break;
                case 23:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[817512+instanceToComputeNo];
                  break;
                case 24:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[853056+instanceToComputeNo];
                  break;
                case 25:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[888600+instanceToComputeNo];
                  break;
                case 26:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[924144+instanceToComputeNo];
                  break;
                case 27:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[959688+instanceToComputeNo];
                  break;
                case 28:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[995232+instanceToComputeNo];
                  break;
                case 29:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1030776+instanceToComputeNo];
                  break;
                case 30:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1066320+instanceToComputeNo];
                  break;
                case 31:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1101864+instanceToComputeNo];
                  break;
                case 32:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1137408+instanceToComputeNo];
                  break;
                case 33:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1172952+instanceToComputeNo];
                  break;
                case 34:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1208496+instanceToComputeNo];
                  break;
                case 35:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1244040+instanceToComputeNo];
                  break;
                case 36:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1279584+instanceToComputeNo];
                  break;
                case 37:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1315128+instanceToComputeNo];
                  break;
                case 38:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1350672+instanceToComputeNo];
                  break;
                case 39:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1386216+instanceToComputeNo];
                  break;
                case 40:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1421760+instanceToComputeNo];
                  break;
                case 41:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1457304+instanceToComputeNo];
                  break;
                case 42:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1492848+instanceToComputeNo];
                  break;
                case 43:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1528392+instanceToComputeNo];
                  break;
                case 44:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1563936+instanceToComputeNo];
                  break;
                case 45:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1599480+instanceToComputeNo];
                  break;
                case 46:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1635024+instanceToComputeNo];
                  break;
                case 47:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1670568+instanceToComputeNo];
                  break;
                case 48:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1706112+instanceToComputeNo];
                  break;
                case 49:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1741656+instanceToComputeNo];
                  break;
                case 50:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1777200+instanceToComputeNo];
                  break;
                case 51:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1812744+instanceToComputeNo];
                  break;
                case 52:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1848288+instanceToComputeNo];
                  break;
                case 53:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1883832+instanceToComputeNo];
                  break;
                case 54:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1919376+instanceToComputeNo];
                  break;
                case 55:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1954920+instanceToComputeNo];
                  break;
                case 56:
                  statesForTransfer[i*nInstancesToCompute + instanceToComputeNo] = states[1990464+instanceToComputeNo];
                  break;

              }
            }              
          }


        }  // loop over 0D timesteps
      }  // loop over instances
    }  // loop over fibers
  } // loop over splitting timesteps

  } // end pragma omp target

  // map back from GPU to host
  //#pragma omp target update from(statesForTransfer[:nStatesForTransfer])

}
