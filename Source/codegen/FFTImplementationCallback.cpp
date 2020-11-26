//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  FFTImplementationCallback.cpp
//
//  Code generation for function 'FFTImplementationCallback'
//


// Include files
#include "FFTImplementationCallback.h"
#include "additive.h"
#include "findpeaks.h"
#include "getMagnitudes.h"
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>
#include <cstring>

// Function Definitions
void FFTImplementationCallback::b_r2br_r2dit_trig(const creal_T x[512], const
  double costab[257], const double sintab[257], creal_T y[512])
{
  int ix;
  int iy;
  int ju;
  int i;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  int j;
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i < 511; i++) {
    boolean_T tst;
    y[iy] = x[ix];
    iy = 512;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 510; i += 2) {
    double re;
    double im;
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 128;
  iheight = 509;
  while (ju > 0) {
    int istart;
    int temp_re_tmp;
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 256; j += ju) {
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  for (iy = 0; iy < 512; iy++) {
    y[iy].re *= 0.001953125;
    y[iy].im *= 0.001953125;
  }
}

void FFTImplementationCallback::doHalfLengthBluestein(const double x_data[],
  const int x_size[1], coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int
  nfft, const coder::array<creal_T, 1U> &wwc, const coder::array<double, 2U>
  &costab, const coder::array<double, 2U> &sintab, const coder::array<double, 2U>
  &costabinv, const coder::array<double, 2U> &sintabinv)
{
  int hnRows;
  coder::array<creal_T, 1U> ytmp;
  int ju;
  boolean_T tst;
  int ihi;
  int nd2;
  double twid_re;
  int j;
  coder::array<double, 2U> costab1q;
  int k;
  coder::array<double, 2U> b_costab;
  coder::array<double, 2U> b_sintab;
  coder::array<double, 2U> hsintab;
  coder::array<double, 2U> hcostabinv;
  coder::array<double, 2U> hsintabinv;
  int i;
  coder::array<creal_T, 1U> reconVar1;
  int iDelta2;
  coder::array<creal_T, 1U> reconVar2;
  coder::array<int, 2U> wrapIndex;
  int ix;
  int temp_re_tmp;
  double twid_im;
  int loop_ub_tmp;
  coder::array<creal_T, 1U> fy;
  int nRowsD2;
  double temp_re;
  double temp_im;
  coder::array<creal_T, 1U> fv;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (ju = 0; ju < hnRows; ju++) {
      ytmp[ju].re = 0.0;
      ytmp[ju].im = 0.0;
    }
  }

  if ((x_size[0] & 1) == 0) {
    tst = true;
    ihi = x_size[0];
  } else if (x_size[0] >= nRows) {
    tst = true;
    ihi = nRows;
  } else {
    tst = false;
    ihi = x_size[0] - 1;
  }

  if (ihi >= nRows) {
    ihi = nRows;
  }

  nd2 = nRows << 1;
  twid_re = 6.2831853071795862 / static_cast<double>(nd2);
  j = nd2 / 2 / 2;
  costab1q.set_size(1, (j + 1));
  costab1q[0] = 1.0;
  nd2 = j / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(twid_re * (static_cast<double>(k) + 1.0));
  }

  ju = nd2 + 2;
  nd2 = j - 1;
  for (k = ju; k <= nd2; k++) {
    costab1q[k] = std::sin(twid_re * static_cast<double>(j - k));
  }

  costab1q[j] = 0.0;
  j = costab1q.size(1) - 1;
  nd2 = (costab1q.size(1) - 1) << 1;
  b_costab.set_size(1, (nd2 + 1));
  b_sintab.set_size(1, (nd2 + 1));
  b_costab[0] = 1.0;
  b_sintab[0] = 0.0;
  for (k = 0; k < j; k++) {
    b_costab[k + 1] = costab1q[k + 1];
    b_sintab[k + 1] = -costab1q[(j - k) - 1];
  }

  ju = costab1q.size(1);
  for (k = ju; k <= nd2; k++) {
    b_costab[k] = -costab1q[nd2 - k];
    b_sintab[k] = -costab1q[k - j];
  }

  nd2 = costab.size(1) / 2;
  costab1q.set_size(1, nd2);
  hsintab.set_size(1, nd2);
  hcostabinv.set_size(1, nd2);
  hsintabinv.set_size(1, nd2);
  for (i = 0; i < nd2; i++) {
    iDelta2 = ((i + 1) << 1) - 2;
    costab1q[i] = costab[iDelta2];
    hsintab[i] = sintab[iDelta2];
    hcostabinv[i] = costabinv[iDelta2];
    hsintabinv[i] = sintabinv[iDelta2];
  }

  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  nd2 = 0;
  wrapIndex.set_size(1, hnRows);
  for (i = 0; i < hnRows; i++) {
    reconVar1[i].re = b_sintab[nd2] + 1.0;
    reconVar1[i].im = -b_costab[nd2];
    reconVar2[i].re = 1.0 - b_sintab[nd2];
    reconVar2[i].im = b_costab[nd2];
    nd2 += 2;
    if (i + 1 != 1) {
      wrapIndex[i] = (hnRows - i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }

  nd2 = 0;
  ju = static_cast<int>(static_cast<double>(ihi) / 2.0);
  for (ix = 0; ix < ju; ix++) {
    temp_re_tmp = (hnRows + ix) - 1;
    twid_im = x_data[nd2 + 1];
    ytmp[ix].re = wwc[temp_re_tmp].re * x_data[nd2] + wwc[temp_re_tmp].im *
      twid_im;
    ytmp[ix].im = wwc[temp_re_tmp].re * twid_im - wwc[temp_re_tmp].im *
      x_data[nd2];
    nd2 += 2;
  }

  if (!tst) {
    temp_re_tmp = (hnRows + ju) - 1;
    ytmp[ju].re = wwc[temp_re_tmp].re * x_data[nd2] + wwc[temp_re_tmp].im * 0.0;
    ytmp[ju].im = wwc[temp_re_tmp].re * 0.0 - wwc[temp_re_tmp].im * x_data[nd2];
    if (ju + 2 <= hnRows) {
      ju = static_cast<int>(static_cast<double>(ihi) / 2.0) + 2;
      for (i = ju; i <= hnRows; i++) {
        ytmp[i - 1].re = 0.0;
        ytmp[i - 1].im = 0.0;
      }
    }
  } else {
    if (ju + 1 <= hnRows) {
      ju = static_cast<int>(static_cast<double>(ihi) / 2.0) + 1;
      for (i = ju; i <= hnRows; i++) {
        ytmp[i - 1].re = 0.0;
        ytmp[i - 1].im = 0.0;
      }
    }
  }

  loop_ub_tmp = static_cast<int>(static_cast<double>(nfft) / 2.0);
  fy.set_size(loop_ub_tmp);
  if (loop_ub_tmp > ytmp.size(0)) {
    fy.set_size(loop_ub_tmp);
    for (ju = 0; ju < loop_ub_tmp; ju++) {
      fy[ju].re = 0.0;
      fy[ju].im = 0.0;
    }
  }

  ihi = ytmp.size(0);
  if (ihi >= loop_ub_tmp) {
    ihi = loop_ub_tmp;
  }

  iDelta2 = loop_ub_tmp - 2;
  nRowsD2 = loop_ub_tmp / 2;
  k = nRowsD2 / 2;
  ix = 0;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= ihi - 2; i++) {
    fy[nd2] = ytmp[ix];
    j = loop_ub_tmp;
    tst = true;
    while (tst) {
      j >>= 1;
      ju ^= j;
      tst = ((ju & j) == 0);
    }

    nd2 = ju;
    ix++;
  }

  fy[nd2] = ytmp[ix];
  if (loop_ub_tmp > 1) {
    for (i = 0; i <= iDelta2; i += 2) {
      temp_re = fy[i + 1].re;
      temp_im = fy[i + 1].im;
      twid_re = fy[i].re;
      twid_im = fy[i].im;
      fy[i + 1].re = fy[i].re - fy[i + 1].re;
      fy[i + 1].im = fy[i].im - fy[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      fy[i].re = twid_re;
      fy[i].im = twid_im;
    }
  }

  nd2 = 2;
  iDelta2 = 4;
  ix = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ix; i += iDelta2) {
      temp_re_tmp = i + nd2;
      temp_re = fy[temp_re_tmp].re;
      temp_im = fy[temp_re_tmp].im;
      fy[temp_re_tmp].re = fy[i].re - fy[temp_re_tmp].re;
      fy[temp_re_tmp].im = fy[i].im - fy[temp_re_tmp].im;
      fy[i].re = fy[i].re + temp_re;
      fy[i].im = fy[i].im + temp_im;
    }

    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab1q[j];
      twid_im = hsintab[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re_tmp = i + nd2;
        temp_re = twid_re * fy[temp_re_tmp].re - twid_im * fy[temp_re_tmp].im;
        temp_im = twid_re * fy[temp_re_tmp].im + twid_im * fy[temp_re_tmp].re;
        fy[temp_re_tmp].re = fy[i].re - temp_re;
        fy[temp_re_tmp].im = fy[i].im - temp_im;
        fy[i].re = fy[i].re + temp_re;
        fy[i].im = fy[i].im + temp_im;
        i += iDelta2;
      }

      ju++;
    }

    k /= 2;
    nd2 = iDelta2;
    iDelta2 += iDelta2;
    ix -= nd2;
  }

  FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (loop_ub_tmp),
    (costab1q), (hsintab), (fv));
  nd2 = fy.size(0);
  for (ju = 0; ju < nd2; ju++) {
    twid_im = fy[ju].re * fv[ju].im + fy[ju].im * fv[ju].re;
    fy[ju].re = fy[ju].re * fv[ju].re - fy[ju].im * fv[ju].im;
    fy[ju].im = twid_im;
  }

  FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (loop_ub_tmp),
    (hcostabinv), (hsintabinv), (fv));
  if (fv.size(0) > 1) {
    twid_re = 1.0 / static_cast<double>(fv.size(0));
    nd2 = fv.size(0);
    for (ju = 0; ju < nd2; ju++) {
      fv[ju].re = twid_re * fv[ju].re;
      fv[ju].im = twid_re * fv[ju].im;
    }
  }

  nd2 = 0;
  ju = wwc.size(0);
  for (k = hnRows; k <= ju; k++) {
    ytmp[nd2].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
    ytmp[nd2].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
    nd2++;
  }

  for (i = 0; i < hnRows; i++) {
    ju = wrapIndex[i];
    twid_re = ytmp[ju - 1].re;
    twid_im = -ytmp[ju - 1].im;
    y[i].re = 0.5 * ((ytmp[i].re * reconVar1[i].re - ytmp[i].im * reconVar1[i].
                      im) + (twid_re * reconVar2[i].re - twid_im * reconVar2[i].
      im));
    y[i].im = 0.5 * ((ytmp[i].re * reconVar1[i].im + ytmp[i].im * reconVar1[i].
                      re) + (twid_re * reconVar2[i].im + twid_im * reconVar2[i].
      re));
    twid_re = ytmp[ju - 1].re;
    twid_im = -ytmp[ju - 1].im;
    ju = hnRows + i;
    y[ju].re = 0.5 * ((ytmp[i].re * reconVar2[i].re - ytmp[i].im * reconVar2[i].
                       im) + (twid_re * reconVar1[i].re - twid_im * reconVar1[i]
      .im));
    y[ju].im = 0.5 * ((ytmp[i].re * reconVar2[i].im + ytmp[i].im * reconVar2[i].
                       re) + (twid_re * reconVar1[i].im + twid_im * reconVar1[i]
      .re));
  }
}

