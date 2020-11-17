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
#include "ifft.h"
#include "irfft.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void fft(const coder::array<double, 2U> &x, double varargin_1, coder::array<
         creal_T, 2U> &y)
{
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int loop_ub;
  int N2blue;
  int nd2;
  int i;
  coder::array<double, 2U> costab1q;
  coder::array<creal_T, 1U> yCol;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  guard1 = false;
  guard2 = false;
  if (x.size(1) == 0) {
    guard2 = true;
  } else {
    loop_ub = static_cast<int>(varargin_1);
    if (0 == loop_ub) {
      guard2 = true;
    } else {
      boolean_T useRadix2;
      double e;
      int n;
      int k;
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

      i = nd2 + 2;
      nd2 = n - 1;
      for (k = i; k <= nd2; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(n - k));
      }

      costab1q[n] = 0.0;
      if (!useRadix2) {
        n = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (nd2 + 1));
        for (k = 0; k < n; k++) {
          sintabinv[k + 1] = costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - n];
        }

        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - n];
        }
      } else {
        n = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - n];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        yCol.set_size(loop_ub);
        if (loop_ub > x.size(1)) {
          yCol.set_size(loop_ub);
          for (i = 0; i < loop_ub; i++) {
            yCol[i].re = 0.0;
            yCol[i].im = 0.0;
          }
        }

        if (loop_ub != 1) {
          coder::array<double, 1U> b_x;
          nd2 = x.size(1);
          b_x = x.reshape(nd2);
          FFTImplementationCallback::doHalfLengthRadix2((b_x), (yCol), (
            static_cast<int>(varargin_1)), (costab), (sintab));
          guard1 = true;
        } else {
          int b_loop_ub;
          nd2 = x.size(1);
          if (nd2 >= 1) {
            nd2 = 1;
          }

          b_loop_ub = nd2 - 2;
          n = 0;
          int exitg1;
          do {
            if (n <= b_loop_ub) {
              yCol[0].re = x[0];
              yCol[0].im = 0.0;
              exitg1 = 1;
            } else {
              yCol[0].re = x[0];
              yCol[0].im = 0.0;
              guard1 = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
      } else {
        coder::array<double, 1U> b_x;
        nd2 = x.size(1);
        b_x = x.reshape(nd2);
        FFTImplementationCallback::dobluesteinfft((b_x), (N2blue), (static_cast<
          int>(varargin_1)), (costab), (sintab), (sintabinv), (yCol));
        guard1 = true;
      }
    }
  }

  if (guard2) {
    loop_ub = static_cast<int>(varargin_1);
    y.set_size(1, loop_ub);
    for (i = 0; i < loop_ub; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  }

  if (guard1) {
    y.set_size(1, loop_ub);
    for (i = 0; i < loop_ub; i++) {
      y[i] = yCol[i];
    }
  }
}

// End of code generation (fft.cpp)
