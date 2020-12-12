//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  sortIdx.h
//
//  Code generation for function 'sortIdx'
//


#ifndef SORTIDX_H
#define SORTIDX_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder
{
  namespace internal
  {
    void merge(int idx[6], double x[6], int offset, int np, int nq, int iwork[6],
               double xwork[6]);
  }
}

#endif

// End of code generation (sortIdx.h)
