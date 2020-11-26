//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  interp1.h
//
//  Code generation for function 'interp1'
//


#ifndef INTERP1_H
#define INTERP1_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void interp1(const coder::array<double, 1U> &varargin_1, const coder::
                    array<double, 1U> &varargin_2, const coder::array<double, 1U>
                    &varargin_3, coder::array<double, 1U> &Vq);

#endif

// End of code generation (interp1.h)
