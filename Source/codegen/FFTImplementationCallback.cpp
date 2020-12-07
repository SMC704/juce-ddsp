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
#include "getPitch2.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void FFTImplementationCallback::doHalfLengthBluestein(const double x_data[],
  const int x_size[1], coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int
  nfft, const coder::array<creal_T, 1U> &wwc, const coder::array<double, 2U>
  &costab, const coder::array<double, 2U> &sintab, const coder::array<double, 2U>
  &costabinv, const coder::array<double, 2U> &sintabinv)
{
  int hnRows;
  coder::array<creal_T, 1U> ytmp;
  int i;
  boolean_T nxeven;
  int u0;
  coder::array<double, 2U> costable;
  coder::array<double, 2U> sintable;
  coder::array<double, 2U> unusedU0;
  coder::array<double, 2U> hsintab;
  coder::array<double, 2U> hcostabinv;
  coder::array<double, 2U> hsintabinv;
  coder::array<creal_T, 1U> reconVar1;
  coder::array<creal_T, 1U> reconVar2;
  int idx;
  coder::array<int, 2U> wrapIndex;
  int xidx;
  double b_im;
  coder::array<creal_T, 1U> fv;
  coder::array<creal_T, 1U> b_fv;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (i = 0; i < hnRows; i++) {
      ytmp[i].re = 0.0;
      ytmp[i].im = 0.0;
    }
  }

  if ((x_size[0] & 1) == 0) {
    nxeven = true;
    u0 = x_size[0];
  } else if (x_size[0] >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x_size[0] - 1;
  }

  if (u0 >= nRows) {
    u0 = nRows;
  }

  FFTImplementationCallback::generate_twiddle_tables((nRows << 1), (costable),
    (sintable), (unusedU0));
  FFTImplementationCallback::get_half_twiddle_tables((costab), (sintab),
    (costabinv), (sintabinv), (unusedU0), (hsintab), (hcostabinv), (hsintabinv));
  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  idx = 0;
  wrapIndex.set_size(1, hnRows);
  for (xidx = 0; xidx < hnRows; xidx++) {
    reconVar1[xidx].re = sintable[idx] + 1.0;
    reconVar1[xidx].im = -costable[idx];
    reconVar2[xidx].re = 1.0 - sintable[idx];
    reconVar2[xidx].im = costable[idx];
    idx += 2;
    if (xidx + 1 != 1) {
      wrapIndex[xidx] = (hnRows - xidx) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }

  xidx = 0;
  i = static_cast<int>(static_cast<double>(u0) / 2.0);
  for (int k1 = 0; k1 < i; k1++) {
    idx = (hnRows + k1) - 1;
    b_im = x_data[xidx + 1];
    ytmp[k1].re = wwc[idx].re * x_data[xidx] + wwc[idx].im * b_im;
    ytmp[k1].im = wwc[idx].re * b_im - wwc[idx].im * x_data[xidx];
    xidx += 2;
  }

  if (!nxeven) {
    idx = (hnRows + i) - 1;
    ytmp[i].re = wwc[idx].re * x_data[xidx] + wwc[idx].im * 0.0;
    ytmp[i].im = wwc[idx].re * 0.0 - wwc[idx].im * x_data[xidx];
    if (i + 2 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
      for (xidx = i; xidx <= hnRows; xidx++) {
        ytmp[xidx - 1].re = 0.0;
        ytmp[xidx - 1].im = 0.0;
      }
    }
  } else {
    if (i + 1 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
      for (xidx = i; xidx <= hnRows; xidx++) {
        ytmp[xidx - 1].re = 0.0;
        ytmp[xidx - 1].im = 0.0;
      }
    }
  }

  idx = static_cast<int>(static_cast<double>(nfft) / 2.0);
  FFTImplementationCallback::r2br_r2dit_trig_impl((ytmp), (idx), (unusedU0),
    (hsintab), (fv));
  FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (idx), (unusedU0),
    (hsintab), (b_fv));
  b_fv.set_size(fv.size(0));
  xidx = fv.size(0);
  for (i = 0; i < xidx; i++) {
    b_im = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
    b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
    b_fv[i].im = b_im;
  }

  FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (idx), (hcostabinv),
    (hsintabinv), (fv));
  if (fv.size(0) > 1) {
    b_im = 1.0 / static_cast<double>(fv.size(0));
    xidx = fv.size(0);
    for (i = 0; i < xidx; i++) {
      fv[i].re = b_im * fv[i].re;
      fv[i].im = b_im * fv[i].im;
    }
  }

  idx = 0;
  i = wwc.size(0);
  for (xidx = hnRows; xidx <= i; xidx++) {
    ytmp[idx].re = wwc[xidx - 1].re * fv[xidx - 1].re + wwc[xidx - 1].im *
      fv[xidx - 1].im;
    ytmp[idx].im = wwc[xidx - 1].re * fv[xidx - 1].im - wwc[xidx - 1].im *
      fv[xidx - 1].re;
    idx++;
  }

  for (xidx = 0; xidx < hnRows; xidx++) {
    double ytmp_im;
    i = wrapIndex[xidx];
    b_im = ytmp[i - 1].re;
    ytmp_im = -ytmp[i - 1].im;
    y[xidx].re = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].re - ytmp[xidx].im *
                         reconVar1[xidx].im) + (b_im * reconVar2[xidx].re -
      ytmp_im * reconVar2[xidx].im));
    y[xidx].im = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].im + ytmp[xidx].im *
                         reconVar1[xidx].re) + (b_im * reconVar2[xidx].im +
      ytmp_im * reconVar2[xidx].re));
    b_im = ytmp[i - 1].re;
    ytmp_im = -ytmp[i - 1].im;
    i = hnRows + xidx;
    y[i].re = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].re - ytmp[xidx].im *
                      reconVar2[xidx].im) + (b_im * reconVar1[xidx].re - ytmp_im
      * reconVar1[xidx].im));
    y[i].im = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].im + ytmp[xidx].im *
                      reconVar2[xidx].re) + (b_im * reconVar1[xidx].im + ytmp_im
      * reconVar1[xidx].re));
  }
}

