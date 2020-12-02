//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ifft.cpp
//
//  Code generation for function 'ifft'
//


// Include files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void ifft(const coder::array<double, 1U> &x, double varargin_1, coder::array<
          creal_T, 1U> &y)
{
  int loop_ub;
  int N2blue;
  int nd2;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  loop_ub = static_cast<int>(varargin_1);
  if (0 == loop_ub) {
    y.set_size(0);
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
        sintab[k + 1] = costab1q[(n - k) - 1];
      }

      nd2 = costab1q.size(1);
      for (k = nd2; k <= n2; k++) {
        costab[k] = -costab1q[n2 - k];
        sintab[k] = costab1q[k - n];
      }

      sintabinv.set_size(1, 0);
    }

    if (useRadix2) {
      boolean_T guard1 = false;
      y.set_size(loop_ub);
      if (loop_ub > x.size(0)) {
        y.set_size(loop_ub);
        for (nd2 = 0; nd2 < loop_ub; nd2++) {
          y[nd2].re = 0.0;
          y[nd2].im = 0.0;
        }
      }

      guard1 = false;
      if (loop_ub != 1) {
        FFTImplementationCallback::doHalfLengthRadix2((x), (y), (static_cast<int>
          (varargin_1)), (costab), (sintab));
        guard1 = true;
      } else {
        int b_loop_ub;
        nd2 = x.size(0);
        if (nd2 >= 1) {
          nd2 = 1;
        }

        b_loop_ub = nd2 - 2;
        n2 = 0;
        int exitg1;
        do {
          if (n2 <= b_loop_ub) {
            y[0].re = x[0];
            y[0].im = 0.0;
            exitg1 = 1;
          } else {
            y[0].re = x[0];
            y[0].im = 0.0;
            guard1 = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (guard1 && (y.size(0) > 1)) {
        e = 1.0 / static_cast<double>(y.size(0));
        loop_ub = y.size(0);
        for (nd2 = 0; nd2 < loop_ub; nd2++) {
          y[nd2].re = e * y[nd2].re;
          y[nd2].im = e * y[nd2].im;
        }
      }
    } else {
      FFTImplementationCallback::dobluesteinfft((x), (N2blue), (static_cast<int>
        (varargin_1)), (costab), (sintab), (sintabinv), (y));
    }
  }
}

// End of code generation (ifft.cpp)
