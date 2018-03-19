#include <time.h> 
#include <stdlib.h> // sonst Fehler: "error: dereferencing pointer to incomplete type ‘struct timeval’ \n   if (x->tv_usec < y->tv_usec) {"
//#include "numerics.h"
#include "RHS_routine.h"

   int forwardEulerForAVX(double timeSpan, int Ksteps,
                      double* state0, double* state1, double* state2, double* state3, double* state4, double* state5, double* state6, double* state7, double* state8, double* state9,
                      double* state10,double* state11,double* state12,double* state13,double* state14,double* state15,double* state16,double* state17,double* state18,double* state19,
                      double* state20,double* state21,double* state22,double* state23,double* state24,double* state25,double* state26,double* state27,double* state28,double* state29,
                      double* state30,double* state31,double* state32,double* state33,double* state34,double* state35,double* state36,double* state37,double* state38,double* state39,
                      double* state40,double* state41,double* state42,double* state43,double* state44,double* state45,double* state46,double* state47,double* state48,double* state49,
                      double* state50,double* state51,double* state52,double* state53,double* state54,double* state55,double* state56,
                      double* rate0, double* rate1, double* rate2, double* rate3, double* rate4, double* rate5, double* rate6, double* rate7, double* rate8, double* rate9,
                      double* rate10,double* rate11,double* rate12,double* rate13,double* rate14,double* rate15,double* rate16,double* rate17,double* rate18,double* rate19,
                      double* rate20,double* rate21,double* rate22,double* rate23,double* rate24,double* rate25,double* rate26,double* rate27,double* rate28,double* rate29,
                      double* rate30,double* rate31,double* rate32,double* rate33,double* rate34,double* rate35,double* rate36,double* rate37,double* rate38,double* rate39,
                      double* rate40,double* rate41,double* rate42,double* rate43,double* rate44,double* rate45,double* rate46,double* rate47,double* rate48,double* rate49,
                      double* rate50,double* rate51,double* rate52,double* rate53,double* rate54,double* rate55,double* rate56,
                      double* gamma_OutFromRhs, double* StimValue_INtoRHS,  double* L_hs_INtoRHS, int NumberOfCells, clock_t * handle_array, double * portions_array){
   double dt_0D;
   int k;
   int cell;
   
   if (Ksteps == 0){
     dt_0D = timeSpan /5;
   }
   else{
     dt_0D = timeSpan / Ksteps;
   }
   handle_array[0]=clock();
   for(k=1; k<=Ksteps; k++){
      RHS_routineForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                        state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                        state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,state50,state51,state52,state53,state54,state55,state56,NumberOfCells,
                        rate0, rate1, rate2, rate3, rate4, rate5, rate6, rate7, rate8, rate9, rate10,rate11,rate12,rate13,rate14,rate15,rate16,rate17,rate18,rate19,
                        rate20,rate21,rate22,rate23,rate24,rate25,rate26,rate27,rate28,rate29,rate30,rate31,rate32,rate33,rate34,rate35,rate36,rate37,rate38,rate39,
                        rate40,rate41,rate42,rate43,rate44,rate45,rate46,rate47,rate48,rate49,rate50,rate51,rate52,rate53,rate54,rate55,rate56,
                        gamma_OutFromRhs,StimValue_INtoRHS,L_hs_INtoRHS, handle_array, portions_array);
      handle_array[1]=clock();  
#pragma GCC ivdep     // needed, otherwise not vectorized
      for(cell=1; cell<=NumberOfCells; cell++){ /* step forward*/
         state0[cell] = state0[cell] + dt_0D * rate0[cell];
         state1[cell] = state1[cell] + dt_0D * rate1[cell];
         state2[cell] = state2[cell] + dt_0D * rate2[cell];
         state3[cell] = state3[cell] + dt_0D * rate3[cell];
         state4[cell] = state4[cell] + dt_0D * rate4[cell];
         state5[cell] = state5[cell] + dt_0D * rate5[cell];
         state6[cell] = state6[cell] + dt_0D * rate6[cell];
         state7[cell] = state7[cell] + dt_0D * rate7[cell];
         state8[cell] = state8[cell] + dt_0D * rate8[cell];
         state9[cell] = state9[cell] + dt_0D * rate9[cell];
         state10[cell] = state10[cell] + dt_0D * rate10[cell];
         state11[cell] = state11[cell] + dt_0D * rate11[cell];
         state12[cell] = state12[cell] + dt_0D * rate12[cell];
         state13[cell] = state13[cell] + dt_0D * rate13[cell];
         state14[cell] = state14[cell] + dt_0D * rate14[cell];
         state15[cell] = state15[cell] + dt_0D * rate15[cell];
         state16[cell] = state16[cell] + dt_0D * rate16[cell];
         state17[cell] = state17[cell] + dt_0D * rate17[cell];
         state18[cell] = state18[cell] + dt_0D * rate18[cell];
         state19[cell] = state19[cell] + dt_0D * rate19[cell];
         state20[cell] = state20[cell] + dt_0D * rate20[cell];
         state21[cell] = state21[cell] + dt_0D * rate21[cell];
         state22[cell] = state22[cell] + dt_0D * rate22[cell];
         state23[cell] = state23[cell] + dt_0D * rate23[cell];
         state24[cell] = state24[cell] + dt_0D * rate24[cell];
         state25[cell] = state25[cell] + dt_0D * rate25[cell];
         state26[cell] = state26[cell] + dt_0D * rate26[cell];
         state27[cell] = state27[cell] + dt_0D * rate27[cell];
         //state28[cell] = state28[cell] + dt_0D * rate28[cell]; dummy variable
         state29[cell] = state29[cell] + dt_0D * rate29[cell];
         state30[cell] = state30[cell] + dt_0D * rate30[cell];
         state31[cell] = state31[cell] + dt_0D * rate31[cell];
         state32[cell] = state32[cell] + dt_0D * rate32[cell];
         state33[cell] = state33[cell] + dt_0D * rate33[cell];
         state34[cell] = state34[cell] + dt_0D * rate34[cell];
         state35[cell] = state35[cell] + dt_0D * rate35[cell];
         state36[cell] = state36[cell] + dt_0D * rate36[cell];
         state37[cell] = state37[cell] + dt_0D * rate37[cell];
         state38[cell] = state38[cell] + dt_0D * rate38[cell];
         state39[cell] = state39[cell] + dt_0D * rate39[cell];
         state40[cell] = state40[cell] + dt_0D * rate40[cell];
         state41[cell] = state41[cell] + dt_0D * rate41[cell];
         state42[cell] = state42[cell] + dt_0D * rate42[cell];
         state43[cell] = state43[cell] + dt_0D * rate43[cell];
         state44[cell] = state44[cell] + dt_0D * rate44[cell];
         state45[cell] = state45[cell] + dt_0D * rate45[cell];
         state46[cell] = state46[cell] + dt_0D * rate46[cell];
         state47[cell] = state47[cell] + dt_0D * rate47[cell];
         state48[cell] = state48[cell] + dt_0D * rate48[cell];
         state49[cell] = state49[cell] + dt_0D * rate49[cell];
         state50[cell] = state50[cell] + dt_0D * rate50[cell];
         state51[cell] = state51[cell] + dt_0D * rate51[cell];
         state52[cell] = state52[cell] + dt_0D * rate52[cell];
         state53[cell] = state53[cell] + dt_0D * rate53[cell];
         state54[cell] = state54[cell] + dt_0D * rate54[cell];
         state55[cell] = state55[cell] + dt_0D * rate55[cell];
         state56[cell] = state56[cell] + dt_0D * rate56[cell];
      }  
      handle_array[2]=clock();
      // time to actualize states:
      portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
   }
   handle_array[1]=clock();
   RHS_routineForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                     state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                     state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,state50,state51,state52,state53,state54,state55,state56,NumberOfCells,
                     rate0, rate1, rate2, rate3, rate4, rate5, rate6, rate7, rate8, rate9, rate10,rate11,rate12,rate13,rate14,rate15,rate16,rate17,rate18,rate19,
                     rate20,rate21,rate22,rate23,rate24,rate25,rate26,rate27,rate28,rate29,rate30,rate31,rate32,rate33,rate34,rate35,rate36,rate37,rate38,rate39,
                     rate40,rate41,rate42,rate43,rate44,rate45,rate46,rate47,rate48,rate49,rate50,rate51,rate52,rate53,rate54,rate55,rate56,
                     gamma_OutFromRhs,StimValue_INtoRHS,L_hs_INtoRHS,handle_array,portions_array);
   handle_array[2]=clock();
   // time to do the whole Euler integration: (Thus, [0] includes [2].)
   portions_array[0] += ((double) (handle_array[1]-handle_array[0])) / CLOCKS_PER_SEC;
   // time to compute L_hs after numerical integration:
   portions_array[1] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
  return 0;
 }
 