void FFTImplementationCallback::doHalfLengthBluestein(const coder::array<double,
  1U> &x, coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const
  coder::array<creal_T, 1U> &wwc, const coder::array<double, 2U> &costab, const
  coder::array<double, 2U> &sintab, const coder::array<double, 2U> &costabinv,
  const coder::array<double, 2U> &sintabinv)
{
  int hnRows;
  coder::array<creal_T, 1U> ytmp;
  int i;
  boolean_T nxeven;
  int u0;
  coder::array<double, 2U> costable;
  coder::array<double, 2U> sintable;
  coder::array<double, 2U> unusedU0;
  coder::array<double, 2U> hsintab;
  coder::array<double, 2U> hcostabinv;
  coder::array<double, 2U> hsintabinv;
  coder::array<creal_T, 1U> reconVar1;
  coder::array<creal_T, 1U> reconVar2;
  int idx;
  coder::array<int, 2U> wrapIndex;
  int xidx;
  double b_im;
  coder::array<creal_T, 1U> fv;
  coder::array<creal_T, 1U> b_fv;
  double re;
  hnRows = nRows / 2;
  ytmp.set_size(hnRows);
  if (hnRows > nrowsx) {
    ytmp.set_size(hnRows);
    for (i = 0; i < hnRows; i++) {
      ytmp[i].re = 0.0;
      ytmp[i].im = 0.0;
    }
  }

  if ((x.size(0) & 1) == 0) {
    nxeven = true;
    u0 = x.size(0);
  } else if (x.size(0) >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x.size(0) - 1;
  }

  if (u0 >= nRows) {
    u0 = nRows;
  }

  FFTImplementationCallback::generate_twiddle_tables((nRows << 1), (costable),
    (sintable), (unusedU0));
  FFTImplementationCallback::get_half_twiddle_tables((costab), (sintab),
    (costabinv), (sintabinv), (unusedU0), (hsintab), (hcostabinv), (hsintabinv));
  reconVar1.set_size(hnRows);
  reconVar2.set_size(hnRows);
  idx = 0;
  wrapIndex.set_size(1, hnRows);
  for (xidx = 0; xidx < hnRows; xidx++) {
    reconVar1[xidx].re = 1.0 - sintable[idx];
    reconVar1[xidx].im = -costable[idx];
    reconVar2[xidx].re = sintable[idx] + 1.0;
    reconVar2[xidx].im = costable[idx];
    idx += 2;
    if (xidx + 1 != 1) {
      wrapIndex[xidx] = (hnRows - xidx) + 1;
    } else {
      wrapIndex[0] = 1;
    }
  }

  xidx = 0;
  i = static_cast<int>(static_cast<double>(u0) / 2.0);
  for (int k1 = 0; k1 < i; k1++) {
    idx = (hnRows + k1) - 1;
    b_im = x[xidx + 1];
    ytmp[k1].re = wwc[idx].re * x[xidx] + wwc[idx].im * b_im;
    ytmp[k1].im = wwc[idx].re * b_im - wwc[idx].im * x[xidx];
    xidx += 2;
  }

  if (!nxeven) {
    idx = (hnRows + i) - 1;
    ytmp[i].re = wwc[idx].re * x[xidx] + wwc[idx].im * 0.0;
    ytmp[i].im = wwc[idx].re * 0.0 - wwc[idx].im * x[xidx];
    if (i + 2 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 2;
      for (xidx = i; xidx <= hnRows; xidx++) {
        ytmp[xidx - 1].re = 0.0;
        ytmp[xidx - 1].im = 0.0;
      }
    }
  } else {
    if (i + 1 <= hnRows) {
      i = static_cast<int>(static_cast<double>(u0) / 2.0) + 1;
      for (xidx = i; xidx <= hnRows; xidx++) {
        ytmp[xidx - 1].re = 0.0;
        ytmp[xidx - 1].im = 0.0;
      }
    }
  }

  idx = static_cast<int>(static_cast<double>(nfft) / 2.0);
  FFTImplementationCallback::r2br_r2dit_trig_impl((ytmp), (idx), (unusedU0),
    (hsintab), (fv));
  FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (idx), (unusedU0),
    (hsintab), (b_fv));
  b_fv.set_size(fv.size(0));
  xidx = fv.size(0);
  for (i = 0; i < xidx; i++) {
    b_im = fv[i].re * b_fv[i].im + fv[i].im * b_fv[i].re;
    b_fv[i].re = fv[i].re * b_fv[i].re - fv[i].im * b_fv[i].im;
    b_fv[i].im = b_im;
  }

  FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (idx), (hcostabinv),
    (hsintabinv), (fv));
  if (fv.size(0) > 1) {
    b_im = 1.0 / static_cast<double>(fv.size(0));
    xidx = fv.size(0);
    for (i = 0; i < xidx; i++) {
      fv[i].re = b_im * fv[i].re;
      fv[i].im = b_im * fv[i].im;
    }
  }

  idx = 0;
  i = wwc.size(0);
  for (xidx = hnRows; xidx <= i; xidx++) {
    ytmp[idx].re = wwc[xidx - 1].re * fv[xidx - 1].re + wwc[xidx - 1].im *
      fv[xidx - 1].im;
    ytmp[idx].im = wwc[xidx - 1].re * fv[xidx - 1].im - wwc[xidx - 1].im *
      fv[xidx - 1].re;
    if (ytmp[idx].im == 0.0) {
      re = ytmp[idx].re / static_cast<double>(hnRows);
      b_im = 0.0;
    } else if (ytmp[idx].re == 0.0) {
      re = 0.0;
      b_im = ytmp[idx].im / static_cast<double>(hnRows);
    } else {
      re = ytmp[idx].re / static_cast<double>(hnRows);
      b_im = ytmp[idx].im / static_cast<double>(hnRows);
    }

    ytmp[idx].re = re;
    ytmp[idx].im = b_im;
    idx++;
  }

  for (xidx = 0; xidx < hnRows; xidx++) {
    i = wrapIndex[xidx];
    b_im = ytmp[i - 1].re;
    re = -ytmp[i - 1].im;
    y[xidx].re = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].re - ytmp[xidx].im *
                         reconVar1[xidx].im) + (b_im * reconVar2[xidx].re - re *
      reconVar2[xidx].im));
    y[xidx].im = 0.5 * ((ytmp[xidx].re * reconVar1[xidx].im + ytmp[xidx].im *
                         reconVar1[xidx].re) + (b_im * reconVar2[xidx].im + re *
      reconVar2[xidx].re));
    b_im = ytmp[i - 1].re;
    re = -ytmp[i - 1].im;
    i = hnRows + xidx;
    y[i].re = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].re - ytmp[xidx].im *
                      reconVar2[xidx].im) + (b_im * reconVar1[xidx].re - re *
      reconVar1[xidx].im));
    y[i].im = 0.5 * ((ytmp[xidx].re * reconVar2[xidx].im + ytmp[xidx].im *
                      reconVar2[xidx].re) + (b_im * reconVar1[xidx].im + re *
      reconVar1[xidx].re));
  }

  xidx = y.size(0);
  for (i = 0; i < xidx; i++) {
    double ai;
    b_im = y[i].re;
    ai = y[i].im;
    if (ai == 0.0) {
      re = b_im / 2.0;
      b_im = 0.0;
    } else if (b_im == 0.0) {
      re = 0.0;
      b_im = ai / 2.0;
    } else {
      re = b_im / 2.0;
      b_im = ai / 2.0;
    }

    y[i].re = re;
    y[i].im = b_im;
  }
}

