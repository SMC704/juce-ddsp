//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  hamming.cpp
//
//  Code generation for function 'hamming'
//


// Include files
#include "hamming.h"
#include "DDSPSynth_rtwutil.h"
#include "additive.h"
#include "gencoswin.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void b_hamming(double varargin_1, double w_data[], int w_size[1])
{
  int w_size_idx_0;
  signed char b_w_data[1];
  int trivialwin;
  double L;
  coder::array<double, 1U> r;
  w_size_idx_0 = 1;
  b_w_data[0] = 0;
  trivialwin = 0;
  if (varargin_1 == std::floor(varargin_1)) {
    L = varargin_1;
  } else {
    L = rt_roundd_snf(varargin_1);
  }

  if (L == 0.0) {
    w_size_idx_0 = 0;
    trivialwin = 1;
  } else {
    if (L == 1.0) {
      b_w_data[0] = 1;
      trivialwin = 1;
    }
  }

  w_size[0] = w_size_idx_0;
  if (0 <= w_size_idx_0 - 1) {
    w_data[0] = b_w_data[0];
  }

  if (trivialwin == 0) {
    sym_window(L, r);
    w_size[0] = r.size(0);
    w_size_idx_0 = r.size(0);
    for (trivialwin = 0; trivialwin < w_size_idx_0; trivialwin++) {
      w_data[trivialwin] = r[trivialwin];
    }
  }
}

void hamming(int varargin_1, coder::array<double, 1U> &w)
{
  int w_size_idx_0;
  signed char w_data[1];
  int trivialwin;
  w_size_idx_0 = 1;
  w_data[0] = 0;
  trivialwin = 0;
  if (varargin_1 == 0) {
    w_size_idx_0 = 0;
    trivialwin = 1;
  } else {
    if (varargin_1 == 1) {
      w_data[0] = 1;
      trivialwin = 1;
    }
  }

  w.set_size(w_size_idx_0);
  for (int i = 0; i < w_size_idx_0; i++) {
    w[0] = w_data[0];
  }

  if (trivialwin == 0) {
    sym_window(static_cast<double>(varargin_1), w);
  }
}

// End of code generation (hamming.cpp)
