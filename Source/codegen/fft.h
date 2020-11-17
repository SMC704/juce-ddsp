//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  fft.h
//
//  Code generation for function 'fft'
//


#ifndef FFT_H
#define FFT_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void fft(const coder::array<double, 2U> &x, double varargin_1, coder::
                array<creal_T, 2U> &y);

#endif

// End of code generation (fft.h)
