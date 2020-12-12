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
#include "fftshift.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
void subtractive(double n_samples, const double magnitudes[65], double color,
                 double initial_bias, double out[4096])
{
  static const double dv[65] = { 0.0, 0.0024076366639015356,
    0.0096073597983847847, 0.021529832133895588, 0.038060233744356631,
    0.059039367825822475, 0.084265193848727382, 0.1134947733186315,
    0.14644660940672621, 0.18280335791817726, 0.22221488349019886,
    0.2643016315870011, 0.30865828381745508, 0.35485766137276886,
    0.40245483899193585, 0.45099142983521961, 0.49999999999999994,
    0.54900857016478033, 0.5975451610080641, 0.645142338627231,
    0.69134171618254481, 0.73569836841299885, 0.777785116509801,
    0.81719664208182263, 0.85355339059327373, 0.88650522668136844,
    0.91573480615127267, 0.94096063217417747, 0.96193976625564337,
    0.97847016786610441, 0.99039264020161522, 0.99759236333609835, 1.0,
    0.99759236333609835, 0.99039264020161522, 0.97847016786610441,
    0.96193976625564337, 0.94096063217417747, 0.91573480615127267,
    0.88650522668136844, 0.85355339059327373, 0.81719664208182263,
    0.777785116509801, 0.73569836841299885, 0.69134171618254481,
    0.645142338627231, 0.5975451610080641, 0.54900857016478033,
    0.49999999999999994, 0.45099142983521961, 0.40245483899193585,
    0.35485766137276886, 0.30865828381745508, 0.2643016315870011,
    0.22221488349019886, 0.18280335791817726, 0.14644660940672621,
    0.1134947733186315, 0.084265193848727382, 0.059039367825822475,
    0.038060233744356631, 0.021529832133895588, 0.0096073597983847847,
    0.0024076366639015356, 0.0 };

  coder::dsp::ColoredNoise white_n;
  coder::dsp::b_ColoredNoise brown_n;
  coder::dsp::c_ColoredNoise violet_n;
  coder::array<creal_T, 1U> H;
  coder::array<creal_T, 1U> X;
  coder::array<double, 1U> sub;
  creal_T dcv[65];
  creal_T dcv1[65];
  double brown_noise[4096];
  double violet_noise[4096];
  double white_noise[4096];
  double x[65];
  double z1[65];
  double r1;
  double r3;
  double sigma;
  int signal_size[1];
  int b_eint;
  int eint;
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
    z1[k] = rt_powd_snf(1.0 / (std::exp(-(magnitudes[k] + initial_bias)) + 1.0),
                        2.3025850929940459);
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
  for (idx = 0; idx < 4096; idx++) {
    white_noise[idx] *= 1.0 - sigma;
  }

  if (color > 0.0) {
    for (idx = 0; idx < 4096; idx++) {
      white_noise[idx] += color * violet_noise[idx];
    }
  }

  if (color < 0.0) {
    for (idx = 0; idx < 4096; idx++) {
      white_noise[idx] += sigma * brown_noise[idx];
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
      r1 = white_noise[0];
      r3 = white_noise[0];
    } else {
      if ((white_noise[0] > white_noise[1]) || (rtIsNaN(white_noise[0]) &&
           (!rtIsNaN(white_noise[1])))) {
        r1 = white_noise[1];
      } else {
        r1 = white_noise[0];
      }

      if ((white_noise[0] < white_noise[1]) || (rtIsNaN(white_noise[0]) &&
           (!rtIsNaN(white_noise[1])))) {
        r3 = white_noise[1];
      } else {
        r3 = white_noise[0];
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
      r1 = white_noise[0];
    } else {
      r1 = white_noise[idx - 1];
      idx++;
      for (k = idx; k <= loop_ub; k++) {
        sigma = white_noise[k - 1];
        if (r1 > sigma) {
          r1 = sigma;
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
      r3 = white_noise[0];
    } else {
      r3 = white_noise[idx - 1];
      idx++;
      for (k = idx; k <= loop_ub; k++) {
        sigma = white_noise[k - 1];
        if (r3 < sigma) {
          r3 = sigma;
        }
      }
    }
  }

  if (loop_ub != 0) {
    double iMax;
    double iMin;
    if ((0.0 < r3) || rtIsNaN(r3)) {
      sigma = 0.0;
    } else {
      sigma = r3;
    }

    if ((!(sigma > r1)) && (!rtIsNaN(r1))) {
      sigma = r1;
    }

    signal_size[0] = loop_ub;
    for (idx = 0; idx < loop_ub; idx++) {
      brown_noise[idx] = white_noise[idx] - sigma;
    }

    iMin = r1 - sigma;
    iMax = r3 - sigma;
    sigma = std::abs(iMax);
    r1 = std::abs(iMin);
    if ((!(sigma > r1)) && (!rtIsNaN(r1))) {
      sigma = r1;
    }

    if ((!rtIsInf(sigma)) && (!rtIsNaN(sigma))) {
      frexp(sigma, &b_eint);
    } else {
      b_eint = 0;
    }

    r1 = rt_powd_snf(2.0, static_cast<double>(b_eint) - 1.0);
    sigma = (static_cast<double>(b_eint) + 1.0) / 2.0;
    if (sigma < 0.0) {
      sigma = std::ceil(sigma);
    } else {
      sigma = std::floor(sigma);
    }

    r3 = rt_powd_snf(2.0, sigma - 1.0);
    if (iMin == iMax) {
      for (idx = 0; idx < loop_ub; idx++) {
        tmp_data[idx] = rtIsNaN(brown_noise[idx]);
      }

      for (idx = 0; idx < loop_ub; idx++) {
        tmp_data[idx] = !tmp_data[idx];
      }

      k = loop_ub - 1;
      loop_ub = 0;
      idx = 0;
      for (b_eint = 0; b_eint <= k; b_eint++) {
        if (tmp_data[b_eint]) {
          loop_ub++;
          b_tmp_data[idx] = static_cast<short>(b_eint + 1);
          idx++;
        }
      }

      for (idx = 0; idx < loop_ub; idx++) {
        brown_noise[b_tmp_data[idx] - 1] = -1.0;
      }
    } else {
      double c1;
      c1 = iMax / r1;
      sigma = iMin / r1;
      r1 = 2.0 / (iMax / r3 - iMin / r3) / r3;
      sigma = r3 * ((c1 * (-1.0 / r3) - sigma * (1.0 / r3)) / (c1 - sigma));
      sub.set_size(loop_ub);
      for (idx = 0; idx < loop_ub; idx++) {
        sub[idx] = brown_noise[idx];
      }

      for (idx = 0; idx < loop_ub; idx++) {
        brown_noise[idx] = r1 * brown_noise[idx] + sigma;
      }

      k = sub.size(0);
      for (b_eint = 0; b_eint < k; b_eint++) {
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
    r1 = frexp(sigma, &eint);
    sigma = eint;
    if (r1 == 0.5) {
      sigma = static_cast<double>(eint) - 1.0;
    }
  }

  sigma = rt_powd_snf(2.0, sigma);
  for (b_eint = 0; b_eint < 65; b_eint++) {
    dcv[b_eint].re = 2.0 * z1[b_eint] + 1.0E-7;
    dcv[b_eint].im = 0.0;
    x[b_eint] = dv[b_eint];
  }

  coder::ifft(dcv, dcv1);
  coder::fftshift(x);
  for (idx = 0; idx < 65; idx++) {
    x[idx] *= dcv1[idx].re;
  }

  coder::fftshift(x);
  coder::fft(x, sigma, H);
  coder::fft(brown_noise, signal_size, sigma, X);
  loop_ub = X.size(0);
  for (idx = 0; idx < loop_ub; idx++) {
    sigma = X[idx].re * H[idx].im + X[idx].im * H[idx].re;
    X[idx].re = X[idx].re * H[idx].re - X[idx].im * H[idx].im;
    X[idx].im = sigma;
  }

  coder::ifft(X, n_samples, H);
  sub.set_size(H.size(0));
  loop_ub = H.size(0);
  for (idx = 0; idx < loop_ub; idx++) {
    sub[idx] = H[idx].re;
  }

  std::memset(&out[0], 0, 4096U * sizeof(double));
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  for (idx = 0; idx < loop_ub; idx++) {
    out[idx] = sub[idx];
  }
}

// End of code generation (subtractive.cpp)
