//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ifft.h
//
//  Code generation for function 'ifft'
//


#ifndef IFFT_H
#define IFFT_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_ifft(const coder::array<creal_T, 2U> &x, coder::array<creal_T, 2U>
                   &y);
extern void ifft(const creal_T x_data[], creal_T y_data[], int y_size[1]);

#endif

// End of code generation (ifft.h)
