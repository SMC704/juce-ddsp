//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getMagnitudes.h
//
//  Code generation for function 'getMagnitudes'
//


#ifndef GETMAGNITUDES_H
#define GETMAGNITUDES_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void getMagnitudes(int n_samples, const double input[4096], double
  magnitudes[65]);

#endif

// End of code generation (getMagnitudes.h)
