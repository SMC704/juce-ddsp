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
#include "stft.h"
#include "weightingFilter.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

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

void compute_loudness(double n_samples, const double audio[4096], double
                      sample_rate, double loudness_out[100])
{
  static creal_T y[4096];
  coder::weightingFilter A_weighting;
  coder::array<creal_T, 2U> s;
  coder::array<double, 2U> amplitude;
  coder::array<double, 2U> loudness;
  coder::array<double, 2U> power_db;
  coder::array<double, 1U> b_window;
  coder::array<double, 1U> window;
  double audio_data[4096];
  double b_y[2048];
  double freq_filtered[2048];
  double n_in;
  int audio_size[1];
  int b_i;
  int i;
  int k;
  int loop_ub;
  int npages;
  int nx;
  int xpageoffset;
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

  n_in = std::floor(0.0384615 * n_samples);
  nx = 1;
  w_data[0] = 0;
  npages = 0;
  if (n_in == 0.0) {
    nx = 0;
    npages = 1;
  } else {
    if (n_in == 1.0) {
      w_data[0] = 1;
      npages = 1;
    }
  }

  window.set_size(nx);
  for (i = 0; i < nx; i++) {
    window[0] = w_data[0];
  }

  if (npages == 0) {
    if (coder::signalwavelet::internal::iseven(n_in)) {
      coder::calc_window(n_in / 2.0, n_in, window);
      if (1 > window.size(0)) {
        i = 0;
        k = 1;
        nx = -1;
      } else {
        i = window.size(0) - 1;
        k = -1;
        nx = 0;
      }

      npages = div_s32_floor(nx - i, k);
      b_window.set_size(((window.size(0) + npages) + 1));
      xpageoffset = window.size(0);
      for (nx = 0; nx < xpageoffset; nx++) {
        b_window[nx] = window[nx];
      }

      for (nx = 0; nx <= npages; nx++) {
        b_window[nx + window.size(0)] = window[i + k * nx];
      }

      window.set_size(b_window.size(0));
      npages = b_window.size(0);
      for (i = 0; i < npages; i++) {
        window[i] = b_window[i];
      }
    } else {
      coder::calc_window((n_in + 1.0) / 2.0, n_in, window);
      if (1 > window.size(0) - 1) {
        i = 0;
        k = 1;
        nx = -1;
      } else {
        i = window.size(0) - 2;
        k = -1;
        nx = 0;
      }

      npages = div_s32_floor(nx - i, k);
      b_window.set_size(((window.size(0) + npages) + 1));
      xpageoffset = window.size(0);
      for (nx = 0; nx < xpageoffset; nx++) {
        b_window[nx] = window[nx];
      }

      for (nx = 0; nx <= npages; nx++) {
        b_window[nx + window.size(0)] = window[i + k * nx];
      }

      window.set_size(b_window.size(0));
      npages = b_window.size(0);
      for (i = 0; i < npages; i++) {
        window[i] = b_window[i];
      }
    }
  }

  audio_size[0] = loop_ub;
  if (0 <= loop_ub - 1) {
    std::memcpy(&audio_data[0], &audio[0], loop_ub * sizeof(double));
  }

  coder::stft(audio_data, audio_size, sample_rate, window, s);
  nx = s.size(0) * s.size(1);
  amplitude.set_size(s.size(0), s.size(1));
  for (k = 0; k < nx; k++) {
    amplitude[k] = rt_hypotd_snf(s[k].re, s[k].im);
  }

  power_db.set_size(amplitude.size(0), amplitude.size(1));
  nx = amplitude.size(0) * amplitude.size(1);
  for (k = 0; k < nx; k++) {
    if ((1.0E-20 > amplitude[k]) || rtIsNaN(amplitude[k])) {
      power_db[k] = 1.0E-20;
    } else {
      power_db[k] = amplitude[k];
    }
  }

  nx = power_db.size(0) * power_db.size(1);
  for (k = 0; k < nx; k++) {
    power_db[k] = std::log10(power_db[k]);
  }

  loop_ub = power_db.size(0) * power_db.size(1);
  for (i = 0; i < loop_ub; i++) {
    power_db[i] = power_db[i] * 20.0;
  }

  coder::internal::FFTImplementationCallback::doHalfLengthRadix2((audio), (y));
  A_weighting.init(sample_rate);
  for (i = 0; i < 2048; i++) {
    b_y[i] = y[i].re;
  }

  A_weighting.step(b_y, freq_filtered);
  i = power_db.size(1);
  for (b_i = 0; b_i < i; b_i++) {
    nx = power_db.size(0);
    loop_ub = power_db.size(0);
    for (k = 0; k < loop_ub; k++) {
      b_y[k] = power_db[k + power_db.size(0) * b_i] + freq_filtered[k];
    }

    for (k = 0; k < nx; k++) {
      power_db[k + power_db.size(0) * b_i] = b_y[k];
    }
  }

  amplitude.set_size(power_db.size(0), power_db.size(1));
  loop_ub = power_db.size(0) * power_db.size(1);
  for (i = 0; i < loop_ub; i++) {
    amplitude[i] = power_db[i] - 20.7;
  }

  power_db.set_size(amplitude.size(0), amplitude.size(1));
  nx = amplitude.size(0) * amplitude.size(1);
  for (k = 0; k < nx; k++) {
    if (amplitude[k] > -120.0) {
      power_db[k] = amplitude[k];
    } else {
      power_db[k] = -120.0;
    }
  }

  nx = power_db.size(0);
  if (power_db.size(1) == 0) {
    loudness.set_size(1, 0);
  } else {
    npages = power_db.size(1);
    loudness.set_size(1, power_db.size(1));
    for (b_i = 0; b_i < npages; b_i++) {
      xpageoffset = b_i * power_db.size(0);
      loudness[b_i] = power_db[xpageoffset];
      for (k = 2; k <= nx; k++) {
        loudness[b_i] = loudness[b_i] + power_db[(xpageoffset + k) - 1];
      }
    }
  }

  i = loudness.size(0) * loudness.size(1);
  loudness.set_size(1, loudness.size(1));
  loop_ub = i - 1;
  for (i = 0; i <= loop_ub; i++) {
    loudness[i] = loudness[i] / static_cast<double>(power_db.size(0));
  }

  for (b_i = 0; b_i < 100; b_i++) {
    loudness_out[b_i] = -120.0;
  }

  i = loudness.size(1);
  for (b_i = 0; b_i < i; b_i++) {
    loudness_out[b_i] = loudness[b_i];
  }

  A_weighting.matlabCodegenDestructor();
  A_weighting.pFilter.matlabCodegenDestructor();
}

// End of code generation (compute_loudness.cpp)