void FFTImplementationCallback::generate_twiddle_tables(int nRows, coder::array<
  double, 2U> &costab, coder::array<double, 2U> &sintab, coder::array<double, 2U>
  &sintabinv)
{
  double e;
  int n;
  coder::array<double, 2U> costab1q;
  int nd2;
  int k;
  int i;
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  costab1q.set_size(1, (n + 1));
  costab1q[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }

  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q[k] = std::sin(e * static_cast<double>(n - k));
  }

  costab1q[n] = 0.0;
  n = costab1q.size(1) - 1;
  nd2 = (costab1q.size(1) - 1) << 1;
  costab.set_size(1, (nd2 + 1));
  sintab.set_size(1, (nd2 + 1));
  costab[0] = 1.0;
  sintab[0] = 0.0;
  sintabinv.set_size(1, (nd2 + 1));
  for (k = 0; k < n; k++) {
    sintabinv[k + 1] = costab1q[(n - k) - 1];
  }

  i = costab1q.size(1);
  for (k = i; k <= nd2; k++) {
    sintabinv[k] = costab1q[k - n];
  }

  for (k = 0; k < n; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[(n - k) - 1];
  }

  i = costab1q.size(1);
  for (k = i; k <= nd2; k++) {
    costab[k] = -costab1q[nd2 - k];
    sintab[k] = -costab1q[k - n];
  }
}

