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
  int N2blue;
  int nd2;
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
      double e;
      int n;
      int k;
      int n2;
      useRadix2 = ((loop_ub > 0) && ((loop_ub & (loop_ub - 1)) == 0));
      FFTImplementationCallback::get_algo_sizes((static_cast<int>(varargin_1)),
        (useRadix2), (&N2blue), (&nd2));
      e = 6.2831853071795862 / static_cast<double>(nd2);
      n = nd2 / 2 / 2;
      costab1q.set_size(1, (n + 1));
      costab1q[0] = 1.0;
      nd2 = n / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }

      nd2 += 2;
      n2 = n - 1;
      for (k = nd2; k <= n2; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(n - k));
      }

      costab1q[n] = 0.0;
      if (!useRadix2) {
        n = costab1q.size(1) - 1;
        n2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (n2 + 1));
        sintab.set_size(1, (n2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (n2 + 1));
        for (k = 0; k < n; k++) {
          sintabinv[k + 1] = costab1q[(n - k) - 1];
        }

        nd2 = costab1q.size(1);
        for (k = nd2; k <= n2; k++) {
          sintabinv[k] = costab1q[k - n];
        }

        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        nd2 = costab1q.size(1);
        for (k = nd2; k <= n2; k++) {
          costab[k] = -costab1q[n2 - k];
          sintab[k] = -costab1q[k - n];
        }
      } else {
        n = costab1q.size(1) - 1;
        n2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (n2 + 1));
        sintab.set_size(1, (n2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        nd2 = costab1q.size(1);
        for (k = nd2; k <= n2; k++) {
          costab[k] = -costab1q[n2 - k];
          sintab[k] = -costab1q[k - n];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        y.set_size(loop_ub);
        if (loop_ub > x_size[0]) {
          y.set_size(loop_ub);
          for (nd2 = 0; nd2 < loop_ub; nd2++) {
            y[nd2].re = 0.0;
            y[nd2].im = 0.0;
          }
        }

        if (loop_ub != 1) {
          FFTImplementationCallback::doHalfLengthRadix2((x_data), (x_size), (y),
            (static_cast<int>(varargin_1)), (costab), (sintab));
        } else {
          int b_loop_ub;
          nd2 = x_size[0];
          if (nd2 >= 1) {
            nd2 = 1;
          }

          b_loop_ub = nd2 - 2;
          n2 = 0;
          int exitg1;
          do {
            if (n2 <= b_loop_ub) {
              y[0].re = x_data[0];
              y[0].im = 0.0;
              exitg1 = 1;
            } else {
              y[0].re = x_data[0];
              y[0].im = 0.0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
      } else {
        FFTImplementationCallback::dobluesteinfft((x_data), (x_size), (N2blue),
          (static_cast<int>(varargin_1)), (costab), (sintab), (sintabinv), (y));
      }
    }
  }

  if (guard1) {
    loop_ub = static_cast<int>(varargin_1);
    y.set_size(loop_ub);
    for (nd2 = 0; nd2 < loop_ub; nd2++) {
      y[nd2].re = 0.0;
      y[nd2].im = 0.0;
    }
  }
}

// End of code generation (fft.cpp)