int improvedEulerForAVX(double timeSpan, int Ksteps,
                      double* state0, double* state1, double* state2, double* state3, double* state4, double* state5, double* state6, double* state7, double* state8, double* state9,
                      double* state10,double* state11,double* state12,double* state13,double* state14,double* state15,double* state16,double* state17,double* state18,double* state19,
                      double* state20,double* state21,double* state22,double* state23,double* state24,double* state25,double* state26,double* state27,double* state28,double* state29,
                      double* state30,double* state31,double* state32,double* state33,double* state34,double* state35,double* state36,double* state37,double* state38,double* state39,
                      double* state40,double* state41,double* state42,double* state43,double* state44,double* state45,double* state46,double* state47,double* state48,double* state49,
                      double* state50,double* state51,double* state52,double* state53,double* state54,double* state55,double* state56,
                      double* rate0, double* rate1, double* rate2, double* rate3, double* rate4, double* rate5, double* rate6, double* rate7, double* rate8, double* rate9,
                      double* rate10,double* rate11,double* rate12,double* rate13,double* rate14,double* rate15,double* rate16,double* rate17,double* rate18,double* rate19,
                      double* rate20,double* rate21,double* rate22,double* rate23,double* rate24,double* rate25,double* rate26,double* rate27,double* rate28,double* rate29,
                      double* rate30,double* rate31,double* rate32,double* rate33,double* rate34,double* rate35,double* rate36,double* rate37,double* rate38,double* rate39,
                      double* rate40,double* rate41,double* rate42,double* rate43,double* rate44,double* rate45,double* rate46,double* rate47,double* rate48,double* rate49,
                      double* rate50,double* rate51,double* rate52,double* rate53,double* rate54,double* rate55,double* rate56,
                      double* gamma_OutFromRhs, double* StimValue_INtoRHS,  double* L_hs_INtoRHS, int NumberOfCells, clock_t * handle_array, double * portions_array){
   double dt_0D;
   int k;
   int cell;
   double stateCopy_0[NumberOfCells],  stateCopy_1[NumberOfCells],  stateCopy_2[NumberOfCells],  stateCopy_3[NumberOfCells],  stateCopy_4[NumberOfCells],  stateCopy_5[NumberOfCells],  stateCopy_6[NumberOfCells],  stateCopy_7[NumberOfCells],  stateCopy_8[NumberOfCells],  stateCopy_9[NumberOfCells],
          stateCopy_10[NumberOfCells], stateCopy_11[NumberOfCells], stateCopy_12[NumberOfCells], stateCopy_13[NumberOfCells], stateCopy_14[NumberOfCells], stateCopy_15[NumberOfCells], stateCopy_16[NumberOfCells], stateCopy_17[NumberOfCells], stateCopy_18[NumberOfCells], stateCopy_19[NumberOfCells],
          stateCopy_20[NumberOfCells], stateCopy_21[NumberOfCells], stateCopy_22[NumberOfCells], stateCopy_23[NumberOfCells], stateCopy_24[NumberOfCells], stateCopy_25[NumberOfCells], stateCopy_26[NumberOfCells], stateCopy_27[NumberOfCells], stateCopy_28[NumberOfCells], stateCopy_29[NumberOfCells],
          stateCopy_30[NumberOfCells], stateCopy_31[NumberOfCells], stateCopy_32[NumberOfCells], stateCopy_33[NumberOfCells], stateCopy_34[NumberOfCells], stateCopy_35[NumberOfCells], stateCopy_36[NumberOfCells], stateCopy_37[NumberOfCells], stateCopy_38[NumberOfCells], stateCopy_39[NumberOfCells],
          stateCopy_40[NumberOfCells], stateCopy_41[NumberOfCells], stateCopy_42[NumberOfCells], stateCopy_43[NumberOfCells], stateCopy_44[NumberOfCells], stateCopy_45[NumberOfCells], stateCopy_46[NumberOfCells], stateCopy_47[NumberOfCells], stateCopy_48[NumberOfCells], stateCopy_49[NumberOfCells],
          stateCopy_50[NumberOfCells], stateCopy_51[NumberOfCells], stateCopy_52[NumberOfCells], stateCopy_53[NumberOfCells], stateCopy_54[NumberOfCells], stateCopy_55[NumberOfCells], stateCopy_56[NumberOfCells],
          rate2_0[NumberOfCells],  rate2_1[NumberOfCells],  rate2_2[NumberOfCells],  rate2_3[NumberOfCells],  rate2_4[NumberOfCells],  rate2_5[NumberOfCells],  rate2_6[NumberOfCells],  rate2_7[NumberOfCells],  rate2_8[NumberOfCells],  rate2_9[NumberOfCells],
          rate2_10[NumberOfCells], rate2_11[NumberOfCells], rate2_12[NumberOfCells], rate2_13[NumberOfCells], rate2_14[NumberOfCells], rate2_15[NumberOfCells], rate2_16[NumberOfCells], rate2_17[NumberOfCells], rate2_18[NumberOfCells], rate2_19[NumberOfCells],
          rate2_20[NumberOfCells], rate2_21[NumberOfCells], rate2_22[NumberOfCells], rate2_23[NumberOfCells], rate2_24[NumberOfCells], rate2_25[NumberOfCells], rate2_26[NumberOfCells], rate2_27[NumberOfCells], rate2_28[NumberOfCells], rate2_29[NumberOfCells],
          rate2_30[NumberOfCells], rate2_31[NumberOfCells], rate2_32[NumberOfCells], rate2_33[NumberOfCells], rate2_34[NumberOfCells], rate2_35[NumberOfCells], rate2_36[NumberOfCells], rate2_37[NumberOfCells], rate2_38[NumberOfCells], rate2_39[NumberOfCells],
          rate2_40[NumberOfCells], rate2_41[NumberOfCells], rate2_42[NumberOfCells], rate2_43[NumberOfCells], rate2_44[NumberOfCells], rate2_45[NumberOfCells], rate2_46[NumberOfCells], rate2_47[NumberOfCells], rate2_48[NumberOfCells], rate2_49[NumberOfCells],
          rate2_50[NumberOfCells], rate2_51[NumberOfCells], rate2_52[NumberOfCells], rate2_53[NumberOfCells], rate2_54[NumberOfCells], rate2_55[NumberOfCells], rate2_56[NumberOfCells];
   
   if (Ksteps == 0){
     dt_0D = timeSpan /5;
   }
   else{
     dt_0D = timeSpan / Ksteps;
   }
   handle_array[0]=clock(); // 5-10 in rhs benutzt
   for(k=1; k<=Ksteps; k++){
     handle_array[1]=clock();
#pragma GCC ivdep
     for (cell=0;cell<NumberOfCells;cell++){ /*statesCopy = states*/
       stateCopy_0[cell]=state0[cell];
       stateCopy_1[cell]=state1[cell];
       stateCopy_2[cell]=state2[cell];
       stateCopy_3[cell]=state3[cell];
       stateCopy_4[cell]=state4[cell];
       stateCopy_5[cell]=state5[cell];
       stateCopy_6[cell]=state6[cell];
       stateCopy_7[cell]=state7[cell];
       stateCopy_8[cell]=state8[cell];
       stateCopy_9[cell]=state9[cell];
       stateCopy_10[cell]=state10[cell];
       stateCopy_11[cell]=state11[cell];
       stateCopy_12[cell]=state12[cell];
       stateCopy_13[cell]=state13[cell]; 
       stateCopy_14[cell]=state14[cell]; 
       stateCopy_15[cell]=state15[cell];
       stateCopy_16[cell]=state16[cell];
       stateCopy_17[cell]=state17[cell];
       stateCopy_18[cell]=state18[cell]; 
       stateCopy_19[cell]=state19[cell];
       stateCopy_20[cell]=state20[cell];
       stateCopy_21[cell]=state21[cell];
       stateCopy_22[cell]=state22[cell];
       stateCopy_23[cell]=state23[cell];
       stateCopy_24[cell]=state24[cell];
       stateCopy_25[cell]=state25[cell];
       stateCopy_26[cell]=state26[cell];
       stateCopy_27[cell]=state27[cell];
       //stateCopy_28[cell]=state28[cell]; dummy variable
       stateCopy_29[cell]=state29[cell];
       stateCopy_30[cell]=state30[cell];
       stateCopy_31[cell]=state31[cell];
       stateCopy_32[cell]=state32[cell]; 
       stateCopy_33[cell]=state33[cell]; 
       stateCopy_34[cell]=state34[cell]; 
       stateCopy_35[cell]=state35[cell]; 
       stateCopy_36[cell]=state36[cell];
       stateCopy_37[cell]=state37[cell]; 
       stateCopy_38[cell]=state38[cell];
       stateCopy_39[cell]=state39[cell];
       stateCopy_40[cell]=state40[cell];
       stateCopy_41[cell]=state41[cell];
       stateCopy_42[cell]=state42[cell];
       stateCopy_43[cell]=state43[cell];
       stateCopy_44[cell]=state44[cell];
       stateCopy_45[cell]=state45[cell];
       stateCopy_46[cell]=state46[cell];
       stateCopy_47[cell]=state47[cell];
       stateCopy_48[cell]=state48[cell];
       stateCopy_49[cell]=state49[cell];
       stateCopy_50[cell]=state50[cell];
       stateCopy_51[cell]=state51[cell];
       stateCopy_52[cell]=state52[cell];
       stateCopy_53[cell]=state53[cell];
       stateCopy_54[cell]=state54[cell];
       stateCopy_55[cell]=state55[cell]; 
       stateCopy_56[cell]=state56[cell];
     }
     handle_array[2]=clock();
     // time to actualize states (plus COPY if T==1):  (Is part of [0].)
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
     // first step. compute rate
     RHS_routineForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                     state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                     state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,state50,state51,state52,state53,state54,state55,state56,NumberOfCells,
                     rate0, rate1, rate2, rate3, rate4, rate5, rate6, rate7, rate8, rate9, rate10,rate11,rate12,rate13,rate14,rate15,rate16,rate17,rate18,rate19,
                     rate20,rate21,rate22,rate23,rate24,rate25,rate26,rate27,rate28,rate29,rate30,rate31,rate32,rate33,rate34,rate35,rate36,rate37,rate38,rate39,
                     rate40,rate41,rate42,rate43,rate44,rate45,rate46,rate47,rate48,rate49,rate50,rate51,rate52,rate53,rate54,rate55,rate56,
                     gamma_OutFromRhs,StimValue_INtoRHS,L_hs_INtoRHS, handle_array, portions_array);
     handle_array[1]=clock();
#pragma GCC ivdep     // needed, otherwise not vectorized
      for(cell=1; cell<=NumberOfCells; cell++){ /* step forward to compute pre state*/
         state0[cell] = state0[cell] + dt_0D * rate0[cell];
         state1[cell] = state1[cell] + dt_0D * rate1[cell];
         state2[cell] = state2[cell] + dt_0D * rate2[cell];
         state3[cell] = state3[cell] + dt_0D * rate3[cell];
         state4[cell] = state4[cell] + dt_0D * rate4[cell];
         state5[cell] = state5[cell] + dt_0D * rate5[cell];
         state6[cell] = state6[cell] + dt_0D * rate6[cell];
         state7[cell] = state7[cell] + dt_0D * rate7[cell];
         state8[cell] = state8[cell] + dt_0D * rate8[cell];
         state9[cell] = state9[cell] + dt_0D * rate9[cell];
         state10[cell] = state10[cell] + dt_0D * rate10[cell];
         state11[cell] = state11[cell] + dt_0D * rate11[cell];
         state12[cell] = state12[cell] + dt_0D * rate12[cell];
         state13[cell] = state13[cell] + dt_0D * rate13[cell];
         state14[cell] = state14[cell] + dt_0D * rate14[cell];
         state15[cell] = state15[cell] + dt_0D * rate15[cell];
         state16[cell] = state16[cell] + dt_0D * rate16[cell];
         state17[cell] = state17[cell] + dt_0D * rate17[cell];
         state18[cell] = state18[cell] + dt_0D * rate18[cell];
         state19[cell] = state19[cell] + dt_0D * rate19[cell];
         state20[cell] = state20[cell] + dt_0D * rate20[cell];
         state21[cell] = state21[cell] + dt_0D * rate21[cell];
         state22[cell] = state22[cell] + dt_0D * rate22[cell];
         state23[cell] = state23[cell] + dt_0D * rate23[cell];
         state24[cell] = state24[cell] + dt_0D * rate24[cell];
         state25[cell] = state25[cell] + dt_0D * rate25[cell];
         state26[cell] = state26[cell] + dt_0D * rate26[cell];
         state27[cell] = state27[cell] + dt_0D * rate27[cell];
         state29[cell] = state29[cell] + dt_0D * rate29[cell];
         state30[cell] = state30[cell] + dt_0D * rate30[cell];
         state31[cell] = state31[cell] + dt_0D * rate31[cell];
         state32[cell] = state32[cell] + dt_0D * rate32[cell];
         state33[cell] = state33[cell] + dt_0D * rate33[cell];
         state34[cell] = state34[cell] + dt_0D * rate34[cell];
         state35[cell] = state35[cell] + dt_0D * rate35[cell];
         state36[cell] = state36[cell] + dt_0D * rate36[cell];
         state37[cell] = state37[cell] + dt_0D * rate37[cell];
         state38[cell] = state38[cell] + dt_0D * rate38[cell];
         state39[cell] = state39[cell] + dt_0D * rate39[cell];
         state40[cell] = state40[cell] + dt_0D * rate40[cell];
         state41[cell] = state41[cell] + dt_0D * rate41[cell];
         state42[cell] = state42[cell] + dt_0D * rate42[cell];
         state43[cell] = state43[cell] + dt_0D * rate43[cell];
         state44[cell] = state44[cell] + dt_0D * rate44[cell];
         state45[cell] = state45[cell] + dt_0D * rate45[cell];
         state46[cell] = state46[cell] + dt_0D * rate46[cell];
         state47[cell] = state47[cell] + dt_0D * rate47[cell];
         state48[cell] = state48[cell] + dt_0D * rate48[cell];
         state49[cell] = state49[cell] + dt_0D * rate49[cell];
         state50[cell] = state50[cell] + dt_0D * rate50[cell];
         state51[cell] = state51[cell] + dt_0D * rate51[cell];
         state52[cell] = state52[cell] + dt_0D * rate52[cell];
         state53[cell] = state53[cell] + dt_0D * rate53[cell];
         state54[cell] = state54[cell] + dt_0D * rate54[cell];
         state55[cell] = state55[cell] + dt_0D * rate55[cell];
         state56[cell] = state56[cell] + dt_0D * rate56[cell];
      }
      handle_array[2]=clock();
     // time to actualize states (plus COPY if T==1):  (Is part of [0].)
     portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
     // second step compute rate2
      RHS_routineForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                        state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                        state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,state50,state51,state52,state53,state54,state55,state56,NumberOfCells,
                        rate2_0, rate2_1, rate2_2, rate2_3, rate2_4, rate2_5, rate2_6, rate2_7, rate2_8, rate2_9, rate2_10,rate2_11,rate2_12,rate2_13,rate2_14,rate2_15,rate2_16,rate2_17,rate2_18,rate2_19,
                        rate2_20,rate2_21,rate2_22,rate2_23,rate2_24,rate2_25,rate2_26,rate2_27,rate2_28,rate2_29,rate2_30,rate2_31,rate2_32,rate2_33,rate2_34,rate2_35,rate2_36,rate2_37,rate2_38,rate2_39,
                        rate2_40,rate2_41,rate2_42,rate2_43,rate2_44,rate2_45,rate2_46,rate2_47,rate2_48,rate2_49,rate2_50,rate2_51,rate2_52,rate2_53,rate2_54,rate2_55,rate2_56,
                        gamma_OutFromRhs,StimValue_INtoRHS,L_hs_INtoRHS, handle_array, portions_array);
     handle_array[1]=clock();
