//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  compute_loudness.h
//
//  Code generation for function 'compute_loudness'
//


#ifndef COMPUTE_LOUDNESS_H
#define COMPUTE_LOUDNESS_H

// Include files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void compute_loudness(double n_samples, const double audio[4096], double
  sample_rate, double loudness_out[100]);

#endif

// End of code generation (compute_loudness.h)
