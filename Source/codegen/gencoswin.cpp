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
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Declarations
static void calc_window(double m, double n, coder::array<double, 1U> &w);
static int div_s32_floor(int numerator, int denominator);

// Function Definitions
static void calc_window(double m, double n, coder::array<double, 1U> &w)
{
  coder::array<double, 2U> y;
  int nx;
  int k;
  if (rtIsNaN(m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y.set_size(1, 0);
  } else if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
    y.set_size(1, 1);
    y[0] = rtNaN;
  } else {
    nx = static_cast<int>(std::floor(m - 1.0));
    y.set_size(1, (nx + 1));
    for (k = 0; k <= nx; k++) {
      y[k] = k;
    }
  }

  w.set_size(y.size(1));
  nx = y.size(1);
  for (k = 0; k < nx; k++) {
    w[k] = 6.2831853071795862 * (y[k] / (n - 1.0));
  }

  nx = w.size(0);
  for (k = 0; k < nx; k++) {
    w[k] = std::cos(w[k]);
  }

  nx = w.size(0);
  for (k = 0; k < nx; k++) {
    w[k] = 0.54 - 0.46 * w[k];
  }
}

static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int absDenominator;
    boolean_T quotientNeedsNegation;
    unsigned int tempAbsQuotient;
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

void sym_window(double n, coder::array<double, 1U> &w)
{
  double r;
  coder::array<double, 1U> b_w;
  if (rtIsNaN(n) || rtIsInf(n)) {
    r = rtNaN;
  } else if (n == 0.0) {
    r = 0.0;
  } else {
    r = std::fmod(n, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else {
      if (n < 0.0) {
        r += 2.0;
      }
    }
  }

  if (r == 0.0) {
    int i;
    int i1;
    int i2;
    int loop_ub;
    int b_loop_ub;
    calc_window(n / 2.0, n, w);
    if (1 > w.size(0)) {
      i = 0;
      i1 = 1;
      i2 = -1;
    } else {
      i = w.size(0) - 1;
      i1 = -1;
      i2 = 0;
    }

    loop_ub = div_s32_floor(i2 - i, i1);
    b_w.set_size(((w.size(0) + loop_ub) + 1));
    b_loop_ub = w.size(0);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
      b_w[i2] = w[i2];
    }

    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_w[i2 + w.size(0)] = w[i + i1 * i2];
    }

    w.set_size(b_w.size(0));
    loop_ub = b_w.size(0);
    for (i = 0; i < loop_ub; i++) {
      w[i] = b_w[i];
    }
  } else {
    int i;
    int i1;
    int i2;
    int loop_ub;
    int b_loop_ub;
    calc_window((n + 1.0) / 2.0, n, w);
    if (1 > w.size(0) - 1) {
      i = 0;
      i1 = 1;
      i2 = -1;
    } else {
      i = w.size(0) - 2;
      i1 = -1;
      i2 = 0;
    }

    loop_ub = div_s32_floor(i2 - i, i1);
    b_w.set_size(((w.size(0) + loop_ub) + 1));
    b_loop_ub = w.size(0);
    for (i2 = 0; i2 < b_loop_ub; i2++) {
      b_w[i2] = w[i2];
    }

    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_w[i2 + w.size(0)] = w[i + i1 * i2];
    }

    w.set_size(b_w.size(0));
    loop_ub = b_w.size(0);
    for (i = 0; i < loop_ub; i++) {
      w[i] = b_w[i];
    }
  }
}

// End of code generation (gencoswin.cpp)
