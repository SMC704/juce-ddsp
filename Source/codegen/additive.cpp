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
#include <cmath>
#include <cstring>

// Function Declarations
static void get_harmonic_frequencies(const double f0_data[], const int f0_size[1],
	double stretch, coder::array<double, 2U> &harmonic_frequencies);
static void remove_above_nyquist(const coder::array<double, 2U>
	&harmonic_frequencies, double harmonic_distribution[50], double sample_rate);
static void scale_fn(const double x[50], double y[50]);

// Function Definitions
static void get_harmonic_frequencies(const double f0_data[], const int f0_size[1],
	double stretch, coder::array<double, 2U> &harmonic_frequencies)
{
	int i;
	double f_ratios[50];
	int loop_ub;

	//  Calculate sample-wise oscillator frequencies of harmonics
	for (i = 0; i < 50; i++) {
		f_ratios[i] = static_cast<double>(i) + 1.0;
	}

	//  Incorporate stretch parameter and shift back to f0
	if (stretch > 0.0) {
		for (i = 0; i < 50; i++) {
			f_ratios[i] = ((static_cast<double>(i) + 1.0) + (static_cast<double>(i) +
				1.0) * stretch) - stretch;
		}
	}
	else {
		if (stretch < 0.0) {
			double b_stretch;
			b_stretch = stretch * 0.5;
			for (i = 0; i < 50; i++) {
				f_ratios[i] = ((static_cast<double>(i) + 1.0) + (static_cast<double>(i)
					+ 1.0) * stretch * 0.5) - b_stretch;
			}
		}
	}

	harmonic_frequencies.set_size(f0_size[0], 50);
	loop_ub = f0_size[0];
	for (i = 0; i < 50; i++) {
		for (int i1 = 0; i1 < loop_ub; i1++) {
			harmonic_frequencies[i1 + harmonic_frequencies.size(0) * i] = f0_data[i1] *
				f_ratios[i];
		}
	}
}

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

static void scale_fn(const double x[50], double y[50])
{
	//  Scale Function
	//  Exponentiated Sigmoid pointwise nonlinearity
	for (int k = 0; k < 50; k++) {
		y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
			+ 1.0E-7;
	}
}

