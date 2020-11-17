//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  useConstantDim.cpp
//
//  Code generation for function 'useConstantDim'
//


// Include files
#include "useConstantDim.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Function Definitions
void useConstantDim(double varargin_2[51200])
{
  for (int k = 0; k < 50; k++) {
    for (int b_k = 0; b_k < 1023; b_k++) {
      int i;
      int i1;
      i = b_k + (k << 10);
      i1 = i + 1;
      varargin_2[i1] += varargin_2[i];
    }
  }
}

// End of code generation (useConstantDim.cpp)
