//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  stft.cpp
//
//  Code generation for function 'stft'
//


// Include files
#include "stft.h"
#include "computeDFT.h"
#include "iseven.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder
{
  void stft(const double x_data[], const int x_size[1], double varargin_1, const
            ::coder::array<double, 1U> &varargin_3, ::coder::array<creal_T, 2U>
            &varargout_1)
  {
    static const char b[8] = { 'o', 'n', 'e', 's', 'i', 'd', 'e', 'd' };

    static const char b_b[8] = { 'c', 'e', 'n', 't', 'e', 'r', 'e', 'd' };

    static const char c_b[8] = { 't', 'w', 'o', 's', 'i', 'd', 'e', 'd' };

    static const char freqRange[8] = { 'c', 'e', 'n', 't', 'e', 'r', 'e', 'd' };

    array<creal_T, 2U> S;
    array<creal_T, 2U> buffer;
    array<double, 2U> c;
    array<double, 2U> xin;
    double f_data[2048];
    double nCol;
    double opts_NumFreqSamples;
    double tmp_im;
    int f_size[1];
    int b_k;
    int bcoef;
    int hopSize;
    int i;
    int i1;
    int ib;
    int k;
    int ret;
    ret = memcmp(&freqRange[0], &b[0], 8);
    if (ret == 0) {
      if (signalwavelet::internal::iseven(2048.0)) {
        opts_NumFreqSamples = 1025.0;
      } else {
        opts_NumFreqSamples = 1024.5;
      }
    } else {
      opts_NumFreqSamples = 2048.0;
    }

    ret = static_cast<int>(std::floor(static_cast<double>(varargin_3.size(0)) *
      0.75));
    hopSize = varargin_3.size(0) - ret;
    nCol = static_cast<double>(x_size[0] - ret) / static_cast<double>(hopSize);
    if (nCol < 0.0) {
      nCol = std::ceil(nCol);
    } else {
      nCol = std::floor(nCol);
    }

    xin.set_size(varargin_3.size(0), (static_cast<int>(nCol)));
    ib = varargin_3.size(0) * static_cast<int>(nCol);
    for (i = 0; i < ib; i++) {
      xin[i] = 0.0;
    }

    i = static_cast<int>(nCol);
    for (ret = 0; ret < i; ret++) {
      nCol = static_cast<double>(hopSize) * ((static_cast<double>(ret) + 1.0) -
        1.0);
      tmp_im = static_cast<double>(varargin_3.size(0)) + nCol;
      if (nCol + 1.0 > tmp_im) {
        i1 = 0;
        bcoef = 0;
      } else {
        i1 = static_cast<int>(nCol + 1.0) - 1;
        bcoef = static_cast<int>(tmp_im);
      }

      ib = bcoef - i1;
      for (bcoef = 0; bcoef < ib; bcoef++) {
        xin[bcoef + xin.size(0) * ret] = x_data[i1 + bcoef];
      }
    }

    ret = xin.size(0);
    hopSize = varargin_3.size(0);
    if (ret < hopSize) {
      hopSize = ret;
    }

    if (xin.size(0) == 1) {
      hopSize = varargin_3.size(0);
    } else if (varargin_3.size(0) == 1) {
      hopSize = xin.size(0);
    } else {
      if (varargin_3.size(0) == xin.size(0)) {
        hopSize = varargin_3.size(0);
      }
    }

    c.set_size(hopSize, xin.size(1));
    ret = xin.size(0);
    hopSize = varargin_3.size(0);
    if (ret < hopSize) {
      hopSize = ret;
    }

    if (xin.size(0) == 1) {
      hopSize = varargin_3.size(0);
    } else if (varargin_3.size(0) == 1) {
      hopSize = xin.size(0);
    } else {
      if (varargin_3.size(0) == xin.size(0)) {
        hopSize = varargin_3.size(0);
      }
    }

    if ((hopSize != 0) && (xin.size(1) != 0)) {
      ret = (xin.size(1) != 1);
      i = xin.size(1) - 1;
      for (k = 0; k <= i; k++) {
        ib = ret * k;
        hopSize = (varargin_3.size(0) != 1);
        bcoef = (xin.size(0) != 1);
        i1 = c.size(0) - 1;
        for (b_k = 0; b_k <= i1; b_k++) {
          c[b_k + c.size(0) * k] = varargin_3[hopSize * b_k] * xin[bcoef * b_k +
            xin.size(0) * ib];
        }
      }
    }

    computeDFT(c, varargin_1, S, f_data, f_size);
    ret = memcmp(&freqRange[0], &b_b[0], 8);
    if (ret == 0) {
      ret = 0;
    } else {
      ret = memcmp(&freqRange[0], &c_b[0], 8);
      if (ret == 0) {
        ret = 1;
      } else {
        ret = -1;
      }
    }

    switch (ret) {
     case 0:
      if (signalwavelet::internal::iseven(2048.0)) {
        if (S.size(1) != 0) {
          hopSize = S.size(1);
          if (2048 > hopSize) {
            hopSize = 2048;
          }

          ib = static_cast<int>(std::floor(static_cast<double>(hopSize) / 2.0));
          buffer.set_size(1, ib);
          for (i = 0; i < ib; i++) {
            buffer[i].re = 0.0;
            buffer[i].im = 0.0;
          }

          bcoef = S.size(1);
          for (b_k = 0; b_k < bcoef; b_k++) {
            ret = (b_k << 11) - 1;
            for (k = 0; k < 1023; k++) {
              buffer[k] = S[(ret + k) + 1026];
            }

            for (k = 1024; k >= 0; k--) {
              i = ret + k;
              S[i + 1024] = S[i + 1];
            }

            for (k = 0; k < 1023; k++) {
              S[(ret + k) + 1] = buffer[k];
            }
          }
        }
      } else {
        bcoef = S.size(1);
        ret = 1;
        for (b_k = 0; b_k < bcoef; b_k++) {
          hopSize = ret - 1;
          ret += 2048;
          ib = hopSize + 1024;
          for (k = 0; k < 1024; k++) {
            nCol = S[hopSize].re;
            tmp_im = S[hopSize].im;
            S[hopSize] = S[ib];
            S[ib].re = nCol;
            S[ib].im = tmp_im;
            hopSize++;
            ib++;
          }
        }
      }

      varargout_1.set_size(2048, S.size(1));
      ib = S.size(0) * S.size(1);
      for (i = 0; i < ib; i++) {
        varargout_1[i] = S[i];
      }
      break;

     case 1:
      varargout_1.set_size(2048, S.size(1));
      ib = S.size(0) * S.size(1);
      for (i = 0; i < ib; i++) {
        varargout_1[i] = S[i];
      }
      break;

     default:
      if (2048.0 != opts_NumFreqSamples) {
        ib = static_cast<int>(opts_NumFreqSamples);
        ret = S.size(1);
        varargout_1.set_size((static_cast<int>(opts_NumFreqSamples)), S.size(1));
        for (i = 0; i < ret; i++) {
          for (i1 = 0; i1 < ib; i1++) {
            varargout_1[i1 + varargout_1.size(0) * i] = S[i1 + 2048 * i];
          }
        }
      } else {
        varargout_1.set_size(2048, S.size(1));
        ib = S.size(0) * S.size(1);
        for (i = 0; i < ib; i++) {
          varargout_1[i] = S[i];
        }
      }
      break;
    }
  }
}

// End of code generation (stft.cpp)
