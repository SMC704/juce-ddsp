//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  chorus.cpp
//
//  Code generation for function 'chorus'
//


// Include files
#include "chorus.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_roundd_snf(double u);
static float rt_roundf_snf(float u);

// Function Definitions
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static float rt_roundf_snf(float u)
{
  float y;
  if (std::abs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = std::floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = std::ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

void chorus(int n_samples, double sample_rate, const double audio_in[4096],
            double buffer[4096], int *write_pointer, float amount, float rate,
            float phase_in, double audio_out[4096], float *phase_out)
{
  float q;
  coder::array<float, 2U> lfo_n;
  int nx;
  int k;
  float phase;
  coder::array<float, 2U> g;
  double delay;
  int qY;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  Chorus for the DDSP synth
  q = rt_roundf_snf(static_cast<float>(sample_rate) * rate);
  if (rtIsNaNF(q)) {
    lfo_n.set_size(1, 1);
    lfo_n[0] = rtNaNF;
  } else if (q < 1.0F) {
    lfo_n.set_size(1, 0);
  } else if (rtIsInfF(q) && (1.0F == q)) {
    lfo_n.set_size(1, 1);
    lfo_n[0] = rtNaNF;
  } else {
    nx = static_cast<int>(q - 1.0);
    lfo_n.set_size(1, (nx + 1));
    for (k = 0; k <= nx; k++) {
      lfo_n[k] = static_cast<float>(static_cast<double>(k) + 1.0);
    }
  }

  if (rtIsNaNF(phase_in) || rtIsInfF(phase_in)) {
    phase = rtNaNF;
  } else if (phase_in == 0.0F) {
    phase = 0.0F;
  } else {
    boolean_T rEQ0;
    phase = std::fmod(phase_in, 6.28318548F);
    rEQ0 = (phase == 0.0F);
    if (!rEQ0) {
      q = std::abs(phase_in / 6.28318548F);
      rEQ0 = !(std::abs(q - std::floor(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      phase = 0.0F;
    } else {
      if (phase_in < 0.0F) {
        phase += 6.28318548F;
      }
    }
  }

  q = 6.28318548F * rate;
  k = lfo_n.size(0) * lfo_n.size(1);
  lfo_n.set_size(1, lfo_n.size(1));
  nx = k - 1;
  for (k = 0; k <= nx; k++) {
    lfo_n[k] = q * (lfo_n[k] / static_cast<float>(sample_rate)) + phase;
  }

  g.set_size(1, lfo_n.size(1));
  nx = lfo_n.size(0) * lfo_n.size(1);
  for (k = 0; k < nx; k++) {
    g[k] = lfo_n[k];
  }

  nx = lfo_n.size(1);
  for (k = 0; k < nx; k++) {
    g[k] = std::sin(g[k]);
  }

  k = g.size(0) * g.size(1);
  g.set_size(1, g.size(1));
  nx = k - 1;
  for (k = 0; k <= nx; k++) {
    g[k] = (g[k] + 1.0F) * 5.0F / 2.0F;
  }

  std::memset(&audio_out[0], 0, 4096U * sizeof(double));
  delay = rt_roundd_snf(0.02 * sample_rate);
  for (int n = 0; n < n_samples; n++) {
    double d;
    d = static_cast<double>(*write_pointer) - delay;
    if (d < 2.147483648E+9) {
      if (d >= -2.147483648E+9) {
        k = static_cast<int>(d);
      } else {
        k = MIN_int32_T;
      }
    } else if (d >= 2.147483648E+9) {
      k = MAX_int32_T;
    } else {
      k = 0;
    }

    q = rt_roundf_snf(g[n]);
    if (q < 2.14748365E+9F) {
      if (q >= -2.14748365E+9F) {
        nx = static_cast<int>(q);
      } else {
        nx = MIN_int32_T;
      }
    } else if (q >= 2.14748365E+9F) {
      nx = MAX_int32_T;
    } else {
      nx = 0;
    }

    if ((k >= 0) && (nx < k - MAX_int32_T)) {
      qY = MAX_int32_T;
    } else if ((k < 0) && (nx > k - MIN_int32_T)) {
      qY = MIN_int32_T;
    } else {
      qY = k - nx;
    }

    if (qY > 2147479551) {
      qY = MAX_int32_T;
    } else {
      qY += 4096;
    }

    k = *write_pointer;
    if (k > 2147483646) {
      nx = MAX_int32_T;
    } else {
      nx = k + 1;
    }

    buffer[nx - 1] = audio_in[n];
    k = qY - ((qY >> 12) << 12);
    if (k > 2147483646) {
      qY = MAX_int32_T;
    } else {
      qY = k + 1;
    }

    audio_out[n] = static_cast<float>(audio_in[n]) + static_cast<float>
      (buffer[qY - 1]) * amount;

    //          audio_out(n,1) = buffer(read_pointer, 1);
    k = *write_pointer;
    if (k > 2147483646) {
      qY = MAX_int32_T;
    } else {
      qY = k + 1;
    }

    *write_pointer = qY - ((qY >> 12) << 12);
  }

  //      plot(audio_out);
  //      audio_out(1:n_samples) = rescale(audio_out(1:n_samples), -1, 1);
  *phase_out = lfo_n[lfo_n.size(1) - 1];
}

// End of code generation (chorus.cpp)
