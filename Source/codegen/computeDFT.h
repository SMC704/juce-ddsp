//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  computeDFT.h
//
//  Code generation for function 'computeDFT'
//


#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void computeDFT(const ::coder::array<double, 2U> &xin, double varargin_1, ::
                  coder::array<creal_T, 2U> &Xx, double f_data[], int f_size[1]);
}

#endif

// End of code generation (computeDFT.h)
