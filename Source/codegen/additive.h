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
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void additive(double n_samples, double sample_rate, const double
                     amplitudes[4096], double n_harmonics, double
                     harmonic_distribution[100], const double f0[4096], const
                     double prev_phases[100], double shift, double stretch,
                     double audio[4096], double last_phases[100]);

#endif

// End of code generation (additive.h)
