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
#include "irfft.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void b_ifft(const coder::array<creal_T, 2U> &x, coder::array<creal_T, 2U> &y)
{
  int N2blue;
  int nd2;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    unsigned int ySize_idx_1;
    ySize_idx_1 = static_cast<unsigned int>(x.size(1));
    y.set_size(x.size(0), (static_cast<int>(ySize_idx_1)));
    nd2 = x.size(0) * static_cast<int>(ySize_idx_1);
    for (int i = 0; i < nd2; i++) {
      y[i].re = 0.0;
      y[i].im = 0.0;
    }
  } else {
    boolean_T useRadix2;
    double e;
    int n;
    int i;
    int k;
    useRadix2 = ((x.size(0) & (x.size(0) - 1)) == 0);
    FFTImplementationCallback::get_algo_sizes((x.size(0)), (useRadix2), (&N2blue),
      (&nd2));
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
        sintab[k + 1] = costab1q[(n - k) - 1];
      }

      i = costab1q.size(1);
      for (k = i; k <= nd2; k++) {
        costab[k] = -costab1q[nd2 - k];
        sintab[k] = costab1q[k - n];
      }

      sintabinv.set_size(1, 0);
    }

    if (useRadix2) {
      FFTImplementationCallback::r2br_r2dit_trig((x), (x.size(0)), (costab),
        (sintab), (y));
    } else {
      FFTImplementationCallback::dobluesteinfft((x), (N2blue), (x.size(0)),
        (costab), (sintab), (sintabinv), (y));
    }
  }
}

void ifft(const creal_T x_data[], creal_T y_data[], int y_size[1])
{
  int N2blue;
  int nRows;
  double costab_data[2047];
  int costab_size[2];
  double sintab_data[2047];
  int sintab_size[2];
  double sintabinv_data[2047];
  int sintabinv_size[2];
  FFTImplementationCallback::get_algo_sizes((1023), (false), (&N2blue), (&nRows));
  FFTImplementationCallback::generate_twiddle_tables((nRows), (costab_data),
    (costab_size), (sintab_data), (sintab_size), (sintabinv_data),
    (sintabinv_size));
  FFTImplementationCallback::dobluesteinfft((x_data), (N2blue), (costab_data),
    (costab_size), (sintab_data), (sintab_size), (sintabinv_data),
    (sintabinv_size), (y_data), (y_size));
}

// End of code generation (ifft.cpp)
