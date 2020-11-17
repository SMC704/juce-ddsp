//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_initialize.h
//
//  Code generation for function 'DDSPSynth_initialize'
//


#ifndef DDSPSYNTH_INITIALIZE_H
#define DDSPSYNTH_INITIALIZE_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void DDSPSynth_initialize();

#endif

// End of code generation (DDSPSynth_initialize.h)
