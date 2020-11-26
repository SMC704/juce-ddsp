//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  fft.cpp
//
//  Code generation for function 'fft'
//


// Include files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "additive.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void fft(const double x_data[], const int x_size[1], double varargin_1, coder::
         array<creal_T, 1U> &y)
{
  boolean_T guard1 = false;
  int loop_ub;
  int pmin;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  guard1 = false;
  if (x_size[0] == 0) {
    guard1 = true;
  } else {
    loop_ub = static_cast<int>(varargin_1);
    if (0 == loop_ub) {
      guard1 = true;
    } else {
      boolean_T useRadix2;
      int pow2p;
      int n;
      int pmax;
      double e;
      int k;
      useRadix2 = ((loop_ub > 0) && ((loop_ub & (loop_ub - 1)) == 0));
      pow2p = 1;
      if (useRadix2) {
        pmin = loop_ub;
      } else {
        if (loop_ub > 0) {
          n = (loop_ub + loop_ub) - 1;
          pmax = 31;
          if (n <= 1) {
            pmax = 0;
          } else {
            boolean_T exitg1;
            pmin = 0;
            exitg1 = false;
            while ((!exitg1) && (pmax - pmin > 1)) {
              k = (pmin + pmax) >> 1;
              pow2p = 1 << k;
              if (pow2p == n) {
                pmax = k;
                exitg1 = true;
              } else if (pow2p > n) {
                pmax = k;
              } else {
                pmin = k;
              }
            }
          }

          pow2p = 1 << pmax;
        }

        pmin = pow2p;
      }

      e = 6.2831853071795862 / static_cast<double>(pmin);
      n = pmin / 2 / 2;
      costab1q.set_size(1, (n + 1));
      costab1q[0] = 1.0;
      pmin = n / 2 - 1;
      for (k = 0; k <= pmin; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }

      pmin += 2;
      pmax = n - 1;
      for (k = pmin; k <= pmax; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(n - k));
      }

      costab1q[n] = 0.0;
      if (!useRadix2) {
        n = costab1q.size(1) - 1;
        pmax = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (pmax + 1));
        sintab.set_size(1, (pmax + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (pmax + 1));
        for (k = 0; k < n; k++) {
          sintabinv[k + 1] = costab1q[(n - k) - 1];
        }

        pmin = costab1q.size(1);
        for (k = pmin; k <= pmax; k++) {
          sintabinv[k] = costab1q[k - n];
        }

        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        pmin = costab1q.size(1);
        for (k = pmin; k <= pmax; k++) {
          costab[k] = -costab1q[pmax - k];
          sintab[k] = -costab1q[k - n];
        }
      } else {
        n = costab1q.size(1) - 1;
        pmax = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (pmax + 1));
        sintab.set_size(1, (pmax + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        pmin = costab1q.size(1);
        for (k = pmin; k <= pmax; k++) {
          costab[k] = -costab1q[pmax - k];
          sintab[k] = -costab1q[k - n];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        y.set_size(loop_ub);
        if (loop_ub > x_size[0]) {
          y.set_size(loop_ub);
          for (pmin = 0; pmin < loop_ub; pmin++) {
            y[pmin].re = 0.0;
            y[pmin].im = 0.0;
          }
        }

        if (loop_ub != 1) {
          FFTImplementationCallback::doHalfLengthRadix2((x_data), (x_size), (y),
            (static_cast<int>(varargin_1)), (costab), (sintab));
        } else {
          int b_loop_ub;
          pmin = x_size[0];
          if (pmin >= 1) {
            pmin = 1;
          }

          b_loop_ub = pmin - 2;
          pmax = 0;
          int exitg2;
          do {
            if (pmax <= b_loop_ub) {
              y[0].re = x_data[0];
              y[0].im = 0.0;
              exitg2 = 1;
            } else {
              y[0].re = x_data[0];
              y[0].im = 0.0;
              exitg2 = 1;
            }
          } while (exitg2 == 0);
        }
      } else {
        FFTImplementationCallback::dobluesteinfft((x_data), (x_size), (pow2p), (
          static_cast<int>(varargin_1)), (costab), (sintab), (sintabinv), (y));
      }
    }
  }

  if (guard1) {
    loop_ub = static_cast<int>(varargin_1);
    y.set_size(loop_ub);
    for (pmin = 0; pmin < loop_ub; pmin++) {
      y[pmin].re = 0.0;
      y[pmin].im = 0.0;
    }
  }
}

// End of code generation (fft.cpp)
