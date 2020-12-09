//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  interp1.cpp
//
//  Code generation for function 'interp1'
//


// Include files
#include "interp1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder
{
  void interp1Linear(const ::coder::array<double, 1U> &y, const ::coder::array<
                     double, 1U> &xi, ::coder::array<double, 1U> &yi, const ::
                     coder::array<double, 1U> &varargin_1)
  {
    double d;
    double maxx;
    double minx;
    double r;
    int high_i;
    int low_i;
    int low_ip1;
    int mid_i;
    int ub_loop;
    minx = varargin_1[0];
    maxx = varargin_1[varargin_1.size(0) - 1];
    ub_loop = xi.size(0) - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(high_i,low_i,low_ip1,r,mid_i,d)

    for (int k = 0; k <= ub_loop; k++) {
      if (rtIsNaN(xi[k])) {
        yi[k] = rtNaN;
      } else {
        if ((!(xi[k] > maxx)) && (!(xi[k] < minx))) {
          high_i = varargin_1.size(0);
          low_i = 1;
          low_ip1 = 2;
          while (high_i > low_ip1) {
            mid_i = (low_i >> 1) + (high_i >> 1);
            if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
              mid_i++;
            }

            if (xi[k] >= varargin_1[mid_i - 1]) {
              low_i = mid_i;
              low_ip1 = mid_i + 1;
            } else {
              high_i = mid_i;
            }
          }

          r = varargin_1[low_i - 1];
          r = (xi[k] - r) / (varargin_1[low_i] - r);
          if (r == 0.0) {
            yi[k] = y[low_i - 1];
          } else if (r == 1.0) {
            yi[k] = y[low_i];
          } else {
            d = y[low_i - 1];
            if (d == y[low_i]) {
              yi[k] = d;
            } else {
              yi[k] = (1.0 - r) * d + r * y[low_i];
            }
          }
        }
      }
    }
  }
}

// End of code generation (interp1.cpp)
