//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  eml_setop.cpp
//
//  Code generation for function 'eml_setop'
//


// Include files
#include "eml_setop.h"
#include "additive.h"
#include "findpeaks.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Function Definitions
void do_vectors(const coder::array<int, 1U> &a, const coder::array<int, 1U> &b,
                coder::array<int, 1U> &c, coder::array<int, 1U> &ia, coder::
                array<int, 1U> &ib)
{
  int na;
  int nb;
  int ncmax;
  int nc;
  int nia;
  int nib;
  int iafirst;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  int b_iblast;
  na = a.size(0);
  nb = b.size(0);
  ncmax = a.size(0) + b.size(0);
  c.set_size(ncmax);
  ia.set_size(a.size(0));
  ib.set_size(b.size(0));
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 0;
  ibfirst = 0;
  iblast = 0;
  while ((ialast + 1 <= na) && (iblast + 1 <= nb)) {
    int ak;
    int bk;
    b_ialast = ialast + 1;
    ak = a[ialast];
    while ((b_ialast < a.size(0)) && (a[b_ialast] == ak)) {
      b_ialast++;
    }

    ialast = b_ialast - 1;
    b_iblast = iblast + 1;
    bk = b[iblast];
    while ((b_iblast < b.size(0)) && (b[b_iblast] == bk)) {
      b_iblast++;
    }

    iblast = b_iblast - 1;
    if (ak == bk) {
      nc++;
      c[nc] = ak;
      nia++;
      ia[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c[nc] = ak;
      ia[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c[nc] = bk;
      ib[nib - 1] = ibfirst + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    }
  }

  while (ialast + 1 <= na) {
    b_ialast = ialast + 1;
    while ((b_ialast < a.size(0)) && (a[b_ialast] == a[ialast])) {
      b_ialast++;
    }

    nc++;
    nia++;
    c[nc] = a[ialast];
    ia[nia] = iafirst;
    ialast = b_ialast;
    iafirst = b_ialast + 1;
  }

  while (iblast + 1 <= nb) {
    b_iblast = iblast + 1;
    while ((b_iblast < b.size(0)) && (b[b_iblast] == b[iblast])) {
      b_iblast++;
    }

    nc++;
    nib++;
    c[nc] = b[iblast];
    ib[nib - 1] = ibfirst + 1;
    iblast = b_iblast;
    ibfirst = b_iblast;
  }

  if (a.size(0) > 0) {
    if (1 > nia + 1) {
      na = 0;
    } else {
      na = nia + 1;
    }

    ia.set_size(na);
  }

  if (b.size(0) > 0) {
    if (1 > nib) {
      nib = 0;
    }

    ib.set_size(nib);
  }

  if (ncmax > 0) {
    if (1 > nc + 1) {
      na = 0;
    } else {
      na = nc + 1;
    }

    c.set_size(na);
  }
}

// End of code generation (eml_setop.cpp)