void FFTImplementationCallback::get_bitrevIndex(int nRowsM1, int nfftLen, coder::
  array<int, 1U> &bitrevIndex)
{
  int ju;
  int iy;
  int b_j1;
  ju = 0;
  iy = 1;
  bitrevIndex.set_size(nfftLen);
  for (b_j1 = 0; b_j1 < nfftLen; b_j1++) {
    bitrevIndex[b_j1] = 0;
  }

  for (b_j1 = 0; b_j1 < nRowsM1; b_j1++) {
    boolean_T tst;
    bitrevIndex[b_j1] = iy;
    iy = nfftLen;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju + 1;
  }

  bitrevIndex[nRowsM1] = iy;
}

void FFTImplementationCallback::get_half_twiddle_tables(const coder::array<
  double, 2U> &costab, const coder::array<double, 2U> &sintab, const coder::
  array<double, 2U> &costabinv, const coder::array<double, 2U> &sintabinv, coder::
  array<double, 2U> &hcostab, coder::array<double, 2U> &hsintab, coder::array<
  double, 2U> &hcostabinv, coder::array<double, 2U> &hsintabinv)
{
  int hszCostab;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  hcostabinv.set_size(1, hszCostab);
  hsintabinv.set_size(1, hszCostab);
  for (int i = 0; i < hszCostab; i++) {
    int hcostab_tmp;
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab[i] = costab[hcostab_tmp];
    hsintab[i] = sintab[hcostab_tmp];
    hcostabinv[i] = costabinv[hcostab_tmp];
    hsintabinv[i] = sintabinv[hcostab_tmp];
  }
}

