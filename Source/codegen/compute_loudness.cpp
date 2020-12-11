//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  compute_loudness.cpp
//
//  Code generation for function 'compute_loudness'
//


// Include files
#include "compute_loudness.h"
#include "BiquadFilter.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "FFTImplementationCallback.h"
#include "gencoswin.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "weightingFilter.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_hypotd_snf(double u0, double u1);

// Function Definitions
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

double compute_loudness(double n_samples, const double audio[4096], double
  sample_rate)
{
  static creal_T y[4096];
  coder::weightingFilter A_weighting;
  coder::array<double, 1U> b_window;
  coder::array<double, 1U> window;
  creal_T X[2048];
  double x_win_data[4096];
  double amplitude[2048];
  double b_loudness[2048];
  double b_y[2048];
  double L;
  double loudness;
  int x_win_size[1];
  int i;
  int loop_ub;
  int trivialwin;
  int w_size_idx_0;
  signed char w_data[1];
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  A_weighting.pFilter.matlabCodegenIsDeleted = true;
  A_weighting.matlabCodegenIsDeleted = true;

  //  MATLAB Reimplementation of ddsp.spectral_ops.compute_loudness
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  w_size_idx_0 = 1;
  w_data[0] = 0;
  trivialwin = 0;
  if (n_samples == std::floor(n_samples)) {
    L = n_samples;
  } else {
    L = rt_roundd_snf(n_samples);
  }

  if (L == 0.0) {
    w_size_idx_0 = 0;
    trivialwin = 1;
  } else {
    if (L == 1.0) {
      w_data[0] = 1;
      trivialwin = 1;
    }
  }

  window.set_size(w_size_idx_0);
  for (i = 0; i < w_size_idx_0; i++) {
    window[0] = w_data[0];
  }

  if (trivialwin == 0) {
    if (coder::iseven(L)) {
      int b_loop_ub;
      int c_loop_ub;
      coder::calc_window(L / 2.0, L, window);
      if (1 > window.size(0)) {
        i = 0;
        w_size_idx_0 = 1;
        trivialwin = -1;
      } else {
        i = window.size(0) - 1;
        w_size_idx_0 = -1;
        trivialwin = 0;
      }

      b_loop_ub = div_s32_floor(trivialwin - i, w_size_idx_0);
      b_window.set_size(((window.size(0) + b_loop_ub) + 1));
      c_loop_ub = window.size(0);
      for (trivialwin = 0; trivialwin < c_loop_ub; trivialwin++) {
        b_window[trivialwin] = window[trivialwin];
      }

      for (trivialwin = 0; trivialwin <= b_loop_ub; trivialwin++) {
        b_window[trivialwin + window.size(0)] = window[i + w_size_idx_0 *
          trivialwin];
      }

      window.set_size(b_window.size(0));
      b_loop_ub = b_window.size(0);
      for (i = 0; i < b_loop_ub; i++) {
        window[i] = b_window[i];
      }
    } else {
      int b_loop_ub;
      int c_loop_ub;
      coder::calc_window((L + 1.0) / 2.0, L, window);
      if (1 > window.size(0) - 1) {
        i = 0;
        w_size_idx_0 = 1;
        trivialwin = -1;
      } else {
        i = window.size(0) - 2;
        w_size_idx_0 = -1;
        trivialwin = 0;
      }

      b_loop_ub = div_s32_floor(trivialwin - i, w_size_idx_0);
      b_window.set_size(((window.size(0) + b_loop_ub) + 1));
      c_loop_ub = window.size(0);
      for (trivialwin = 0; trivialwin < c_loop_ub; trivialwin++) {
        b_window[trivialwin] = window[trivialwin];
      }

      for (trivialwin = 0; trivialwin <= b_loop_ub; trivialwin++) {
        b_window[trivialwin + window.size(0)] = window[i + w_size_idx_0 *
          trivialwin];
      }

      window.set_size(b_window.size(0));
      b_loop_ub = b_window.size(0);
      for (i = 0; i < b_loop_ub; i++) {
        window[i] = b_window[i];
      }
    }
  }

  x_win_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    x_win_data[i] = audio[i] * window[i];
  }

  if (loop_ub == 0) {
    std::memset(&X[0], 0, 2048U * sizeof(creal_T));
  } else {
    if (2048 > loop_ub) {
      std::memset(&X[0], 0, 2048U * sizeof(creal_T));
    }

    coder::internal::FFTImplementationCallback::doHalfLengthRadix2((x_win_data),
      (x_win_size), (X));
  }

  //      s = stft(x, sample_rate, 'Window', window, 'FFTLength', NFFT);
  for (w_size_idx_0 = 0; w_size_idx_0 < 2048; w_size_idx_0++) {
    L = rt_hypotd_snf(X[w_size_idx_0].re, X[w_size_idx_0].im);
    if ((1.0E-20 > L) || rtIsNaN(L)) {
      L = 1.0E-20;
    }

    L = std::log10(L);
    b_loudness[w_size_idx_0] = L;
  }

  coder::internal::FFTImplementationCallback::doHalfLengthRadix2((audio), (y));
  A_weighting.init(sample_rate);
  for (i = 0; i < 2048; i++) {
    b_y[i] = y[i].re;
  }

  A_weighting.step(b_y, amplitude);
  for (w_size_idx_0 = 0; w_size_idx_0 < 2048; w_size_idx_0++) {
    L = (b_loudness[w_size_idx_0] * 20.0 + amplitude[w_size_idx_0]) - 20.7;
    b_loudness[w_size_idx_0] = L;
    if (L > -120.0) {
      amplitude[w_size_idx_0] = L;
    } else {
      amplitude[w_size_idx_0] = -120.0;
    }
  }

  L = amplitude[0];
  for (w_size_idx_0 = 0; w_size_idx_0 < 2047; w_size_idx_0++) {
    L += amplitude[w_size_idx_0 + 1];
  }

  loudness = L / 2048.0;
  A_weighting.matlabCodegenDestructor();
  A_weighting.pFilter.matlabCodegenDestructor();
  return loudness;
}

// End of code generation (compute_loudness.cpp)
