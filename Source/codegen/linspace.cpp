//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  linspace.cpp
//
//  Code generation for function 'linspace'
//


// Include files
#include "linspace.h"
#include "additive.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void linspace(double d2, double n1, coder::array<double, 2U> &y)
{
  int i;
  if (n1 < 0.0) {
    n1 = 0.0;
  }

  i = static_cast<int>(std::floor(n1));
  y.set_size(1, i);
  if (i >= 1) {
    int y_tmp;
    y_tmp = i - 1;
    y[y_tmp] = d2;
    if (y.size(1) >= 2) {
      y[0] = 1.0;
      if (y.size(1) >= 3) {
        if ((1.0 == -d2) && (i > 2)) {
          for (int k = 2; k <= y_tmp; k++) {
            y[k - 1] = d2 * (static_cast<double>(((k << 1) - i) - 1) / (
              static_cast<double>(i) - 1.0));
          }

          if ((i & 1) == 1) {
            y[i >> 1] = 0.0;
          }
        } else if ((d2 < 0.0) && (std::abs(d2) > 8.9884656743115785E+307)) {
          double delta1;
          double delta2;
          delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
          delta2 = d2 / (static_cast<double>(y.size(1)) - 1.0);
          i = y.size(1);
          for (int k = 0; k <= i - 3; k++) {
            y[k + 1] = (delta2 * (static_cast<double>(k) + 1.0) + 1.0) - delta1 *
              (static_cast<double>(k) + 1.0);
          }
        } else {
          double delta1;
          delta1 = (d2 - 1.0) / (static_cast<double>(y.size(1)) - 1.0);
          i = y.size(1);
          for (int k = 0; k <= i - 3; k++) {
            y[k + 1] = (static_cast<double>(k) + 1.0) * delta1 + 1.0;
          }
        }
      }
    }
  }
}

// End of code generation (linspace.cpp)
