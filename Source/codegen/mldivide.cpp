//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  mldivide.cpp
//
//  Code generation for function 'mldivide'
//


// Include files
#include "mldivide.h"
#include "additive.h"
#include "findpeaks.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Definitions
void mldiv(const double A_data[], double B_data[])
{
  double b_A_data[4225];
  coder::array<int, 2U> y;
  int yk;
  int k;
  int i;
  int ipiv_data[65];
  int jA;
  int ix;
  std::memcpy(&b_A_data[0], &A_data[0], 4225U * sizeof(double));
  y.set_size(1, 65);
  y[0] = 1;
  yk = 1;
  for (k = 0; k < 64; k++) {
    yk++;
    y[k + 1] = yk;
  }

  yk = y.size(0) * y.size(1);
  for (i = 0; i < yk; i++) {
    ipiv_data[i] = y[i];
  }

  for (int j = 0; j < 64; j++) {
    int mmj_tmp;
    int b;
    int jj;
    int jp1j;
    double smax;
    mmj_tmp = 63 - j;
    b = j * 66;
    jj = j * 66;
    jp1j = b + 2;
    yk = 65 - j;
    jA = 0;
    ix = b;
    smax = std::abs(b_A_data[jj]);
    for (k = 2; k <= yk; k++) {
      double s;
      ix++;
      s = std::abs(b_A_data[ix]);
      if (s > smax) {
        jA = k - 1;
        smax = s;
      }
    }

    if (b_A_data[jj + jA] != 0.0) {
      if (jA != 0) {
        yk = j + jA;
        ipiv_data[j] = yk + 1;
        ix = j;
        for (k = 0; k < 65; k++) {
          smax = b_A_data[ix];
          b_A_data[ix] = b_A_data[yk];
          b_A_data[yk] = smax;
          ix += 65;
          yk += 65;
        }
      }

      i = (jj - j) + 65;
      for (jA = jp1j; jA <= i; jA++) {
        b_A_data[jA - 1] /= b_A_data[jj];
      }
    }

    yk = b + 65;
    jA = jj;
    for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
      smax = b_A_data[yk];
      if (b_A_data[yk] != 0.0) {
        ix = jj + 1;
        i = jA + 67;
        b = (jA - j) + 130;
        for (k = i; k <= b; k++) {
          b_A_data[k - 1] += b_A_data[ix] * -smax;
          ix++;
        }
      }

      yk += 65;
      jA += 65;
    }

    if (ipiv_data[j] != j + 1) {
      smax = B_data[j];
      B_data[j] = B_data[ipiv_data[j] - 1];
      B_data[ipiv_data[j] - 1] = smax;
    }
  }

  for (k = 0; k < 65; k++) {
    yk = 65 * k;
    if (B_data[k] != 0.0) {
      i = k + 2;
      for (jA = i; jA < 66; jA++) {
        B_data[jA - 1] -= B_data[k] * b_A_data[(jA + yk) - 1];
      }
    }
  }

  for (k = 64; k >= 0; k--) {
    yk = 65 * k;
    if (B_data[k] != 0.0) {
      B_data[k] /= b_A_data[k + yk];
      for (jA = 0; jA < k; jA++) {
        B_data[jA] -= B_data[k] * b_A_data[jA + yk];
      }
    }
  }
}

// End of code generation (mldivide.cpp)
