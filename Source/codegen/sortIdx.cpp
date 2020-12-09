//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  sortIdx.cpp
//
//  Code generation for function 'sortIdx'
//


// Include files
#include "sortIdx.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder
{
  namespace internal
  {
    void merge(int idx[6], double x[6], int offset, int np, int nq, int iwork[6],
               double xwork[6])
    {
      if (nq != 0) {
        int iout;
        int j;
        int n_tmp;
        int p;
        int q;
        n_tmp = np + nq;
        for (j = 0; j < n_tmp; j++) {
          iout = offset + j;
          iwork[j] = idx[iout];
          xwork[j] = x[iout];
        }

        p = 0;
        q = np;
        iout = offset - 1;
        int exitg1;
        do {
          exitg1 = 0;
          iout++;
          if (xwork[p] <= xwork[q]) {
            idx[iout] = iwork[p];
            x[iout] = xwork[p];
            if (p + 1 < np) {
              p++;
            } else {
              exitg1 = 1;
            }
          } else {
            idx[iout] = iwork[q];
            x[iout] = xwork[q];
            if (q + 1 < n_tmp) {
              q++;
            } else {
              q = iout - p;
              for (j = p + 1; j <= np; j++) {
                iout = q + j;
                idx[iout] = iwork[j - 1];
                x[iout] = xwork[j - 1];
              }

              exitg1 = 1;
            }
          }
        } while (exitg1 == 0);
      }
    }
  }
}

// End of code generation (sortIdx.cpp)
