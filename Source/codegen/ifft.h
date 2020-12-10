//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ifft.h
//
//  Code generation for function 'ifft'
//


#ifndef IFFT_H
#define IFFT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void ifft(const ::coder::array<double, 1U> &x, double varargin_1, ::coder::
            array<creal_T, 1U> &y);
}

#endif

// End of code generation (ifft.h)