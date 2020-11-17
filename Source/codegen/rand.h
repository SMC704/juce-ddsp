//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  rand.h
//
//  Code generation for function 'rand'
//


#ifndef RAND_H
#define RAND_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_rand(double varargin_2, coder::array<double, 2U> &r);

#endif

// End of code generation (rand.h)
