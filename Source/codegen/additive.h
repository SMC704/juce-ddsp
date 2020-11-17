//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  additive.h
//
//  Code generation for function 'additive'
//


#ifndef ADDITIVE_H
#define ADDITIVE_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void additive(double sample_rate, double amplitudes[1024], double
                     harmonic_distribution[51200], const double f0[1024], const
                     double prev_phases[50], double audio[1024], double
                     last_phases[50]);

#endif

// End of code generation (additive.h)
