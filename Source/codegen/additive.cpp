//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  additive.cpp
//
//  Code generation for function 'additive'
//


// Include files
#include "additive.h"
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include "useConstantDim.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void b_scale_fn(const double x[51200], double y[51200]);
static void remove_above_nyquist(const double harmonic_frequencies[51200],
  double harmonic_distribution[51200], double sample_rate);
static void scale_fn(const double x[1024], double y[1024]);

// Function Definitions
static void b_scale_fn(const double x[51200], double y[51200])
{
  //  Scale Function
  //  Exponentiated Sigmoid pointwise nonlinearity
  for (int k = 0; k < 51200; k++) {
    y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
      + 1.0E-7;
  }
}

static void remove_above_nyquist(const double harmonic_frequencies[51200],
  double harmonic_distribution[51200], double sample_rate)
{
  int trueCount;
  int i;
  coder::array<unsigned short, 1U> r;

  //  Set amplitudes for oscillators above nyquist to 0
  trueCount = 0;
  for (i = 0; i < 51200; i++) {
    if (harmonic_frequencies[i] >= sample_rate / 2.0) {
      trueCount++;
    }
  }

  r.set_size(trueCount);
  trueCount = 0;
  for (i = 0; i < 51200; i++) {
    if (harmonic_frequencies[i] >= sample_rate / 2.0) {
      r[trueCount] = static_cast<unsigned short>(i + 1);
      trueCount++;
    }
  }

  trueCount = r.size(0);
  for (i = 0; i < trueCount; i++) {
    harmonic_distribution[r[i] - 1] = 0.0;
  }
}

static void scale_fn(const double x[1024], double y[1024])
{
  //  Scale Function
  //  Exponentiated Sigmoid pointwise nonlinearity
  for (int k = 0; k < 1024; k++) {
    y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
      + 1.0E-7;
  }
}

void additive(double sample_rate, double amplitudes[1024], double
              harmonic_distribution[51200], const double f0[1024], const double
              prev_phases[50], double audio[1024], double last_phases[50])
{
  double harm_sum[1024];
  static double harmonic_frequencies[51200];
  int j;
  int k;
  int xoffset;
  static double harmonic_amplitudes[51200];
  double r;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  ADDITIVE SYNTH
  //
  //  INPUTS:
  //
  //  sample_rate: int
  //  amplitudes: Frame-wise oscillator peak amplitude. Shape: [n_frames, 1]
  //  harmonic distribution: Frame-wise harmonic amplitude variations. Shape. [n_frames, n_harmonics] 
  //  f0: Frame-wise fundamental frequency in Hz. Shape: [n_frames, 1]
  //
  //  RETURNS:
  //
  //  Sample-wise audio signal
  //  Scale the amplitudes
  std::memcpy(&harm_sum[0], &amplitudes[0], 1024U * sizeof(double));
  scale_fn(harm_sum, amplitudes);
  std::memcpy(&harmonic_frequencies[0], &harmonic_distribution[0], 51200U *
              sizeof(double));
  b_scale_fn(harmonic_frequencies, harmonic_distribution);

  //  Bandlimit the harmonic distribution
  //  Calculate sample-wise oscillator frequencies of harmonics
  for (j = 0; j < 50; j++) {
    for (k = 0; k < 1024; k++) {
      harmonic_frequencies[k + (j << 10)] = f0[k] * (static_cast<double>(j) +
        1.0);
    }
  }

  remove_above_nyquist(harmonic_frequencies, harmonic_distribution, sample_rate);

  //  Normalize the harmonic distribution
  //      harmonic_distribution = harmonic_distribution ./ sum(harmonic_distribution, 2); %%%%% DO A FOR LOOP! 
  std::memcpy(&harm_sum[0], &harmonic_distribution[0], 1024U * sizeof(double));
  for (k = 0; k < 49; k++) {
    xoffset = (k + 1) << 10;
    for (j = 0; j < 1024; j++) {
      harm_sum[j] += harmonic_distribution[xoffset + j];
    }
  }

  for (xoffset = 0; xoffset < 50; xoffset++) {
    for (j = 0; j < 1024; j++) {
      k = j + (xoffset << 10);
      harmonic_distribution[k] /= harm_sum[j];
    }
  }

  //  Create harmonic amplitudes
  //      harmonic_amplitudes = amplitudes .* harmonic_distribution;
  std::memset(&harmonic_amplitudes[0], 0, 51200U * sizeof(double));
  for (xoffset = 0; xoffset < 50; xoffset++) {
    for (j = 0; j < 1024; j++) {
      k = j + (xoffset << 10);
      harmonic_amplitudes[k] = harmonic_distribution[k] * amplitudes[j];
    }
  }

  // radiant/second
  // radiant/sample
  //  Accumulate phase and synthesize
  for (j = 0; j < 51200; j++) {
    harmonic_frequencies[j] = harmonic_frequencies[j] * 2.0 * 3.1415926535897931
      / sample_rate;
  }

  useConstantDim(harmonic_frequencies);

  //  Save last phases of all harmonics for next buffer
  //      phases = phases+prev_phases;
  for (xoffset = 0; xoffset < 50; xoffset++) {
    for (j = 0; j < 1024; j++) {
      k = j + (xoffset << 10);
      harmonic_frequencies[k] += prev_phases[xoffset];
    }
  }

  for (k = 0; k < 51200; k++) {
    if (rtIsNaN(harmonic_frequencies[k]) || rtIsInf(harmonic_frequencies[k])) {
      r = rtNaN;
    } else if (harmonic_frequencies[k] == 0.0) {
      r = 0.0;
    } else {
      boolean_T rEQ0;
      r = std::fmod(harmonic_frequencies[k], 6.2831853071795862);
      rEQ0 = (r == 0.0);
      if (!rEQ0) {
        double q;
        q = std::abs(harmonic_frequencies[k] / 6.2831853071795862);
        rEQ0 = !(std::abs(q - std::floor(q + 0.5)) > 2.2204460492503131E-16 * q);
      }

      if (rEQ0) {
        r = 0.0;
      } else {
        if (harmonic_frequencies[k] < 0.0) {
          r += 6.2831853071795862;
        }
      }
    }

    harmonic_frequencies[k] = r;
  }

  for (j = 0; j < 50; j++) {
    last_phases[j] = harmonic_frequencies[(j << 10) + 1023];
  }

  //  Convert to waveforms
  for (k = 0; k < 51200; k++) {
    r = std::sin(harmonic_frequencies[k]);
    harmonic_frequencies[k] = r;
    harmonic_amplitudes[k] *= r;
  }

  std::memcpy(&audio[0], &harmonic_amplitudes[0], 1024U * sizeof(double));
  for (k = 0; k < 49; k++) {
    xoffset = (k + 1) << 10;
    for (j = 0; j < 1024; j++) {
      audio[j] += harmonic_amplitudes[xoffset + j];
    }
  }
}

// End of code generation (additive.cpp)
