//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_rtwutil.h
//
//  Code generation for function 'DDSPSynth_rtwutil'
//


#ifndef DDSPSYNTH_RTWUTIL_H
#define DDSPSYNTH_RTWUTIL_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern double rt_powd_snf(double u0, double u1);
extern double rt_roundd_snf(double u);

#endif

// End of code generation (DDSPSynth_rtwutil.h)
