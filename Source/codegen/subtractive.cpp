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
#include "DDSPSynth_data.h"
#include "DDSPSynth_initialize.h"
#include "DDSPSynth_rtwutil.h"
#include "additive.h"
#include "hann.h"
#include "ifft.h"
#include "irfft.h"
#include "rand.h"
#include "rfft.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Declarations
static void c_scale_fn(const double x[1024], double y[1024]);

// Function Definitions
static void c_scale_fn(const double x[1024], double y[1024])
{
  for (int k = 0; k < 1024; k++) {
    y[k] = 2.0 * rt_powd_snf(1.0 / (std::exp(-x[k]) + 1.0), 2.3025850929940459)
      + 1.0E-7;
  }
}

void subtractive(double n_samples, double window_size, const double magnitudes
                 [1024], coder::array<double, 2U> &out)
{
  int i1;
  double b_magnitudes[1024];
  coder::array<double, 2U> a;
  double x_data[2047];
  int x_size[1];
  int window_size_idx_0;
  int vspread;
  static double window_data[5116];
  double half_idx;
  int vlend2;
  int midoffset;
  int i2;
  double dv[1024];
  double impulse_response[2046];
  int ia;
  static double b_window_data[5116];
  int ib;
  double xtmp;
  int k;
  double impulse_response_data[3070];
  int eint;
  coder::array<double, 2U> b_a;
  coder::array<creal_T, 2U> audio_fft;
  coder::array<double, 2U> b_impulse_response_data;
  coder::array<creal_T, 2U> ir_fft;
  coder::array<creal_T, 2U> b_audio_fft;
  coder::array<creal_T, 2U> r;
  if (!isInitialized_DDSPSynth) {
    DDSPSynth_initialize();
  }

  //  magnitudes: row = frames, column = freq responses
  //  normalize magnitudes
  //  optional; colab examplees do not use it
  for (i1 = 0; i1 < 1024; i1++) {
    b_magnitudes[i1] = magnitudes[i1] + -5.0;
  }

  //  generate white noise
  b_rand(n_samples, a);

  //  get IR from provided FR
  if ((window_size <= 0.0) || (window_size > 2046.0)) {
    window_size = 2046.0;
  }

  hann(window_size, x_data, x_size);
  window_size_idx_0 = x_size[0];
  vspread = x_size[0];
  if (0 <= vspread - 1) {
    std::memcpy(&window_data[0], &x_data[0], vspread * sizeof(double));
  }

  half_idx = 0.0;
  if (2046.0 - window_size > 0.0) {
    half_idx = std::floor((window_size + 1.0) / 2.0);
    if (half_idx + 1.0 > x_size[0]) {
      i1 = -1;
      midoffset = 0;
    } else {
      i1 = static_cast<int>(half_idx + 1.0) - 2;
      midoffset = x_size[0];
    }

    if (1.0 > half_idx) {
      vspread = -1;
    } else {
      vspread = static_cast<int>(half_idx) - 1;
    }

    i2 = midoffset - i1;
    vlend2 = static_cast<int>(2046.0 - window_size);
    window_size_idx_0 = (i2 + vlend2) + vspread;
    for (ia = 0; ia <= i2 - 2; ia++) {
      b_window_data[ia] = window_data[(i1 + ia) + 1];
    }

    if (0 <= vlend2 - 1) {
      std::memset(&b_window_data[(midoffset - i1) + -1], 0, ((((vlend2 +
        midoffset) - i1) - midoffset) + i1) * sizeof(double));
    }

    for (ia = 0; ia <= vspread; ia++) {
      b_window_data[(((ia + midoffset) - i1) + vlend2) - 1] = window_data[ia];
    }

    if (0 <= window_size_idx_0 - 1) {
      std::memcpy(&window_data[0], &b_window_data[0], window_size_idx_0 * sizeof
                  (double));
    }
  } else {
    if (0 <= window_size_idx_0 - 1) {
      std::memcpy(&x_data[0], &window_data[0], window_size_idx_0 * sizeof(double));
    }

    if (window_size_idx_0 > 1) {
      vlend2 = window_size_idx_0 / 2;
      vspread = window_size_idx_0 - 1;
      midoffset = vlend2 - 1;
      if (vlend2 << 1 == window_size_idx_0) {
        i2 = 0;
        for (int i = 0; i < 1; i++) {
          i1 = i2;
          i2 += vspread;
          for (int j = 0; j < 1; j++) {
            i1++;
            i2++;
            ia = i1 - 1;
            ib = i1 + midoffset;
            for (k = 0; k < vlend2; k++) {
              xtmp = x_data[ia];
              x_data[ia] = x_data[ib];
              x_data[ib] = xtmp;
              ia++;
              ib++;
            }
          }
        }
      } else {
        i2 = 0;
        for (int i = 0; i < 1; i++) {
          i1 = i2;
          i2 += vspread;
          for (int j = 0; j < 1; j++) {
            i1++;
            i2++;
            ia = i1 - 1;
            ib = i1 + midoffset;
            xtmp = x_data[ib];
            for (k = 0; k < vlend2; k++) {
              int ic;
              ic = ib + 1;
              x_data[ib] = x_data[ia];
              x_data[ia] = x_data[ic];
              ia++;
              ib = ic;
            }

            x_data[ib] = xtmp;
          }
        }
      }
    }

    vspread = x_size[0];
    if (0 <= vspread - 1) {
      std::memcpy(&window_data[0], &x_data[0], vspread * sizeof(double));
    }
  }

  //      window = repmat(window', n_ir_frames, 1);
  //  apply hann window to IR
  c_scale_fn(b_magnitudes, dv);
  irfft(dv, impulse_response);
  if (0 <= window_size_idx_0 - 1) {
    std::memcpy(&b_window_data[0], &window_data[0], window_size_idx_0 * sizeof
                (double));
  }

  for (i1 = 0; i1 < 2046; i1++) {
    impulse_response[i1] *= b_window_data[i1];
  }

  if (2046.0 - window_size > 0.0) {
    if (((2046.0 - (half_idx - 1.0)) + 1.0) + 1.0 > 2046.0) {
      i1 = 0;
      midoffset = 0;
    } else {
      i1 = 2048 - static_cast<int>(half_idx);
      midoffset = 2046;
    }

    vspread = midoffset - i1;
    i2 = static_cast<int>(half_idx);
    vlend2 = (vspread + i2) + 1;
    for (ia = 0; ia < vspread; ia++) {
      impulse_response_data[ia] = impulse_response[i1 + ia];
    }

    for (ia = 0; ia <= i2; ia++) {
      impulse_response_data[(ia + midoffset) - i1] = impulse_response[ia];
    }
  } else {
    ia = 0;
    ib = 1023;
    for (k = 0; k < 1023; k++) {
      xtmp = impulse_response[ia];
      impulse_response[ia] = impulse_response[ib];
      impulse_response[ib] = xtmp;
      ia++;
      ib++;
    }

    vlend2 = 2046;
    std::memcpy(&impulse_response_data[0], &impulse_response[0], 2046U * sizeof
                (double));
  }

  //      frame_size = ceil(n_samples / n_ir_frames);
  //      hop_size = frame_size;
  //      % divide audio into number of frames (= number of rows from 'magnitudes' 
  //      % Dont user buffer. MATLAB coder doesn't like it -
  //  %    audio_frames = buffer(signal, frame_size)';
  //      desired_length = n_ir_frames * frame_size;
  //      padding_needed = desired_length - numel(signal);
  //      signal_padded = [signal zeros(1, padding_needed)];
  //      audio_frames = zeros(n_ir_frames, frame_size);
  //      start_pos = 1;
  //      end_pos = frame_size;
  //      for n = 1:1:n_ir_frames
  //          audio_frames(n,:) = signal_padded(start_pos:end_pos);
  //          start_pos = start_pos + hop_size;
  //          end_pos = end_pos + hop_size;
  //      end
  if ((n_samples + 2046.0) - 1.0 == 0.0) {
    xtmp = rtMinusInf;
  } else if ((n_samples + 2046.0) - 1.0 < 0.0) {
    xtmp = rtNaN;
  } else if ((!rtIsInf((n_samples + 2046.0) - 1.0)) && (!rtIsNaN((n_samples +
                2046.0) - 1.0))) {
    xtmp = frexp((n_samples + 2046.0) - 1.0, &eint);
    if (xtmp == 0.5) {
      xtmp = static_cast<double>(eint) - 1.0;
    } else if ((eint == 1) && (xtmp < 0.75)) {
      xtmp = std::log(2.0 * xtmp) / 0.69314718055994529;
    } else {
      xtmp = std::log(xtmp) / 0.69314718055994529 + static_cast<double>(eint);
    }
  } else {
    xtmp = (n_samples + 2046.0) - 1.0;
  }

  xtmp = rt_powd_snf(2.0, std::ceil(xtmp));

  //  convolve audio with windowed IR <=> multiply in frequency domain
  b_a.set_size(1, a.size(1));
  vspread = a.size(0) * a.size(1);
  for (i1 = 0; i1 < vspread; i1++) {
    b_a[i1] = a[i1] * 2.0 - 1.0;
  }

  rfft(b_a, xtmp, audio_fft);
  b_impulse_response_data.set((&impulse_response_data[0]), 1, vlend2);
  rfft(b_impulse_response_data, xtmp, ir_fft);

  //  apply "overlap and add" to the resulting frames to get back to samples
  //      audio_frames_out = irfft(audio_ir_fft, fft_size, 2);
  b_audio_fft.set_size(1, audio_fft.size(1));
  vspread = audio_fft.size(0) * audio_fft.size(1);
  for (i1 = 0; i1 < vspread; i1++) {
    b_audio_fft[i1].re = audio_fft[i1].re * ir_fft[i1].re - audio_fft[i1].im *
      ir_fft[i1].im;
    b_audio_fft[i1].im = audio_fft[i1].re * ir_fft[i1].im + audio_fft[i1].im *
      ir_fft[i1].re;
  }

  b_irfft(b_audio_fft, n_samples, r);
  out.set_size(r.size(0), r.size(1));
  vspread = r.size(0) * r.size(1);
  for (i1 = 0; i1 < vspread; i1++) {
    out[i1] = r[i1].re;
  }

  //      out_size = n_ir_frames * frame_size + max(fft_size - hop_size, 0);
  //      out_size = 1024;
  //      out = zeros(1, out_size);
  //      for i=0:n_ir_frames-1
  //          out(i*hop_size + 1:i * hop_size + fft_size) = real(out(i*hop_size + 1:i * hop_size + fft_size) + audio_frames_out(i+1, :)); 
  //      end
}

// End of code generation (subtractive.cpp)