void FFTImplementationCallback::getback_radix2_fft(coder::array<creal_T, 1U> &y,
  const coder::array<creal_T, 1U> &reconVar1, const coder::array<creal_T, 1U>
  &reconVar2, const coder::array<int, 2U> &wrapIndex, int hnRows)
{
  int iterVar;
  double temp1_re;
  double temp1_im;
  double y_im;
  double y_re;
  double b_y_im;
  int b_i;
  iterVar = hnRows / 2;
  temp1_re = y[0].re;
  temp1_im = y[0].im;
  y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
  y_re = y[0].re;
  b_y_im = -y[0].im;
  y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im) +
                   (y_re * reconVar2[0].re - b_y_im * reconVar2[0].im));
  y[0].im = 0.5 * (y_im + (y_re * reconVar2[0].im + b_y_im * reconVar2[0].re));
  y[hnRows].re = 0.5 * ((temp1_re * reconVar2[0].re - temp1_im * reconVar2[0].im)
                        + (temp1_re * reconVar1[0].re - -temp1_im * reconVar1[0]
    .im));
  y[hnRows].im = 0.5 * ((temp1_re * reconVar2[0].im + temp1_im * reconVar2[0].re)
                        + (temp1_re * reconVar1[0].im + -temp1_im * reconVar1[0]
    .re));
  for (int i = 2; i <= iterVar; i++) {
    double temp2_re;
    double temp2_im;
    int i1;
    temp1_re = y[i - 1].re;
    temp1_im = y[i - 1].im;
    b_i = wrapIndex[i - 1];
    temp2_re = y[b_i - 1].re;
    temp2_im = y[b_i - 1].im;
    y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i - 1].re;
    y_re = y[b_i - 1].re;
    b_y_im = -y[b_i - 1].im;
    y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                          reconVar1[i - 1].im) + (y_re * reconVar2[i - 1].re -
      b_y_im * reconVar2[i - 1].im));
    y[i - 1].im = 0.5 * (y_im + (y_re * reconVar2[i - 1].im + b_y_im *
      reconVar2[i - 1].re));
    i1 = (hnRows + i) - 1;
    y[i1].re = 0.5 * ((temp1_re * reconVar2[i - 1].re - temp1_im * reconVar2[i -
                       1].im) + (temp2_re * reconVar1[i - 1].re - -temp2_im *
      reconVar1[i - 1].im));
    y[i1].im = 0.5 * ((temp1_re * reconVar2[i - 1].im + temp1_im * reconVar2[i -
                       1].re) + (temp2_re * reconVar1[i - 1].im + -temp2_im *
      reconVar1[i - 1].re));
    y[b_i - 1].re = 0.5 * ((temp2_re * reconVar1[b_i - 1].re - temp2_im *
      reconVar1[b_i - 1].im) + (temp1_re * reconVar2[b_i - 1].re - -temp1_im *
      reconVar2[b_i - 1].im));
    y[b_i - 1].im = 0.5 * ((temp2_re * reconVar1[b_i - 1].im + temp2_im *
      reconVar1[b_i - 1].re) + (temp1_re * reconVar2[b_i - 1].im + -temp1_im *
      reconVar2[b_i - 1].re));
    i1 = (b_i + hnRows) - 1;
    y[i1].re = 0.5 * ((temp2_re * reconVar2[b_i - 1].re - temp2_im *
                       reconVar2[b_i - 1].im) + (temp1_re * reconVar1[b_i - 1].
      re - -temp1_im * reconVar1[b_i - 1].im));
    y[i1].im = 0.5 * ((temp2_re * reconVar2[b_i - 1].im + temp2_im *
                       reconVar2[b_i - 1].re) + (temp1_re * reconVar1[b_i - 1].
      im + -temp1_im * reconVar1[b_i - 1].re));
  }

  if (iterVar != 0) {
    temp1_re = y[iterVar].re;
    temp1_im = y[iterVar].im;
    y_im = y[iterVar].re * reconVar1[iterVar].im + y[iterVar].im *
      reconVar1[iterVar].re;
    y_re = y[iterVar].re;
    b_y_im = -y[iterVar].im;
    y[iterVar].re = 0.5 * ((y[iterVar].re * reconVar1[iterVar].re - y[iterVar].
      im * reconVar1[iterVar].im) + (y_re * reconVar2[iterVar].re - b_y_im *
      reconVar2[iterVar].im));
    y[iterVar].im = 0.5 * (y_im + (y_re * reconVar2[iterVar].im + b_y_im *
      reconVar2[iterVar].re));
    b_i = hnRows + iterVar;
    y[b_i].re = 0.5 * ((temp1_re * reconVar2[iterVar].re - temp1_im *
                        reconVar2[iterVar].im) + (temp1_re * reconVar1[iterVar].
      re - -temp1_im * reconVar1[iterVar].im));
    y[b_i].im = 0.5 * ((temp1_re * reconVar2[iterVar].im + temp1_im *
                        reconVar2[iterVar].re) + (temp1_re * reconVar1[iterVar].
      im + -temp1_im * reconVar1[iterVar].re));
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
  int istart;
  int nRowsD2;
  int k;
  int hszCostab;
  coder::array<double, 2U> hcostab;
  coder::array<double, 2U> hsintab;
  int i;
  coder::array<creal_T, 1U> reconVar1;
  int ix;
  coder::array<creal_T, 1U> reconVar2;
  coder::array<int, 2U> wrapIndex;
  double temp_re;
  double temp_im;
  coder::array<int, 1U> bitrevIndex;
  boolean_T nxeven;
  int j;
  nRows = unsigned_nRows / 2;
  istart = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  for (i = 0; i < hszCostab; i++) {
    ix = ((i + 1) << 1) - 2;
    hcostab[i] = costab[ix];
    hsintab[i] = sintab[ix];
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

  hszCostab = y.size(0);
  if (hszCostab >= nRows) {
    hszCostab = nRows;
  }

  FFTImplementationCallback::get_bitrevIndex((hszCostab - 1), (static_cast<int>(
    static_cast<double>(unsigned_nRows) / 2.0)), (bitrevIndex));
  if ((x_size[0] & 1) == 0) {
    nxeven = true;
    hszCostab = x_size[0];
  } else if (x_size[0] >= unsigned_nRows) {
    nxeven = true;
    hszCostab = unsigned_nRows;
  } else {
    nxeven = false;
    hszCostab = x_size[0] - 1;
  }

  ix = 0;
  if (hszCostab >= unsigned_nRows) {
    hszCostab = unsigned_nRows;
  }

  temp_re = static_cast<double>(hszCostab) / 2.0;
  hszCostab = static_cast<int>(temp_re);
  for (i = 0; i < hszCostab; i++) {
    y[bitrevIndex[i] - 1].re = x_data[ix];
    y[bitrevIndex[i] - 1].im = x_data[ix + 1];
    ix += 2;
  }

  if (!nxeven) {
    hszCostab = bitrevIndex[static_cast<int>(temp_re)] - 1;
    y[hszCostab].re = x_data[ix];
    y[hszCostab].im = 0.0;
  }

  if (nRows > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
  }

  hszCostab = 2;
  ix = 4;
  nRows = ((k - 1) << 2) + 1;
  while (k > 0) {
    int temp_re_tmp;
    for (i = 0; i < nRows; i += ix) {
      temp_re_tmp = i + hszCostab;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - temp_re;
      y[temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }

    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_re;
      double twid_im;
      int ihi;
      twid_re = hcostab[j];
      twid_im = hsintab[j];
      i = istart;
      ihi = istart + nRows;
      while (i < ihi) {
        temp_re_tmp = i + hszCostab;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += ix;
      }

      istart++;
    }

    k /= 2;
    hszCostab = ix;
    ix += ix;
    nRows -= hszCostab;
  }

  FFTImplementationCallback::getback_radix2_fft((y), (reconVar1), (reconVar2),
    (wrapIndex), (static_cast<int>(static_cast<double>(unsigned_nRows) / 2.0)));
}

void FFTImplementationCallback::doHalfLengthRadix2(const coder::array<double, 1U>
  &x, coder::array<creal_T, 1U> &y, int unsigned_nRows, const coder::array<
  double, 2U> &costab, const coder::array<double, 2U> &sintab)
{
  int nRows;
  int istart;
  int nRowsD2;
  int k;
  int hszCostab;
  coder::array<double, 2U> hcostab;
  coder::array<double, 2U> hsintab;
  int i;
  coder::array<creal_T, 1U> reconVar1;
  int ix;
  coder::array<creal_T, 1U> reconVar2;
  coder::array<int, 2U> wrapIndex;
  double temp_re;
  double temp_im;
  coder::array<int, 1U> bitrevIndex;
  boolean_T nxeven;
  int j;
  nRows = unsigned_nRows / 2;
  istart = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab.size(1) / 2;
  hcostab.set_size(1, hszCostab);
  hsintab.set_size(1, hszCostab);
  for (i = 0; i < hszCostab; i++) {
    ix = ((i + 1) << 1) - 2;
    hcostab[i] = costab[ix];
    hsintab[i] = sintab[ix];
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

  hszCostab = y.size(0);
  if (hszCostab >= nRows) {
    hszCostab = nRows;
  }

  FFTImplementationCallback::get_bitrevIndex((hszCostab - 1), (static_cast<int>(
    static_cast<double>(unsigned_nRows) / 2.0)), (bitrevIndex));
  if ((x.size(0) & 1) == 0) {
    nxeven = true;
    hszCostab = x.size(0);
  } else if (x.size(0) >= unsigned_nRows) {
    nxeven = true;
    hszCostab = unsigned_nRows;
  } else {
    nxeven = false;
    hszCostab = x.size(0) - 1;
  }

  ix = 0;
  if (hszCostab >= unsigned_nRows) {
    hszCostab = unsigned_nRows;
  }

  temp_re = static_cast<double>(hszCostab) / 2.0;
  hszCostab = static_cast<int>(temp_re);
  for (i = 0; i < hszCostab; i++) {
    y[bitrevIndex[i] - 1].re = x[ix];
    y[bitrevIndex[i] - 1].im = x[ix + 1];
    ix += 2;
  }

  if (!nxeven) {
    hszCostab = bitrevIndex[static_cast<int>(temp_re)] - 1;
    y[hszCostab].re = x[ix];
    y[hszCostab].im = 0.0;
  }

  if (nRows > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re = y[i + 1].re;
      temp_im = y[i + 1].im;
      y[i + 1].re = y[i].re - y[i + 1].re;
      y[i + 1].im = y[i].im - y[i + 1].im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }
  }

  hszCostab = 2;
  ix = 4;
  nRows = ((k - 1) << 2) + 1;
  while (k > 0) {
    int temp_re_tmp;
    for (i = 0; i < nRows; i += ix) {
      temp_re_tmp = i + hszCostab;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - temp_re;
      y[temp_re_tmp].im = y[i].im - temp_im;
      y[i].re = y[i].re + temp_re;
      y[i].im = y[i].im + temp_im;
    }

    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_re;
      double twid_im;
      int ihi;
      twid_re = hcostab[j];
      twid_im = hsintab[j];
      i = istart;
      ihi = istart + nRows;
      while (i < ihi) {
        temp_re_tmp = i + hszCostab;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re = y[i].re + temp_re;
        y[i].im = y[i].im + temp_im;
        i += ix;
      }

      istart++;
    }

    k /= 2;
    hszCostab = ix;
    ix += ix;
    nRows -= hszCostab;
  }

  FFTImplementationCallback::getback_radix2_fft((y), (reconVar1), (reconVar2),
    (wrapIndex), (static_cast<int>(static_cast<double>(unsigned_nRows) / 2.0)));
}

