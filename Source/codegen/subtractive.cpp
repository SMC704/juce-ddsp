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
#include "FFTImplementationCallback.h"
#include "SystemCore.h"
#include "additive.h"
#include "fft.h"
#include "getPitch2.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
void subtractive(double n_samples, const double magnitudes[65], double color,
                 double out[4096])
{
  dsp_ColoredNoise white_n;
  b_dsp_ColoredNoise brown_n;
  c_dsp_ColoredNoise violet_n;
  double white_noise[4096];
  double brown_noise[4096];
  double violet_noise[4096];
  double mag_rel_bin_size;
  int i;
  int loop_ub;
  int white_noise_size[1];
  coder::array<creal_T, 1U> r;
  coder::array<double, 1U> noise_freq;
  coder::array<double, 1U> mag_rescaled;
  int idx;
  double r1;
  int k;
  double r3;
  int eint;
  coder::array<boolean_T, 1U> b_r1;
  coder::array<short, 1U> r2;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  function [out, b] = subtractive(n_samples, magnitudes, color, ir_coeffs, recalculate_ir) 
  //  magnitudes: row = frames, column = freq responses
  //  magnitudes should be 65
  //      normalize magnitudes
  //      initial_bias = 1;
  //      optional; colab examplees do not use it
  //      magnitudes = scale_fn(magnitudes + initial_bias);
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
  mag_rel_bin_size = std::abs(color);
  for (i = 0; i < 4096; i++) {
    white_noise[i] *= 1.0 - mag_rel_bin_size;
  }

  if (color > 0.0) {
    for (i = 0; i < 4096; i++) {
      white_noise[i] += color * violet_noise[i];
    }
  }

  if (color < 0.0) {
    for (i = 0; i < 4096; i++) {
      white_noise[i] += mag_rel_bin_size * brown_noise[i];
    }
  }

  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  white_noise_size[0] = loop_ub;
  if (0 <= loop_ub - 1) {
    std::memcpy(&brown_noise[0], &white_noise[0], loop_ub * sizeof(double));
  }

  fft(brown_noise, white_noise_size, 2.0 * (n_samples - 1.0), r);
  noise_freq.set_size(r.size(0));
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    noise_freq[i] = r[i].re;
  }

  mag_rel_bin_size = std::ceil(n_samples / 65.0);
  loop_ub = static_cast<int>(65.0 * mag_rel_bin_size);
  mag_rescaled.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    mag_rescaled[i] = 0.0;
  }

  i = static_cast<int>(mag_rel_bin_size);
  for (idx = 0; idx < 65; idx++) {
    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      mag_rescaled[static_cast<int>((static_cast<double>(loop_ub) + 1.0) * (
        static_cast<double>(idx) + 1.0)) - 1] = magnitudes[loop_ub];
    }
  }

  loop_ub = static_cast<int>(static_cast<double>(noise_freq.size(0)) / 2.0 + 1.0);
  mag_rescaled.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    mag_rescaled[i] = noise_freq[i] * mag_rescaled[i];
  }

  ifft(mag_rescaled, n_samples * 2.0, r);
  noise_freq.set_size(r.size(0));
  loop_ub = r.size(0);
  for (i = 0; i < loop_ub; i++) {
    noise_freq[i] = r[i].re;
  }

  if (1.0 > n_samples) {
    loop_ub = 0;
    i = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
    i = static_cast<int>(n_samples);
  }

  noise_freq.set_size(i);
  if (loop_ub <= 2) {
    if (loop_ub == 1) {
      r1 = noise_freq[0];
      r3 = noise_freq[0];
    } else {
      if ((noise_freq[0] > noise_freq[1]) || (rtIsNaN(noise_freq[0]) &&
           (!rtIsNaN(noise_freq[1])))) {
        r1 = noise_freq[1];
      } else {
        r1 = noise_freq[0];
      }

      if ((noise_freq[0] < noise_freq[1]) || (rtIsNaN(noise_freq[0]) &&
           (!rtIsNaN(noise_freq[1])))) {
        r3 = noise_freq[1];
      } else {
        r3 = noise_freq[0];
      }
    }
  } else {
    boolean_T exitg1;
    if (!rtIsNaN(noise_freq[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub)) {
        if (!rtIsNaN(noise_freq[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      r1 = noise_freq[0];
    } else {
      r1 = noise_freq[idx - 1];
      i = idx + 1;
      for (k = i; k <= loop_ub; k++) {
        mag_rel_bin_size = noise_freq[k - 1];
        if (r1 > mag_rel_bin_size) {
          r1 = mag_rel_bin_size;
        }
      }
    }

    if (!rtIsNaN(noise_freq[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub)) {
        if (!rtIsNaN(noise_freq[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      r3 = noise_freq[0];
    } else {
      r3 = noise_freq[idx - 1];
      i = idx + 1;
      for (k = i; k <= loop_ub; k++) {
        mag_rel_bin_size = noise_freq[k - 1];
        if (r3 < mag_rel_bin_size) {
          r3 = mag_rel_bin_size;
        }
      }
    }
  }

  if (loop_ub != 0) {
    double c1;
    double iMin;
    double iMax;
    if ((0.0 < r3) || rtIsNaN(r3)) {
      c1 = 0.0;
    } else {
      c1 = r3;
    }

    if ((c1 > r1) || rtIsNaN(r1)) {
      mag_rel_bin_size = c1;
    } else {
      mag_rel_bin_size = r1;
    }

    for (i = 0; i < loop_ub; i++) {
      noise_freq[i] = noise_freq[i] - mag_rel_bin_size;
    }

    iMin = r1 - mag_rel_bin_size;
    iMax = r3 - mag_rel_bin_size;
    c1 = std::abs(iMax);
    mag_rel_bin_size = std::abs(iMin);
    if ((c1 > mag_rel_bin_size) || rtIsNaN(mag_rel_bin_size)) {
      mag_rel_bin_size = c1;
    }

    if ((!rtIsInf(mag_rel_bin_size)) && (!rtIsNaN(mag_rel_bin_size))) {
      frexp(mag_rel_bin_size, &eint);
    } else {
      eint = 0;
    }

    r1 = rt_powd_snf(2.0, static_cast<double>(eint) - 1.0);
    mag_rel_bin_size = (static_cast<double>(eint) + 1.0) / 2.0;
    if (mag_rel_bin_size < 0.0) {
      mag_rel_bin_size = std::ceil(mag_rel_bin_size);
    } else {
      mag_rel_bin_size = std::floor(mag_rel_bin_size);
    }

    r3 = rt_powd_snf(2.0, mag_rel_bin_size - 1.0);
    if (iMin == iMax) {
      b_r1.set_size(noise_freq.size(0));
      loop_ub = noise_freq.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_r1[i] = rtIsNaN(noise_freq[i]);
      }

      loop_ub = b_r1.size(0);
      for (i = 0; i < loop_ub; i++) {
        b_r1[i] = !b_r1[i];
      }

      loop_ub = b_r1.size(0) - 1;
      idx = 0;
      for (k = 0; k <= loop_ub; k++) {
        if (b_r1[k]) {
          idx++;
        }
      }

      r2.set_size(idx);
      idx = 0;
      for (k = 0; k <= loop_ub; k++) {
        if (b_r1[k]) {
          r2[idx] = static_cast<short>(k + 1);
          idx++;
        }
      }

      loop_ub = r2.size(0);
      for (i = 0; i < loop_ub; i++) {
        noise_freq[r2[i] - 1] = -1.0;
      }
    } else {
      c1 = iMax / r1;
      mag_rel_bin_size = iMin / r1;
      r1 = 2.0 / (iMax / r3 - iMin / r3) / r3;
      mag_rel_bin_size = r3 * ((c1 * (-1.0 / r3) - mag_rel_bin_size * (1.0 / r3))
        / (c1 - mag_rel_bin_size));
      loop_ub = noise_freq.size(0);
      for (i = 0; i < loop_ub; i++) {
        noise_freq[i] = r1 * noise_freq[i] + mag_rel_bin_size;
      }

      loop_ub = noise_freq.size(0);
      for (k = 0; k < loop_ub; k++) {
        if (noise_freq[k] < -1.0) {
          noise_freq[k] = -1.0;
        }
      }

      loop_ub = noise_freq.size(0);
      for (k = 0; k < loop_ub; k++) {
        if (noise_freq[k] > 1.0) {
          noise_freq[k] = 1.0;
        }
      }
    }
  }

  std::memset(&out[0], 0, 4096U * sizeof(double));
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  for (i = 0; i < loop_ub; i++) {
    out[i] = noise_freq[i];
  }
}

// End of code generation (subtractive.cpp)