#pragma GCC ivdep     // needed, otherwise not vectorized
      for(cell=1; cell<=NumberOfCells; cell++){ /* step forward to compute new state*/
         state0[cell] = stateCopy_0[cell] + dt_0D * (rate0[cell] + rate2_0[cell])/2.0;
         state1[cell] = stateCopy_1[cell] + dt_0D * (rate1[cell] + rate2_1[cell])/2.0;
         state2[cell] = stateCopy_2[cell] + dt_0D * (rate2[cell] + rate2_2[cell])/2.0;
         state3[cell] = stateCopy_3[cell] + dt_0D * (rate3[cell] + rate2_3[cell])/2.0;
         state4[cell] = stateCopy_4[cell] + dt_0D * (rate4[cell] + rate2_4[cell])/2.0;
         state5[cell] = stateCopy_5[cell] + dt_0D * (rate5[cell] + rate2_5[cell])/2.0;
         state6[cell] = stateCopy_6[cell] + dt_0D * (rate6[cell] + rate2_6[cell])/2.0;
         state7[cell] = stateCopy_7[cell] + dt_0D * (rate7[cell] + rate2_7[cell])/2.0;
         state8[cell] = stateCopy_8[cell] + dt_0D * (rate8[cell] + rate2_8[cell])/2.0;
         state9[cell] = stateCopy_9[cell] + dt_0D * (rate9[cell] + rate2_9[cell])/2.0;
         state10[cell] = stateCopy_10[cell] + dt_0D * (rate10[cell] + rate2_10[cell])/2.0;
         state11[cell] = stateCopy_11[cell] + dt_0D * (rate11[cell] + rate2_11[cell])/2.0;
         state12[cell] = stateCopy_12[cell] + dt_0D * (rate12[cell] + rate2_12[cell])/2.0;
         state13[cell] = stateCopy_13[cell] + dt_0D * (rate13[cell] + rate2_13[cell])/2.0;
         state14[cell] = stateCopy_14[cell] + dt_0D * (rate14[cell] + rate2_14[cell])/2.0;
         state15[cell] = stateCopy_15[cell] + dt_0D * (rate15[cell] + rate2_15[cell])/2.0;
         state16[cell] = stateCopy_16[cell] + dt_0D * (rate16[cell] + rate2_16[cell])/2.0;
         state17[cell] = stateCopy_17[cell] + dt_0D * (rate17[cell] + rate2_17[cell])/2.0;
         state18[cell] = stateCopy_18[cell] + dt_0D * (rate18[cell] + rate2_18[cell])/2.0;
         state19[cell] = stateCopy_19[cell] + dt_0D * (rate19[cell] + rate2_19[cell])/2.0;
         state20[cell] = stateCopy_20[cell] + dt_0D * (rate20[cell] + rate2_20[cell])/2.0;
         state21[cell] = stateCopy_21[cell] + dt_0D * (rate21[cell] + rate2_21[cell])/2.0;
         state22[cell] = stateCopy_22[cell] + dt_0D * (rate22[cell] + rate2_22[cell])/2.0;
         state23[cell] = stateCopy_23[cell] + dt_0D * (rate23[cell] + rate2_23[cell])/2.0;
         state24[cell] = stateCopy_24[cell] + dt_0D * (rate24[cell] + rate2_24[cell])/2.0;
         state25[cell] = stateCopy_25[cell] + dt_0D * (rate25[cell] + rate2_25[cell])/2.0;
         state26[cell] = stateCopy_26[cell] + dt_0D * (rate26[cell] + rate2_26[cell])/2.0;
         state27[cell] = stateCopy_27[cell] + dt_0D * (rate27[cell] + rate2_27[cell])/2.0;
         state28[cell] = 0.0; //not necessary
         state29[cell] = stateCopy_29[cell] + dt_0D * (rate29[cell] + rate2_29[cell])/2.0;
         state30[cell] = stateCopy_30[cell] + dt_0D * (rate30[cell] + rate2_30[cell])/2.0;
         state31[cell] = stateCopy_31[cell] + dt_0D * (rate31[cell] + rate2_31[cell])/2.0;
         state32[cell] = stateCopy_32[cell] + dt_0D * (rate32[cell] + rate2_32[cell])/2.0;
         state33[cell] = stateCopy_33[cell] + dt_0D * (rate33[cell] + rate2_33[cell])/2.0;
         state34[cell] = stateCopy_34[cell] + dt_0D * (rate34[cell] + rate2_34[cell])/2.0;
         state35[cell] = stateCopy_35[cell] + dt_0D * (rate35[cell] + rate2_35[cell])/2.0;
         state36[cell] = stateCopy_36[cell] + dt_0D * (rate36[cell] + rate2_36[cell])/2.0;
         state37[cell] = stateCopy_37[cell] + dt_0D * (rate37[cell] + rate2_37[cell])/2.0;
         state38[cell] = stateCopy_38[cell] + dt_0D * (rate38[cell] + rate2_38[cell])/2.0;
         state39[cell] = stateCopy_39[cell] + dt_0D * (rate39[cell] + rate2_39[cell])/2.0;
         state40[cell] = stateCopy_40[cell] + dt_0D * (rate40[cell] + rate2_40[cell])/2.0;
         state41[cell] = stateCopy_41[cell] + dt_0D * (rate41[cell] + rate2_41[cell])/2.0;
         state42[cell] = stateCopy_42[cell] + dt_0D * (rate42[cell] + rate2_42[cell])/2.0;
         state43[cell] = stateCopy_43[cell] + dt_0D * (rate43[cell] + rate2_43[cell])/2.0;
         state44[cell] = stateCopy_44[cell] + dt_0D * (rate44[cell] + rate2_44[cell])/2.0;
         state45[cell] = stateCopy_45[cell] + dt_0D * (rate45[cell] + rate2_45[cell])/2.0;
         state46[cell] = stateCopy_46[cell] + dt_0D * (rate46[cell] + rate2_46[cell])/2.0;
         state47[cell] = stateCopy_47[cell] + dt_0D * (rate47[cell] + rate2_47[cell])/2.0;
         state48[cell] = stateCopy_48[cell] + dt_0D * (rate48[cell] + rate2_48[cell])/2.0;
         state49[cell] = stateCopy_49[cell] + dt_0D * (rate49[cell] + rate2_49[cell])/2.0;
         state50[cell] = stateCopy_50[cell] + dt_0D * (rate50[cell] + rate2_50[cell])/2.0;
         state51[cell] = stateCopy_51[cell] + dt_0D * (rate51[cell] + rate2_51[cell])/2.0;
         state52[cell] = stateCopy_52[cell] + dt_0D * (rate52[cell] + rate2_52[cell])/2.0;
         state53[cell] = stateCopy_53[cell] + dt_0D * (rate53[cell] + rate2_53[cell])/2.0;
         state54[cell] = stateCopy_54[cell] + dt_0D * (rate54[cell] + rate2_54[cell])/2.0;
         state55[cell] = stateCopy_55[cell] + dt_0D * (rate55[cell] + rate2_55[cell])/2.0;
         state56[cell] = stateCopy_56[cell] + dt_0D * (rate56[cell] + rate2_56[cell])/2.0;
      } 
      handle_array[2]=clock();
      // time to actualize states (plus COPY if T==1):  (Is part of [0].)
      portions_array[2] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
     } // end for k
   handle_array[1]=clock();
   // compute OUTfromRHS value (L_hs):
   RHS_routineForAVX(state0, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10,state11,state12,state13,state14,state15,state16,state17,state18,state19,
                     state20,state21,state22,state23,state24,state25,state26,state27,state28,state29,state30,state31,state32,state33,state34,state35,state36,state37,state38,state39,
                     state40,state41,state42,state43,state44,state45,state46,state47,state48,state49,state50,state51,state52,state53,state54,state55,state56,NumberOfCells,
                     rate0, rate1, rate2, rate3, rate4, rate5, rate6, rate7, rate8, rate9, rate10,rate11,rate12,rate13,rate14,rate15,rate16,rate17,rate18,rate19,
                     rate20,rate21,rate22,rate23,rate24,rate25,rate26,rate27,rate28,rate29,rate30,rate31,rate32,rate33,rate34,rate35,rate36,rate37,rate38,rate39,
                     rate40,rate41,rate42,rate43,rate44,rate45,rate46,rate47,rate48,rate49,rate50,rate51,rate52,rate53,rate54,rate55,rate56,
                     gamma_OutFromRhs,StimValue_INtoRHS,L_hs_INtoRHS, handle_array, portions_array);
   handle_array[2]=clock();
   // time to do the whole Heun integration: (Thus, [0] includes [2].)
   portions_array[0] += ((double) (handle_array[1]-handle_array[0])) / CLOCKS_PER_SEC;
   // time to compute L_hs after numerical integration:
   portions_array[1] += ((double) (handle_array[2]-handle_array[1])) / CLOCKS_PER_SEC;
  return 0;
 }

