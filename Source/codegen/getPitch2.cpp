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
#include "linspace.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <math.h>

// Function Definitions
double getPitch2(double n_samples, const double input[4096], double fs)
{
  double f0;
  int loop_ub;
  double delta1;
  int nx;
  double NFFT;
  coder::array<double, 2U> b;
  coder::array<double, 2U> y;
  int k;
  coder::array<double, 1U> log_spaced_frequency;
  int end;
  int i;
  coder::array<double, 1U> bw_temp;
  double win_data[4097];
  int win_size[1];
  int input_size[1];
  double input_data[4096];
  coder::array<creal_T, 1U> Y;
  coder::array<double, 1U> b_y;
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

  delta1 = frexp(static_cast<double>(static_cast<int>(std::abs(2.0 *
    static_cast<double>(loop_ub) - 1.0))), &nx);
  if (delta1 == 0.5) {
    nx--;
  }

  NFFT = rt_powd_snf(2.0, static_cast<double>(nx));
  delta1 = fs / 2.0 - 1.0;
  if (!(delta1 < 4000.0)) {
    delta1 = 4000.0;
  }

  linspace(std::log10(delta1), NFFT, b);
  y.set_size(1, b.size(1));
  nx = b.size(1);
  for (k = 0; k < nx; k++) {
    y[k] = rt_powd_snf(10.0, b[k]);
  }

  log_spaced_frequency.set_size(y.size(1));
  nx = y.size(1);
  for (end = 0; end < nx; end++) {
    log_spaced_frequency[end] = y[end];
  }

  if (3 > log_spaced_frequency.size(0)) {
    end = 0;
    i = 0;
  } else {
    end = 2;
    i = log_spaced_frequency.size(0);
  }

  nx = i - end;
  bw_temp.set_size(nx);
  for (i = 0; i < nx; i++) {
    bw_temp[i] = (log_spaced_frequency[end + i] - log_spaced_frequency[i]) / 2.0;
  }

  hamming(static_cast<double>(loop_ub), win_data, win_size);
  input_size[0] = loop_ub;
  for (end = 0; end < loop_ub; end++) {
    input_data[end] = input[end] * win_data[end];
  }

  fft(input_data, input_size, NFFT, Y);
  loop_ub = static_cast<int>(NFFT / 2.0 + 1.0);
  delta1 = fs / 2.0;
  end = static_cast<int>(rt_roundd_snf(NFFT / 2.0));
  i = end + 1;
  y.set_size(1, i);
  y[end] = delta1;
  if (y.size(1) >= 2) {
    y[0] = 0.0;
    if (y.size(1) >= 3) {
      if ((0.0 == -delta1) && (i > 2)) {
        for (k = 2; k <= end; k++) {
          y[k - 1] = delta1 * ((static_cast<double>(((k << 1) - end) - 1) - 1.0)
                               / (static_cast<double>(i) - 1.0));
        }

        if ((i & 1) == 1) {
          y[i >> 1] = 0.0;
        }
      } else if ((delta1 < 0.0) && (std::abs(delta1) > 8.9884656743115785E+307))
      {
        delta1 /= static_cast<double>(y.size(1)) - 1.0;
        end = y.size(1);
        for (k = 0; k <= end - 3; k++) {
          y[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
        }
      } else {
        delta1 /= static_cast<double>(y.size(1)) - 1.0;
        end = y.size(1);
        for (k = 0; k <= end - 3; k++) {
          y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
        }
      }
    }
  }

  b_y.set_size(y.size(1));
  nx = y.size(1);
  for (end = 0; end < nx; end++) {
    b_y[end] = y[end];
  }

  b_Y.set_size(loop_ub);
  for (end = 0; end < loop_ub; end++) {
    b_Y[end] = Y[end].re * Y[end].re - Y[end].im * -Y[end].im;
  }

  interp1(b_y, b_Y, log_spaced_frequency, locs);
  b_y.set_size((bw_temp.size(0) + 2));
  b_y[0] = bw_temp[0] / NFFT;
  loop_ub = bw_temp.size(0);
  for (end = 0; end < loop_ub; end++) {
    b_y[end + 1] = bw_temp[end] / NFFT;
  }

  b_y[bw_temp.size(0) + 1] = bw_temp[bw_temp.size(0) - 1] / NFFT;
  bw_temp.set_size(b_y.size(0));
  nx = b_y.size(0);
  for (k = 0; k < nx; k++) {
    bw_temp[k] = b_y[k];
  }

  b_y.set_size(locs.size(0));
  loop_ub = locs.size(0);
  for (end = 0; end < loop_ub; end++) {
    b_y[end] = locs[end] * bw_temp[end];
  }

  findpeaks(b_y, bw_temp, locs);
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
