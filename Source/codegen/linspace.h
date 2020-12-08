//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  linspace.h
//
//  Code generation for function 'linspace'
//


#ifndef LINSPACE_H
#define LINSPACE_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void linspace(double d2, double n1, coder::array<double, 2U> &y);

#endif

// End of code generation (linspace.h)
