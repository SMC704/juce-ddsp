//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  subtractive.h
//
//  Code generation for function 'subtractive'
//


#ifndef SUBTRACTIVE_H
#define SUBTRACTIVE_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void subtractive(double n_samples, double magnitudes[65], double color,
  double initial_bias, double out[4096]);

#endif

// End of code generation (subtractive.h)
