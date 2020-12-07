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
#include "additive.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Function Declarations
static void interp1Linear(const coder::array<double, 1U> &y, const coder::array<
  double, 1U> &xi, coder::array<double, 1U> &yi, const coder::array<double, 1U>
  &varargin_1);

// Function Definitions
static void interp1Linear(const coder::array<double, 1U> &y, const coder::array<
  double, 1U> &xi, coder::array<double, 1U> &yi, const coder::array<double, 1U>
  &varargin_1)
{
  double minx;
  double maxx;
  int ub_loop;
  int high_i;
  int low_i;
  int low_ip1;
  double r;
  int mid_i;
  double d;
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

void interp1(const coder::array<double, 1U> &varargin_1, const coder::array<
             double, 1U> &varargin_2, const coder::array<double, 1U> &varargin_3,
             coder::array<double, 1U> &Vq)
{
  coder::array<double, 1U> y;
  int n;
  int k;
  coder::array<double, 1U> x;
  int nx;
  y.set_size(varargin_2.size(0));
  n = varargin_2.size(0);
  for (k = 0; k < n; k++) {
    y[k] = varargin_2[k];
  }

  x.set_size(varargin_1.size(0));
  n = varargin_1.size(0);
  for (k = 0; k < n; k++) {
    x[k] = varargin_1[k];
  }

  nx = varargin_1.size(0) - 1;
  Vq.set_size(varargin_3.size(0));
  n = varargin_3.size(0);
  for (k = 0; k < n; k++) {
    Vq[k] = rtNaN;
  }

  if (varargin_3.size(0) != 0) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1[1] < varargin_1[0]) {
          int b_j1;
          double xtmp;
          k = (nx + 1) >> 1;
          for (b_j1 = 0; b_j1 < k; b_j1++) {
            xtmp = x[b_j1];
            n = nx - b_j1;
            x[b_j1] = x[n];
            x[n] = xtmp;
          }

          if (varargin_2.size(0) > 1) {
            n = varargin_2.size(0) - 1;
            nx = varargin_2.size(0) >> 1;
            for (k = 0; k < nx; k++) {
              xtmp = y[k];
              b_j1 = n - k;
              y[k] = y[b_j1];
              y[b_j1] = xtmp;
            }
          }
        }

        interp1Linear(y, varargin_3, Vq, x);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

// End of code generation (interp1.cpp)
