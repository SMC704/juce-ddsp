//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_data.cpp
//
//  Code generation for function 'DDSPSynth_data'
//


// Include files
#include "DDSPSynth_data.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Variable Definitions
unsigned int state[625];
omp_nest_lock_t emlrtNestLockGlobal;
boolean_T isInitialized_DDSPSynth = false;

// End of code generation (DDSPSynth_data.cpp)