void additive(int n_samples, double sample_rate, const double amplitudes[4096],
	double harmonic_distribution[50], const double f0[4096], const
	double prev_phases[50], double shift, double stretch, double
	audio_data[], int audio_size[1], double last_phases[50])
{
	int loop_ub;
	int nx;
	int f0_size[1];
	double f0_data[4096];
	int i;
	int k;
	double x_data[4096];
	double amplitudes_data[4096];
	double b_harmonic_distribution[50];
	coder::array<double, 2U> harmonic_frequencies;
	coder::array<double, 2U> harmonic_amplitudes;
	int c;
	short subsb_idx_1;
	coder::array<double, 2U> x;
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
	//  shift: Shift fundamental frequency, range -12 (one octave down) to 12 (one octave up), 0: no effect 
	//  stretch: Stretch/squeeze harmonic frequencies, range -1 (max squeezed) to 1 (max stretched), 0: no effect 
	//
	//  RETURNS:
	//
	//  Sample-wise audio signal
	//  Resize the input
	if (1 > n_samples) {
		loop_ub = 0;
		nx = 0;
	}
	else {
		loop_ub = n_samples;
		nx = n_samples;
	}

	f0_size[0] = nx;
	if (0 <= nx - 1) {
		std::memcpy(&f0_data[0], &f0[0], nx * sizeof(double));
	}

	//  Incorporate shift parameter
	if (shift > 0.0) {
		f0_size[0] = nx;
		for (i = 0; i < nx; i++) {
			f0_data[i] = f0[i] + f0[i] / 12.0 * shift;
		}
	}
	else {
		if (shift < 0.0) {
			f0_size[0] = nx;
			for (i = 0; i < nx; i++) {
				f0_data[i] = f0[i] + f0[i] / 12.0 * shift * 0.5;
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

	std::memcpy(&b_harmonic_distribution[0], &harmonic_distribution[0], 50U *
		sizeof(double));
	scale_fn(b_harmonic_distribution, harmonic_distribution);

	//  Bandlimit the harmonic distribution
	get_harmonic_frequencies(f0_data, f0_size, stretch, harmonic_frequencies);
	remove_above_nyquist(harmonic_frequencies, harmonic_distribution, sample_rate);

	//  Normalize the harmonic distribution
	//      harm_sum = sum(harmonic_distribution,2);
	//      for c = 1:size(harmonic_distribution,2)
	//          harmonic_distribution(1:end,c) = harmonic_distribution(1:end,c) ./ harm_sum; 
	//      end
	//  Create harmonic amplitudes
	harmonic_amplitudes.set_size(loop_ub, 50);
	nx = loop_ub * 50;
	for (i = 0; i < nx; i++) {
		harmonic_amplitudes[i] = 0.0;
	}

	for (c = 0; c < 50; c++) {
		for (i = 0; i < loop_ub; i++) {
			harmonic_amplitudes[i + harmonic_amplitudes.size(0) * c] =
				harmonic_distribution[c] * amplitudes_data[i];
		}
	}

	// radiant/second
	nx = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
	harmonic_frequencies.set_size(harmonic_frequencies.size(0), 50);
	for (i = 0; i < nx; i++) {
		harmonic_frequencies[i] = harmonic_frequencies[i] * 2.0 * 3.1415926535897931
			/ sample_rate;
	}

	// radiant/sample
	//  Accumulate phase and synthesize
	if (harmonic_frequencies.size(0) != 1) {
		nx = 1;
	}
	else {
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
					int i1;
					c = static_cast<short>(static_cast<short>(nx + 1) + 1) - 1;
					i1 = subsb_idx_1 - 1;
					harmonic_frequencies[c + harmonic_frequencies.size(0) * i1] =
						harmonic_frequencies[nx + harmonic_frequencies.size(0) * k] +
						harmonic_frequencies[c + harmonic_frequencies.size(0) * i1];
				}
			}
		}
	}
	else {
		if (harmonic_frequencies.size(0) != 0) {
			for (k = 0; k < 49; k++) {
				i = harmonic_frequencies.size(0);
				for (nx = 0; nx < i; nx++) {
					int i1;
					c = static_cast<short>(nx + 1) - 1;
					i1 = k + 1;
					harmonic_frequencies[c + harmonic_frequencies.size(0) * i1] =
						harmonic_frequencies[nx + harmonic_frequencies.size(0) * k] +
						harmonic_frequencies[c + harmonic_frequencies.size(0) * i1];
				}
			}
		}
	}

	//  Save last phases of all harmonics for next buffer;
	for (c = 0; c < 50; c++) {
		if (1 > harmonic_frequencies.size(0)) {
			nx = 0;
		}
		else {
			nx = harmonic_frequencies.size(0);
		}

		for (i = 0; i < nx; i++) {
			f0_data[i] = harmonic_frequencies[i + harmonic_frequencies.size(0) * c] +
				prev_phases[c];
		}

		for (i = 0; i < nx; i++) {
			harmonic_frequencies[i + harmonic_frequencies.size(0) * c] = f0_data[i];
		}
	}

	x.set_size(harmonic_frequencies.size(0), 50);
	nx = harmonic_frequencies.size(0) * harmonic_frequencies.size(1);
	for (i = 0; i < nx; i++) {
		x[i] = harmonic_frequencies[i];
	}

	subsb_idx_1 = static_cast<short>(harmonic_frequencies.size(0));
	harmonic_frequencies.set_size((static_cast<int>(static_cast<short>
		(harmonic_frequencies.size(0)))), 50);
	nx = subsb_idx_1 * 50;
	for (k = 0; k < nx; k++) {
		if (rtIsNaN(x[k]) || rtIsInf(x[k])) {
			r = rtNaN;
		}
		else if (x[k] == 0.0) {
			r = 0.0;
		}
		else {
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
			}
			else {
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
	}
	else {
		loop_ub = audio_size[0];
	}

	for (c = 0; c < 50; c++) {
		for (i = 0; i < loop_ub; i++) {
			f0_data[i] = audio_data[i] + harmonic_amplitudes[i +
				harmonic_amplitudes.size(0) * c] * harmonic_frequencies[i +
				harmonic_frequencies.size(0) * c];
		}

		if (0 <= loop_ub - 1) {
			std::memcpy(&audio_data[0], &f0_data[0], loop_ub * sizeof(double));
		}
	}
}

// End of code generation (additive.cpp)
