//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  rescale.cpp
//
//  Code generation for function 'rescale'
//


// Include files
#include "rescale.h"
#include "DDSPSynth_rtwutil.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <math.h>

// Function Definitions
void RESCALE(double A_data[], const int A_size[1], double inputMin, double
             inputMax)
{
  int eint;
  boolean_T tmp_data[4161];
  short b_tmp_data[4161];
  if (A_size[0] != 0) {
    double sigma;
    int loop_ub;
    int i;
    double iMin;
    double iMax;
    double r1;
    double r3;
    if ((0.0 < inputMax) || rtIsNaN(inputMax)) {
      sigma = 0.0;
    } else {
      sigma = inputMax;
    }

    if ((!(sigma > inputMin)) && (!rtIsNaN(inputMin))) {
      sigma = inputMin;
    }

    loop_ub = A_size[0];
    for (i = 0; i < loop_ub; i++) {
      A_data[i] -= sigma;
    }

    iMin = inputMin - sigma;
    iMax = inputMax - sigma;
    sigma = std::abs(iMax);
    r1 = std::abs(iMin);
    if ((!(sigma > r1)) && (!rtIsNaN(r1))) {
      sigma = r1;
    }

    if ((!rtIsInf(sigma)) && (!rtIsNaN(sigma))) {
      frexp(sigma, &eint);
    } else {
      eint = 0;
    }

    r1 = rt_powd_snf(2.0, static_cast<double>(eint) - 1.0);
    sigma = (static_cast<double>(eint) + 1.0) / 2.0;
    if (sigma < 0.0) {
      sigma = std::ceil(sigma);
    } else {
      sigma = std::floor(sigma);
    }

    r3 = rt_powd_snf(2.0, sigma - 1.0);
    if (iMin == iMax) {
      int trueCount;
      eint = A_size[0];
      loop_ub = A_size[0];
      for (i = 0; i < loop_ub; i++) {
        tmp_data[i] = rtIsNaN(A_data[i]);
      }

      for (i = 0; i < eint; i++) {
        tmp_data[i] = !tmp_data[i];
      }

      eint--;
      trueCount = 0;
      loop_ub = 0;
      for (i = 0; i <= eint; i++) {
        if (tmp_data[i]) {
          trueCount++;
          b_tmp_data[loop_ub] = static_cast<short>(i + 1);
          loop_ub++;
        }
      }

      for (i = 0; i < trueCount; i++) {
        A_data[b_tmp_data[i] - 1] = -1.0;
      }
    } else {
      double c1;
      c1 = iMax / r1;
      sigma = iMin / r1;
      r1 = 2.0 / (iMax / r3 - iMin / r3) / r3;
      sigma = r3 * ((c1 * (-1.0 / r3) - sigma * (1.0 / r3)) / (c1 - sigma));
      loop_ub = A_size[0];
      for (i = 0; i < loop_ub; i++) {
        A_data[i] = r1 * A_data[i] + sigma;
      }

      eint = A_size[0];
      for (i = 0; i < eint; i++) {
        if (A_data[i] < -1.0) {
          A_data[i] = -1.0;
        }
      }

      eint = A_size[0];
      for (i = 0; i < eint; i++) {
        if (A_data[i] > 1.0) {
          A_data[i] = 1.0;
        }
      }
    }
  }
}

// End of code generation (rescale.cpp)
