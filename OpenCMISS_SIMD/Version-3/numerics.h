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
                      double* gamma_OutFromRhs, double* StimValue_INtoRHS,  double* L_hs_INtoRHS, int NumberOfCells, clock_t * handle_array, double * portions_array, int* usedRamSize_pnt);
 
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
                      double* gamma_OutFromRhs, double* StimValue_INtoRHS,  double* L_hs_INtoRHS, int NumberOfCells, clock_t * handle_array, double * portions_array, int* usedRamSize_pnt);
 
 int initVectorsForAVX(double* state0, double* state1, double* state2, double* state3, double* state4, double* state5, double* state6, double* state7, double* state8, double* state9,
                      double* state10,double* state11,double* state12,double* state13,double* state14,double* state15,double* state16,double* state17,double* state18,double* state19,
                      double* state20,double* state21,double* state22,double* state23,double* state24,double* state25,double* state26,double* state27,double* state28,double* state29,
                      double* state30,double* state31,double* state32,double* state33,double* state34,double* state35,double* state36,double* state37,double* state38,double* state39,
                      double* state40,double* state41,double* state42,double* state43,double* state44,double* state45,double* state46,double* state47,double* state48,double* state49,
                      double* state50,double* state51,double* state52,double* state53,double* state54,double* state55,double* state56,
                      double* parameters0,double* parameters1,int NumberOfCells);
 
 int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y);