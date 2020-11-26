//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  hamming.h
//
//  Code generation for function 'hamming'
//


#ifndef HAMMING_H
#define HAMMING_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_hamming(double varargin_1, double w_data[], int w_size[1]);
extern void hamming(int varargin_1, coder::array<double, 1U> &w);

#endif

// End of code generation (hamming.h)
