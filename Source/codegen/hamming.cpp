//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  hamming.cpp
//
//  Code generation for function 'hamming'
//


// Include files
#include "hamming.h"
#include "DDSPSynth_rtwutil.h"
#include "additive.h"
#include "gencoswin.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Declarations
static int div_s32_floor(int numerator, int denominator);

// Function Definitions
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

void hamming(double varargin_1, double w_data[], int w_size[1])
{
  int w_size_idx_0;
  signed char b_w_data[1];
  int trivialwin;
  double L;
  double tmp_data[2048];
  int tmp_size[1];
  double c_w_data[4097];
  w_size_idx_0 = 1;
  b_w_data[0] = 0;
  trivialwin = 0;
  if (varargin_1 == std::floor(varargin_1)) {
    L = varargin_1;
  } else {
    L = rt_roundd_snf(varargin_1);
  }

  if (L == 0.0) {
    w_size_idx_0 = 0;
    trivialwin = 1;
  } else {
    if (L == 1.0) {
      b_w_data[0] = 1;
      trivialwin = 1;
    }
  }

  w_size[0] = w_size_idx_0;
  if (0 <= w_size_idx_0 - 1) {
    w_data[0] = b_w_data[0];
  }

  if (trivialwin == 0) {
    double r;
    if (rtIsNaN(L) || rtIsInf(L)) {
      r = rtNaN;
    } else if (L == 0.0) {
      r = 0.0;
    } else {
      r = std::fmod(L, 2.0);
      if (r == 0.0) {
        r = 0.0;
      }
    }

    if (r == 0.0) {
      int loop_ub;
      int i;
      int i1;
      calc_window(L / 2.0, L, tmp_data, tmp_size);
      loop_ub = tmp_size[0];
      if (0 <= loop_ub - 1) {
        std::memcpy(&w_data[0], &tmp_data[0], loop_ub * sizeof(double));
      }

      if (1 > tmp_size[0]) {
        i = 0;
        i1 = 1;
        trivialwin = -1;
      } else {
        i = tmp_size[0] - 1;
        i1 = -1;
        trivialwin = 0;
      }

      loop_ub = div_s32_floor(trivialwin - i, i1);
      w_size_idx_0 = (tmp_size[0] + loop_ub) + 1;
      trivialwin = tmp_size[0];
      if (0 <= trivialwin - 1) {
        std::memcpy(&c_w_data[0], &w_data[0], trivialwin * sizeof(double));
      }

      for (trivialwin = 0; trivialwin <= loop_ub; trivialwin++) {
        c_w_data[trivialwin + tmp_size[0]] = w_data[i + i1 * trivialwin];
      }

      w_size[0] = w_size_idx_0;
      if (0 <= w_size_idx_0 - 1) {
        std::memcpy(&w_data[0], &c_w_data[0], w_size_idx_0 * sizeof(double));
      }
    } else {
      int loop_ub;
      int i;
      int i1;
      calc_window((L + 1.0) / 2.0, L, tmp_data, tmp_size);
      loop_ub = tmp_size[0];
      if (0 <= loop_ub - 1) {
        std::memcpy(&w_data[0], &tmp_data[0], loop_ub * sizeof(double));
      }

      if (1 > tmp_size[0] - 1) {
        i = 0;
        i1 = 1;
        trivialwin = -1;
      } else {
        i = tmp_size[0] - 2;
        i1 = -1;
        trivialwin = 0;
      }

      loop_ub = div_s32_floor(trivialwin - i, i1);
      w_size_idx_0 = (tmp_size[0] + loop_ub) + 1;
      trivialwin = tmp_size[0];
      if (0 <= trivialwin - 1) {
        std::memcpy(&c_w_data[0], &w_data[0], trivialwin * sizeof(double));
      }

      for (trivialwin = 0; trivialwin <= loop_ub; trivialwin++) {
        c_w_data[trivialwin + tmp_size[0]] = w_data[i + i1 * trivialwin];
      }

      w_size[0] = w_size_idx_0;
      if (0 <= w_size_idx_0 - 1) {
        std::memcpy(&w_data[0], &c_w_data[0], w_size_idx_0 * sizeof(double));
      }
    }
  }
}

// End of code generation (hamming.cpp)
