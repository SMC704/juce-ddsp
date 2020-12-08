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
#include "getPitch2.h"
#include "linspace.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void scale_fn(const double x[60], double y[60]);

// Function Definitions
static void scale_fn(const double x[60], double y[60])
{
	//  Scale Function
	//  Exponentiated Sigmoid pointwise nonlinearity
	for (int k = 0; k < 60; k++) {
		y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
			+ 1.0E-7;
	}
}

void additive(double n_samples, double sample_rate, const double amplitudes[4096],
	double n_harmonics, double harmonic_distribution[60], const double
	f0[4096], const double prev_phases[60], double shift, double
	stretch, double audio_data[], int audio_size[1], double
	last_phases[60])
{
	int loop_ub;
	int b_loop_ub;
	double f0_data[4096];
	int i;
	double b_harmonic_distribution[60];
	coder::array<double, 2U> f_ratios;
	int nx;
	coder::array<double, 2U> harmonic_frequencies;
	double b_stretch;
	double q;
	int i1;
	coder::array<boolean_T, 2U> r;
	int b_i;
	coder::array<int, 2U> r1;
	int subsb_idx_1;
	coder::array<double, 2U> b_harmonic_frequencies;
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
	}
	else {
		loop_ub = static_cast<int>(n_samples);
		b_loop_ub = static_cast<int>(n_samples);
	}

	if (0 <= b_loop_ub - 1) {
		std::memcpy(&f0_data[0], &f0[0], b_loop_ub * sizeof(double));
	}

	//  Incorporate shift parameter
	if (shift > 0.0) {
		for (i = 0; i < b_loop_ub; i++) {
			f0_data[i] = f0[i] + f0[i] / 12.0 * shift;
		}
	}
	else {
		if (shift < 0.0) {
			for (i = 0; i < b_loop_ub; i++) {
				f0_data[i] = f0[i] + f0[i] / 12.0 * shift * 0.5;
			}
		}
	}

	//  Scale the amplitudes
	//      amplitudes = scale_fn(amplitudes);
	std::memcpy(&b_harmonic_distribution[0], &harmonic_distribution[0], 60U *
		sizeof(double));
	scale_fn(b_harmonic_distribution, harmonic_distribution);

	//  Bandlimit the harmonic distribution
	//  Calculate sample-wise oscillator frequencies of harmonics
	linspace(n_harmonics, n_harmonics, f_ratios);

	//  Incorporate stretch parameter and shift back to f0
	if (stretch > 0.0) {
		i = f_ratios.size(0) * f_ratios.size(1);
		f_ratios.set_size(1, f_ratios.size(1));
		nx = i - 1;
		for (i = 0; i <= nx; i++) {
			q = f_ratios[i];
			q = (q + q * stretch) - stretch;
			f_ratios[i] = q;
		}
	}
	else {
		if (stretch < 0.0) {
			i = f_ratios.size(0) * f_ratios.size(1);
			f_ratios.set_size(1, f_ratios.size(1));
			b_stretch = stretch * 0.5;
			nx = i - 1;
			for (i = 0; i <= nx; i++) {
				q = f_ratios[i];
				q = (q + q * stretch * 0.5) - b_stretch;
				f_ratios[i] = q;
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
	}
	else {
		b_loop_ub = harmonic_frequencies.size(1);
	}

	b_stretch = sample_rate / 2.0;
	r.set_size(1, b_loop_ub);
	for (i = 0; i < b_loop_ub; i++) {
		r[i] = (harmonic_frequencies[harmonic_frequencies.size(0) * i] >= b_stretch);
	}

	b_loop_ub = r.size(1) - 1;
	nx = 0;
	for (b_i = 0; b_i <= b_loop_ub; b_i++) {
		if (r[b_i]) {
			nx++;
		}
	}

	r1.set_size(1, nx);
	nx = 0;
	for (b_i = 0; b_i <= b_loop_ub; b_i++) {
		if (r[b_i]) {
			r1[nx] = b_i + 1;
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
	//      harm_sum = sum(harmonic_distribution,2);
	//      for c = 1:size(harmonic_distribution,2)
	//          harmonic_distribution(1:end,c) = harmonic_distribution(1:end,c) ./ harm_sum; 
	//      end
	//  Create harmonic amplitudes
	f_ratios.set_size(loop_ub, 60);
	b_loop_ub = loop_ub * 60;
	for (i = 0; i < b_loop_ub; i++) {
		f_ratios[i] = 0.0;
	}

	for (nx = 0; nx < 60; nx++) {
		for (i = 0; i < loop_ub; i++) {
			f_ratios[i + f_ratios.size(0) * nx] = harmonic_distribution[nx] *
				amplitudes[i];
		}
	}

	// radiant/second
	b_loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
	for (i = 0; i < b_loop_ub; i++) {
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
			for (b_i = 0; b_i < i; b_i++) {
				i1 = harmonic_frequencies.size(0);
				if (0 <= i1 - 2) {
					subsb_idx_1 = b_i + 1;
				}

				for (nx = 0; nx <= i1 - 2; nx++) {
					harmonic_frequencies[(nx + harmonic_frequencies.size(0) * (subsb_idx_1
						- 1)) + 1] = harmonic_frequencies[nx + harmonic_frequencies.size(0) *
						b_i] + harmonic_frequencies[(nx + harmonic_frequencies.size(0) *
						(subsb_idx_1 - 1)) + 1];
				}
			}
		}
	}
	else {
		if ((harmonic_frequencies.size(0) != 0) && (harmonic_frequencies.size(1) !=
			0)) {
			i = harmonic_frequencies.size(1);
			for (b_i = 0; b_i <= i - 2; b_i++) {
				i1 = harmonic_frequencies.size(0);
				for (nx = 0; nx < i1; nx++) {
					harmonic_frequencies[nx + harmonic_frequencies.size(0) * (b_i + 1)] =
						harmonic_frequencies[nx + harmonic_frequencies.size(0) * b_i] +
						harmonic_frequencies[nx + harmonic_frequencies.size(0) * (b_i + 1)];
				}
			}
		}
	}

	//  Save last phases of all harmonics for next buffer;
	i = harmonic_frequencies.size(1);
	for (nx = 0; nx < i; nx++) {
		if (1 > harmonic_frequencies.size(0)) {
			b_loop_ub = 0;
		}
		else {
			b_loop_ub = harmonic_frequencies.size(0);
		}

		for (i1 = 0; i1 < b_loop_ub; i1++) {
			f0_data[i1] = harmonic_frequencies[i1 + harmonic_frequencies.size(0) * nx]
				+ prev_phases[nx];
		}

		for (i1 = 0; i1 < b_loop_ub; i1++) {
			harmonic_frequencies[i1 + harmonic_frequencies.size(0) * nx] = f0_data[i1];
		}
	}

	b_harmonic_frequencies.set_size(harmonic_frequencies.size(0),
		harmonic_frequencies.size(1));
	b_loop_ub = harmonic_frequencies.size(0) * harmonic_frequencies.size(1) - 1;
	for (i = 0; i <= b_loop_ub; i++) {
		b_harmonic_frequencies[i] = harmonic_frequencies[i];
	}

	unsigned int unnamed_idx_0;
	unsigned int unnamed_idx_1;
	unnamed_idx_0 = static_cast<unsigned int>(b_harmonic_frequencies.size(0));
	unnamed_idx_1 = static_cast<unsigned int>(b_harmonic_frequencies.size(1));
	harmonic_frequencies.set_size((static_cast<int>(unnamed_idx_0)), (static_cast<
		int>(unnamed_idx_1)));
	nx = static_cast<int>(unnamed_idx_0) * static_cast<int>(unnamed_idx_1);
	for (b_i = 0; b_i < nx; b_i++) {
		if (rtIsNaN(b_harmonic_frequencies[b_i]) || rtIsInf
		(b_harmonic_frequencies[b_i])) {
			b_stretch = rtNaN;
		}
		else if (b_harmonic_frequencies[b_i] == 0.0) {
			b_stretch = 0.0;
		}
		else {
			boolean_T rEQ0;
			b_stretch = std::fmod(b_harmonic_frequencies[b_i], 6.2831853071795862);
			rEQ0 = (b_stretch == 0.0);
			if (!rEQ0) {
				q = std::abs(b_harmonic_frequencies[b_i] / 6.2831853071795862);
				rEQ0 = !(std::abs(q - std::floor(q + 0.5)) > 2.2204460492503131E-16 * q);
			}

			if (rEQ0) {
				b_stretch = 0.0;
			}
			else {
				if (b_harmonic_frequencies[b_i] < 0.0) {
					b_stretch += 6.2831853071795862;
				}
			}
		}

		harmonic_frequencies[b_i] = b_stretch;
	}

	std::memset(&last_phases[0], 0, 60U * sizeof(double));
	i = harmonic_frequencies.size(1);
	for (nx = 0; nx < i; nx++) {
		last_phases[nx] = harmonic_frequencies[(harmonic_frequencies.size(0) +
			harmonic_frequencies.size(0) * nx) - 1];
	}

	//  Convert to waveforms
	nx = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
	for (b_i = 0; b_i < nx; b_i++) {
		harmonic_frequencies[b_i] = std::sin(harmonic_frequencies[b_i]);
	}

	audio_size[0] = static_cast<short>(loop_ub);
	loop_ub = static_cast<short>(loop_ub);
	if (0 <= loop_ub - 1) {
		std::memset(&audio_data[0], 0, loop_ub * sizeof(double));
	}

	if (1 > audio_size[0]) {
		loop_ub = 0;
	}
	else {
		loop_ub = audio_size[0];
	}

	for (nx = 0; nx < 60; nx++) {
		for (i = 0; i < loop_ub; i++) {
			f0_data[i] = audio_data[i] + f_ratios[i + f_ratios.size(0) * nx] *
				harmonic_frequencies[i + harmonic_frequencies.size(0) * nx];
		}

		if (0 <= loop_ub - 1) {
			std::memcpy(&audio_data[0], &f0_data[0], loop_ub * sizeof(double));
		}
	}
}

// End of code generation (additive.cpp)
