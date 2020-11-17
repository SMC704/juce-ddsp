//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  gencoswin.cpp
//
//  Code generation for function 'gencoswin'
//


// Include files
#include "gencoswin.h"
#include "FFTImplementationCallback.h"
#include "additive.h"
#include "ifft.h"
#include "irfft.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void calc_window(double m, double n, double w_data[], int w_size[1])
{
  coder::array<double, 2U> y;
  int nx;
  coder::array<double, 1U> r;
  int k;
  if (rtIsNaN(m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y.set_size(1, 0);
  } else if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else {
    nx = static_cast<int>(std::floor(m - 1.0));
    y.set_size(1, (nx + 1));
    for (k = 0; k <= nx; k++) {
      y[k] = k;
    }
  }

  r.set_size(y.size(1));
  nx = y.size(1);
  for (k = 0; k < nx; k++) {
    r[k] = y[k];
  }

  w_size[0] = r.size(0);
  nx = r.size(0);
  for (k = 0; k < nx; k++) {
    w_data[k] = 6.2831853071795862 * (r[k] / (n - 1.0));
  }

  nx = w_size[0];
  for (k = 0; k < nx; k++) {
    w_data[k] = std::cos(w_data[k]);
  }

  nx = w_size[0];
  for (k = 0; k < nx; k++) {
    w_data[k] = 0.5 - 0.5 * w_data[k];
  }
}

// End of code generation (gencoswin.cpp)
