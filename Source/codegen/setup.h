//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  setup.h
//
//  Code generation for function 'setup'
//


#ifndef SETUP_H
#define SETUP_H

// Include files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct dsp_BiquadFilter_0;

// Function Declarations
namespace coder
{
  void Outputs(dsp_BiquadFilter_0 *obj, const double U0[2048], const double U1[9],
               const double U2[6], const double U3[4], double Y0[2048]);
}

#endif

// End of code generation (setup.h)
