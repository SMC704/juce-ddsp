//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  irfft.h
//
//  Code generation for function 'irfft'
//


#ifndef IRFFT_H
#define IRFFT_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_irfft(const coder::array<creal_T, 2U> &y, double n, coder::array<
                    creal_T, 2U> &x);
extern void irfft(const double y[1024], double x[2046]);

#endif

// End of code generation (irfft.h)
