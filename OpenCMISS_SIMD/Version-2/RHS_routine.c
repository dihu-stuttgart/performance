#include <math.h>
#include <time.h> 
#include "RHS_routine.h"

/*void fun(double* rates, int c){
  c = c+1-1;
}*/

void RHS_routineForAVX(double * restrict X0, double * restrict X1, double * restrict X2, double * restrict X3, double * restrict X4, double * restrict X5, double * restrict X6, double * restrict X7, double * restrict X8, double * restrict X9,
                      double * restrict X10,double * restrict X11,double * restrict X12,double * restrict X13,double * restrict X14,double * restrict X15,double * restrict X16,double * restrict X17,double * restrict X18,double * restrict X19,
                      double * restrict X20,double * restrict X21,double * restrict X22,double * restrict X23,double * restrict X24,double * restrict X25,double * restrict X26,double * restrict X27,double * restrict X28,double * restrict X29,
                      double * restrict X30,double * restrict X31,double * restrict X32,double * restrict X33,double * restrict X34,double * restrict X35,double * restrict X36,double * restrict X37,double * restrict X38,double * restrict X39,
                      double * restrict X40,double * restrict X41,double * restrict X42,double * restrict X43,double * restrict X44,double * restrict X45,double * restrict X46,double * restrict X47,double * restrict X48,double * restrict X49,
                      double * restrict X50,double * restrict X51,double * restrict X52,double * restrict X53,double * restrict X54,double * restrict X55,double * restrict X56,int N, //the number of existing cells. also the length of all the double vectors we have a pointer for
                      double * restrict X_t0, double * restrict X_t1, double * restrict X_t2, double * restrict X_t3, double * restrict X_t4, double * restrict X_t5, double * restrict X_t6, double * restrict X_t7, double * restrict X_t8, double * restrict X_t9,
                      double * restrict X_t10,double * restrict X_t11,double * restrict X_t12,double * restrict X_t13,double * restrict X_t14,double * restrict X_t15,double * restrict X_t16,double * restrict X_t17,double * restrict X_t18,double * restrict X_t19,
                      double * restrict X_t20,double * restrict X_t21,double * restrict X_t22,double * restrict X_t23,double * restrict X_t24,double * restrict X_t25,double * restrict X_t26,double * restrict X_t27,double * restrict X_t28,double * restrict X_t29,
                      double * restrict X_t30,double * restrict X_t31,double * restrict X_t32,double * restrict X_t33,double * restrict X_t34,double * restrict X_t35,double * restrict X_t36,double * restrict X_t37,double * restrict X_t38,double * restrict X_t39,
                      double * restrict X_t40,double * restrict X_t41,double * restrict X_t42,double * restrict X_t43,double * restrict X_t44,double * restrict X_t45,double * restrict X_t46,double * restrict X_t47,double * restrict X_t48,double * restrict X_t49,
                      double * restrict X_t50,double * restrict X_t51,double * restrict X_t52,double * restrict X_t53,double * restrict X_t54,double * restrict X_t55,double * restrict X_t56,
                      double * restrict Gamma, double * restrict StimValue, double * restrict L_hs, clock_t * restrict handle_array, double * restrict portions_array)
{
  double CONSTANTS[110];
  double TMP0[N],  TMP1[N],  TMP2[N],  TMP3[N],  TMP4[N],  TMP5[N],  TMP6[N],  TMP7[N],  TMP8[N],  TMP9[N],
         TMP10[N], TMP11[N], TMP12[N], TMP13[N], TMP14[N], TMP15[N], TMP16[N], TMP17[N], TMP18[N], TMP19[N],
         TMP20[N], TMP21[N], TMP22[N], TMP23[N], TMP24[N], TMP25[N], TMP26[N], TMP27[N], TMP28[N], TMP29[N],
         TMP30[N], TMP31[N], TMP32[N], TMP33[N], TMP34[N], TMP35[N], TMP36[N], TMP37[N], TMP38[N], TMP39[N],
         TMP40[N], TMP41[N], TMP42[N], TMP43[N], TMP44[N], TMP45[N], TMP46[N], TMP47[N], TMP48[N], TMP49[N],
         TMP50[N], TMP51[N], TMP52[N], TMP53[N], TMP54[N], TMP55[N], TMP56[N], TMP57[N], TMP58[N], TMP59[N],
         TMP60[N], TMP61[N], TMP62[N], TMP63[N], TMP64[N], TMP65[N], TMP66[N], TMP67[N], TMP68[N], TMP69[N];
  int cell;
  handle_array[3]=clock();
/* Constant C_m */
CONSTANTS[0] = 0.58;
/* Constant gam */
CONSTANTS[1] = 2.79;
/* Constant R_a */
CONSTANTS[2] = 150;
/* Constant tsi */
CONSTANTS[3] = 0.000001;
/* Constant tsi2 */
CONSTANTS[4] = 0.0025;
/* Constant tsi3 */
CONSTANTS[5] = 0.0005;
/* Constant FF */
CONSTANTS[6] = 96485;
/* Constant tau_K */
CONSTANTS[7] = 559;
/* Constant tau_Na */
CONSTANTS[8] = 559;
/* Constant f_T */
CONSTANTS[9] = 0.00174;
/* Constant tau_K2 */
CONSTANTS[10] = 40229.885;
/* Constant tau_Na2 */
CONSTANTS[11] = 40229.885;
/* Constant I_K_rest */
CONSTANTS[12] = 0.34;
/* Constant I_Na_rest */
CONSTANTS[13] = -0.43;
/* Constant alpha_h_bar */
CONSTANTS[14] = 0.0081;
/* Constant alpha_m_bar */
CONSTANTS[15] = 0.288;
/* Constant alpha_n_bar */
CONSTANTS[16] = 0.0131;
/* Constant beta_h_bar */
CONSTANTS[17] = 4.38;
/* Constant beta_m_bar */
CONSTANTS[18] = 1.38;
/* Constant beta_n_bar */
CONSTANTS[19] = 0.067;
/* Constant V_m */
CONSTANTS[20] = -46;
/* Constant V_n */
CONSTANTS[21] = -40;
/* Constant V_h */
CONSTANTS[22] = -45;
/* Constant V_a */
CONSTANTS[23] = 70;
/* Constant V_S_inf */
CONSTANTS[24] = -68;
/* Constant V_h_K_inf */
CONSTANTS[25] = -40;
/* Constant A_a */
CONSTANTS[26] = 150;
/* Constant A_S_inf */
CONSTANTS[27] = 7.1;
/* Constant A_h_K_inf */
CONSTANTS[28] = 7.5;
/* Constant K_alpha_h */
CONSTANTS[29] = 14.7;
/* Constant K_beta_h */
CONSTANTS[30] = 9;
/* Constant K_alpha_m */
CONSTANTS[31] = 10;
/* Constant K_alpha_n */
CONSTANTS[32] = 7;
/* Constant K_beta_m */
CONSTANTS[33] = 18;
/* Constant K_beta_n */
CONSTANTS[34] = 40;
/* Constant RR */
CONSTANTS[35] = 8314.41;
/* Constant TT */
CONSTANTS[36] = 293;
/* Constant g_Cl_bar */
CONSTANTS[37] = 3.275;
/* Constant g_K_bar */
CONSTANTS[38] = 10.8;
/* Constant g_Na_bar */
CONSTANTS[39] = 134;
/* Constant G_K */
CONSTANTS[40] = 1.85;
/* Constant del */
CONSTANTS[41] = 0.4;
/* Constant K_K */
CONSTANTS[42] = 950;
/* Constant K_S */
CONSTANTS[43] = 1;
/* Constant K_m_K */
CONSTANTS[44] = 1;
/* Constant K_m_Na */
CONSTANTS[45] = 13;
/* Constant S_i */
CONSTANTS[46] = 10;
/* Constant J_NaK_bar */
CONSTANTS[47] = 0.0001656;
/* Constant V_tau */
CONSTANTS[48] = 70;
/* Constant eta_Cl */
CONSTANTS[49] = 0.1;
/* Constant eta_IR */
CONSTANTS[50] = 1.0;
/* Constant eta_DR */
CONSTANTS[51] = 0.45;
/* Constant eta_Na */
CONSTANTS[52] = 0.1;
/* Constant eta_NaK */
CONSTANTS[53] = 0.1;
/* Constant k_L */
CONSTANTS[54] = 0.002;
/* Constant k_Lm */
CONSTANTS[55] = 1000;
/* Constant f */
CONSTANTS[56] = 0.2;
/* Constant alpha1 */
CONSTANTS[57] = 0.2;
/* Constant K */
CONSTANTS[58] = 4.5;
/* Constant Vbar */
CONSTANTS[59] = -20;
/* Constant nu_SR */
CONSTANTS[60] = 2.4375;
/* Constant K_SR */
CONSTANTS[61] = 1;
/* Constant L_e */
CONSTANTS[62] = 0.00004;
/* Constant tau_R */
CONSTANTS[63] = 0.75;
/* Constant tau_SR_R */
CONSTANTS[64] = 0.75;
/* Constant L_S_0 */
CONSTANTS[65] = 1.0;
/* Constant R_R */
CONSTANTS[66] = 0.5;
/* Constant k_T_on */
CONSTANTS[67] = 0.0885;
/* Constant k_T_off */
CONSTANTS[68] = 0.115;
/* Constant T_tot_0 */
CONSTANTS[69] = 140;
/* Constant k_P_on */
CONSTANTS[70] = 0;
/* Constant k_P_off */
CONSTANTS[71] = 0;
/* Constant P_tot */
CONSTANTS[72] = 1500;
/* Constant k_Mg_on */
CONSTANTS[73] = 0;
/* Constant k_Mg_off */
CONSTANTS[74] = 0;
/* Constant k_Cs_on */
CONSTANTS[75] = 0.000004;
/* Constant k_Cs_off */
CONSTANTS[76] = 0.005;
/* Constant Cs_tot */
CONSTANTS[77] = 31000;
/* Constant k_CATP_on */
CONSTANTS[78] = 0.15;
/* Constant k_CATP_off */
CONSTANTS[79] = 30;
/* Constant k_MATP_on */
CONSTANTS[80] = 0.0015;
/* Constant k_MATP_off */
CONSTANTS[81] = 0.15;
/* Constant tau_ATP */
CONSTANTS[82] = 0.375;
/* Constant tau_Mg */
CONSTANTS[83] = 1.5;
/* Constant k_0_on */
CONSTANTS[84] = 0;
/* Constant k_0_off */
CONSTANTS[85] = 0.15;
/* Constant k_Ca_on */
CONSTANTS[86] = 0.15;
/* Constant k_Ca_off */
CONSTANTS[87] = 0.05;
/* Constant f_o */
CONSTANTS[88] = 0.5;
/* Constant f_p */
CONSTANTS[89] = 5;
/* Constant h_o */
CONSTANTS[90] = 0.08;
/* Constant h_p */
CONSTANTS[91] = 0.06;
/* Constant g_o */
CONSTANTS[92] = 0.04;
/* Constant b_p */
CONSTANTS[93] = 0.00000394;
/* Constant k_p */
CONSTANTS[94] = 0.00000362;
/* Constant A_p */
CONSTANTS[95] = 1;
/* Constant B_p */
CONSTANTS[96] = 0.0001;
/* Constant PP */
CONSTANTS[97] = 6;
/* Constant x_0 */
CONSTANTS[98] = 0.05;
/* Constant x_1 */
CONSTANTS[99] = 0.000000;
/* Constant x_2 */
CONSTANTS[100] = 0.050000;
/* Constant eta war 0.000107 nach umstellung der gamma gleichung jetzt 0.2996*/
CONSTANTS[101] = 0.2996;
/* war Constant zeta 0.0021. jetzt nach umstellung der gamma gleichung A_max = 6.1796*/
CONSTANTS[102] = 6.1796;
/* Constant i2 */
CONSTANTS[103] = 60;
/* Constant V_o_Eqn */
CONSTANTS[104] =  0.950000*CONSTANTS[65]* 3.14159265358979*pow(CONSTANTS[66], 2.00000);
/* Constant V_SR_Eqn */
CONSTANTS[105] =  0.0500000*CONSTANTS[65]* 3.14159265358979*pow(CONSTANTS[66], 2.00000);
/* Constant V_1_Eqn */
CONSTANTS[106] =  0.0100000*CONSTANTS[104];
/* Constant V_2_Eqn */
CONSTANTS[107] =  0.990000*CONSTANTS[104];
/* Constant V_SR1_Eqn */
CONSTANTS[108] =  0.0100000*CONSTANTS[105];
/* Constant V_SR2_Eqn */
CONSTANTS[109] =  0.990000*CONSTANTS[105];
  // time that is spent initializing all the constants:
  handle_array[4]=clock();
  // time to set up the constants for the RHS evaluations:
  portions_array[3] += ((double) (handle_array[4]-handle_array[3])) / CLOCKS_PER_SEC;
/* dCa1_Eqn */
#pragma GCC ivdep
for (cell=1;cell<=N;cell++){
   X_t29[cell] = (((( ( CONSTANTS[103]*(X18[cell]+X19[cell]+X20[cell]+X21[cell]+X22[cell]))*((X30[cell] - X29[cell])/CONSTANTS[106]) -  CONSTANTS[60]*((X29[cell]/(X29[cell]+CONSTANTS[61]))/CONSTANTS[106]))+ CONSTANTS[62]*((X30[cell] - X29[cell])/CONSTANTS[106]))+ - CONSTANTS[63]*((X29[cell] - X31[cell])/CONSTANTS[106]))+- ( ( CONSTANTS[70]*X29[cell])*((CONSTANTS[72]+- X34[cell])+- X36[cell])+ - CONSTANTS[71]*X34[cell]))+- ( ( CONSTANTS[78]*X29[cell])*X44[cell]+ - CONSTANTS[79]*X40[cell]);



   /* dCaSR1_Eqn */
   X_t30[cell] = ((( - ( CONSTANTS[103]*(X18[cell]+X19[cell]+X20[cell]+X21[cell]+X22[cell]))*((X30[cell] - X29[cell])/CONSTANTS[108])+ CONSTANTS[60]*((X29[cell]/(X29[cell]+CONSTANTS[61]))/CONSTANTS[108]))+ - CONSTANTS[62]*((X30[cell] - X29[cell])/CONSTANTS[108]))+ - CONSTANTS[64]*((X30[cell] - X32[cell])/CONSTANTS[108]))+- ( ( CONSTANTS[75]*X30[cell])*(CONSTANTS[77] - X38[cell])+ - CONSTANTS[76]*X38[cell]);



   /* dCa_SR2_Eqn */
   X_t32[cell] = ((( CONSTANTS[60]*((X31[cell]/(X31[cell]+CONSTANTS[61]))/CONSTANTS[109])+ - CONSTANTS[62]*((X32[cell]+- X31[cell])/CONSTANTS[109]))+ CONSTANTS[64]*((X30[cell]+- X32[cell])/CONSTANTS[109]))+- ( ( CONSTANTS[75]*X32[cell])*(CONSTANTS[77]+- X39[cell])+ - CONSTANTS[76]*X39[cell])) -  (1000.00/1.00000)*( CONSTANTS[95]*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97])*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*X55[cell]*X32[cell] -  CONSTANTS[96]*X56[cell]*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell])*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell]>0.00000 ? 1.00000 : 0.00000));



   /* dCa_P1_Eqn */
   X_t34[cell] =  ( CONSTANTS[70]*X29[cell])*((CONSTANTS[72]+- X34[cell])+- X36[cell])+ - CONSTANTS[71]*X34[cell];



   /* dCa_P2_Eqn */
   X_t35[cell] =  ( CONSTANTS[70]*X31[cell])*((CONSTANTS[72]+- X35[cell])+- X37[cell])+ - CONSTANTS[71]*X35[cell];



   /* dMg_P1_Eqn */
   X_t36[cell] =  ( CONSTANTS[73]*(CONSTANTS[72]+- X34[cell]+- X36[cell]))*X46[cell]+ - CONSTANTS[74]*X36[cell];



   /* dMP2_Eqn */
   X_t37[cell] =  ( CONSTANTS[73]*(CONSTANTS[72]+- X35[cell]+- X37[cell]))*X47[cell]+ - CONSTANTS[74]*X37[cell];



   /* dCa_Cs1_Eqn */
   X_t38[cell] =  ( CONSTANTS[75]*X30[cell])*(CONSTANTS[77]+- X38[cell])+ - CONSTANTS[76]*X38[cell];



   /* dCs_Cs2_Eqn */
   X_t39[cell] =  ( CONSTANTS[75]*X32[cell])*(CONSTANTS[77]+- X39[cell])+ - CONSTANTS[76]*X39[cell];



   /* dCa_ATP1_Eqn */
   X_t40[cell] = ( ( CONSTANTS[78]*X29[cell])*X44[cell]+ - CONSTANTS[79]*X40[cell])+ - CONSTANTS[82]*((X40[cell]+- X41[cell])/CONSTANTS[106]);



   /* dCa_ATP2_Eqn */
   X_t41[cell] = ( ( CONSTANTS[78]*X31[cell])*X45[cell]+ - CONSTANTS[79]*X41[cell])+ CONSTANTS[82]*((X40[cell]+- X41[cell])/CONSTANTS[107]);



   /* dMg_ATP1_Eqn */
   X_t42[cell] = ( ( CONSTANTS[80]*X46[cell])*X44[cell]+ - CONSTANTS[81]*X42[cell])+ - CONSTANTS[82]*((X42[cell]+- X43[cell])/CONSTANTS[106]);



   /* dMg_ATP2_Eqn */
   X_t43[cell] = ( ( CONSTANTS[80]*X47[cell])*X45[cell]+ - CONSTANTS[81]*X43[cell])+ CONSTANTS[82]*((X42[cell]+- X43[cell])/CONSTANTS[107]);



   /* dATP1_Eqn */
   X_t44[cell] = (- ( ( CONSTANTS[78]*X29[cell])*X44[cell]+ - CONSTANTS[79]*X40[cell])+- ( ( CONSTANTS[80]*X46[cell])*X44[cell]+ - CONSTANTS[81]*X42[cell]))+ - CONSTANTS[82]*((X44[cell]+- X45[cell])/CONSTANTS[106]);



   /* dATP2_Eqn */
   X_t45[cell] = (- ( ( CONSTANTS[78]*X31[cell])*X45[cell]+ - CONSTANTS[79]*X41[cell])+- ( ( CONSTANTS[80]*X47[cell])*X45[cell]+ - CONSTANTS[81]*X43[cell]))+ CONSTANTS[82]*((X44[cell]+- X45[cell])/CONSTANTS[107]);



   /* dMg1_Eqn */
   X_t46[cell] = (- ( ( CONSTANTS[73]*(CONSTANTS[72]+- X34[cell]+- X36[cell]))*X46[cell]+ - CONSTANTS[74]*X36[cell])+- ( ( CONSTANTS[80]*X46[cell])*X44[cell]+ - CONSTANTS[81]*X42[cell]))+ - CONSTANTS[83]*((X46[cell]+- X47[cell])/CONSTANTS[106]);



   /*dMg2_Eqn */
   X_t47[cell]= (- ( ( CONSTANTS[73]*(CONSTANTS[72]+- X35[cell]+- X37[cell]))*X47[cell]+ - CONSTANTS[74]*X37[cell])+- ( ( CONSTANTS[80]*X47[cell])*X45[cell]+ - CONSTANTS[81]*X43[cell]))+ CONSTANTS[83]*((X46[cell]+- X47[cell])/CONSTANTS[107]);



   /* dCa_CaT2_Eqn */
   X_t48[cell] = (( ( CONSTANTS[67]*X31[cell])*X33[cell]+ - CONSTANTS[68]*X48[cell])+ - CONSTANTS[86]*X48[cell])+ CONSTANTS[87]*X51[cell];



   /* dD_1_Eqn */
   X_t50[cell] = (((( CONSTANTS[67]*X31[cell]*X49[cell]+ - CONSTANTS[68]*X50[cell])+ CONSTANTS[84]*X33[cell])+ - CONSTANTS[85]*X50[cell])+ ( - CONSTANTS[67]*X31[cell])*X50[cell])+ CONSTANTS[68]*X51[cell];



   /* dD_2_Eqn */
   X_t51[cell] = ((((( CONSTANTS[67]*X31[cell]*X50[cell]+ - CONSTANTS[68]*X51[cell])+ CONSTANTS[86]*X48[cell])+ - CONSTANTS[87]*X51[cell])+ - CONSTANTS[88]*X51[cell])+ CONSTANTS[89]*X52[cell])+ CONSTANTS[92]*X53[cell];



   /* dA_1_Eqn */
   X_t52[cell] = (( CONSTANTS[88]*X51[cell]+ - CONSTANTS[89]*X52[cell])+ CONSTANTS[91]*X53[cell])+ - CONSTANTS[90]*X52[cell];



   /* dA_2_Eqn */
   X_t53[cell] = ( - CONSTANTS[91]*X53[cell]+ CONSTANTS[90]*X52[cell])+ - CONSTANTS[92]*X53[cell];



   /* dP_Eqn */
   X_t54[cell] =  (0.00100000/1.00000)*( CONSTANTS[90]*X52[cell] -  CONSTANTS[91]*X53[cell])+ -1.00000*CONSTANTS[93]*X54[cell]+ -1.00000*CONSTANTS[94]*((X54[cell] - X55[cell])/CONSTANTS[107]);



   /* dP_SR_Eqn */
   X_t55[cell] =  CONSTANTS[94]*((X54[cell] - X55[cell])/CONSTANTS[109]) -  1.00000*( CONSTANTS[95]*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97])*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*X55[cell]*X32[cell] -  CONSTANTS[96]*X56[cell]*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell])*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell]>0.00000 ? 1.00000 : 0.00000));



   /* dP_C_SR_Eqn */
   X_t56[cell] =  1.00000*( CONSTANTS[95]*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97])*( X55[cell]*(0.00100000/1.00000)*X32[cell] - CONSTANTS[97]>0.00000 ? 1.00000 : 0.00000)*(0.00100000/1.00000)*X55[cell]*X32[cell] -  CONSTANTS[96]*X56[cell]*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell])*(CONSTANTS[97] -  X55[cell]*(0.00100000/1.00000)*X32[cell]>0.00000 ? 1.00000 : 0.00000));



   /* T_0_Eqn */
   TMP12[cell] = (CONSTANTS[69]+- X33[cell]+- X48[cell]+- X49[cell]+- X50[cell]+- X51[cell]+- X52[cell]+- X53[cell]>0.00000 ? CONSTANTS[69]+- X33[cell]+- X48[cell]+- X49[cell]+- X50[cell]+- X51[cell]+- X52[cell]+- X53[cell] : 0.00000);



   /* dCa2_Eqn */
   X_t31[cell] = (((( - CONSTANTS[60]*((X31[cell]/(X31[cell]+CONSTANTS[61]))/CONSTANTS[107])+ CONSTANTS[62]*((X32[cell]+- X31[cell])/CONSTANTS[107]))+ CONSTANTS[63]*((X29[cell] - X31[cell])/CONSTANTS[107]))+- ((((((( CONSTANTS[67]*X31[cell]*TMP12[cell]+ - CONSTANTS[68]*X33[cell])+ CONSTANTS[67]*X31[cell]*X33[cell])+ - CONSTANTS[68]*X48[cell])+ CONSTANTS[67]*X31[cell]*X49[cell])+ - CONSTANTS[68]*X50[cell])+ CONSTANTS[67]*X31[cell]*X50[cell])+ - CONSTANTS[68]*X51[cell]))+- ( ( CONSTANTS[70]*X31[cell])*(CONSTANTS[72]+- X35[cell]+- X37[cell])+ - CONSTANTS[71]*X35[cell]))+- ( ( CONSTANTS[78]*X31[cell])*X45[cell]+ - CONSTANTS[79]*X41[cell]);



   /* dCa_T_2_Eqn */
   X_t33[cell] = (((( ( CONSTANTS[67]*X31[cell])*TMP12[cell]+ - CONSTANTS[68]*X33[cell])+ ( - CONSTANTS[67]*X31[cell])*X33[cell])+ CONSTANTS[68]*X48[cell])+ - CONSTANTS[84]*X33[cell])+ CONSTANTS[85]*X50[cell];



   /* dD_0_Eqn */
   X_t49[cell] = (( ( - CONSTANTS[67]*X31[cell])*X49[cell]+ CONSTANTS[68]*X50[cell])+ CONSTANTS[84]*TMP12[cell])+ - CONSTANTS[85]*X49[cell];



   /* stress_Eqn  wie im paper gamma = Xi * (A - Amin)/(Amax-Amin) */
   Gamma[cell] =  (  X53[cell] - CONSTANTS[101])/(CONSTANTS[102]-CONSTANTS[101])*(L_hs[cell]>=0.635000&&L_hs[cell]<=0.850000 ?  (0.700000/(0.850000 - 0.635000))*(L_hs[cell] - 0.635000) : L_hs[cell]>0.850000&&L_hs[cell]<=1.17000 ? 0.700000+ (0.300000/(1.17000 - 0.850000))*(L_hs[cell] - 0.850000) : L_hs[cell]>1.17000&&L_hs[cell]<=1.25500 ? 1.00000 : L_hs[cell]>1.25500&&L_hs[cell]<=1.97000 ? 1.00000 -  (1.00000/(1.97000 - 1.25500))*(L_hs[cell] - 1.25500) : 0.00000);



   /* dummy_Eqn */
   X_t28[cell] = Gamma[cell];



   /* alpha_n_Eqn */
   TMP1[cell] =  CONSTANTS[16]*((X0[cell] - CONSTANTS[21])/(1.00000 - exp(- ((X0[cell] - CONSTANTS[21])/CONSTANTS[32]))));



   /* beta_n_Eqn */
   TMP14[cell] =  CONSTANTS[19]*exp(- ((X0[cell] - CONSTANTS[21])/CONSTANTS[34]));



   /* dn_Eqn */
   X_t8[cell] =  TMP1[cell]*(1.00000 - X8[cell]) -  TMP14[cell]*X8[cell];



   /* h_K_inf_Eqn */
   TMP2[cell] = 1.00000/(1.00000+exp((X0[cell] - CONSTANTS[25])/CONSTANTS[28]));

