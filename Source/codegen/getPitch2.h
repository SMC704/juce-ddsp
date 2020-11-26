//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getPitch2.h
//
//  Code generation for function 'getPitch2'
//


#ifndef GETPITCH2_H
#define GETPITCH2_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern double getPitch2(int n_samples, const double input[4096], double fs);

#endif

// End of code generation (getPitch2.h)
