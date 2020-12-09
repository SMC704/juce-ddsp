//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  gencoswin.h
//
//  Code generation for function 'gencoswin'
//


#ifndef GENCOSWIN_H
#define GENCOSWIN_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  void calc_window(double m, double n, ::coder::array<double, 1U> &w);
  void calc_window(double m, double n, double w_data[], int w_size[1]);
}

#endif

// End of code generation (gencoswin.h)
