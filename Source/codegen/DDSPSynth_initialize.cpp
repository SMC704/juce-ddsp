//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_initialize.cpp
//
//  Code generation for function 'DDSPSynth_initialize'
//


// Include files
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_data.h"
#include "eml_rand_mt19937ar_stateful.h"
#include "rt_nonfinite.h"

// Function Definitions
void DDSPSynth_initialize()
{
  omp_init_nest_lock(&emlrtNestLockGlobal);
  eml_rand_mt19937ar_stateful_init();
  isInitialized_DDSPSynth = true;
}

// End of code generation (DDSPSynth_initialize.cpp)
