//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  interp1.h
//
//  Code generation for function 'interp1'
//


#ifndef INTERP1_H
#define INTERP1_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void interp1Linear(const ::coder::array<double, 1U> &y, const ::coder::array<
                     double, 1U> &xi, ::coder::array<double, 1U> &yi, const ::
                     coder::array<double, 1U> &varargin_1);
}

#endif

// End of code generation (interp1.h)
