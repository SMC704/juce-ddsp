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
extern void additive(double n_samples, double sample_rate, const double
                     amplitudes[4096], double n_harmonics, double
                     harmonic_distribution[60], const double f0[4096], const
                     double prev_phases[60], double shift, double stretch,
                     double audio_data[], int audio_size[1], double last_phases
                     [60]);

#endif

// End of code generation (additive.h)