void FFTImplementationCallback::r2br_r2dit_trig(const creal_T x[261], const
  double costab[257], const double sintab[257], creal_T y[512])
{
  int ix;
  int iy;
  int ju;
  int i;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  int j;
  std::memset(&y[0], 0, 512U * sizeof(creal_T));
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i < 260; i++) {
    boolean_T tst;
    y[iy] = x[ix];
    iy = 512;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 510; i += 2) {
    double re;
    double im;
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 128;
  iheight = 509;
  while (ju > 0) {
    int istart;
    int temp_re_tmp;
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 256; j += ju) {
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

void FFTImplementationCallback::r2br_r2dit_trig_impl(const creal_T x[131], const
  double costab[257], const double sintab[257], creal_T y[512])
{
  int ix;
  int iy;
  int ju;
  int i;
  double twid_re;
  double temp_re;
  double twid_im;
  int iheight;
  double temp_im;
  int j;
  std::memset(&y[0], 0, 512U * sizeof(creal_T));
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i < 130; i++) {
    boolean_T tst;
    y[iy] = x[ix];
    iy = 512;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 510; i += 2) {
    double re;
    double im;
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 128;
  iheight = 509;
  while (ju > 0) {
    int istart;
    int temp_re_tmp;
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 256; j += ju) {
      int ihi;
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

void FFTImplementationCallback::r2br_r2dit_trig_impl(const coder::array<creal_T,
  1U> &x, int unsigned_nRows, const coder::array<double, 2U> &costab, const
  coder::array<double, 2U> &sintab, coder::array<creal_T, 1U> &y)
{
  int iDelta2;
  int iy;
  int iheight;
  int nRowsD2;
  int k;
  int ix;
  int ju;
  int i;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  y.set_size(unsigned_nRows);
  if (unsigned_nRows > x.size(0)) {
    y.set_size(unsigned_nRows);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y[iy].re = 0.0;
      y[iy].im = 0.0;
    }
  }

  iDelta2 = x.size(0);
  if (iDelta2 >= unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }

  iheight = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    boolean_T tst;
    y[iy] = x[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      twid_re = y[i].re;
      twid_im = y[i].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y[i].re = twid_re;
      y[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int temp_re_tmp;
    for (i = 0; i < iheight; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }

    ix = 1;
    for (ju = k; ju < nRowsD2; ju += k) {
      int ihi;
      twid_re = costab[ju];
      twid_im = sintab[ju];
      i = ix;
      ihi = ix + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += iDelta2;
      }

      ix++;
    }

    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

void FFTImplementationCallback::doHalfLengthRadix2(const double x_data[], const
  int x_size[1], coder::array<creal_T, 1U> &y, int unsigned_nRows, const coder::
  array<double, 2U> &costab, const coder::array<double, 2U> &sintab)
{
  int nRows;
  int j;
  int ihi;
  int nRowsD2;
  int k;
  int hszCostab;
  coder::array<double, 2U> hcostab;
  coder::array<double, 2U> hsintab;
  int i;
  coder::array<creal_T, 1U> reconVar1;
  int ju;
  coder::array<creal_T, 1U> reconVar2;
  coder::array<int, 2U> wrapIndex;
  double temp_re;
  double temp_im;
  int loop_ub;
  coder::array<int, 1U> bitrevIndex;
  int iheight;
  boolean_T tst;
  double y_im;
  double y_re;
  double b_y_im;
  double temp2_re;
  double temp2_im;
  nRows = unsigned_nRows / 2;
  j = y.size(0);
  if (j >= nRows) {
    j = nRows;
  }

  ihi = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  for (i = 0; i < hszCostab; i++) {
    ju = ((i + 1) << 1) - 2;
    hcostab[i] = costab[ju];
    hsintab[i] = sintab[ju];
  }

  reconVar1.set_size(nRows);
  reconVar2.set_size(nRows);
  wrapIndex.set_size(1, nRows);
  for (i = 0; i < nRows; i++) {
    temp_re = sintab[i];
    temp_im = costab[i];
    reconVar1[i].re = temp_re + 1.0;
    reconVar1[i].im = -temp_im;
    reconVar2[i].re = 1.0 - temp_re;
    reconVar2[i].im = temp_im;
    if (i + 1 != 1) {
      wrapIndex[i] = (nRows - i) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }

  ju = 0;
  hszCostab = 1;
  loop_ub = static_cast<int>(static_cast<double>(unsigned_nRows) / 2.0);
  bitrevIndex.set_size(loop_ub);
  for (iheight = 0; iheight < loop_ub; iheight++) {
    bitrevIndex[iheight] = 0;
  }

  for (iheight = 0; iheight <= j - 2; iheight++) {
    bitrevIndex[iheight] = hszCostab;
    hszCostab = loop_ub;
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }

    hszCostab = ju + 1;
  }

  bitrevIndex[j - 1] = hszCostab;
  if ((x_size[0] & 1) == 0) {
    tst = true;
    j = x_size[0];
  } else if (x_size[0] >= unsigned_nRows) {
    tst = true;
    j = unsigned_nRows;
  } else {
    tst = false;
    j = x_size[0] - 1;
  }

  hszCostab = 0;
  if (j >= unsigned_nRows) {
    j = unsigned_nRows;
  }

  temp_re = static_cast<double>(j) / 2.0;
  iheight = static_cast<int>(temp_re);
  for (i = 0; i < iheight; i++) {
    y[bitrevIndex[i] - 1].re = x_data[hszCostab];
    y[bitrevIndex[i] - 1].im = x_data[hszCostab + 1];
    hszCostab += 2;
  }

  if (!tst) {
    iheight = bitrevIndex[static_cast<int>(temp_re)] - 1;
    y[iheight].re = x_data[hszCostab];
    y[iheight].im = 0.0;
  }

  if (nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
  }

  hszCostab = 2;
  ju = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    int temp_re_tmp;
    for (i = 0; i < iheight; i += ju) {
      temp_re_tmp = i + hszCostab;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - temp_re;
      y[temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }

    nRows = 1;
    for (j = k; j < nRowsD2; j += k) {
      temp2_re = hcostab[j];
      temp2_im = hsintab[j];
      i = nRows;
      ihi = nRows + iheight;
      while (i < ihi) {
        temp_re_tmp = i + hszCostab;
        temp_re = temp2_re * y[temp_re_tmp].re - temp2_im * y[temp_re_tmp].im;
        temp_im = temp2_re * y[temp_re_tmp].im + temp2_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += ju;
      }

      nRows++;
    }

    k /= 2;
    hszCostab = ju;
    ju += ju;
    iheight -= hszCostab;
  }

  hszCostab = loop_ub / 2;
  temp_re = y[0].re;
  temp_im = y[0].im;
  y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
  y_re = y[0].re;
  b_y_im = -y[0].im;
  y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im) +
                   (y_re * reconVar2[0].re - b_y_im * reconVar2[0].im));
  y[0].im = 0.5 * (y_im + (y_re * reconVar2[0].im + b_y_im * reconVar2[0].re));
  y[loop_ub].re = 0.5 * ((temp_re * reconVar2[0].re - temp_im * reconVar2[0].im)
    + (temp_re * reconVar1[0].re - -temp_im * reconVar1[0].im));
  y[loop_ub].im = 0.5 * ((temp_re * reconVar2[0].im + temp_im * reconVar2[0].re)
    + (temp_re * reconVar1[0].im + -temp_im * reconVar1[0].re));
  for (i = 2; i <= hszCostab; i++) {
    temp_re = y[i - 1].re;
    temp_im = y[i - 1].im;
    iheight = wrapIndex[i - 1];
    temp2_re = y[iheight - 1].re;
    temp2_im = y[iheight - 1].im;
    y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i - 1].re;
    y_re = y[iheight - 1].re;
    b_y_im = -y[iheight - 1].im;
    y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                          reconVar1[i - 1].im) + (y_re * reconVar2[i - 1].re -
      b_y_im * reconVar2[i - 1].im));
    y[i - 1].im = 0.5 * (y_im + (y_re * reconVar2[i - 1].im + b_y_im *
      reconVar2[i - 1].re));
    ju = (loop_ub + i) - 1;
    y[ju].re = 0.5 * ((temp_re * reconVar2[i - 1].re - temp_im * reconVar2[i - 1]
                       .im) + (temp2_re * reconVar1[i - 1].re - -temp2_im *
      reconVar1[i - 1].im));
    y[ju].im = 0.5 * ((temp_re * reconVar2[i - 1].im + temp_im * reconVar2[i - 1]
                       .re) + (temp2_re * reconVar1[i - 1].im + -temp2_im *
      reconVar1[i - 1].re));
    y[iheight - 1].re = 0.5 * ((temp2_re * reconVar1[iheight - 1].re - temp2_im *
      reconVar1[iheight - 1].im) + (temp_re * reconVar2[iheight - 1].re -
      -temp_im * reconVar2[iheight - 1].im));
    y[iheight - 1].im = 0.5 * ((temp2_re * reconVar1[iheight - 1].im + temp2_im *
      reconVar1[iheight - 1].re) + (temp_re * reconVar2[iheight - 1].im +
      -temp_im * reconVar2[iheight - 1].re));
    ju = (iheight + loop_ub) - 1;
    y[ju].re = 0.5 * ((temp2_re * reconVar2[iheight - 1].re - temp2_im *
                       reconVar2[iheight - 1].im) + (temp_re * reconVar1[iheight
      - 1].re - -temp_im * reconVar1[iheight - 1].im));
    y[ju].im = 0.5 * ((temp2_re * reconVar2[iheight - 1].im + temp2_im *
                       reconVar2[iheight - 1].re) + (temp_re * reconVar1[iheight
      - 1].im + -temp_im * reconVar1[iheight - 1].re));
  }

  if (hszCostab != 0) {
    temp_re = y[hszCostab].re;
    temp_im = y[hszCostab].im;
    y_im = y[hszCostab].re * reconVar1[hszCostab].im + y[hszCostab].im *
      reconVar1[hszCostab].re;
    y_re = y[hszCostab].re;
    b_y_im = -y[hszCostab].im;
    y[hszCostab].re = 0.5 * ((y[hszCostab].re * reconVar1[hszCostab].re -
      y[hszCostab].im * reconVar1[hszCostab].im) + (y_re * reconVar2[hszCostab].
      re - b_y_im * reconVar2[hszCostab].im));
    y[hszCostab].im = 0.5 * (y_im + (y_re * reconVar2[hszCostab].im + b_y_im *
      reconVar2[hszCostab].re));
    iheight = loop_ub + hszCostab;
    y[iheight].re = 0.5 * ((temp_re * reconVar2[hszCostab].re - temp_im *
      reconVar2[hszCostab].im) + (temp_re * reconVar1[hszCostab].re - -temp_im *
      reconVar1[hszCostab].im));
    y[iheight].im = 0.5 * ((temp_re * reconVar2[hszCostab].im + temp_im *
      reconVar2[hszCostab].re) + (temp_re * reconVar1[hszCostab].im + -temp_im *
      reconVar1[hszCostab].re));
  }
}

