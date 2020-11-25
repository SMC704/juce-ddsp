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
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void remove_above_nyquist(const coder::array<double, 2U>
  &harmonic_frequencies, double harmonic_distribution[50], double sample_rate);

// Function Definitions
static void remove_above_nyquist(const coder::array<double, 2U>
  &harmonic_frequencies, double harmonic_distribution[50], double sample_rate)
{
  double b_sample_rate;
  int trueCount;
  int partialTrueCount;
  signed char tmp_data[50];

  //  Set amplitudes for oscillators above nyquist to 0
  b_sample_rate = sample_rate / 2.0;
  trueCount = 0;
  partialTrueCount = 0;
  for (int i = 0; i < 50; i++) {
    boolean_T b;
    b = (harmonic_frequencies[harmonic_frequencies.size(0) * i] >= b_sample_rate);
    if (b) {
      trueCount++;
      tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
      partialTrueCount++;
    }
  }

  for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++) {
    harmonic_distribution[tmp_data[partialTrueCount] - 1] = 0.0;
  }

  //  function plot_controls(amplitudes, harmonic_distribution, f0)
  //
  //      % figure('Name', 'Synth Controls');
  //      t = tiledlayout(3,1);
  //      nexttile;
  //      plot(amplitudes);
  //      title('Amplitudes');
  //      ylabel('amplitude');
  //      nexttile;
  //      plot(harmonic_distribution);
  //      title('Harmonic Distribution');
  //      ylabel('amplitude');
  //      nexttile;
  //      plot(f0);
  //      title('Fundamental Frequency');
  //      ylabel('frequency');
  //      xlabel(t,'samples');
  //      t.TileSpacing = 'none';
  //
  //  end
}

