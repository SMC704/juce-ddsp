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
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
namespace coder
{
  void linspace(double d2, double n, ::coder::array<double, 2U> &y)
  {
    if (!(n >= 0.0)) {
      y.set_size(1, 0);
    } else {
      double delta1;
      delta1 = std::floor(n);
      y.set_size(1, (static_cast<int>(delta1)));
      if (static_cast<int>(delta1) >= 1) {
        int y_tmp;
        y_tmp = static_cast<int>(delta1) - 1;
        y[static_cast<int>(delta1) - 1] = d2;
        if (y.size(1) >= 2) {
          y[0] = 1.0;
          if (y.size(1) >= 3) {
            if ((1.0 == -d2) && (static_cast<int>(delta1) > 2)) {
              for (int k = 2; k <= y_tmp; k++) {
                y[k - 1] = d2 * (static_cast<double>(((k << 1) - static_cast<int>
                  (delta1)) - 1) / (static_cast<double>(static_cast<int>(delta1))
                                    - 1.0));
              }

              if ((static_cast<int>(delta1) & 1) == 1) {
                y[static_cast<int>(delta1) >> 1] = 0.0;
              }
            } else if ((d2 < 0.0) && (std::abs(d2) > 8.9884656743115785E+307)) {
              double delta2;
              delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
              delta2 = d2 / (static_cast<double>(y.size(1)) - 1.0);
              y_tmp = y.size(1);
              for (int k = 0; k <= y_tmp - 3; k++) {
                y[k + 1] = (delta2 * (static_cast<double>(k) + 1.0) + 1.0) -
                  delta1 * (static_cast<double>(k) + 1.0);
              }
            } else {
              delta1 = (d2 - 1.0) / (static_cast<double>(y.size(1)) - 1.0);
              y_tmp = y.size(1);
              for (int k = 0; k <= y_tmp - 3; k++) {
                y[k + 1] = (static_cast<double>(k) + 1.0) * delta1 + 1.0;
              }
            }
          }
        }
      }
    }
  }
}

// End of code generation (linspace.cpp)
