//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  chorus.h
//
//  Code generation for function 'chorus'
//


#ifndef CHORUS_H
#define CHORUS_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "DDSPSynth_types.h"

// Function Declarations
extern void chorus(int n_samples, double sample_rate, const double audio_in[4096],
                   double buffer[4096], int *write_pointer, float amount, float
                   rate, float phase_in, double audio_out[4096], float
                   *phase_out);

#endif

// End of code generation (chorus.h)
