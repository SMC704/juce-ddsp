//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  fftshift.cpp
//
//  Code generation for function 'fftshift'
//


// Include files
#include "fftshift.h"
#include "rt_nonfinite.h"

// Function Definitions
namespace coder
{
  void fftshift(double x[65])
  {
    int i2;
    i2 = 0;
    for (int i = 0; i < 1; i++) {
      int i1;
      i1 = i2;
      i2 += 64;
      for (int j = 0; j < 1; j++) {
        double xtmp;
        int ia;
        int ib;
        i1++;
        i2++;
        ia = i1 - 1;
        ib = i1 + 31;
        xtmp = x[i1 + 31];
        for (int k = 0; k < 32; k++) {
          x[ib] = x[ia];
          x[ia] = x[ib + 1];
          ia++;
          ib++;
        }

        x[ib] = xtmp;
      }
    }
  }
}

// End of code generation (fftshift.cpp)
