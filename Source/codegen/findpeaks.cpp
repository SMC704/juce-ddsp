//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  findpeaks.cpp
//
//  Code generation for function 'findpeaks'
//


// Include files
#include "findpeaks.h"
#include "additive.h"
#include "eml_setop.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"

// Function Definitions
void findpeaks(const coder::array<double, 1U> &Yin, coder::array<double, 1U>
               &Ypk, coder::array<double, 1U> &Xpk)
{
  coder::array<unsigned int, 2U> y;
  int ny;
  int nInf;
  coder::array<unsigned int, 1U> x;
  coder::array<int, 1U> iFinite;
  coder::array<int, 1U> iInfinite;
  int nPk;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  coder::array<int, 1U> iPk;
  coder::array<int, 1U> c;
  coder::array<int, 1U> idx;
  coder::array<int, 2U> b_y;
  y.set_size(1, Yin.size(0));
  ny = Yin.size(0) - 1;
  for (nInf = 0; nInf <= ny; nInf++) {
    y[nInf] = nInf + 1U;
  }

  x.set_size(y.size(1));
  ny = y.size(1);
  for (nInf = 0; nInf < ny; nInf++) {
    x[nInf] = y[nInf];
  }

  iFinite.set_size(Yin.size(0));
  iInfinite.set_size(Yin.size(0));
  ny = Yin.size(0);
  nPk = 0;
  nInf = 0;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 1; k <= ny; k++) {
    boolean_T isinfyk;
    yk = Yin[k - 1];
    if (rtIsNaN(yk)) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(yk) && (yk > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite[nInf - 1] = k;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      char previousdir;
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (('d' != previousdir) && (previousdir == 'i')) {
          nPk++;
          iFinite[nPk - 1] = kfirst;
        }
      } else {
        dir = 'i';
      }

      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }

  if (1 > nPk) {
    nPk = 0;
  }

  iFinite.set_size(nPk);
  if (1 > nInf) {
    nInf = 0;
  }

  iInfinite.set_size(nInf);
  iPk.set_size(iFinite.size(0));
  nPk = 0;
  nInf = iFinite.size(0);
  for (k = 0; k < nInf; k++) {
    ykfirst = Yin[iFinite[k] - 1];
    if (ykfirst > rtMinusInf) {
      yk = Yin[iFinite[k] - 2];
      if ((!(yk > Yin[iFinite[k]])) && (!rtIsNaN(Yin[iFinite[k]]))) {
        yk = Yin[iFinite[k]];
      }

      if (ykfirst - yk >= 0.0) {
        nPk++;
        iPk[nPk - 1] = iFinite[k];
      }
    }
  }

  if (1 > nPk) {
    nPk = 0;
  }

  iPk.set_size(nPk);
  do_vectors(iPk, iInfinite, c, idx, iFinite);
  if (c.size(0) < 1) {
    nInf = 0;
  } else {
    nInf = c.size(0);
  }

  b_y.set_size(1, nInf);
  if (nInf > 0) {
    b_y[0] = 1;
    ny = 1;
    for (k = 2; k <= nInf; k++) {
      ny++;
      b_y[k - 1] = ny;
    }
  }

  idx.set_size(b_y.size(1));
  ny = b_y.size(1);
  for (nInf = 0; nInf < ny; nInf++) {
    idx[nInf] = b_y[nInf];
  }

  if (idx.size(0) > Yin.size(0)) {
    idx.set_size(Yin.size(0));
  }

  iPk.set_size(idx.size(0));
  ny = idx.size(0);
  for (nInf = 0; nInf < ny; nInf++) {
    iPk[nInf] = c[idx[nInf] - 1];
  }

  Ypk.set_size(iPk.size(0));
  ny = iPk.size(0);
  for (nInf = 0; nInf < ny; nInf++) {
    Ypk[nInf] = Yin[iPk[nInf] - 1];
  }

  Xpk.set_size(iPk.size(0));
  ny = iPk.size(0);
  for (nInf = 0; nInf < ny; nInf++) {
    Xpk[nInf] = x[iPk[nInf] - 1];
  }
}

// End of code generation (findpeaks.cpp)
