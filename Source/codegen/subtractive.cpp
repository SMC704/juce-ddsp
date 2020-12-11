//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  subtractive.cpp
//
//  Code generation for function 'subtractive'
//


// Include files
#include "subtractive.h"
#include "ColoredNoise.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "fft.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
void subtractive(double n_samples, double magnitudes[65], double color, double
                 initial_bias, double out[4096])
{
  coder::dsp::ColoredNoise white_n;
  coder::dsp::b_ColoredNoise brown_n;
  coder::dsp::c_ColoredNoise violet_n;
  coder::array<creal_T, 1U> b_x;
  coder::array<creal_T, 1U> x;
  coder::array<double, 1U> mag_rescaled;
  double brown_noise[4096];
  double violet_noise[4096];
  double white_noise[4096];
  double ex;
  double r3;
  double sigma;
  int signal_size[1];
  int b_eint;
  int eint;
  int i;
  int idx;
  int k;
  int loop_ub;
  short b_tmp_data[4096];
  boolean_T tmp_data[4096];
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  function [out, b] = subtractive(n_samples, magnitudes, color, ir_coeffs, recalculate_ir) 
  //  magnitudes: row = frames, column = freq responses
  //  magnitudes should be 65
  for (k = 0; k < 65; k++) {
    magnitudes[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-(magnitudes[k] +
      initial_bias)) + 1.0), 2.3025850929940459) + 1.0E-7;
  }

  //  generate white noise
  white_n.init();
  brown_n.init();
  violet_n.init();
  white_n.step(white_noise);
  brown_n.step(brown_noise);
  violet_n.step(violet_noise);
  white_n.release();
  brown_n.release();
  violet_n.release();
  sigma = std::abs(color);
  for (i = 0; i < 4096; i++) {
    white_noise[i] *= 1.0 - sigma;
  }

  if (color > 0.0) {
    for (i = 0; i < 4096; i++) {
      white_noise[i] += color * violet_noise[i];
    }
  }

  if (color < 0.0) {
    for (i = 0; i < 4096; i++) {
      white_noise[i] += sigma * brown_noise[i];
    }
  }

  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  signal_size[0] = loop_ub;
  if (0 <= loop_ub - 1) {
    std::memcpy(&brown_noise[0], &white_noise[0], loop_ub * sizeof(double));
  }

  if (loop_ub <= 2) {
    if (loop_ub == 1) {
      r3 = white_noise[0];
      ex = white_noise[0];
    } else {
      if ((white_noise[0] > white_noise[1]) || (rtIsNaN(white_noise[0]) &&
           (!rtIsNaN(white_noise[1])))) {
        r3 = white_noise[1];
      } else {
        r3 = white_noise[0];
      }

      if ((white_noise[0] < white_noise[1]) || (rtIsNaN(white_noise[0]) &&
           (!rtIsNaN(white_noise[1])))) {
        ex = white_noise[1];
      } else {
        ex = white_noise[0];
      }
    }
  } else {
    boolean_T b;
    boolean_T exitg1;
    b = rtIsNaN(white_noise[0]);
    if (!b) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub)) {
        if (!rtIsNaN(white_noise[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      r3 = white_noise[0];
    } else {
      r3 = white_noise[idx - 1];
      i = idx + 1;
      for (k = i; k <= loop_ub; k++) {
        sigma = white_noise[k - 1];
        if (r3 > sigma) {
          r3 = sigma;
        }
      }
    }

    if (!b) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub)) {
        if (!rtIsNaN(white_noise[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = white_noise[0];
    } else {
      ex = white_noise[idx - 1];
      i = idx + 1;
      for (k = i; k <= loop_ub; k++) {
        sigma = white_noise[k - 1];
        if (ex < sigma) {
          ex = sigma;
        }
      }
    }
  }

  if (loop_ub != 0) {
    double iMax;
    double iMin;
    if ((0.0 < ex) || rtIsNaN(ex)) {
      sigma = 0.0;
    } else {
      sigma = ex;
    }

    if ((!(sigma > r3)) && (!rtIsNaN(r3))) {
      sigma = r3;
    }

    signal_size[0] = loop_ub;
    for (i = 0; i < loop_ub; i++) {
      brown_noise[i] = white_noise[i] - sigma;
    }

    iMin = r3 - sigma;
    iMax = ex - sigma;
    sigma = std::abs(iMax);
    r3 = std::abs(iMin);
    if ((sigma > r3) || rtIsNaN(r3)) {
      ex = sigma;
    } else {
      ex = r3;
    }

    if ((!rtIsInf(ex)) && (!rtIsNaN(ex))) {
      frexp(ex, &b_eint);
    } else {
      b_eint = 0;
    }

    sigma = rt_powd_snf(2.0, static_cast<double>(b_eint) - 1.0);
    ex = (static_cast<double>(b_eint) + 1.0) / 2.0;
    if (ex < 0.0) {
      ex = std::ceil(ex);
    } else {
      ex = std::floor(ex);
    }

    r3 = rt_powd_snf(2.0, ex - 1.0);
    if (iMin == iMax) {
      for (i = 0; i < loop_ub; i++) {
        tmp_data[i] = rtIsNaN(brown_noise[i]);
      }

      for (i = 0; i < loop_ub; i++) {
        tmp_data[i] = !tmp_data[i];
      }

      idx = loop_ub - 1;
      loop_ub = 0;
      k = 0;
      for (b_eint = 0; b_eint <= idx; b_eint++) {
        if (tmp_data[b_eint]) {
          loop_ub++;
          b_tmp_data[k] = static_cast<short>(b_eint + 1);
          k++;
        }
      }

      for (i = 0; i < loop_ub; i++) {
        brown_noise[b_tmp_data[i] - 1] = -1.0;
      }
    } else {
      double c1;
      c1 = iMax / sigma;
      sigma = iMin / sigma;
      ex = 2.0 / (iMax / r3 - iMin / r3) / r3;
      sigma = r3 * ((c1 * (-1.0 / r3) - sigma * (1.0 / r3)) / (c1 - sigma));
      mag_rescaled.set_size(loop_ub);
      for (i = 0; i < loop_ub; i++) {
        mag_rescaled[i] = brown_noise[i];
      }

      for (i = 0; i < loop_ub; i++) {
        brown_noise[i] = ex * brown_noise[i] + sigma;
      }

      idx = mag_rescaled.size(0);
      for (b_eint = 0; b_eint < idx; b_eint++) {
        if (brown_noise[b_eint] < -1.0) {
          brown_noise[b_eint] = -1.0;
        }
      }

      for (b_eint = 0; b_eint < loop_ub; b_eint++) {
        if (brown_noise[b_eint] > 1.0) {
          brown_noise[b_eint] = 1.0;
        }
      }
    }
  }

  sigma = std::abs(n_samples);
  if (!rtIsInf(sigma)) {
    r3 = frexp(sigma, &eint);
    sigma = eint;
    if (r3 == 0.5) {
      sigma = static_cast<double>(eint) - 1.0;
    }
  }

  coder::fft(brown_noise, signal_size, rt_powd_snf(2.0, sigma), x);

  //      noise_freq = real(fft(signal, NFFT))/NFFT;
  //      noise_freq_half = noise_freq(1:end/2+1);
  sigma = std::ceil(n_samples / 65.0);
  loop_ub = static_cast<int>(65.0 * sigma);
  mag_rescaled.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    mag_rescaled[i] = 0.0;
  }

  i = static_cast<int>(sigma);
  for (idx = 0; idx < 65; idx++) {
    for (k = 0; k < i; k++) {
      mag_rescaled[static_cast<int>((static_cast<double>(k) + 1.0) * (
        static_cast<double>(idx) + 1.0)) - 1] = magnitudes[k];
    }
  }

  b_x.set_size(x.size(0));
  loop_ub = x.size(0);
  for (i = 0; i < loop_ub; i++) {
    sigma = x[i].re;
    ex = x[i].im;
    if (ex == 0.0) {
      r3 = sigma / n_samples;
      sigma = 0.0;
    } else if (sigma == 0.0) {
      r3 = 0.0;
      sigma = ex / n_samples;
    } else {
      r3 = sigma / n_samples;
      sigma = ex / n_samples;
    }

    b_x[i].re = mag_rescaled[i] * r3;
    b_x[i].im = mag_rescaled[i] * sigma;
  }

  coder::ifft(b_x, n_samples, x);
  mag_rescaled.set_size(x.size(0));
  loop_ub = x.size(0);
  for (i = 0; i < loop_ub; i++) {
    mag_rescaled[i] = x[i].re;
  }

  std::memset(&out[0], 0, 4096U * sizeof(double));
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  for (i = 0; i < loop_ub; i++) {
    out[i] = mag_rescaled[i];
  }
}

// End of code generation (subtractive.cpp)
