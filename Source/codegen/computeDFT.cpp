//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  computeDFT.cpp
//
//  Code generation for function 'computeDFT'
//


// Include files
#include "computeDFT.h"
#include "fft.h"
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
namespace coder
{
  void computeDFT(const ::coder::array<double, 2U> &xin, double varargin_1, ::
                  coder::array<creal_T, 2U> &Xx, double f_data[], int f_size[1])
  {
    array<double, 2U> wrappedData;
    array<double, 2U> xw;
    int b_remainder;
    int i;
    int i1;
    int nFullPasses;
    int offset;
    xw.set_size(2048, xin.size(1));
    offset = xin.size(1) << 11;
    for (i = 0; i < offset; i++) {
      xw[i] = 0.0;
    }

    if (xin.size(0) > 2048) {
      i = xin.size(1);
      if (0 <= xin.size(1) - 1) {
        nFullPasses = xin.size(0) / 2048;
        b_remainder = (xin.size(0) - (nFullPasses << 11)) - 1;
        i1 = b_remainder + 2;
      }

      for (int j = 0; j < i; j++) {
        int k;
        wrappedData.set_size(2048, 1);
        for (offset = 0; offset < 2048; offset++) {
          wrappedData[offset] = 0.0;
        }

        offset = nFullPasses << 11;
        for (k = 0; k <= b_remainder; k++) {
          wrappedData[k] = xin[(offset + k) + xin.size(0) * j];
        }

        for (k = i1; k < 2049; k++) {
          wrappedData[k - 1] = 0.0;
        }

        for (int b_j = 0; b_j < nFullPasses; b_j++) {
          offset = b_j << 11;
          for (k = 0; k < 2048; k++) {
            wrappedData[k] = wrappedData[k] + xin[(offset + k) + xin.size(0) * j];
          }
        }

        for (offset = 0; offset < 2048; offset++) {
          xw[offset + xw.size(0) * j] = wrappedData[offset];
        }
      }
    } else {
      xw.set_size(xin.size(0), xin.size(1));
      offset = xin.size(0) * xin.size(1);
      for (i = 0; i < offset; i++) {
        xw[i] = xin[i];
      }
    }

    fft(xw, Xx);
    psdfreqvec(varargin_1, f_data, f_size);
  }
}

// End of code generation (computeDFT.cpp)
