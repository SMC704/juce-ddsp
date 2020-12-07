//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  findpeaks.h
//
//  Code generation for function 'findpeaks'
//


#ifndef FINDPEAKS_H
#define FINDPEAKS_H

// Include files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "DDSPSynth_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void findpeaks(const coder::array<double, 1U> &Yin, coder::array<double,
                      1U> &Ypk, coder::array<double, 1U> &Xpk);

#endif

// End of code generation (findpeaks.h)
