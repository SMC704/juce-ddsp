//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  scale_f0.cpp
//
//  Code generation for function 'scale_f0'
//


// Include files
#include "scale_f0.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
void scale_f0(const double f0_in[100], boolean_T to_midi, double f0_scaled[100])
{
  int i;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  std::memset(&f0_scaled[0], 0, 100U * sizeof(double));
  if (to_midi) {
    double note;
    if (f0_in[0] == -1.0) {
      note = 0.0;
    } else {
      if (f0_in[0] == 0.0) {
        note = rtMinusInf;
      } else if (f0_in[0] < 0.0) {
        note = rtNaN;
      } else if ((!rtIsInf(f0_in[0])) && (!rtIsNaN(f0_in[0]))) {
        note = frexp(f0_in[0], &i);
        if (note == 0.5) {
          note = static_cast<double>(i) - 1.0;
        } else if ((i == 1) && (note < 0.75)) {
          note = std::log(2.0 * note) / 0.69314718055994529;
        } else {
          note = std::log(note) / 0.69314718055994529 + static_cast<double>(i);
        }
      } else {
        note = f0_in[0];
      }

      note = 12.0 * (note - 8.78135971352466) + 69.0;
    }

    for (i = 0; i < 100; i++) {
      f0_scaled[i] = note / 127.0;
    }
  }

  if (!to_midi) {
    for (i = 0; i < 100; i++) {
      f0_scaled[i] = 440.0 * rt_powd_snf(2.0, (f0_in[i] * 127.0 - 69.0) / 12.0);
    }
  }
}

// End of code generation (scale_f0.cpp)
