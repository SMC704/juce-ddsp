//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  sort.cpp
//
//  Code generation for function 'sort'
//


// Include files
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder
{
  namespace internal
  {
    void sort(double x[6], int idx[6])
    {
      double xwork[6];
      double x4[4];
      int iwork[6];
      int i;
      int i1;
      int i2;
      int i3;
      int k;
      int nNaNs;
      signed char idx4[4];
      signed char perm[4];
      x4[0] = 0.0;
      idx4[0] = 0;
      x4[1] = 0.0;
      idx4[1] = 0;
      x4[2] = 0.0;
      idx4[2] = 0;
      x4[3] = 0.0;
      idx4[3] = 0;
      for (i = 0; i < 6; i++) {
        idx[i] = 0;
        xwork[i] = 0.0;
      }

      nNaNs = 0;
      i = 0;
      for (k = 0; k < 6; k++) {
        if (rtIsNaN(x[k])) {
          idx[5 - nNaNs] = k + 1;
          xwork[5 - nNaNs] = x[k];
          nNaNs++;
        } else {
          i++;
          idx4[i - 1] = static_cast<signed char>(k + 1);
          x4[i - 1] = x[k];
          if (i == 4) {
            double d;
            double d1;
            int i4;
            i = k - nNaNs;
            if (x4[0] <= x4[1]) {
              i1 = 1;
              i2 = 2;
            } else {
              i1 = 2;
              i2 = 1;
            }

            if (x4[2] <= x4[3]) {
              i3 = 3;
              i4 = 4;
            } else {
              i3 = 4;
              i4 = 3;
            }

            d = x4[i1 - 1];
            d1 = x4[i3 - 1];
            if (d <= d1) {
              d = x4[i2 - 1];
              if (d <= d1) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i2);
                perm[2] = static_cast<signed char>(i3);
                perm[3] = static_cast<signed char>(i4);
              } else if (d <= x4[i4 - 1]) {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i2);
                perm[3] = static_cast<signed char>(i4);
              } else {
                perm[0] = static_cast<signed char>(i1);
                perm[1] = static_cast<signed char>(i3);
                perm[2] = static_cast<signed char>(i4);
                perm[3] = static_cast<signed char>(i2);
              }
            } else {
              d1 = x4[i4 - 1];
              if (d <= d1) {
                if (x4[i2 - 1] <= d1) {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i2);
                  perm[3] = static_cast<signed char>(i4);
                } else {
                  perm[0] = static_cast<signed char>(i3);
                  perm[1] = static_cast<signed char>(i1);
                  perm[2] = static_cast<signed char>(i4);
                  perm[3] = static_cast<signed char>(i2);
                }
              } else {
                perm[0] = static_cast<signed char>(i3);
                perm[1] = static_cast<signed char>(i4);
                perm[2] = static_cast<signed char>(i1);
                perm[3] = static_cast<signed char>(i2);
              }
            }

            idx[i - 3] = idx4[perm[0] - 1];
            idx[i - 2] = idx4[perm[1] - 1];
            idx[i - 1] = idx4[perm[2] - 1];
            idx[i] = idx4[perm[3] - 1];
            x[i - 3] = x4[perm[0] - 1];
            x[i - 2] = x4[perm[1] - 1];
            x[i - 1] = x4[perm[2] - 1];
            x[i] = x4[perm[3] - 1];
            i = 0;
          }
        }
      }

      if (i > 0) {
        perm[1] = 0;
        perm[2] = 0;
        perm[3] = 0;
        if (i == 1) {
          perm[0] = 1;
        } else if (i == 2) {
          if (x4[0] <= x4[1]) {
            perm[0] = 1;
            perm[1] = 2;
          } else {
            perm[0] = 2;
            perm[1] = 1;
          }
        } else if (x4[0] <= x4[1]) {
          if (x4[1] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 2;
            perm[2] = 3;
          } else if (x4[0] <= x4[2]) {
            perm[0] = 1;
            perm[1] = 3;
            perm[2] = 2;
          } else {
            perm[0] = 3;
            perm[1] = 1;
            perm[2] = 2;
          }
        } else if (x4[0] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 1;
          perm[2] = 3;
        } else if (x4[1] <= x4[2]) {
          perm[0] = 2;
          perm[1] = 3;
          perm[2] = 1;
        } else {
          perm[0] = 3;
          perm[1] = 2;
          perm[2] = 1;
        }

        for (k = 0; k < i; k++) {
          i2 = perm[k] - 1;
          i1 = ((k - nNaNs) - i) + 6;
          idx[i1] = idx4[i2];
          x[i1] = x4[i2];
        }
      }

      i = (nNaNs >> 1) + 6;
      for (k = 0; k <= i - 7; k++) {
        i2 = (k - nNaNs) + 6;
        i1 = idx[i2];
        idx[i2] = idx[5 - k];
        idx[5 - k] = i1;
        x[i2] = xwork[5 - k];
        x[5 - k] = xwork[i2];
      }

      if ((nNaNs & 1) != 0) {
        i -= nNaNs;
        x[i] = xwork[i];
      }

      if (6 - nNaNs > 1) {
        for (i = 0; i < 6; i++) {
          iwork[i] = 0;
        }

        i3 = (6 - nNaNs) >> 2;
        i1 = 4;
        while (i3 > 1) {
          if ((i3 & 1) != 0) {
            i3--;
            i = i1 * i3;
            i2 = 6 - (nNaNs + i);
            if (i2 > i1) {
              merge(idx, x, i, i1, i2 - i1, iwork, xwork);
            }
          }

          i = i1 << 1;
          i3 >>= 1;
          for (k = 0; k < i3; k++) {
            merge(idx, x, k * i, i1, i1, iwork, xwork);
          }

          i1 = i;
        }

        if (6 - nNaNs > i1) {
          merge(idx, x, 0, i1, 6 - (nNaNs + i1), iwork, xwork);
        }
      }
    }
  }
}

// End of code generation (sort.cpp)
