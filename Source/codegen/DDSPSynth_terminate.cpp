//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_terminate.cpp
//
//  Code generation for function 'DDSPSynth_terminate'
//


// Include files
#include "DDSPSynth_terminate.h"
#include "DDSPSynth_data.h"
#include "additive.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Function Definitions
void DDSPSynth_terminate()
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_DDSPSynth = false;
}

// End of code generation (DDSPSynth_terminate.cpp)
