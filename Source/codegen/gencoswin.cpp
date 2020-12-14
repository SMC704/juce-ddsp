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
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
namespace coder
{
  void calc_window(double m, double n, ::coder::array<double, 1U> &w)
  {
    array<double, 2U> y;
    int k;
    int nx;
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

    w.set_size(y.size(1));
    nx = y.size(1);
    for (k = 0; k < nx; k++) {
      w[k] = 6.2831853071795862 * (y[k] / (n - 1.0));
    }

    nx = w.size(0);
    for (k = 0; k < nx; k++) {
      w[k] = std::cos(w[k]);
    }

    nx = w.size(0);
    for (k = 0; k < nx; k++) {
      w[k] = 0.5 - 0.5 * w[k];
    }
  }

  void calc_window(double m, double n, double w_data[], int w_size[1])
  {
    array<double, 2U> y;
    array<double, 1U> b_y;
    int i;
    int loop_ub;
    int nx;
    if (rtIsNaN(m - 1.0)) {
      nx = 1;
      y.set_size(1, 1);
      y[0] = rtNaN;
    } else if (m - 1.0 < 0.0) {
      nx = 0;
      y.set_size(1, 0);
    } else {
      if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
        nx = 1;
      } else {
        nx = static_cast<int>(std::floor(m - 1.0)) + 1;
      }

      if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
        y.set_size(1, 1);
        y[0] = rtNaN;
      } else {
        y.set_size(1, (static_cast<int>(std::floor(m - 1.0)) + 1));
        loop_ub = static_cast<int>(std::floor(m - 1.0));
        for (i = 0; i <= loop_ub; i++) {
          y[i] = i;
        }
      }
    }

    b_y.set_size(y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
      b_y[i] = y[i];
    }

    b_y.set_size(nx);
    for (i = 0; i < nx; i++) {
      b_y[i] = 6.2831853071795862 * (b_y[i] / (n - 1.0));
    }

    nx = b_y.size(0);
    for (loop_ub = 0; loop_ub < nx; loop_ub++) {
      b_y[loop_ub] = std::cos(b_y[loop_ub]);
    }

    w_size[0] = b_y.size(0);
    loop_ub = b_y.size(0);
    for (i = 0; i < loop_ub; i++) {
      w_data[i] = 0.54 - 0.46 * b_y[i];
    }
  }
}

// End of code generation (gencoswin.cpp)