/* To investigate the effect of vectorizing these "micro-kernels" we have a look on two exemplary different kinds of loops.
 * 
 * One with constants (all vector elements muultiplied with a common scalar value.)
 * One with ONLY vectors.
 * 
 * We take the two following ones.
 * 
 *  fun() needs to be commented to vectorize at compile time. For the time measureing there's a bit of alias, however..
*/
 // handle_array[8]=clock();


   /* tau_h_K_Eqn */
   TMP15[cell] =  1000.00*exp(- ((X0[cell]+40.0000)/25.7500));
   //fun(TMP15,cell);

 // handle_array[9]=clock();


   /* dh_K_Eqn */
   X_t9[cell] = (TMP2[cell] - X9[cell])/TMP15[cell];

 // handle_array[10]=clock();
  // time of exemplary loop with constants
 // portions_array[5] += ((double) (handle_array[9]-handle_array[8])) / CLOCKS_PER_SEC;
  // time of exemplary loop without constants
 // portions_array[6] += ((double) (handle_array[10]-handle_array[9])) / CLOCKS_PER_SEC;


   /* alpha_m_Eqn */
   TMP4[cell] =  CONSTANTS[15]*((X0[cell] - CONSTANTS[20])/(1.00000 - exp(- ((X0[cell] - CONSTANTS[20])/CONSTANTS[31]))));



   /* beta_m_Eqn */
   TMP17[cell] =  CONSTANTS[18]*exp(- ((X0[cell] - CONSTANTS[20])/CONSTANTS[33]));



   /* dm_Eqn */
   X_t10[cell] =  TMP4[cell]*(1.00000 - X10[cell]) -  TMP17[cell]*X10[cell];



   /* alpha_h_Eqn */
   TMP3[cell] =  CONSTANTS[14]*exp(- ((X0[cell] - CONSTANTS[22])/CONSTANTS[29]));



   /* beta_h_Eqn */
   TMP16[cell] = CONSTANTS[17]/(1.00000+exp(- ((X0[cell] - CONSTANTS[22])/CONSTANTS[30])));



   /* dh_Eqn */
   X_t11[cell] =  TMP3[cell]*(1.00000 - X11[cell]) -  TMP16[cell]*X11[cell];



   /* S_inf_Eqn */
   TMP5[cell] = 1.00000/(1.00000+exp((X0[cell] - CONSTANTS[24])/CONSTANTS[27]));



   /* tau_S_Eqn */
   TMP18[cell] = 8571.00/(0.200000+ 5.65000*pow((X0[cell]+CONSTANTS[48])/100.000, 2.00000));



   /* dS_Eqn */
   X_t12[cell] = (TMP5[cell] - X12[cell])/TMP18[cell];



   /* alpha_n_t_Eqn */
   TMP6[cell] =  CONSTANTS[16]*((X1[cell] - CONSTANTS[21])/(1.00000 - exp(- ((X1[cell] - CONSTANTS[21])/CONSTANTS[32]))));



   /* beta_n_t_Eqn */
   TMP19[cell] =  CONSTANTS[19]*exp(- ((X1[cell] - CONSTANTS[21])/CONSTANTS[34]));



   /* dn_t_Eqn */
   X_t13[cell] =  TMP6[cell]*(1.00000 - X13[cell]) -  TMP19[cell]*X13[cell];



   /* h_K_inf_t_Eqn */
   TMP7[cell] = 1.00000/(1.00000+exp((X1[cell] - CONSTANTS[25])/CONSTANTS[28]));



   /* tau_h_K_t_Eqn */
   TMP20[cell] =  1.00000*exp(- ((X1[cell]+40.0000)/25.7500));



   /* dh_K_t_Eqn */
   X_t14[cell] = (TMP7[cell] - X14[cell])/TMP20[cell];



   /* alpha_m_t_Eqn */
   TMP9[cell] =  CONSTANTS[15]*((X1[cell] - CONSTANTS[20])/(1.00000 - exp(- ((X1[cell] - CONSTANTS[20])/CONSTANTS[31]))));



   /* beta_m_t_Eqn */
   TMP22[cell] =  CONSTANTS[18]*exp(- ((X1[cell] - CONSTANTS[20])/CONSTANTS[33]));



   /* dm_t_Eqn */
   X_t15[cell] =  TMP9[cell]*(1.00000 - X15[cell]) -  TMP22[cell]*X15[cell];



   /* alpha_h_t_Eqn */
   TMP8[cell] =  CONSTANTS[14]*exp(- ((X1[cell] - CONSTANTS[22])/CONSTANTS[29]));



   /* beta_h_t_Eqn */
   TMP21[cell] = CONSTANTS[17]/(1.00000+exp(- ((X1[cell] - CONSTANTS[22])/CONSTANTS[30])));



   /* dh_t_Eqn */
   X_t16[cell] =  TMP8[cell]*(1.00000 - X16[cell]) -  TMP21[cell]*X16[cell];



   /* S_inf_t_Eqn */
   TMP10[cell] = 1.00000/(1.00000+exp((X1[cell] - CONSTANTS[24])/CONSTANTS[27]));



   /* tau_S_t_Eqn */
   TMP23[cell] = 8571.00/(0.200000+ 5.65000*pow((X1[cell]+CONSTANTS[48])/100.000, 2.00000));



   /* dS_t_Eqn */
   X_t17[cell] = (TMP10[cell] - X17[cell])/TMP23[cell];



   /* k_C_Eqn */
   TMP11[cell] =  0.500000*CONSTANTS[57]*exp((X1[cell] - CONSTANTS[59])/( 8.00000*CONSTANTS[58]));



   /* k_Cm_Eqn */
   TMP24[cell] =  0.500000*CONSTANTS[57]*exp((CONSTANTS[59] - X1[cell])/( 8.00000*CONSTANTS[58]));



   /* dC_0_Eqn */
   X_t23[cell] =  - CONSTANTS[54]*X23[cell]+ CONSTANTS[55]*X18[cell]+ -4.00000*TMP11[cell]*X23[cell]+ TMP24[cell]*X24[cell];



   /* dO_0_Eqn */
   X_t18[cell] =  CONSTANTS[54]*X23[cell]+ - CONSTANTS[55]*X18[cell]+( -4.00000*TMP11[cell]*X18[cell])/CONSTANTS[56]+ CONSTANTS[56]*TMP24[cell]*X19[cell];



   /* dC_1_Eqn */
   X_t24[cell] =  4.00000*TMP11[cell]*X23[cell]+ - TMP24[cell]*X24[cell]+( - CONSTANTS[54]*X24[cell])/CONSTANTS[56]+ CONSTANTS[56]*CONSTANTS[55]*X19[cell]+ -3.00000*TMP11[cell]*X24[cell]+ 2.00000*TMP24[cell]*X25[cell];



   /* dO_1_Eqn */
   X_t19[cell] = ( CONSTANTS[54]*X24[cell])/CONSTANTS[56]+ - CONSTANTS[55]*CONSTANTS[56]*X19[cell]+( 4.00000*TMP11[cell]*X18[cell])/CONSTANTS[56]+ - CONSTANTS[56]*TMP24[cell]*X19[cell]+( -3.00000*TMP11[cell]*X19[cell])/CONSTANTS[56]+ 2.00000*CONSTANTS[56]*TMP24[cell]*X20[cell];



   /* dC_2_Eqn */
   X_t25[cell] =  3.00000*TMP11[cell]*X24[cell]+ -2.00000*TMP24[cell]*X25[cell]+( - CONSTANTS[54]*X25[cell])/pow(CONSTANTS[56], 2.00000)+ pow(CONSTANTS[56], 2.00000)*CONSTANTS[55]*X20[cell]+ -2.00000*TMP11[cell]*X25[cell]+ 3.00000*TMP24[cell]*X26[cell];



   /* dO_2_Eqn */
   X_t20[cell] = ( 3.00000*TMP11[cell]*X19[cell])/CONSTANTS[56]+ -2.00000*CONSTANTS[56]*TMP24[cell]*X20[cell]+( CONSTANTS[54]*X25[cell])/pow(CONSTANTS[56], 2.00000)+ - CONSTANTS[55]*pow(CONSTANTS[56], 2.00000)*X20[cell]+( -2.00000*TMP11[cell]*X20[cell])/CONSTANTS[56]+ 3.00000*CONSTANTS[56]*TMP24[cell]*X21[cell];



   /* dC_3_Eqn */
   X_t26[cell] =  2.00000*TMP11[cell]*X25[cell]+ -3.00000*TMP24[cell]*X26[cell]+( - CONSTANTS[54]*X26[cell])/pow(CONSTANTS[56], 3.00000)+ CONSTANTS[55]*pow(CONSTANTS[56], 3.00000)*X21[cell]+ - TMP11[cell]*X26[cell]+ 4.00000*TMP24[cell]*X27[cell];



   /* dO_3_Eqn */
   X_t21[cell] = ( CONSTANTS[54]*X26[cell])/pow(CONSTANTS[56], 3.00000)+ - CONSTANTS[55]*pow(CONSTANTS[56], 3.00000)*X21[cell]+( 2.00000*TMP11[cell]*X20[cell])/CONSTANTS[56]+ -3.00000*TMP24[cell]*CONSTANTS[56]*X21[cell]+( - TMP11[cell]*X21[cell])/CONSTANTS[56]+ 4.00000*CONSTANTS[56]*TMP24[cell]*X22[cell];



   /* dC_4_Eqn */
   X_t27[cell] =  TMP11[cell]*X26[cell]+ -4.00000*TMP24[cell]*X27[cell]+( - CONSTANTS[54]*X27[cell])/pow(CONSTANTS[56], 4.00000)+ CONSTANTS[55]*pow(CONSTANTS[56], 4.00000)*X22[cell];



   /* dO_4_Eqn */
   X_t22[cell] = ( TMP11[cell]*X21[cell])/CONSTANTS[56]+ -4.00000*CONSTANTS[56]*TMP24[cell]*X22[cell]+( CONSTANTS[54]*X27[cell])/pow(CONSTANTS[56], 4.00000)+ - CONSTANTS[55]*pow(CONSTANTS[56], 4.00000)*X22[cell];



   /* J_K_eqn */
   TMP30[cell] =  X0[cell]*((X3[cell] -  X4[cell]*exp(( -1.00000*CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* E_K_eqn */
   TMP13[cell] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(X4[cell]/X3[cell]);



   /* K_R_Eqn */
   TMP36[cell] =  X4[cell]*exp( ( - CONSTANTS[41]*TMP13[cell])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));



   /* g_IR_bar_Eqn */
   TMP37[cell] =  CONSTANTS[40]*(pow(TMP36[cell], 2.00000)/(CONSTANTS[42]+pow(TMP36[cell], 2.00000)));



   /* y_Eqn */
   TMP38[cell] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(TMP36[cell], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*X0[cell]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);



   /* g_IR_Eqn */
   TMP39[cell] =  TMP37[cell]*TMP38[cell];



   /* I_IR_Eqn */
   TMP40[cell] =  TMP39[cell]*(TMP30[cell]>0.00000 ? 1.00000 : 0.00000)*(TMP30[cell]/50.0000);



   /* g_DR_Eqn */
   TMP41[cell] =  ( CONSTANTS[38]*pow(X8[cell], 4.00000))*X9[cell];



   /* I_DR_Eqn */
   TMP42[cell] =  TMP41[cell]*(TMP30[cell]/50.0000);



   /* sig_Eqn */
   TMP46[cell] =  (1.00000/7.00000)*(exp(X7[cell]/67.3000) - 1.00000);



   /* f1_Eqn */
   TMP47[cell] = pow(1.00000+ 0.120000*exp( -0.100000*X0[cell]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*TMP46[cell]*exp(- ( X0[cell]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);



   /* I_NaK_bar_Eqn */
   TMP48[cell] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/X4[cell], 2.00000)*pow(1.00000+CONSTANTS[45]/X5[cell], 3.00000)));



   /* I_NaK_Eqn */
   TMP49[cell] =  TMP48[cell]*TMP47[cell];



   /* dK_e_Eqn */
   X_t4[cell] = (TMP40[cell]+TMP42[cell]+CONSTANTS[12]+ - 2.00000*TMP49[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(X2[cell] - X4[cell])/CONSTANTS[10];



   /* g_Na_Eqn */
   TMP44[cell] =  ( ( CONSTANTS[39]*pow(X10[cell], 3.00000))*X11[cell])*X12[cell];



   /* J_Na_eqn */
   TMP43[cell] =  X0[cell]*((X5[cell] -  X7[cell]*exp(( -1.00000*CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* I_Na_Eqn */
   TMP45[cell] =  TMP44[cell]*(TMP43[cell]/75.0000);



   /* dNa_e_Eqn */
   X_t7[cell] = (TMP45[cell]+CONSTANTS[13]+ 3.00000*TMP49[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[5])+(X6[cell] - X7[cell])/CONSTANTS[11];



   /* I_T_Eqn */
   TMP0[cell] =  (1000.00/1.00000)*((X0[cell] - X1[cell])/CONSTANTS[2]);



   /* Cl_i_eqn */
   TMP26[cell] = 156.500/(5.00000+exp(( - CONSTANTS[6]*TMP13[cell])/( CONSTANTS[35]*CONSTANTS[36])));



   /* Cl_o_eqn */
   TMP27[cell] = 156.500 -  5.00000*TMP26[cell];



   /* J_Cl_eqn */
   TMP33[cell] =  X0[cell]*((TMP26[cell] -  TMP27[cell]*exp(( CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*X0[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* a_Eqn */
   TMP32[cell] = 1.00000/(1.00000+exp((X0[cell] - CONSTANTS[23])/CONSTANTS[26]));



   /* g_Cl_Eqn */
   TMP34[cell] =  CONSTANTS[37]*pow(TMP32[cell], 4.00000);



   /* I_Cl_Eqn */
   TMP35[cell] =  TMP34[cell]*(TMP33[cell]/45.0000);



   /* I_ionic_s_Eqn */
   TMP50[cell] = TMP35[cell]+TMP40[cell]+TMP42[cell]+TMP45[cell]+TMP49[cell]+- StimValue[cell];



   /* vS_diff_calculation */
   X_t0[cell] = - ((TMP50[cell]+TMP0[cell])/CONSTANTS[0]);



   /* J_K_t_eqn */
   TMP31[cell] =  X1[cell]*((X3[cell] -  X2[cell]*exp(( -1.00000*CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* E_K_t_eqn */
   TMP25[cell] =  (( CONSTANTS[35]*CONSTANTS[36])/CONSTANTS[6])*log(X2[cell]/X3[cell]);



   /* K_R_t_Eqn */
   TMP55[cell] =  X2[cell]*exp( ( - CONSTANTS[41]*TMP25[cell])*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])));



   /* g_IR_bar_t_Eqn */
   TMP56[cell] =  CONSTANTS[40]*(pow(TMP55[cell], 2.00000)/(CONSTANTS[42]+pow(TMP55[cell], 2.00000)));



   /* y_t_Eqn */
   TMP57[cell] = 1.00000 - pow(1.00000+( CONSTANTS[43]*(1.00000+pow(TMP55[cell], 2.00000)/CONSTANTS[42]))/( pow(CONSTANTS[46], 2.00000)*exp(( 2.00000*(1.00000 - CONSTANTS[41])*X1[cell]*CONSTANTS[6])/( CONSTANTS[35]*CONSTANTS[36]))), -1.00000);



   /* g_IR_t_Eqn */
   TMP58[cell] =  TMP56[cell]*TMP57[cell];



   /* I_IR_t_Eqn */
   TMP59[cell] =  CONSTANTS[50]*TMP58[cell]*(TMP31[cell]/50.0000);



   /* g_DR_t_Eqn */
   TMP60[cell] =  ( CONSTANTS[38]*pow(X13[cell], 4.00000))*X14[cell];



   /* I_DR_t_Eqn */
   TMP61[cell] =  CONSTANTS[51]*TMP60[cell]*(TMP31[cell]/50.0000);



   /* sig_t_Eqn */
   TMP65[cell] =  (1.00000/7.00000)*(exp(X6[cell]/67.3000) - 1.00000);



   /* f1_t_Eqn */
   TMP66[cell] = pow(1.00000+ 0.120000*exp( -0.100000*X1[cell]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))+ 0.0400000*TMP65[cell]*exp(- ( X1[cell]*(CONSTANTS[6]/( CONSTANTS[35]*CONSTANTS[36])))), -1.00000);



   /* I_NaK_bar_t_Eqn */
   TMP67[cell] =  CONSTANTS[6]*(CONSTANTS[47]/( pow(1.00000+CONSTANTS[44]/X2[cell], 2.00000)*pow(1.00000+CONSTANTS[45]/X5[cell], 3.00000)));



   /* I_NaK_t_Eqn */
   TMP68[cell] =  CONSTANTS[53]*TMP67[cell]*TMP66[cell];



   /* dK_i_Eqn */
   X_t3[cell] =  - CONSTANTS[9]*((TMP59[cell]+TMP61[cell]+CONSTANTS[12]+ - 2.00000*TMP68[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (TMP40[cell]+TMP42[cell]+CONSTANTS[12]+ -2.00000*TMP49[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);



   /* dK_t_Eqn */
   X_t2[cell] = (TMP59[cell]+TMP61[cell]+CONSTANTS[12]+ - 2.00000*TMP68[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (X2[cell] - X4[cell])/CONSTANTS[7];



   /* g_Na_t_Eqn */
   TMP63[cell] =  ( ( CONSTANTS[39]*pow(X15[cell], 3.00000))*X16[cell])*X17[cell];



   /* J_Na_t_eqn */
   TMP62[cell] =  X1[cell]*((X5[cell] -  X6[cell]*exp(( -1.00000*CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( -1.00000*CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* I_Na_t_Eqn */
   TMP64[cell] =  CONSTANTS[52]*TMP63[cell]*(TMP62[cell]/75.0000);



   /* dNa_i_Eqn */
   X_t5[cell] =  - CONSTANTS[9]*((TMP64[cell]+CONSTANTS[13]+ 3.00000*TMP68[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3])) - (TMP45[cell]+CONSTANTS[13]+ 3.00000*TMP49[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[4]);



   /* dNa_t_Eqn */
   X_t6[cell] = (TMP64[cell]+CONSTANTS[13]+ 3.00000*TMP68[cell])/( (1000.00/1.00000)*CONSTANTS[6]*CONSTANTS[3]) - (X6[cell] - X7[cell])/CONSTANTS[8];



   /* Cl_i_t_eqn */
   TMP28[cell] = 156.500/(5.00000+exp(( - CONSTANTS[6]*TMP25[cell])/( CONSTANTS[35]*CONSTANTS[36])));



   /* Cl_o_t_eqn */
   TMP29[cell] = 156.500 -  5.00000*TMP28[cell];



   /* J_Cl_t_eqn */
   TMP52[cell] =  X1[cell]*((TMP28[cell] -  TMP29[cell]*exp(( CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36])))/(1.00000 - exp(( CONSTANTS[6]*X1[cell])/( CONSTANTS[35]*CONSTANTS[36]))));



   /* a_t_Eqn */
   TMP51[cell] = 1.00000/(1.00000+exp((X1[cell] - CONSTANTS[23])/CONSTANTS[26]));



   /* g_Cl_t_Eqn */
   TMP53[cell] =  CONSTANTS[37]*pow(TMP51[cell], 4.00000);



   /* I_Cl_t_Eqn */
   TMP54[cell] =  CONSTANTS[49]*TMP53[cell]*(TMP52[cell]/45.0000);



   /* I_ionic_t_Eqn */
   TMP69[cell] = TMP54[cell]+TMP59[cell]+TMP61[cell]+TMP64[cell]+TMP68[cell];



   /* dvT_Eqn */
   X_t1[cell] = - ((TMP69[cell] - TMP0[cell]/CONSTANTS[1])/CONSTANTS[0]);
}// end for cell
  handle_array[3]=clock();
  // time to evaluate RHS (excludes set up of constants)
  portions_array[4] += ((double) (handle_array[3]-handle_array[4])) / CLOCKS_PER_SEC;

}//RHS_routineForAVX()
;