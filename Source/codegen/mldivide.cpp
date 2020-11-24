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
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Definitions
void mldiv(const double A_data[], double B_data[])
{
  double b_A_data[4225];
  int ipiv_data[65];
  int yk;
  int k;
  int iy;
  int i;
  int jA;
  int ix;
  std::memcpy(&b_A_data[0], &A_data[0], 4225U * sizeof(double));
  ipiv_data[0] = 1;
  yk = 1;
  for (k = 0; k < 64; k++) {
    int mmj_tmp;
    int b;
    int jj;
    int jp1j;
    double smax;
    int b_k;
    yk++;
    ipiv_data[k + 1] = yk;
    mmj_tmp = 63 - k;
    b = k * 66;
    jj = k * 66;
    jp1j = b + 2;
    iy = 65 - k;
    jA = 0;
    ix = b;
    smax = std::abs(b_A_data[jj]);
    for (b_k = 2; b_k <= iy; b_k++) {
      double s;
      ix++;
      s = std::abs(b_A_data[ix]);
      if (s > smax) {
        jA = b_k - 1;
        smax = s;
      }
    }

    if (b_A_data[jj + jA] != 0.0) {
      if (jA != 0) {
        iy = k + jA;
        ipiv_data[k] = iy + 1;
        ix = k;
        for (b_k = 0; b_k < 65; b_k++) {
          smax = b_A_data[ix];
          b_A_data[ix] = b_A_data[iy];
          b_A_data[iy] = smax;
          ix += 65;
          iy += 65;
        }
      }

      i = (jj - k) + 65;
      for (jA = jp1j; jA <= i; jA++) {
        b_A_data[jA - 1] /= b_A_data[jj];
      }
    }

    iy = b + 65;
    jA = jj;
    for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
      smax = b_A_data[iy];
      if (b_A_data[iy] != 0.0) {
        ix = jj + 1;
        i = jA + 67;
        b = (jA - k) + 130;
        for (b_k = i; b_k <= b; b_k++) {
          b_A_data[b_k - 1] += b_A_data[ix] * -smax;
          ix++;
        }
      }

      iy += 65;
      jA += 65;
    }

    if (ipiv_data[k] != k + 1) {
      smax = B_data[k];
      B_data[k] = B_data[ipiv_data[k] - 1];
      B_data[ipiv_data[k] - 1] = smax;
    }
  }

  for (k = 0; k < 65; k++) {
    iy = 65 * k;
    if (B_data[k] != 0.0) {
      i = k + 2;
      for (jA = i; jA < 66; jA++) {
        B_data[jA - 1] -= B_data[k] * b_A_data[(jA + iy) - 1];
      }
    }
  }

  for (k = 64; k >= 0; k--) {
    iy = 65 * k;
    if (B_data[k] != 0.0) {
      B_data[k] /= b_A_data[k + iy];
      for (jA = 0; jA < k; jA++) {
        B_data[jA] -= B_data[k] * b_A_data[jA + iy];
      }
    }
  }
}

// End of code generation (mldivide.cpp)
