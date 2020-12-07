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
extern void hamming(double varargin_1, double w_data[], int w_size[1]);

#endif

// End of code generation (hamming.h)
