//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getPitch2.cpp
//
//  Code generation for function 'getPitch2'
//


// Include files
#include "getPitch2.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "additive.h"
#include "fft.h"
#include "findpeaks.h"
#include "hamming.h"
#include "interp1.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <math.h>

// Function Definitions
double getPitch2(double n_samples, const double input[4096], double fs)
{
  double f0;
  int loop_ub;
  double delta2;
  int nx;
  double NFFT;
  int i;
  coder::array<double, 2U> y;
  coder::array<double, 2U> b_y;
  int k;
  coder::array<double, 1U> log_spaced_frequency;
  double delta1;
  int end;
  coder::array<double, 1U> bw_temp;
  double win_data[4097];
  int win_size[1];
  int input_size[1];
  double input_data[4096];
  coder::array<creal_T, 1U> Y;
  coder::array<double, 1U> c_y;
  coder::array<double, 1U> b_Y;
  coder::array<double, 1U> locs;
  coder::array<double, 1U> candidates;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  getPitch2
  //  parameters: n_samples (int32), input (double[4096]), fs (double)
  //  output: f0 (double)
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  delta2 = frexp(static_cast<double>(static_cast<int>(std::abs(2.0 *
    static_cast<double>(loop_ub) - 1.0))), &nx);
  if (delta2 == 0.5) {
    nx--;
  }

  NFFT = rt_powd_snf(2.0, static_cast<double>(nx));
  delta2 = fs / 2.0 - 1.0;
  if (!(delta2 < 4000.0)) {
    delta2 = 4000.0;
  }

  delta2 = std::log10(delta2);
  i = static_cast<int>(std::floor(NFFT));
  y.set_size(1, i);
  if (i >= 1) {
    nx = i - 1;
    y[nx] = delta2;
    if (y.size(1) >= 2) {
      y[0] = 1.0;
      if (y.size(1) >= 3) {
        if ((1.0 == -delta2) && (i > 2)) {
          for (k = 2; k <= nx; k++) {
            y[k - 1] = delta2 * ((static_cast<double>((k << 1) - i) - 1.0) / (
              static_cast<double>(i) - 1.0));
          }

          if ((i & 1) == 1) {
            y[i >> 1] = 0.0;
          }
        } else if ((delta2 < 0.0) && (std::abs(delta2) > 8.9884656743115785E+307))
        {
          delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
          delta2 /= static_cast<double>(y.size(1)) - 1.0;
          i = y.size(1);
          for (k = 0; k <= i - 3; k++) {
            y[k + 1] = (delta2 * (static_cast<double>(k) + 1.0) + 1.0) - delta1 *
              (static_cast<double>(k) + 1.0);
          }
        } else {
          delta1 = (delta2 - 1.0) / (static_cast<double>(y.size(1)) - 1.0);
          i = y.size(1);
          for (k = 0; k <= i - 3; k++) {
            y[k + 1] = (static_cast<double>(k) + 1.0) * delta1 + 1.0;
          }
        }
      }
    }
  }

  b_y.set_size(1, (static_cast<int>(static_cast<short>(y.size(1)))));
  nx = static_cast<short>(y.size(1));
  for (k = 0; k < nx; k++) {
    b_y[k] = rt_powd_snf(10.0, y[k]);
  }

  log_spaced_frequency.set_size(b_y.size(1));
  nx = b_y.size(1);
  for (i = 0; i < nx; i++) {
    log_spaced_frequency[i] = b_y[i];
  }

  if (3 > log_spaced_frequency.size(0)) {
    i = 0;
    end = 0;
  } else {
    i = 2;
    end = log_spaced_frequency.size(0);
  }

  nx = end - i;
  bw_temp.set_size(nx);
  for (end = 0; end < nx; end++) {
    bw_temp[end] = (log_spaced_frequency[i + end] - log_spaced_frequency[end]) /
      2.0;
  }

  hamming(static_cast<double>(loop_ub), win_data, win_size);
  input_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    input_data[i] = input[i] * win_data[i];
  }

  fft(input_data, input_size, NFFT, Y);
  loop_ub = static_cast<int>(NFFT / 2.0 + 1.0);
  delta2 = fs / 2.0;
  i = static_cast<int>(rt_roundd_snf(NFFT / 2.0));
  end = i + 1;
  b_y.set_size(1, end);
  b_y[i] = delta2;
  if (b_y.size(1) >= 2) {
    b_y[0] = 0.0;
    if (b_y.size(1) >= 3) {
      if ((0.0 == -delta2) && (end > 2)) {
        for (k = 2; k <= i; k++) {
          b_y[k - 1] = delta2 * ((static_cast<double>(((k << 1) - i) - 1) - 1.0)
            / (static_cast<double>(end) - 1.0));
        }

        if ((end & 1) == 1) {
          b_y[end >> 1] = 0.0;
        }
      } else if ((delta2 < 0.0) && (std::abs(delta2) > 8.9884656743115785E+307))
      {
        delta2 /= static_cast<double>(b_y.size(1)) - 1.0;
        i = b_y.size(1);
        for (k = 0; k <= i - 3; k++) {
          b_y[k + 1] = delta2 * (static_cast<double>(k) + 1.0);
        }
      } else {
        delta1 = delta2 / (static_cast<double>(b_y.size(1)) - 1.0);
        i = b_y.size(1);
        for (k = 0; k <= i - 3; k++) {
          b_y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
        }
      }
    }
  }

  c_y.set_size(b_y.size(1));
  nx = b_y.size(1);
  for (i = 0; i < nx; i++) {
    c_y[i] = b_y[i];
  }

  b_Y.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    b_Y[i] = Y[i].re * Y[i].re - Y[i].im * -Y[i].im;
  }

  interp1(c_y, b_Y, log_spaced_frequency, locs);
  c_y.set_size((bw_temp.size(0) + 2));
  c_y[0] = bw_temp[0] / NFFT;
  loop_ub = bw_temp.size(0);
  for (i = 0; i < loop_ub; i++) {
    c_y[i + 1] = bw_temp[i] / NFFT;
  }

  c_y[bw_temp.size(0) + 1] = bw_temp[bw_temp.size(0) - 1] / NFFT;
  bw_temp.set_size(c_y.size(0));
  nx = c_y.size(0);
  for (k = 0; k < nx; k++) {
    bw_temp[k] = c_y[k];
  }

  c_y.set_size(locs.size(0));
  loop_ub = locs.size(0);
  for (i = 0; i < loop_ub; i++) {
    c_y[i] = locs[i] * bw_temp[i];
  }

  findpeaks(c_y, bw_temp, locs);
  end = bw_temp.size(0) - 1;
  nx = 0;
  for (i = 0; i <= end; i++) {
    if (bw_temp[i] > 10.0) {
      nx++;
    }
  }

  candidates.set_size(nx);
  nx = 0;
  for (i = 0; i <= end; i++) {
    if (bw_temp[i] > 10.0) {
      candidates[nx] = log_spaced_frequency[static_cast<int>(locs[i]) - 1];
      nx++;
    }
  }

  if (candidates.size(0) < 1) {
    f0 = -1.0;
  } else {
    f0 = candidates[0];
  }

  return f0;
}

// End of code generation (getPitch2.cpp)
