//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  psdfreqvec.cpp
//
//  Code generation for function 'psdfreqvec'
//


// Include files
#include "psdfreqvec.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder
{
  void psdfreqvec(double varargin_4, double w_data[], int w_size[1])
  {
    double w1_data[2048];
    double Fs1;
    double freq_res;
    if (rtIsNaN(varargin_4)) {
      Fs1 = 6.2831853071795862;
    } else {
      Fs1 = varargin_4;
    }

    freq_res = Fs1 / 2048.0;
    for (int i = 0; i < 2048; i++) {
      w1_data[i] = freq_res * static_cast<double>(i);
    }

    w1_data[1024] = Fs1 / 2.0;
    w1_data[2047] = Fs1 - freq_res;
    w_size[0] = 2048;
    std::memcpy(&w_data[0], &w1_data[0], 2048U * sizeof(double));
  }
}

// End of code generation (psdfreqvec.cpp)