void additive(int n_samples, double sample_rate, const double amplitudes[4096],
              double harmonic_distribution[50], const double f0[4096], const
              double prev_phases[50], double audio_data[], int audio_size[1],
              double last_phases[50])
{
  int loop_ub;
  int b_loop_ub;
  coder::array<double, 2U> harmonic_frequencies;
  int i;
  int i1;
  coder::array<double, 2U> harmonic_amplitudes;
  int nx;
  int k;
  short subsb_idx_1;
  coder::array<double, 2U> x;
  double harmonic_frequencies_data[4096];
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
  //  harmonic distribution: Frame-wise harmonic amplitude variations. Shape. [n_harmonics] 
  //  f0: Frame-wise fundamental frequency in Hz. Shape: [n_frames, 1]
  //
  //  RETURNS:
  //
  //  Sample-wise audio signal
  //  Resize the input
  if (1 > n_samples) {
    loop_ub = 0;
    b_loop_ub = 0;
  } else {
    loop_ub = n_samples;
    b_loop_ub = n_samples;
  }

  //  Scale the amplitudes
  //      amplitudes = scale_fn(amplitudes);
  //      harmonic_distribution = scale_fn(harmonic_distribution);
  //  Bandlimit the harmonic distribution
  //  Calculate sample-wise oscillator frequencies of harmonics
  harmonic_frequencies.set_size(b_loop_ub, 50);
  for (i = 0; i < 50; i++) {
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      harmonic_frequencies[i1 + harmonic_frequencies.size(0) * i] = f0[i1] * (
        static_cast<double>(i) + 1.0);
    }
  }

  remove_above_nyquist(harmonic_frequencies, harmonic_distribution, sample_rate);

  //  Normalize the harmonic distribution
  //      harm_sum = sum(harmonic_distribution,2);
  //      for c = 1:size(harmonic_distribution,2)
  //          harmonic_distribution(1:end,c) = harmonic_distribution(1:end,c) ./ harm_sum; 
  //      end
  //  Create harmonic amplitudes
  harmonic_amplitudes.set_size(loop_ub, 50);
  b_loop_ub = loop_ub * 50;
  for (i = 0; i < b_loop_ub; i++) {
    harmonic_amplitudes[i] = 0.0;
  }

  for (nx = 0; nx < 50; nx++) {
    for (i = 0; i < loop_ub; i++) {
      harmonic_amplitudes[i + harmonic_amplitudes.size(0) * nx] =
        harmonic_distribution[nx] * amplitudes[i];
    }
  }

  // radiant/second
  b_loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
  harmonic_frequencies.set_size(harmonic_frequencies.size(0), 50);
  for (i = 0; i < b_loop_ub; i++) {
    harmonic_frequencies[i] = harmonic_frequencies[i] * 2.0 * 3.1415926535897931
      / sample_rate;
  }

  // radiant/sample
  //  Accumulate phase and synthesize
  if (harmonic_frequencies.size(0) != 1) {
    nx = 1;
  } else {
    nx = 2;
  }

  if (1 == nx) {
    if (harmonic_frequencies.size(0) != 0) {
      for (k = 0; k < 50; k++) {
        i = harmonic_frequencies.size(0);
        if (0 <= i - 2) {
          subsb_idx_1 = static_cast<short>(k + 1);
        }

        for (nx = 0; nx <= i - 2; nx++) {
          i1 = static_cast<short>(static_cast<short>(nx + 1) + 1) - 1;
          b_loop_ub = subsb_idx_1 - 1;
          harmonic_frequencies[i1 + harmonic_frequencies.size(0) * b_loop_ub] =
            harmonic_frequencies[nx + harmonic_frequencies.size(0) * k] +
            harmonic_frequencies[i1 + harmonic_frequencies.size(0) * b_loop_ub];
        }
      }
    }
  } else {
    if (harmonic_frequencies.size(0) != 0) {
      for (k = 0; k < 49; k++) {
        i = harmonic_frequencies.size(0);
        for (nx = 0; nx < i; nx++) {
          i1 = static_cast<short>(nx + 1) - 1;
          b_loop_ub = k + 1;
          harmonic_frequencies[i1 + harmonic_frequencies.size(0) * b_loop_ub] =
            harmonic_frequencies[nx + harmonic_frequencies.size(0) * k] +
            harmonic_frequencies[i1 + harmonic_frequencies.size(0) * b_loop_ub];
        }
      }
    }
  }

  //  Save last phases of all harmonics for next buffer;
  for (nx = 0; nx < 50; nx++) {
    if (1 > harmonic_frequencies.size(0)) {
      b_loop_ub = 0;
    } else {
      b_loop_ub = harmonic_frequencies.size(0);
    }

    for (i = 0; i < b_loop_ub; i++) {
      harmonic_frequencies_data[i] = harmonic_frequencies[i +
        harmonic_frequencies.size(0) * nx] + prev_phases[nx];
    }

    for (i = 0; i < b_loop_ub; i++) {
      harmonic_frequencies[i + harmonic_frequencies.size(0) * nx] =
        harmonic_frequencies_data[i];
    }
  }

  x.set_size(harmonic_frequencies.size(0), 50);
  b_loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
  for (i = 0; i < b_loop_ub; i++) {
    x[i] = harmonic_frequencies[i];
  }

  subsb_idx_1 = static_cast<short>(harmonic_frequencies.size(0));
  harmonic_frequencies.set_size((static_cast<int>(static_cast<short>
    (harmonic_frequencies.size(0)))), 50);
  nx = subsb_idx_1 * 50;
  for (k = 0; k < nx; k++) {
    if (rtIsNaN(x[k]) || rtIsInf(x[k])) {
      r = rtNaN;
    } else if (x[k] == 0.0) {
      r = 0.0;
    } else {
      boolean_T rEQ0;
      r = std::fmod(x[k], 6.2831853071795862);
      rEQ0 = (r == 0.0);
      if (!rEQ0) {
        double q;
        q = std::abs(x[k] / 6.2831853071795862);
        rEQ0 = !(std::abs(q - std::floor(q + 0.5)) > 2.2204460492503131E-16 * q);
      }

      if (rEQ0) {
        r = 0.0;
      } else {
        if (x[k] < 0.0) {
          r += 6.2831853071795862;
        }
      }
    }

    harmonic_frequencies[k] = r;
  }

  for (i = 0; i < 50; i++) {
    last_phases[i] = harmonic_frequencies[(harmonic_frequencies.size(0) +
      harmonic_frequencies.size(0) * i) - 1];
  }

  //  Convert to waveforms
  nx = harmonic_frequencies.size(0) * 50;
  for (k = 0; k < nx; k++) {
    harmonic_frequencies[k] = std::sin(harmonic_frequencies[k]);
  }

  audio_size[0] = static_cast<short>(loop_ub);
  loop_ub = static_cast<short>(loop_ub);
  if (0 <= loop_ub - 1) {
    std::memset(&audio_data[0], 0, loop_ub * sizeof(double));
  }

  if (1 > audio_size[0]) {
    loop_ub = 0;
  } else {
    loop_ub = audio_size[0];
  }

  for (nx = 0; nx < 50; nx++) {
    for (i = 0; i < loop_ub; i++) {
      harmonic_frequencies_data[i] = audio_data[i] + harmonic_amplitudes[i +
        harmonic_amplitudes.size(0) * nx] * harmonic_frequencies[i +
        harmonic_frequencies.size(0) * nx];
    }

    if (0 <= loop_ub - 1) {
      std::memcpy(&audio_data[0], &harmonic_frequencies_data[0], loop_ub *
                  sizeof(double));
    }
  }
}

// End of code generation (additive.cpp)
