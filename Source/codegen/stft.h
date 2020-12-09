//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  stft.h
//
//  Code generation for function 'stft'
//


#ifndef STFT_H
#define STFT_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void stft(const double x_data[], const int x_size[1], double varargin_1, const
            ::coder::array<double, 1U> &varargin_3, ::coder::array<creal_T, 2U>
            &varargout_1);
}

#endif

// End of code generation (stft.h)
