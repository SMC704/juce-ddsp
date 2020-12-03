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
#include "DDSPSynth_rtwutil.h"
#include "SystemCore.h"
#include "additive.h"
#include "firls.h"
#include "rescale.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void b_scale_fn(const double x[65], double y[65]);

// Function Definitions
static void b_scale_fn(const double x[65], double y[65])
{
	for (int k = 0; k < 65; k++) {
		y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
			+ 1.0E-7;
	}
}

void subtractive(double n_samples, double magnitudes[65], double color, const
	double ir_coeffs[129], boolean_T recalculate_ir, double out
	[4096], double b[129])
{
	int i;
	double b_magnitudes[65];
	dsp_ColoredNoise white_n;
	b_dsp_ColoredNoise brown_n;
	c_dsp_ColoredNoise violet_n;
	static double white_noise[4161];
	static double brown_noise[4161];
	static double violet_noise[4161];
	double signal_tmp;
	int loop_ub;
	int tmp_size[2];
	int k;
	int nx_m_nb;
	int filtered_signal_tmp;
	double inputMin;
	double inputMax;
	int filtered_signal_size[1];
	if (!isInitialized_DDSPSynth) {
		DDSPSynth_initialize();
	}

	//  magnitudes: row = frames, column = freq responses
	//  magnitudes should be 65
	//      normalize magnitudes
	//      optional; colab examplees do not use it
	for (i = 0; i < 65; i++) {
		b_magnitudes[i] = magnitudes[i] + -5.0;
	}

	b_scale_fn(b_magnitudes, magnitudes);

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

	if (1.0 > n_samples + 65.0) {
		loop_ub = 0;
	}
	else {
		loop_ub = static_cast<int>(n_samples + 65.0);
	}

	if (recalculate_ir) {
		firls(*(double(*)[64])&magnitudes[0], b, tmp_size);
	}
	else {
		std::memcpy(&b[0], &ir_coeffs[0], 129U * sizeof(double));
	}

	if (0 <= loop_ub - 1) {
		std::memset(&violet_noise[0], 0, loop_ub * sizeof(double));
	}

	if (loop_ub >= 258) {
		for (k = 0; k < 129; k++) {
			nx_m_nb = k + 1;
			for (int j = nx_m_nb; j <= loop_ub; j++) {
				violet_noise[j - 1] += b[k] * white_noise[(j - k) - 1];
			}
		}
	}
	else {
		int j;
		int naxpy;
		if (loop_ub > 129) {
			nx_m_nb = loop_ub - 130;
		}
		else {
			nx_m_nb = -1;
		}

		for (k = 0; k <= nx_m_nb; k++) {
			for (j = 0; j < 129; j++) {
				filtered_signal_tmp = k + j;
				violet_noise[filtered_signal_tmp] += white_noise[k] * b[j];
			}
		}

		naxpy = (loop_ub - nx_m_nb) - 2;
		i = nx_m_nb + 2;
		for (k = i; k <= loop_ub; k++) {
			for (j = 0; j <= naxpy; j++) {
				filtered_signal_tmp = (k + j) - 1;
				violet_noise[filtered_signal_tmp] += white_noise[k - 1] * b[j];
			}

			naxpy--;
		}
	}

	std::memset(&out[0], 0, 4096U * sizeof(double));

	//      out(1:n_samples) = filtered_signal(66:n_samples+65);
	if (66.0 > n_samples + 65.0) {
		i = 0;
		nx_m_nb = 0;
	}
	else {
		i = 65;
		nx_m_nb = static_cast<int>(n_samples + 65.0);
	}

	if (1.0 > n_samples) {
		loop_ub = 0;
	}
	else {
		loop_ub = static_cast<int>(n_samples);
	}

	filtered_signal_tmp = nx_m_nb - i;
	if (filtered_signal_tmp <= 2) {
		if (filtered_signal_tmp == 1) {
			inputMin = violet_noise[i];
			inputMax = violet_noise[i];
		}
		else {
			inputMin = violet_noise[i + 1];
			if ((!(violet_noise[i] > inputMin)) && ((!rtIsNaN(violet_noise[i])) ||
				rtIsNaN(inputMin))) {
				inputMin = violet_noise[i];
			}

			inputMax = violet_noise[i + 1];
			if ((!(violet_noise[i] < inputMax)) && ((!rtIsNaN(violet_noise[i])) ||
				rtIsNaN(violet_noise[i + 1]))) {
				inputMax = violet_noise[i];
			}
		}
	}
	else {
		boolean_T b_b;
		boolean_T exitg1;
		b_b = rtIsNaN(violet_noise[i]);
		if (!b_b) {
			nx_m_nb = 1;
		}
		else {
			nx_m_nb = 0;
			k = 2;
			exitg1 = false;
			while ((!exitg1) && (k <= filtered_signal_tmp)) {
				if (!rtIsNaN(violet_noise[(i + k) - 1])) {
					nx_m_nb = k;
					exitg1 = true;
				}
				else {
					k++;
				}
			}
		}

		if (nx_m_nb == 0) {
			inputMin = violet_noise[i];
		}
		else {
			inputMin = violet_noise[(i + nx_m_nb) - 1];
			nx_m_nb++;
			for (k = nx_m_nb; k <= filtered_signal_tmp; k++) {
				signal_tmp = violet_noise[(i + k) - 1];
				if (inputMin > signal_tmp) {
					inputMin = signal_tmp;
				}
			}
		}

		if (!b_b) {
			nx_m_nb = 1;
		}
		else {
			nx_m_nb = 0;
			k = 2;
			exitg1 = false;
			while ((!exitg1) && (k <= filtered_signal_tmp)) {
				if (!rtIsNaN(violet_noise[(i + k) - 1])) {
					nx_m_nb = k;
					exitg1 = true;
				}
				else {
					k++;
				}
			}
		}

		if (nx_m_nb == 0) {
			inputMax = violet_noise[i];
		}
		else {
			inputMax = violet_noise[(i + nx_m_nb) - 1];
			nx_m_nb++;
			for (k = nx_m_nb; k <= filtered_signal_tmp; k++) {
				signal_tmp = violet_noise[(i + k) - 1];
				if (inputMax < signal_tmp) {
					inputMax = signal_tmp;
				}
			}
		}
	}

	for (nx_m_nb = 0; nx_m_nb < filtered_signal_tmp; nx_m_nb++) {
		brown_noise[nx_m_nb] = violet_noise[i + nx_m_nb];
	}

	filtered_signal_size[0] = filtered_signal_tmp;
	if (0 <= filtered_signal_tmp - 1) {
		std::memcpy(&violet_noise[0], &brown_noise[0], filtered_signal_tmp * sizeof
		(double));
	}

	RESCALE(violet_noise, filtered_signal_size, inputMin, inputMax);
	if (0 <= loop_ub - 1) {
		std::memcpy(&out[0], &violet_noise[0], loop_ub * sizeof(double));
	}
}

// End of code generation (subtractive.cpp)