void FFTImplementationCallback::dobluesteinfft(const double x_data[], const int
  x_size[1], const double costab[257], const double sintab[257], const double
  sintabinv[257], creal_T y[131])
{
  int minNrowsNx;
  int xidx;
  int k;
  static const creal_T wwc[261] = { { -0.99971245465315683,// re
      -0.023979324664381876            // im
    }, { -0.99540258098282641,         // re
      -0.095779443372404877            // im
    }, { -0.97679799210758655,         // re
      -0.21416274796188808             // im
    }, { -0.9272836402518978,          // re
      -0.3743595204094442              // im
    }, { -0.82559493429568642,         // re
      -0.5642632403987532              // im
    }, { -0.64990382581691786,         // re
      -0.76001645849845467             // im
    }, { -0.38545122514572494,         // re
      -0.922728211898639               // im
    }, { -0.035964677315181923,        // re
      -0.99935306172824367             // im
    }, { 0.36321399106939722,          // re
      -0.93170574576495979             // im
    }, { 0.73615119338287982,          // re
      -0.67681712484316014             // im
    }, { 0.971381640325756,            // re
      -0.2375241226445087              // im
    }, { 0.9517948536518398,           // re
      0.30673532004298554              // im
    }, { 0.61271754403145939,          // re
      0.79030197471349939              // im
    }, { 0.011990524318043143,         // re
      0.9999281110792807               // im
    }, { -0.63149226758730082,         // re
      0.77538217414217669              // im
    }, { -0.9896657201539989,          // re
      0.14339373191345106              // im
    }, { -0.79759196536929566,         // re
      -0.60319736138211366             // im
    }, { -0.083837159038076842,        // re
      -0.99647946831052381             // im
    }, { 0.71970989895762216,          // re
      -0.69427491769644778             // im
    }, { 0.98594266152884857,          // re
      0.16708401532585454              // im
    }, { 0.40746678980960094,          // re
      0.91322002562485372              // im
    }, { -0.57412199225992522,         // re
      0.81876977106112947              // im
    }, { -0.99281963123362849,         // re
      -0.1196209841002909              // im
    }, { -0.31812578851038181,         // re
      -0.94804851283288649             // im
    }, { 0.75216913410767694,          // re
      -0.65897010076004781             // im
    }, { 0.87584414752517514,          // re
      0.48259406258873427              // im
    }, { -0.20243503195489745,         // re
      0.97929569479162915              // im
    }, { -0.99884998397728031,         // re
      0.047944859042308309             // im
    }, { -0.24915442247211414,         // re
      -0.96846376997933548             // im
    }, { 0.91804011567483912,          // re
      -0.3964875105368742              // im
    }, { 0.49306119997214554,          // re
      0.869994628191478                // im
    }, { -0.83888818975165,            // re
      0.54430378015883707              // im
    }, { -0.55432335998687454,         // re
      -0.83230139527268721             // im
    }, { 0.85169900841664392,          // re
      -0.52403129588041364             // im
    }, { 0.45078240187579044,          // re
      0.8926338701612736               // im
    }, { -0.94416586364517918,         // re
      0.32947051753859985              // im
    }, { -0.15525003437706544,         // re
      -0.98787520812394114             // im
    }, { 0.99741308397122974,          // re
      0.0718828207779892               // im
    }, { -0.34076787600698871,         // re
      0.94014746432763707              // im
    }, { -0.78289835614569425,         // re
      -0.62214963147491265             // im
    }, { 0.86402002290807578,          // re
      -0.50345744608052845             // im
    }, { 0.10770795674511113,          // re
      0.9941825768206729               // im
    }, { -0.93599389263703991,         // re
      -0.35201623960573375             // im
    }, { 0.7677545093633712,           // re
      -0.64074410910457                // im
    }, { 0.13151681260858591,          // re
      0.9913139401830674               // im
    }, { -0.88716458232391282,         // re
      -0.46145314374271768             // im
    }, { 0.90826863477082542,          // re
      -0.41838748438683127             // im
    }, { -0.27230588644331188,         // re
      0.96221073794066658              // im
    }, { -0.513781306164056,           // re
      -0.85792119069082129             // im
    }, { 0.96540665600255637,          // re
      0.26074889941467028              // im
    }, { -0.89797481702758764,         // re
      0.44004684748816292              // im
    }, { 0.42924802411467106,          // re
      -0.90318665501304363             // im
    }, { 0.1788939732955811,           // re
      0.98386835822609919              // im
    }, { -0.68559530797654489,         // re
      -0.7279828800738013              // im
    }, { 0.95887647529586684,          // re
      0.28382372191938954              // im
    }, { -0.9816525964545445,          // re
      0.19067821027598092              // im
    }, { 0.81182688687625426,          // re
      -0.58389819810032761             // im
    }, { -0.53420594150820178,         // re
      0.845354370697482                // im
    }, { 0.22585967211126023,          // re
      -0.97415984751671736             // im
    }, { 0.059918147361093958,         // re
      0.9982032937316998               // im
    }, { -0.29530074983338095,         // re
      -0.9554043474612427              // im
    }, { 0.47205753887271307,          // re
      0.88156773987790471              // im
    }, { -0.593590452318187,           // re
      -0.80476727997396258             // im
    }, { 0.667941630404517,            // re
      0.74421366446240123              // im
    }, { -0.70285470606732026,         // re
      -0.711333439505708               // im
    }, { 0.70285470606731981,          // re
      0.7113334395057086               // im
    }, { -0.66794163040451682,         // re
      -0.74421366446240145             // im
    }, { 0.593590452318187,            // re
      0.80476727997396258              // im
    }, { -0.47205753887271334,         // re
      -0.88156773987790449             // im
    }, { 0.29530074983338062,          // re
      0.95540434746124281              // im
    }, { -0.059918147361094527,        // re
      -0.9982032937316998              // im
    }, { -0.22585967211126057,         // re
      0.97415984751671725              // im
    }, { 0.53420594150820211,          // re
      -0.84535437069748176             // im
    }, { -0.81182688687625437,         // re
      0.5838981981003275               // im
    }, { 0.9816525964545445,           // re
      -0.19067821027598103             // im
    }, { -0.95887647529586673,         // re
      -0.28382372191938965             // im
    }, { 0.68559530797654455,          // re
      0.72798288007380163              // im
    }, { -0.17889397329558054,         // re
      -0.9838683582260993              // im
    }, { -0.42924802411467156,         // re
      0.9031866550130434               // im
    }, { 0.89797481702758775,          // re
      -0.44004684748816264             // im
    }, { -0.96540665600255637,         // re
      -0.26074889941467017             // im
    }, { 0.51378130616405615,          // re
      0.85792119069082118              // im
    }, { 0.27230588644331194,          // re
      -0.96221073794066658             // im
    }, { -0.90826863477082542,         // re
      0.41838748438683115              // im
    }, { 0.88716458232391282,          // re
      0.46145314374271779              // im
    }, { -0.13151681260858558,         // re
      -0.9913139401830674              // im
    }, { -0.767754509363371,           // re
      0.64074410910457025              // im
    }, { 0.93599389263703991,          // re
      0.35201623960573381              // im
    }, { -0.10770795674511124,         // re
      -0.9941825768206729              // im
    }, { -0.864020022908076,           // re
      0.503457446080528                // im
    }, { 0.78289835614569425,          // re
      0.62214963147491265              // im
    }, { 0.34076787600698921,          // re
      -0.94014746432763685             // im
    }, { -0.99741308397122985,         // re
      -0.071882820777988923            // im
    }, { 0.15525003437706575,          // re
      0.987875208123941                // im
    }, { 0.94416586364517918,          // re
      -0.32947051753859996             // im
    }, { -0.45078240187579016,         // re
      -0.89263387016127371             // im
    }, { -0.85169900841664414,         // re
      0.52403129588041308              // im
    }, { 0.55432335998687432,          // re
      0.83230139527268732              // im
    }, { 0.83888818975164969,          // re
      -0.54430378015883751             // im
    }, { -0.49306119997214559,         // re
      -0.86999462819147788             // im
    }, { -0.91804011567483923,         // re
      0.39648751053687409              // im
    }, { 0.24915442247211336,          // re
      0.9684637699793357               // im
    }, { 0.99884998397728031,          // re
      -0.047944859042308878            // im
    }, { 0.20243503195489732,          // re
      -0.97929569479162915             // im
    }, { -0.87584414752517536,         // re
      -0.48259406258873383             // im
    }, { -0.752169134107677,           // re
      0.65897010076004769              // im
    }, { 0.3181257885103817,           // re
      0.9480485128328866               // im
    }, { 0.99281963123362849,          // re
      0.11962098410029071              // im
    }, { 0.57412199225992511,          // re
      -0.81876977106112958             // im
    }, { -0.40746678980960105,         // re
      -0.91322002562485372             // im
    }, { -0.98594266152884857,         // re
      -0.16708401532585435             // im
    }, { -0.71970989895762216,         // re
      0.69427491769644767              // im
    }, { 0.0838371590380765,           // re
      0.99647946831052381              // im
    }, { 0.79759196536929589,          // re
      0.60319736138211344              // im
    }, { 0.989665720153999,            // re
      -0.14339373191345073             // im
    }, { 0.63149226758730037,          // re
      -0.775382174142177               // im
    }, { -0.011990524318043044,        // re
      -0.9999281110792807              // im
    }, { -0.61271754403145917,         // re
      -0.7903019747134995              // im
    }, { -0.95179485365183991,         // re
      -0.30673532004298543             // im
    }, { -0.971381640325756,           // re
      0.23752412264450856              // im
    }, { -0.73615119338287993,         // re
      0.67681712484316014              // im
    }, { -0.36321399106939695,         // re
      0.9317057457649599               // im
    }, { 0.035964677315181139,         // re
      0.99935306172824367              // im
    }, { 0.38545122514572466,          // re
      0.92272821189863918              // im
    }, { 0.64990382581691819,          // re
      0.76001645849845434              // im
    }, { 0.82559493429568631,          // re
      0.56426324039875353              // im
    }, { 0.9272836402518978,           // re
      0.37435952040944404              // im
    }, { 0.97679799210758655,          // re
      0.21416274796188825              // im
    }, { 0.99540258098282641,          // re
      0.095779443372404918             // im
    }, { 0.99971245465315683,          // re
      0.023979324664381761             // im
    }, { 1.0,                          // re
      0.0                              // im
    }, { 0.99971245465315683,          // re
      0.023979324664381761             // im
    }, { 0.99540258098282641,          // re
      0.095779443372404918             // im
    }, { 0.97679799210758655,          // re
      0.21416274796188825              // im
    }, { 0.9272836402518978,           // re
      0.37435952040944404              // im
    }, { 0.82559493429568631,          // re
      0.56426324039875353              // im
    }, { 0.64990382581691819,          // re
      0.76001645849845434              // im
    }, { 0.38545122514572466,          // re
      0.92272821189863918              // im
    }, { 0.035964677315181139,         // re
      0.99935306172824367              // im
    }, { -0.36321399106939695,         // re
      0.9317057457649599               // im
    }, { -0.73615119338287993,         // re
      0.67681712484316014              // im
    }, { -0.971381640325756,           // re
      0.23752412264450856              // im
    }, { -0.95179485365183991,         // re
      -0.30673532004298543             // im
    }, { -0.61271754403145917,         // re
      -0.7903019747134995              // im
    }, { -0.011990524318043044,        // re
      -0.9999281110792807              // im
    }, { 0.63149226758730037,          // re
      -0.775382174142177               // im
    }, { 0.989665720153999,            // re
      -0.14339373191345073             // im
    }, { 0.79759196536929589,          // re
      0.60319736138211344              // im
    }, { 0.0838371590380765,           // re
      0.99647946831052381              // im
    }, { -0.71970989895762216,         // re
      0.69427491769644767              // im
    }, { -0.98594266152884857,         // re
      -0.16708401532585435             // im
    }, { -0.40746678980960105,         // re
      -0.91322002562485372             // im
    }, { 0.57412199225992511,          // re
      -0.81876977106112958             // im
    }, { 0.99281963123362849,          // re
      0.11962098410029071              // im
    }, { 0.3181257885103817,           // re
      0.9480485128328866               // im
    }, { -0.752169134107677,           // re
      0.65897010076004769              // im
    }, { -0.87584414752517536,         // re
      -0.48259406258873383             // im
    }, { 0.20243503195489732,          // re
      -0.97929569479162915             // im
    }, { 0.99884998397728031,          // re
      -0.047944859042308878            // im
    }, { 0.24915442247211336,          // re
      0.9684637699793357               // im
    }, { -0.91804011567483923,         // re
      0.39648751053687409              // im
    }, { -0.49306119997214559,         // re
      -0.86999462819147788             // im
    }, { 0.83888818975164969,          // re
      -0.54430378015883751             // im
    }, { 0.55432335998687432,          // re
      0.83230139527268732              // im
    }, { -0.85169900841664414,         // re
      0.52403129588041308              // im
    }, { -0.45078240187579016,         // re
      -0.89263387016127371             // im
    }, { 0.94416586364517918,          // re
      -0.32947051753859996             // im
    }, { 0.15525003437706575,          // re
      0.987875208123941                // im
    }, { -0.99741308397122985,         // re
      -0.071882820777988923            // im
    }, { 0.34076787600698921,          // re
      -0.94014746432763685             // im
    }, { 0.78289835614569425,          // re
      0.62214963147491265              // im
    }, { -0.864020022908076,           // re
      0.503457446080528                // im
    }, { -0.10770795674511124,         // re
      -0.9941825768206729              // im
    }, { 0.93599389263703991,          // re
      0.35201623960573381              // im
    }, { -0.767754509363371,           // re
      0.64074410910457025              // im
    }, { -0.13151681260858558,         // re
      -0.9913139401830674              // im
    }, { 0.88716458232391282,          // re
      0.46145314374271779              // im
    }, { -0.90826863477082542,         // re
      0.41838748438683115              // im
    }, { 0.27230588644331194,          // re
      -0.96221073794066658             // im
    }, { 0.51378130616405615,          // re
      0.85792119069082118              // im
    }, { -0.96540665600255637,         // re
      -0.26074889941467017             // im
    }, { 0.89797481702758775,          // re
      -0.44004684748816264             // im
    }, { -0.42924802411467156,         // re
      0.9031866550130434               // im
    }, { -0.17889397329558054,         // re
      -0.9838683582260993              // im
    }, { 0.68559530797654455,          // re
      0.72798288007380163              // im
    }, { -0.95887647529586673,         // re
      -0.28382372191938965             // im
    }, { 0.9816525964545445,           // re
      -0.19067821027598103             // im
    }, { -0.81182688687625437,         // re
      0.5838981981003275               // im
    }, { 0.53420594150820211,          // re
      -0.84535437069748176             // im
    }, { -0.22585967211126057,         // re
      0.97415984751671725              // im
    }, { -0.059918147361094527,        // re
      -0.9982032937316998              // im
    }, { 0.29530074983338062,          // re
      0.95540434746124281              // im
    }, { -0.47205753887271334,         // re
      -0.88156773987790449             // im
    }, { 0.593590452318187,            // re
      0.80476727997396258              // im
    }, { -0.66794163040451682,         // re
      -0.74421366446240145             // im
    }, { 0.70285470606731981,          // re
      0.7113334395057086               // im
    }, { -0.70285470606732026,         // re
      -0.711333439505708               // im
    }, { 0.667941630404517,            // re
      0.74421366446240123              // im
    }, { -0.593590452318187,           // re
      -0.80476727997396258             // im
    }, { 0.47205753887271307,          // re
      0.88156773987790471              // im
    }, { -0.29530074983338095,         // re
      -0.9554043474612427              // im
    }, { 0.059918147361093958,         // re
      0.9982032937316998               // im
    }, { 0.22585967211126023,          // re
      -0.97415984751671736             // im
    }, { -0.53420594150820178,         // re
      0.845354370697482                // im
    }, { 0.81182688687625426,          // re
      -0.58389819810032761             // im
    }, { -0.9816525964545445,          // re
      0.19067821027598092              // im
    }, { 0.95887647529586684,          // re
      0.28382372191938954              // im
    }, { -0.68559530797654489,         // re
      -0.7279828800738013              // im
    }, { 0.1788939732955811,           // re
      0.98386835822609919              // im
    }, { 0.42924802411467106,          // re
      -0.90318665501304363             // im
    }, { -0.89797481702758764,         // re
      0.44004684748816292              // im
    }, { 0.96540665600255637,          // re
      0.26074889941467028              // im
    }, { -0.513781306164056,           // re
      -0.85792119069082129             // im
    }, { -0.27230588644331188,         // re
      0.96221073794066658              // im
    }, { 0.90826863477082542,          // re
      -0.41838748438683127             // im
    }, { -0.88716458232391282,         // re
      -0.46145314374271768             // im
    }, { 0.13151681260858591,          // re
      0.9913139401830674               // im
    }, { 0.7677545093633712,           // re
      -0.64074410910457                // im
    }, { -0.93599389263703991,         // re
      -0.35201623960573375             // im
    }, { 0.10770795674511113,          // re
      0.9941825768206729               // im
    }, { 0.86402002290807578,          // re
      -0.50345744608052845             // im
    }, { -0.78289835614569425,         // re
      -0.62214963147491265             // im
    }, { -0.34076787600698871,         // re
      0.94014746432763707              // im
    }, { 0.99741308397122974,          // re
      0.0718828207779892               // im
    }, { -0.15525003437706544,         // re
      -0.98787520812394114             // im
    }, { -0.94416586364517918,         // re
      0.32947051753859985              // im
    }, { 0.45078240187579044,          // re
      0.8926338701612736               // im
    }, { 0.85169900841664392,          // re
      -0.52403129588041364             // im
    }, { -0.55432335998687454,         // re
      -0.83230139527268721             // im
    }, { -0.83888818975165,            // re
      0.54430378015883707              // im
    }, { 0.49306119997214554,          // re
      0.869994628191478                // im
    }, { 0.91804011567483912,          // re
      -0.3964875105368742              // im
    }, { -0.24915442247211414,         // re
      -0.96846376997933548             // im
    }, { -0.99884998397728031,         // re
      0.047944859042308309             // im
    }, { -0.20243503195489745,         // re
      0.97929569479162915              // im
    }, { 0.87584414752517514,          // re
      0.48259406258873427              // im
    }, { 0.75216913410767694,          // re
      -0.65897010076004781             // im
    }, { -0.31812578851038181,         // re
      -0.94804851283288649             // im
    }, { -0.99281963123362849,         // re
      -0.1196209841002909              // im
    }, { -0.57412199225992522,         // re
      0.81876977106112947              // im
    }, { 0.40746678980960094,          // re
      0.91322002562485372              // im
    }, { 0.98594266152884857,          // re
      0.16708401532585454              // im
    }, { 0.71970989895762216,          // re
      -0.69427491769644778             // im
    }, { -0.083837159038076842,        // re
      -0.99647946831052381             // im
    }, { -0.79759196536929566,         // re
      -0.60319736138211366             // im
    }, { -0.9896657201539989,          // re
      0.14339373191345106              // im
    }, { -0.63149226758730082,         // re
      0.77538217414217669              // im
    }, { 0.011990524318043143,         // re
      0.9999281110792807               // im
    }, { 0.61271754403145939,          // re
      0.79030197471349939              // im
    }, { 0.9517948536518398,           // re
      0.30673532004298554              // im
    }, { 0.971381640325756,            // re
      -0.2375241226445087              // im
    }, { 0.73615119338287982,          // re
      -0.67681712484316014             // im
    }, { 0.36321399106939722,          // re
      -0.93170574576495979             // im
    }, { -0.035964677315181923,        // re
      -0.99935306172824367             // im
    }, { -0.38545122514572494,         // re
      -0.922728211898639               // im
    }, { -0.64990382581691786,         // re
      -0.76001645849845467             // im
    }, { -0.82559493429568642,         // re
      -0.5642632403987532              // im
    }, { -0.9272836402518978,          // re
      -0.3743595204094442              // im
    }, { -0.97679799210758655,         // re
      -0.21416274796188808             // im
    }, { -0.99540258098282641,         // re
      -0.095779443372404877            // im
    }, { -0.99971245465315683,         // re
      -0.023979324664381876            // im
    } };

  creal_T fv[512];
  creal_T b_fv[512];
  double im;
  if (131 > x_size[0]) {
    std::memset(&y[0], 0, 131U * sizeof(creal_T));
  }

  if (131 < x_size[0]) {
    minNrowsNx = 130;
  } else {
    minNrowsNx = x_size[0] - 1;
  }

  xidx = 0;
  for (k = 0; k <= minNrowsNx; k++) {
    y[k].re = wwc[k + 130].re * x_data[xidx];
    y[k].im = wwc[k + 130].im * -x_data[xidx];
    xidx++;
  }

  minNrowsNx += 2;
  for (k = minNrowsNx; k < 132; k++) {
    y[k - 1].re = 0.0;
    y[k - 1].im = 0.0;
  }

  FFTImplementationCallback::r2br_r2dit_trig_impl((y), (costab), (sintab), (fv));
  FFTImplementationCallback::r2br_r2dit_trig((wwc), (costab), (sintab), (b_fv));
  for (minNrowsNx = 0; minNrowsNx < 512; minNrowsNx++) {
    im = fv[minNrowsNx].re * b_fv[minNrowsNx].im + fv[minNrowsNx].im *
      b_fv[minNrowsNx].re;
    b_fv[minNrowsNx].re = fv[minNrowsNx].re * b_fv[minNrowsNx].re -
      fv[minNrowsNx].im * b_fv[minNrowsNx].im;
    b_fv[minNrowsNx].im = im;
  }

  FFTImplementationCallback::b_r2br_r2dit_trig((b_fv), (costab), (sintabinv),
    (fv));
  minNrowsNx = 0;
  for (k = 0; k < 131; k++) {
    double d;
    double d1;
    double d2;
    im = wwc[k + 130].re;
    d = wwc[k + 130].im;
    d1 = fv[k + 130].re;
    d2 = fv[k + 130].im;
    y[minNrowsNx].re = im * d1 + d * d2;
    y[minNrowsNx].im = im * d2 - d * d1;
    minNrowsNx++;
  }
}

