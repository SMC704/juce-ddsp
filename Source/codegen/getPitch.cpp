//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  getPitch.cpp
//
//  Code generation for function 'getPitch'
//


// Include files
#include "getPitch.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "fft.h"
#include "findpeaks.h"
#include "gencoswin.h"
#include "iseven.h"
#include "linspace.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions
double getPitch(double n_samples, const double input[4096], double fs)
{
  coder::array<creal_T, 1U> Y;
  coder::array<double, 2U> b;
  coder::array<double, 2U> z1;
  coder::array<double, 1U> Vq;
  coder::array<double, 1U> bw;
  coder::array<double, 1U> bw_temp;
  coder::array<double, 1U> candidates;
  coder::array<double, 1U> log_spaced_frequency;
  coder::array<double, 1U> r;
  double b_win_data[4097];
  double win_data[4097];
  double input_data[4096];
  double tmp_data[2048];
  double NFFT;
  double delta1;
  double f0;
  int input_size[1];
  int tmp_size[1];
  int i;
  int k;
  int loop_ub;
  int low_ip1;
  int mid_i;
  int n;
  int nrows;
  int nx;
  unsigned int u;
  signed char w_data[1];
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  getPitch
  //  parameters: n_samples (int32), input (double[4096]), fs (double)
  //  output: f0 (double)
  if (1.0 > n_samples) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
  }

  delta1 = frexp(static_cast<double>(static_cast<int>(std::abs(2.0 *
    static_cast<double>(loop_ub) - 1.0))), &nrows);
  if (delta1 == 0.5) {
    nrows--;
  }

  NFFT = rt_powd_snf(2.0, static_cast<double>(nrows));
  delta1 = fs / 2.0 - 1.0;
  if (!(delta1 < 4000.0)) {
    delta1 = 4000.0;
  }

  coder::linspace(std::log10(delta1), NFFT, b);
  z1.set_size(1, b.size(1));
  nx = b.size(1);
  for (k = 0; k < nx; k++) {
    z1[k] = rt_powd_snf(10.0, b[k]);
  }

  log_spaced_frequency.set_size(z1.size(1));
  nrows = z1.size(1);
  for (i = 0; i < nrows; i++) {
    log_spaced_frequency[i] = z1[i];
  }

  delta1 = fs / 2.0;
  u = static_cast<unsigned int>(rt_roundd_snf(NFFT / 2.0));
  z1.set_size(1, (static_cast<int>(u) + 1));
  z1[static_cast<int>(u)] = delta1;
  if (z1.size(1) >= 2) {
    z1[0] = 0.0;
    if (z1.size(1) >= 3) {
      if ((0.0 == -delta1) && (static_cast<int>(u) + 1 > 2)) {
        i = static_cast<int>(u);
        for (k = 2; k <= i; k++) {
          z1[k - 1] = delta1 * ((static_cast<double>(((k << 1) - static_cast<int>
            (u)) - 1) - 1.0) / (static_cast<double>(static_cast<int>(u) + 1) -
                                1.0));
        }

        if (((static_cast<int>(u) + 1) & 1) == 1) {
          z1[(static_cast<int>(u) + 1) >> 1] = 0.0;
        }
      } else if ((delta1 < 0.0) && (std::abs(delta1) > 8.9884656743115785E+307))
      {
        delta1 /= static_cast<double>(z1.size(1)) - 1.0;
        i = z1.size(1);
        for (k = 0; k <= i - 3; k++) {
          z1[k + 1] = delta1 * (static_cast<double>(k) + 1.0);
        }
      } else {
        delta1 /= static_cast<double>(z1.size(1)) - 1.0;
        i = z1.size(1);
        for (k = 0; k <= i - 3; k++) {
          z1[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
        }
      }
    }
  }

  if (3 > log_spaced_frequency.size(0)) {
    i = 0;
    n = 0;
  } else {
    i = 2;
    n = log_spaced_frequency.size(0);
  }

  nrows = n - i;
  bw_temp.set_size(nrows);
  for (n = 0; n < nrows; n++) {
    bw_temp[n] = (log_spaced_frequency[i + n] - log_spaced_frequency[n]) / 2.0;
  }

  bw.set_size((bw_temp.size(0) + 2));
  bw[0] = bw_temp[0] / NFFT;
  nrows = bw_temp.size(0);
  for (i = 0; i < nrows; i++) {
    bw[i + 1] = bw_temp[i] / NFFT;
  }

  bw[bw_temp.size(0) + 1] = bw_temp[bw_temp.size(0) - 1] / NFFT;
  nrows = 1;
  w_data[0] = 0;
  n = 0;
  if (loop_ub == 0) {
    nrows = 0;
    n = 1;
  } else {
    if (loop_ub == 1) {
      w_data[0] = 1;
      n = 1;
    }
  }

  if (0 <= nrows - 1) {
    win_data[0] = w_data[0];
  }

  if (n == 0) {
    if (coder::iseven(static_cast<double>(loop_ub))) {
      coder::calc_window(static_cast<double>(loop_ub) / 2.0, static_cast<double>
                         (loop_ub), tmp_data, tmp_size);
      nx = tmp_size[0];
      nrows = tmp_size[0];
      if (0 <= nrows - 1) {
        std::memcpy(&win_data[0], &tmp_data[0], nrows * sizeof(double));
      }

      if (1 > tmp_size[0]) {
        i = 0;
        n = 1;
        low_ip1 = -1;
      } else {
        i = tmp_size[0] - 1;
        n = -1;
        low_ip1 = 0;
      }

      nrows = div_s32_floor(low_ip1 - i, n);
      mid_i = (tmp_size[0] + nrows) + 1;
      if (0 <= nx - 1) {
        std::memcpy(&b_win_data[0], &win_data[0], nx * sizeof(double));
      }

      for (low_ip1 = 0; low_ip1 <= nrows; low_ip1++) {
        b_win_data[low_ip1 + nx] = win_data[i + n * low_ip1];
      }

      if (0 <= mid_i - 1) {
        std::memcpy(&win_data[0], &b_win_data[0], mid_i * sizeof(double));
      }
    } else {
      coder::calc_window((static_cast<double>(loop_ub) + 1.0) / 2.0,
                         static_cast<double>(loop_ub), tmp_data, tmp_size);
      nx = tmp_size[0];
      nrows = tmp_size[0];
      if (0 <= nrows - 1) {
        std::memcpy(&win_data[0], &tmp_data[0], nrows * sizeof(double));
      }

      if (1 > tmp_size[0] - 1) {
        i = 0;
        n = 1;
        low_ip1 = -1;
      } else {
        i = tmp_size[0] - 2;
        n = -1;
        low_ip1 = 0;
      }

      nrows = div_s32_floor(low_ip1 - i, n);
      mid_i = (tmp_size[0] + nrows) + 1;
      if (0 <= nx - 1) {
        std::memcpy(&b_win_data[0], &win_data[0], nx * sizeof(double));
      }

      for (low_ip1 = 0; low_ip1 <= nrows; low_ip1++) {
        b_win_data[low_ip1 + nx] = win_data[i + n * low_ip1];
      }

      if (0 <= mid_i - 1) {
        std::memcpy(&win_data[0], &b_win_data[0], mid_i * sizeof(double));
      }
    }
  }

  input_size[0] = loop_ub;
  for (i = 0; i < loop_ub; i++) {
    input_data[i] = input[i] * win_data[i];
  }

  coder::fft(input_data, input_size, NFFT, Y);
  loop_ub = static_cast<int>(NFFT / 2.0 + 1.0);
  r.set_size(bw.size(0));
  nrows = bw.size(0);
  for (k = 0; k < nrows; k++) {
    r[k] = bw[k];
  }

  bw_temp.set_size(z1.size(1));
  nrows = z1.size(1);
  for (i = 0; i < nrows; i++) {
    bw_temp[i] = z1[i];
  }

  bw.set_size(loop_ub);
  for (i = 0; i < loop_ub; i++) {
    bw[i] = Y[i].re * Y[i].re - Y[i].im * -Y[i].im;
  }

  nx = bw_temp.size(0) - 1;
  Vq.set_size(log_spaced_frequency.size(0));
  loop_ub = log_spaced_frequency.size(0);
  for (i = 0; i < loop_ub; i++) {
    Vq[i] = rtNaN;
  }

  if (log_spaced_frequency.size(0) != 0) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(bw_temp[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (bw_temp[1] < bw_temp[0]) {
          i = (nx + 1) >> 1;
          for (n = 0; n < i; n++) {
            delta1 = bw_temp[n];
            nrows = nx - n;
            bw_temp[n] = bw_temp[nrows];
            bw_temp[nrows] = delta1;
          }

          if (bw.size(0) > 1) {
            n = bw.size(0) - 1;
            nrows = bw.size(0) >> 1;
            for (k = 0; k < nrows; k++) {
              delta1 = bw[k];
              nx = n - k;
              bw[k] = bw[nx];
              bw[nx] = delta1;
            }
          }
        }

        nrows = log_spaced_frequency.size(0);
        for (k = 0; k < nrows; k++) {
          if (rtIsNaN(log_spaced_frequency[k])) {
            Vq[k] = rtNaN;
          } else {
            if ((!(log_spaced_frequency[k] > bw_temp[bw_temp.size(0) - 1])) && (
                 !(log_spaced_frequency[k] < bw_temp[0]))) {
              n = bw_temp.size(0);
              nx = 1;
              low_ip1 = 2;
              while (n > low_ip1) {
                mid_i = (nx >> 1) + (n >> 1);
                if (((nx & 1) == 1) && ((n & 1) == 1)) {
                  mid_i++;
                }

                if (log_spaced_frequency[k] >= bw_temp[mid_i - 1]) {
                  nx = mid_i;
                  low_ip1 = mid_i + 1;
                } else {
                  n = mid_i;
                }
              }

              delta1 = bw_temp[nx - 1];
              delta1 = (log_spaced_frequency[k] - delta1) / (bw_temp[nx] -
                delta1);
              if (delta1 == 0.0) {
                Vq[k] = bw[nx - 1];
              } else if (delta1 == 1.0) {
                Vq[k] = bw[nx];
              } else {
                NFFT = bw[nx - 1];
                if (NFFT == bw[nx]) {
                  Vq[k] = NFFT;
                } else {
                  Vq[k] = (1.0 - delta1) * NFFT + delta1 * bw[nx];
                }
              }
            }
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  loop_ub = Vq.size(0);
  for (i = 0; i < loop_ub; i++) {
    Vq[i] = Vq[i] * r[i];
  }

  coder::findpeaks(Vq, bw_temp, bw);
  nrows = bw_temp.size(0) - 1;
  n = 0;
  for (nx = 0; nx <= nrows; nx++) {
    if (bw_temp[nx] > 10.0) {
      n++;
    }
  }

  candidates.set_size(n);
  n = 0;
  for (nx = 0; nx <= nrows; nx++) {
    if (bw_temp[nx] > 10.0) {
      candidates[n] = log_spaced_frequency[static_cast<int>(bw[nx]) - 1];
      n++;
    }
  }

  if (candidates.size(0) < 1) {
    f0 = -1.0;
  } else {
    f0 = candidates[0];
  }

  return f0;
}

// End of code generation (getPitch.cpp)
