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
#include "SystemCore.h"
#include "additive.h"
#include "firls.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
void subtractive(double n_samples, const double magnitudes[65], double color,
                 double out[4096])
{
  dsp_ColoredNoise white_n;
  b_dsp_ColoredNoise brown_n;
  c_dsp_ColoredNoise violet_n;
  static double white_noise[4161];
  static double brown_noise[4161];
  static double violet_noise[4161];
  double signal_tmp;
  int i;
  int loop_ub;
  double b_data[129];
  int b_size[2];
  int nx_m_nb;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  magnitudes: row = frames, column = freq responses
  //  magnitudes should be 65
  //  %     normalize magnitudes
  //      initial_bias = 1;
  //
  //  %     optional; colab examplees do not use it
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
  signal_tmp = std::abs(color);
  for (i = 0; i < 4161; i++) {
    white_noise[i] *= 1.0 - signal_tmp;
  }

  if (color > 0.0) {
    for (i = 0; i < 4161; i++) {
      white_noise[i] += color * violet_noise[i];
    }
  }

  if (color < 0.0) {
    for (i = 0; i < 4161; i++) {
      white_noise[i] += signal_tmp * brown_noise[i];
    }
  }

  //      signal = rand(n_samples, 1) * 2 - 1;
  if (1.0 > n_samples + 65.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples + 65.0);
  }

  firls(*(double (*)[64])&magnitudes[0], b_data, b_size);
  if (0 <= loop_ub - 1) {
    std::memset(&brown_noise[0], 0, loop_ub * sizeof(double));
  }

  if (loop_ub >= 258) {
    for (int k = 0; k < 129; k++) {
      nx_m_nb = k + 1;
      for (int j = nx_m_nb; j <= loop_ub; j++) {
        brown_noise[j - 1] += b_data[k] * white_noise[(j - k) - 1];
      }
    }
  } else {
    int k;
    int j;
    int naxpy;
    int filtered_signal_tmp;
    if (loop_ub > 129) {
      nx_m_nb = loop_ub - 130;
    } else {
      nx_m_nb = -1;
    }

    for (k = 0; k <= nx_m_nb; k++) {
      for (j = 0; j < 129; j++) {
        filtered_signal_tmp = k + j;
        brown_noise[filtered_signal_tmp] += white_noise[k] * b_data[j];
      }
    }

    naxpy = (loop_ub - nx_m_nb) - 2;
    i = nx_m_nb + 2;
    for (k = i; k <= loop_ub; k++) {
      for (j = 0; j <= naxpy; j++) {
        filtered_signal_tmp = (k + j) - 1;
        brown_noise[filtered_signal_tmp] += white_noise[k - 1] * b_data[j];
      }

      naxpy--;
    }
  }

  std::memset(&out[0], 0, 4096U * sizeof(double));

  //      out(1:n_samples) = filtered_signal(66:n_samples+65);
  if (66.0 > n_samples + 65.0) {
    i = 0;
    nx_m_nb = 0;
  } else {
    i = 65;
    nx_m_nb = static_cast<int>(n_samples + 65.0);
  }

  loop_ub = nx_m_nb - i;
  for (nx_m_nb = 0; nx_m_nb < loop_ub; nx_m_nb++) {
    out[nx_m_nb] = brown_noise[i + nx_m_nb];
  }
}

// End of code generation (subtractive.cpp)
