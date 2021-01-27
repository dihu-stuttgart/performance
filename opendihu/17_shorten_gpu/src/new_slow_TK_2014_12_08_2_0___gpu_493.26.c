#include <math.h>
#include <omp.h>
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


/* This function was created by opendihu at 2021/1/19 20:25:22.
 * It is designed for 493 instances of the CellML problem.
  * The "optimizationType" is "gpu". (Other options are "vc", "openmp" and "simd".) */
void computeCellMLRightHandSide(void *context, double t, double *states, double *rates, double *algebraics, double *parameters)
{
  double VOI = t;   /* current simulation time */

  /* define constants */
  double CONSTANTS[112];
  CONSTANTS[0] = 0.58;
  CONSTANTS[1] = 2.79;
  CONSTANTS[2] = 150;
  CONSTANTS[3] = 0.000001;
  CONSTANTS[4] = 0.0025;
  CONSTANTS[5] = 0.0005;
  CONSTANTS[6] = 96485;
  CONSTANTS[7] = 559;
  CONSTANTS[8] = 559;
  CONSTANTS[9] = 0.00174;
  CONSTANTS[10] = 40229.885;
  CONSTANTS[11] = 40229.885;
  CONSTANTS[12] = 0.34;
  CONSTANTS[13] = -0.43;
  CONSTANTS[14] = 0.0081;
  CONSTANTS[15] = 0.288;
  CONSTANTS[16] = 0.0131;
  CONSTANTS[17] = 4.38;
  CONSTANTS[18] = 1.38;
  CONSTANTS[19] = 0.067;
  CONSTANTS[20] = -46;
  CONSTANTS[21] = -40;
  CONSTANTS[22] = -45;
  CONSTANTS[23] = 70;
  CONSTANTS[24] = -68;
  CONSTANTS[25] = -40;
  CONSTANTS[26] = 150;
  CONSTANTS[27] = 7.1;
  CONSTANTS[28] = 7.5;
  CONSTANTS[29] = 14.7;
  CONSTANTS[30] = 9;
  CONSTANTS[31] = 10;
  CONSTANTS[32] = 7;
  CONSTANTS[33] = 18;
  CONSTANTS[34] = 40;
  CONSTANTS[35] = 8314.41;
  CONSTANTS[36] = 293;
  CONSTANTS[37] = 3.275;
  CONSTANTS[38] = 10.8;
  CONSTANTS[39] = 134;
  CONSTANTS[40] = 1.85;
  CONSTANTS[41] = 0.4;
  CONSTANTS[42] = 950;
  CONSTANTS[43] = 1;
  CONSTANTS[44] = 1;
  CONSTANTS[45] = 13;
  CONSTANTS[46] = 10;
  CONSTANTS[47] = 0.0001656;
  CONSTANTS[48] = 70;
  CONSTANTS[49] = 0.1;
  CONSTANTS[50] = 1.0;
  CONSTANTS[51] = 0.45;
  CONSTANTS[52] = 0.1;
  CONSTANTS[53] = 0.1;
  CONSTANTS[54] = 0.0;
  CONSTANTS[55] = 0.002;
  CONSTANTS[56] = 1000;
  CONSTANTS[57] = 0.2;
  CONSTANTS[58] = 0.2;
  CONSTANTS[59] = 4.5;
  CONSTANTS[60] = -20;
  CONSTANTS[61] = 2.4375;
  CONSTANTS[62] = 1;
  CONSTANTS[63] = 0.00004;
  CONSTANTS[64] = 0.75;
  CONSTANTS[65] = 0.75;
  CONSTANTS[66] = 1.0;
  CONSTANTS[67] = 1.0;
  CONSTANTS[68] = 0.5;
  CONSTANTS[69] = 0.0885;
  CONSTANTS[70] = 0.115;
  CONSTANTS[71] = 140;
  CONSTANTS[72] = 0;
  CONSTANTS[73] = 0;
  CONSTANTS[74] = 1500;
  CONSTANTS[75] = 0;
  CONSTANTS[76] = 0;
  CONSTANTS[77] = 0.000004;
  CONSTANTS[78] = 0.005;
  CONSTANTS[79] = 31000;
  CONSTANTS[80] = 0.15;
  CONSTANTS[81] = 30;
  CONSTANTS[82] = 0.0015;
  CONSTANTS[83] = 0.15;
  CONSTANTS[84] = 0.375;
  CONSTANTS[85] = 1.5;
  CONSTANTS[86] = 0;
  CONSTANTS[87] = 0.15;
  CONSTANTS[88] = 0.15;
  CONSTANTS[89] = 0.05;
  CONSTANTS[90] = 0.5;
  CONSTANTS[91] = 5;
  CONSTANTS[92] = 0.08;
  CONSTANTS[93] = 0.06;
  CONSTANTS[94] = 0.04;
  CONSTANTS[95] = 0.00000394;
  CONSTANTS[96] = 0.00000362;
  CONSTANTS[97] = 1;
  CONSTANTS[98] = 0.0001;
  CONSTANTS[99] = 6;
  CONSTANTS[100] = 0.05;
  CONSTANTS[101] = 0.0;
  CONSTANTS[102] = 0.05;
  CONSTANTS[103] = 0.000107;
  CONSTANTS[104] = 0.0021;
  CONSTANTS[105] = 60;
  CONSTANTS[106] =  0.950000*CONSTANTS[66]* 3.14159265358979*pow(CONSTANTS[68], 2.00000);
  CONSTANTS[107] =  0.0500000*CONSTANTS[66]* 3.14159265358979*pow(CONSTANTS[68], 2.00000);
  CONSTANTS[108] =  0.0100000*CONSTANTS[106];
  CONSTANTS[109] =  0.990000*CONSTANTS[106];
  CONSTANTS[110] =  0.0100000*CONSTANTS[107];
  CONSTANTS[111] =  0.990000*CONSTANTS[107];

  #pragma omp target parallel for map(to:states,t,parameters) map(from:rates,algebraics)
  for (int i = 0; i < 493; i++)
  {
    rates[14297+i] = (((( ( CONSTANTS[105]*(states[8874+i]+states[9367+i]+states[9860+i]+states[10353+i]+states[10846+i]))*((states[14790+i] - states[14297+i])/CONSTANTS[108]) -  CONSTANTS[61]*((states[14297+i]/(states[14297+i]+CONSTANTS[62]))/CONSTANTS[108]))+ CONSTANTS[63]*((states[14790+i] - states[14297+i])/CONSTANTS[108]))+ - CONSTANTS[64]*((states[14297+i] - states[15283+i])/CONSTANTS[108]))+- ( ( CONSTANTS[72]*states[14297+i])*((CONSTANTS[74]+- states[16762+i])+- states[17748+i])+ - CONSTANTS[73]*states[16762+i]))+- ( ( CONSTANTS[80]*states[14297+i])*states[21692+i]+ - CONSTANTS[81]*states[19720+i]);
    rates[14790+i] = ((( - ( CONSTANTS[105]*(states[8874+i]+states[9367+i]+states[9860+i]+states[10353+i]+states[10846+i]))*((states[14790+i] - states[14297+i])/CONSTANTS[110])+ CONSTANTS[61]*((states[14297+i]/(states[14297+i]+CONSTANTS[62]))/CONSTANTS[110]))+ - CONSTANTS[63]*((states[14790+i] - states[14297+i])/CONSTANTS[110]))+ - CONSTANTS[65]*((states[14790+i] - states[15776+i])/CONSTANTS[110]))+- ( ( CONSTANTS[77]*states[14790+i])*(CONSTANTS[79] - states[18734+i])+ - CONSTANTS[78]*states[18734+i]);
    rates[15776+i] = ((( CONSTANTS[61]*((states[15283+i]/(states[15283+i]+CONSTANTS[62]))/CONSTANTS[111])+ - CONSTANTS[63]*((states[15776+i]+- states[15283+i])/CONSTANTS[111]))+ CONSTANTS[65]*((states[14790+i]+- states[15776+i])/CONSTANTS[111]))+- ( ( CONSTANTS[77]*states[15776+i])*(CONSTANTS[79]+- states[19227+i])+ - CONSTANTS[78]*states[19227+i])) -  (1000.00/1.00000)*( CONSTANTS[97]*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99])*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[27115+i]*states[15776+i] -  CONSTANTS[98]*states[27608+i]*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i])*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i]>0.00000 ? 1.00000 : 0.00000));
    rates[16762+i] =  ( CONSTANTS[72]*states[14297+i])*((CONSTANTS[74]+- states[16762+i])+- states[17748+i])+ - CONSTANTS[73]*states[16762+i];
    rates[17255+i] =  ( CONSTANTS[72]*states[15283+i])*((CONSTANTS[74]+- states[17255+i])+- states[18241+i])+ - CONSTANTS[73]*states[17255+i];
    rates[17748+i] =  ( CONSTANTS[75]*(CONSTANTS[74]+- states[16762+i]+- states[17748+i]))*states[22678+i]+ - CONSTANTS[76]*states[17748+i];
    rates[18241+i] =  ( CONSTANTS[75]*(CONSTANTS[74]+- states[17255+i]+- states[18241+i]))*states[23171+i]+ - CONSTANTS[76]*states[18241+i];
    rates[18734+i] =  ( CONSTANTS[77]*states[14790+i])*(CONSTANTS[79]+- states[18734+i])+ - CONSTANTS[78]*states[18734+i];
    rates[19227+i] =  ( CONSTANTS[77]*states[15776+i])*(CONSTANTS[79]+- states[19227+i])+ - CONSTANTS[78]*states[19227+i];
    rates[19720+i] = ( ( CONSTANTS[80]*states[14297+i])*states[21692+i]+ - CONSTANTS[81]*states[19720+i])+ - CONSTANTS[84]*((states[19720+i]+- states[20213+i])/CONSTANTS[108]);
    rates[20213+i] = ( ( CONSTANTS[80]*states[15283+i])*states[22185+i]+ - CONSTANTS[81]*states[20213+i])+ CONSTANTS[84]*((states[19720+i]+- states[20213+i])/CONSTANTS[109]);
    rates[20706+i] = ( ( CONSTANTS[82]*states[22678+i])*states[21692+i]+ - CONSTANTS[83]*states[20706+i])+ - CONSTANTS[84]*((states[20706+i]+- states[21199+i])/CONSTANTS[108]);
    rates[21199+i] = ( ( CONSTANTS[82]*states[23171+i])*states[22185+i]+ - CONSTANTS[83]*states[21199+i])+ CONSTANTS[84]*((states[20706+i]+- states[21199+i])/CONSTANTS[109]);
    rates[21692+i] = (- ( ( CONSTANTS[80]*states[14297+i])*states[21692+i]+ - CONSTANTS[81]*states[19720+i])+- ( ( CONSTANTS[82]*states[22678+i])*states[21692+i]+ - CONSTANTS[83]*states[20706+i]))+ - CONSTANTS[84]*((states[21692+i]+- states[22185+i])/CONSTANTS[108]);
    rates[22185+i] = (- ( ( CONSTANTS[80]*states[15283+i])*states[22185+i]+ - CONSTANTS[81]*states[20213+i])+- ( ( CONSTANTS[82]*states[23171+i])*states[22185+i]+ - CONSTANTS[83]*states[21199+i]))+ CONSTANTS[84]*((states[21692+i]+- states[22185+i])/CONSTANTS[109]);
    rates[22678+i] = (- ( ( CONSTANTS[75]*(CONSTANTS[74]+- states[16762+i]+- states[17748+i]))*states[22678+i]+ - CONSTANTS[76]*states[17748+i])+- ( ( CONSTANTS[82]*states[22678+i])*states[21692+i]+ - CONSTANTS[83]*states[20706+i]))+ - CONSTANTS[85]*((states[22678+i]+- states[23171+i])/CONSTANTS[108]);
    rates[23171+i] = (- ( ( CONSTANTS[75]*(CONSTANTS[74]+- states[17255+i]+- states[18241+i]))*states[23171+i]+ - CONSTANTS[76]*states[18241+i])+- ( ( CONSTANTS[82]*states[23171+i])*states[22185+i]+ - CONSTANTS[83]*states[21199+i]))+ CONSTANTS[85]*((states[22678+i]+- states[23171+i])/CONSTANTS[109]);
    rates[23664+i] = (( ( CONSTANTS[69]*states[15283+i])*states[16269+i]+ - CONSTANTS[70]*states[23664+i])+ - CONSTANTS[88]*states[23664+i])+ CONSTANTS[89]*states[25143+i];
    rates[24650+i] = (((( CONSTANTS[69]*states[15283+i]*states[24157+i]+ - CONSTANTS[70]*states[24650+i])+ CONSTANTS[86]*states[16269+i])+ - CONSTANTS[87]*states[24650+i])+ ( - CONSTANTS[69]*states[15283+i])*states[24650+i])+ CONSTANTS[70]*states[25143+i];
    rates[25143+i] = ((((( CONSTANTS[69]*states[15283+i]*states[24650+i]+ - CONSTANTS[70]*states[25143+i])+ CONSTANTS[88]*states[23664+i])+ - CONSTANTS[89]*states[25143+i])+ - CONSTANTS[90]*states[25143+i])+ CONSTANTS[91]*states[25636+i])+ CONSTANTS[94]*states[26129+i];
    rates[25636+i] = (( CONSTANTS[90]*states[25143+i]+ - CONSTANTS[91]*states[25636+i])+ CONSTANTS[93]*states[26129+i])+ - CONSTANTS[92]*states[25636+i];
    rates[26129+i] = ( - CONSTANTS[93]*states[26129+i]+ CONSTANTS[92]*states[25636+i])+ - CONSTANTS[94]*states[26129+i];
    rates[26622+i] =  (0.00100000/1.00000)*( CONSTANTS[92]*states[25636+i] -  CONSTANTS[93]*states[26129+i])+ -1.00000*CONSTANTS[95]*states[26622+i]+ -1.00000*CONSTANTS[96]*((states[26622+i] - states[27115+i])/CONSTANTS[109]);
    rates[27115+i] =  CONSTANTS[96]*((states[26622+i] - states[27115+i])/CONSTANTS[111]) -  1.00000*( CONSTANTS[97]*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99])*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[27115+i]*states[15776+i] -  CONSTANTS[98]*states[27608+i]*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i])*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i]>0.00000 ? 1.00000 : 0.00000));
    rates[27608+i] =  1.00000*( CONSTANTS[97]*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99])*( states[27115+i]*(0.00100000/1.00000)*states[15776+i] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[27115+i]*states[15776+i] -  CONSTANTS[98]*states[27608+i]*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i])*(CONSTANTS[99] -  states[27115+i]*(0.00100000/1.00000)*states[15776+i]>0.00000 ? 1.00000 : 0.00000));
    algebraics[6409+i] = (CONSTANTS[71]+- states[16269+i]+- states[23664+i]+- states[24157+i]+- states[24650+i]+- states[25143+i]+- states[25636+i]+- states[26129+i]>0.00000 ? CONSTANTS[71]+- states[16269+i]+- states[23664+i]+- states[24157+i]+- states[24650+i]+- states[25143+i]+- states[25636+i]+- states[26129+i] : 0.00000);
    rates[15283+i] = (((( - CONSTANTS[61]*((states[15283+i]/(states[15283+i]+CONSTANTS[62]))/CONSTANTS[109])+ CONSTANTS[63]*((states[15776+i]+- states[15283+i])/CONSTANTS[109]))+ CONSTANTS[64]*((states[14297+i] - states[15283+i])/CONSTANTS[109]))+- ((((((( CONSTANTS[69]*states[15283+i]*algebraics[6409+i]+ - CONSTANTS[70]*states[16269+i])+ CONSTANTS[69]*states[15283+i]*states[16269+i])+ - CONSTANTS[70]*states[23664+i])+ CONSTANTS[69]*states[15283+i]*states[24157+i])+ - CONSTANTS[70]*states[24650+i])+ CONSTANTS[69]*states[15283+i]*states[24650+i])+ - CONSTANTS[70]*states[25143+i]))+- ( ( CONSTANTS[72]*states[15283+i])*(CONSTANTS[74]+- states[17255+i]+- states[18241+i])+ - CONSTANTS[73]*states[17255+i]))+- ( ( CONSTANTS[80]*states[15283+i])*states[22185+i]+ - CONSTANTS[81]*states[20213+i]);
    rates[16269+i] = (((( ( CONSTANTS[69]*states[15283+i])*algebraics[6409+i]+ - CONSTANTS[70]*states[16269+i])+ ( - CONSTANTS[69]*states[15283+i])*states[16269+i])+ CONSTANTS[70]*states[23664+i])+ - CONSTANTS[86]*states[16269+i])+ CONSTANTS[87]*states[24650+i];
    rates[24157+i] = (( ( - CONSTANTS[69]*states[15283+i])*states[24157+i]+ CONSTANTS[70]*states[24650+i])+ CONSTANTS[86]*algebraics[6409+i])+ - CONSTANTS[87]*states[24157+i];
    algebraics[5916+i] =  ((( (states[25636+i]/CONSTANTS[71])*CONSTANTS[101]+ (states[26129+i]/CONSTANTS[71])*CONSTANTS[102]) - CONSTANTS[103])/CONSTANTS[104])*(parameters[493+i]>=0.635000&&parameters[493+i]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[493+i] - 0.635000) : parameters[493+i]>0.850000&&parameters[493+i]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[493+i] - 0.850000) : parameters[493+i]>1.17000&&parameters[493+i]<=1.25500 ? 1.00000 : parameters[493+i]>1.25500&&parameters[493+i]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[493+i] - 1.25500) : 0.00000);
    rates[13804+i] = algebraics[5916+i];
    algebraics[493+i] =  CONSTANTS[16]*((states[0+i] - CONSTANTS[21])/(1.00000 - exp(- ((states[0+i] - CONSTANTS[21])/CONSTANTS[32]))));
    algebraics[7395+i] =  CONSTANTS[19]*exp(- ((states[0+i] - CONSTANTS[21])/CONSTANTS[34]));
    rates[3944+i] =  algebraics[493+i]*(1.00000 - states[3944+i]) -  algebraics[7395+i]*states[3944+i];
    algebraics[986+i] = 1.00000/(1.00000+exp((states[0+i] - CONSTANTS[25])/CONSTANTS[28]));
    algebraics[7888+i] =  1000.00*exp(- ((states[0+i]+40.0000)/25.7500));
    rates[4437+i] = (algebraics[986+i] - states[4437+i])/algebraics[7888+i];
    algebraics[1972+i] =  CONSTANTS[15]*((states[0+i] - CONSTANTS[20])/(1.00000 - exp(- ((states[0+i] - CONSTANTS[20])/CONSTANTS[31]))));
    algebraics[8874+i] =  CONSTANTS[18]*exp(- ((states[0+i] - CONSTANTS[20])/CONSTANTS[33]));
    rates[4930+i] =  algebraics[1972+i]*(1.00000 - states[4930+i]) -  algebraics[8874+i]*states[4930+i];
    algebraics[1479+i] =  CONSTANTS[14]*exp(- ((states[0+i] - CONSTANTS[22])/CONSTANTS[29]));
    algebraics[8381+i] = CONSTANTS[17]/(1.00000+exp(- ((states[0+i] - CONSTANTS[22])/CONSTANTS[30])));
    rates[5423+i] =  algebraics[1479+i]*(1.00000 - states[5423+i]) -  algebraics[8381+i]*states[5423+i];
    algebraics[2465+i] = 1.00000/(1.00000+exp((states[0+i] - CONSTANTS[24])/CONSTANTS[27]));
    algebraics[9367+i] = 8571.00/(0.200000+ 5.65000*pow((states[0+i]+CONSTANTS[48])/100.000, 2.00000));
    rates[5916+i] = (algebraics[2465+i] - states[5916+i])/algebraics[9367+i];
    algebraics[2958+i] =  CONSTANTS[16]*((states[493+i] - CONSTANTS[21])/(1.00000 - exp(- ((states[493+i] - CONSTANTS[21])/CONSTANTS[32]))));
    algebraics[9860+i] =  CONSTANTS[19]*exp(- ((states[493+i] - CONSTANTS[21])/CONSTANTS[34]));
    rates[6409+i] =  algebraics[2958+i]*(1.00000 - states[6409+i]) -  algebraics[9860+i]*states[6409+i];
    algebraics[3451+i] = 1.00000/(1.00000+exp((states[493+i] - CONSTANTS[25])/CONSTANTS[28]));
    algebraics[10353+i] =  1.00000*exp(- ((states[493+i]+40.0000)/25.7500));
    rates[6902+i] = (algebraics[3451+i] - states[6902+i])/algebraics[10353+i];
    algebraics[4437+i] =  CONSTANTS[15]*((states[493+i] - CONSTANTS[20])/(1.00000 - exp(- ((states[493+i] - CONSTANTS[20])/CONSTANTS[31]))));
    algebraics[11339+i] =  CONSTANTS[18]*exp(- ((states[493+i] - CONSTANTS[20])/CONSTANTS[33]));
    rates[7395+i] =  algebraics[4437+i]*(1.00000 - states[7395+i]) -  algebraics[11339+i]*states[7395+i];
    algebraics[3944+i] =  CONSTANTS[14]*exp(- ((states[493+i] - CONSTANTS[22])/CONSTANTS[29]));
    algebraics[10846+i] = CONSTANTS[17]/(1.00000+exp(- ((states[493+i] - CONSTANTS[22])/CONSTANTS[30])));
    rates[7888+i] =  algebraics[3944+i]*(1.00000 - states[7888+i]) -  algebraics[10846+i]*states[7888+i];
    algebraics[4930+i] = 1.00000/(1.00000+exp((states[493+i] - CONSTANTS[24])/CONSTANTS[27]));
    algebraics[11832+i] = 8571.00/(0.200000+ 5.65000*pow((states[493+i]+CONSTANTS[48])/100.000, 2.00000));
    rates[8381+i] = (algebraics[4930+i] - states[8381+i])/algebraics[11832+i];
    algebraics[5423+i] =  0.500000*CONSTANTS[58]*exp((states[493+i] - CONSTANTS[60])/( 8.00000*CONSTANTS[59]));
    algebraics[12325+i] =  0.500000*CONSTANTS[58]*exp((CONSTANTS[60] - states[493+i])/( 8.00000*CONSTANTS[59]));
    rates[11339+i] =  - CONSTANTS[55]*states[11339+i]+ CONSTANTS[56]*states[8874+i]+ -4.00000*algebraics[5423+i]*states[11339+i]+ algebraics[12325+i]*states[11832+i];
    rates[8874+i] =  CONSTANTS[55]*states[11339+i]+ - CONSTANTS[56]*states[8874+i]+( -4.00000*algebraics[5423+i]*states[8874+i])/CONSTANTS[57]+ CONSTANTS[57]*algebraics[12325+i]*states[9367+i];
    rates[11832+i] =  4.00000*algebraics[5423+i]*states[11339+i]+ - algebraics[12325+i]*states[11832+i]+( - CONSTANTS[55]*states[11832+i])/CONSTANTS[57]+ CONSTANTS[57]*CONSTANTS[56]*states[9367+i]+ -3.00000*algebraics[5423+i]*states[11832+i]+ 2.00000*algebraics[12325+i]*states[12325+i];
    rates[9367+i] = ( CONSTANTS[55]*states[11832+i])/CONSTANTS[57]+ - CONSTANTS[56]*CONSTANTS[57]*states[9367+i]+( 4.00000*algebraics[5423+i]*states[8874+i])/CONSTANTS[57]+ - CONSTANTS[57]*algebraics[12325+i]*states[9367+i]+( -3.00000*algebraics[5423+i]*states[9367+i])/CONSTANTS[57]+ 2.00000*CONSTANTS[57]*algebraics[12325+i]*states[9860+i];
    rates[12325+i] =  3.00000*algebraics[5423+i]*states[11832+i]+ -2.00000*algebraics[12325+i]*states[12325+i]+( - CONSTANTS[55]*states[12325+i])/pow(CONSTANTS[57], 2.00000)+ pow(CONSTANTS[57], 2.00000)*CONSTANTS[56]*states[9860+i]+ -2.00000*algebraics[5423+i]*states[12325+i]+ 3.00000*algebraics[12325+i]*states[12818+i];
    rates[9860+i] = ( 3.00000*algebraics[5423+i]*states[9367+i])/CONSTANTS[57]+ -2.00000*CONSTANTS[57]*algebraics[12325+i]*states[9860+i]+( CONSTANTS[55]*states[12325+i])/pow(CONSTANTS[57], 2.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 2.00000)*states[9860+i]+( -2.00000*algebraics[5423+i]*states[9860+i])/CONSTANTS[57]+ 3.00000*CONSTANTS[57]*algebraics[12325+i]*states[10353+i];
    rates[12818+i] =  2.00000*algebraics[5423+i]*states[12325+i]+ -3.00000*algebraics[12325+i]*states[12818+i]+( - CONSTANTS[55]*states[12818+i])/pow(CONSTANTS[57], 3.00000)+ CONSTANTS[56]*pow(CONSTANTS[57], 3.00000)*states[10353+i]+ - algebraics[5423+i]*states[12818+i]+ 4.00000*algebraics[12325+i]*states[13311+i];
    rates[10353+i] = ( CONSTANTS[55]*states[12818+i])/pow(CONSTANTS[57], 3.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 3.00000)*states[10353+i]+( 2.00000*algebraics[5423+i]*states[9860+i])/CONSTANTS[57]+ -3.00000*algebraics[12325+i]*CONSTANTS[57]*states[10353+i]+( - algebraics[5423+i]*states[10353+i])/CONSTANTS[57]+ 4.00000*CONSTANTS[57]*algebraics[12325+i]*states[10846+i];
    rates[13311+i] =  algebraics[5423+i]*states[12818+i]+ -4.00000*algebraics[12325+i]*states[13311+i]+( - CONSTANTS[55]*states[13311+i])/pow(CONSTANTS[57], 4.00000)+ CONSTANTS[56]*pow(CONSTANTS[57], 4.00000)*states[10846+i];
    rates[10846+i] = ( algebraics[5423+i]*states[10353+i])/CONSTANTS[57]+ -4.00000*CONSTANTS[57]*algebraics[12325+i]*states[10846+i]+( CONSTANTS[55]*states[13311+i])/pow(CONSTANTS[57], 4.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 4.00000)*states[10846+i];
    algebraics[15283+i] =  states[0+i]*((states[1479+i] -  states[1972+i]*exp(( -1.00000*CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[6902+i] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(states[1972+i]/states[1479+i]);
    algebraics[18241+i] =  states[1972+i]*exp( ( - CONSTANTS[41]*algebraics[6902+i])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));
    algebraics[18734+i] =  CONSTANTS[40]*(pow(algebraics[18241+i], 2.00000)/(CONSTANTS[42]+pow(algebraics[18241+i], 2.00000)));
    algebraics[19227+i] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(algebraics[18241+i], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*states[0+i]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);
    algebraics[19720+i] =  algebraics[18734+i]*algebraics[19227+i];
    algebraics[20213+i] =  algebraics[19720+i]*(algebraics[15283+i]>0.00000 ? 1.00000 : 0.00000)*(algebraics[15283+i]/50.0000);
    algebraics[20706+i] =  ( CONSTANTS[38]*pow(states[3944+i], 4.00000))*states[4437+i];
    algebraics[21199+i] =  algebraics[20706+i]*(algebraics[15283+i]/50.0000);
    algebraics[23171+i] =  (1.00000/7.00000)*(exp(states[3451+i]/67.3000) - 1.00000);
    algebraics[23664+i] = pow(1.00000+ 0.120000*exp( -0.100000*states[0+i]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*algebraics[23171+i]*exp(- ( states[0+i]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);
    algebraics[24157+i] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/states[1972+i], 2.00000)*pow(1.00000+CONSTANTS[45]/states[2465+i], 3.00000)));
    algebraics[24650+i] =  algebraics[24157+i]*algebraics[23664+i];
    rates[1972+i] = (algebraics[20213+i]+algebraics[21199+i]+CONSTANTS[12]+ - 2.00000*algebraics[24650+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(states[986+i] - states[1972+i])/CONSTANTS[10];
    algebraics[22185+i] =  ( ( CONSTANTS[39]*pow(states[4930+i], 3.00000))*states[5423+i])*states[5916+i];
    algebraics[21692+i] =  states[0+i]*((states[2465+i] -  states[3451+i]*exp(( -1.00000*CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[22678+i] =  algebraics[22185+i]*(algebraics[21692+i]/75.0000);
    rates[3451+i] = (algebraics[22678+i]+CONSTANTS[13]+ 3.00000*algebraics[24650+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(states[2958+i] - states[3451+i])/CONSTANTS[11];
    algebraics[0+i] =  (1000.00/1.00000)*((states[0+i] - states[493+i])/CONSTANTS[2]);
    algebraics[13311+i] = 156.500/(5.00000+exp(( - CONSTANTS[6]*algebraics[6902+i])/( CONSTANTS[35]*CONSTANTS[36])));
    algebraics[13804+i] = 156.500 -  5.00000*algebraics[13311+i];
    algebraics[16762+i] =  states[0+i]*((algebraics[13311+i] -  algebraics[13804+i]*exp(( CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*states[0+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[16269+i] = 1.00000/(1.00000+exp((states[0+i] - CONSTANTS[23])/CONSTANTS[26]));
    algebraics[17255+i] =  CONSTANTS[37]*pow(algebraics[16269+i], 4.00000);
    algebraics[17748+i] =  algebraics[17255+i]*(algebraics[16762+i]/45.0000);
    algebraics[25143+i] = algebraics[17748+i]+algebraics[20213+i]+algebraics[21199+i]+algebraics[22678+i]+algebraics[24650+i]+- parameters[0+i];
    rates[0+i] = - ((algebraics[25143+i]+algebraics[0+i])/CONSTANTS[0]);
    algebraics[15776+i] =  states[493+i]*((states[1479+i] -  states[986+i]*exp(( -1.00000*CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[12818+i] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(states[986+i]/states[1479+i]);
    algebraics[27608+i] =  states[986+i]*exp( ( - CONSTANTS[41]*algebraics[12818+i])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));
    algebraics[28101+i] =  CONSTANTS[40]*(pow(algebraics[27608+i], 2.00000)/(CONSTANTS[42]+pow(algebraics[27608+i], 2.00000)));
    algebraics[28594+i] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(algebraics[27608+i], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*states[493+i]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);
    algebraics[29087+i] =  algebraics[28101+i]*algebraics[28594+i];
    algebraics[29580+i] =  CONSTANTS[50]*algebraics[29087+i]*(algebraics[15776+i]/50.0000);
    algebraics[30073+i] =  ( CONSTANTS[38]*pow(states[6409+i], 4.00000))*states[6902+i];
    algebraics[30566+i] =  CONSTANTS[51]*algebraics[30073+i]*(algebraics[15776+i]/50.0000);
    algebraics[32538+i] =  (1.00000/7.00000)*(exp(states[2958+i]/67.3000) - 1.00000);
    algebraics[33031+i] = pow(1.00000+ 0.120000*exp( -0.100000*states[493+i]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*algebraics[32538+i]*exp(- ( states[493+i]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);
    algebraics[33524+i] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/states[986+i], 2.00000)*pow(1.00000+CONSTANTS[45]/states[2465+i], 3.00000)));
    algebraics[34017+i] =  CONSTANTS[53]*algebraics[33524+i]*algebraics[33031+i];
    rates[1479+i] =  - CONSTANTS[9]*((algebraics[29580+i]+algebraics[30566+i]+CONSTANTS[12]+ - 2.00000*algebraics[34017+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (algebraics[20213+i]+algebraics[21199+i]+CONSTANTS[12]+ -2.00000*algebraics[24650+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);
    rates[986+i] = (algebraics[29580+i]+algebraics[30566+i]+CONSTANTS[12]+ - 2.00000*algebraics[34017+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (states[986+i] - states[1972+i])/CONSTANTS[7];
    algebraics[31552+i] =  ( ( CONSTANTS[39]*pow(states[7395+i], 3.00000))*states[7888+i])*states[8381+i];
    algebraics[31059+i] =  states[493+i]*((states[2465+i] -  states[2958+i]*exp(( -1.00000*CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[32045+i] =  CONSTANTS[52]*algebraics[31552+i]*(algebraics[31059+i]/75.0000);
    rates[2465+i] =  - CONSTANTS[9]*((algebraics[32045+i]+CONSTANTS[13]+ 3.00000*algebraics[34017+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (algebraics[22678+i]+CONSTANTS[13]+ 3.00000*algebraics[24650+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);
    rates[2958+i] = (algebraics[32045+i]+CONSTANTS[13]+ 3.00000*algebraics[34017+i])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (states[2958+i] - states[3451+i])/CONSTANTS[8];
    algebraics[14297+i] = 156.500/(5.00000+exp(( - CONSTANTS[6]*algebraics[12818+i])/( CONSTANTS[35]*CONSTANTS[36])));
    algebraics[14790+i] = 156.500 -  5.00000*algebraics[14297+i];
    algebraics[26129+i] =  states[493+i]*((algebraics[14297+i] -  algebraics[14790+i]*exp(( CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*states[493+i])/( CONSTANTS[35]*CONSTANTS[36]))));
    algebraics[25636+i] = 1.00000/(1.00000+exp((states[493+i] - CONSTANTS[23])/CONSTANTS[26]));
    algebraics[26622+i] =  CONSTANTS[37]*pow(algebraics[25636+i], 4.00000);
    algebraics[27115+i] =  CONSTANTS[49]*algebraics[26622+i]*(algebraics[26129+i]/45.0000);
    algebraics[34510+i] = algebraics[27115+i]+algebraics[29580+i]+algebraics[30566+i]+algebraics[32045+i]+algebraics[34017+i];
    rates[493+i] = - ((algebraics[34510+i] - algebraics[0+i]/CONSTANTS[1])/CONSTANTS[0]);
  }
}
void computeVariables(double VOI, double* CONSTANTS, double* RATES, double* STATES, double* ALGEBRAIC)
{
}



// compute the rhs for a single instance, this can be used for computation of the equilibrium values of the states
#ifdef __cplusplus
extern "C"
#endif
void computeCellMLRightHandSideSingleInstance(void *context, double t, double *states, double *rates, double *algebraics, double *parameters)
{
  double VOI = t;   /* current simulation time */

  /* define constants */
  double CONSTANTS[112];
  CONSTANTS[0] = 0.58;
  CONSTANTS[1] = 2.79;
  CONSTANTS[2] = 150;
  CONSTANTS[3] = 0.000001;
  CONSTANTS[4] = 0.0025;
  CONSTANTS[5] = 0.0005;
  CONSTANTS[6] = 96485;
  CONSTANTS[7] = 559;
  CONSTANTS[8] = 559;
  CONSTANTS[9] = 0.00174;
  CONSTANTS[10] = 40229.885;
  CONSTANTS[11] = 40229.885;
  CONSTANTS[12] = 0.34;
  CONSTANTS[13] = -0.43;
  CONSTANTS[14] = 0.0081;
  CONSTANTS[15] = 0.288;
  CONSTANTS[16] = 0.0131;
  CONSTANTS[17] = 4.38;
  CONSTANTS[18] = 1.38;
  CONSTANTS[19] = 0.067;
  CONSTANTS[20] = -46;
  CONSTANTS[21] = -40;
  CONSTANTS[22] = -45;
  CONSTANTS[23] = 70;
  CONSTANTS[24] = -68;
  CONSTANTS[25] = -40;
  CONSTANTS[26] = 150;
  CONSTANTS[27] = 7.1;
  CONSTANTS[28] = 7.5;
  CONSTANTS[29] = 14.7;
  CONSTANTS[30] = 9;
  CONSTANTS[31] = 10;
  CONSTANTS[32] = 7;
  CONSTANTS[33] = 18;
  CONSTANTS[34] = 40;
  CONSTANTS[35] = 8314.41;
  CONSTANTS[36] = 293;
  CONSTANTS[37] = 3.275;
  CONSTANTS[38] = 10.8;
  CONSTANTS[39] = 134;
  CONSTANTS[40] = 1.85;
  CONSTANTS[41] = 0.4;
  CONSTANTS[42] = 950;
  CONSTANTS[43] = 1;
  CONSTANTS[44] = 1;
  CONSTANTS[45] = 13;
  CONSTANTS[46] = 10;
  CONSTANTS[47] = 0.0001656;
  CONSTANTS[48] = 70;
  CONSTANTS[49] = 0.1;
  CONSTANTS[50] = 1.0;
  CONSTANTS[51] = 0.45;
  CONSTANTS[52] = 0.1;
  CONSTANTS[53] = 0.1;
  CONSTANTS[54] = 0.0;
  CONSTANTS[55] = 0.002;
  CONSTANTS[56] = 1000;
  CONSTANTS[57] = 0.2;
  CONSTANTS[58] = 0.2;
  CONSTANTS[59] = 4.5;
  CONSTANTS[60] = -20;
  CONSTANTS[61] = 2.4375;
  CONSTANTS[62] = 1;
  CONSTANTS[63] = 0.00004;
  CONSTANTS[64] = 0.75;
  CONSTANTS[65] = 0.75;
  CONSTANTS[66] = 1.0;
  CONSTANTS[67] = 1.0;
  CONSTANTS[68] = 0.5;
  CONSTANTS[69] = 0.0885;
  CONSTANTS[70] = 0.115;
  CONSTANTS[71] = 140;
  CONSTANTS[72] = 0;
  CONSTANTS[73] = 0;
  CONSTANTS[74] = 1500;
  CONSTANTS[75] = 0;
  CONSTANTS[76] = 0;
  CONSTANTS[77] = 0.000004;
  CONSTANTS[78] = 0.005;
  CONSTANTS[79] = 31000;
  CONSTANTS[80] = 0.15;
  CONSTANTS[81] = 30;
  CONSTANTS[82] = 0.0015;
  CONSTANTS[83] = 0.15;
  CONSTANTS[84] = 0.375;
  CONSTANTS[85] = 1.5;
  CONSTANTS[86] = 0;
  CONSTANTS[87] = 0.15;
  CONSTANTS[88] = 0.15;
  CONSTANTS[89] = 0.05;
  CONSTANTS[90] = 0.5;
  CONSTANTS[91] = 5;
  CONSTANTS[92] = 0.08;
  CONSTANTS[93] = 0.06;
  CONSTANTS[94] = 0.04;
  CONSTANTS[95] = 0.00000394;
  CONSTANTS[96] = 0.00000362;
  CONSTANTS[97] = 1;
  CONSTANTS[98] = 0.0001;
  CONSTANTS[99] = 6;
  CONSTANTS[100] = 0.05;
  CONSTANTS[101] = 0.0;
  CONSTANTS[102] = 0.05;
  CONSTANTS[103] = 0.000107;
  CONSTANTS[104] = 0.0021;
  CONSTANTS[105] = 60;
  CONSTANTS[106] =  0.950000*CONSTANTS[66]* 3.14159265358979*pow(CONSTANTS[68], 2.00000);
  CONSTANTS[107] =  0.0500000*CONSTANTS[66]* 3.14159265358979*pow(CONSTANTS[68], 2.00000);
  CONSTANTS[108] =  0.0100000*CONSTANTS[106];
  CONSTANTS[109] =  0.990000*CONSTANTS[106];
  CONSTANTS[110] =  0.0100000*CONSTANTS[107];
  CONSTANTS[111] =  0.990000*CONSTANTS[107];

  rates[29] = (((( ( CONSTANTS[105]*(states[18]+states[19]+states[20]+states[21]+states[22]))*((states[30] - states[29])/CONSTANTS[108]) -  CONSTANTS[61]*((states[29]/(states[29]+CONSTANTS[62]))/CONSTANTS[108]))+ CONSTANTS[63]*((states[30] - states[29])/CONSTANTS[108]))+ - CONSTANTS[64]*((states[29] - states[31])/CONSTANTS[108]))+- ( ( CONSTANTS[72]*states[29])*((CONSTANTS[74]+- states[34])+- states[36])+ - CONSTANTS[73]*states[34]))+- ( ( CONSTANTS[80]*states[29])*states[44]+ - CONSTANTS[81]*states[40]);
  rates[30] = ((( - ( CONSTANTS[105]*(states[18]+states[19]+states[20]+states[21]+states[22]))*((states[30] - states[29])/CONSTANTS[110])+ CONSTANTS[61]*((states[29]/(states[29]+CONSTANTS[62]))/CONSTANTS[110]))+ - CONSTANTS[63]*((states[30] - states[29])/CONSTANTS[110]))+ - CONSTANTS[65]*((states[30] - states[32])/CONSTANTS[110]))+- ( ( CONSTANTS[77]*states[30])*(CONSTANTS[79] - states[38])+ - CONSTANTS[78]*states[38]);
  rates[32] = ((( CONSTANTS[61]*((states[31]/(states[31]+CONSTANTS[62]))/CONSTANTS[111])+ - CONSTANTS[63]*((states[32]+- states[31])/CONSTANTS[111]))+ CONSTANTS[65]*((states[30]+- states[32])/CONSTANTS[111]))+- ( ( CONSTANTS[77]*states[32])*(CONSTANTS[79]+- states[39])+ - CONSTANTS[78]*states[39])) -  (1000.00/1.00000)*( CONSTANTS[97]*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99])*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[55]*states[32] -  CONSTANTS[98]*states[56]*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32])*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32]>0.00000 ? 1.00000 : 0.00000));
  rates[34] =  ( CONSTANTS[72]*states[29])*((CONSTANTS[74]+- states[34])+- states[36])+ - CONSTANTS[73]*states[34];
  rates[35] =  ( CONSTANTS[72]*states[31])*((CONSTANTS[74]+- states[35])+- states[37])+ - CONSTANTS[73]*states[35];
  rates[36] =  ( CONSTANTS[75]*(CONSTANTS[74]+- states[34]+- states[36]))*states[46]+ - CONSTANTS[76]*states[36];
  rates[37] =  ( CONSTANTS[75]*(CONSTANTS[74]+- states[35]+- states[37]))*states[47]+ - CONSTANTS[76]*states[37];
  rates[38] =  ( CONSTANTS[77]*states[30])*(CONSTANTS[79]+- states[38])+ - CONSTANTS[78]*states[38];
  rates[39] =  ( CONSTANTS[77]*states[32])*(CONSTANTS[79]+- states[39])+ - CONSTANTS[78]*states[39];
  rates[40] = ( ( CONSTANTS[80]*states[29])*states[44]+ - CONSTANTS[81]*states[40])+ - CONSTANTS[84]*((states[40]+- states[41])/CONSTANTS[108]);
  rates[41] = ( ( CONSTANTS[80]*states[31])*states[45]+ - CONSTANTS[81]*states[41])+ CONSTANTS[84]*((states[40]+- states[41])/CONSTANTS[109]);
  rates[42] = ( ( CONSTANTS[82]*states[46])*states[44]+ - CONSTANTS[83]*states[42])+ - CONSTANTS[84]*((states[42]+- states[43])/CONSTANTS[108]);
  rates[43] = ( ( CONSTANTS[82]*states[47])*states[45]+ - CONSTANTS[83]*states[43])+ CONSTANTS[84]*((states[42]+- states[43])/CONSTANTS[109]);
  rates[44] = (- ( ( CONSTANTS[80]*states[29])*states[44]+ - CONSTANTS[81]*states[40])+- ( ( CONSTANTS[82]*states[46])*states[44]+ - CONSTANTS[83]*states[42]))+ - CONSTANTS[84]*((states[44]+- states[45])/CONSTANTS[108]);
  rates[45] = (- ( ( CONSTANTS[80]*states[31])*states[45]+ - CONSTANTS[81]*states[41])+- ( ( CONSTANTS[82]*states[47])*states[45]+ - CONSTANTS[83]*states[43]))+ CONSTANTS[84]*((states[44]+- states[45])/CONSTANTS[109]);
  rates[46] = (- ( ( CONSTANTS[75]*(CONSTANTS[74]+- states[34]+- states[36]))*states[46]+ - CONSTANTS[76]*states[36])+- ( ( CONSTANTS[82]*states[46])*states[44]+ - CONSTANTS[83]*states[42]))+ - CONSTANTS[85]*((states[46]+- states[47])/CONSTANTS[108]);
  rates[47] = (- ( ( CONSTANTS[75]*(CONSTANTS[74]+- states[35]+- states[37]))*states[47]+ - CONSTANTS[76]*states[37])+- ( ( CONSTANTS[82]*states[47])*states[45]+ - CONSTANTS[83]*states[43]))+ CONSTANTS[85]*((states[46]+- states[47])/CONSTANTS[109]);
  rates[48] = (( ( CONSTANTS[69]*states[31])*states[33]+ - CONSTANTS[70]*states[48])+ - CONSTANTS[88]*states[48])+ CONSTANTS[89]*states[51];
  rates[50] = (((( CONSTANTS[69]*states[31]*states[49]+ - CONSTANTS[70]*states[50])+ CONSTANTS[86]*states[33])+ - CONSTANTS[87]*states[50])+ ( - CONSTANTS[69]*states[31])*states[50])+ CONSTANTS[70]*states[51];
  rates[51] = ((((( CONSTANTS[69]*states[31]*states[50]+ - CONSTANTS[70]*states[51])+ CONSTANTS[88]*states[48])+ - CONSTANTS[89]*states[51])+ - CONSTANTS[90]*states[51])+ CONSTANTS[91]*states[52])+ CONSTANTS[94]*states[53];
  rates[52] = (( CONSTANTS[90]*states[51]+ - CONSTANTS[91]*states[52])+ CONSTANTS[93]*states[53])+ - CONSTANTS[92]*states[52];
  rates[53] = ( - CONSTANTS[93]*states[53]+ CONSTANTS[92]*states[52])+ - CONSTANTS[94]*states[53];
  rates[54] =  (0.00100000/1.00000)*( CONSTANTS[92]*states[52] -  CONSTANTS[93]*states[53])+ -1.00000*CONSTANTS[95]*states[54]+ -1.00000*CONSTANTS[96]*((states[54] - states[55])/CONSTANTS[109]);
  rates[55] =  CONSTANTS[96]*((states[54] - states[55])/CONSTANTS[111]) -  1.00000*( CONSTANTS[97]*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99])*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[55]*states[32] -  CONSTANTS[98]*states[56]*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32])*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32]>0.00000 ? 1.00000 : 0.00000));
  rates[56] =  1.00000*( CONSTANTS[97]*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99])*( states[55]*(0.00100000/1.00000)*states[32] - CONSTANTS[99]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*states[55]*states[32] -  CONSTANTS[98]*states[56]*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32])*(CONSTANTS[99] -  states[55]*(0.00100000/1.00000)*states[32]>0.00000 ? 1.00000 : 0.00000));
  algebraics[13] = (CONSTANTS[71]+- states[33]+- states[48]+- states[49]+- states[50]+- states[51]+- states[52]+- states[53]>0.00000 ? CONSTANTS[71]+- states[33]+- states[48]+- states[49]+- states[50]+- states[51]+- states[52]+- states[53] : 0.00000);
  rates[31] = (((( - CONSTANTS[61]*((states[31]/(states[31]+CONSTANTS[62]))/CONSTANTS[109])+ CONSTANTS[63]*((states[32]+- states[31])/CONSTANTS[109]))+ CONSTANTS[64]*((states[29] - states[31])/CONSTANTS[109]))+- ((((((( CONSTANTS[69]*states[31]*algebraics[13]+ - CONSTANTS[70]*states[33])+ CONSTANTS[69]*states[31]*states[33])+ - CONSTANTS[70]*states[48])+ CONSTANTS[69]*states[31]*states[49])+ - CONSTANTS[70]*states[50])+ CONSTANTS[69]*states[31]*states[50])+ - CONSTANTS[70]*states[51]))+- ( ( CONSTANTS[72]*states[31])*(CONSTANTS[74]+- states[35]+- states[37])+ - CONSTANTS[73]*states[35]))+- ( ( CONSTANTS[80]*states[31])*states[45]+ - CONSTANTS[81]*states[41]);
  rates[33] = (((( ( CONSTANTS[69]*states[31])*algebraics[13]+ - CONSTANTS[70]*states[33])+ ( - CONSTANTS[69]*states[31])*states[33])+ CONSTANTS[70]*states[48])+ - CONSTANTS[86]*states[33])+ CONSTANTS[87]*states[50];
  rates[49] = (( ( - CONSTANTS[69]*states[31])*states[49]+ CONSTANTS[70]*states[50])+ CONSTANTS[86]*algebraics[13])+ - CONSTANTS[87]*states[49];
  algebraics[12] =  ((( (states[52]/CONSTANTS[71])*CONSTANTS[101]+ (states[53]/CONSTANTS[71])*CONSTANTS[102]) - CONSTANTS[103])/CONSTANTS[104])*(parameters[1]>=0.635000&&parameters[1]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(parameters[1] - 0.635000) : parameters[1]>0.850000&&parameters[1]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(parameters[1] - 0.850000) : parameters[1]>1.17000&&parameters[1]<=1.25500 ? 1.00000 : parameters[1]>1.25500&&parameters[1]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(parameters[1] - 1.25500) : 0.00000);
  rates[28] = algebraics[12];
  algebraics[1] =  CONSTANTS[16]*((states[0] - CONSTANTS[21])/(1.00000 - exp(- ((states[0] - CONSTANTS[21])/CONSTANTS[32]))));
  algebraics[15] =  CONSTANTS[19]*exp(- ((states[0] - CONSTANTS[21])/CONSTANTS[34]));
  rates[8] =  algebraics[1]*(1.00000 - states[8]) -  algebraics[15]*states[8];
  algebraics[2] = 1.00000/(1.00000+exp((states[0] - CONSTANTS[25])/CONSTANTS[28]));
  algebraics[16] =  1000.00*exp(- ((states[0]+40.0000)/25.7500));
  rates[9] = (algebraics[2] - states[9])/algebraics[16];
  algebraics[4] =  CONSTANTS[15]*((states[0] - CONSTANTS[20])/(1.00000 - exp(- ((states[0] - CONSTANTS[20])/CONSTANTS[31]))));
  algebraics[18] =  CONSTANTS[18]*exp(- ((states[0] - CONSTANTS[20])/CONSTANTS[33]));
  rates[10] =  algebraics[4]*(1.00000 - states[10]) -  algebraics[18]*states[10];
  algebraics[3] =  CONSTANTS[14]*exp(- ((states[0] - CONSTANTS[22])/CONSTANTS[29]));
  algebraics[17] = CONSTANTS[17]/(1.00000+exp(- ((states[0] - CONSTANTS[22])/CONSTANTS[30])));
  rates[11] =  algebraics[3]*(1.00000 - states[11]) -  algebraics[17]*states[11];
  algebraics[5] = 1.00000/(1.00000+exp((states[0] - CONSTANTS[24])/CONSTANTS[27]));
  algebraics[19] = 8571.00/(0.200000+ 5.65000*pow((states[0]+CONSTANTS[48])/100.000, 2.00000));
  rates[12] = (algebraics[5] - states[12])/algebraics[19];
  algebraics[6] =  CONSTANTS[16]*((states[1] - CONSTANTS[21])/(1.00000 - exp(- ((states[1] - CONSTANTS[21])/CONSTANTS[32]))));
  algebraics[20] =  CONSTANTS[19]*exp(- ((states[1] - CONSTANTS[21])/CONSTANTS[34]));
  rates[13] =  algebraics[6]*(1.00000 - states[13]) -  algebraics[20]*states[13];
  algebraics[7] = 1.00000/(1.00000+exp((states[1] - CONSTANTS[25])/CONSTANTS[28]));
  algebraics[21] =  1.00000*exp(- ((states[1]+40.0000)/25.7500));
  rates[14] = (algebraics[7] - states[14])/algebraics[21];
  algebraics[9] =  CONSTANTS[15]*((states[1] - CONSTANTS[20])/(1.00000 - exp(- ((states[1] - CONSTANTS[20])/CONSTANTS[31]))));
  algebraics[23] =  CONSTANTS[18]*exp(- ((states[1] - CONSTANTS[20])/CONSTANTS[33]));
  rates[15] =  algebraics[9]*(1.00000 - states[15]) -  algebraics[23]*states[15];
  algebraics[8] =  CONSTANTS[14]*exp(- ((states[1] - CONSTANTS[22])/CONSTANTS[29]));
  algebraics[22] = CONSTANTS[17]/(1.00000+exp(- ((states[1] - CONSTANTS[22])/CONSTANTS[30])));
  rates[16] =  algebraics[8]*(1.00000 - states[16]) -  algebraics[22]*states[16];
  algebraics[10] = 1.00000/(1.00000+exp((states[1] - CONSTANTS[24])/CONSTANTS[27]));
  algebraics[24] = 8571.00/(0.200000+ 5.65000*pow((states[1]+CONSTANTS[48])/100.000, 2.00000));
  rates[17] = (algebraics[10] - states[17])/algebraics[24];
  algebraics[11] =  0.500000*CONSTANTS[58]*exp((states[1] - CONSTANTS[60])/( 8.00000*CONSTANTS[59]));
  algebraics[25] =  0.500000*CONSTANTS[58]*exp((CONSTANTS[60] - states[1])/( 8.00000*CONSTANTS[59]));
  rates[23] =  - CONSTANTS[55]*states[23]+ CONSTANTS[56]*states[18]+ -4.00000*algebraics[11]*states[23]+ algebraics[25]*states[24];
  rates[18] =  CONSTANTS[55]*states[23]+ - CONSTANTS[56]*states[18]+( -4.00000*algebraics[11]*states[18])/CONSTANTS[57]+ CONSTANTS[57]*algebraics[25]*states[19];
  rates[24] =  4.00000*algebraics[11]*states[23]+ - algebraics[25]*states[24]+( - CONSTANTS[55]*states[24])/CONSTANTS[57]+ CONSTANTS[57]*CONSTANTS[56]*states[19]+ -3.00000*algebraics[11]*states[24]+ 2.00000*algebraics[25]*states[25];
  rates[19] = ( CONSTANTS[55]*states[24])/CONSTANTS[57]+ - CONSTANTS[56]*CONSTANTS[57]*states[19]+( 4.00000*algebraics[11]*states[18])/CONSTANTS[57]+ - CONSTANTS[57]*algebraics[25]*states[19]+( -3.00000*algebraics[11]*states[19])/CONSTANTS[57]+ 2.00000*CONSTANTS[57]*algebraics[25]*states[20];
  rates[25] =  3.00000*algebraics[11]*states[24]+ -2.00000*algebraics[25]*states[25]+( - CONSTANTS[55]*states[25])/pow(CONSTANTS[57], 2.00000)+ pow(CONSTANTS[57], 2.00000)*CONSTANTS[56]*states[20]+ -2.00000*algebraics[11]*states[25]+ 3.00000*algebraics[25]*states[26];
  rates[20] = ( 3.00000*algebraics[11]*states[19])/CONSTANTS[57]+ -2.00000*CONSTANTS[57]*algebraics[25]*states[20]+( CONSTANTS[55]*states[25])/pow(CONSTANTS[57], 2.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 2.00000)*states[20]+( -2.00000*algebraics[11]*states[20])/CONSTANTS[57]+ 3.00000*CONSTANTS[57]*algebraics[25]*states[21];
  rates[26] =  2.00000*algebraics[11]*states[25]+ -3.00000*algebraics[25]*states[26]+( - CONSTANTS[55]*states[26])/pow(CONSTANTS[57], 3.00000)+ CONSTANTS[56]*pow(CONSTANTS[57], 3.00000)*states[21]+ - algebraics[11]*states[26]+ 4.00000*algebraics[25]*states[27];
  rates[21] = ( CONSTANTS[55]*states[26])/pow(CONSTANTS[57], 3.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 3.00000)*states[21]+( 2.00000*algebraics[11]*states[20])/CONSTANTS[57]+ -3.00000*algebraics[25]*CONSTANTS[57]*states[21]+( - algebraics[11]*states[21])/CONSTANTS[57]+ 4.00000*CONSTANTS[57]*algebraics[25]*states[22];
  rates[27] =  algebraics[11]*states[26]+ -4.00000*algebraics[25]*states[27]+( - CONSTANTS[55]*states[27])/pow(CONSTANTS[57], 4.00000)+ CONSTANTS[56]*pow(CONSTANTS[57], 4.00000)*states[22];
  rates[22] = ( algebraics[11]*states[21])/CONSTANTS[57]+ -4.00000*CONSTANTS[57]*algebraics[25]*states[22]+( CONSTANTS[55]*states[27])/pow(CONSTANTS[57], 4.00000)+ - CONSTANTS[56]*pow(CONSTANTS[57], 4.00000)*states[22];
  algebraics[31] =  states[0]*((states[3] -  states[4]*exp(( -1.00000*CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[14] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(states[4]/states[3]);
  algebraics[37] =  states[4]*exp( ( - CONSTANTS[41]*algebraics[14])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));
  algebraics[38] =  CONSTANTS[40]*(pow(algebraics[37], 2.00000)/(CONSTANTS[42]+pow(algebraics[37], 2.00000)));
  algebraics[39] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(algebraics[37], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*states[0]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);
  algebraics[40] =  algebraics[38]*algebraics[39];
  algebraics[41] =  algebraics[40]*(algebraics[31]>0.00000 ? 1.00000 : 0.00000)*(algebraics[31]/50.0000);
  algebraics[42] =  ( CONSTANTS[38]*pow(states[8], 4.00000))*states[9];
  algebraics[43] =  algebraics[42]*(algebraics[31]/50.0000);
  algebraics[47] =  (1.00000/7.00000)*(exp(states[7]/67.3000) - 1.00000);
  algebraics[48] = pow(1.00000+ 0.120000*exp( -0.100000*states[0]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*algebraics[47]*exp(- ( states[0]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);
  algebraics[49] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/states[4], 2.00000)*pow(1.00000+CONSTANTS[45]/states[5], 3.00000)));
  algebraics[50] =  algebraics[49]*algebraics[48];
  rates[4] = (algebraics[41]+algebraics[43]+CONSTANTS[12]+ - 2.00000*algebraics[50])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(states[2] - states[4])/CONSTANTS[10];
  algebraics[45] =  ( ( CONSTANTS[39]*pow(states[10], 3.00000))*states[11])*states[12];
  algebraics[44] =  states[0]*((states[5] -  states[7]*exp(( -1.00000*CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[46] =  algebraics[45]*(algebraics[44]/75.0000);
  rates[7] = (algebraics[46]+CONSTANTS[13]+ 3.00000*algebraics[50])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(states[6] - states[7])/CONSTANTS[11];
  algebraics[0] =  (1000.00/1.00000)*((states[0] - states[1])/CONSTANTS[2]);
  algebraics[27] = 156.500/(5.00000+exp(( - CONSTANTS[6]*algebraics[14])/( CONSTANTS[35]*CONSTANTS[36])));
  algebraics[28] = 156.500 -  5.00000*algebraics[27];
  algebraics[34] =  states[0]*((algebraics[27] -  algebraics[28]*exp(( CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*states[0])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[33] = 1.00000/(1.00000+exp((states[0] - CONSTANTS[23])/CONSTANTS[26]));
  algebraics[35] =  CONSTANTS[37]*pow(algebraics[33], 4.00000);
  algebraics[36] =  algebraics[35]*(algebraics[34]/45.0000);
  algebraics[51] = algebraics[36]+algebraics[41]+algebraics[43]+algebraics[46]+algebraics[50]+- parameters[0];
  rates[0] = - ((algebraics[51]+algebraics[0])/CONSTANTS[0]);
  algebraics[32] =  states[1]*((states[3] -  states[2]*exp(( -1.00000*CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[26] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(states[2]/states[3]);
  algebraics[56] =  states[2]*exp( ( - CONSTANTS[41]*algebraics[26])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));
  algebraics[57] =  CONSTANTS[40]*(pow(algebraics[56], 2.00000)/(CONSTANTS[42]+pow(algebraics[56], 2.00000)));
  algebraics[58] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(algebraics[56], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*states[1]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);
  algebraics[59] =  algebraics[57]*algebraics[58];
  algebraics[60] =  CONSTANTS[50]*algebraics[59]*(algebraics[32]/50.0000);
  algebraics[61] =  ( CONSTANTS[38]*pow(states[13], 4.00000))*states[14];
  algebraics[62] =  CONSTANTS[51]*algebraics[61]*(algebraics[32]/50.0000);
  algebraics[66] =  (1.00000/7.00000)*(exp(states[6]/67.3000) - 1.00000);
  algebraics[67] = pow(1.00000+ 0.120000*exp( -0.100000*states[1]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*algebraics[66]*exp(- ( states[1]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);
  algebraics[68] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/states[2], 2.00000)*pow(1.00000+CONSTANTS[45]/states[5], 3.00000)));
  algebraics[69] =  CONSTANTS[53]*algebraics[68]*algebraics[67];
  rates[3] =  - CONSTANTS[9]*((algebraics[60]+algebraics[62]+CONSTANTS[12]+ - 2.00000*algebraics[69])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (algebraics[41]+algebraics[43]+CONSTANTS[12]+ -2.00000*algebraics[50])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);
  rates[2] = (algebraics[60]+algebraics[62]+CONSTANTS[12]+ - 2.00000*algebraics[69])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (states[2] - states[4])/CONSTANTS[7];
  algebraics[64] =  ( ( CONSTANTS[39]*pow(states[15], 3.00000))*states[16])*states[17];
  algebraics[63] =  states[1]*((states[5] -  states[6]*exp(( -1.00000*CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[65] =  CONSTANTS[52]*algebraics[64]*(algebraics[63]/75.0000);
  rates[5] =  - CONSTANTS[9]*((algebraics[65]+CONSTANTS[13]+ 3.00000*algebraics[69])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (algebraics[46]+CONSTANTS[13]+ 3.00000*algebraics[50])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);
  rates[6] = (algebraics[65]+CONSTANTS[13]+ 3.00000*algebraics[69])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (states[6] - states[7])/CONSTANTS[8];
  algebraics[29] = 156.500/(5.00000+exp(( - CONSTANTS[6]*algebraics[26])/( CONSTANTS[35]*CONSTANTS[36])));
  algebraics[30] = 156.500 -  5.00000*algebraics[29];
  algebraics[53] =  states[1]*((algebraics[29] -  algebraics[30]*exp(( CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*states[1])/( CONSTANTS[35]*CONSTANTS[36]))));
  algebraics[52] = 1.00000/(1.00000+exp((states[1] - CONSTANTS[23])/CONSTANTS[26]));
  algebraics[54] =  CONSTANTS[37]*pow(algebraics[52], 4.00000);
  algebraics[55] =  CONSTANTS[49]*algebraics[54]*(algebraics[53]/45.0000);
  algebraics[70] = algebraics[55]+algebraics[60]+algebraics[62]+algebraics[65]+algebraics[69];
  rates[1] = - ((algebraics[70] - algebraics[0]/CONSTANTS[1])/CONSTANTS[0]);
}