int initVectorsForAVX(double* state0, double* state1, double* state2, double* state3, double* state4, double* state5, double* state6, double* state7, double* state8, double* state9,
                      double* state10,double* state11,double* state12,double* state13,double* state14,double* state15,double* state16,double* state17,double* state18,double* state19,
                      double* state20,double* state21,double* state22,double* state23,double* state24,double* state25,double* state26,double* state27,double* state28,double* state29,
                      double* state30,double* state31,double* state32,double* state33,double* state34,double* state35,double* state36,double* state37,double* state38,double* state39,
                      double* state40,double* state41,double* state42,double* state43,double* state44,double* state45,double* state46,double* state47,double* state48,double* state49,
                      double* state50,double* state51,double* state52,double* state53,double* state54,double* state55,double* state56,
                      double* parameters0,double* parameters1,int NumberOfCells){
 int i;
 for(i=1;i<=NumberOfCells;i++){
  state0[i]=-79.974;
  state1[i]=-80.2;
  state2[i]=5.9;
  state3[i]=150.9;
  state4[i]=5.9;
  state5[i]=12.7;
  state6[i]=133.0;
  state7[i]=133.0;
  state8[i]=0.009466;
  state9[i]=0.9952;
  state10[i]=0.0358;
  state11[i]=0.4981;
  state12[i]=0.581;
  state13[i]=0.009466;
  state14[i]=0.9952;
  state15[i]=0.0358;
  state16[i]=0.4981;
  state17[i]=0.581;
  state18[i]=0.0; //O_0
  state19[i]=0.0;
  state20[i]=0.0;
  state21[i]=0.0;
  state22[i]=0.0; //O_4
  state23[i]=1.0;
  state24[i]=0.0;
  state25[i]=0.0;
  state26[i]=0.0;
  state27[i]=0.0;
  state28[i]=0.0; // dummy assignment
  state29[i]=0.1;
  state30[i]=1500.0;
  state31[i]=0.1;
  state32[i]=1500.0;
  state33[i]=25;
  state34[i]=615;
  state35[i]=615;
  state36[i]=811;
  state37[i]=811;
  state38[i]=16900.0;
  state39[i]=16900.0;
  state40[i]=0.4;
  state41[i]=0.4;
  state42[i]=7200.0;
  state43[i]=7200.0;
  state44[i]=799.6;
  state45[i]=799.6;
  state46[i]=1000.0;
  state47[i]=1000.0;
  state48[i]=3.0;
  state49[i]=0.8;
  state50[i]=1.2;
  state51[i]=3.0;
  state52[i]=0.3;
  state53[i]=0.23;
  state54[i]=0.23;
  state55[i]=0.23;
  state56[i]=0.23;
  
  parameters0[i]=1200.0;
  parameters1[i]=1.0;
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