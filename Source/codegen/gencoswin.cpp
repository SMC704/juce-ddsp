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
#include "additive.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void calc_window(double m, double n, double w_data[], int w_size[1])
{
  int y_size_idx_1;
  double y_data[2048];
  int loop_ub;
  int i;
  if (rtIsNaN(m - 1.0)) {
    y_size_idx_1 = 1;
    y_data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y_size_idx_1 = 0;
  } else if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
    y_size_idx_1 = 1;
    y_data[0] = rtNaN;
  } else {
    loop_ub = static_cast<int>(std::floor(m - 1.0));
    y_size_idx_1 = loop_ub + 1;
    for (i = 0; i <= loop_ub; i++) {
      y_data[i] = i;
    }
  }

  w_size[0] = y_size_idx_1;
  for (i = 0; i < y_size_idx_1; i++) {
    w_data[i] = 6.2831853071795862 * (y_data[i] / (n - 1.0));
  }

  for (loop_ub = 0; loop_ub < y_size_idx_1; loop_ub++) {
    w_data[loop_ub] = std::cos(w_data[loop_ub]);
  }

  for (i = 0; i < y_size_idx_1; i++) {
    w_data[i] = 0.54 - 0.46 * w_data[i];
  }
}

// End of code generation (gencoswin.cpp)