void FFTImplementationCallback::dobluesteinfft(const double x_data[], const int
  x_size[1], int n2blue, int nfft, const coder::array<double, 2U> &costab, const
  coder::array<double, 2U> &sintab, const coder::array<double, 2U> &sintabinv,
  coder::array<creal_T, 1U> &y)
{
  int nInt2m1;
  int j;
  coder::array<creal_T, 1U> wwc;
  int idx;
  int rt;
  int nInt2;
  int k;
  int ix;
  double nt_im;
  double nt_re;
  coder::array<creal_T, 1U> fy;
  int i;
  double twid_re;
  double twid_im;
  coder::array<creal_T, 1U> fv;
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    j = nfft / 2;
    nInt2m1 = (j + j) - 1;
    wwc.set_size(nInt2m1);
    idx = j;
    rt = 0;
    wwc[j - 1].re = 1.0;
    wwc[j - 1].im = 0.0;
    nInt2 = j << 1;
    for (k = 0; k <= j - 2; k++) {
      ix = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= ix) {
        rt += ix - nInt2;
      } else {
        rt += ix;
      }

      nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
        (j);
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = std::cos(nt_im);
        nt_im = std::sin(nt_im);
      }

      wwc[idx - 2].re = nt_re;
      wwc[idx - 2].im = -nt_im;
      idx--;
    }

    idx = 0;
    rt = nInt2m1 - 1;
    for (k = rt; k >= j; k--) {
      wwc[k] = wwc[idx];
      idx++;
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    wwc.set_size(nInt2m1);
    idx = nfft;
    rt = 0;
    wwc[nfft - 1].re = 1.0;
    wwc[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      ix = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= ix) {
        rt += ix - nInt2;
      } else {
        rt += ix;
      }

      nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
        (nfft);
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = std::cos(nt_im);
        nt_im = std::sin(nt_im);
      }

      wwc[idx - 2].re = nt_re;
      wwc[idx - 2].im = -nt_im;
      idx--;
    }

    idx = 0;
    rt = nInt2m1 - 1;
    for (k = rt; k >= nfft; k--) {
      wwc[k] = wwc[idx];
      idx++;
    }
  }

  y.set_size(nfft);
  if (nfft > x_size[0]) {
    y.set_size(nfft);
    for (rt = 0; rt < nfft; rt++) {
      y[rt].re = 0.0;
      y[rt].im = 0.0;
    }
  }

  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    FFTImplementationCallback::doHalfLengthBluestein((x_data), (x_size), (y),
      (x_size[0]), (nfft), (n2blue), (wwc), (costab), (sintab), (costab),
      (sintabinv));
  } else {
    int nt_re_tmp;
    int nRowsD2;
    nInt2m1 = x_size[0];
    if (nfft < nInt2m1) {
      nInt2m1 = nfft;
    }

    rt = 0;
    for (k = 0; k < nInt2m1; k++) {
      nt_re_tmp = (nfft + k) - 1;
      y[k].re = wwc[nt_re_tmp].re * x_data[rt];
      y[k].im = wwc[nt_re_tmp].im * -x_data[rt];
      rt++;
    }

    rt = nInt2m1 + 1;
    for (k = rt; k <= nfft; k++) {
      y[k - 1].re = 0.0;
      y[k - 1].im = 0.0;
    }

    fy.set_size(n2blue);
    if (n2blue > y.size(0)) {
      fy.set_size(n2blue);
      for (rt = 0; rt < n2blue; rt++) {
        fy[rt].re = 0.0;
        fy[rt].im = 0.0;
      }
    }

    rt = y.size(0);
    if (rt >= n2blue) {
      rt = n2blue;
    }

    nInt2 = n2blue - 2;
    nRowsD2 = n2blue / 2;
    k = nRowsD2 / 2;
    ix = 0;
    nInt2m1 = 0;
    idx = 0;
    for (i = 0; i <= rt - 2; i++) {
      boolean_T tst;
      fy[nInt2m1] = y[ix];
      nInt2m1 = n2blue;
      tst = true;
      while (tst) {
        nInt2m1 >>= 1;
        idx ^= nInt2m1;
        tst = ((idx & nInt2m1) == 0);
      }

      nInt2m1 = idx;
      ix++;
    }

    fy[nInt2m1] = y[ix];
    if (n2blue > 1) {
      for (i = 0; i <= nInt2; i += 2) {
        nt_re = fy[i + 1].re;
        nt_im = fy[i + 1].im;
        twid_re = fy[i].re;
        twid_im = fy[i].im;
        fy[i + 1].re = fy[i].re - fy[i + 1].re;
        fy[i + 1].im = fy[i].im - fy[i + 1].im;
        twid_re += nt_re;
        twid_im += nt_im;
        fy[i].re = twid_re;
        fy[i].im = twid_im;
      }
    }

    nInt2m1 = 2;
    rt = 4;
    nInt2 = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (i = 0; i < nInt2; i += rt) {
        nt_re_tmp = i + nInt2m1;
        nt_re = fy[nt_re_tmp].re;
        nt_im = fy[nt_re_tmp].im;
        fy[nt_re_tmp].re = fy[i].re - fy[nt_re_tmp].re;
        fy[nt_re_tmp].im = fy[i].im - fy[nt_re_tmp].im;
        fy[i].re = fy[i].re + nt_re;
        fy[i].im = fy[i].im + nt_im;
      }

      idx = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = idx;
        ix = idx + nInt2;
        while (i < ix) {
          nt_re_tmp = i + nInt2m1;
          nt_re = twid_re * fy[nt_re_tmp].re - twid_im * fy[nt_re_tmp].im;
          nt_im = twid_re * fy[nt_re_tmp].im + twid_im * fy[nt_re_tmp].re;
          fy[nt_re_tmp].re = fy[i].re - nt_re;
          fy[nt_re_tmp].im = fy[i].im - nt_im;
          fy[i].re = fy[i].re + nt_re;
          fy[i].im = fy[i].im + nt_im;
          i += rt;
        }

        idx++;
      }

      k /= 2;
      nInt2m1 = rt;
      rt += rt;
      nInt2 -= nInt2m1;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (n2blue), (costab),
      (sintab), (fv));
    nInt2m1 = fy.size(0);
    for (rt = 0; rt < nInt2m1; rt++) {
      twid_im = fy[rt].re * fv[rt].im + fy[rt].im * fv[rt].re;
      fy[rt].re = fy[rt].re * fv[rt].re - fy[rt].im * fv[rt].im;
      fy[rt].im = twid_im;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (n2blue), (costab),
      (sintabinv), (fv));
    if (fv.size(0) > 1) {
      twid_re = 1.0 / static_cast<double>(fv.size(0));
      nInt2m1 = fv.size(0);
      for (rt = 0; rt < nInt2m1; rt++) {
        fv[rt].re = twid_re * fv[rt].re;
        fv[rt].im = twid_re * fv[rt].im;
      }
    }

    idx = 0;
    rt = wwc.size(0);
    for (k = nfft; k <= rt; k++) {
      y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
      y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
      idx++;
    }
  }
}

// End of code generation (FFTImplementationCallback.cpp)