void FFTImplementationCallback::dobluesteinfft(const double x_data[], const int
  x_size[1], int n2blue, int nfft, const coder::array<double, 2U> &costab, const
  coder::array<double, 2U> &sintab, const coder::array<double, 2U> &sintabinv,
  coder::array<creal_T, 1U> &y)
{
  int nInt2m1;
  coder::array<creal_T, 1U> wwc;
  int idx;
  int rt;
  int nInt2;
  int k;
  double nt_re;
  coder::array<creal_T, 1U> fv;
  coder::array<creal_T, 1U> b_fv;
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    int nRows;
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    wwc.set_size(nInt2m1);
    idx = nRows;
    rt = 0;
    wwc[nRows - 1].re = 1.0;
    wwc[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      int b_y;
      double nt_im;
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }

      nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
        (nRows);
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
    for (k = rt; k >= nRows; k--) {
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
      int b_y;
      double nt_im;
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
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
    nInt2m1 = x_size[0];
    if (nfft < nInt2m1) {
      nInt2m1 = nfft;
    }

    rt = 0;
    for (k = 0; k < nInt2m1; k++) {
      nInt2 = (nfft + k) - 1;
      y[k].re = wwc[nInt2].re * x_data[rt];
      y[k].im = wwc[nInt2].im * -x_data[rt];
      rt++;
    }

    rt = nInt2m1 + 1;
    for (k = rt; k <= nfft; k++) {
      y[k - 1].re = 0.0;
      y[k - 1].im = 0.0;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((y), (n2blue), (costab),
      (sintab), (fv));
    FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (n2blue), (costab),
      (sintab), (b_fv));
    b_fv.set_size(fv.size(0));
    nInt2m1 = fv.size(0);
    for (rt = 0; rt < nInt2m1; rt++) {
      nt_re = fv[rt].re * b_fv[rt].im + fv[rt].im * b_fv[rt].re;
      b_fv[rt].re = fv[rt].re * b_fv[rt].re - fv[rt].im * b_fv[rt].im;
      b_fv[rt].im = nt_re;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (n2blue), (costab),
      (sintabinv), (fv));
    if (fv.size(0) > 1) {
      nt_re = 1.0 / static_cast<double>(fv.size(0));
      nInt2m1 = fv.size(0);
      for (rt = 0; rt < nInt2m1; rt++) {
        fv[rt].re = nt_re * fv[rt].re;
        fv[rt].im = nt_re * fv[rt].im;
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

void FFTImplementationCallback::dobluesteinfft(const coder::array<double, 1U> &x,
  int n2blue, int nfft, const coder::array<double, 2U> &costab, const coder::
  array<double, 2U> &sintab, const coder::array<double, 2U> &sintabinv, coder::
  array<creal_T, 1U> &y)
{
  int nInt2m1;
  coder::array<creal_T, 1U> wwc;
  int idx;
  int rt;
  int nInt2;
  int k;
  double nt_im;
  double nt_re;
  coder::array<creal_T, 1U> fv;
  coder::array<creal_T, 1U> b_fv;
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    int nRows;
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    wwc.set_size(nInt2m1);
    idx = nRows;
    rt = 0;
    wwc[nRows - 1].re = 1.0;
    wwc[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      int b_y;
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }

      nt_im = 3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
        (nRows);
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
    for (k = rt; k >= nRows; k--) {
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
      int b_y;
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }

      nt_im = 3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
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
  if (nfft > x.size(0)) {
    y.set_size(nfft);
    for (rt = 0; rt < nfft; rt++) {
      y[rt].re = 0.0;
      y[rt].im = 0.0;
    }
  }

  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    FFTImplementationCallback::doHalfLengthBluestein((x), (y), (x.size(0)),
      (nfft), (n2blue), (wwc), (costab), (sintab), (costab), (sintabinv));
  } else {
    nInt2m1 = x.size(0);
    if (nfft < nInt2m1) {
      nInt2m1 = nfft;
    }

    rt = 0;
    for (k = 0; k < nInt2m1; k++) {
      nInt2 = (nfft + k) - 1;
      y[k].re = wwc[nInt2].re * x[rt];
      y[k].im = wwc[nInt2].im * -x[rt];
      rt++;
    }

    rt = nInt2m1 + 1;
    for (k = rt; k <= nfft; k++) {
      y[k - 1].re = 0.0;
      y[k - 1].im = 0.0;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((y), (n2blue), (costab),
      (sintab), (fv));
    FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (n2blue), (costab),
      (sintab), (b_fv));
    b_fv.set_size(fv.size(0));
    nInt2m1 = fv.size(0);
    for (rt = 0; rt < nInt2m1; rt++) {
      nt_re = fv[rt].re * b_fv[rt].im + fv[rt].im * b_fv[rt].re;
      b_fv[rt].re = fv[rt].re * b_fv[rt].re - fv[rt].im * b_fv[rt].im;
      b_fv[rt].im = nt_re;
    }

    FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (n2blue), (costab),
      (sintabinv), (fv));
    if (fv.size(0) > 1) {
      nt_re = 1.0 / static_cast<double>(fv.size(0));
      nInt2m1 = fv.size(0);
      for (rt = 0; rt < nInt2m1; rt++) {
        fv[rt].re = nt_re * fv[rt].re;
        fv[rt].im = nt_re * fv[rt].im;
      }
    }

    idx = 0;
    rt = wwc.size(0);
    for (k = nfft; k <= rt; k++) {
      y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].im;
      y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].re;
      if (y[idx].im == 0.0) {
        nt_im = y[idx].re / static_cast<double>(nfft);
        nt_re = 0.0;
      } else if (y[idx].re == 0.0) {
        nt_im = 0.0;
        nt_re = y[idx].im / static_cast<double>(nfft);
      } else {
        nt_im = y[idx].re / static_cast<double>(nfft);
        nt_re = y[idx].im / static_cast<double>(nfft);
      }

      y[idx].re = nt_im;
      y[idx].im = nt_re;
      idx++;
    }
  }
}

void FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
  int *n2blue, int *nRows)
{
  *n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    if (nfft > 0) {
      int n;
      int pmax;
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }

      *n2blue = 1 << pmax;
    }

    *nRows = *n2blue;
  }
}

// End of code generation (FFTImplementationCallback.cpp)
