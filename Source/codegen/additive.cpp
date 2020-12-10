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
#include "linspace.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
void additive(double n_samples, double sample_rate, const double amplitudes[4096],
              double n_harmonics, double harmonic_distribution[60], const double
              f0[4096], const double prev_phases[60], double shift, double
              stretch, double audio[4096], double last_phases[60])
{
  coder::array<double, 2U> b_harmonic_frequencies;
  coder::array<double, 2U> f_ratios;
  coder::array<double, 2U> harmonic_amplitudes;
  coder::array<double, 2U> harmonic_frequencies;
  coder::array<int, 2U> r1;
  coder::array<boolean_T, 2U> r;
  double amplitudes_data[4096];
  double f0_data[4096];
  double x_data[4096];
  double b_sample_rate;
  double q;
  int b_loop_ub;
  int i;
  int i1;
  int k;
  int loop_ub;
  int nx;
  int subsb_idx_1;
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
  //  shift: Shift fundamental frequency, range -12 (one octave down) to 12 (one octave up), 0: no effect 
  //  stretch: Stretch/squeeze harmonic frequencies, range -1 (max squeezed) to 1 (max stretched), 0: no effect 
  //
  //  RETURNS:
  //
  //  Sample-wise audio signal
  //  Resize the input
  if (1.0 > n_samples) {
    loop_ub = 0;
    b_loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(n_samples);
    b_loop_ub = static_cast<int>(n_samples);
  }

  if (0 <= b_loop_ub - 1) {
    std::memcpy(&f0_data[0], &f0[0], b_loop_ub * sizeof(double));
  }

  //  Incorporate shift parameter
  if (shift > 0.0) {
    for (i = 0; i < b_loop_ub; i++) {
      b_sample_rate = f0[i];
      f0_data[i] = b_sample_rate + b_sample_rate / 12.0 * shift;
    }
  } else {
    if (shift < 0.0) {
      for (i = 0; i < b_loop_ub; i++) {
        b_sample_rate = f0[i];
        f0_data[i] = b_sample_rate + b_sample_rate / 12.0 * shift * 0.5;
      }
    }
  }

  //  Scale the amplitudes
  //  Scale Function
  //  Exponentiated Sigmoid pointwise nonlinearity
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = -amplitudes[i];
  }

  for (k = 0; k < loop_ub; k++) {
    x_data[k] = std::exp(x_data[k]);
  }

  for (i = 0; i < loop_ub; i++) {
    x_data[i] = 1.0 / (x_data[i] + 1.0);
  }

  for (k = 0; k < loop_ub; k++) {
    amplitudes_data[k] = rt_powd_snf(x_data[k], 2.3025850929940459);
  }

  for (i = 0; i < loop_ub; i++) {
    amplitudes_data[i] = 2.0 * amplitudes_data[i] + 1.0E-7;
  }

  //  Scale Function
  //  Exponentiated Sigmoid pointwise nonlinearity
  for (k = 0; k < 60; k++) {
    harmonic_distribution[k] = 2.0 * rt_powd_snf(1.0 / (std::exp
      (-harmonic_distribution[k]) + 1.0), 2.3025850929940459) + 1.0E-7;
  }

  //  Bandlimit the harmonic distribution
  //  Calculate sample-wise oscillator frequencies of harmonics
  coder::linspace(n_harmonics, n_harmonics, f_ratios);

  //  Incorporate stretch parameter and shift back to f0
  if (stretch > 0.0) {
    i = f_ratios.size(0) * f_ratios.size(1);
    f_ratios.set_size(1, f_ratios.size(1));
    nx = i - 1;
    for (i = 0; i <= nx; i++) {
      b_sample_rate = f_ratios[i];
      b_sample_rate = (b_sample_rate + b_sample_rate * stretch) - stretch;
      f_ratios[i] = b_sample_rate;
    }
  } else {
    if (stretch < 0.0) {
      i = f_ratios.size(0) * f_ratios.size(1);
      f_ratios.set_size(1, f_ratios.size(1));
      q = stretch * 0.5;
      nx = i - 1;
      for (i = 0; i <= nx; i++) {
        b_sample_rate = f_ratios[i];
        b_sample_rate = (b_sample_rate + b_sample_rate * stretch * 0.5) - q;
        f_ratios[i] = b_sample_rate;
      }
    }
  }

  harmonic_frequencies.set_size(b_loop_ub, f_ratios.size(1));
  nx = f_ratios.size(1);
  for (i = 0; i < nx; i++) {
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      harmonic_frequencies[i1 + harmonic_frequencies.size(0) * i] = f0_data[i1] *
        f_ratios[i];
    }
  }

  //  Set amplitudes for oscillators above nyquist to 0
  if (1 > harmonic_frequencies.size(1)) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = harmonic_frequencies.size(1);
  }

  b_sample_rate = sample_rate / 2.0;
  r.set_size(1, b_loop_ub);
  for (i = 0; i < b_loop_ub; i++) {
    r[i] = (harmonic_frequencies[harmonic_frequencies.size(0) * i] >=
            b_sample_rate);
  }

  b_loop_ub = r.size(1) - 1;
  nx = 0;
  for (k = 0; k <= b_loop_ub; k++) {
    if (r[k]) {
      nx++;
    }
  }

  r1.set_size(1, nx);
  nx = 0;
  for (k = 0; k <= b_loop_ub; k++) {
    if (r[k]) {
      r1[nx] = k + 1;
      nx++;
    }
  }

  b_loop_ub = r1.size(0) * r1.size(1);
  for (i = 0; i < b_loop_ub; i++) {
    harmonic_distribution[r1[i] - 1] = 0.0;
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
  //  Normalize the harmonic distribution
  for (nx = 0; nx < 60; nx++) {
    b_sample_rate = harmonic_distribution[nx];
    b_sample_rate /= b_sample_rate;
    harmonic_distribution[nx] = b_sample_rate;
  }

  //  Create harmonic amplitudes
  harmonic_amplitudes.set_size(loop_ub, 60);
  b_loop_ub = loop_ub * 60;
  for (i = 0; i < b_loop_ub; i++) {
    harmonic_amplitudes[i] = 0.0;
  }

  for (nx = 0; nx < 60; nx++) {
    for (i = 0; i < loop_ub; i++) {
      harmonic_amplitudes[i + harmonic_amplitudes.size(0) * nx] =
        harmonic_distribution[nx] * amplitudes_data[i];
    }
  }

  // radiant/second
  loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
  for (i = 0; i < loop_ub; i++) {
    harmonic_frequencies[i] = harmonic_frequencies[i] * 2.0 * 3.1415926535897931
      / sample_rate;
  }

  // radiant/sample
  //  Accumulate phase and synthesize
  nx = 2;
  if (harmonic_frequencies.size(0) != 1) {
    nx = 1;
  }

  if (1 == nx) {
    if ((harmonic_frequencies.size(0) != 0) && (harmonic_frequencies.size(1) !=
         0)) {
      i = harmonic_frequencies.size(1);
      for (k = 0; k < i; k++) {
        i1 = harmonic_frequencies.size(0);
        if (0 <= i1 - 2) {
          subsb_idx_1 = k + 1;
        }

        for (nx = 0; nx <= i1 - 2; nx++) {
          harmonic_frequencies[(nx + harmonic_frequencies.size(0) * (subsb_idx_1
            - 1)) + 1] = harmonic_frequencies[nx + harmonic_frequencies.size(0) *
            k] + harmonic_frequencies[(nx + harmonic_frequencies.size(0) *
            (subsb_idx_1 - 1)) + 1];
        }
      }
    }
  } else {
    if ((harmonic_frequencies.size(0) != 0) && (harmonic_frequencies.size(1) !=
         0)) {
      i = harmonic_frequencies.size(1);
      for (k = 0; k <= i - 2; k++) {
        i1 = harmonic_frequencies.size(0);
        for (nx = 0; nx < i1; nx++) {
          harmonic_frequencies[nx + harmonic_frequencies.size(0) * (k + 1)] =
            harmonic_frequencies[nx + harmonic_frequencies.size(0) * k] +
            harmonic_frequencies[nx + harmonic_frequencies.size(0) * (k + 1)];
        }
      }
    }
  }

  //  Save last phases of all harmonics for next buffer;
  i = harmonic_frequencies.size(1);
  for (nx = 0; nx < i; nx++) {
    if (1 > harmonic_frequencies.size(0)) {
      loop_ub = 0;
    } else {
      loop_ub = harmonic_frequencies.size(0);
    }

    for (i1 = 0; i1 < loop_ub; i1++) {
      x_data[i1] = harmonic_frequencies[i1 + harmonic_frequencies.size(0) * nx]
        + prev_phases[nx];
    }

    for (i1 = 0; i1 < loop_ub; i1++) {
      harmonic_frequencies[i1 + harmonic_frequencies.size(0) * nx] = x_data[i1];
    }
  }

  //  For now: check if f0 == 0hz and reset phase
  i = harmonic_frequencies.size(0);
  for (k = 0; k < i; k++) {
    if (f0_data[k] == 0.0) {
      if (1 > harmonic_frequencies.size(1)) {
        loop_ub = 0;
      } else {
        loop_ub = harmonic_frequencies.size(1);
      }

      for (i1 = 0; i1 < loop_ub; i1++) {
        harmonic_frequencies[k + harmonic_frequencies.size(0) * i1] = 0.0;
      }
    }
  }

  b_harmonic_frequencies.set_size(harmonic_frequencies.size(0),
    harmonic_frequencies.size(1));
  loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1) - 1;
  for (i = 0; i <= loop_ub; i++) {
    b_harmonic_frequencies[i] = harmonic_frequencies[i];
  }

  harmonic_frequencies.set_size(b_harmonic_frequencies.size(0),
    b_harmonic_frequencies.size(1));
  nx = b_harmonic_frequencies.size(0) * b_harmonic_frequencies.size(1);
  for (k = 0; k < nx; k++) {
    if (rtIsNaN(b_harmonic_frequencies[k]) || rtIsInf(b_harmonic_frequencies[k]))
    {
      b_sample_rate = rtNaN;
    } else if (b_harmonic_frequencies[k] == 0.0) {
      b_sample_rate = 0.0;
    } else {
      boolean_T rEQ0;
      b_sample_rate = std::fmod(b_harmonic_frequencies[k], 6.2831853071795862);
      rEQ0 = (b_sample_rate == 0.0);
      if (!rEQ0) {
        q = std::abs(b_harmonic_frequencies[k] / 6.2831853071795862);
        rEQ0 = !(std::abs(q - std::floor(q + 0.5)) > 2.2204460492503131E-16 * q);
      }

      if (rEQ0) {
        b_sample_rate = 0.0;
      } else {
        if (b_harmonic_frequencies[k] < 0.0) {
          b_sample_rate += 6.2831853071795862;
        }
      }
    }

    harmonic_frequencies[k] = b_sample_rate;
  }

  std::memset(&last_phases[0], 0, 60U * sizeof(double));
  i = harmonic_frequencies.size(1);
  for (nx = 0; nx < i; nx++) {
    last_phases[nx] = harmonic_frequencies[(harmonic_frequencies.size(0) +
      harmonic_frequencies.size(0) * nx) - 1];
  }

  //  Convert to waveforms
  nx = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
  for (k = 0; k < nx; k++) {
    harmonic_frequencies[k] = std::sin(harmonic_frequencies[k]);
  }

  std::memset(&audio[0], 0, 4096U * sizeof(double));
  i = static_cast<int>(n_harmonics);
  for (nx = 0; nx < i; nx++) {
    for (i1 = 0; i1 < 4096; i1++) {
      audio[i1] += harmonic_amplitudes[i1 + harmonic_amplitudes.size(0) * nx] *
        harmonic_frequencies[i1 + harmonic_frequencies.size(0) * nx];
    }
  }
}

// End of code generation (additive.cpp)
