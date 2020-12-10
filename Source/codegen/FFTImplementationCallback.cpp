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
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder
{
  namespace internal
  {
    void FFTImplementationCallback::doHalfLengthBluestein(const double x_data[],
      const int x_size[1], ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows,
      int nfft, const ::coder::array<creal_T, 1U> &wwc, const ::coder::array<
      double, 2U> &costab, const ::coder::array<double, 2U> &sintab, const ::
      coder::array<double, 2U> &costabinv, const ::coder::array<double, 2U>
      &sintabinv)
    {
      array<creal_T, 1U> fv;
      array<creal_T, 1U> fy;
      array<creal_T, 1U> reconVar1;
      array<creal_T, 1U> reconVar2;
      array<creal_T, 1U> ytmp;
      array<double, 2U> b_costab;
      array<double, 2U> b_sintab;
      array<double, 2U> costab1q;
      array<double, 2U> hcostabinv;
      array<double, 2U> hsintab;
      array<double, 2U> hsintabinv;
      array<int, 2U> wrapIndex;
      double e;
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      double z;
      int hnRows;
      int i;
      int iDelta2;
      int ihi;
      int ix;
      int j;
      int ju;
      int k;
      int nRowsD2;
      int nd2;
      int temp_re_tmp;
      boolean_T tst;
      hnRows = nRows / 2;
      ytmp.set_size(hnRows);
      if (hnRows > nrowsx) {
        ytmp.set_size(hnRows);
        for (iDelta2 = 0; iDelta2 < hnRows; iDelta2++) {
          ytmp[iDelta2].re = 0.0;
          ytmp[iDelta2].im = 0.0;
        }
      }

      if ((x_size[0] & 1) == 0) {
        tst = true;
        ju = x_size[0];
      } else if (x_size[0] >= nRows) {
        tst = true;
        ju = nRows;
      } else {
        tst = false;
        ju = x_size[0] - 1;
      }

      if (ju >= nRows) {
        ju = nRows;
      }

      nd2 = nRows << 1;
      e = 6.2831853071795862 / static_cast<double>(nd2);
      ihi = nd2 / 2 / 2;
      costab1q.set_size(1, (ihi + 1));
      costab1q[0] = 1.0;
      nd2 = ihi / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }

      iDelta2 = nd2 + 2;
      nd2 = ihi - 1;
      for (k = iDelta2; k <= nd2; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(ihi - k));
      }

      costab1q[ihi] = 0.0;
      ihi = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      b_costab.set_size(1, (nd2 + 1));
      b_sintab.set_size(1, (nd2 + 1));
      b_costab[0] = 1.0;
      b_sintab[0] = 0.0;
      for (k = 0; k < ihi; k++) {
        b_costab[k + 1] = costab1q[k + 1];
        b_sintab[k + 1] = -costab1q[(ihi - k) - 1];
      }

      iDelta2 = costab1q.size(1);
      for (k = iDelta2; k <= nd2; k++) {
        b_costab[k] = -costab1q[nd2 - k];
        b_sintab[k] = -costab1q[k - ihi];
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
      e = static_cast<double>(ju) / 2.0;
      iDelta2 = static_cast<int>(e);
      for (ix = 0; ix < iDelta2; ix++) {
        temp_re_tmp = (hnRows + ix) - 1;
        temp_re = wwc[temp_re_tmp].re;
        temp_im = wwc[temp_re_tmp].im;
        twid_re = x_data[nd2];
        twid_im = x_data[nd2 + 1];
        ytmp[ix].re = temp_re * twid_re + temp_im * twid_im;
        ytmp[ix].im = temp_re * twid_im - temp_im * twid_re;
        nd2 += 2;
      }

      if (!tst) {
        temp_re_tmp = (hnRows + static_cast<int>(e)) - 1;
        temp_re = wwc[temp_re_tmp].re;
        temp_im = wwc[temp_re_tmp].im;
        twid_re = x_data[nd2];
        ytmp[static_cast<int>(static_cast<double>(ju) / 2.0)].re = temp_re *
          twid_re + temp_im * 0.0;
        ytmp[static_cast<int>(static_cast<double>(ju) / 2.0)].im = temp_re * 0.0
          - temp_im * twid_re;
        if (static_cast<int>(e) + 2 <= hnRows) {
          iDelta2 = static_cast<int>(static_cast<double>(ju) / 2.0) + 2;
          for (i = iDelta2; i <= hnRows; i++) {
            ytmp[i - 1].re = 0.0;
            ytmp[i - 1].im = 0.0;
          }
        }
      } else {
        if (static_cast<int>(e) + 1 <= hnRows) {
          iDelta2 = static_cast<int>(static_cast<double>(ju) / 2.0) + 1;
          for (i = iDelta2; i <= hnRows; i++) {
            ytmp[i - 1].re = 0.0;
            ytmp[i - 1].im = 0.0;
          }
        }
      }

      z = static_cast<double>(nfft) / 2.0;
      fy.set_size((static_cast<int>(z)));
      if (static_cast<int>(z) > ytmp.size(0)) {
        nd2 = static_cast<int>(z);
        fy.set_size((static_cast<int>(z)));
        for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
          fy[iDelta2].re = 0.0;
          fy[iDelta2].im = 0.0;
        }
      }

      ju = ytmp.size(0);
      j = static_cast<int>(z);
      if (ju < j) {
        j = ju;
      }

      iDelta2 = static_cast<int>(z) - 2;
      nRowsD2 = static_cast<int>(z) / 2;
      k = nRowsD2 / 2;
      ix = 0;
      nd2 = 0;
      ju = 0;
      for (i = 0; i <= j - 2; i++) {
        fy[nd2] = ytmp[ix];
        ihi = static_cast<int>(z);
        tst = true;
        while (tst) {
          ihi >>= 1;
          ju ^= ihi;
          tst = ((ju & ihi) == 0);
        }

        nd2 = ju;
        ix++;
      }

      fy[nd2] = ytmp[ix];
      if (static_cast<int>(z) > 1) {
        for (i = 0; i <= iDelta2; i += 2) {
          temp_re = fy[i + 1].re;
          temp_im = fy[i + 1].im;
          e = fy[i].re;
          twid_re = fy[i].im;
          fy[i + 1].re = fy[i].re - fy[i + 1].re;
          fy[i + 1].im = fy[i].im - fy[i + 1].im;
          e += temp_re;
          twid_re += temp_im;
          fy[i].re = e;
          fy[i].im = twid_re;
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
          fy[temp_re_tmp].re = fy[i].re - temp_re;
          fy[temp_re_tmp].im = fy[i].im - temp_im;
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
            temp_re = twid_re * fy[temp_re_tmp].re - twid_im * fy[temp_re_tmp].
              im;
            temp_im = twid_re * fy[temp_re_tmp].im + twid_im * fy[temp_re_tmp].
              re;
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

      FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (static_cast<int>(z)),
        (costab1q), (hsintab), (fv));
      nd2 = fy.size(0);
      for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
        twid_re = fy[iDelta2].re * fv[iDelta2].im + fy[iDelta2].im * fv[iDelta2]
          .re;
        fy[iDelta2].re = fy[iDelta2].re * fv[iDelta2].re - fy[iDelta2].im *
          fv[iDelta2].im;
        fy[iDelta2].im = twid_re;
      }

      FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (static_cast<int>(z)),
        (hcostabinv), (hsintabinv), (fv));
      if (fv.size(0) > 1) {
        e = 1.0 / static_cast<double>(fv.size(0));
        nd2 = fv.size(0);
        for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
          fv[iDelta2].re = e * fv[iDelta2].re;
          fv[iDelta2].im = e * fv[iDelta2].im;
        }
      }

      nd2 = 0;
      iDelta2 = wwc.size(0);
      for (k = hnRows; k <= iDelta2; k++) {
        ytmp[nd2].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].
          im;
        ytmp[nd2].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].
          re;
        nd2++;
      }

      for (i = 0; i < hnRows; i++) {
        iDelta2 = wrapIndex[i];
        e = ytmp[iDelta2 - 1].re;
        twid_re = -ytmp[iDelta2 - 1].im;
        y[i].re = 0.5 * ((ytmp[i].re * reconVar1[i].re - ytmp[i].im *
                          reconVar1[i].im) + (e * reconVar2[i].re - twid_re *
          reconVar2[i].im));
        y[i].im = 0.5 * ((ytmp[i].re * reconVar1[i].im + ytmp[i].im *
                          reconVar1[i].re) + (e * reconVar2[i].im + twid_re *
          reconVar2[i].re));
        iDelta2 = hnRows + i;
        y[iDelta2].re = 0.5 * ((ytmp[i].re * reconVar2[i].re - ytmp[i].im *
          reconVar2[i].im) + (e * reconVar1[i].re - twid_re * reconVar1[i].im));
        y[iDelta2].im = 0.5 * ((ytmp[i].re * reconVar2[i].im + ytmp[i].im *
          reconVar2[i].re) + (e * reconVar1[i].im + twid_re * reconVar1[i].re));
      }
    }

    void FFTImplementationCallback::doHalfLengthRadix2(const ::coder::array<
      double, 2U> &x, int xoffInit, creal_T y_data[], int y_size[1], const
      double costab_data[], const double sintab_data[])
    {
      array<creal_T, 1U> b_reconVar1_data;
      array<creal_T, 1U> b_reconVar2_data;
      array<creal_T, 1U> y;
      array<int, 2U> wrapIndex;
      array<int, 1U> r;
      creal_T reconVar1_data[1024];
      creal_T reconVar2_data[1024];
      double hcostab_data[513];
      double hsintab_data[513];
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int bitrevIndex_data[1024];
      int i;
      int iDelta;
      int iheight;
      int ix;
      int j;
      int k;
      boolean_T nxeven;
      for (i = 0; i < 512; i++) {
        iDelta = ((i + 1) << 1) - 2;
        hcostab_data[i] = costab_data[iDelta];
        hsintab_data[i] = sintab_data[iDelta];
      }

      wrapIndex.set_size(1, 1024);
      for (i = 0; i < 1024; i++) {
        reconVar1_data[i].re = sintab_data[i] + 1.0;
        reconVar1_data[i].im = -costab_data[i];
        reconVar2_data[i].re = 1.0 - sintab_data[i];
        reconVar2_data[i].im = costab_data[i];
        if (i + 1 != 1) {
          wrapIndex[i] = 1025 - i;
        } else {
          wrapIndex[0] = 1;
        }
      }

      FFTImplementationCallback::get_bitrevIndex((1023), (1024), (r));
      iDelta = r.size(0);
      for (k = 0; k < iDelta; k++) {
        bitrevIndex_data[k] = r[k];
      }

      if ((x.size(0) & 1) == 0) {
        nxeven = true;
        iDelta = x.size(0);
      } else if (x.size(0) >= 2048) {
        nxeven = true;
        iDelta = 2048;
      } else {
        nxeven = false;
        iDelta = x.size(0) - 1;
      }

      ix = xoffInit;
      if (iDelta >= 2048) {
        iDelta = 2048;
      }

      twid_re = static_cast<double>(iDelta) / 2.0;
      k = static_cast<int>(twid_re);
      for (i = 0; i < k; i++) {
        iDelta = bitrevIndex_data[i];
        y_data[iDelta - 1].re = x[ix];
        y_data[iDelta - 1].im = x[ix + 1];
        ix += 2;
      }

      if (!nxeven) {
        k = bitrevIndex_data[static_cast<int>(twid_re)] - 1;
        y_data[k].re = x[ix];
        y_data[k].im = 0.0;
      }

      y.set_size(2048);
      for (k = 0; k < 2048; k++) {
        y[k] = y_data[k];
      }

      for (i = 0; i <= 1022; i += 2) {
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

      iDelta = 2;
      ix = 4;
      k = 256;
      iheight = 1021;
      while (k > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iDelta;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re = y[i].re + temp_re;
          y[i].im = y[i].im + temp_im;
        }

        istart = 1;
        for (j = k; j < 512; j += k) {
          int ihi;
          twid_re = hcostab_data[j];
          twid_im = hsintab_data[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iDelta;
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
        iDelta = ix;
        ix += ix;
        iheight -= iDelta;
      }

      b_reconVar1_data.set((&reconVar1_data[0]), 1024);
      b_reconVar2_data.set((&reconVar2_data[0]), 1024);
      FFTImplementationCallback::getback_radix2_fft((y), (b_reconVar1_data),
        (b_reconVar2_data), (wrapIndex), (1024));
      y_size[0] = y.size(0);
      iDelta = y.size(0);
      for (k = 0; k < iDelta; k++) {
        y_data[k] = y[k];
      }
    }

    void FFTImplementationCallback::get_bitrevIndex(int nRowsM1, int nfftLen, ::
      coder::array<int, 1U> &bitrevIndex)
    {
      int b_j1;
      int iy;
      int ju;
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

    void FFTImplementationCallback::getback_radix2_fft(::coder::array<creal_T,
      1U> &y, const ::coder::array<creal_T, 1U> &reconVar1, const ::coder::array<
      creal_T, 1U> &reconVar2, const ::coder::array<int, 2U> &wrapIndex, int
      hnRows)
    {
      double b_y_im;
      double temp1_im;
      double temp1_re;
      double temp2_im;
      double y_im;
      double y_im_tmp;
      int b_i;
      int iterVar;
      iterVar = hnRows / 2;
      temp1_re = y[0].re;
      temp1_im = y[0].im;
      y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
      temp2_im = y[0].re;
      b_y_im = -y[0].im;
      y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im) +
                       (temp2_im * reconVar2[0].re - b_y_im * reconVar2[0].im));
      y[0].im = 0.5 * (y_im + (temp2_im * reconVar2[0].im + b_y_im * reconVar2[0]
        .re));
      y[hnRows].re = 0.5 * ((temp1_re * reconVar2[0].re - temp1_im * reconVar2[0]
        .im) + (temp1_re * reconVar1[0].re - -temp1_im * reconVar1[0].im));
      y[hnRows].im = 0.5 * ((temp1_re * reconVar2[0].im + temp1_im * reconVar2[0]
        .re) + (temp1_re * reconVar1[0].im + -temp1_im * reconVar1[0].re));
      for (int i = 2; i <= iterVar; i++) {
        int i1;
        temp1_re = y[i - 1].re;
        temp1_im = y[i - 1].im;
        b_i = wrapIndex[i - 1];
        b_y_im = y[b_i - 1].re;
        temp2_im = y[b_i - 1].im;
        y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i - 1]
          .re;
        y_im_tmp = -y[b_i - 1].im;
        y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                              reconVar1[i - 1].im) + (b_y_im * reconVar2[i - 1].
          re - y_im_tmp * reconVar2[i - 1].im));
        y[i - 1].im = 0.5 * (y_im + (b_y_im * reconVar2[i - 1].im + y_im_tmp *
          reconVar2[i - 1].re));
        i1 = (hnRows + i) - 1;
        y[i1].re = 0.5 * ((temp1_re * reconVar2[i - 1].re - temp1_im *
                           reconVar2[i - 1].im) + (b_y_im * reconVar1[i - 1].re
          - -temp2_im * reconVar1[i - 1].im));
        y[i1].im = 0.5 * ((temp1_re * reconVar2[i - 1].im + temp1_im *
                           reconVar2[i - 1].re) + (b_y_im * reconVar1[i - 1].im
          + -temp2_im * reconVar1[i - 1].re));
        y[b_i - 1].re = 0.5 * ((b_y_im * reconVar1[b_i - 1].re - temp2_im *
          reconVar1[b_i - 1].im) + (temp1_re * reconVar2[b_i - 1].re - -temp1_im
          * reconVar2[b_i - 1].im));
        y[b_i - 1].im = 0.5 * ((b_y_im * reconVar1[b_i - 1].im + temp2_im *
          reconVar1[b_i - 1].re) + (temp1_re * reconVar2[b_i - 1].im + -temp1_im
          * reconVar2[b_i - 1].re));
        i1 = (b_i + hnRows) - 1;
        y[i1].re = 0.5 * ((b_y_im * reconVar2[b_i - 1].re - temp2_im *
                           reconVar2[b_i - 1].im) + (temp1_re * reconVar1[b_i -
          1].re - -temp1_im * reconVar1[b_i - 1].im));
        y[i1].im = 0.5 * ((b_y_im * reconVar2[b_i - 1].im + temp2_im *
                           reconVar2[b_i - 1].re) + (temp1_re * reconVar1[b_i -
          1].im + -temp1_im * reconVar1[b_i - 1].re));
      }

      if (iterVar != 0) {
        temp2_im = y[iterVar].re;
        temp1_im = y[iterVar].im;
        y_im = y[iterVar].re * reconVar1[iterVar].im + y[iterVar].im *
          reconVar1[iterVar].re;
        y_im_tmp = -y[iterVar].im;
        y[iterVar].re = 0.5 * ((y[iterVar].re * reconVar1[iterVar].re -
          y[iterVar].im * reconVar1[iterVar].im) + (temp2_im * reconVar2[iterVar]
          .re - y_im_tmp * reconVar2[iterVar].im));
        y[iterVar].im = 0.5 * (y_im + (temp2_im * reconVar2[iterVar].im +
          y_im_tmp * reconVar2[iterVar].re));
        b_i = hnRows + iterVar;
        y[b_i].re = 0.5 * ((temp2_im * reconVar2[iterVar].re - temp1_im *
                            reconVar2[iterVar].im) + (temp2_im *
          reconVar1[iterVar].re - -temp1_im * reconVar1[iterVar].im));
        y[b_i].im = 0.5 * ((temp2_im * reconVar2[iterVar].im + temp1_im *
                            reconVar2[iterVar].re) + (temp2_im *
          reconVar1[iterVar].im + -temp1_im * reconVar1[iterVar].re));
      }
    }

    void FFTImplementationCallback::doHalfLengthRadix2(const double x[4096],
      creal_T y[4096])
    {
      static const creal_T reconVar1[2048] = { { 1.0,// re
          -1.0                         // im
        }, { 0.99846601981371519,      // re
          -0.99999882345170188         // im
        }, { 0.996932043237034,        // re
          -0.99999529380957619         // im
        }, { 0.99539807387955148,      // re
          -0.9999894110819284          // im
        }, { 0.99386411535084551,      // re
          -0.99998117528260111         // im
        }, { 0.99233017126046885,      // re
          -0.99997058643097414         // im
        }, { 0.99079624521794019,      // re
          -0.9999576445519639          // im
        }, { 0.98926234083273545,      // re
          -0.99994234967602391         // im
        }, { 0.98772846171428008,      // re
          -0.9999247018391445          // im
        }, { 0.98619461147193965,      // re
          -0.9999047010828529          // im
        }, { 0.98466079371501192,      // re
          -0.99988234745421256         // im
        }, { 0.98312701205271824,      // re
          -0.99985764100582386         // im
        }, { 0.98159327009419517,      // re
          -0.9998305817958234          // im
        }, { 0.98005957144848554,      // re
          -0.99980116988788426         // im
        }, { 0.97852591972453051,      // re
          -0.99976940535121528         // im
        }, { 0.97699231853116064,      // re
          -0.99973528826056168         // im
        }, { 0.9754587714770877,       // re
          -0.99969881869620425         // im
        }, { 0.97392528217089613,      // re
          -0.99965999674395922         // im
        }, { 0.97239185422103425,      // re
          -0.99961882249517864         // im
        }, { 0.97085849123580625,      // re
          -0.99957529604674922         // im
        }, { 0.96932519682336338,      // re
          -0.99952941750109314         // im
        }, { 0.96779197459169541,      // re
          -0.999481186966167           // im
        }, { 0.96625882814862241,      // re
          -0.99943060455546173         // im
        }, { 0.96472576110178609,      // re
          -0.99937767038800285         // im
        }, { 0.96319277705864115,      // re
          -0.99932238458834954         // im
        }, { 0.96165987962644728,      // re
          -0.99926474728659442         // im
        }, { 0.96012707241226014,      // re
          -0.99920475861836389         // im
        }, { 0.95859435902292323,      // re
          -0.99914241872481691         // im
        }, { 0.9570617430650592,       // re
          -0.99907772775264536         // im
        }, { 0.95552922814506136,      // re
          -0.99901068585407338         // im
        }, { 0.95399681786908541,      // re
          -0.99894129318685687         // im
        }, { 0.9524645158430407,       // re
          -0.99886954991428356         // im
        }, { 0.950932325672582,        // re
          -0.99879545620517241         // im
        }, { 0.94940025096310077,      // re
          -0.99871901223387294         // im
        }, { 0.94786829531971672,      // re
          -0.99864021818026527         // im
        }, { 0.94633646234726942,      // re
          -0.99855907422975931         // im
        }, { 0.94480475565031008,      // re
          -0.99847558057329477         // im
        }, { 0.94327317883309225,      // re
          -0.99838973740734016         // im
        }, { 0.9417417354995643,       // re
          -0.99830154493389289         // im
        }, { 0.94021042925336018,      // re
          -0.99821100336047819         // im
        }, { 0.93867926369779142,      // re
          -0.99811811290014918         // im
        }, { 0.93714824243583861,      // re
          -0.99802287377148624         // im
        }, { 0.93561736907014259,      // re
          -0.997925286198596           // im
        }, { 0.93408664720299617,      // re
          -0.99782535041111164         // im
        }, { 0.932556080436336,        // re
          -0.99772306664419164         // im
        }, { 0.93102567237173328,      // re
          -0.99761843513851955         // im
        }, { 0.92949542661038609,      // re
          -0.99751145614030345         // im
        }, { 0.92796534675311071,      // re
          -0.9974021299012753          // im
        }, { 0.92643543640033255,      // re
          -0.99729045667869021         // im
        }, { 0.92490569915207865,      // re
          -0.99717643673532619         // im
        }, { 0.92337613860796852,      // re
          -0.997060070339483           // im
        }, { 0.92184675836720575,      // re
          -0.99694135776498216         // im
        }, { 0.92031756202856985,      // re
          -0.99682029929116567         // im
        }, { 0.91878855319040753,      // re
          -0.99669689520289606         // im
        }, { 0.91725973545062434,      // re
          -0.99657114579055484         // im
        }, { 0.91573111240667593,      // re
          -0.99644305135004263         // im
        }, { 0.91420268765556012,      // re
          -0.996312612182778           // im
        }, { 0.912674464793808,        // re
          -0.996179828595697           // im
        }, { 0.91114644741747541,      // re
          -0.996044700901252           // im
        }, { 0.909618639122135,        // re
          -0.99590722941741172         // im
        }, { 0.90809104350286729,      // re
          -0.99576741446765982         // im
        }, { 0.90656366415425227,      // re
          -0.99562525638099431         // im
        }, { 0.905036504670361,        // re
          -0.99548075549192694         // im
        }, { 0.90350956864474741,      // re
          -0.99533391214048228         // im
        }, { 0.90198285967043934,      // re
          -0.99518472667219693         // im
        }, { 0.90045638133993067,      // re
          -0.99503319943811863         // im
        }, { 0.89893013724517212,      // re
          -0.99487933079480562         // im
        }, { 0.89740413097756377,      // re
          -0.9947231211043257          // im
        }, { 0.89587836612794547,      // re
          -0.99456457073425542         // im
        }, { 0.8943528462865894,       // re
          -0.9944036800576791          // im
        }, { 0.8928275750431911,       // re
          -0.9942404494531879          // im
        }, { 0.89130255598686126,      // re
          -0.99407487930487937         // im
        }, { 0.8897777927061169,       // re
          -0.99390697000235606         // im
        }, { 0.88825328878887344,      // re
          -0.9937367219407246          // im
        }, { 0.88672904782243567,      // re
          -0.9935641355205953          // im
        }, { 0.88520507339349,         // re
          -0.99338921114808065         // im
        }, { 0.88368136908809525,      // re
          -0.9932119492347945          // im
        }, { 0.882157938491675,        // re
          -0.99303235019785141         // im
        }, { 0.88063478518900862,      // re
          -0.9928504144598651          // im
        }, { 0.879111912764223,        // re
          -0.992666142448948           // im
        }, { 0.87758932480078378,      // re
          -0.99247953459871            // im
        }, { 0.8760670248814878,       // re
          -0.99229059134825737         // im
        }, { 0.87454501658845374,      // re
          -0.9920993131421918          // im
        }, { 0.87302330350311408,      // re
          -0.99190570043060933         // im
        }, { 0.87150188920620686,      // re
          -0.99170975366909953         // im
        }, { 0.86998077727776668,      // re
          -0.9915114733187439          // im
        }, { 0.86845997129711683,      // re
          -0.99131085984611544         // im
        }, { 0.86693947484286094,      // re
          -0.99110791372327689         // im
        }, { 0.86541929149287378,      // re
          -0.99090263542778            // im
        }, { 0.86389942482429383,      // re
          -0.99069502544266463         // im
        }, { 0.86237987841351393,      // re
          -0.99048508425645709         // im
        }, { 0.86086065583617377,      // re
          -0.99027281236316911         // im
        }, { 0.85934176066715073,      // re
          -0.99005821026229712         // im
        }, { 0.85782319648055194,      // re
          -0.98984127845882053         // im
        }, { 0.85630496684970558,      // re
          -0.98962201746320089         // im
        }, { 0.85478707534715248,      // re
          -0.98940042779138038         // im
        }, { 0.85326952554463831,      // re
          -0.989176509964781           // im
        }, { 0.85175232101310394,      // re
          -0.988950264510303           // im
        }, { 0.85023546532267846,      // re
          -0.98872169196032378         // im
        }, { 0.84871896204266983,      // re
          -0.98849079285269659         // im
        }, { 0.84720281474155656,      // re
          -0.98825756773074946         // im
        }, { 0.84568702698697984,      // re
          -0.98802201714328353         // im
        }, { 0.84417160234573474,      // re
          -0.98778414164457218         // im
        }, { 0.8426565443837617,       // re
          -0.98754394179435923         // im
        }, { 0.84114185666613861,      // re
          -0.98730141815785843         // im
        }, { 0.83962754275707174,      // re
          -0.987056571305751           // im
        }, { 0.83811360621988817,      // re
          -0.98680940181418553         // im
        }, { 0.8366000506170268,       // re
          -0.98655991026477541         // im
        }, { 0.83508687951003013,      // re
          -0.98630809724459867         // im
        }, { 0.833574096459536,        // re
          -0.98605396334619544         // im
        }, { 0.83206170502526877,      // re
          -0.98579750916756748         // im
        }, { 0.83054970876603207,      // re
          -0.98553873531217606         // im
        }, { 0.82903811123969873,      // re
          -0.98527764238894122         // im
        }, { 0.827526916003204,        // re
          -0.98501423101223984         // im
        }, { 0.82601612661253621,      // re
          -0.98474850180190421         // im
        }, { 0.82450574662272857,      // re
          -0.98448045538322093         // im
        }, { 0.82299577958785131,      // re
          -0.984210092386929           // im
        }, { 0.82148622906100255,      // re
          -0.98393741344921892         // im
        }, { 0.81997709859430046,      // re
          -0.98366241921173025         // im
        }, { 0.81846839173887509,      // re
          -0.98338511032155118         // im
        }, { 0.81696011204485908,      // re
          -0.98310548743121629         // im
        }, { 0.81545226306138041,      // re
          -0.98282355119870524         // im
        }, { 0.81394484833655334,      // re
          -0.98253930228744124         // im
        }, { 0.81243787141747037,      // re
          -0.98225274136628937         // im
        }, { 0.81093133585019384,      // re
          -0.98196386910955524         // im
        }, { 0.80942524517974723,      // re
          -0.98167268619698311         // im
        }, { 0.80791960295010756,      // re
          -0.98137919331375456         // im
        }, { 0.80641441270419634,      // re
          -0.98108339115048671         // im
        }, { 0.80490967798387181,      // re
          -0.98078528040323043         // im
        }, { 0.80340540232991975,      // re
          -0.98048486177346938         // im
        }, { 0.80190158928204647,      // re
          -0.98018213596811743         // im
        }, { 0.800398242378869,        // re
          -0.97987710369951764         // im
        }, { 0.798895365157908,        // re
          -0.97956976568544052         // im
        }, { 0.79739296115557889,      // re
          -0.979260122649082           // im
        }, { 0.79589103390718319,      // re
          -0.9789481753190622          // im
        }, { 0.79438958694690076,      // re
          -0.97863392442942321         // im
        }, { 0.79288862380778147,      // re
          -0.97831737071962765         // im
        }, { 0.79138814802173651,      // re
          -0.97799851493455714         // im
        }, { 0.78988816311953036,      // re
          -0.97767735782450993         // im
        }, { 0.7883886726307725,       // re
          -0.97735390014520007         // im
        }, { 0.78688968008390869,      // re
          -0.97702814265775439         // im
        }, { 0.7853911890062133,       // re
          -0.97670008612871184         // im
        }, { 0.78389320292378051,      // re
          -0.97636973133002114         // im
        }, { 0.78239572536151636,      // re
          -0.976037079039039           // im
        }, { 0.78089875984313017,      // re
          -0.97570213003852857         // im
        }, { 0.77940230989112647,      // re
          -0.975364885116657           // im
        }, { 0.77790637902679649,      // re
          -0.97502534506699412         // im
        }, { 0.77641097077021,         // re
          -0.97468351068851067         // im
        }, { 0.77491608864020711,      // re
          -0.97433938278557586         // im
        }, { 0.77342173615439,         // re
          -0.97399296216795583         // im
        }, { 0.77192791682911421,      // re
          -0.973644249650812           // im
        }, { 0.7704346341794811,       // re
          -0.97329324605469825         // im
        }, { 0.76894189171932892,      // re
          -0.97293995220556018         // im
        }, { 0.76744969296122478,      // re
          -0.97258436893473221         // im
        }, { 0.76595804141645663,      // re
          -0.97222649707893627         // im
        }, { 0.76446694059502451,      // re
          -0.9718663374802794          // im
        }, { 0.76297639400563277,      // re
          -0.97150389098625178         // im
        }, { 0.76148640515568156,      // re
          -0.97113915844972509         // im
        }, { 0.7599969775512585,       // re
          -0.97077214072895035         // im
        }, { 0.75850811469713064,      // re
          -0.9704028386875555          // im
        }, { 0.75701982009673618,      // re
          -0.970031253194544           // im
        }, { 0.75553209725217585,      // re
          -0.96965738512429245         // im
        }, { 0.75404494966420543,      // re
          -0.96928123535654853         // im
        }, { 0.7525583808322267,       // re
          -0.96890280477642887         // im
        }, { 0.75107239425427985,      // re
          -0.96852209427441727         // im
        }, { 0.74958699342703472,      // re
          -0.96813910474636244         // im
        }, { 0.748102181845783,        // re
          -0.96775383709347551         // im
        }, { 0.74661796300442984,      // re
          -0.96736629222232851         // im
        }, { 0.74513434039548543,      // re
          -0.96697647104485207         // im
        }, { 0.74365131751005709,      // re
          -0.96658437447833312         // im
        }, { 0.742168897837841,        // re
          -0.9661900034454125          // im
        }, { 0.74068708486711377,      // re
          -0.96579335887408368         // im
        }, { 0.73920588208472449,      // re
          -0.9653944416976894          // im
        }, { 0.73772529297608647,      // re
          -0.96499325285492032         // im
        }, { 0.73624532102516871,      // re
          -0.96458979328981276         // im
        }, { 0.73476596971448815,      // re
          -0.96418406395174583         // im
        }, { 0.73328724252510158,      // re
          -0.96377606579543984         // im
        }, { 0.73180914293659682,      // re
          -0.963365799780954           // im
        }, { 0.73033167442708491,      // re
          -0.96295326687368388         // im
        }, { 0.728854840473192,        // re
          -0.96253846804435916         // im
        }, { 0.727378644550051,        // re
          -0.96212140426904158         // im
        }, { 0.72590309013129362,      // re
          -0.96170207652912254         // im
        }, { 0.7244281806890418,       // re
          -0.96128048581132064         // im
        }, { 0.7229539196939001,       // re
          -0.96085663310767966         // im
        }, { 0.721480310614947,        // re
          -0.96043051941556579         // im
        }, { 0.72000735691972673,      // re
          -0.960002145737666           // im
        }, { 0.71853506207424211,      // re
          -0.95957151308198452         // im
        }, { 0.71706342954294455,      // re
          -0.95913862246184189         // im
        }, { 0.71559246278872812,      // re
          -0.9587034748958716          // im
        }, { 0.71412216527291938,      // re
          -0.95826607140801767         // im
        }, { 0.71265254045527049,      // re
          -0.95782641302753291         // im
        }, { 0.71118359179395052,      // re
          -0.95738450078897586         // im
        }, { 0.70971532274553772,      // re
          -0.95694033573220882         // im
        }, { 0.70824773676501074,      // re
          -0.9564939189023951          // im
        }, { 0.70678083730574137,      // re
          -0.95604525134999641         // im
        }, { 0.70531462781948573,      // re
          -0.95559433413077111         // im
        }, { 0.70384911175637621,      // re
          -0.95514116830577078         // im
        }, { 0.70238429256491375,      // re
          -0.95468575494133834         // im
        }, { 0.70092017369195947,      // re
          -0.95422809510910567         // im
        }, { 0.69945675858272649,      // re
          -0.95376818988599033         // im
        }, { 0.69799405068077192,      // re
          -0.95330604035419386         // im
        }, { 0.69653205342798863,      // re
          -0.95284164760119872         // im
        }, { 0.69507077026459763,      // re
          -0.95237501271976588         // im
        }, { 0.693610204629139,        // re
          -0.95190613680793235         // im
        }, { 0.69215035995846508,      // re
          -0.95143502096900834         // im
        }, { 0.69069123968773127,      // re
          -0.95096166631157508         // im
        }, { 0.68923284725038858,      // re
          -0.9504860739494817          // im
        }, { 0.68777518607817512,      // re
          -0.950008245001843           // im
        }, { 0.68631825960110848,      // re
          -0.94952818059303667         // im
        }, { 0.68486207124747756,      // re
          -0.94904588185270056         // im
        }, { 0.68340662444383415,      // re
          -0.94856134991573027         // im
        }, { 0.681951922614985,        // re
          -0.94807458592227623         // im
        }, { 0.68049796918398431,      // re
          -0.94758559101774109         // im
        }, { 0.67904476757212473,      // re
          -0.94709436635277722         // im
        }, { 0.67759232119893009,      // re
          -0.94660091308328353         // im
        }, { 0.67614063348214715,      // re
          -0.94610523237040345         // im
        }, { 0.67468970783773707,      // re
          -0.94560732538052128         // im
        }, { 0.67323954767986827,      // re
          -0.94510719328526061         // im
        }, { 0.67179015642090745,      // re
          -0.94460483726148026         // im
        }, { 0.67034153747141256,      // re
          -0.94410025849127266         // im
        }, { 0.66889369424012357,      // re
          -0.94359345816196039         // im
        }, { 0.66744663013395578,      // re
          -0.94308443746609349         // im
        }, { 0.66600034855799062,      // re
          -0.94257319760144687         // im
        }, { 0.66455485291546834,      // re
          -0.94205973977101731         // im
        }, { 0.66311014660778,         // re
          -0.94154406518302081         // im
        }, { 0.66166623303445893,      // re
          -0.94102617505088926         // im
        }, { 0.66022311559317315,      // re
          -0.9405060705932683          // im
        }, { 0.65878079767971764,      // re
          -0.93998375303401394         // im
        }, { 0.65733928268800557,      // re
          -0.93945922360218992         // im
        }, { 0.65589857401006113,      // re
          -0.9389324835320646          // im
        }, { 0.65445867503601085,      // re
          -0.93840353406310806         // im
        }, { 0.65301958915407632,      // re
          -0.93787237643998989         // im
        }, { 0.65158131975056544,      // re
          -0.937339011912575           // im
        }, { 0.65014387020986508,      // re
          -0.93680344173592156         // im
        }, { 0.64870724391443291,      // re
          -0.93626566717027826         // im
        }, { 0.64727144424478933,      // re
          -0.93572568948108037         // im
        }, { 0.64583647457950966,      // re
          -0.93518350993894761         // im
        }, { 0.6444023382952162,       // re
          -0.93463912981968078         // im
        }, { 0.64296903876657008,      // re
          -0.93409255040425887         // im
        }, { 0.64153657936626352,      // re
          -0.93354377297883617         // im
        }, { 0.64010496346501189,      // re
          -0.932992798834739           // im
        }, { 0.63867419443154572,      // re
          -0.93243962926846236         // im
        }, { 0.63724427563260277,      // re
          -0.93188426558166815         // im
        }, { 0.63581521043292011,      // re
          -0.93132670908118043         // im
        }, { 0.63438700219522615,      // re
          -0.93076696107898371         // im
        }, { 0.63295965428023282,      // re
          -0.93020502289221907         // im
        }, { 0.63153317004662768,      // re
          -0.92964089584318121         // im
        }, { 0.6301075528510659,       // re
          -0.92907458125931586         // im
        }, { 0.62868280604816251,      // re
          -0.92850608047321559         // im
        }, { 0.6272589329904843,       // re
          -0.92793539482261789         // im
        }, { 0.625835937028542,        // re
          -0.92736252565040111         // im
        }, { 0.62441382151078284,      // re
          -0.92678747430458175         // im
        }, { 0.62299258978358174,      // re
          -0.92621024213831138         // im
        }, { 0.62157224519123444,      // re
          -0.92563083050987272         // im
        }, { 0.62015279107594878,      // re
          -0.92504924078267758         // im
        }, { 0.61873423077783762,      // re
          -0.9244654743252626          // im
        }, { 0.61731656763491016,      // re
          -0.92387953251128674         // im
        }, { 0.615899804983065,        // re
          -0.92329141671952764         // im
        }, { 0.61448394615608115,      // re
          -0.92270112833387863         // im
        }, { 0.61306899448561136,      // re
          -0.92210866874334518         // im
        }, { 0.6116549533011737,       // re
          -0.9215140393420419          // im
        }, { 0.61024182593014364,      // re
          -0.92091724152918952         // im
        }, { 0.60882961569774618,      // re
          -0.92031827670911059         // im
        }, { 0.60741832592704847,      // re
          -0.91971714629122736         // im
        }, { 0.60600795993895185,      // re
          -0.91911385169005777         // im
        }, { 0.60459852105218359,      // re
          -0.91850839432521225         // im
        }, { 0.60319001258328964,      // re
          -0.9179007756213905          // im
        }, { 0.60178243784662644,      // re
          -0.91729099700837791         // im
        }, { 0.60037580015435321,      // re
          -0.9166790599210427          // im
        }, { 0.59897010281642438,      // re
          -0.91606496579933172         // im
        }, { 0.59756534914058157,      // re
          -0.91544871608826783         // im
        }, { 0.59616154243234587,      // re
          -0.9148303122379462          // im
        }, { 0.59475868599501014,      // re
          -0.91420975570353069         // im
        }, { 0.59335678312963092,      // re
          -0.91358704794525081         // im
        }, { 0.59195583713502131,      // re
          -0.91296219042839821         // im
        }, { 0.59055585130774246,      // re
          -0.91233518462332275         // im
        }, { 0.58915682894209609,      // re
          -0.91170603200542988         // im
        }, { 0.58775877333011706,      // re
          -0.91107473405517636         // im
        }, { 0.5863616877615655,       // re
          -0.91044129225806725         // im
        }, { 0.58496557552391837,      // re
          -0.90980570810465222         // im
        }, { 0.5835704399023629,       // re
          -0.90916798309052238         // im
        }, { 0.58217628417978773,      // re
          -0.90852811871630612         // im
        }, { 0.58078311163677609,      // re
          -0.90788611648766626         // im
        }, { 0.57939092555159744,      // re
          -0.90724197791529582         // im
        }, { 0.57799972920020037,      // re
          -0.90659570451491533         // im
        }, { 0.576609525856204,        // re
          -0.90594729780726846         // im
        }, { 0.57522031879089119,      // re
          -0.90529675931811882         // im
        }, { 0.57383211127320033,      // re
          -0.90464409057824624         // im
        }, { 0.57244490656971792,      // re
          -0.90398929312344334         // im
        }, { 0.57105870794467051,      // re
          -0.90333236849451182         // im
        }, { 0.56967351865991733,      // re
          -0.90267331823725883         // im
        }, { 0.56828934197494274,      // re
          -0.90201214390249318         // im
        }, { 0.5669061811468481,       // re
          -0.901348847046022           // im
        }, { 0.56552403943034435,      // re
          -0.900683429228647           // im
        }, { 0.56414292007774458,      // re
          -0.90001589201616017         // im
        }, { 0.56276282633895591,      // re
          -0.89934623697934157         // im
        }, { 0.56138376146147229,      // re
          -0.89867446569395382         // im
        }, { 0.5600057286903668,       // re
          -0.89800057974073988         // im
        }, { 0.55862873126828338,      // re
          -0.89732458070541832         // im
        }, { 0.55725277243542992,      // re
          -0.89664647017868015         // im
        }, { 0.5558778554295708,       // re
          -0.89596624975618522         // im
        }, { 0.55450398348601826,      // re
          -0.89528392103855758         // im
        }, { 0.55313115983762584,      // re
          -0.8945994856313827          // im
        }, { 0.55175938771478017,      // re
          -0.89391294514520325         // im
        }, { 0.55038867034539352,      // re
          -0.89322430119551532         // im
        }, { 0.54901901095489614,      // re
          -0.89253355540276458         // im
        }, { 0.54765041276622917,      // re
          -0.89184070939234272         // im
        }, { 0.54628287899983619,      // re
          -0.89114576479458318         // im
        }, { 0.54491641287365611,      // re
          -0.89044872324475788         // im
        }, { 0.54355101760311608,      // re
          -0.88974958638307278         // im
        }, { 0.54218669640112283,      // re
          -0.88904835585466457         // im
        }, { 0.540823452478056,        // re
          -0.88834503330959635         // im
        }, { 0.53946128904176,         // re
          -0.88763962040285393         // im
        }, { 0.53810020929753732,      // re
          -0.88693211879434219         // im
        }, { 0.53674021644813985,      // re
          -0.88622253014888064         // im
        }, { 0.53538131369376218,      // re
          -0.8855108561362             // im
        }, { 0.53402350423203382,      // re
          -0.88479709843093779         // im
        }, { 0.53266679125801164,      // re
          -0.884081258712635           // im
        }, { 0.531311177964172,        // re
          -0.88336333866573158         // im
        }, { 0.52995666754040438,      // re
          -0.88264333997956279         // im
        }, { 0.5286032631740023,       // re
          -0.881921264348355           // im
        }, { 0.52725096804965721,      // re
          -0.88119711347122209         // im
        }, { 0.52589978534945,         // re
          -0.88047088905216075         // im
        }, { 0.52454971825284413,      // re
          -0.87974259280004741         // im
        }, { 0.52320076993667786,      // re
          -0.87901222642863353         // im
        }, { 0.521852943575157,        // re
          -0.87827979165654158         // im
        }, { 0.520506242339847,        // re
          -0.87754529020726135         // im
        }, { 0.519160669399666,        // re
          -0.87680872380914565         // im
        }, { 0.51781622792087734,      // re
          -0.8760700941954066          // im
        }, { 0.51647292106708131,      // re
          -0.87532940310411089         // im
        }, { 0.515130751999209,        // re
          -0.87458665227817611         // im
        }, { 0.51378972387551358,      // re
          -0.87384184346536686         // im
        }, { 0.512449839851564,        // re
          -0.87309497841829009         // im
        }, { 0.51111110308023688,      // re
          -0.87234605889439154         // im
        }, { 0.50977351671170879,      // re
          -0.87159508665595109         // im
        }, { 0.5084370838934501,       // re
          -0.870842063470079           // im
        }, { 0.507101807770216,        // re
          -0.87008699110871146         // im
        }, { 0.50576769148404033,      // re
          -0.86932987134860684         // im
        }, { 0.50443473817422746,      // re
          -0.8685707059713409          // im
        }, { 0.50310295097734548,      // re
          -0.86780949676330332         // im
        }, { 0.50177233302721813,      // re
          -0.86704624551569265         // im
        }, { 0.50044288745491816,      // re
          -0.866280954024513           // im
        }, { 0.49911461738875929,      // re
          -0.86551362409056909         // im
        }, { 0.49778752595428921,      // re
          -0.86474425751946238         // im
        }, { 0.49646161627428242,      // re
          -0.8639728561215867          // im
        }, { 0.49513689146873241,      // re
          -0.86319942171212416         // im
        }, { 0.49381335465484477,      // re
          -0.8624239561110405          // im
        }, { 0.49249100894702913,      // re
          -0.8616464611430813          // im
        }, { 0.491169857456893,        // re
          -0.86086693863776731         // im
        }, { 0.48984990329323319,      // re
          -0.86008539042939014         // im
        }, { 0.4885311495620297,       // re
          -0.85930181835700847         // im
        }, { 0.48721359936643704,      // re
          -0.85851622426444274         // im
        }, { 0.48589725580677834,      // re
          -0.85772861000027212         // im
        }, { 0.48458212198053707,      // re
          -0.85693897741782876         // im
        }, { 0.48326820098235013,      // re
          -0.85614732837519447         // im
        }, { 0.48195549590400066,      // re
          -0.855353664735196           // im
        }, { 0.48064400983441036,      // re
          -0.85455798836540053         // im
        }, { 0.47933374585963284,      // re
          -0.85376030113811141         // im
        }, { 0.47802470706284561,      // re
          -0.85296060493036363         // im
        }, { 0.47671689652434357,      // re
          -0.85215890162391983         // im
        }, { 0.47541031732153105,      // re
          -0.8513551931052652          // im
        }, { 0.47410497252891537,      // re
          -0.85054948126560348         // im
        }, { 0.47280086521809872,      // re
          -0.84974176800085255         // im
        }, { 0.47149799845777152,      // re
          -0.84893205521163961         // im
        }, { 0.47019637531370539,      // re
          -0.84812034480329723         // im
        }, { 0.468895998848745,        // re
          -0.84730663868585832         // im
        }, { 0.4675968721228021,       // re
          -0.84649093877405213         // im
        }, { 0.46629899819284704,      // re
          -0.84567324698729907         // im
        }, { 0.46500238011290285,      // re
          -0.84485356524970712         // im
        }, { 0.46370702093403682,      // re
          -0.84403189549006641         // im
        }, { 0.46241292370435461,      // re
          -0.84320823964184544         // im
        }, { 0.46112009146899158,      // re
          -0.84238259964318585         // im
        }, { 0.45982852727010715,      // re
          -0.84155497743689844         // im
        }, { 0.45853823414687656,      // re
          -0.84072537497045807         // im
        }, { 0.45724921513548411,      // re
          -0.83989379419599952         // im
        }, { 0.45596147326911618,      // re
          -0.83906023707031274         // im
        }, { 0.45467501157795354,      // re
          -0.83822470555483808         // im
        }, { 0.45338983308916514,      // re
          -0.83738720161566194         // im
        }, { 0.45210594082689981,      // re
          -0.836547727223512           // im
        }, { 0.45082333781228034,      // re
          -0.8357062843537526          // im
        }, { 0.44954202706339519,      // re
          -0.83486287498638            // im
        }, { 0.44826201159529266,      // re
          -0.83401750110601813         // im
        }, { 0.44698329441997253,      // re
          -0.83317016470191319         // im
        }, { 0.44570587854638,         // re
          -0.83232086776792968         // im
        }, { 0.44442976698039782,      // re
          -0.83146961230254524         // im
        }, { 0.4431549627248399,       // re
          -0.83061640030884631         // im
        }, { 0.4418814687794439,       // re
          -0.829761233794523           // im
        }, { 0.44060928814086386,      // re
          -0.82890411477186487         // im
        }, { 0.43933842380266397,      // re
          -0.8280450452577558          // im
        }, { 0.43806887875531064,      // re
          -0.82718402727366913         // im
        }, { 0.43680065598616591,      // re
          -0.82632106284566353         // im
        }, { 0.4355337584794805,       // re
          -0.82545615400437755         // im
        }, { 0.43426818921638688,      // re
          -0.82458930278502529         // im
        }, { 0.43300395117489132,      // re
          -0.82372051122739143         // im
        }, { 0.43174104732986851,      // re
          -0.82284978137582643         // im
        }, { 0.43047948065305286,      // re
          -0.82197711527924155         // im
        }, { 0.42921925411303274,      // re
          -0.82110251499110465         // im
        }, { 0.42796037067524295,      // re
          -0.82022598256943469         // im
        }, { 0.4267028333019578,       // re
          -0.819347520076797           // im
        }, { 0.42544664495228424,      // re
          -0.81846712958029866         // im
        }, { 0.42419180858215466,      // re
          -0.81758481315158371         // im
        }, { 0.42293832714432056,      // re
          -0.81670057286682785         // im
        }, { 0.42168620358834441,      // re
          -0.81581441080673378         // im
        }, { 0.42043544086059437,      // re
          -0.81492632905652662         // im
        }, { 0.41918604190423547,      // re
          -0.81403632970594841         // im
        }, { 0.41793800965922456,      // re
          -0.81314441484925359         // im
        }, { 0.41669134706230171,      // re
          -0.81225058658520388         // im
        }, { 0.41544605704698467,      // re
          -0.81135484701706373         // im
        }, { 0.41420214254356114,      // re
          -0.81045719825259477         // im
        }, { 0.41295960647908203,      // re
          -0.80955764240405126         // im
        }, { 0.41171845177735478,      // re
          -0.808656181588175           // im
        }, { 0.41047868135893606,      // re
          -0.80775281792619036         // im
        }, { 0.40924029814112584,      // re
          -0.80684755354379933         // im
        }, { 0.408003305037959,        // re
          -0.80594039057117628         // im
        }, { 0.4067677049602002,       // re
          -0.80503133114296366         // im
        }, { 0.40553350081533557,      // re
          -0.8041203773982657          // im
        }, { 0.40430069550756664,      // re
          -0.80320753148064494         // im
        }, { 0.40306929193780361,      // re
          -0.80229279553811572         // im
        }, { 0.40183929300365762,      // re
          -0.80137617172314024         // im
        }, { 0.40061070159943546,      // re
          -0.80045766219262282         // im
        }, { 0.399383520616131,        // re
          -0.799537269107905           // im
        }, { 0.39815775294142,         // re
          -0.79861499463476093         // im
        }, { 0.39693340145965184,      // re
          -0.79769084094339116         // im
        }, { 0.39571046905184404,      // re
          -0.79676481020841883         // im
        }, { 0.39448895859567445,      // re
          -0.79583690460888357         // im
        }, { 0.39326887296547552,      // re
          -0.794907126328237           // im
        }, { 0.39205021503222637,      // re
          -0.79397547755433717         // im
        }, { 0.39083298766354679,      // re
          -0.79304196047944364         // im
        }, { 0.38961719372369052,      // re
          -0.79210657730021239         // im
        }, { 0.38840283607353809,      // re
          -0.7911693302176902          // im
        }, { 0.38718991757059029,      // re
          -0.79023022143731            // im
        }, { 0.38597844106896151,      // re
          -0.78928925316888565         // im
        }, { 0.38476840941937318,      // re
          -0.78834642762660634         // im
        }, { 0.38355982546914635,      // re
          -0.78740174702903143         // im
        }, { 0.38235269206219613,      // re
          -0.78645521359908577         // im
        }, { 0.38114701203902368,      // re
          -0.78550682956405393         // im
        }, { 0.3799427882367109,       // re
          -0.78455659715557524         // im
        }, { 0.37874002348891245,      // re
          -0.78360451860963831         // im
        }, { 0.37753872062585003,      // re
          -0.78265059616657573         // im
        }, { 0.37633888247430547,      // re
          -0.78169483207105939         // im
        }, { 0.37514051185761366,      // re
          -0.78073722857209449         // im
        }, { 0.37394361159565648,      // re
          -0.77977778792301455         // im
        }, { 0.37274818450485592,      // re
          -0.778816512381476           // im
        }, { 0.3715542333981674,       // re
          -0.77785340420945315         // im
        }, { 0.370361761085073,        // re
          -0.77688846567323244         // im
        }, { 0.36917077037157553,      // re
          -0.77592169904340769         // im
        }, { 0.36798126406019094,      // re
          -0.77495310659487393         // im
        }, { 0.36679324494994281,      // re
          -0.7739826906068229          // im
        }, { 0.36560671583635451,      // re
          -0.773010453362737           // im
        }, { 0.36442167951144389,      // re
          -0.77203639715038452         // im
        }, { 0.3632381387637158,       // re
          -0.77106052426181382         // im
        }, { 0.36205609637815594,      // re
          -0.7700828369933479          // im
        }, { 0.36087555513622427,      // re
          -0.7691033376455797          // im
        }, { 0.35969651781584833,      // re
          -0.76812202852336542         // im
        }, { 0.35851898719141695,      // re
          -0.7671389119358204          // im
        }, { 0.35734296603377314,      // re
          -0.76615399019631292         // im
        }, { 0.35616845711020861,      // re
          -0.765167265622459           // im
        }, { 0.35499546318445607,      // re
          -0.76417874053611679         // im
        }, { 0.35382398701668372,      // re
          -0.76318841726338127         // im
        }, { 0.35265403136348794,      // re
          -0.7621962981345789          // im
        }, { 0.35148559897788756,      // re
          -0.76120238548426178         // im
        }, { 0.35031869260931681,      // re
          -0.76020668165120242         // im
        }, { 0.349153315003619,        // re
          -0.759209188978388           // im
        }, { 0.3479894689030405,       // re
          -0.75820990981301528         // im
        }, { 0.34682715704622324,      // re
          -0.75720884650648457         // im
        }, { 0.34566638216819956,      // re
          -0.75620600141439454         // im
        }, { 0.34450714700038465,      // re
          -0.75520137689653655         // im
        }, { 0.34334945427057106,      // re
          -0.75419497531688917         // im
        }, { 0.34219330670292136,      // re
          -0.75318679904361252         // im
        }, { 0.34103870701796268,      // re
          -0.7521768504490427          // im
        }, { 0.33988565793257952,      // re
          -0.75116513190968637         // im
        }, { 0.33873416216000773,      // re
          -0.75015164580621507         // im
        }, { 0.33758422240982822,      // re
          -0.74913639452345937         // im
        }, { 0.33643584138796023,      // re
          -0.7481193804504036          // im
        }, { 0.33528902179665521,      // re
          -0.74710060598018013         // im
        }, { 0.33414376633449028,      // re
          -0.74608007351006378         // im
        }, { 0.33300007769636253,      // re
          -0.745057785441466           // im
        }, { 0.33185795857348155,      // re
          -0.74403374417992929         // im
        }, { 0.330717411653364,        // re
          -0.74300795213512172         // im
        }, { 0.32957843961982691,      // re
          -0.74198041172083107         // im
        }, { 0.32844104515298167,      // re
          -0.74095112535495922         // im
        }, { 0.32730523092922714,      // re
          -0.7399200954595162          // im
        }, { 0.32617099962124396,      // re
          -0.73888732446061511         // im
        }, { 0.32503835389798796,      // re
          -0.737852814788466           // im
        }, { 0.32390729642468408,      // re
          -0.73681656887736979         // im
        }, { 0.32277782986281967,      // re
          -0.73577858916571359         // im
        }, { 0.32164995687013853,      // re
          -0.7347388780959635          // im
        }, { 0.32052368010063503,      // re
          -0.73369743811466037         // im
        }, { 0.319399002204547,        // re
          -0.73265427167241282         // im
        }, { 0.31827592582835029,      // re
          -0.73160938122389263         // im
        }, { 0.31715445361475192,      // re
          -0.73056276922782759         // im
        }, { 0.3160345882026846,       // re
          -0.729514438146997           // im
        }, { 0.31491633222729964,      // re
          -0.7284643904482252          // im
        }, { 0.31379968831996141,      // re
          -0.72741262860237577         // im
        }, { 0.31268465910824095,      // re
          -0.726359155084346           // im
        }, { 0.31157124721590956,      // re
          -0.72530397237306077         // im
        }, { 0.31045945526293317,      // re
          -0.724247082951467           // im
        }, { 0.3093492858654654,       // re
          -0.72318848930652746         // im
        }, { 0.30824074163584225,      // re
          -0.72212819392921535         // im
        }, { 0.30713382518257537,      // re
          -0.72106619931450811         // im
        }, { 0.30602853911034611,      // re
          -0.72000250796138165         // im
        }, { 0.30492488601999912,      // re
          -0.71893712237280449         // im
        }, { 0.303822868508537,        // re
          -0.71787004505573171         // im
        }, { 0.30272248916911348,      // re
          -0.71680127852109954         // im
        }, { 0.30162375059102708,      // re
          -0.71573082528381859         // im
        }, { 0.30052665535971623,      // re
          -0.71465868786276909         // im
        }, { 0.29943120605675166,      // re
          -0.71358486878079352         // im
        }, { 0.29833740525983155,      // re
          -0.71250937056469243         // im
        }, { 0.2972452555427747,       // re
          -0.71143219574521643         // im
        }, { 0.29615475947551506,      // re
          -0.71035334685706242         // im
        }, { 0.29506591962409512,      // re
          -0.70927282643886569         // im
        }, { 0.29397873855066026,      // re
          -0.7081906370331954          // im
        }, { 0.29289321881345243,      // re
          -0.70710678118654757         // im
        }, { 0.2918093629668046,       // re
          -0.70602126144933974         // im
        }, { 0.29072717356113431,      // re
          -0.70493408037590488         // im
        }, { 0.28964665314293758,      // re
          -0.70384524052448494         // im
        }, { 0.28856780425478357,      // re
          -0.7027547444572253          // im
        }, { 0.28749062943530757,      // re
          -0.70166259474016845         // im
        }, { 0.28641513121920648,      // re
          -0.70056879394324834         // im
        }, { 0.28534131213723091,      // re
          -0.69947334464028377         // im
        }, { 0.28426917471618141,      // re
          -0.69837624940897292         // im
        }, { 0.28319872147890046,      // re
          -0.69727751083088652         // im
        }, { 0.28212995494426829,      // re
          -0.696177131491463           // im
        }, { 0.28106287762719551,      // re
          -0.69507511398000088         // im
        }, { 0.27999749203861835,      // re
          -0.69397146088965389         // im
        }, { 0.27893380068549189,      // re
          -0.69286617481742463         // im
        }, { 0.27787180607078465,      // re
          -0.69175925836415775         // im
        }, { 0.27681151069347254,      // re
          -0.6906507141345346          // im
        }, { 0.275752917048533,        // re
          -0.68954054473706683         // im
        }, { 0.27469602762693923,      // re
          -0.68842875278409044         // im
        }, { 0.273640844915654,        // re
          -0.687315340891759           // im
        }, { 0.27258737139762423,      // re
          -0.68620031168003859         // im
        }, { 0.2715356095517748,       // re
          -0.68508366777270036         // im
        }, { 0.270485561853003,        // re
          -0.6839654117973154          // im
        }, { 0.26943723077217241,      // re
          -0.68284554638524808         // im
        }, { 0.26839061877610737,      // re
          -0.68172407417164971         // im
        }, { 0.26734572832758718,      // re
          -0.680600997795453           // im
        }, { 0.26630256188533963,      // re
          -0.679476319899365           // im
        }, { 0.2652611219040365,       // re
          -0.67835004312986147         // im
        }, { 0.26422141083428641,      // re
          -0.67722217013718033         // im
        }, { 0.26318343112263021,      // re
          -0.67609270357531592         // im
        }, { 0.262147185211534,        // re
          -0.674961646102012           // im
        }, { 0.26111267553938489,      // re
          -0.673829000378756           // im
        }, { 0.2600799045404838,       // re
          -0.67269476907077286         // im
        }, { 0.25904887464504078,      // re
          -0.67155895484701833         // im
        }, { 0.25801958827916893,      // re
          -0.67042156038017309         // im
        }, { 0.25699204786487828,      // re
          -0.669282588346636           // im
        }, { 0.25596625582007071,      // re
          -0.66814204142651845         // im
        }, { 0.25494221455853405,      // re
          -0.66699992230363747         // im
        }, { 0.25391992648993622,      // re
          -0.66585623366550972         // im
        }, { 0.25289939401981987,      // re
          -0.66471097820334479         // im
        }, { 0.2518806195495964,       // re
          -0.66356415861203977         // im
        }, { 0.25086360547654063,      // re
          -0.66241577759017178         // im
        }, { 0.24984835419378493,      // re
          -0.66126583783999227         // im
        }, { 0.24883486809031363,      // re
          -0.66011434206742048         // im
        }, { 0.2478231495509573,       // re
          -0.65896129298203732         // im
        }, { 0.24681320095638748,      // re
          -0.65780669329707864         // im
        }, { 0.24580502468311083,      // re
          -0.65665054572942894         // im
        }, { 0.24479862310346345,      // re
          -0.65549285299961535         // im
        }, { 0.24379399858560546,      // re
          -0.65433361783180044         // im
        }, { 0.24279115349351543,      // re
          -0.65317284295377676         // im
        }, { 0.24179009018698472,      // re
          -0.6520105310969595          // im
        }, { 0.24079081102161204,      // re
          -0.650846684996381           // im
        }, { 0.23979331834879758,      // re
          -0.64968130739068319         // im
        }, { 0.23879761451573822,      // re
          -0.64851440102211244         // im
        }, { 0.2378037018654211,       // re
          -0.64734596863651206         // im
        }, { 0.23681158273661873,      // re
          -0.64617601298331628         // im
        }, { 0.23582125946388321,      // re
          -0.64500453681554393         // im
        }, { 0.23483273437754104,      // re
          -0.64383154288979139         // im
        }, { 0.23384600980368708,      // re
          -0.64265703396622686         // im
        }, { 0.2328610880641796,       // re
          -0.641481012808583           // im
        }, { 0.23187797147663458,      // re
          -0.64030348218415167         // im
        }, { 0.2308966623544203,       // re
          -0.63912444486377573         // im
        }, { 0.2299171630066521,       // re
          -0.637943903621844           // im
        }, { 0.22893947573818618,      // re
          -0.6367618612362842          // im
        }, { 0.22796360284961548,      // re
          -0.63557832048855611         // im
        }, { 0.226989546637263,        // re
          -0.63439328416364549         // im
        }, { 0.2260173093931771,       // re
          -0.63320675505005719         // im
        }, { 0.22504689340512607,      // re
          -0.63201873593980906         // im
        }, { 0.22407830095659231,      // re
          -0.63082922962842447         // im
        }, { 0.22311153432676756,      // re
          -0.629638238914927           // im
        }, { 0.22214659579054685,      // re
          -0.6284457666018326          // im
        }, { 0.22118348761852402,      // re
          -0.62725181549514408         // im
        }, { 0.22022221207698545,      // re
          -0.62605638840434352         // im
        }, { 0.21926277142790551,      // re
          -0.62485948814238634         // im
        }, { 0.21830516792894061,      // re
          -0.62366111752569453         // im
        }, { 0.21734940383342427,      // re
          -0.62246127937415            // im
        }, { 0.21639548139036169,      // re
          -0.62125997651108755         // im
        }, { 0.21544340284442476,      // re
          -0.6200572117632891          // im
        }, { 0.21449317043594607,      // re
          -0.61885298796097632         // im
        }, { 0.21354478640091423,      // re
          -0.61764730793780387         // im
        }, { 0.21259825297096857,      // re
          -0.61644017453085365         // im
        }, { 0.21165357237339366,      // re
          -0.61523159058062682         // im
        }, { 0.21071074683111435,      // re
          -0.61402155893103849         // im
        }, { 0.20976977856268997,      // re
          -0.61281008242940971         // im
        }, { 0.2088306697823098,       // re
          -0.61159716392646191         // im
        }, { 0.20789342269978761,      // re
          -0.61038280627630948         // im
        }, { 0.20695803952055636,      // re
          -0.60916701233645321         // im
        }, { 0.20602452244566283,      // re
          -0.60794978496777363         // im
        }, { 0.205092873671763,        // re
          -0.60673112703452448         // im
        }, { 0.20416309539111643,      // re
          -0.60551104140432555         // im
        }, { 0.20323518979158117,      // re
          -0.604289530948156           // im
        }, { 0.20230915905660884,      // re
          -0.60306659854034816         // im
        }, { 0.20138500536523907,      // re
          -0.60184224705858            // im
        }, { 0.200462730892095,        // re
          -0.600616479383869           // im
        }, { 0.19954233780737718,      // re
          -0.59938929840056454         // im
        }, { 0.19862382827685976,      // re
          -0.59816070699634238         // im
        }, { 0.19770720446188428,      // re
          -0.59693070806219639         // im
        }, { 0.19679246851935506,      // re
          -0.59569930449243336         // im
        }, { 0.1958796226017343,       // re
          -0.59446649918466443         // im
        }, { 0.19496866885703634,      // re
          -0.5932322950397998          // im
        }, { 0.19405960942882372,      // re
          -0.591996694962041           // im
        }, { 0.19315244645620067,      // re
          -0.59075970185887416         // im
        }, { 0.19224718207380964,      // re
          -0.58952131864106394         // im
        }, { 0.19134381841182502,      // re
          -0.58828154822264522         // im
        }, { 0.19044235759594874,      // re
          -0.587040393520918           // im
        }, { 0.18954280174740523,      // re
          -0.58579785745643886         // im
        }, { 0.18864515298293627,      // re
          -0.58455394295301533         // im
        }, { 0.18774941341479612,      // re
          -0.58330865293769829         // im
        }, { 0.18685558515074641,      // re
          -0.58206199034077544         // im
        }, { 0.18596367029405159,      // re
          -0.58081395809576453         // im
        }, { 0.18507367094347338,      // re
          -0.57956455913940563         // im
        }, { 0.18418558919326622,      // re
          -0.57831379641165559         // im
        }, { 0.18329942713317215,      // re
          -0.57706167285567944         // im
        }, { 0.18241518684841629,      // re
          -0.57580819141784534         // im
        }, { 0.18153287041970134,      // re
          -0.57455335504771576         // im
        }, { 0.180652479923203,        // re
          -0.5732971666980422          // im
        }, { 0.17977401743056531,      // re
          -0.572039629324757           // im
        }, { 0.17889748500889535,      // re
          -0.57078074588696726         // im
        }, { 0.17802288472075845,      // re
          -0.56952051934694714         // im
        }, { 0.17715021862417357,      // re
          -0.56825895267013149         // im
        }, { 0.17627948877260857,      // re
          -0.56699604882510868         // im
        }, { 0.17541069721497471,      // re
          -0.56573181078361312         // im
        }, { 0.17454384599562245,      // re
          -0.5644662415205195          // im
        }, { 0.17367893715433647,      // re
          -0.56319934401383409         // im
        }, { 0.17281597272633087,      // re
          -0.56193112124468936         // im
        }, { 0.1719549547422442,       // re
          -0.560661576197336           // im
        }, { 0.17109588522813513,      // re
          -0.55939071185913614         // im
        }, { 0.17023876620547695,      // re
          -0.5581185312205561          // im
        }, { 0.16938359969115369,      // re
          -0.5568450372751601          // im
        }, { 0.16853038769745476,      // re
          -0.55557023301960218         // im
        }, { 0.16767913223207032,      // re
          -0.55429412145362            // im
        }, { 0.16682983529808681,      // re
          -0.55301670558002747         // im
        }, { 0.16598249889398187,      // re
          -0.55173798840470734         // im
        }, { 0.16513712501362,         // re
          -0.55045797293660481         // im
        }, { 0.1642937156462474,       // re
          -0.54917666218771966         // im
        }, { 0.163452272776488,        // re
          -0.54789405917310019         // im
        }, { 0.16261279838433806,      // re
          -0.54661016691083486         // im
        }, { 0.16177529444516192,      // re
          -0.54532498842204646         // im
        }, { 0.16093976292968726,      // re
          -0.54403852673088382         // im
        }, { 0.16010620580400048,      // re
          -0.54275078486451589         // im
        }, { 0.15927462502954193,      // re
          -0.54146176585312344         // im
        }, { 0.15844502256310156,      // re
          -0.54017147272989285         // im
        }, { 0.15761740035681415,      // re
          -0.53887990853100842         // im
        }, { 0.15679176035815456,      // re
          -0.53758707629564539         // im
        }, { 0.15596810450993359,      // re
          -0.53629297906596318         // im
        }, { 0.15514643475029288,      // re
          -0.53499761988709715         // im
        }, { 0.15432675301270093,      // re
          -0.533701001807153           // im
        }, { 0.15350906122594787,      // re
          -0.5324031278771979          // im
        }, { 0.15269336131414168,      // re
          -0.531104001151255           // im
        }, { 0.15187965519670277,      // re
          -0.52980362468629461         // im
        }, { 0.15106794478836039,      // re
          -0.52850200154222848         // im
        }, { 0.15025823199914745,      // re
          -0.52719913478190128         // im
        }, { 0.14945051873439652,      // re
          -0.52589502747108463         // im
        }, { 0.1486448068947348,       // re
          -0.524589682678469           // im
        }, { 0.14784109837608017,      // re
          -0.52328310347565643         // im
        }, { 0.14703939506963637,      // re
          -0.52197529293715439         // im
        }, { 0.14623969886188859,      // re
          -0.52066625414036716         // im
        }, { 0.14544201163459947,      // re
          -0.51935599016558964         // im
        }, { 0.14464633526480397,      // re
          -0.51804450409599934         // im
        }, { 0.14385267162480553,      // re
          -0.51673179901764987         // im
        }, { 0.14306102258217124,      // re
          -0.51541787801946293         // im
        }, { 0.14227138999972788,      // re
          -0.51410274419322166         // im
        }, { 0.14148377573555726,      // re
          -0.512786400633563           // im
        }, { 0.14069818164299153,      // re
          -0.5114688504379703          // im
        }, { 0.13991460957060986,      // re
          -0.51015009670676681         // im
        }, { 0.13913306136223269,      // re
          -0.508830142543107           // im
        }, { 0.1383535388569187,       // re
          -0.50750899105297087         // im
        }, { 0.1375760438889595,       // re
          -0.50618664534515523         // im
        }, { 0.13680057828787584,      // re
          -0.50486310853126759         // im
        }, { 0.1360271438784133,       // re
          -0.50353838372571758         // im
        }, { 0.13525574248053762,      // re
          -0.50221247404571079         // im
        }, { 0.13448637590943091,      // re
          -0.50088538261124071         // im
        }, { 0.133719045975487,        // re
          -0.49955711254508184         // im
        }, { 0.13295375448430735,      // re
          -0.49822766697278181         // im
        }, { 0.13219050323669668,      // re
          -0.49689704902265447         // im
        }, { 0.1314292940286591,       // re
          -0.49556526182577254         // im
        }, { 0.13067012865139316,      // re
          -0.49423230851595967         // im
        }, { 0.12991300889128854,      // re
          -0.49289819222978404         // im
        }, { 0.12915793652992102,      // re
          -0.4915629161065499          // im
        }, { 0.12840491334404891,      // re
          -0.49022648328829116         // im
        }, { 0.12765394110560846,      // re
          -0.48888889691976317         // im
        }, { 0.12690502158170991,      // re
          -0.487550160148436           // im
        }, { 0.12615815653463314,      // re
          -0.48621027612448642         // im
        }, { 0.12541334772182389,      // re
          -0.48486924800079106         // im
        }, { 0.12467059689588911,      // re
          -0.48352707893291874         // im
        }, { 0.1239299058045934,       // re
          -0.48218377207912272         // im
        }, { 0.12319127619085435,      // re
          -0.48083933060033396         // im
        }, { 0.12245470979273865,      // re
          -0.47949375766015295         // im
        }, { 0.12172020834345842,      // re
          -0.478147056424843           // im
        }, { 0.12098777357136647,      // re
          -0.47679923006332209         // im
        }, { 0.12025740719995259,      // re
          -0.47545028174715587         // im
        }, { 0.11952911094783925,      // re
          -0.47410021465054997         // im
        }, { 0.11880288652877791,      // re
          -0.47274903195034279         // im
        }, { 0.11807873565164495,      // re
          -0.47139673682599764         // im
        }, { 0.11735666002043721,      // re
          -0.47004333245959562         // im
        }, { 0.11663666133426842,      // re
          -0.46868882203582796         // im
        }, { 0.11591874128736501,      // re
          -0.46733320874198842         // im
        }, { 0.11520290156906221,      // re
          -0.46597649576796618         // im
        }, { 0.11448914386380005,      // re
          -0.46461868630623782         // im
        }, { 0.11377746985111936,      // re
          -0.46325978355186015         // im
        }, { 0.11306788120565781,      // re
          -0.46189979070246273         // im
        }, { 0.11236037959714607,      // re
          -0.46053871095824            // im
        }, { 0.11165496669040365,      // re
          -0.45917654752194409         // im
        }, { 0.11095164414533543,      // re
          -0.45781330359887717         // im
        }, { 0.11025041361692722,      // re
          -0.45644898239688392         // im
        }, { 0.10955127675524212,      // re
          -0.45508358712634384         // im
        }, { 0.10885423520541682,      // re
          -0.45371712100016387         // im
        }, { 0.10815929060765728,      // re
          -0.45234958723377089         // im
        }, { 0.10746644459723542,      // re
          -0.45098098904510386         // im
        }, { 0.10677569880448468,      // re
          -0.44961132965460654         // im
        }, { 0.10608705485479675,      // re
          -0.44824061228521989         // im
        }, { 0.1054005143686173,       // re
          -0.44686884016237416         // im
        }, { 0.10471607896144242,      // re
          -0.44549601651398174         // im
        }, { 0.10403375024381478,      // re
          -0.4441221445704292          // im
        }, { 0.10335352982131985,      // re
          -0.44274722756457            // im
        }, { 0.10267541929458168,      // re
          -0.44137126873171667         // im
        }, { 0.10199942025926012,      // re
          -0.43999427130963326         // im
        }, { 0.10132553430604618,      // re
          -0.43861623853852766         // im
        }, { 0.10065376302065843,      // re
          -0.43723717366104409         // im
        }, { 0.099984107983839832,     // re
          -0.43585707992225547         // im
        }, { 0.09931657077135303,      // re
          -0.43447596056965565         // im
        }, { 0.098651152953977972,     // re
          -0.43309381885315196         // im
        }, { 0.09798785609750682,      // re
          -0.43171065802505726         // im
        }, { 0.097326681762741174,     // re
          -0.43032648134008261         // im
        }, { 0.096667631505488183,     // re
          -0.42894129205532949         // im
        }, { 0.096010706876556662,     // re
          -0.42755509343028208         // im
        }, { 0.09535590942175376,      // re
          -0.42616788872679962         // im
        }, { 0.094703240681881184,     // re
          -0.42477968120910881         // im
        }, { 0.094052702192731541,     // re
          -0.42339047414379605         // im
        }, { 0.093404295485084665,     // re
          -0.42200027079979968         // im
        }, { 0.092758022084704184,     // re
          -0.42060907444840251         // im
        }, { 0.092113883512333739,     // re
          -0.41921688836322391         // im
        }, { 0.091471881283693879,     // re
          -0.41782371582021227         // im
        }, { 0.09083201690947762,      // re
          -0.41642956009763715         // im
        }, { 0.090194291895347778,     // re
          -0.41503442447608163         // im
        }, { 0.089558707741932753,     // re
          -0.4136383122384345          // im
        }, { 0.088925265944823639,     // re
          -0.41224122666988289         // im
        }, { 0.088293967994570122,     // re
          -0.41084317105790391         // im
        }, { 0.087664815376677252,     // re
          -0.40944414869225759         // im
        }, { 0.087037809571601787,     // re
          -0.40804416286497869         // im
        }, { 0.086412952054749192,     // re
          -0.40664321687036903         // im
        }, { 0.085790244296469309,     // re
          -0.40524131400498986         // im
        }, { 0.0851696877620538,       // re
          -0.40383845756765407         // im
        }, { 0.084551283911732167,     // re
          -0.40243465085941843         // im
        }, { 0.083935034200668279,     // re
          -0.40102989718357562         // im
        }, { 0.0833209400789573,       // re
          -0.39962419984564679         // im
        }, { 0.0827090029916221,       // re
          -0.39821756215337356         // im
        }, { 0.0820992243786095,       // re
          -0.39680998741671031         // im
        }, { 0.081491605674787748,     // re
          -0.39540147894781635         // im
        }, { 0.08088614830994223,      // re
          -0.3939920400610481          // im
        }, { 0.080282853708772639,     // re
          -0.39258167407295147         // im
        }, { 0.0796817232908894,       // re
          -0.39117038430225387         // im
        }, { 0.079082758470810477,     // re
          -0.38975817406985641         // im
        }, { 0.0784859606579581,       // re
          -0.38834504669882625         // im
        }, { 0.077891331256654817,     // re
          -0.38693100551438858         // im
        }, { 0.077298871666121372,     // re
          -0.38551605384391885         // im
        }, { 0.076708583280472364,     // re
          -0.38410019501693504         // im
        }, { 0.076120467488713262,     // re
          -0.38268343236508978         // im
        }, { 0.0755345256747374,       // re
          -0.38126576922216238         // im
        }, { 0.074950759217322416,     // re
          -0.37984720892405116         // im
        }, { 0.074369169490127285,     // re
          -0.37842775480876556         // im
        }, { 0.073789757861688621,     // re
          -0.37700741021641826         // im
        }, { 0.073212525695418251,     // re
          -0.37558617848921722         // im
        }, { 0.072637474349598885,     // re
          -0.37416406297145793         // im
        }, { 0.072064605177382113,     // re
          -0.37274106700951576         // im
        }, { 0.071493919526784411,     // re
          -0.37131719395183749         // im
        }, { 0.070925418740684143,     // re
          -0.3698924471489341          // im
        }, { 0.070359104156818786,     // re
          -0.36846682995337232         // im
        }, { 0.069794977107780931,     // re
          -0.36704034571976718         // im
        }, { 0.069233038921016288,     // re
          -0.36561299780477385         // im
        }, { 0.068673290918819574,     // re
          -0.36418478956707989         // im
        }, { 0.068115734418331852,     // re
          -0.36275572436739723         // im
        }, { 0.067560370731537644,     // re
          -0.36132580556845428         // im
        }, { 0.067007201165261043,     // re
          -0.35989503653498811         // im
        }, { 0.066456227021163827,     // re
          -0.35846342063373654         // im
        }, { 0.06590744959574113,      // re
          -0.35703096123343            // im
        }, { 0.065360870180319219,     // re
          -0.35559766170478385         // im
        }, { 0.06481649006105239,      // re
          -0.35416352542049034         // im
        }, { 0.064274310518919631,     // re
          -0.35272855575521073         // im
        }, { 0.06373433282972174,      // re
          -0.35129275608556709         // im
        }, { 0.06319655826407844,      // re
          -0.34985612979013492         // im
        }, { 0.06266098808742504,      // re
          -0.34841868024943456         // im
        }, { 0.062127623560010115,     // re
          -0.34698041084592368         // im
        }, { 0.061596465936891942,     // re
          -0.34554132496398909         // im
        }, { 0.0610675164679354,       // re
          -0.34410142598993881         // im
        }, { 0.060540776397810081,     // re
          -0.34266071731199438         // im
        }, { 0.060016246965986064,     // re
          -0.34121920232028236         // im
        }, { 0.059493929406731705,     // re
          -0.33977688440682685         // im
        }, { 0.058973824949110742,     // re
          -0.33833376696554113         // im
        }, { 0.058455934816979194,     // re
          -0.33688985339222005         // im
        }, { 0.057940260228982687,     // re
          -0.3354451470845316          // im
        }, { 0.057426802398553134,     // re
          -0.33399965144200938         // im
        }, { 0.056915562533906505,     // re
          -0.33255336986604422         // im
        }, { 0.056406541838039614,     // re
          -0.33110630575987643         // im
        }, { 0.055899741508727341,     // re
          -0.32965846252858749         // im
        }, { 0.055395162738519743,     // re
          -0.3282098435790925          // im
        }, { 0.054892806714739395,     // re
          -0.32676045232013173         // im
        }, { 0.05439267461947872,      // re
          -0.32531029216226293         // im
        }, { 0.053894767629596552,     // re
          -0.32385936651785285         // im
        }, { 0.053399086916716465,     // re
          -0.32240767880106985         // im
        }, { 0.052905633647222783,     // re
          -0.32095523242787521         // im
        }, { 0.052414408982258909,     // re
          -0.31950203081601569         // im
        }, { 0.051925414077723775,     // re
          -0.31804807738501495         // im
        }, { 0.051438650084269733,     // re
          -0.31659337555616585         // im
        }, { 0.050954118147299443,     // re
          -0.31513792875252244         // im
        }, { 0.050471819406963325,     // re
          -0.31368174039889152         // im
        }, { 0.049991754998157,        // re
          -0.31222481392182488         // im
        }, { 0.0495139260505183,       // re
          -0.31076715274961147         // im
        }, { 0.049038333688424918,     // re
          -0.30930876031226873         // im
        }, { 0.048564979030991662,     // re
          -0.30784964004153487         // im
        }, { 0.048093863192067654,     // re
          -0.30638979537086092         // im
        }, { 0.047624987280234121,     // re
          -0.30492922973540237         // im
        }, { 0.047158352398801284,     // re
          -0.30346794657201132         // im
        }, { 0.046693959645806138,     // re
          -0.30200594931922808         // im
        }, { 0.046231810114009675,     // re
          -0.30054324141727345         // im
        }, { 0.045771904890894333,     // re
          -0.29907982630804048         // im
        }, { 0.045314245058661662,     // re
          -0.2976157074350862          // im
        }, { 0.044858831694229218,     // re
          -0.29615088824362379         // im
        }, { 0.044405665869228894,     // re
          -0.29468537218051433         // im
        }, { 0.043954748650003594,     // re
          -0.29321916269425863         // im
        }, { 0.0435060810976049,       // re
          -0.29175226323498926         // im
        }, { 0.043059664267791176,     // re
          -0.29028467725446233         // im
        }, { 0.042615499211024144,     // re
          -0.28881640820604948         // im
        }, { 0.042173586972467092,     // re
          -0.28734745954472951         // im
        }, { 0.041733928591982328,     // re
          -0.28587783472708062         // im
        }, { 0.0412965251041284,       // re
          -0.28440753721127188         // im
        }, { 0.040861377538158106,     // re
          -0.28293657045705539         // im
        }, { 0.040428486918015483,     // re
          -0.28146493792575794         // im
        }, { 0.039997854262334043,     // re
          -0.27999264308027322         // im
        }, { 0.039569480584434213,     // re
          -0.27851968938505306         // im
        }, { 0.039143366892320341,     // re
          -0.2770460803060999          // im
        }, { 0.03871951418867936,      // re
          -0.27557181931095814         // im
        }, { 0.03829792347087746,      // re
          -0.27409690986870638         // im
        }, { 0.03787859573095842,      // re
          -0.272621355449949           // im
        }, { 0.037461531955640837,     // re
          -0.271145159526808           // im
        }, { 0.037046733126316123,     // re
          -0.26966832557291509         // im
        }, { 0.036634200219045954,     // re
          -0.26819085706340318         // im
        }, { 0.03622393420456016,      // re
          -0.26671275747489837         // im
        }, { 0.035815936048254171,     // re
          -0.26523403028551179         // im
        }, { 0.035410206710187242,     // re
          -0.26375467897483135         // im
        }, { 0.035006747145079675,     // re
          -0.26227470702391359         // im
        }, { 0.0346055583023106,       // re
          -0.26079411791527551         // im
        }, { 0.034206641125916315,     // re
          -0.25931291513288623         // im
        }, { 0.033809996554587496,     // re
          -0.257831102162159           // im
        }, { 0.033415625521666881,     // re
          -0.25634868248994291         // im
        }, { 0.033023528955147929,     // re
          -0.25486565960451457         // im
        }, { 0.032633707777671495,     // re
          -0.25338203699557016         // im
        }, { 0.032246162906524489,     // re
          -0.25189781815421697         // im
        }, { 0.031860895253637556,     // re
          -0.25041300657296522         // im
        }, { 0.031477905725582733,     // re
          -0.24892760574572015         // im
        }, { 0.031097195223571128,     // re
          -0.24744161916777327         // im
        }, { 0.030718764643451468,     // re
          -0.24595505033579459         // im
        }, { 0.030342614875707552,     // re
          -0.24446790274782415         // im
        }, { 0.029968746805456026,     // re
          -0.24298017990326387         // im
        }, { 0.029597161312444498,     // re
          -0.24149188530286933         // im
        }, { 0.02922785927104965,      // re
          -0.2400030224487415          // im
        }, { 0.028860841550274907,     // re
          -0.23851359484431842         // im
        }, { 0.028496109013748216,     // re
          -0.2370236059943672          // im
        }, { 0.028133662519720604,     // re
          -0.23553305940497549         // im
        }, { 0.027773502921063731,     // re
          -0.23404195858354343         // im
        }, { 0.027415631065267787,     // re
          -0.23255030703877524         // im
        }, { 0.027060047794439823,     // re
          -0.23105810828067111         // im
        }, { 0.026706753945301753,     // re
          -0.22956536582051887         // im
        }, { 0.026355750349188023,     // re
          -0.22807208317088573         // im
        }, { 0.026007037832044166,     // re
          -0.22657826384561            // im
        }, { 0.025660617214424142,     // re
          -0.22508391135979283         // im
        }, { 0.025316489311489332,     // re
          -0.22358902922979            // im
        }, { 0.02497465493300588,      // re
          -0.22209362097320351         // im
        }, { 0.024635114883343023,     // re
          -0.22059769010887351         // im
        }, { 0.02429786996147143,      // re
          -0.2191012401568698          // im
        }, { 0.023962920960960976,     // re
          -0.21760427463848364         // im
        }, { 0.02363026866997886,      // re
          -0.21610679707621952         // im
        }, { 0.023299913871288158,     // re
          -0.21460881099378676         // im
        }, { 0.022971857342245605,     // re
          -0.21311031991609136         // im
        }, { 0.022646099854799928,     // re
          -0.21161132736922755         // im
        }, { 0.022322642175490071,     // re
          -0.21011183688046961         // im
        }, { 0.022001485065442861,     // re
          -0.20861185197826349         // im
        }, { 0.021682629280372345,     // re
          -0.20711137619221856         // im
        }, { 0.021366075570576792,     // re
          -0.20561041305309924         // im
        }, { 0.021051824680937803,     // re
          -0.20410896609281687         // im
        }, { 0.020739877350917979,     // re
          -0.20260703884442113         // im
        }, { 0.020430234314559481,     // re
          -0.2011046348420919          // im
        }, { 0.020122896300482362,     // re
          -0.19960175762113097         // im
        }, { 0.019817864031882571,     // re
          -0.19809841071795356         // im
        }, { 0.019515138226530615,     // re
          -0.19659459767008022         // im
        }, { 0.019214719596769569,     // re
          -0.19509032201612825         // im
        }, { 0.018916608849513294,     // re
          -0.19358558729580361         // im
        }, { 0.018620806686245439,     // re
          -0.19208039704989244         // im
        }, { 0.018327313803016887,     // re
          -0.19057475482025274         // im
        }, { 0.018036130890444757,     // re
          -0.18906866414980619         // im
        }, { 0.017747258633710628,     // re
          -0.1875621285825296          // im
        }, { 0.017460697712558759,     // re
          -0.18605515166344663         // im
        }, { 0.017176448801294764,     // re
          -0.18454773693861962         // im
        }, { 0.016894512568783715,     // re
          -0.18303988795514095         // im
        }, { 0.016614889678448819,     // re
          -0.18153160826112497         // im
        }, { 0.016337580788269745,     // re
          -0.18002290140569951         // im
        }, { 0.016062586550781077,     // re
          -0.17851377093899751         // im
        }, { 0.015789907613070975,     // re
          -0.17700422041214875         // im
        }, { 0.015519544616779068,     // re
          -0.17549425337727143         // im
        }, { 0.015251498198095792,     // re
          -0.17398387338746382         // im
        }, { 0.014985768987760162,     // re
          -0.17247308399679595         // im
        }, { 0.014722357611058778,     // re
          -0.17096188876030122         // im
        }, { 0.014461264687823938,     // re
          -0.16945029123396796         // im
        }, { 0.014202490832432524,     // re
          -0.16793829497473117         // im
        }, { 0.013946036653804561,     // re
          -0.1664259035404641          // im
        }, { 0.013691902755401331,     // re
          -0.16491312048996992         // im
        }, { 0.013440089735224592,     // re
          -0.16339994938297323         // im
        }, { 0.013190598185814473,     // re
          -0.16188639378011183         // im
        }, { 0.012943428694249026,     // re
          -0.16037245724292828         // im
        }, { 0.012698581842141565,     // re
          -0.15885814333386145         // im
        }, { 0.012456058205640774,     // re
          -0.15734345561623825         // im
        }, { 0.012215858355427822,     // re
          -0.15582839765426523         // im
        }, { 0.011977982856716474,     // re
          -0.1543129730130201          // im
        }, { 0.011742432269250536,     // re
          -0.15279718525844344         // im
        }, { 0.011509207147303413,     // re
          -0.15128103795733022         // im
        }, { 0.011278308039676221,     // re
          -0.14976453467732151         // im
        }, { 0.01104973548969701,      // re
          -0.14824767898689603         // im
        }, { 0.010823490035218986,     // re
          -0.14673047445536175         // im
        }, { 0.010599572208619623,     // re
          -0.14521292465284746         // im
        }, { 0.010377982536799113,     // re
          -0.14369503315029447         // im
        }, { 0.010158721541179472,     // re
          -0.14217680351944803         // im
        }, { 0.0099417897377028774,    // re
          -0.14065823933284921         // im
        }, { 0.0097271876368308918,    // re
          -0.1391393441638262          // im
        }, { 0.0095149157435429066,    // re
          -0.13762012158648604         // im
        }, { 0.0093049745573353659,    // re
          -0.1361005751757062          // im
        }, { 0.00909736457221999,      // re
          -0.13458070850712617         // im
        }, { 0.00889208627672311,      // re
          -0.13306052515713906         // im
        }, { 0.0086891401538845559,    // re
          -0.13154002870288312         // im
        }, { 0.0084885266812561033,    // re
          -0.13001922272223335         // im
        }, { 0.0082902463309004748,    // re
          -0.12849811079379317         // im
        }, { 0.0080942995693906727,    // re
          -0.12697669649688587         // im
        }, { 0.0079006868578082035,    // re
          -0.12545498341154623         // im
        }, { 0.007709408651742633,     // re
          -0.12393297511851216         // im
        }, { 0.0075204654012900329,    // re
          -0.1224106751992162          // im
        }, { 0.007333857551051981,     // re
          -0.12088808723577708         // im
        }, { 0.0071495855401348951,    // re
          -0.11936521481099135         // im
        }, { 0.00696764980214859,      // re
          -0.11784206150832498         // im
        }, { 0.0067880507652055,       // re
          -0.11631863091190475         // im
        }, { 0.006610788851919347,     // re
          -0.11479492660651008         // im
        }, { 0.006435864479404696,     // re
          -0.11327095217756435         // im
        }, { 0.0062632780592754012,    // re
          -0.11174671121112659         // im
        }, { 0.0060930299976439395,    // re
          -0.11022220729388306         // im
        }, { 0.0059251206951206337,    // re
          -0.10869744401313872         // im
        }, { 0.0057595505468120978,    // re
          -0.10717242495680884         // im
        }, { 0.0055963199423209042,    // re
          -0.10564715371341062         // im
        }, { 0.0054354292657445846,    // re
          -0.10412163387205459         // im
        }, { 0.0052768788956742974,    // re
          -0.10259586902243628         // im
        }, { 0.0051206692051943836,    // re
          -0.10106986275482782         // im
        }, { 0.0049668005618813682,    // re
          -0.099543618660069319        // im
        }, { 0.0048152733278030713,    // re
          -0.0980171403295606          // im
        }, { 0.00466608785951772,      // re
          -0.096490431355252593        // im
        }, { 0.0045192445080730614,    // re
          -0.094963495329638992        // im
        }, { 0.0043747436190056943,    // re
          -0.093436335845747787        // im
        }, { 0.0042325855323401829,    // re
          -0.091908956497132724        // im
        }, { 0.0040927705825882787,    // re
          -0.090381360877864983        // im
        }, { 0.003955299098748033,     // re
          -0.0888535525825246          // im
        }, { 0.0038201714043030188,    // re
          -0.087325535206192059        // im
        }, { 0.0036873878172219987,    // re
          -0.0857973123444399          // im
        }, { 0.00355694864995737,      // re
          -0.084268887593324071        // im
        }, { 0.0034288542094451646,    // re
          -0.082740264549375692        // im
        }, { 0.0033031047971039396,    // re
          -0.081211446809592441        // im
        }, { 0.0031797007088343321,    // re
          -0.079682437971430126        // im
        }, { 0.0030586422350178388,    // re
          -0.078153241632794232        // im
        }, { 0.0029399296605170377,    // re
          -0.076623861392031492        // im
        }, { 0.0028235632646738118,    // re
          -0.0750943008479213          // im
        }, { 0.002709543321309793,     // re
          -0.073564563599667426        // im
        }, { 0.0025978700987246972,    // re
          -0.072034653246889332        // im
        }, { 0.0024885438596965459,    // re
          -0.070504573389613856        // im
        }, { 0.0023815648614804452,    // re
          -0.068974327628266746        // im
        }, { 0.0022769333558083638,    // re
          -0.067443919563664051        // im
        }, { 0.0021746495888883555,    // re
          -0.0659133527970038          // im
        }, { 0.0020747138014040045,    // re
          -0.064382630929857465        // im
        }, { 0.0019771262285137592,    // re
          -0.0628517575641614          // im
        }, { 0.0018818870998508208,    // re
          -0.061320736302208578        // im
        }, { 0.0017889966395218115,    // re
          -0.059789570746639868        // im
        }, { 0.0016984550661071074,    // re
          -0.058258264500435752        // im
        }, { 0.0016102625926598391,    // re
          -0.056726821166907748        // im
        }, { 0.0015244194267052258,    // re
          -0.055195244349689941        // im
        }, { 0.0014409257702406864,    // re
          -0.05366353765273052         // im
        }, { 0.0013597818197347289,    // re
          -0.052131704680283324        // im
        }, { 0.0012809877661270619,    // re
          -0.050599749036899282        // im
        }, { 0.001204543794827595,     // re
          -0.049067674327418015        // im
        }, { 0.001130450085716439,     // re
          -0.0475354841569593          // im
        }, { 0.0010587068131431288,    // re
          -0.046003182130914623        // im
        }, { 0.000989314145926623,     // re
          -0.044470771854938668        // im
        }, { 0.00092227224735463853,   // re
          -0.04293825693494082         // im
        }, { 0.00085758127518309468,   // re
          -0.041405640977076739        // im
        }, { 0.00079524138163611369,   // re
          -0.039872927587739811        // im
        }, { 0.00073525271340557641,   // re
          -0.038340120373552694        // im
        }, { 0.00067761541165045625,   // re
          -0.036807222941358832        // im
        }, { 0.0006223296119971522,    // re
          -0.035274238898213947        // im
        }, { 0.00056939544453826763,   // re
          -0.03374117185137758         // im
        }, { 0.00051881303383305433,   // re
          -0.032208025408304586        // im
        }, { 0.00047058249890685744,   // re
          -0.030674803176636626        // im
        }, { 0.00042470395325078236,   // re
          -0.029141508764193722        // im
        }, { 0.0003811775048213617,    // re
          -0.02760814577896574         // im
        }, { 0.0003400032560407773,    // re
          -0.0260747178291039          // im
        }, { 0.00030118130379575003,   // re
          -0.024541228522912288        // im
        }, { 0.00026471173943831694,   // re
          -0.023007681468839369        // im
        }, { 0.00023059464878472102,   // re
          -0.021474080275469508        // im
        }, { 0.00019883011211574431,   // re
          -0.019940428551514441        // im
        }, { 0.00016941820417659681,   // re
          -0.01840672990580482         // im
        }, { 0.0001423589941761394,    // re
          -0.01687298794728171         // im
        }, { 0.00011765254578743889,   // re
          -0.0153392062849881          // im
        }, { 9.5298917147101925E-5,    // re
          -0.013805388528060391        // im
        }, { 7.5298160855497009E-5,    // re
          -0.012271538285719925        // im
        }, { 5.765032397608838E-5,     // re
          -0.010737659167264491        // im
        }, { 4.2355448036102139E-5,    // re
          -0.00920375478205982         // im
        }, { 2.941356902586012E-5,     // re
          -0.007669828739531097        // im
        }, { 1.8824717398890911E-5,    // re
          -0.0061358846491544753       // im
        }, { 1.0588918071596787E-5,    // re
          -0.0046019261204485705       // im
        }, { 4.70619042380882E-6,      // re
          -0.0030679567629659761       // im
        }, { 1.1765482981207498E-6,    // re
          -0.0015339801862847655       // im
        }, { 0.0,                      // re
          -0.0                         // im
        }, { 1.1765482981207498E-6,    // re
          0.0015339801862847655        // im
        }, { 4.70619042380882E-6,      // re
          0.0030679567629659761        // im
        }, { 1.0588918071596787E-5,    // re
          0.0046019261204485705        // im
        }, { 1.8824717398890911E-5,    // re
          0.0061358846491544753        // im
        }, { 2.941356902586012E-5,     // re
          0.007669828739531097         // im
        }, { 4.2355448036102139E-5,    // re
          0.00920375478205982          // im
        }, { 5.765032397608838E-5,     // re
          0.010737659167264491         // im
        }, { 7.5298160855497009E-5,    // re
          0.012271538285719925         // im
        }, { 9.5298917147101925E-5,    // re
          0.013805388528060391         // im
        }, { 0.00011765254578743889,   // re
          0.0153392062849881           // im
        }, { 0.0001423589941761394,    // re
          0.01687298794728171          // im
        }, { 0.00016941820417659681,   // re
          0.01840672990580482          // im
        }, { 0.00019883011211574431,   // re
          0.019940428551514441         // im
        }, { 0.00023059464878472102,   // re
          0.021474080275469508         // im
        }, { 0.00026471173943831694,   // re
          0.023007681468839369         // im
        }, { 0.00030118130379575003,   // re
          0.024541228522912288         // im
        }, { 0.0003400032560407773,    // re
          0.0260747178291039           // im
        }, { 0.0003811775048213617,    // re
          0.02760814577896574          // im
        }, { 0.00042470395325078236,   // re
          0.029141508764193722         // im
        }, { 0.00047058249890685744,   // re
          0.030674803176636626         // im
        }, { 0.00051881303383305433,   // re
          0.032208025408304586         // im
        }, { 0.00056939544453826763,   // re
          0.03374117185137758          // im
        }, { 0.0006223296119971522,    // re
          0.035274238898213947         // im
        }, { 0.00067761541165045625,   // re
          0.036807222941358832         // im
        }, { 0.00073525271340557641,   // re
          0.038340120373552694         // im
        }, { 0.00079524138163611369,   // re
          0.039872927587739811         // im
        }, { 0.00085758127518309468,   // re
          0.041405640977076739         // im
        }, { 0.00092227224735463853,   // re
          0.04293825693494082          // im
        }, { 0.000989314145926623,     // re
          0.044470771854938668         // im
        }, { 0.0010587068131431288,    // re
          0.046003182130914623         // im
        }, { 0.001130450085716439,     // re
          0.0475354841569593           // im
        }, { 0.001204543794827595,     // re
          0.049067674327418015         // im
        }, { 0.0012809877661270619,    // re
          0.050599749036899282         // im
        }, { 0.0013597818197347289,    // re
          0.052131704680283324         // im
        }, { 0.0014409257702406864,    // re
          0.05366353765273052          // im
        }, { 0.0015244194267052258,    // re
          0.055195244349689941         // im
        }, { 0.0016102625926598391,    // re
          0.056726821166907748         // im
        }, { 0.0016984550661071074,    // re
          0.058258264500435752         // im
        }, { 0.0017889966395218115,    // re
          0.059789570746639868         // im
        }, { 0.0018818870998508208,    // re
          0.061320736302208578         // im
        }, { 0.0019771262285137592,    // re
          0.0628517575641614           // im
        }, { 0.0020747138014040045,    // re
          0.064382630929857465         // im
        }, { 0.0021746495888883555,    // re
          0.0659133527970038           // im
        }, { 0.0022769333558083638,    // re
          0.067443919563664051         // im
        }, { 0.0023815648614804452,    // re
          0.068974327628266746         // im
        }, { 0.0024885438596965459,    // re
          0.070504573389613856         // im
        }, { 0.0025978700987246972,    // re
          0.072034653246889332         // im
        }, { 0.002709543321309793,     // re
          0.073564563599667426         // im
        }, { 0.0028235632646738118,    // re
          0.0750943008479213           // im
        }, { 0.0029399296605170377,    // re
          0.076623861392031492         // im
        }, { 0.0030586422350178388,    // re
          0.078153241632794232         // im
        }, { 0.0031797007088343321,    // re
          0.079682437971430126         // im
        }, { 0.0033031047971039396,    // re
          0.081211446809592441         // im
        }, { 0.0034288542094451646,    // re
          0.082740264549375692         // im
        }, { 0.00355694864995737,      // re
          0.084268887593324071         // im
        }, { 0.0036873878172219987,    // re
          0.0857973123444399           // im
        }, { 0.0038201714043030188,    // re
          0.087325535206192059         // im
        }, { 0.003955299098748033,     // re
          0.0888535525825246           // im
        }, { 0.0040927705825882787,    // re
          0.090381360877864983         // im
        }, { 0.0042325855323401829,    // re
          0.091908956497132724         // im
        }, { 0.0043747436190056943,    // re
          0.093436335845747787         // im
        }, { 0.0045192445080730614,    // re
          0.094963495329638992         // im
        }, { 0.00466608785951772,      // re
          0.096490431355252593         // im
        }, { 0.0048152733278030713,    // re
          0.0980171403295606           // im
        }, { 0.0049668005618813682,    // re
          0.099543618660069319         // im
        }, { 0.0051206692051943836,    // re
          0.10106986275482782          // im
        }, { 0.0052768788956742974,    // re
          0.10259586902243628          // im
        }, { 0.0054354292657445846,    // re
          0.10412163387205459          // im
        }, { 0.0055963199423209042,    // re
          0.10564715371341062          // im
        }, { 0.0057595505468120978,    // re
          0.10717242495680884          // im
        }, { 0.0059251206951206337,    // re
          0.10869744401313872          // im
        }, { 0.0060930299976439395,    // re
          0.11022220729388306          // im
        }, { 0.0062632780592754012,    // re
          0.11174671121112659          // im
        }, { 0.006435864479404696,     // re
          0.11327095217756435          // im
        }, { 0.006610788851919347,     // re
          0.11479492660651008          // im
        }, { 0.0067880507652055,       // re
          0.11631863091190475          // im
        }, { 0.00696764980214859,      // re
          0.11784206150832498          // im
        }, { 0.0071495855401348951,    // re
          0.11936521481099135          // im
        }, { 0.007333857551051981,     // re
          0.12088808723577708          // im
        }, { 0.0075204654012900329,    // re
          0.1224106751992162           // im
        }, { 0.007709408651742633,     // re
          0.12393297511851216          // im
        }, { 0.0079006868578082035,    // re
          0.12545498341154623          // im
        }, { 0.0080942995693906727,    // re
          0.12697669649688587          // im
        }, { 0.0082902463309004748,    // re
          0.12849811079379317          // im
        }, { 0.0084885266812561033,    // re
          0.13001922272223335          // im
        }, { 0.0086891401538845559,    // re
          0.13154002870288312          // im
        }, { 0.00889208627672311,      // re
          0.13306052515713906          // im
        }, { 0.00909736457221999,      // re
          0.13458070850712617          // im
        }, { 0.0093049745573353659,    // re
          0.1361005751757062           // im
        }, { 0.0095149157435429066,    // re
          0.13762012158648604          // im
        }, { 0.0097271876368308918,    // re
          0.1391393441638262           // im
        }, { 0.0099417897377028774,    // re
          0.14065823933284921          // im
        }, { 0.010158721541179472,     // re
          0.14217680351944803          // im
        }, { 0.010377982536799113,     // re
          0.14369503315029447          // im
        }, { 0.010599572208619623,     // re
          0.14521292465284746          // im
        }, { 0.010823490035218986,     // re
          0.14673047445536175          // im
        }, { 0.01104973548969701,      // re
          0.14824767898689603          // im
        }, { 0.011278308039676221,     // re
          0.14976453467732151          // im
        }, { 0.011509207147303413,     // re
          0.15128103795733022          // im
        }, { 0.011742432269250536,     // re
          0.15279718525844344          // im
        }, { 0.011977982856716474,     // re
          0.1543129730130201           // im
        }, { 0.012215858355427822,     // re
          0.15582839765426523          // im
        }, { 0.012456058205640774,     // re
          0.15734345561623825          // im
        }, { 0.012698581842141565,     // re
          0.15885814333386145          // im
        }, { 0.012943428694249026,     // re
          0.16037245724292828          // im
        }, { 0.013190598185814473,     // re
          0.16188639378011183          // im
        }, { 0.013440089735224592,     // re
          0.16339994938297323          // im
        }, { 0.013691902755401331,     // re
          0.16491312048996992          // im
        }, { 0.013946036653804561,     // re
          0.1664259035404641           // im
        }, { 0.014202490832432524,     // re
          0.16793829497473117          // im
        }, { 0.014461264687823938,     // re
          0.16945029123396796          // im
        }, { 0.014722357611058778,     // re
          0.17096188876030122          // im
        }, { 0.014985768987760162,     // re
          0.17247308399679595          // im
        }, { 0.015251498198095792,     // re
          0.17398387338746382          // im
        }, { 0.015519544616779068,     // re
          0.17549425337727143          // im
        }, { 0.015789907613070975,     // re
          0.17700422041214875          // im
        }, { 0.016062586550781077,     // re
          0.17851377093899751          // im
        }, { 0.016337580788269745,     // re
          0.18002290140569951          // im
        }, { 0.016614889678448819,     // re
          0.18153160826112497          // im
        }, { 0.016894512568783715,     // re
          0.18303988795514095          // im
        }, { 0.017176448801294764,     // re
          0.18454773693861962          // im
        }, { 0.017460697712558759,     // re
          0.18605515166344663          // im
        }, { 0.017747258633710628,     // re
          0.1875621285825296           // im
        }, { 0.018036130890444757,     // re
          0.18906866414980619          // im
        }, { 0.018327313803016887,     // re
          0.19057475482025274          // im
        }, { 0.018620806686245439,     // re
          0.19208039704989244          // im
        }, { 0.018916608849513294,     // re
          0.19358558729580361          // im
        }, { 0.019214719596769569,     // re
          0.19509032201612825          // im
        }, { 0.019515138226530615,     // re
          0.19659459767008022          // im
        }, { 0.019817864031882571,     // re
          0.19809841071795356          // im
        }, { 0.020122896300482362,     // re
          0.19960175762113097          // im
        }, { 0.020430234314559481,     // re
          0.2011046348420919           // im
        }, { 0.020739877350917979,     // re
          0.20260703884442113          // im
        }, { 0.021051824680937803,     // re
          0.20410896609281687          // im
        }, { 0.021366075570576792,     // re
          0.20561041305309924          // im
        }, { 0.021682629280372345,     // re
          0.20711137619221856          // im
        }, { 0.022001485065442861,     // re
          0.20861185197826349          // im
        }, { 0.022322642175490071,     // re
          0.21011183688046961          // im
        }, { 0.022646099854799928,     // re
          0.21161132736922755          // im
        }, { 0.022971857342245605,     // re
          0.21311031991609136          // im
        }, { 0.023299913871288158,     // re
          0.21460881099378676          // im
        }, { 0.02363026866997886,      // re
          0.21610679707621952          // im
        }, { 0.023962920960960976,     // re
          0.21760427463848364          // im
        }, { 0.02429786996147143,      // re
          0.2191012401568698           // im
        }, { 0.024635114883343023,     // re
          0.22059769010887351          // im
        }, { 0.02497465493300588,      // re
          0.22209362097320351          // im
        }, { 0.025316489311489332,     // re
          0.22358902922979             // im
        }, { 0.025660617214424142,     // re
          0.22508391135979283          // im
        }, { 0.026007037832044166,     // re
          0.22657826384561             // im
        }, { 0.026355750349188023,     // re
          0.22807208317088573          // im
        }, { 0.026706753945301753,     // re
          0.22956536582051887          // im
        }, { 0.027060047794439823,     // re
          0.23105810828067111          // im
        }, { 0.027415631065267787,     // re
          0.23255030703877524          // im
        }, { 0.027773502921063731,     // re
          0.23404195858354343          // im
        }, { 0.028133662519720604,     // re
          0.23553305940497549          // im
        }, { 0.028496109013748216,     // re
          0.2370236059943672           // im
        }, { 0.028860841550274907,     // re
          0.23851359484431842          // im
        }, { 0.02922785927104965,      // re
          0.2400030224487415           // im
        }, { 0.029597161312444498,     // re
          0.24149188530286933          // im
        }, { 0.029968746805456026,     // re
          0.24298017990326387          // im
        }, { 0.030342614875707552,     // re
          0.24446790274782415          // im
        }, { 0.030718764643451468,     // re
          0.24595505033579459          // im
        }, { 0.031097195223571128,     // re
          0.24744161916777327          // im
        }, { 0.031477905725582733,     // re
          0.24892760574572015          // im
        }, { 0.031860895253637556,     // re
          0.25041300657296522          // im
        }, { 0.032246162906524489,     // re
          0.25189781815421697          // im
        }, { 0.032633707777671495,     // re
          0.25338203699557016          // im
        }, { 0.033023528955147929,     // re
          0.25486565960451457          // im
        }, { 0.033415625521666881,     // re
          0.25634868248994291          // im
        }, { 0.033809996554587496,     // re
          0.257831102162159            // im
        }, { 0.034206641125916315,     // re
          0.25931291513288623          // im
        }, { 0.0346055583023106,       // re
          0.26079411791527551          // im
        }, { 0.035006747145079675,     // re
          0.26227470702391359          // im
        }, { 0.035410206710187242,     // re
          0.26375467897483135          // im
        }, { 0.035815936048254171,     // re
          0.26523403028551179          // im
        }, { 0.03622393420456016,      // re
          0.26671275747489837          // im
        }, { 0.036634200219045954,     // re
          0.26819085706340318          // im
        }, { 0.037046733126316123,     // re
          0.26966832557291509          // im
        }, { 0.037461531955640837,     // re
          0.271145159526808            // im
        }, { 0.03787859573095842,      // re
          0.272621355449949            // im
        }, { 0.03829792347087746,      // re
          0.27409690986870638          // im
        }, { 0.03871951418867936,      // re
          0.27557181931095814          // im
        }, { 0.039143366892320341,     // re
          0.2770460803060999           // im
        }, { 0.039569480584434213,     // re
          0.27851968938505306          // im
        }, { 0.039997854262334043,     // re
          0.27999264308027322          // im
        }, { 0.040428486918015483,     // re
          0.28146493792575794          // im
        }, { 0.040861377538158106,     // re
          0.28293657045705539          // im
        }, { 0.0412965251041284,       // re
          0.28440753721127188          // im
        }, { 0.041733928591982328,     // re
          0.28587783472708062          // im
        }, { 0.042173586972467092,     // re
          0.28734745954472951          // im
        }, { 0.042615499211024144,     // re
          0.28881640820604948          // im
        }, { 0.043059664267791176,     // re
          0.29028467725446233          // im
        }, { 0.0435060810976049,       // re
          0.29175226323498926          // im
        }, { 0.043954748650003594,     // re
          0.29321916269425863          // im
        }, { 0.044405665869228894,     // re
          0.29468537218051433          // im
        }, { 0.044858831694229218,     // re
          0.29615088824362379          // im
        }, { 0.045314245058661662,     // re
          0.2976157074350862           // im
        }, { 0.045771904890894333,     // re
          0.29907982630804048          // im
        }, { 0.046231810114009675,     // re
          0.30054324141727345          // im
        }, { 0.046693959645806138,     // re
          0.30200594931922808          // im
        }, { 0.047158352398801284,     // re
          0.30346794657201132          // im
        }, { 0.047624987280234121,     // re
          0.30492922973540237          // im
        }, { 0.048093863192067654,     // re
          0.30638979537086092          // im
        }, { 0.048564979030991662,     // re
          0.30784964004153487          // im
        }, { 0.049038333688424918,     // re
          0.30930876031226873          // im
        }, { 0.0495139260505183,       // re
          0.31076715274961147          // im
        }, { 0.049991754998157,        // re
          0.31222481392182488          // im
        }, { 0.050471819406963325,     // re
          0.31368174039889152          // im
        }, { 0.050954118147299443,     // re
          0.31513792875252244          // im
        }, { 0.051438650084269733,     // re
          0.31659337555616585          // im
        }, { 0.051925414077723775,     // re
          0.31804807738501495          // im
        }, { 0.052414408982258909,     // re
          0.31950203081601569          // im
        }, { 0.052905633647222783,     // re
          0.32095523242787521          // im
        }, { 0.053399086916716465,     // re
          0.32240767880106985          // im
        }, { 0.053894767629596552,     // re
          0.32385936651785285          // im
        }, { 0.05439267461947872,      // re
          0.32531029216226293          // im
        }, { 0.054892806714739395,     // re
          0.32676045232013173          // im
        }, { 0.055395162738519743,     // re
          0.3282098435790925           // im
        }, { 0.055899741508727341,     // re
          0.32965846252858749          // im
        }, { 0.056406541838039614,     // re
          0.33110630575987643          // im
        }, { 0.056915562533906505,     // re
          0.33255336986604422          // im
        }, { 0.057426802398553134,     // re
          0.33399965144200938          // im
        }, { 0.057940260228982687,     // re
          0.3354451470845316           // im
        }, { 0.058455934816979194,     // re
          0.33688985339222005          // im
        }, { 0.058973824949110742,     // re
          0.33833376696554113          // im
        }, { 0.059493929406731705,     // re
          0.33977688440682685          // im
        }, { 0.060016246965986064,     // re
          0.34121920232028236          // im
        }, { 0.060540776397810081,     // re
          0.34266071731199438          // im
        }, { 0.0610675164679354,       // re
          0.34410142598993881          // im
        }, { 0.061596465936891942,     // re
          0.34554132496398909          // im
        }, { 0.062127623560010115,     // re
          0.34698041084592368          // im
        }, { 0.06266098808742504,      // re
          0.34841868024943456          // im
        }, { 0.06319655826407844,      // re
          0.34985612979013492          // im
        }, { 0.06373433282972174,      // re
          0.35129275608556709          // im
        }, { 0.064274310518919631,     // re
          0.35272855575521073          // im
        }, { 0.06481649006105239,      // re
          0.35416352542049034          // im
        }, { 0.065360870180319219,     // re
          0.35559766170478385          // im
        }, { 0.06590744959574113,      // re
          0.35703096123343             // im
        }, { 0.066456227021163827,     // re
          0.35846342063373654          // im
        }, { 0.067007201165261043,     // re
          0.35989503653498811          // im
        }, { 0.067560370731537644,     // re
          0.36132580556845428          // im
        }, { 0.068115734418331852,     // re
          0.36275572436739723          // im
        }, { 0.068673290918819574,     // re
          0.36418478956707989          // im
        }, { 0.069233038921016288,     // re
          0.36561299780477385          // im
        }, { 0.069794977107780931,     // re
          0.36704034571976718          // im
        }, { 0.070359104156818786,     // re
          0.36846682995337232          // im
        }, { 0.070925418740684143,     // re
          0.3698924471489341           // im
        }, { 0.071493919526784411,     // re
          0.37131719395183749          // im
        }, { 0.072064605177382113,     // re
          0.37274106700951576          // im
        }, { 0.072637474349598885,     // re
          0.37416406297145793          // im
        }, { 0.073212525695418251,     // re
          0.37558617848921722          // im
        }, { 0.073789757861688621,     // re
          0.37700741021641826          // im
        }, { 0.074369169490127285,     // re
          0.37842775480876556          // im
        }, { 0.074950759217322416,     // re
          0.37984720892405116          // im
        }, { 0.0755345256747374,       // re
          0.38126576922216238          // im
        }, { 0.076120467488713262,     // re
          0.38268343236508978          // im
        }, { 0.076708583280472364,     // re
          0.38410019501693504          // im
        }, { 0.077298871666121372,     // re
          0.38551605384391885          // im
        }, { 0.077891331256654817,     // re
          0.38693100551438858          // im
        }, { 0.0784859606579581,       // re
          0.38834504669882625          // im
        }, { 0.079082758470810477,     // re
          0.38975817406985641          // im
        }, { 0.0796817232908894,       // re
          0.39117038430225387          // im
        }, { 0.080282853708772639,     // re
          0.39258167407295147          // im
        }, { 0.08088614830994223,      // re
          0.3939920400610481           // im
        }, { 0.081491605674787748,     // re
          0.39540147894781635          // im
        }, { 0.0820992243786095,       // re
          0.39680998741671031          // im
        }, { 0.0827090029916221,       // re
          0.39821756215337356          // im
        }, { 0.0833209400789573,       // re
          0.39962419984564679          // im
        }, { 0.083935034200668279,     // re
          0.40102989718357562          // im
        }, { 0.084551283911732167,     // re
          0.40243465085941843          // im
        }, { 0.0851696877620538,       // re
          0.40383845756765407          // im
        }, { 0.085790244296469309,     // re
          0.40524131400498986          // im
        }, { 0.086412952054749192,     // re
          0.40664321687036903          // im
        }, { 0.087037809571601787,     // re
          0.40804416286497869          // im
        }, { 0.087664815376677252,     // re
          0.40944414869225759          // im
        }, { 0.088293967994570122,     // re
          0.41084317105790391          // im
        }, { 0.088925265944823639,     // re
          0.41224122666988289          // im
        }, { 0.089558707741932753,     // re
          0.4136383122384345           // im
        }, { 0.090194291895347778,     // re
          0.41503442447608163          // im
        }, { 0.09083201690947762,      // re
          0.41642956009763715          // im
        }, { 0.091471881283693879,     // re
          0.41782371582021227          // im
        }, { 0.092113883512333739,     // re
          0.41921688836322391          // im
        }, { 0.092758022084704184,     // re
          0.42060907444840251          // im
        }, { 0.093404295485084665,     // re
          0.42200027079979968          // im
        }, { 0.094052702192731541,     // re
          0.42339047414379605          // im
        }, { 0.094703240681881184,     // re
          0.42477968120910881          // im
        }, { 0.09535590942175376,      // re
          0.42616788872679962          // im
        }, { 0.096010706876556662,     // re
          0.42755509343028208          // im
        }, { 0.096667631505488183,     // re
          0.42894129205532949          // im
        }, { 0.097326681762741174,     // re
          0.43032648134008261          // im
        }, { 0.09798785609750682,      // re
          0.43171065802505726          // im
        }, { 0.098651152953977972,     // re
          0.43309381885315196          // im
        }, { 0.09931657077135303,      // re
          0.43447596056965565          // im
        }, { 0.099984107983839832,     // re
          0.43585707992225547          // im
        }, { 0.10065376302065843,      // re
          0.43723717366104409          // im
        }, { 0.10132553430604618,      // re
          0.43861623853852766          // im
        }, { 0.10199942025926012,      // re
          0.43999427130963326          // im
        }, { 0.10267541929458168,      // re
          0.44137126873171667          // im
        }, { 0.10335352982131985,      // re
          0.44274722756457             // im
        }, { 0.10403375024381478,      // re
          0.4441221445704292           // im
        }, { 0.10471607896144242,      // re
          0.44549601651398174          // im
        }, { 0.1054005143686173,       // re
          0.44686884016237416          // im
        }, { 0.10608705485479675,      // re
          0.44824061228521989          // im
        }, { 0.10677569880448468,      // re
          0.44961132965460654          // im
        }, { 0.10746644459723542,      // re
          0.45098098904510386          // im
        }, { 0.10815929060765728,      // re
          0.45234958723377089          // im
        }, { 0.10885423520541682,      // re
          0.45371712100016387          // im
        }, { 0.10955127675524212,      // re
          0.45508358712634384          // im
        }, { 0.11025041361692722,      // re
          0.45644898239688392          // im
        }, { 0.11095164414533543,      // re
          0.45781330359887717          // im
        }, { 0.11165496669040365,      // re
          0.45917654752194409          // im
        }, { 0.11236037959714607,      // re
          0.46053871095824             // im
        }, { 0.11306788120565781,      // re
          0.46189979070246273          // im
        }, { 0.11377746985111936,      // re
          0.46325978355186015          // im
        }, { 0.11448914386380005,      // re
          0.46461868630623782          // im
        }, { 0.11520290156906221,      // re
          0.46597649576796618          // im
        }, { 0.11591874128736501,      // re
          0.46733320874198842          // im
        }, { 0.11663666133426842,      // re
          0.46868882203582796          // im
        }, { 0.11735666002043721,      // re
          0.47004333245959562          // im
        }, { 0.11807873565164495,      // re
          0.47139673682599764          // im
        }, { 0.11880288652877791,      // re
          0.47274903195034279          // im
        }, { 0.11952911094783925,      // re
          0.47410021465054997          // im
        }, { 0.12025740719995259,      // re
          0.47545028174715587          // im
        }, { 0.12098777357136647,      // re
          0.47679923006332209          // im
        }, { 0.12172020834345842,      // re
          0.478147056424843            // im
        }, { 0.12245470979273865,      // re
          0.47949375766015295          // im
        }, { 0.12319127619085435,      // re
          0.48083933060033396          // im
        }, { 0.1239299058045934,       // re
          0.48218377207912272          // im
        }, { 0.12467059689588911,      // re
          0.48352707893291874          // im
        }, { 0.12541334772182389,      // re
          0.48486924800079106          // im
        }, { 0.12615815653463314,      // re
          0.48621027612448642          // im
        }, { 0.12690502158170991,      // re
          0.487550160148436            // im
        }, { 0.12765394110560846,      // re
          0.48888889691976317          // im
        }, { 0.12840491334404891,      // re
          0.49022648328829116          // im
        }, { 0.12915793652992102,      // re
          0.4915629161065499           // im
        }, { 0.12991300889128854,      // re
          0.49289819222978404          // im
        }, { 0.13067012865139316,      // re
          0.49423230851595967          // im
        }, { 0.1314292940286591,       // re
          0.49556526182577254          // im
        }, { 0.13219050323669668,      // re
          0.49689704902265447          // im
        }, { 0.13295375448430735,      // re
          0.49822766697278181          // im
        }, { 0.133719045975487,        // re
          0.49955711254508184          // im
        }, { 0.13448637590943091,      // re
          0.50088538261124071          // im
        }, { 0.13525574248053762,      // re
          0.50221247404571079          // im
        }, { 0.1360271438784133,       // re
          0.50353838372571758          // im
        }, { 0.13680057828787584,      // re
          0.50486310853126759          // im
        }, { 0.1375760438889595,       // re
          0.50618664534515523          // im
        }, { 0.1383535388569187,       // re
          0.50750899105297087          // im
        }, { 0.13913306136223269,      // re
          0.508830142543107            // im
        }, { 0.13991460957060986,      // re
          0.51015009670676681          // im
        }, { 0.14069818164299153,      // re
          0.5114688504379703           // im
        }, { 0.14148377573555726,      // re
          0.512786400633563            // im
        }, { 0.14227138999972788,      // re
          0.51410274419322166          // im
        }, { 0.14306102258217124,      // re
          0.51541787801946293          // im
        }, { 0.14385267162480553,      // re
          0.51673179901764987          // im
        }, { 0.14464633526480397,      // re
          0.51804450409599934          // im
        }, { 0.14544201163459947,      // re
          0.51935599016558964          // im
        }, { 0.14623969886188859,      // re
          0.52066625414036716          // im
        }, { 0.14703939506963637,      // re
          0.52197529293715439          // im
        }, { 0.14784109837608017,      // re
          0.52328310347565643          // im
        }, { 0.1486448068947348,       // re
          0.524589682678469            // im
        }, { 0.14945051873439652,      // re
          0.52589502747108463          // im
        }, { 0.15025823199914745,      // re
          0.52719913478190128          // im
        }, { 0.15106794478836039,      // re
          0.52850200154222848          // im
        }, { 0.15187965519670277,      // re
          0.52980362468629461          // im
        }, { 0.15269336131414168,      // re
          0.531104001151255            // im
        }, { 0.15350906122594787,      // re
          0.5324031278771979           // im
        }, { 0.15432675301270093,      // re
          0.533701001807153            // im
        }, { 0.15514643475029288,      // re
          0.53499761988709715          // im
        }, { 0.15596810450993359,      // re
          0.53629297906596318          // im
        }, { 0.15679176035815456,      // re
          0.53758707629564539          // im
        }, { 0.15761740035681415,      // re
          0.53887990853100842          // im
        }, { 0.15844502256310156,      // re
          0.54017147272989285          // im
        }, { 0.15927462502954193,      // re
          0.54146176585312344          // im
        }, { 0.16010620580400048,      // re
          0.54275078486451589          // im
        }, { 0.16093976292968726,      // re
          0.54403852673088382          // im
        }, { 0.16177529444516192,      // re
          0.54532498842204646          // im
        }, { 0.16261279838433806,      // re
          0.54661016691083486          // im
        }, { 0.163452272776488,        // re
          0.54789405917310019          // im
        }, { 0.1642937156462474,       // re
          0.54917666218771966          // im
        }, { 0.16513712501362,         // re
          0.55045797293660481          // im
        }, { 0.16598249889398187,      // re
          0.55173798840470734          // im
        }, { 0.16682983529808681,      // re
          0.55301670558002747          // im
        }, { 0.16767913223207032,      // re
          0.55429412145362             // im
        }, { 0.16853038769745476,      // re
          0.55557023301960218          // im
        }, { 0.16938359969115369,      // re
          0.5568450372751601           // im
        }, { 0.17023876620547695,      // re
          0.5581185312205561           // im
        }, { 0.17109588522813513,      // re
          0.55939071185913614          // im
        }, { 0.1719549547422442,       // re
          0.560661576197336            // im
        }, { 0.17281597272633087,      // re
          0.56193112124468936          // im
        }, { 0.17367893715433647,      // re
          0.56319934401383409          // im
        }, { 0.17454384599562245,      // re
          0.5644662415205195           // im
        }, { 0.17541069721497471,      // re
          0.56573181078361312          // im
        }, { 0.17627948877260857,      // re
          0.56699604882510868          // im
        }, { 0.17715021862417357,      // re
          0.56825895267013149          // im
        }, { 0.17802288472075845,      // re
          0.56952051934694714          // im
        }, { 0.17889748500889535,      // re
          0.57078074588696726          // im
        }, { 0.17977401743056531,      // re
          0.572039629324757            // im
        }, { 0.180652479923203,        // re
          0.5732971666980422           // im
        }, { 0.18153287041970134,      // re
          0.57455335504771576          // im
        }, { 0.18241518684841629,      // re
          0.57580819141784534          // im
        }, { 0.18329942713317215,      // re
          0.57706167285567944          // im
        }, { 0.18418558919326622,      // re
          0.57831379641165559          // im
        }, { 0.18507367094347338,      // re
          0.57956455913940563          // im
        }, { 0.18596367029405159,      // re
          0.58081395809576453          // im
        }, { 0.18685558515074641,      // re
          0.58206199034077544          // im
        }, { 0.18774941341479612,      // re
          0.58330865293769829          // im
        }, { 0.18864515298293627,      // re
          0.58455394295301533          // im
        }, { 0.18954280174740523,      // re
          0.58579785745643886          // im
        }, { 0.19044235759594874,      // re
          0.587040393520918            // im
        }, { 0.19134381841182502,      // re
          0.58828154822264522          // im
        }, { 0.19224718207380964,      // re
          0.58952131864106394          // im
        }, { 0.19315244645620067,      // re
          0.59075970185887416          // im
        }, { 0.19405960942882372,      // re
          0.591996694962041            // im
        }, { 0.19496866885703634,      // re
          0.5932322950397998           // im
        }, { 0.1958796226017343,       // re
          0.59446649918466443          // im
        }, { 0.19679246851935506,      // re
          0.59569930449243336          // im
        }, { 0.19770720446188428,      // re
          0.59693070806219639          // im
        }, { 0.19862382827685976,      // re
          0.59816070699634238          // im
        }, { 0.19954233780737718,      // re
          0.59938929840056454          // im
        }, { 0.200462730892095,        // re
          0.600616479383869            // im
        }, { 0.20138500536523907,      // re
          0.60184224705858             // im
        }, { 0.20230915905660884,      // re
          0.60306659854034816          // im
        }, { 0.20323518979158117,      // re
          0.604289530948156            // im
        }, { 0.20416309539111643,      // re
          0.60551104140432555          // im
        }, { 0.205092873671763,        // re
          0.60673112703452448          // im
        }, { 0.20602452244566283,      // re
          0.60794978496777363          // im
        }, { 0.20695803952055636,      // re
          0.60916701233645321          // im
        }, { 0.20789342269978761,      // re
          0.61038280627630948          // im
        }, { 0.2088306697823098,       // re
          0.61159716392646191          // im
        }, { 0.20976977856268997,      // re
          0.61281008242940971          // im
        }, { 0.21071074683111435,      // re
          0.61402155893103849          // im
        }, { 0.21165357237339366,      // re
          0.61523159058062682          // im
        }, { 0.21259825297096857,      // re
          0.61644017453085365          // im
        }, { 0.21354478640091423,      // re
          0.61764730793780387          // im
        }, { 0.21449317043594607,      // re
          0.61885298796097632          // im
        }, { 0.21544340284442476,      // re
          0.6200572117632891           // im
        }, { 0.21639548139036169,      // re
          0.62125997651108755          // im
        }, { 0.21734940383342427,      // re
          0.62246127937415             // im
        }, { 0.21830516792894061,      // re
          0.62366111752569453          // im
        }, { 0.21926277142790551,      // re
          0.62485948814238634          // im
        }, { 0.22022221207698545,      // re
          0.62605638840434352          // im
        }, { 0.22118348761852402,      // re
          0.62725181549514408          // im
        }, { 0.22214659579054685,      // re
          0.6284457666018326           // im
        }, { 0.22311153432676756,      // re
          0.629638238914927            // im
        }, { 0.22407830095659231,      // re
          0.63082922962842447          // im
        }, { 0.22504689340512607,      // re
          0.63201873593980906          // im
        }, { 0.2260173093931771,       // re
          0.63320675505005719          // im
        }, { 0.226989546637263,        // re
          0.63439328416364549          // im
        }, { 0.22796360284961548,      // re
          0.63557832048855611          // im
        }, { 0.22893947573818618,      // re
          0.6367618612362842           // im
        }, { 0.2299171630066521,       // re
          0.637943903621844            // im
        }, { 0.2308966623544203,       // re
          0.63912444486377573          // im
        }, { 0.23187797147663458,      // re
          0.64030348218415167          // im
        }, { 0.2328610880641796,       // re
          0.641481012808583            // im
        }, { 0.23384600980368708,      // re
          0.64265703396622686          // im
        }, { 0.23483273437754104,      // re
          0.64383154288979139          // im
        }, { 0.23582125946388321,      // re
          0.64500453681554393          // im
        }, { 0.23681158273661873,      // re
          0.64617601298331628          // im
        }, { 0.2378037018654211,       // re
          0.64734596863651206          // im
        }, { 0.23879761451573822,      // re
          0.64851440102211244          // im
        }, { 0.23979331834879758,      // re
          0.64968130739068319          // im
        }, { 0.24079081102161204,      // re
          0.650846684996381            // im
        }, { 0.24179009018698472,      // re
          0.6520105310969595           // im
        }, { 0.24279115349351543,      // re
          0.65317284295377676          // im
        }, { 0.24379399858560546,      // re
          0.65433361783180044          // im
        }, { 0.24479862310346345,      // re
          0.65549285299961535          // im
        }, { 0.24580502468311083,      // re
          0.65665054572942894          // im
        }, { 0.24681320095638748,      // re
          0.65780669329707864          // im
        }, { 0.2478231495509573,       // re
          0.65896129298203732          // im
        }, { 0.24883486809031363,      // re
          0.66011434206742048          // im
        }, { 0.24984835419378493,      // re
          0.66126583783999227          // im
        }, { 0.25086360547654063,      // re
          0.66241577759017178          // im
        }, { 0.2518806195495964,       // re
          0.66356415861203977          // im
        }, { 0.25289939401981987,      // re
          0.66471097820334479          // im
        }, { 0.25391992648993622,      // re
          0.66585623366550972          // im
        }, { 0.25494221455853405,      // re
          0.66699992230363747          // im
        }, { 0.25596625582007071,      // re
          0.66814204142651845          // im
        }, { 0.25699204786487828,      // re
          0.669282588346636            // im
        }, { 0.25801958827916893,      // re
          0.67042156038017309          // im
        }, { 0.25904887464504078,      // re
          0.67155895484701833          // im
        }, { 0.2600799045404838,       // re
          0.67269476907077286          // im
        }, { 0.26111267553938489,      // re
          0.673829000378756            // im
        }, { 0.262147185211534,        // re
          0.674961646102012            // im
        }, { 0.26318343112263021,      // re
          0.67609270357531592          // im
        }, { 0.26422141083428641,      // re
          0.67722217013718033          // im
        }, { 0.2652611219040365,       // re
          0.67835004312986147          // im
        }, { 0.26630256188533963,      // re
          0.679476319899365            // im
        }, { 0.26734572832758718,      // re
          0.680600997795453            // im
        }, { 0.26839061877610737,      // re
          0.68172407417164971          // im
        }, { 0.26943723077217241,      // re
          0.68284554638524808          // im
        }, { 0.270485561853003,        // re
          0.6839654117973154           // im
        }, { 0.2715356095517748,       // re
          0.68508366777270036          // im
        }, { 0.27258737139762423,      // re
          0.68620031168003859          // im
        }, { 0.273640844915654,        // re
          0.687315340891759            // im
        }, { 0.27469602762693923,      // re
          0.68842875278409044          // im
        }, { 0.275752917048533,        // re
          0.68954054473706683          // im
        }, { 0.27681151069347254,      // re
          0.6906507141345346           // im
        }, { 0.27787180607078465,      // re
          0.69175925836415775          // im
        }, { 0.27893380068549189,      // re
          0.69286617481742463          // im
        }, { 0.27999749203861835,      // re
          0.69397146088965389          // im
        }, { 0.28106287762719551,      // re
          0.69507511398000088          // im
        }, { 0.28212995494426829,      // re
          0.696177131491463            // im
        }, { 0.28319872147890046,      // re
          0.69727751083088652          // im
        }, { 0.28426917471618141,      // re
          0.69837624940897292          // im
        }, { 0.28534131213723091,      // re
          0.69947334464028377          // im
        }, { 0.28641513121920648,      // re
          0.70056879394324834          // im
        }, { 0.28749062943530757,      // re
          0.70166259474016845          // im
        }, { 0.28856780425478357,      // re
          0.7027547444572253           // im
        }, { 0.28964665314293758,      // re
          0.70384524052448494          // im
        }, { 0.29072717356113431,      // re
          0.70493408037590488          // im
        }, { 0.2918093629668046,       // re
          0.70602126144933974          // im
        }, { 0.29289321881345243,      // re
          0.70710678118654757          // im
        }, { 0.29397873855066026,      // re
          0.7081906370331954           // im
        }, { 0.29506591962409512,      // re
          0.70927282643886569          // im
        }, { 0.29615475947551506,      // re
          0.71035334685706242          // im
        }, { 0.2972452555427747,       // re
          0.71143219574521643          // im
        }, { 0.29833740525983155,      // re
          0.71250937056469243          // im
        }, { 0.29943120605675166,      // re
          0.71358486878079352          // im
        }, { 0.30052665535971623,      // re
          0.71465868786276909          // im
        }, { 0.30162375059102708,      // re
          0.71573082528381859          // im
        }, { 0.30272248916911348,      // re
          0.71680127852109954          // im
        }, { 0.303822868508537,        // re
          0.71787004505573171          // im
        }, { 0.30492488601999912,      // re
          0.71893712237280449          // im
        }, { 0.30602853911034611,      // re
          0.72000250796138165          // im
        }, { 0.30713382518257537,      // re
          0.72106619931450811          // im
        }, { 0.30824074163584225,      // re
          0.72212819392921535          // im
        }, { 0.3093492858654654,       // re
          0.72318848930652746          // im
        }, { 0.31045945526293317,      // re
          0.724247082951467            // im
        }, { 0.31157124721590956,      // re
          0.72530397237306077          // im
        }, { 0.31268465910824095,      // re
          0.726359155084346            // im
        }, { 0.31379968831996141,      // re
          0.72741262860237577          // im
        }, { 0.31491633222729964,      // re
          0.7284643904482252           // im
        }, { 0.3160345882026846,       // re
          0.729514438146997            // im
        }, { 0.31715445361475192,      // re
          0.73056276922782759          // im
        }, { 0.31827592582835029,      // re
          0.73160938122389263          // im
        }, { 0.319399002204547,        // re
          0.73265427167241282          // im
        }, { 0.32052368010063503,      // re
          0.73369743811466037          // im
        }, { 0.32164995687013853,      // re
          0.7347388780959635           // im
        }, { 0.32277782986281967,      // re
          0.73577858916571359          // im
        }, { 0.32390729642468408,      // re
          0.73681656887736979          // im
        }, { 0.32503835389798796,      // re
          0.737852814788466            // im
        }, { 0.32617099962124396,      // re
          0.73888732446061511          // im
        }, { 0.32730523092922714,      // re
          0.7399200954595162           // im
        }, { 0.32844104515298167,      // re
          0.74095112535495922          // im
        }, { 0.32957843961982691,      // re
          0.74198041172083107          // im
        }, { 0.330717411653364,        // re
          0.74300795213512172          // im
        }, { 0.33185795857348155,      // re
          0.74403374417992929          // im
        }, { 0.33300007769636253,      // re
          0.745057785441466            // im
        }, { 0.33414376633449028,      // re
          0.74608007351006378          // im
        }, { 0.33528902179665521,      // re
          0.74710060598018013          // im
        }, { 0.33643584138796023,      // re
          0.7481193804504036           // im
        }, { 0.33758422240982822,      // re
          0.74913639452345937          // im
        }, { 0.33873416216000773,      // re
          0.75015164580621507          // im
        }, { 0.33988565793257952,      // re
          0.75116513190968637          // im
        }, { 0.34103870701796268,      // re
          0.7521768504490427           // im
        }, { 0.34219330670292136,      // re
          0.75318679904361252          // im
        }, { 0.34334945427057106,      // re
          0.75419497531688917          // im
        }, { 0.34450714700038465,      // re
          0.75520137689653655          // im
        }, { 0.34566638216819956,      // re
          0.75620600141439454          // im
        }, { 0.34682715704622324,      // re
          0.75720884650648457          // im
        }, { 0.3479894689030405,       // re
          0.75820990981301528          // im
        }, { 0.349153315003619,        // re
          0.759209188978388            // im
        }, { 0.35031869260931681,      // re
          0.76020668165120242          // im
        }, { 0.35148559897788756,      // re
          0.76120238548426178          // im
        }, { 0.35265403136348794,      // re
          0.7621962981345789           // im
        }, { 0.35382398701668372,      // re
          0.76318841726338127          // im
        }, { 0.35499546318445607,      // re
          0.76417874053611679          // im
        }, { 0.35616845711020861,      // re
          0.765167265622459            // im
        }, { 0.35734296603377314,      // re
          0.76615399019631292          // im
        }, { 0.35851898719141695,      // re
          0.7671389119358204           // im
        }, { 0.35969651781584833,      // re
          0.76812202852336542          // im
        }, { 0.36087555513622427,      // re
          0.7691033376455797           // im
        }, { 0.36205609637815594,      // re
          0.7700828369933479           // im
        }, { 0.3632381387637158,       // re
          0.77106052426181382          // im
        }, { 0.36442167951144389,      // re
          0.77203639715038452          // im
        }, { 0.36560671583635451,      // re
          0.773010453362737            // im
        }, { 0.36679324494994281,      // re
          0.7739826906068229           // im
        }, { 0.36798126406019094,      // re
          0.77495310659487393          // im
        }, { 0.36917077037157553,      // re
          0.77592169904340769          // im
        }, { 0.370361761085073,        // re
          0.77688846567323244          // im
        }, { 0.3715542333981674,       // re
          0.77785340420945315          // im
        }, { 0.37274818450485592,      // re
          0.778816512381476            // im
        }, { 0.37394361159565648,      // re
          0.77977778792301455          // im
        }, { 0.37514051185761366,      // re
          0.78073722857209449          // im
        }, { 0.37633888247430547,      // re
          0.78169483207105939          // im
        }, { 0.37753872062585003,      // re
          0.78265059616657573          // im
        }, { 0.37874002348891245,      // re
          0.78360451860963831          // im
        }, { 0.3799427882367109,       // re
          0.78455659715557524          // im
        }, { 0.38114701203902368,      // re
          0.78550682956405393          // im
        }, { 0.38235269206219613,      // re
          0.78645521359908577          // im
        }, { 0.38355982546914635,      // re
          0.78740174702903143          // im
        }, { 0.38476840941937318,      // re
          0.78834642762660634          // im
        }, { 0.38597844106896151,      // re
          0.78928925316888565          // im
        }, { 0.38718991757059029,      // re
          0.79023022143731             // im
        }, { 0.38840283607353809,      // re
          0.7911693302176902           // im
        }, { 0.38961719372369052,      // re
          0.79210657730021239          // im
        }, { 0.39083298766354679,      // re
          0.79304196047944364          // im
        }, { 0.39205021503222637,      // re
          0.79397547755433717          // im
        }, { 0.39326887296547552,      // re
          0.794907126328237            // im
        }, { 0.39448895859567445,      // re
          0.79583690460888357          // im
        }, { 0.39571046905184404,      // re
          0.79676481020841883          // im
        }, { 0.39693340145965184,      // re
          0.79769084094339116          // im
        }, { 0.39815775294142,         // re
          0.79861499463476093          // im
        }, { 0.399383520616131,        // re
          0.799537269107905            // im
        }, { 0.40061070159943546,      // re
          0.80045766219262282          // im
        }, { 0.40183929300365762,      // re
          0.80137617172314024          // im
        }, { 0.40306929193780361,      // re
          0.80229279553811572          // im
        }, { 0.40430069550756664,      // re
          0.80320753148064494          // im
        }, { 0.40553350081533557,      // re
          0.8041203773982657           // im
        }, { 0.4067677049602002,       // re
          0.80503133114296366          // im
        }, { 0.408003305037959,        // re
          0.80594039057117628          // im
        }, { 0.40924029814112584,      // re
          0.80684755354379933          // im
        }, { 0.41047868135893606,      // re
          0.80775281792619036          // im
        }, { 0.41171845177735478,      // re
          0.808656181588175            // im
        }, { 0.41295960647908203,      // re
          0.80955764240405126          // im
        }, { 0.41420214254356114,      // re
          0.81045719825259477          // im
        }, { 0.41544605704698467,      // re
          0.81135484701706373          // im
        }, { 0.41669134706230171,      // re
          0.81225058658520388          // im
        }, { 0.41793800965922456,      // re
          0.81314441484925359          // im
        }, { 0.41918604190423547,      // re
          0.81403632970594841          // im
        }, { 0.42043544086059437,      // re
          0.81492632905652662          // im
        }, { 0.42168620358834441,      // re
          0.81581441080673378          // im
        }, { 0.42293832714432056,      // re
          0.81670057286682785          // im
        }, { 0.42419180858215466,      // re
          0.81758481315158371          // im
        }, { 0.42544664495228424,      // re
          0.81846712958029866          // im
        }, { 0.4267028333019578,       // re
          0.819347520076797            // im
        }, { 0.42796037067524295,      // re
          0.82022598256943469          // im
        }, { 0.42921925411303274,      // re
          0.82110251499110465          // im
        }, { 0.43047948065305286,      // re
          0.82197711527924155          // im
        }, { 0.43174104732986851,      // re
          0.82284978137582643          // im
        }, { 0.43300395117489132,      // re
          0.82372051122739143          // im
        }, { 0.43426818921638688,      // re
          0.82458930278502529          // im
        }, { 0.4355337584794805,       // re
          0.82545615400437755          // im
        }, { 0.43680065598616591,      // re
          0.82632106284566353          // im
        }, { 0.43806887875531064,      // re
          0.82718402727366913          // im
        }, { 0.43933842380266397,      // re
          0.8280450452577558           // im
        }, { 0.44060928814086386,      // re
          0.82890411477186487          // im
        }, { 0.4418814687794439,       // re
          0.829761233794523            // im
        }, { 0.4431549627248399,       // re
          0.83061640030884631          // im
        }, { 0.44442976698039782,      // re
          0.83146961230254524          // im
        }, { 0.44570587854638,         // re
          0.83232086776792968          // im
        }, { 0.44698329441997253,      // re
          0.83317016470191319          // im
        }, { 0.44826201159529266,      // re
          0.83401750110601813          // im
        }, { 0.44954202706339519,      // re
          0.83486287498638             // im
        }, { 0.45082333781228034,      // re
          0.8357062843537526           // im
        }, { 0.45210594082689981,      // re
          0.836547727223512            // im
        }, { 0.45338983308916514,      // re
          0.83738720161566194          // im
        }, { 0.45467501157795354,      // re
          0.83822470555483808          // im
        }, { 0.45596147326911618,      // re
          0.83906023707031274          // im
        }, { 0.45724921513548411,      // re
          0.83989379419599952          // im
        }, { 0.45853823414687656,      // re
          0.84072537497045807          // im
        }, { 0.45982852727010715,      // re
          0.84155497743689844          // im
        }, { 0.46112009146899158,      // re
          0.84238259964318585          // im
        }, { 0.46241292370435461,      // re
          0.84320823964184544          // im
        }, { 0.46370702093403682,      // re
          0.84403189549006641          // im
        }, { 0.46500238011290285,      // re
          0.84485356524970712          // im
        }, { 0.46629899819284704,      // re
          0.84567324698729907          // im
        }, { 0.4675968721228021,       // re
          0.84649093877405213          // im
        }, { 0.468895998848745,        // re
          0.84730663868585832          // im
        }, { 0.47019637531370539,      // re
          0.84812034480329723          // im
        }, { 0.47149799845777152,      // re
          0.84893205521163961          // im
        }, { 0.47280086521809872,      // re
          0.84974176800085255          // im
        }, { 0.47410497252891537,      // re
          0.85054948126560348          // im
        }, { 0.47541031732153105,      // re
          0.8513551931052652           // im
        }, { 0.47671689652434357,      // re
          0.85215890162391983          // im
        }, { 0.47802470706284561,      // re
          0.85296060493036363          // im
        }, { 0.47933374585963284,      // re
          0.85376030113811141          // im
        }, { 0.48064400983441036,      // re
          0.85455798836540053          // im
        }, { 0.48195549590400066,      // re
          0.855353664735196            // im
        }, { 0.48326820098235013,      // re
          0.85614732837519447          // im
        }, { 0.48458212198053707,      // re
          0.85693897741782876          // im
        }, { 0.48589725580677834,      // re
          0.85772861000027212          // im
        }, { 0.48721359936643704,      // re
          0.85851622426444274          // im
        }, { 0.4885311495620297,       // re
          0.85930181835700847          // im
        }, { 0.48984990329323319,      // re
          0.86008539042939014          // im
        }, { 0.491169857456893,        // re
          0.86086693863776731          // im
        }, { 0.49249100894702913,      // re
          0.8616464611430813           // im
        }, { 0.49381335465484477,      // re
          0.8624239561110405           // im
        }, { 0.49513689146873241,      // re
          0.86319942171212416          // im
        }, { 0.49646161627428242,      // re
          0.8639728561215867           // im
        }, { 0.49778752595428921,      // re
          0.86474425751946238          // im
        }, { 0.49911461738875929,      // re
          0.86551362409056909          // im
        }, { 0.50044288745491816,      // re
          0.866280954024513            // im
        }, { 0.50177233302721813,      // re
          0.86704624551569265          // im
        }, { 0.50310295097734548,      // re
          0.86780949676330332          // im
        }, { 0.50443473817422746,      // re
          0.8685707059713409           // im
        }, { 0.50576769148404033,      // re
          0.86932987134860684          // im
        }, { 0.507101807770216,        // re
          0.87008699110871146          // im
        }, { 0.5084370838934501,       // re
          0.870842063470079            // im
        }, { 0.50977351671170879,      // re
          0.87159508665595109          // im
        }, { 0.51111110308023688,      // re
          0.87234605889439154          // im
        }, { 0.512449839851564,        // re
          0.87309497841829009          // im
        }, { 0.51378972387551358,      // re
          0.87384184346536686          // im
        }, { 0.515130751999209,        // re
          0.87458665227817611          // im
        }, { 0.51647292106708131,      // re
          0.87532940310411089          // im
        }, { 0.51781622792087734,      // re
          0.8760700941954066           // im
        }, { 0.519160669399666,        // re
          0.87680872380914565          // im
        }, { 0.520506242339847,        // re
          0.87754529020726135          // im
        }, { 0.521852943575157,        // re
          0.87827979165654158          // im
        }, { 0.52320076993667786,      // re
          0.87901222642863353          // im
        }, { 0.52454971825284413,      // re
          0.87974259280004741          // im
        }, { 0.52589978534945,         // re
          0.88047088905216075          // im
        }, { 0.52725096804965721,      // re
          0.88119711347122209          // im
        }, { 0.5286032631740023,       // re
          0.881921264348355            // im
        }, { 0.52995666754040438,      // re
          0.88264333997956279          // im
        }, { 0.531311177964172,        // re
          0.88336333866573158          // im
        }, { 0.53266679125801164,      // re
          0.884081258712635            // im
        }, { 0.53402350423203382,      // re
          0.88479709843093779          // im
        }, { 0.53538131369376218,      // re
          0.8855108561362              // im
        }, { 0.53674021644813985,      // re
          0.88622253014888064          // im
        }, { 0.53810020929753732,      // re
          0.88693211879434219          // im
        }, { 0.53946128904176,         // re
          0.88763962040285393          // im
        }, { 0.540823452478056,        // re
          0.88834503330959635          // im
        }, { 0.54218669640112283,      // re
          0.88904835585466457          // im
        }, { 0.54355101760311608,      // re
          0.88974958638307278          // im
        }, { 0.54491641287365611,      // re
          0.89044872324475788          // im
        }, { 0.54628287899983619,      // re
          0.89114576479458318          // im
        }, { 0.54765041276622917,      // re
          0.89184070939234272          // im
        }, { 0.54901901095489614,      // re
          0.89253355540276458          // im
        }, { 0.55038867034539352,      // re
          0.89322430119551532          // im
        }, { 0.55175938771478017,      // re
          0.89391294514520325          // im
        }, { 0.55313115983762584,      // re
          0.8945994856313827           // im
        }, { 0.55450398348601826,      // re
          0.89528392103855758          // im
        }, { 0.5558778554295708,       // re
          0.89596624975618522          // im
        }, { 0.55725277243542992,      // re
          0.89664647017868015          // im
        }, { 0.55862873126828338,      // re
          0.89732458070541832          // im
        }, { 0.5600057286903668,       // re
          0.89800057974073988          // im
        }, { 0.56138376146147229,      // re
          0.89867446569395382          // im
        }, { 0.56276282633895591,      // re
          0.89934623697934157          // im
        }, { 0.56414292007774458,      // re
          0.90001589201616017          // im
        }, { 0.56552403943034435,      // re
          0.900683429228647            // im
        }, { 0.5669061811468481,       // re
          0.901348847046022            // im
        }, { 0.56828934197494274,      // re
          0.90201214390249318          // im
        }, { 0.56967351865991733,      // re
          0.90267331823725883          // im
        }, { 0.57105870794467051,      // re
          0.90333236849451182          // im
        }, { 0.57244490656971792,      // re
          0.90398929312344334          // im
        }, { 0.57383211127320033,      // re
          0.90464409057824624          // im
        }, { 0.57522031879089119,      // re
          0.90529675931811882          // im
        }, { 0.576609525856204,        // re
          0.90594729780726846          // im
        }, { 0.57799972920020037,      // re
          0.90659570451491533          // im
        }, { 0.57939092555159744,      // re
          0.90724197791529582          // im
        }, { 0.58078311163677609,      // re
          0.90788611648766626          // im
        }, { 0.58217628417978773,      // re
          0.90852811871630612          // im
        }, { 0.5835704399023629,       // re
          0.90916798309052238          // im
        }, { 0.58496557552391837,      // re
          0.90980570810465222          // im
        }, { 0.5863616877615655,       // re
          0.91044129225806725          // im
        }, { 0.58775877333011706,      // re
          0.91107473405517636          // im
        }, { 0.58915682894209609,      // re
          0.91170603200542988          // im
        }, { 0.59055585130774246,      // re
          0.91233518462332275          // im
        }, { 0.59195583713502131,      // re
          0.91296219042839821          // im
        }, { 0.59335678312963092,      // re
          0.91358704794525081          // im
        }, { 0.59475868599501014,      // re
          0.91420975570353069          // im
        }, { 0.59616154243234587,      // re
          0.9148303122379462           // im
        }, { 0.59756534914058157,      // re
          0.91544871608826783          // im
        }, { 0.59897010281642438,      // re
          0.91606496579933172          // im
        }, { 0.60037580015435321,      // re
          0.9166790599210427           // im
        }, { 0.60178243784662644,      // re
          0.91729099700837791          // im
        }, { 0.60319001258328964,      // re
          0.9179007756213905           // im
        }, { 0.60459852105218359,      // re
          0.91850839432521225          // im
        }, { 0.60600795993895185,      // re
          0.91911385169005777          // im
        }, { 0.60741832592704847,      // re
          0.91971714629122736          // im
        }, { 0.60882961569774618,      // re
          0.92031827670911059          // im
        }, { 0.61024182593014364,      // re
          0.92091724152918952          // im
        }, { 0.6116549533011737,       // re
          0.9215140393420419           // im
        }, { 0.61306899448561136,      // re
          0.92210866874334518          // im
        }, { 0.61448394615608115,      // re
          0.92270112833387863          // im
        }, { 0.615899804983065,        // re
          0.92329141671952764          // im
        }, { 0.61731656763491016,      // re
          0.92387953251128674          // im
        }, { 0.61873423077783762,      // re
          0.9244654743252626           // im
        }, { 0.62015279107594878,      // re
          0.92504924078267758          // im
        }, { 0.62157224519123444,      // re
          0.92563083050987272          // im
        }, { 0.62299258978358174,      // re
          0.92621024213831138          // im
        }, { 0.62441382151078284,      // re
          0.92678747430458175          // im
        }, { 0.625835937028542,        // re
          0.92736252565040111          // im
        }, { 0.6272589329904843,       // re
          0.92793539482261789          // im
        }, { 0.62868280604816251,      // re
          0.92850608047321559          // im
        }, { 0.6301075528510659,       // re
          0.92907458125931586          // im
        }, { 0.63153317004662768,      // re
          0.92964089584318121          // im
        }, { 0.63295965428023282,      // re
          0.93020502289221907          // im
        }, { 0.63438700219522615,      // re
          0.93076696107898371          // im
        }, { 0.63581521043292011,      // re
          0.93132670908118043          // im
        }, { 0.63724427563260277,      // re
          0.93188426558166815          // im
        }, { 0.63867419443154572,      // re
          0.93243962926846236          // im
        }, { 0.64010496346501189,      // re
          0.932992798834739            // im
        }, { 0.64153657936626352,      // re
          0.93354377297883617          // im
        }, { 0.64296903876657008,      // re
          0.93409255040425887          // im
        }, { 0.6444023382952162,       // re
          0.93463912981968078          // im
        }, { 0.64583647457950966,      // re
          0.93518350993894761          // im
        }, { 0.64727144424478933,      // re
          0.93572568948108037          // im
        }, { 0.64870724391443291,      // re
          0.93626566717027826          // im
        }, { 0.65014387020986508,      // re
          0.93680344173592156          // im
        }, { 0.65158131975056544,      // re
          0.937339011912575            // im
        }, { 0.65301958915407632,      // re
          0.93787237643998989          // im
        }, { 0.65445867503601085,      // re
          0.93840353406310806          // im
        }, { 0.65589857401006113,      // re
          0.9389324835320646           // im
        }, { 0.65733928268800557,      // re
          0.93945922360218992          // im
        }, { 0.65878079767971764,      // re
          0.93998375303401394          // im
        }, { 0.66022311559317315,      // re
          0.9405060705932683           // im
        }, { 0.66166623303445893,      // re
          0.94102617505088926          // im
        }, { 0.66311014660778,         // re
          0.94154406518302081          // im
        }, { 0.66455485291546834,      // re
          0.94205973977101731          // im
        }, { 0.66600034855799062,      // re
          0.94257319760144687          // im
        }, { 0.66744663013395578,      // re
          0.94308443746609349          // im
        }, { 0.66889369424012357,      // re
          0.94359345816196039          // im
        }, { 0.67034153747141256,      // re
          0.94410025849127266          // im
        }, { 0.67179015642090745,      // re
          0.94460483726148026          // im
        }, { 0.67323954767986827,      // re
          0.94510719328526061          // im
        }, { 0.67468970783773707,      // re
          0.94560732538052128          // im
        }, { 0.67614063348214715,      // re
          0.94610523237040345          // im
        }, { 0.67759232119893009,      // re
          0.94660091308328353          // im
        }, { 0.67904476757212473,      // re
          0.94709436635277722          // im
        }, { 0.68049796918398431,      // re
          0.94758559101774109          // im
        }, { 0.681951922614985,        // re
          0.94807458592227623          // im
        }, { 0.68340662444383415,      // re
          0.94856134991573027          // im
        }, { 0.68486207124747756,      // re
          0.94904588185270056          // im
        }, { 0.68631825960110848,      // re
          0.94952818059303667          // im
        }, { 0.68777518607817512,      // re
          0.950008245001843            // im
        }, { 0.68923284725038858,      // re
          0.9504860739494817           // im
        }, { 0.69069123968773127,      // re
          0.95096166631157508          // im
        }, { 0.69215035995846508,      // re
          0.95143502096900834          // im
        }, { 0.693610204629139,        // re
          0.95190613680793235          // im
        }, { 0.69507077026459763,      // re
          0.95237501271976588          // im
        }, { 0.69653205342798863,      // re
          0.95284164760119872          // im
        }, { 0.69799405068077192,      // re
          0.95330604035419386          // im
        }, { 0.69945675858272649,      // re
          0.95376818988599033          // im
        }, { 0.70092017369195947,      // re
          0.95422809510910567          // im
        }, { 0.70238429256491375,      // re
          0.95468575494133834          // im
        }, { 0.70384911175637621,      // re
          0.95514116830577078          // im
        }, { 0.70531462781948573,      // re
          0.95559433413077111          // im
        }, { 0.70678083730574137,      // re
          0.95604525134999641          // im
        }, { 0.70824773676501074,      // re
          0.9564939189023951           // im
        }, { 0.70971532274553772,      // re
          0.95694033573220882          // im
        }, { 0.71118359179395052,      // re
          0.95738450078897586          // im
        }, { 0.71265254045527049,      // re
          0.95782641302753291          // im
        }, { 0.71412216527291938,      // re
          0.95826607140801767          // im
        }, { 0.71559246278872812,      // re
          0.9587034748958716           // im
        }, { 0.71706342954294455,      // re
          0.95913862246184189          // im
        }, { 0.71853506207424211,      // re
          0.95957151308198452          // im
        }, { 0.72000735691972673,      // re
          0.960002145737666            // im
        }, { 0.721480310614947,        // re
          0.96043051941556579          // im
        }, { 0.7229539196939001,       // re
          0.96085663310767966          // im
        }, { 0.7244281806890418,       // re
          0.96128048581132064          // im
        }, { 0.72590309013129362,      // re
          0.96170207652912254          // im
        }, { 0.727378644550051,        // re
          0.96212140426904158          // im
        }, { 0.728854840473192,        // re
          0.96253846804435916          // im
        }, { 0.73033167442708491,      // re
          0.96295326687368388          // im
        }, { 0.73180914293659682,      // re
          0.963365799780954            // im
        }, { 0.73328724252510158,      // re
          0.96377606579543984          // im
        }, { 0.73476596971448815,      // re
          0.96418406395174583          // im
        }, { 0.73624532102516871,      // re
          0.96458979328981276          // im
        }, { 0.73772529297608647,      // re
          0.96499325285492032          // im
        }, { 0.73920588208472449,      // re
          0.9653944416976894           // im
        }, { 0.74068708486711377,      // re
          0.96579335887408368          // im
        }, { 0.742168897837841,        // re
          0.9661900034454125           // im
        }, { 0.74365131751005709,      // re
          0.96658437447833312          // im
        }, { 0.74513434039548543,      // re
          0.96697647104485207          // im
        }, { 0.74661796300442984,      // re
          0.96736629222232851          // im
        }, { 0.748102181845783,        // re
          0.96775383709347551          // im
        }, { 0.74958699342703472,      // re
          0.96813910474636244          // im
        }, { 0.75107239425427985,      // re
          0.96852209427441727          // im
        }, { 0.7525583808322267,       // re
          0.96890280477642887          // im
        }, { 0.75404494966420543,      // re
          0.96928123535654853          // im
        }, { 0.75553209725217585,      // re
          0.96965738512429245          // im
        }, { 0.75701982009673618,      // re
          0.970031253194544            // im
        }, { 0.75850811469713064,      // re
          0.9704028386875555           // im
        }, { 0.7599969775512585,       // re
          0.97077214072895035          // im
        }, { 0.76148640515568156,      // re
          0.97113915844972509          // im
        }, { 0.76297639400563277,      // re
          0.97150389098625178          // im
        }, { 0.76446694059502451,      // re
          0.9718663374802794           // im
        }, { 0.76595804141645663,      // re
          0.97222649707893627          // im
        }, { 0.76744969296122478,      // re
          0.97258436893473221          // im
        }, { 0.76894189171932892,      // re
          0.97293995220556018          // im
        }, { 0.7704346341794811,       // re
          0.97329324605469825          // im
        }, { 0.77192791682911421,      // re
          0.973644249650812            // im
        }, { 0.77342173615439,         // re
          0.97399296216795583          // im
        }, { 0.77491608864020711,      // re
          0.97433938278557586          // im
        }, { 0.77641097077021,         // re
          0.97468351068851067          // im
        }, { 0.77790637902679649,      // re
          0.97502534506699412          // im
        }, { 0.77940230989112647,      // re
          0.975364885116657            // im
        }, { 0.78089875984313017,      // re
          0.97570213003852857          // im
        }, { 0.78239572536151636,      // re
          0.976037079039039            // im
        }, { 0.78389320292378051,      // re
          0.97636973133002114          // im
        }, { 0.7853911890062133,       // re
          0.97670008612871184          // im
        }, { 0.78688968008390869,      // re
          0.97702814265775439          // im
        }, { 0.7883886726307725,       // re
          0.97735390014520007          // im
        }, { 0.78988816311953036,      // re
          0.97767735782450993          // im
        }, { 0.79138814802173651,      // re
          0.97799851493455714          // im
        }, { 0.79288862380778147,      // re
          0.97831737071962765          // im
        }, { 0.79438958694690076,      // re
          0.97863392442942321          // im
        }, { 0.79589103390718319,      // re
          0.9789481753190622           // im
        }, { 0.79739296115557889,      // re
          0.979260122649082            // im
        }, { 0.798895365157908,        // re
          0.97956976568544052          // im
        }, { 0.800398242378869,        // re
          0.97987710369951764          // im
        }, { 0.80190158928204647,      // re
          0.98018213596811743          // im
        }, { 0.80340540232991975,      // re
          0.98048486177346938          // im
        }, { 0.80490967798387181,      // re
          0.98078528040323043          // im
        }, { 0.80641441270419634,      // re
          0.98108339115048671          // im
        }, { 0.80791960295010756,      // re
          0.98137919331375456          // im
        }, { 0.80942524517974723,      // re
          0.98167268619698311          // im
        }, { 0.81093133585019384,      // re
          0.98196386910955524          // im
        }, { 0.81243787141747037,      // re
          0.98225274136628937          // im
        }, { 0.81394484833655334,      // re
          0.98253930228744124          // im
        }, { 0.81545226306138041,      // re
          0.98282355119870524          // im
        }, { 0.81696011204485908,      // re
          0.98310548743121629          // im
        }, { 0.81846839173887509,      // re
          0.98338511032155118          // im
        }, { 0.81997709859430046,      // re
          0.98366241921173025          // im
        }, { 0.82148622906100255,      // re
          0.98393741344921892          // im
        }, { 0.82299577958785131,      // re
          0.984210092386929            // im
        }, { 0.82450574662272857,      // re
          0.98448045538322093          // im
        }, { 0.82601612661253621,      // re
          0.98474850180190421          // im
        }, { 0.827526916003204,        // re
          0.98501423101223984          // im
        }, { 0.82903811123969873,      // re
          0.98527764238894122          // im
        }, { 0.83054970876603207,      // re
          0.98553873531217606          // im
        }, { 0.83206170502526877,      // re
          0.98579750916756748          // im
        }, { 0.833574096459536,        // re
          0.98605396334619544          // im
        }, { 0.83508687951003013,      // re
          0.98630809724459867          // im
        }, { 0.8366000506170268,       // re
          0.98655991026477541          // im
        }, { 0.83811360621988817,      // re
          0.98680940181418553          // im
        }, { 0.83962754275707174,      // re
          0.987056571305751            // im
        }, { 0.84114185666613861,      // re
          0.98730141815785843          // im
        }, { 0.8426565443837617,       // re
          0.98754394179435923          // im
        }, { 0.84417160234573474,      // re
          0.98778414164457218          // im
        }, { 0.84568702698697984,      // re
          0.98802201714328353          // im
        }, { 0.84720281474155656,      // re
          0.98825756773074946          // im
        }, { 0.84871896204266983,      // re
          0.98849079285269659          // im
        }, { 0.85023546532267846,      // re
          0.98872169196032378          // im
        }, { 0.85175232101310394,      // re
          0.988950264510303            // im
        }, { 0.85326952554463831,      // re
          0.989176509964781            // im
        }, { 0.85478707534715248,      // re
          0.98940042779138038          // im
        }, { 0.85630496684970558,      // re
          0.98962201746320089          // im
        }, { 0.85782319648055194,      // re
          0.98984127845882053          // im
        }, { 0.85934176066715073,      // re
          0.99005821026229712          // im
        }, { 0.86086065583617377,      // re
          0.99027281236316911          // im
        }, { 0.86237987841351393,      // re
          0.99048508425645709          // im
        }, { 0.86389942482429383,      // re
          0.99069502544266463          // im
        }, { 0.86541929149287378,      // re
          0.99090263542778             // im
        }, { 0.86693947484286094,      // re
          0.99110791372327689          // im
        }, { 0.86845997129711683,      // re
          0.99131085984611544          // im
        }, { 0.86998077727776668,      // re
          0.9915114733187439           // im
        }, { 0.87150188920620686,      // re
          0.99170975366909953          // im
        }, { 0.87302330350311408,      // re
          0.99190570043060933          // im
        }, { 0.87454501658845374,      // re
          0.9920993131421918           // im
        }, { 0.8760670248814878,       // re
          0.99229059134825737          // im
        }, { 0.87758932480078378,      // re
          0.99247953459871             // im
        }, { 0.879111912764223,        // re
          0.992666142448948            // im
        }, { 0.88063478518900862,      // re
          0.9928504144598651           // im
        }, { 0.882157938491675,        // re
          0.99303235019785141          // im
        }, { 0.88368136908809525,      // re
          0.9932119492347945           // im
        }, { 0.88520507339349,         // re
          0.99338921114808065          // im
        }, { 0.88672904782243567,      // re
          0.9935641355205953           // im
        }, { 0.88825328878887344,      // re
          0.9937367219407246           // im
        }, { 0.8897777927061169,       // re
          0.99390697000235606          // im
        }, { 0.89130255598686126,      // re
          0.99407487930487937          // im
        }, { 0.8928275750431911,       // re
          0.9942404494531879           // im
        }, { 0.8943528462865894,       // re
          0.9944036800576791           // im
        }, { 0.89587836612794547,      // re
          0.99456457073425542          // im
        }, { 0.89740413097756377,      // re
          0.9947231211043257           // im
        }, { 0.89893013724517212,      // re
          0.99487933079480562          // im
        }, { 0.90045638133993067,      // re
          0.99503319943811863          // im
        }, { 0.90198285967043934,      // re
          0.99518472667219693          // im
        }, { 0.90350956864474741,      // re
          0.99533391214048228          // im
        }, { 0.905036504670361,        // re
          0.99548075549192694          // im
        }, { 0.90656366415425227,      // re
          0.99562525638099431          // im
        }, { 0.90809104350286729,      // re
          0.99576741446765982          // im
        }, { 0.909618639122135,        // re
          0.99590722941741172          // im
        }, { 0.91114644741747541,      // re
          0.996044700901252            // im
        }, { 0.912674464793808,        // re
          0.996179828595697            // im
        }, { 0.91420268765556012,      // re
          0.996312612182778            // im
        }, { 0.91573111240667593,      // re
          0.99644305135004263          // im
        }, { 0.91725973545062434,      // re
          0.99657114579055484          // im
        }, { 0.91878855319040753,      // re
          0.99669689520289606          // im
        }, { 0.92031756202856985,      // re
          0.99682029929116567          // im
        }, { 0.92184675836720575,      // re
          0.99694135776498216          // im
        }, { 0.92337613860796852,      // re
          0.997060070339483            // im
        }, { 0.92490569915207865,      // re
          0.99717643673532619          // im
        }, { 0.92643543640033255,      // re
          0.99729045667869021          // im
        }, { 0.92796534675311071,      // re
          0.9974021299012753           // im
        }, { 0.92949542661038609,      // re
          0.99751145614030345          // im
        }, { 0.93102567237173328,      // re
          0.99761843513851955          // im
        }, { 0.932556080436336,        // re
          0.99772306664419164          // im
        }, { 0.93408664720299617,      // re
          0.99782535041111164          // im
        }, { 0.93561736907014259,      // re
          0.997925286198596            // im
        }, { 0.93714824243583861,      // re
          0.99802287377148624          // im
        }, { 0.93867926369779142,      // re
          0.99811811290014918          // im
        }, { 0.94021042925336018,      // re
          0.99821100336047819          // im
        }, { 0.9417417354995643,       // re
          0.99830154493389289          // im
        }, { 0.94327317883309225,      // re
          0.99838973740734016          // im
        }, { 0.94480475565031008,      // re
          0.99847558057329477          // im
        }, { 0.94633646234726942,      // re
          0.99855907422975931          // im
        }, { 0.94786829531971672,      // re
          0.99864021818026527          // im
        }, { 0.94940025096310077,      // re
          0.99871901223387294          // im
        }, { 0.950932325672582,        // re
          0.99879545620517241          // im
        }, { 0.9524645158430407,       // re
          0.99886954991428356          // im
        }, { 0.95399681786908541,      // re
          0.99894129318685687          // im
        }, { 0.95552922814506136,      // re
          0.99901068585407338          // im
        }, { 0.9570617430650592,       // re
          0.99907772775264536          // im
        }, { 0.95859435902292323,      // re
          0.99914241872481691          // im
        }, { 0.96012707241226014,      // re
          0.99920475861836389          // im
        }, { 0.96165987962644728,      // re
          0.99926474728659442          // im
        }, { 0.96319277705864115,      // re
          0.99932238458834954          // im
        }, { 0.96472576110178609,      // re
          0.99937767038800285          // im
        }, { 0.96625882814862241,      // re
          0.99943060455546173          // im
        }, { 0.96779197459169541,      // re
          0.999481186966167            // im
        }, { 0.96932519682336338,      // re
          0.99952941750109314          // im
        }, { 0.97085849123580625,      // re
          0.99957529604674922          // im
        }, { 0.97239185422103425,      // re
          0.99961882249517864          // im
        }, { 0.97392528217089613,      // re
          0.99965999674395922          // im
        }, { 0.9754587714770877,       // re
          0.99969881869620425          // im
        }, { 0.97699231853116064,      // re
          0.99973528826056168          // im
        }, { 0.97852591972453051,      // re
          0.99976940535121528          // im
        }, { 0.98005957144848554,      // re
          0.99980116988788426          // im
        }, { 0.98159327009419517,      // re
          0.9998305817958234           // im
        }, { 0.98312701205271824,      // re
          0.99985764100582386          // im
        }, { 0.98466079371501192,      // re
          0.99988234745421256          // im
        }, { 0.98619461147193965,      // re
          0.9999047010828529           // im
        }, { 0.98772846171428008,      // re
          0.9999247018391445           // im
        }, { 0.98926234083273545,      // re
          0.99994234967602391          // im
        }, { 0.99079624521794019,      // re
          0.9999576445519639           // im
        }, { 0.99233017126046885,      // re
          0.99997058643097414          // im
        }, { 0.99386411535084551,      // re
          0.99998117528260111          // im
        }, { 0.99539807387955148,      // re
          0.9999894110819284           // im
        }, { 0.996932043237034,        // re
          0.99999529380957619          // im
        }, { 0.99846601981371519,      // re
          0.99999882345170188          // im
        } };

      static const creal_T reconVar2[2048] = { { 1.0,// re
          1.0                          // im
        }, { 1.0015339801862848,       // re
          0.99999882345170188          // im
        }, { 1.0030679567629659,       // re
          0.99999529380957619          // im
        }, { 1.0046019261204486,       // re
          0.9999894110819284           // im
        }, { 1.0061358846491544,       // re
          0.99998117528260111          // im
        }, { 1.0076698287395311,       // re
          0.99997058643097414          // im
        }, { 1.0092037547820598,       // re
          0.9999576445519639           // im
        }, { 1.0107376591672645,       // re
          0.99994234967602391          // im
        }, { 1.01227153828572,         // re
          0.9999247018391445           // im
        }, { 1.0138053885280605,       // re
          0.9999047010828529           // im
        }, { 1.0153392062849882,       // re
          0.99988234745421256          // im
        }, { 1.0168729879472818,       // re
          0.99985764100582386          // im
        }, { 1.0184067299058048,       // re
          0.9998305817958234           // im
        }, { 1.0199404285515143,       // re
          0.99980116988788426          // im
        }, { 1.0214740802754696,       // re
          0.99976940535121528          // im
        }, { 1.0230076814688394,       // re
          0.99973528826056168          // im
        }, { 1.0245412285229123,       // re
          0.99969881869620425          // im
        }, { 1.0260747178291039,       // re
          0.99965999674395922          // im
        }, { 1.0276081457789656,       // re
          0.99961882249517864          // im
        }, { 1.0291415087641937,       // re
          0.99957529604674922          // im
        }, { 1.0306748031766366,       // re
          0.99952941750109314          // im
        }, { 1.0322080254083046,       // re
          0.999481186966167            // im
        }, { 1.0337411718513776,       // re
          0.99943060455546173          // im
        }, { 1.0352742388982139,       // re
          0.99937767038800285          // im
        }, { 1.0368072229413587,       // re
          0.99932238458834954          // im
        }, { 1.0383401203735527,       // re
          0.99926474728659442          // im
        }, { 1.0398729275877399,       // re
          0.99920475861836389          // im
        }, { 1.0414056409770767,       // re
          0.99914241872481691          // im
        }, { 1.0429382569349408,       // re
          0.99907772775264536          // im
        }, { 1.0444707718549386,       // re
          0.99901068585407338          // im
        }, { 1.0460031821309146,       // re
          0.99894129318685687          // im
        }, { 1.0475354841569593,       // re
          0.99886954991428356          // im
        }, { 1.0490676743274181,       // re
          0.99879545620517241          // im
        }, { 1.0505997490368992,       // re
          0.99871901223387294          // im
        }, { 1.0521317046802834,       // re
          0.99864021818026527          // im
        }, { 1.0536635376527306,       // re
          0.99855907422975931          // im
        }, { 1.05519524434969,         // re
          0.99847558057329477          // im
        }, { 1.0567268211669076,       // re
          0.99838973740734016          // im
        }, { 1.0582582645004357,       // re
          0.99830154493389289          // im
        }, { 1.0597895707466398,       // re
          0.99821100336047819          // im
        }, { 1.0613207363022086,       // re
          0.99811811290014918          // im
        }, { 1.0628517575641614,       // re
          0.99802287377148624          // im
        }, { 1.0643826309298574,       // re
          0.997925286198596            // im
        }, { 1.0659133527970037,       // re
          0.99782535041111164          // im
        }, { 1.067443919563664,        // re
          0.99772306664419164          // im
        }, { 1.0689743276282668,       // re
          0.99761843513851955          // im
        }, { 1.0705045733896139,       // re
          0.99751145614030345          // im
        }, { 1.0720346532468894,       // re
          0.9974021299012753           // im
        }, { 1.0735645635996673,       // re
          0.99729045667869021          // im
        }, { 1.0750943008479212,       // re
          0.99717643673532619          // im
        }, { 1.0766238613920316,       // re
          0.997060070339483            // im
        }, { 1.0781532416327941,       // re
          0.99694135776498216          // im
        }, { 1.07968243797143,         // re
          0.99682029929116567          // im
        }, { 1.0812114468095924,       // re
          0.99669689520289606          // im
        }, { 1.0827402645493758,       // re
          0.99657114579055484          // im
        }, { 1.084268887593324,        // re
          0.99644305135004263          // im
        }, { 1.08579731234444,         // re
          0.996312612182778            // im
        }, { 1.0873255352061921,       // re
          0.996179828595697            // im
        }, { 1.0888535525825247,       // re
          0.996044700901252            // im
        }, { 1.090381360877865,        // re
          0.99590722941741172          // im
        }, { 1.0919089564971327,       // re
          0.99576741446765982          // im
        }, { 1.0934363358457477,       // re
          0.99562525638099431          // im
        }, { 1.094963495329639,        // re
          0.99548075549192694          // im
        }, { 1.0964904313552526,       // re
          0.99533391214048228          // im
        }, { 1.0980171403295607,       // re
          0.99518472667219693          // im
        }, { 1.0995436186600693,       // re
          0.99503319943811863          // im
        }, { 1.1010698627548279,       // re
          0.99487933079480562          // im
        }, { 1.1025958690224362,       // re
          0.9947231211043257           // im
        }, { 1.1041216338720545,       // re
          0.99456457073425542          // im
        }, { 1.1056471537134107,       // re
          0.9944036800576791           // im
        }, { 1.1071724249568089,       // re
          0.9942404494531879           // im
        }, { 1.1086974440131387,       // re
          0.99407487930487937          // im
        }, { 1.110222207293883,        // re
          0.99390697000235606          // im
        }, { 1.1117467112111266,       // re
          0.9937367219407246           // im
        }, { 1.1132709521775643,       // re
          0.9935641355205953           // im
        }, { 1.11479492660651,         // re
          0.99338921114808065          // im
        }, { 1.1163186309119046,       // re
          0.9932119492347945           // im
        }, { 1.1178420615083249,       // re
          0.99303235019785141          // im
        }, { 1.1193652148109914,       // re
          0.9928504144598651           // im
        }, { 1.1208880872357772,       // re
          0.992666142448948            // im
        }, { 1.1224106751992162,       // re
          0.99247953459871             // im
        }, { 1.1239329751185121,       // re
          0.99229059134825737          // im
        }, { 1.1254549834115462,       // re
          0.9920993131421918           // im
        }, { 1.1269766964968859,       // re
          0.99190570043060933          // im
        }, { 1.1284981107937933,       // re
          0.99170975366909953          // im
        }, { 1.1300192227222334,       // re
          0.9915114733187439           // im
        }, { 1.1315400287028832,       // re
          0.99131085984611544          // im
        }, { 1.1330605251571391,       // re
          0.99110791372327689          // im
        }, { 1.1345807085071262,       // re
          0.99090263542778             // im
        }, { 1.1361005751757063,       // re
          0.99069502544266463          // im
        }, { 1.1376201215864861,       // re
          0.99048508425645709          // im
        }, { 1.1391393441638262,       // re
          0.99027281236316911          // im
        }, { 1.1406582393328493,       // re
          0.99005821026229712          // im
        }, { 1.1421768035194479,       // re
          0.98984127845882053          // im
        }, { 1.1436950331502944,       // re
          0.98962201746320089          // im
        }, { 1.1452129246528475,       // re
          0.98940042779138038          // im
        }, { 1.1467304744553617,       // re
          0.989176509964781            // im
        }, { 1.1482476789868961,       // re
          0.988950264510303            // im
        }, { 1.1497645346773215,       // re
          0.98872169196032378          // im
        }, { 1.1512810379573302,       // re
          0.98849079285269659          // im
        }, { 1.1527971852584433,       // re
          0.98825756773074946          // im
        }, { 1.1543129730130202,       // re
          0.98802201714328353          // im
        }, { 1.1558283976542651,       // re
          0.98778414164457218          // im
        }, { 1.1573434556162383,       // re
          0.98754394179435923          // im
        }, { 1.1588581433338614,       // re
          0.98730141815785843          // im
        }, { 1.1603724572429284,       // re
          0.987056571305751            // im
        }, { 1.1618863937801118,       // re
          0.98680940181418553          // im
        }, { 1.1633999493829732,       // re
          0.98655991026477541          // im
        }, { 1.1649131204899699,       // re
          0.98630809724459867          // im
        }, { 1.166425903540464,        // re
          0.98605396334619544          // im
        }, { 1.1679382949747312,       // re
          0.98579750916756748          // im
        }, { 1.1694502912339679,       // re
          0.98553873531217606          // im
        }, { 1.1709618887603013,       // re
          0.98527764238894122          // im
        }, { 1.1724730839967958,       // re
          0.98501423101223984          // im
        }, { 1.1739838733874639,       // re
          0.98474850180190421          // im
        }, { 1.1754942533772714,       // re
          0.98448045538322093          // im
        }, { 1.1770042204121487,       // re
          0.984210092386929            // im
        }, { 1.1785137709389975,       // re
          0.98393741344921892          // im
        }, { 1.1800229014056995,       // re
          0.98366241921173025          // im
        }, { 1.1815316082611249,       // re
          0.98338511032155118          // im
        }, { 1.1830398879551409,       // re
          0.98310548743121629          // im
        }, { 1.1845477369386197,       // re
          0.98282355119870524          // im
        }, { 1.1860551516634465,       // re
          0.98253930228744124          // im
        }, { 1.1875621285825295,       // re
          0.98225274136628937          // im
        }, { 1.1890686641498063,       // re
          0.98196386910955524          // im
        }, { 1.1905747548202528,       // re
          0.98167268619698311          // im
        }, { 1.1920803970498923,       // re
          0.98137919331375456          // im
        }, { 1.1935855872958037,       // re
          0.98108339115048671          // im
        }, { 1.1950903220161282,       // re
          0.98078528040323043          // im
        }, { 1.1965945976700803,       // re
          0.98048486177346938          // im
        }, { 1.1980984107179535,       // re
          0.98018213596811743          // im
        }, { 1.1996017576211311,       // re
          0.97987710369951764          // im
        }, { 1.201104634842092,        // re
          0.97956976568544052          // im
        }, { 1.2026070388444212,       // re
          0.979260122649082            // im
        }, { 1.2041089660928168,       // re
          0.9789481753190622           // im
        }, { 1.2056104130530994,       // re
          0.97863392442942321          // im
        }, { 1.2071113761922185,       // re
          0.97831737071962765          // im
        }, { 1.2086118519782634,       // re
          0.97799851493455714          // im
        }, { 1.2101118368804695,       // re
          0.97767735782450993          // im
        }, { 1.2116113273692275,       // re
          0.97735390014520007          // im
        }, { 1.2131103199160913,       // re
          0.97702814265775439          // im
        }, { 1.2146088109937867,       // re
          0.97670008612871184          // im
        }, { 1.2161067970762196,       // re
          0.97636973133002114          // im
        }, { 1.2176042746384836,       // re
          0.976037079039039            // im
        }, { 1.2191012401568697,       // re
          0.97570213003852857          // im
        }, { 1.2205976901088735,       // re
          0.975364885116657            // im
        }, { 1.2220936209732036,       // re
          0.97502534506699412          // im
        }, { 1.22358902922979,         // re
          0.97468351068851067          // im
        }, { 1.2250839113597929,       // re
          0.97433938278557586          // im
        }, { 1.22657826384561,         // re
          0.97399296216795583          // im
        }, { 1.2280720831708858,       // re
          0.973644249650812            // im
        }, { 1.2295653658205188,       // re
          0.97329324605469825          // im
        }, { 1.2310581082806711,       // re
          0.97293995220556018          // im
        }, { 1.2325503070387753,       // re
          0.97258436893473221          // im
        }, { 1.2340419585835434,       // re
          0.97222649707893627          // im
        }, { 1.2355330594049754,       // re
          0.9718663374802794           // im
        }, { 1.2370236059943671,       // re
          0.97150389098625178          // im
        }, { 1.2385135948443184,       // re
          0.97113915844972509          // im
        }, { 1.2400030224487415,       // re
          0.97077214072895035          // im
        }, { 1.2414918853028694,       // re
          0.9704028386875555           // im
        }, { 1.2429801799032638,       // re
          0.970031253194544            // im
        }, { 1.2444679027478243,       // re
          0.96965738512429245          // im
        }, { 1.2459550503357946,       // re
          0.96928123535654853          // im
        }, { 1.2474416191677733,       // re
          0.96890280477642887          // im
        }, { 1.2489276057457201,       // re
          0.96852209427441727          // im
        }, { 1.2504130065729653,       // re
          0.96813910474636244          // im
        }, { 1.2518978181542169,       // re
          0.96775383709347551          // im
        }, { 1.2533820369955702,       // re
          0.96736629222232851          // im
        }, { 1.2548656596045147,       // re
          0.96697647104485207          // im
        }, { 1.2563486824899428,       // re
          0.96658437447833312          // im
        }, { 1.2578311021621591,       // re
          0.9661900034454125           // im
        }, { 1.2593129151328863,       // re
          0.96579335887408368          // im
        }, { 1.2607941179152755,       // re
          0.9653944416976894           // im
        }, { 1.2622747070239135,       // re
          0.96499325285492032          // im
        }, { 1.2637546789748313,       // re
          0.96458979328981276          // im
        }, { 1.2652340302855118,       // re
          0.96418406395174583          // im
        }, { 1.2667127574748984,       // re
          0.96377606579543984          // im
        }, { 1.2681908570634031,       // re
          0.963365799780954            // im
        }, { 1.2696683255729151,       // re
          0.96295326687368388          // im
        }, { 1.271145159526808,        // re
          0.96253846804435916          // im
        }, { 1.272621355449949,        // re
          0.96212140426904158          // im
        }, { 1.2740969098687063,       // re
          0.96170207652912254          // im
        }, { 1.2755718193109582,       // re
          0.96128048581132064          // im
        }, { 1.2770460803061,          // re
          0.96085663310767966          // im
        }, { 1.278519689385053,        // re
          0.96043051941556579          // im
        }, { 1.2799926430802733,       // re
          0.960002145737666            // im
        }, { 1.2814649379257579,       // re
          0.95957151308198452          // im
        }, { 1.2829365704570554,       // re
          0.95913862246184189          // im
        }, { 1.2844075372112718,       // re
          0.9587034748958716           // im
        }, { 1.2858778347270805,       // re
          0.95826607140801767          // im
        }, { 1.2873474595447294,       // re
          0.95782641302753291          // im
        }, { 1.2888164082060496,       // re
          0.95738450078897586          // im
        }, { 1.2902846772544623,       // re
          0.95694033573220882          // im
        }, { 1.2917522632349892,       // re
          0.9564939189023951           // im
        }, { 1.2932191626942586,       // re
          0.95604525134999641          // im
        }, { 1.2946853721805143,       // re
          0.95559433413077111          // im
        }, { 1.2961508882436239,       // re
          0.95514116830577078          // im
        }, { 1.2976157074350863,       // re
          0.95468575494133834          // im
        }, { 1.2990798263080405,       // re
          0.95422809510910567          // im
        }, { 1.3005432414172735,       // re
          0.95376818988599033          // im
        }, { 1.302005949319228,        // re
          0.95330604035419386          // im
        }, { 1.3034679465720114,       // re
          0.95284164760119872          // im
        }, { 1.3049292297354023,       // re
          0.95237501271976588          // im
        }, { 1.306389795370861,        // re
          0.95190613680793235          // im
        }, { 1.3078496400415349,       // re
          0.95143502096900834          // im
        }, { 1.3093087603122688,       // re
          0.95096166631157508          // im
        }, { 1.3107671527496114,       // re
          0.9504860739494817           // im
        }, { 1.3122248139218249,       // re
          0.950008245001843            // im
        }, { 1.3136817403988914,       // re
          0.94952818059303667          // im
        }, { 1.3151379287525224,       // re
          0.94904588185270056          // im
        }, { 1.3165933755561658,       // re
          0.94856134991573027          // im
        }, { 1.3180480773850149,       // re
          0.94807458592227623          // im
        }, { 1.3195020308160157,       // re
          0.94758559101774109          // im
        }, { 1.3209552324278753,       // re
          0.94709436635277722          // im
        }, { 1.32240767880107,         // re
          0.94660091308328353          // im
        }, { 1.3238593665178529,       // re
          0.94610523237040345          // im
        }, { 1.3253102921622628,       // re
          0.94560732538052128          // im
        }, { 1.3267604523201317,       // re
          0.94510719328526061          // im
        }, { 1.3282098435790926,       // re
          0.94460483726148026          // im
        }, { 1.3296584625285874,       // re
          0.94410025849127266          // im
        }, { 1.3311063057598764,       // re
          0.94359345816196039          // im
        }, { 1.3325533698660443,       // re
          0.94308443746609349          // im
        }, { 1.3339996514420094,       // re
          0.94257319760144687          // im
        }, { 1.3354451470845317,       // re
          0.94205973977101731          // im
        }, { 1.33688985339222,         // re
          0.94154406518302081          // im
        }, { 1.3383337669655411,       // re
          0.94102617505088926          // im
        }, { 1.339776884406827,        // re
          0.9405060705932683           // im
        }, { 1.3412192023202825,       // re
          0.93998375303401394          // im
        }, { 1.3426607173119944,       // re
          0.93945922360218992          // im
        }, { 1.3441014259899389,       // re
          0.9389324835320646           // im
        }, { 1.3455413249639891,       // re
          0.93840353406310806          // im
        }, { 1.3469804108459238,       // re
          0.93787237643998989          // im
        }, { 1.3484186802494347,       // re
          0.937339011912575            // im
        }, { 1.349856129790135,        // re
          0.93680344173592156          // im
        }, { 1.351292756085567,        // re
          0.93626566717027826          // im
        }, { 1.3527285557552107,       // re
          0.93572568948108037          // im
        }, { 1.3541635254204905,       // re
          0.93518350993894761          // im
        }, { 1.3555976617047838,       // re
          0.93463912981968078          // im
        }, { 1.35703096123343,         // re
          0.93409255040425887          // im
        }, { 1.3584634206337365,       // re
          0.93354377297883617          // im
        }, { 1.3598950365349882,       // re
          0.932992798834739            // im
        }, { 1.3613258055684543,       // re
          0.93243962926846236          // im
        }, { 1.3627557243673971,       // re
          0.93188426558166815          // im
        }, { 1.36418478956708,         // re
          0.93132670908118043          // im
        }, { 1.365612997804774,        // re
          0.93076696107898371          // im
        }, { 1.3670403457197673,       // re
          0.93020502289221907          // im
        }, { 1.3684668299533724,       // re
          0.92964089584318121          // im
        }, { 1.369892447148934,        // re
          0.92907458125931586          // im
        }, { 1.3713171939518376,       // re
          0.92850608047321559          // im
        }, { 1.3727410670095157,       // re
          0.92793539482261789          // im
        }, { 1.374164062971458,        // re
          0.92736252565040111          // im
        }, { 1.3755861784892172,       // re
          0.92678747430458175          // im
        }, { 1.3770074102164183,       // re
          0.92621024213831138          // im
        }, { 1.3784277548087656,       // re
          0.92563083050987272          // im
        }, { 1.3798472089240512,       // re
          0.92504924078267758          // im
        }, { 1.3812657692221624,       // re
          0.9244654743252626           // im
        }, { 1.3826834323650898,       // re
          0.92387953251128674          // im
        }, { 1.3841001950169352,       // re
          0.92329141671952764          // im
        }, { 1.3855160538439188,       // re
          0.92270112833387863          // im
        }, { 1.3869310055143886,       // re
          0.92210866874334518          // im
        }, { 1.3883450466988263,       // re
          0.9215140393420419           // im
        }, { 1.3897581740698564,       // re
          0.92091724152918952          // im
        }, { 1.3911703843022538,       // re
          0.92031827670911059          // im
        }, { 1.3925816740729515,       // re
          0.91971714629122736          // im
        }, { 1.3939920400610482,       // re
          0.91911385169005777          // im
        }, { 1.3954014789478164,       // re
          0.91850839432521225          // im
        }, { 1.3968099874167104,       // re
          0.9179007756213905           // im
        }, { 1.3982175621533734,       // re
          0.91729099700837791          // im
        }, { 1.3996241998456469,       // re
          0.9166790599210427           // im
        }, { 1.4010298971835757,       // re
          0.91606496579933172          // im
        }, { 1.4024346508594183,       // re
          0.91544871608826783          // im
        }, { 1.4038384575676541,       // re
          0.9148303122379462           // im
        }, { 1.4052413140049897,       // re
          0.91420975570353069          // im
        }, { 1.4066432168703691,       // re
          0.91358704794525081          // im
        }, { 1.4080441628649787,       // re
          0.91296219042839821          // im
        }, { 1.4094441486922575,       // re
          0.91233518462332275          // im
        }, { 1.4108431710579039,       // re
          0.91170603200542988          // im
        }, { 1.4122412266698829,       // re
          0.91107473405517636          // im
        }, { 1.4136383122384344,       // re
          0.91044129225806725          // im
        }, { 1.4150344244760817,       // re
          0.90980570810465222          // im
        }, { 1.4164295600976371,       // re
          0.90916798309052238          // im
        }, { 1.4178237158202123,       // re
          0.90852811871630612          // im
        }, { 1.4192168883632239,       // re
          0.90788611648766626          // im
        }, { 1.4206090744484026,       // re
          0.90724197791529582          // im
        }, { 1.4220002707997996,       // re
          0.90659570451491533          // im
        }, { 1.4233904741437962,       // re
          0.90594729780726846          // im
        }, { 1.4247796812091087,       // re
          0.90529675931811882          // im
        }, { 1.4261678887267997,       // re
          0.90464409057824624          // im
        }, { 1.4275550934302821,       // re
          0.90398929312344334          // im
        }, { 1.4289412920553295,       // re
          0.90333236849451182          // im
        }, { 1.4303264813400827,       // re
          0.90267331823725883          // im
        }, { 1.4317106580250574,       // re
          0.90201214390249318          // im
        }, { 1.4330938188531519,       // re
          0.901348847046022            // im
        }, { 1.4344759605696558,       // re
          0.900683429228647            // im
        }, { 1.4358570799222554,       // re
          0.90001589201616017          // im
        }, { 1.4372371736610441,       // re
          0.89934623697934157          // im
        }, { 1.4386162385385277,       // re
          0.89867446569395382          // im
        }, { 1.4399942713096332,       // re
          0.89800057974073988          // im
        }, { 1.4413712687317166,       // re
          0.89732458070541832          // im
        }, { 1.44274722756457,         // re
          0.89664647017868015          // im
        }, { 1.4441221445704291,       // re
          0.89596624975618522          // im
        }, { 1.4454960165139816,       // re
          0.89528392103855758          // im
        }, { 1.4468688401623742,       // re
          0.8945994856313827           // im
        }, { 1.4482406122852198,       // re
          0.89391294514520325          // im
        }, { 1.4496113296546065,       // re
          0.89322430119551532          // im
        }, { 1.450980989045104,        // re
          0.89253355540276458          // im
        }, { 1.4523495872337708,       // re
          0.89184070939234272          // im
        }, { 1.4537171210001638,       // re
          0.89114576479458318          // im
        }, { 1.4550835871263439,       // re
          0.89044872324475788          // im
        }, { 1.4564489823968838,       // re
          0.88974958638307278          // im
        }, { 1.4578133035988772,       // re
          0.88904835585466457          // im
        }, { 1.459176547521944,        // re
          0.88834503330959635          // im
        }, { 1.46053871095824,         // re
          0.88763962040285393          // im
        }, { 1.4618997907024627,       // re
          0.88693211879434219          // im
        }, { 1.4632597835518601,       // re
          0.88622253014888064          // im
        }, { 1.4646186863062378,       // re
          0.8855108561362              // im
        }, { 1.4659764957679662,       // re
          0.88479709843093779          // im
        }, { 1.4673332087419884,       // re
          0.884081258712635            // im
        }, { 1.4686888220358281,       // re
          0.88336333866573158          // im
        }, { 1.4700433324595956,       // re
          0.88264333997956279          // im
        }, { 1.4713967368259977,       // re
          0.881921264348355            // im
        }, { 1.4727490319503427,       // re
          0.88119711347122209          // im
        }, { 1.47410021465055,         // re
          0.88047088905216075          // im
        }, { 1.4754502817471558,       // re
          0.87974259280004741          // im
        }, { 1.4767992300633221,       // re
          0.87901222642863353          // im
        }, { 1.4781470564248429,       // re
          0.87827979165654158          // im
        }, { 1.479493757660153,        // re
          0.87754529020726135          // im
        }, { 1.480839330600334,        // re
          0.87680872380914565          // im
        }, { 1.4821837720791227,       // re
          0.8760700941954066           // im
        }, { 1.4835270789329187,       // re
          0.87532940310411089          // im
        }, { 1.484869248000791,        // re
          0.87458665227817611          // im
        }, { 1.4862102761244864,       // re
          0.87384184346536686          // im
        }, { 1.487550160148436,        // re
          0.87309497841829009          // im
        }, { 1.4888888969197631,       // re
          0.87234605889439154          // im
        }, { 1.4902264832882912,       // re
          0.87159508665595109          // im
        }, { 1.4915629161065498,       // re
          0.870842063470079            // im
        }, { 1.4928981922297839,       // re
          0.87008699110871146          // im
        }, { 1.4942323085159597,       // re
          0.86932987134860684          // im
        }, { 1.4955652618257727,       // re
          0.8685707059713409           // im
        }, { 1.4968970490226545,       // re
          0.86780949676330332          // im
        }, { 1.4982276669727819,       // re
          0.86704624551569265          // im
        }, { 1.4995571125450819,       // re
          0.866280954024513            // im
        }, { 1.5008853826112407,       // re
          0.86551362409056909          // im
        }, { 1.5022124740457108,       // re
          0.86474425751946238          // im
        }, { 1.5035383837257177,       // re
          0.8639728561215867           // im
        }, { 1.5048631085312676,       // re
          0.86319942171212416          // im
        }, { 1.5061866453451551,       // re
          0.8624239561110405           // im
        }, { 1.5075089910529709,       // re
          0.8616464611430813           // im
        }, { 1.508830142543107,        // re
          0.86086693863776731          // im
        }, { 1.5101500967067669,       // re
          0.86008539042939014          // im
        }, { 1.5114688504379703,       // re
          0.85930181835700847          // im
        }, { 1.512786400633563,        // re
          0.85851622426444274          // im
        }, { 1.5141027441932216,       // re
          0.85772861000027212          // im
        }, { 1.5154178780194629,       // re
          0.85693897741782876          // im
        }, { 1.5167317990176499,       // re
          0.85614732837519447          // im
        }, { 1.5180445040959993,       // re
          0.855353664735196            // im
        }, { 1.5193559901655895,       // re
          0.85455798836540053          // im
        }, { 1.5206662541403673,       // re
          0.85376030113811141          // im
        }, { 1.5219752929371544,       // re
          0.85296060493036363          // im
        }, { 1.5232831034756564,       // re
          0.85215890162391983          // im
        }, { 1.5245896826784691,       // re
          0.8513551931052652           // im
        }, { 1.5258950274710847,       // re
          0.85054948126560348          // im
        }, { 1.5271991347819012,       // re
          0.84974176800085255          // im
        }, { 1.5285020015422286,       // re
          0.84893205521163961          // im
        }, { 1.5298036246862945,       // re
          0.84812034480329723          // im
        }, { 1.5311040011512551,       // re
          0.84730663868585832          // im
        }, { 1.5324031278771979,       // re
          0.84649093877405213          // im
        }, { 1.5337010018071529,       // re
          0.84567324698729907          // im
        }, { 1.5349976198870972,       // re
          0.84485356524970712          // im
        }, { 1.5362929790659632,       // re
          0.84403189549006641          // im
        }, { 1.5375870762956454,       // re
          0.84320823964184544          // im
        }, { 1.5388799085310083,       // re
          0.84238259964318585          // im
        }, { 1.540171472729893,        // re
          0.84155497743689844          // im
        }, { 1.5414617658531236,       // re
          0.84072537497045807          // im
        }, { 1.5427507848645159,       // re
          0.83989379419599952          // im
        }, { 1.5440385267308838,       // re
          0.83906023707031274          // im
        }, { 1.5453249884220464,       // re
          0.83822470555483808          // im
        }, { 1.5466101669108347,       // re
          0.83738720161566194          // im
        }, { 1.5478940591731,          // re
          0.836547727223512            // im
        }, { 1.5491766621877197,       // re
          0.8357062843537526           // im
        }, { 1.5504579729366048,       // re
          0.83486287498638             // im
        }, { 1.5517379884047073,       // re
          0.83401750110601813          // im
        }, { 1.5530167055800275,       // re
          0.83317016470191319          // im
        }, { 1.5542941214536201,       // re
          0.83232086776792968          // im
        }, { 1.5555702330196022,       // re
          0.83146961230254524          // im
        }, { 1.55684503727516,         // re
          0.83061640030884631          // im
        }, { 1.5581185312205561,       // re
          0.829761233794523            // im
        }, { 1.5593907118591361,       // re
          0.82890411477186487          // im
        }, { 1.5606615761973361,       // re
          0.8280450452577558           // im
        }, { 1.5619311212446894,       // re
          0.82718402727366913          // im
        }, { 1.5631993440138341,       // re
          0.82632106284566353          // im
        }, { 1.5644662415205195,       // re
          0.82545615400437755          // im
        }, { 1.5657318107836131,       // re
          0.82458930278502529          // im
        }, { 1.5669960488251087,       // re
          0.82372051122739143          // im
        }, { 1.5682589526701314,       // re
          0.82284978137582643          // im
        }, { 1.569520519346947,        // re
          0.82197711527924155          // im
        }, { 1.5707807458869674,       // re
          0.82110251499110465          // im
        }, { 1.5720396293247569,       // re
          0.82022598256943469          // im
        }, { 1.5732971666980422,       // re
          0.819347520076797            // im
        }, { 1.5745533550477158,       // re
          0.81846712958029866          // im
        }, { 1.5758081914178454,       // re
          0.81758481315158371          // im
        }, { 1.5770616728556794,       // re
          0.81670057286682785          // im
        }, { 1.5783137964116556,       // re
          0.81581441080673378          // im
        }, { 1.5795645591394056,       // re
          0.81492632905652662          // im
        }, { 1.5808139580957645,       // re
          0.81403632970594841          // im
        }, { 1.5820619903407755,       // re
          0.81314441484925359          // im
        }, { 1.5833086529376983,       // re
          0.81225058658520388          // im
        }, { 1.5845539429530153,       // re
          0.81135484701706373          // im
        }, { 1.5857978574564389,       // re
          0.81045719825259477          // im
        }, { 1.5870403935209181,       // re
          0.80955764240405126          // im
        }, { 1.5882815482226453,       // re
          0.808656181588175            // im
        }, { 1.5895213186410639,       // re
          0.80775281792619036          // im
        }, { 1.5907597018588742,       // re
          0.80684755354379933          // im
        }, { 1.591996694962041,        // re
          0.80594039057117628          // im
        }, { 1.5932322950397997,       // re
          0.80503133114296366          // im
        }, { 1.5944664991846644,       // re
          0.8041203773982657           // im
        }, { 1.5956993044924332,       // re
          0.80320753148064494          // im
        }, { 1.5969307080621964,       // re
          0.80229279553811572          // im
        }, { 1.5981607069963424,       // re
          0.80137617172314024          // im
        }, { 1.5993892984005647,       // re
          0.80045766219262282          // im
        }, { 1.6006164793838691,       // re
          0.799537269107905            // im
        }, { 1.60184224705858,         // re
          0.79861499463476093          // im
        }, { 1.6030665985403481,       // re
          0.79769084094339116          // im
        }, { 1.604289530948156,        // re
          0.79676481020841883          // im
        }, { 1.6055110414043257,       // re
          0.79583690460888357          // im
        }, { 1.6067311270345246,       // re
          0.794907126328237            // im
        }, { 1.6079497849677735,       // re
          0.79397547755433717          // im
        }, { 1.6091670123364532,       // re
          0.79304196047944364          // im
        }, { 1.6103828062763095,       // re
          0.79210657730021239          // im
        }, { 1.6115971639264619,       // re
          0.7911693302176902           // im
        }, { 1.6128100824294096,       // re
          0.79023022143731             // im
        }, { 1.6140215589310385,       // re
          0.78928925316888565          // im
        }, { 1.6152315905806267,       // re
          0.78834642762660634          // im
        }, { 1.6164401745308536,       // re
          0.78740174702903143          // im
        }, { 1.617647307937804,        // re
          0.78645521359908577          // im
        }, { 1.6188529879609763,       // re
          0.78550682956405393          // im
        }, { 1.6200572117632892,       // re
          0.78455659715557524          // im
        }, { 1.6212599765110876,       // re
          0.78360451860963831          // im
        }, { 1.62246127937415,         // re
          0.78265059616657573          // im
        }, { 1.6236611175256945,       // re
          0.78169483207105939          // im
        }, { 1.6248594881423863,       // re
          0.78073722857209449          // im
        }, { 1.6260563884043435,       // re
          0.77977778792301455          // im
        }, { 1.6272518154951441,       // re
          0.778816512381476            // im
        }, { 1.6284457666018326,       // re
          0.77785340420945315          // im
        }, { 1.6296382389149269,       // re
          0.77688846567323244          // im
        }, { 1.6308292296284246,       // re
          0.77592169904340769          // im
        }, { 1.6320187359398091,       // re
          0.77495310659487393          // im
        }, { 1.6332067550500571,       // re
          0.7739826906068229           // im
        }, { 1.6343932841636455,       // re
          0.773010453362737            // im
        }, { 1.6355783204885561,       // re
          0.77203639715038452          // im
        }, { 1.6367618612362842,       // re
          0.77106052426181382          // im
        }, { 1.6379439036218439,       // re
          0.7700828369933479           // im
        }, { 1.6391244448637758,       // re
          0.7691033376455797           // im
        }, { 1.6403034821841516,       // re
          0.76812202852336542          // im
        }, { 1.6414810128085831,       // re
          0.7671389119358204           // im
        }, { 1.642657033966227,        // re
          0.76615399019631292          // im
        }, { 1.6438315428897914,       // re
          0.765167265622459            // im
        }, { 1.6450045368155439,       // re
          0.76417874053611679          // im
        }, { 1.6461760129833163,       // re
          0.76318841726338127          // im
        }, { 1.6473459686365119,       // re
          0.7621962981345789           // im
        }, { 1.6485144010221124,       // re
          0.76120238548426178          // im
        }, { 1.6496813073906833,       // re
          0.76020668165120242          // im
        }, { 1.650846684996381,        // re
          0.759209188978388            // im
        }, { 1.6520105310969595,       // re
          0.75820990981301528          // im
        }, { 1.6531728429537766,       // re
          0.75720884650648457          // im
        }, { 1.6543336178318004,       // re
          0.75620600141439454          // im
        }, { 1.6554928529996153,       // re
          0.75520137689653655          // im
        }, { 1.6566505457294289,       // re
          0.75419497531688917          // im
        }, { 1.6578066932970787,       // re
          0.75318679904361252          // im
        }, { 1.6589612929820374,       // re
          0.7521768504490427           // im
        }, { 1.6601143420674205,       // re
          0.75116513190968637          // im
        }, { 1.6612658378399923,       // re
          0.75015164580621507          // im
        }, { 1.6624157775901718,       // re
          0.74913639452345937          // im
        }, { 1.6635641586120398,       // re
          0.7481193804504036           // im
        }, { 1.6647109782033449,       // re
          0.74710060598018013          // im
        }, { 1.6658562336655098,       // re
          0.74608007351006378          // im
        }, { 1.6669999223036376,       // re
          0.745057785441466            // im
        }, { 1.6681420414265185,       // re
          0.74403374417992929          // im
        }, { 1.669282588346636,        // re
          0.74300795213512172          // im
        }, { 1.6704215603801731,       // re
          0.74198041172083107          // im
        }, { 1.6715589548470184,       // re
          0.74095112535495922          // im
        }, { 1.6726947690707727,       // re
          0.7399200954595162           // im
        }, { 1.6738290003787561,       // re
          0.73888732446061511          // im
        }, { 1.674961646102012,        // re
          0.737852814788466            // im
        }, { 1.6760927035753159,       // re
          0.73681656887736979          // im
        }, { 1.6772221701371803,       // re
          0.73577858916571359          // im
        }, { 1.6783500431298615,       // re
          0.7347388780959635           // im
        }, { 1.679476319899365,        // re
          0.73369743811466037          // im
        }, { 1.680600997795453,        // re
          0.73265427167241282          // im
        }, { 1.6817240741716497,       // re
          0.73160938122389263          // im
        }, { 1.6828455463852481,       // re
          0.73056276922782759          // im
        }, { 1.6839654117973155,       // re
          0.729514438146997            // im
        }, { 1.6850836677727004,       // re
          0.7284643904482252           // im
        }, { 1.6862003116800386,       // re
          0.72741262860237577          // im
        }, { 1.6873153408917592,       // re
          0.726359155084346            // im
        }, { 1.6884287527840904,       // re
          0.72530397237306077          // im
        }, { 1.6895405447370668,       // re
          0.724247082951467            // im
        }, { 1.6906507141345346,       // re
          0.72318848930652746          // im
        }, { 1.6917592583641579,       // re
          0.72212819392921535          // im
        }, { 1.6928661748174245,       // re
          0.72106619931450811          // im
        }, { 1.6939714608896539,       // re
          0.72000250796138165          // im
        }, { 1.6950751139800009,       // re
          0.71893712237280449          // im
        }, { 1.6961771314914631,       // re
          0.71787004505573171          // im
        }, { 1.6972775108308866,       // re
          0.71680127852109954          // im
        }, { 1.6983762494089729,       // re
          0.71573082528381859          // im
        }, { 1.6994733446402837,       // re
          0.71465868786276909          // im
        }, { 1.7005687939432483,       // re
          0.71358486878079352          // im
        }, { 1.7016625947401685,       // re
          0.71250937056469243          // im
        }, { 1.7027547444572253,       // re
          0.71143219574521643          // im
        }, { 1.703845240524485,        // re
          0.71035334685706242          // im
        }, { 1.7049340803759048,       // re
          0.70927282643886569          // im
        }, { 1.7060212614493397,       // re
          0.7081906370331954           // im
        }, { 1.7071067811865475,       // re
          0.70710678118654757          // im
        }, { 1.7081906370331954,       // re
          0.70602126144933974          // im
        }, { 1.7092728264388657,       // re
          0.70493408037590488          // im
        }, { 1.7103533468570624,       // re
          0.70384524052448494          // im
        }, { 1.7114321957452163,       // re
          0.7027547444572253           // im
        }, { 1.7125093705646925,       // re
          0.70166259474016845          // im
        }, { 1.7135848687807935,       // re
          0.70056879394324834          // im
        }, { 1.714658687862769,        // re
          0.69947334464028377          // im
        }, { 1.7157308252838186,       // re
          0.69837624940897292          // im
        }, { 1.7168012785210995,       // re
          0.69727751083088652          // im
        }, { 1.7178700450557316,       // re
          0.696177131491463            // im
        }, { 1.7189371223728045,       // re
          0.69507511398000088          // im
        }, { 1.7200025079613817,       // re
          0.69397146088965389          // im
        }, { 1.721066199314508,        // re
          0.69286617481742463          // im
        }, { 1.7221281939292155,       // re
          0.69175925836415775          // im
        }, { 1.7231884893065275,       // re
          0.6906507141345346           // im
        }, { 1.7242470829514671,       // re
          0.68954054473706683          // im
        }, { 1.7253039723730608,       // re
          0.68842875278409044          // im
        }, { 1.726359155084346,        // re
          0.687315340891759            // im
        }, { 1.7274126286023757,       // re
          0.68620031168003859          // im
        }, { 1.7284643904482251,       // re
          0.68508366777270036          // im
        }, { 1.7295144381469969,       // re
          0.6839654117973154           // im
        }, { 1.7305627692278276,       // re
          0.68284554638524808          // im
        }, { 1.7316093812238926,       // re
          0.68172407417164971          // im
        }, { 1.7326542716724127,       // re
          0.680600997795453            // im
        }, { 1.7336974381146604,       // re
          0.679476319899365            // im
        }, { 1.7347388780959636,       // re
          0.67835004312986147          // im
        }, { 1.7357785891657136,       // re
          0.67722217013718033          // im
        }, { 1.7368165688773698,       // re
          0.67609270357531592          // im
        }, { 1.737852814788466,        // re
          0.674961646102012            // im
        }, { 1.7388873244606151,       // re
          0.673829000378756            // im
        }, { 1.7399200954595162,       // re
          0.67269476907077286          // im
        }, { 1.7409511253549592,       // re
          0.67155895484701833          // im
        }, { 1.7419804117208311,       // re
          0.67042156038017309          // im
        }, { 1.7430079521351218,       // re
          0.669282588346636            // im
        }, { 1.7440337441799292,       // re
          0.66814204142651845          // im
        }, { 1.7450577854414659,       // re
          0.66699992230363747          // im
        }, { 1.7460800735100639,       // re
          0.66585623366550972          // im
        }, { 1.7471006059801801,       // re
          0.66471097820334479          // im
        }, { 1.7481193804504036,       // re
          0.66356415861203977          // im
        }, { 1.7491363945234593,       // re
          0.66241577759017178          // im
        }, { 1.750151645806215,        // re
          0.66126583783999227          // im
        }, { 1.7511651319096864,       // re
          0.66011434206742048          // im
        }, { 1.7521768504490427,       // re
          0.65896129298203732          // im
        }, { 1.7531867990436125,       // re
          0.65780669329707864          // im
        }, { 1.7541949753168891,       // re
          0.65665054572942894          // im
        }, { 1.7552013768965367,       // re
          0.65549285299961535          // im
        }, { 1.7562060014143945,       // re
          0.65433361783180044          // im
        }, { 1.7572088465064846,       // re
          0.65317284295377676          // im
        }, { 1.7582099098130153,       // re
          0.6520105310969595           // im
        }, { 1.7592091889783878,       // re
          0.650846684996381            // im
        }, { 1.7602066816512023,       // re
          0.64968130739068319          // im
        }, { 1.7612023854842618,       // re
          0.64851440102211244          // im
        }, { 1.7621962981345789,       // re
          0.64734596863651206          // im
        }, { 1.7631884172633812,       // re
          0.64617601298331628          // im
        }, { 1.7641787405361167,       // re
          0.64500453681554393          // im
        }, { 1.7651672656224591,       // re
          0.64383154288979139          // im
        }, { 1.766153990196313,        // re
          0.64265703396622686          // im
        }, { 1.7671389119358203,       // re
          0.641481012808583            // im
        }, { 1.7681220285233654,       // re
          0.64030348218415167          // im
        }, { 1.7691033376455798,       // re
          0.63912444486377573          // im
        }, { 1.7700828369933479,       // re
          0.637943903621844            // im
        }, { 1.7710605242618138,       // re
          0.6367618612362842           // im
        }, { 1.7720363971503845,       // re
          0.63557832048855611          // im
        }, { 1.7730104533627369,       // re
          0.63439328416364549          // im
        }, { 1.773982690606823,        // re
          0.63320675505005719          // im
        }, { 1.7749531065948738,       // re
          0.63201873593980906          // im
        }, { 1.7759216990434077,       // re
          0.63082922962842447          // im
        }, { 1.7768884656732324,       // re
          0.629638238914927            // im
        }, { 1.7778534042094531,       // re
          0.6284457666018326           // im
        }, { 1.7788165123814759,       // re
          0.62725181549514408          // im
        }, { 1.7797777879230146,       // re
          0.62605638840434352          // im
        }, { 1.7807372285720944,       // re
          0.62485948814238634          // im
        }, { 1.7816948320710595,       // re
          0.62366111752569453          // im
        }, { 1.7826505961665757,       // re
          0.62246127937415             // im
        }, { 1.7836045186096383,       // re
          0.62125997651108755          // im
        }, { 1.7845565971555752,       // re
          0.6200572117632891           // im
        }, { 1.7855068295640539,       // re
          0.61885298796097632          // im
        }, { 1.7864552135990857,       // re
          0.61764730793780387          // im
        }, { 1.7874017470290315,       // re
          0.61644017453085365          // im
        }, { 1.7883464276266063,       // re
          0.61523159058062682          // im
        }, { 1.7892892531688855,       // re
          0.61402155893103849          // im
        }, { 1.79023022143731,         // re
          0.61281008242940971          // im
        }, { 1.79116933021769,         // re
          0.61159716392646191          // im
        }, { 1.7921065773002125,       // re
          0.61038280627630948          // im
        }, { 1.7930419604794436,       // re
          0.60916701233645321          // im
        }, { 1.7939754775543371,       // re
          0.60794978496777363          // im
        }, { 1.794907126328237,        // re
          0.60673112703452448          // im
        }, { 1.7958369046088836,       // re
          0.60551104140432555          // im
        }, { 1.7967648102084188,       // re
          0.604289530948156            // im
        }, { 1.7976908409433912,       // re
          0.60306659854034816          // im
        }, { 1.7986149946347609,       // re
          0.60184224705858             // im
        }, { 1.799537269107905,        // re
          0.600616479383869            // im
        }, { 1.8004576621926227,       // re
          0.59938929840056454          // im
        }, { 1.8013761717231402,       // re
          0.59816070699634238          // im
        }, { 1.8022927955381158,       // re
          0.59693070806219639          // im
        }, { 1.8032075314806448,       // re
          0.59569930449243336          // im
        }, { 1.8041203773982657,       // re
          0.59446649918466443          // im
        }, { 1.8050313311429638,       // re
          0.5932322950397998           // im
        }, { 1.8059403905711764,       // re
          0.591996694962041            // im
        }, { 1.8068475535437993,       // re
          0.59075970185887416          // im
        }, { 1.8077528179261904,       // re
          0.58952131864106394          // im
        }, { 1.808656181588175,        // re
          0.58828154822264522          // im
        }, { 1.8095576424040511,       // re
          0.587040393520918            // im
        }, { 1.8104571982525948,       // re
          0.58579785745643886          // im
        }, { 1.8113548470170637,       // re
          0.58455394295301533          // im
        }, { 1.8122505865852039,       // re
          0.58330865293769829          // im
        }, { 1.8131444148492535,       // re
          0.58206199034077544          // im
        }, { 1.8140363297059485,       // re
          0.58081395809576453          // im
        }, { 1.8149263290565267,       // re
          0.57956455913940563          // im
        }, { 1.8158144108067338,       // re
          0.57831379641165559          // im
        }, { 1.8167005728668277,       // re
          0.57706167285567944          // im
        }, { 1.8175848131515837,       // re
          0.57580819141784534          // im
        }, { 1.8184671295802985,       // re
          0.57455335504771576          // im
        }, { 1.819347520076797,        // re
          0.5732971666980422           // im
        }, { 1.8202259825694347,       // re
          0.572039629324757            // im
        }, { 1.8211025149911046,       // re
          0.57078074588696726          // im
        }, { 1.8219771152792417,       // re
          0.56952051934694714          // im
        }, { 1.8228497813758264,       // re
          0.56825895267013149          // im
        }, { 1.8237205112273913,       // re
          0.56699604882510868          // im
        }, { 1.8245893027850253,       // re
          0.56573181078361312          // im
        }, { 1.8254561540043777,       // re
          0.5644662415205195           // im
        }, { 1.8263210628456634,       // re
          0.56319934401383409          // im
        }, { 1.827184027273669,        // re
          0.56193112124468936          // im
        }, { 1.8280450452577557,       // re
          0.560661576197336            // im
        }, { 1.828904114771865,        // re
          0.55939071185913614          // im
        }, { 1.829761233794523,        // re
          0.5581185312205561           // im
        }, { 1.8306164003088463,       // re
          0.5568450372751601           // im
        }, { 1.8314696123025453,       // re
          0.55557023301960218          // im
        }, { 1.8323208677679297,       // re
          0.55429412145362             // im
        }, { 1.8331701647019132,       // re
          0.55301670558002747          // im
        }, { 1.8340175011060182,       // re
          0.55173798840470734          // im
        }, { 1.83486287498638,         // re
          0.55045797293660481          // im
        }, { 1.8357062843537526,       // re
          0.54917666218771966          // im
        }, { 1.836547727223512,        // re
          0.54789405917310019          // im
        }, { 1.837387201615662,        // re
          0.54661016691083486          // im
        }, { 1.838224705554838,        // re
          0.54532498842204646          // im
        }, { 1.8390602370703126,       // re
          0.54403852673088382          // im
        }, { 1.8398937941959996,       // re
          0.54275078486451589          // im
        }, { 1.8407253749704582,       // re
          0.54146176585312344          // im
        }, { 1.8415549774368984,       // re
          0.54017147272989285          // im
        }, { 1.842382599643186,        // re
          0.53887990853100842          // im
        }, { 1.8432082396418454,       // re
          0.53758707629564539          // im
        }, { 1.8440318954900663,       // re
          0.53629297906596318          // im
        }, { 1.8448535652497071,       // re
          0.53499761988709715          // im
        }, { 1.8456732469872992,       // re
          0.533701001807153            // im
        }, { 1.846490938774052,        // re
          0.5324031278771979           // im
        }, { 1.8473066386858583,       // re
          0.531104001151255            // im
        }, { 1.8481203448032972,       // re
          0.52980362468629461          // im
        }, { 1.8489320552116397,       // re
          0.52850200154222848          // im
        }, { 1.8497417680008525,       // re
          0.52719913478190128          // im
        }, { 1.8505494812656034,       // re
          0.52589502747108463          // im
        }, { 1.8513551931052652,       // re
          0.524589682678469            // im
        }, { 1.8521589016239197,       // re
          0.52328310347565643          // im
        }, { 1.8529606049303635,       // re
          0.52197529293715439          // im
        }, { 1.8537603011381114,       // re
          0.52066625414036716          // im
        }, { 1.8545579883654004,       // re
          0.51935599016558964          // im
        }, { 1.855353664735196,        // re
          0.51804450409599934          // im
        }, { 1.8561473283751946,       // re
          0.51673179901764987          // im
        }, { 1.8569389774178289,       // re
          0.51541787801946293          // im
        }, { 1.8577286100002721,       // re
          0.51410274419322166          // im
        }, { 1.8585162242644429,       // re
          0.512786400633563            // im
        }, { 1.8593018183570085,       // re
          0.5114688504379703           // im
        }, { 1.8600853904293901,       // re
          0.51015009670676681          // im
        }, { 1.8608669386377672,       // re
          0.508830142543107            // im
        }, { 1.8616464611430814,       // re
          0.50750899105297087          // im
        }, { 1.8624239561110405,       // re
          0.50618664534515523          // im
        }, { 1.8631994217121242,       // re
          0.50486310853126759          // im
        }, { 1.8639728561215867,       // re
          0.50353838372571758          // im
        }, { 1.8647442575194624,       // re
          0.50221247404571079          // im
        }, { 1.865513624090569,        // re
          0.50088538261124071          // im
        }, { 1.8662809540245129,       // re
          0.49955711254508184          // im
        }, { 1.8670462455156926,       // re
          0.49822766697278181          // im
        }, { 1.8678094967633032,       // re
          0.49689704902265447          // im
        }, { 1.868570705971341,        // re
          0.49556526182577254          // im
        }, { 1.8693298713486068,       // re
          0.49423230851595967          // im
        }, { 1.8700869911087115,       // re
          0.49289819222978404          // im
        }, { 1.8708420634700791,       // re
          0.4915629161065499           // im
        }, { 1.871595086655951,        // re
          0.49022648328829116          // im
        }, { 1.8723460588943914,       // re
          0.48888889691976317          // im
        }, { 1.87309497841829,         // re
          0.487550160148436            // im
        }, { 1.873841843465367,        // re
          0.48621027612448642          // im
        }, { 1.8745866522781762,       // re
          0.48486924800079106          // im
        }, { 1.8753294031041108,       // re
          0.48352707893291874          // im
        }, { 1.8760700941954065,       // re
          0.48218377207912272          // im
        }, { 1.8768087238091455,       // re
          0.48083933060033396          // im
        }, { 1.8775452902072614,       // re
          0.47949375766015295          // im
        }, { 1.8782797916565417,       // re
          0.478147056424843            // im
        }, { 1.8790122264286335,       // re
          0.47679923006332209          // im
        }, { 1.8797425928000475,       // re
          0.47545028174715587          // im
        }, { 1.8804708890521606,       // re
          0.47410021465054997          // im
        }, { 1.881197113471222,        // re
          0.47274903195034279          // im
        }, { 1.8819212643483549,       // re
          0.47139673682599764          // im
        }, { 1.8826433399795628,       // re
          0.47004333245959562          // im
        }, { 1.8833633386657316,       // re
          0.46868882203582796          // im
        }, { 1.884081258712635,        // re
          0.46733320874198842          // im
        }, { 1.8847970984309379,       // re
          0.46597649576796618          // im
        }, { 1.8855108561362,          // re
          0.46461868630623782          // im
        }, { 1.8862225301488806,       // re
          0.46325978355186015          // im
        }, { 1.8869321187943422,       // re
          0.46189979070246273          // im
        }, { 1.887639620402854,        // re
          0.46053871095824             // im
        }, { 1.8883450333095964,       // re
          0.45917654752194409          // im
        }, { 1.8890483558546647,       // re
          0.45781330359887717          // im
        }, { 1.8897495863830729,       // re
          0.45644898239688392          // im
        }, { 1.890448723244758,        // re
          0.45508358712634384          // im
        }, { 1.8911457647945831,       // re
          0.45371712100016387          // im
        }, { 1.8918407093923428,       // re
          0.45234958723377089          // im
        }, { 1.8925335554027645,       // re
          0.45098098904510386          // im
        }, { 1.8932243011955152,       // re
          0.44961132965460654          // im
        }, { 1.8939129451452033,       // re
          0.44824061228521989          // im
        }, { 1.8945994856313826,       // re
          0.44686884016237416          // im
        }, { 1.8952839210385575,       // re
          0.44549601651398174          // im
        }, { 1.8959662497561851,       // re
          0.4441221445704292           // im
        }, { 1.89664647017868,         // re
          0.44274722756457             // im
        }, { 1.8973245807054182,       // re
          0.44137126873171667          // im
        }, { 1.89800057974074,         // re
          0.43999427130963326          // im
        }, { 1.8986744656939538,       // re
          0.43861623853852766          // im
        }, { 1.8993462369793415,       // re
          0.43723717366104409          // im
        }, { 1.9000158920161603,       // re
          0.43585707992225547          // im
        }, { 1.900683429228647,        // re
          0.43447596056965565          // im
        }, { 1.901348847046022,        // re
          0.43309381885315196          // im
        }, { 1.9020121439024931,       // re
          0.43171065802505726          // im
        }, { 1.9026733182372588,       // re
          0.43032648134008261          // im
        }, { 1.9033323684945118,       // re
          0.42894129205532949          // im
        }, { 1.9039892931234434,       // re
          0.42755509343028208          // im
        }, { 1.9046440905782462,       // re
          0.42616788872679962          // im
        }, { 1.9052967593181189,       // re
          0.42477968120910881          // im
        }, { 1.9059472978072685,       // re
          0.42339047414379605          // im
        }, { 1.9065957045149153,       // re
          0.42200027079979968          // im
        }, { 1.9072419779152958,       // re
          0.42060907444840251          // im
        }, { 1.9078861164876662,       // re
          0.41921688836322391          // im
        }, { 1.9085281187163061,       // re
          0.41782371582021227          // im
        }, { 1.9091679830905224,       // re
          0.41642956009763715          // im
        }, { 1.9098057081046522,       // re
          0.41503442447608163          // im
        }, { 1.9104412922580671,       // re
          0.4136383122384345           // im
        }, { 1.9110747340551764,       // re
          0.41224122666988289          // im
        }, { 1.91170603200543,         // re
          0.41084317105790391          // im
        }, { 1.9123351846233227,       // re
          0.40944414869225759          // im
        }, { 1.9129621904283982,       // re
          0.40804416286497869          // im
        }, { 1.9135870479452508,       // re
          0.40664321687036903          // im
        }, { 1.9142097557035307,       // re
          0.40524131400498986          // im
        }, { 1.9148303122379462,       // re
          0.40383845756765407          // im
        }, { 1.9154487160882678,       // re
          0.40243465085941843          // im
        }, { 1.9160649657993316,       // re
          0.40102989718357562          // im
        }, { 1.9166790599210426,       // re
          0.39962419984564679          // im
        }, { 1.917290997008378,        // re
          0.39821756215337356          // im
        }, { 1.9179007756213906,       // re
          0.39680998741671031          // im
        }, { 1.9185083943252121,       // re
          0.39540147894781635          // im
        }, { 1.9191138516900579,       // re
          0.3939920400610481           // im
        }, { 1.9197171462912275,       // re
          0.39258167407295147          // im
        }, { 1.9203182767091107,       // re
          0.39117038430225387          // im
        }, { 1.9209172415291895,       // re
          0.38975817406985641          // im
        }, { 1.9215140393420418,       // re
          0.38834504669882625          // im
        }, { 1.9221086687433453,       // re
          0.38693100551438858          // im
        }, { 1.9227011283338786,       // re
          0.38551605384391885          // im
        }, { 1.9232914167195276,       // re
          0.38410019501693504          // im
        }, { 1.9238795325112867,       // re
          0.38268343236508978          // im
        }, { 1.9244654743252627,       // re
          0.38126576922216238          // im
        }, { 1.9250492407826776,       // re
          0.37984720892405116          // im
        }, { 1.9256308305098728,       // re
          0.37842775480876556          // im
        }, { 1.9262102421383114,       // re
          0.37700741021641826          // im
        }, { 1.9267874743045819,       // re
          0.37558617848921722          // im
        }, { 1.927362525650401,        // re
          0.37416406297145793          // im
        }, { 1.9279353948226179,       // re
          0.37274106700951576          // im
        }, { 1.9285060804732157,       // re
          0.37131719395183749          // im
        }, { 1.9290745812593157,       // re
          0.3698924471489341           // im
        }, { 1.9296408958431812,       // re
          0.36846682995337232          // im
        }, { 1.9302050228922192,       // re
          0.36704034571976718          // im
        }, { 1.9307669610789837,       // re
          0.36561299780477385          // im
        }, { 1.9313267090811803,       // re
          0.36418478956707989          // im
        }, { 1.9318842655816681,       // re
          0.36275572436739723          // im
        }, { 1.9324396292684622,       // re
          0.36132580556845428          // im
        }, { 1.9329927988347388,       // re
          0.35989503653498811          // im
        }, { 1.9335437729788363,       // re
          0.35846342063373654          // im
        }, { 1.9340925504042588,       // re
          0.35703096123343             // im
        }, { 1.9346391298196808,       // re
          0.35559766170478385          // im
        }, { 1.9351835099389476,       // re
          0.35416352542049034          // im
        }, { 1.9357256894810804,       // re
          0.35272855575521073          // im
        }, { 1.9362656671702783,       // re
          0.35129275608556709          // im
        }, { 1.9368034417359214,       // re
          0.34985612979013492          // im
        }, { 1.9373390119125751,       // re
          0.34841868024943456          // im
        }, { 1.9378723764399899,       // re
          0.34698041084592368          // im
        }, { 1.9384035340631081,       // re
          0.34554132496398909          // im
        }, { 1.9389324835320645,       // re
          0.34410142598993881          // im
        }, { 1.93945922360219,         // re
          0.34266071731199438          // im
        }, { 1.939983753034014,        // re
          0.34121920232028236          // im
        }, { 1.9405060705932682,       // re
          0.33977688440682685          // im
        }, { 1.9410261750508893,       // re
          0.33833376696554113          // im
        }, { 1.9415440651830207,       // re
          0.33688985339222005          // im
        }, { 1.9420597397710173,       // re
          0.3354451470845316           // im
        }, { 1.9425731976014469,       // re
          0.33399965144200938          // im
        }, { 1.9430844374660934,       // re
          0.33255336986604422          // im
        }, { 1.9435934581619603,       // re
          0.33110630575987643          // im
        }, { 1.9441002584912725,       // re
          0.32965846252858749          // im
        }, { 1.9446048372614801,       // re
          0.3282098435790925           // im
        }, { 1.9451071932852606,       // re
          0.32676045232013173          // im
        }, { 1.9456073253805213,       // re
          0.32531029216226293          // im
        }, { 1.9461052323704036,       // re
          0.32385936651785285          // im
        }, { 1.9466009130832835,       // re
          0.32240767880106985          // im
        }, { 1.9470943663527773,       // re
          0.32095523242787521          // im
        }, { 1.9475855910177411,       // re
          0.31950203081601569          // im
        }, { 1.9480745859222761,       // re
          0.31804807738501495          // im
        }, { 1.9485613499157304,       // re
          0.31659337555616585          // im
        }, { 1.9490458818527006,       // re
          0.31513792875252244          // im
        }, { 1.9495281805930367,       // re
          0.31368174039889152          // im
        }, { 1.950008245001843,        // re
          0.31222481392182488          // im
        }, { 1.9504860739494818,       // re
          0.31076715274961147          // im
        }, { 1.9509616663115752,       // re
          0.30930876031226873          // im
        }, { 1.9514350209690083,       // re
          0.30784964004153487          // im
        }, { 1.9519061368079322,       // re
          0.30638979537086092          // im
        }, { 1.9523750127197659,       // re
          0.30492922973540237          // im
        }, { 1.9528416476011987,       // re
          0.30346794657201132          // im
        }, { 1.9533060403541938,       // re
          0.30200594931922808          // im
        }, { 1.9537681898859902,       // re
          0.30054324141727345          // im
        }, { 1.9542280951091056,       // re
          0.29907982630804048          // im
        }, { 1.9546857549413383,       // re
          0.2976157074350862           // im
        }, { 1.9551411683057709,       // re
          0.29615088824362379          // im
        }, { 1.9555943341307711,       // re
          0.29468537218051433          // im
        }, { 1.9560452513499964,       // re
          0.29321916269425863          // im
        }, { 1.9564939189023951,       // re
          0.29175226323498926          // im
        }, { 1.9569403357322088,       // re
          0.29028467725446233          // im
        }, { 1.9573845007889759,       // re
          0.28881640820604948          // im
        }, { 1.9578264130275329,       // re
          0.28734745954472951          // im
        }, { 1.9582660714080178,       // re
          0.28587783472708062          // im
        }, { 1.9587034748958716,       // re
          0.28440753721127188          // im
        }, { 1.9591386224618419,       // re
          0.28293657045705539          // im
        }, { 1.9595715130819844,       // re
          0.28146493792575794          // im
        }, { 1.960002145737666,        // re
          0.27999264308027322          // im
        }, { 1.9604305194155658,       // re
          0.27851968938505306          // im
        }, { 1.9608566331076798,       // re
          0.2770460803060999           // im
        }, { 1.9612804858113206,       // re
          0.27557181931095814          // im
        }, { 1.9617020765291224,       // re
          0.27409690986870638          // im
        }, { 1.9621214042690416,       // re
          0.272621355449949            // im
        }, { 1.9625384680443592,       // re
          0.271145159526808            // im
        }, { 1.9629532668736838,       // re
          0.26966832557291509          // im
        }, { 1.9633657997809539,       // re
          0.26819085706340318          // im
        }, { 1.96377606579544,         // re
          0.26671275747489837          // im
        }, { 1.9641840639517458,       // re
          0.26523403028551179          // im
        }, { 1.9645897932898126,       // re
          0.26375467897483135          // im
        }, { 1.9649932528549203,       // re
          0.26227470702391359          // im
        }, { 1.9653944416976894,       // re
          0.26079411791527551          // im
        }, { 1.9657933588740837,       // re
          0.25931291513288623          // im
        }, { 1.9661900034454125,       // re
          0.257831102162159            // im
        }, { 1.9665843744783331,       // re
          0.25634868248994291          // im
        }, { 1.9669764710448521,       // re
          0.25486565960451457          // im
        }, { 1.9673662922223285,       // re
          0.25338203699557016          // im
        }, { 1.9677538370934755,       // re
          0.25189781815421697          // im
        }, { 1.9681391047463626,       // re
          0.25041300657296522          // im
        }, { 1.9685220942744173,       // re
          0.24892760574572015          // im
        }, { 1.968902804776429,        // re
          0.24744161916777327          // im
        }, { 1.9692812353565485,       // re
          0.24595505033579459          // im
        }, { 1.9696573851242924,       // re
          0.24446790274782415          // im
        }, { 1.9700312531945441,       // re
          0.24298017990326387          // im
        }, { 1.9704028386875554,       // re
          0.24149188530286933          // im
        }, { 1.9707721407289505,       // re
          0.2400030224487415           // im
        }, { 1.9711391584497251,       // re
          0.23851359484431842          // im
        }, { 1.9715038909862517,       // re
          0.2370236059943672           // im
        }, { 1.9718663374802794,       // re
          0.23553305940497549          // im
        }, { 1.9722264970789363,       // re
          0.23404195858354343          // im
        }, { 1.9725843689347322,       // re
          0.23255030703877524          // im
        }, { 1.9729399522055602,       // re
          0.23105810828067111          // im
        }, { 1.9732932460546984,       // re
          0.22956536582051887          // im
        }, { 1.973644249650812,        // re
          0.22807208317088573          // im
        }, { 1.9739929621679559,       // re
          0.22657826384561             // im
        }, { 1.9743393827855757,       // re
          0.22508391135979283          // im
        }, { 1.9746835106885108,       // re
          0.22358902922979             // im
        }, { 1.9750253450669941,       // re
          0.22209362097320351          // im
        }, { 1.975364885116657,        // re
          0.22059769010887351          // im
        }, { 1.9757021300385285,       // re
          0.2191012401568698           // im
        }, { 1.9760370790390391,       // re
          0.21760427463848364          // im
        }, { 1.976369731330021,        // re
          0.21610679707621952          // im
        }, { 1.9767000861287118,       // re
          0.21460881099378676          // im
        }, { 1.9770281426577543,       // re
          0.21311031991609136          // im
        }, { 1.9773539001452,          // re
          0.21161132736922755          // im
        }, { 1.97767735782451,         // re
          0.21011183688046961          // im
        }, { 1.9779985149345571,       // re
          0.20861185197826349          // im
        }, { 1.9783173707196275,       // re
          0.20711137619221856          // im
        }, { 1.9786339244294231,       // re
          0.20561041305309924          // im
        }, { 1.9789481753190623,       // re
          0.20410896609281687          // im
        }, { 1.979260122649082,        // re
          0.20260703884442113          // im
        }, { 1.9795697656854405,       // re
          0.2011046348420919           // im
        }, { 1.9798771036995175,       // re
          0.19960175762113097          // im
        }, { 1.9801821359681173,       // re
          0.19809841071795356          // im
        }, { 1.9804848617734694,       // re
          0.19659459767008022          // im
        }, { 1.9807852804032304,       // re
          0.19509032201612825          // im
        }, { 1.9810833911504866,       // re
          0.19358558729580361          // im
        }, { 1.9813791933137546,       // re
          0.19208039704989244          // im
        }, { 1.9816726861969831,       // re
          0.19057475482025274          // im
        }, { 1.9819638691095554,       // re
          0.18906866414980619          // im
        }, { 1.9822527413662894,       // re
          0.1875621285825296           // im
        }, { 1.9825393022874414,       // re
          0.18605515166344663          // im
        }, { 1.9828235511987051,       // re
          0.18454773693861962          // im
        }, { 1.9831054874312164,       // re
          0.18303988795514095          // im
        }, { 1.9833851103215512,       // re
          0.18153160826112497          // im
        }, { 1.9836624192117303,       // re
          0.18002290140569951          // im
        }, { 1.9839374134492189,       // re
          0.17851377093899751          // im
        }, { 1.984210092386929,        // re
          0.17700422041214875          // im
        }, { 1.9844804553832209,       // re
          0.17549425337727143          // im
        }, { 1.9847485018019042,       // re
          0.17398387338746382          // im
        }, { 1.9850142310122398,       // re
          0.17247308399679595          // im
        }, { 1.9852776423889411,       // re
          0.17096188876030122          // im
        }, { 1.9855387353121761,       // re
          0.16945029123396796          // im
        }, { 1.9857975091675675,       // re
          0.16793829497473117          // im
        }, { 1.9860539633461953,       // re
          0.1664259035404641           // im
        }, { 1.9863080972445988,       // re
          0.16491312048996992          // im
        }, { 1.9865599102647753,       // re
          0.16339994938297323          // im
        }, { 1.9868094018141855,       // re
          0.16188639378011183          // im
        }, { 1.9870565713057511,       // re
          0.16037245724292828          // im
        }, { 1.9873014181578585,       // re
          0.15885814333386145          // im
        }, { 1.9875439417943592,       // re
          0.15734345561623825          // im
        }, { 1.9877841416445721,       // re
          0.15582839765426523          // im
        }, { 1.9880220171432836,       // re
          0.1543129730130201           // im
        }, { 1.9882575677307495,       // re
          0.15279718525844344          // im
        }, { 1.9884907928526965,       // re
          0.15128103795733022          // im
        }, { 1.9887216919603237,       // re
          0.14976453467732151          // im
        }, { 1.988950264510303,        // re
          0.14824767898689603          // im
        }, { 1.9891765099647811,       // re
          0.14673047445536175          // im
        }, { 1.9894004277913804,       // re
          0.14521292465284746          // im
        }, { 1.9896220174632009,       // re
          0.14369503315029447          // im
        }, { 1.9898412784588206,       // re
          0.14217680351944803          // im
        }, { 1.9900582102622972,       // re
          0.14065823933284921          // im
        }, { 1.9902728123631692,       // re
          0.1391393441638262           // im
        }, { 1.990485084256457,        // re
          0.13762012158648604          // im
        }, { 1.9906950254426645,       // re
          0.1361005751757062           // im
        }, { 1.99090263542778,         // re
          0.13458070850712617          // im
        }, { 1.991107913723277,        // re
          0.13306052515713906          // im
        }, { 1.9913108598461156,       // re
          0.13154002870288312          // im
        }, { 1.9915114733187438,       // re
          0.13001922272223335          // im
        }, { 1.9917097536690995,       // re
          0.12849811079379317          // im
        }, { 1.9919057004306093,       // re
          0.12697669649688587          // im
        }, { 1.9920993131421918,       // re
          0.12545498341154623          // im
        }, { 1.9922905913482574,       // re
          0.12393297511851216          // im
        }, { 1.99247953459871,         // re
          0.1224106751992162           // im
        }, { 1.992666142448948,        // re
          0.12088808723577708          // im
        }, { 1.9928504144598651,       // re
          0.11936521481099135          // im
        }, { 1.9930323501978515,       // re
          0.11784206150832498          // im
        }, { 1.9932119492347944,       // re
          0.11631863091190475          // im
        }, { 1.9933892111480807,       // re
          0.11479492660651008          // im
        }, { 1.9935641355205953,       // re
          0.11327095217756435          // im
        }, { 1.9937367219407247,       // re
          0.11174671121112659          // im
        }, { 1.9939069700023562,       // re
          0.11022220729388306          // im
        }, { 1.9940748793048795,       // re
          0.10869744401313872          // im
        }, { 1.994240449453188,        // re
          0.10717242495680884          // im
        }, { 1.9944036800576792,       // re
          0.10564715371341062          // im
        }, { 1.9945645707342554,       // re
          0.10412163387205459          // im
        }, { 1.9947231211043257,       // re
          0.10259586902243628          // im
        }, { 1.9948793307948056,       // re
          0.10106986275482782          // im
        }, { 1.9950331994381187,       // re
          0.099543618660069319         // im
        }, { 1.9951847266721969,       // re
          0.0980171403295606           // im
        }, { 1.9953339121404823,       // re
          0.096490431355252593         // im
        }, { 1.9954807554919269,       // re
          0.094963495329638992         // im
        }, { 1.9956252563809942,       // re
          0.093436335845747787         // im
        }, { 1.9957674144676598,       // re
          0.091908956497132724         // im
        }, { 1.9959072294174116,       // re
          0.090381360877864983         // im
        }, { 1.9960447009012521,       // re
          0.0888535525825246           // im
        }, { 1.9961798285956971,       // re
          0.087325535206192059         // im
        }, { 1.9963126121827779,       // re
          0.0857973123444399           // im
        }, { 1.9964430513500426,       // re
          0.084268887593324071         // im
        }, { 1.9965711457905548,       // re
          0.082740264549375692         // im
        }, { 1.9966968952028961,       // re
          0.081211446809592441         // im
        }, { 1.9968202992911657,       // re
          0.079682437971430126         // im
        }, { 1.9969413577649822,       // re
          0.078153241632794232         // im
        }, { 1.997060070339483,        // re
          0.076623861392031492         // im
        }, { 1.9971764367353262,       // re
          0.0750943008479213           // im
        }, { 1.9972904566786902,       // re
          0.073564563599667426         // im
        }, { 1.9974021299012752,       // re
          0.072034653246889332         // im
        }, { 1.9975114561403036,       // re
          0.070504573389613856         // im
        }, { 1.9976184351385196,       // re
          0.068974327628266746         // im
        }, { 1.9977230666441916,       // re
          0.067443919563664051         // im
        }, { 1.9978253504111116,       // re
          0.0659133527970038           // im
        }, { 1.9979252861985959,       // re
          0.064382630929857465         // im
        }, { 1.9980228737714862,       // re
          0.0628517575641614           // im
        }, { 1.9981181129001491,       // re
          0.061320736302208578         // im
        }, { 1.9982110033604781,       // re
          0.059789570746639868         // im
        }, { 1.9983015449338928,       // re
          0.058258264500435752         // im
        }, { 1.99838973740734,         // re
          0.056726821166907748         // im
        }, { 1.9984755805732948,       // re
          0.055195244349689941         // im
        }, { 1.9985590742297594,       // re
          0.05366353765273052          // im
        }, { 1.9986402181802654,       // re
          0.052131704680283324         // im
        }, { 1.9987190122338729,       // re
          0.050599749036899282         // im
        }, { 1.9987954562051724,       // re
          0.049067674327418015         // im
        }, { 1.9988695499142834,       // re
          0.0475354841569593           // im
        }, { 1.9989412931868569,       // re
          0.046003182130914623         // im
        }, { 1.9990106858540733,       // re
          0.044470771854938668         // im
        }, { 1.9990777277526455,       // re
          0.04293825693494082          // im
        }, { 1.999142418724817,        // re
          0.041405640977076739         // im
        }, { 1.9992047586183639,       // re
          0.039872927587739811         // im
        }, { 1.9992647472865945,       // re
          0.038340120373552694         // im
        }, { 1.9993223845883494,       // re
          0.036807222941358832         // im
        }, { 1.9993776703880028,       // re
          0.035274238898213947         // im
        }, { 1.9994306045554617,       // re
          0.03374117185137758          // im
        }, { 1.9994811869661668,       // re
          0.032208025408304586         // im
        }, { 1.9995294175010931,       // re
          0.030674803176636626         // im
        }, { 1.9995752960467492,       // re
          0.029141508764193722         // im
        }, { 1.9996188224951785,       // re
          0.02760814577896574          // im
        }, { 1.9996599967439592,       // re
          0.0260747178291039           // im
        }, { 1.9996988186962041,       // re
          0.024541228522912288         // im
        }, { 1.9997352882605617,       // re
          0.023007681468839369         // im
        }, { 1.9997694053512154,       // re
          0.021474080275469508         // im
        }, { 1.9998011698878844,       // re
          0.019940428551514441         // im
        }, { 1.9998305817958233,       // re
          0.01840672990580482          // im
        }, { 1.999857641005824,        // re
          0.01687298794728171          // im
        }, { 1.9998823474542125,       // re
          0.0153392062849881           // im
        }, { 1.999904701082853,        // re
          0.013805388528060391         // im
        }, { 1.9999247018391446,       // re
          0.012271538285719925         // im
        }, { 1.999942349676024,        // re
          0.010737659167264491         // im
        }, { 1.999957644551964,        // re
          0.00920375478205982          // im
        }, { 1.9999705864309743,       // re
          0.007669828739531097         // im
        }, { 1.9999811752826011,       // re
          0.0061358846491544753        // im
        }, { 1.9999894110819283,       // re
          0.0046019261204485705        // im
        }, { 1.9999952938095762,       // re
          0.0030679567629659761        // im
        }, { 1.9999988234517019,       // re
          0.0015339801862847655        // im
        }, { 2.0,                      // re
          0.0                          // im
        }, { 1.9999988234517019,       // re
          -0.0015339801862847655       // im
        }, { 1.9999952938095762,       // re
          -0.0030679567629659761       // im
        }, { 1.9999894110819283,       // re
          -0.0046019261204485705       // im
        }, { 1.9999811752826011,       // re
          -0.0061358846491544753       // im
        }, { 1.9999705864309743,       // re
          -0.007669828739531097        // im
        }, { 1.999957644551964,        // re
          -0.00920375478205982         // im
        }, { 1.999942349676024,        // re
          -0.010737659167264491        // im
        }, { 1.9999247018391446,       // re
          -0.012271538285719925        // im
        }, { 1.999904701082853,        // re
          -0.013805388528060391        // im
        }, { 1.9998823474542125,       // re
          -0.0153392062849881          // im
        }, { 1.999857641005824,        // re
          -0.01687298794728171         // im
        }, { 1.9998305817958233,       // re
          -0.01840672990580482         // im
        }, { 1.9998011698878844,       // re
          -0.019940428551514441        // im
        }, { 1.9997694053512154,       // re
          -0.021474080275469508        // im
        }, { 1.9997352882605617,       // re
          -0.023007681468839369        // im
        }, { 1.9996988186962041,       // re
          -0.024541228522912288        // im
        }, { 1.9996599967439592,       // re
          -0.0260747178291039          // im
        }, { 1.9996188224951785,       // re
          -0.02760814577896574         // im
        }, { 1.9995752960467492,       // re
          -0.029141508764193722        // im
        }, { 1.9995294175010931,       // re
          -0.030674803176636626        // im
        }, { 1.9994811869661668,       // re
          -0.032208025408304586        // im
        }, { 1.9994306045554617,       // re
          -0.03374117185137758         // im
        }, { 1.9993776703880028,       // re
          -0.035274238898213947        // im
        }, { 1.9993223845883494,       // re
          -0.036807222941358832        // im
        }, { 1.9992647472865945,       // re
          -0.038340120373552694        // im
        }, { 1.9992047586183639,       // re
          -0.039872927587739811        // im
        }, { 1.999142418724817,        // re
          -0.041405640977076739        // im
        }, { 1.9990777277526455,       // re
          -0.04293825693494082         // im
        }, { 1.9990106858540733,       // re
          -0.044470771854938668        // im
        }, { 1.9989412931868569,       // re
          -0.046003182130914623        // im
        }, { 1.9988695499142834,       // re
          -0.0475354841569593          // im
        }, { 1.9987954562051724,       // re
          -0.049067674327418015        // im
        }, { 1.9987190122338729,       // re
          -0.050599749036899282        // im
        }, { 1.9986402181802654,       // re
          -0.052131704680283324        // im
        }, { 1.9985590742297594,       // re
          -0.05366353765273052         // im
        }, { 1.9984755805732948,       // re
          -0.055195244349689941        // im
        }, { 1.99838973740734,         // re
          -0.056726821166907748        // im
        }, { 1.9983015449338928,       // re
          -0.058258264500435752        // im
        }, { 1.9982110033604781,       // re
          -0.059789570746639868        // im
        }, { 1.9981181129001491,       // re
          -0.061320736302208578        // im
        }, { 1.9980228737714862,       // re
          -0.0628517575641614          // im
        }, { 1.9979252861985959,       // re
          -0.064382630929857465        // im
        }, { 1.9978253504111116,       // re
          -0.0659133527970038          // im
        }, { 1.9977230666441916,       // re
          -0.067443919563664051        // im
        }, { 1.9976184351385196,       // re
          -0.068974327628266746        // im
        }, { 1.9975114561403036,       // re
          -0.070504573389613856        // im
        }, { 1.9974021299012752,       // re
          -0.072034653246889332        // im
        }, { 1.9972904566786902,       // re
          -0.073564563599667426        // im
        }, { 1.9971764367353262,       // re
          -0.0750943008479213          // im
        }, { 1.997060070339483,        // re
          -0.076623861392031492        // im
        }, { 1.9969413577649822,       // re
          -0.078153241632794232        // im
        }, { 1.9968202992911657,       // re
          -0.079682437971430126        // im
        }, { 1.9966968952028961,       // re
          -0.081211446809592441        // im
        }, { 1.9965711457905548,       // re
          -0.082740264549375692        // im
        }, { 1.9964430513500426,       // re
          -0.084268887593324071        // im
        }, { 1.9963126121827779,       // re
          -0.0857973123444399          // im
        }, { 1.9961798285956971,       // re
          -0.087325535206192059        // im
        }, { 1.9960447009012521,       // re
          -0.0888535525825246          // im
        }, { 1.9959072294174116,       // re
          -0.090381360877864983        // im
        }, { 1.9957674144676598,       // re
          -0.091908956497132724        // im
        }, { 1.9956252563809942,       // re
          -0.093436335845747787        // im
        }, { 1.9954807554919269,       // re
          -0.094963495329638992        // im
        }, { 1.9953339121404823,       // re
          -0.096490431355252593        // im
        }, { 1.9951847266721969,       // re
          -0.0980171403295606          // im
        }, { 1.9950331994381187,       // re
          -0.099543618660069319        // im
        }, { 1.9948793307948056,       // re
          -0.10106986275482782         // im
        }, { 1.9947231211043257,       // re
          -0.10259586902243628         // im
        }, { 1.9945645707342554,       // re
          -0.10412163387205459         // im
        }, { 1.9944036800576792,       // re
          -0.10564715371341062         // im
        }, { 1.994240449453188,        // re
          -0.10717242495680884         // im
        }, { 1.9940748793048795,       // re
          -0.10869744401313872         // im
        }, { 1.9939069700023562,       // re
          -0.11022220729388306         // im
        }, { 1.9937367219407247,       // re
          -0.11174671121112659         // im
        }, { 1.9935641355205953,       // re
          -0.11327095217756435         // im
        }, { 1.9933892111480807,       // re
          -0.11479492660651008         // im
        }, { 1.9932119492347944,       // re
          -0.11631863091190475         // im
        }, { 1.9930323501978515,       // re
          -0.11784206150832498         // im
        }, { 1.9928504144598651,       // re
          -0.11936521481099135         // im
        }, { 1.992666142448948,        // re
          -0.12088808723577708         // im
        }, { 1.99247953459871,         // re
          -0.1224106751992162          // im
        }, { 1.9922905913482574,       // re
          -0.12393297511851216         // im
        }, { 1.9920993131421918,       // re
          -0.12545498341154623         // im
        }, { 1.9919057004306093,       // re
          -0.12697669649688587         // im
        }, { 1.9917097536690995,       // re
          -0.12849811079379317         // im
        }, { 1.9915114733187438,       // re
          -0.13001922272223335         // im
        }, { 1.9913108598461156,       // re
          -0.13154002870288312         // im
        }, { 1.991107913723277,        // re
          -0.13306052515713906         // im
        }, { 1.99090263542778,         // re
          -0.13458070850712617         // im
        }, { 1.9906950254426645,       // re
          -0.1361005751757062          // im
        }, { 1.990485084256457,        // re
          -0.13762012158648604         // im
        }, { 1.9902728123631692,       // re
          -0.1391393441638262          // im
        }, { 1.9900582102622972,       // re
          -0.14065823933284921         // im
        }, { 1.9898412784588206,       // re
          -0.14217680351944803         // im
        }, { 1.9896220174632009,       // re
          -0.14369503315029447         // im
        }, { 1.9894004277913804,       // re
          -0.14521292465284746         // im
        }, { 1.9891765099647811,       // re
          -0.14673047445536175         // im
        }, { 1.988950264510303,        // re
          -0.14824767898689603         // im
        }, { 1.9887216919603237,       // re
          -0.14976453467732151         // im
        }, { 1.9884907928526965,       // re
          -0.15128103795733022         // im
        }, { 1.9882575677307495,       // re
          -0.15279718525844344         // im
        }, { 1.9880220171432836,       // re
          -0.1543129730130201          // im
        }, { 1.9877841416445721,       // re
          -0.15582839765426523         // im
        }, { 1.9875439417943592,       // re
          -0.15734345561623825         // im
        }, { 1.9873014181578585,       // re
          -0.15885814333386145         // im
        }, { 1.9870565713057511,       // re
          -0.16037245724292828         // im
        }, { 1.9868094018141855,       // re
          -0.16188639378011183         // im
        }, { 1.9865599102647753,       // re
          -0.16339994938297323         // im
        }, { 1.9863080972445988,       // re
          -0.16491312048996992         // im
        }, { 1.9860539633461953,       // re
          -0.1664259035404641          // im
        }, { 1.9857975091675675,       // re
          -0.16793829497473117         // im
        }, { 1.9855387353121761,       // re
          -0.16945029123396796         // im
        }, { 1.9852776423889411,       // re
          -0.17096188876030122         // im
        }, { 1.9850142310122398,       // re
          -0.17247308399679595         // im
        }, { 1.9847485018019042,       // re
          -0.17398387338746382         // im
        }, { 1.9844804553832209,       // re
          -0.17549425337727143         // im
        }, { 1.984210092386929,        // re
          -0.17700422041214875         // im
        }, { 1.9839374134492189,       // re
          -0.17851377093899751         // im
        }, { 1.9836624192117303,       // re
          -0.18002290140569951         // im
        }, { 1.9833851103215512,       // re
          -0.18153160826112497         // im
        }, { 1.9831054874312164,       // re
          -0.18303988795514095         // im
        }, { 1.9828235511987051,       // re
          -0.18454773693861962         // im
        }, { 1.9825393022874414,       // re
          -0.18605515166344663         // im
        }, { 1.9822527413662894,       // re
          -0.1875621285825296          // im
        }, { 1.9819638691095554,       // re
          -0.18906866414980619         // im
        }, { 1.9816726861969831,       // re
          -0.19057475482025274         // im
        }, { 1.9813791933137546,       // re
          -0.19208039704989244         // im
        }, { 1.9810833911504866,       // re
          -0.19358558729580361         // im
        }, { 1.9807852804032304,       // re
          -0.19509032201612825         // im
        }, { 1.9804848617734694,       // re
          -0.19659459767008022         // im
        }, { 1.9801821359681173,       // re
          -0.19809841071795356         // im
        }, { 1.9798771036995175,       // re
          -0.19960175762113097         // im
        }, { 1.9795697656854405,       // re
          -0.2011046348420919          // im
        }, { 1.979260122649082,        // re
          -0.20260703884442113         // im
        }, { 1.9789481753190623,       // re
          -0.20410896609281687         // im
        }, { 1.9786339244294231,       // re
          -0.20561041305309924         // im
        }, { 1.9783173707196275,       // re
          -0.20711137619221856         // im
        }, { 1.9779985149345571,       // re
          -0.20861185197826349         // im
        }, { 1.97767735782451,         // re
          -0.21011183688046961         // im
        }, { 1.9773539001452,          // re
          -0.21161132736922755         // im
        }, { 1.9770281426577543,       // re
          -0.21311031991609136         // im
        }, { 1.9767000861287118,       // re
          -0.21460881099378676         // im
        }, { 1.976369731330021,        // re
          -0.21610679707621952         // im
        }, { 1.9760370790390391,       // re
          -0.21760427463848364         // im
        }, { 1.9757021300385285,       // re
          -0.2191012401568698          // im
        }, { 1.975364885116657,        // re
          -0.22059769010887351         // im
        }, { 1.9750253450669941,       // re
          -0.22209362097320351         // im
        }, { 1.9746835106885108,       // re
          -0.22358902922979            // im
        }, { 1.9743393827855757,       // re
          -0.22508391135979283         // im
        }, { 1.9739929621679559,       // re
          -0.22657826384561            // im
        }, { 1.973644249650812,        // re
          -0.22807208317088573         // im
        }, { 1.9732932460546984,       // re
          -0.22956536582051887         // im
        }, { 1.9729399522055602,       // re
          -0.23105810828067111         // im
        }, { 1.9725843689347322,       // re
          -0.23255030703877524         // im
        }, { 1.9722264970789363,       // re
          -0.23404195858354343         // im
        }, { 1.9718663374802794,       // re
          -0.23553305940497549         // im
        }, { 1.9715038909862517,       // re
          -0.2370236059943672          // im
        }, { 1.9711391584497251,       // re
          -0.23851359484431842         // im
        }, { 1.9707721407289505,       // re
          -0.2400030224487415          // im
        }, { 1.9704028386875554,       // re
          -0.24149188530286933         // im
        }, { 1.9700312531945441,       // re
          -0.24298017990326387         // im
        }, { 1.9696573851242924,       // re
          -0.24446790274782415         // im
        }, { 1.9692812353565485,       // re
          -0.24595505033579459         // im
        }, { 1.968902804776429,        // re
          -0.24744161916777327         // im
        }, { 1.9685220942744173,       // re
          -0.24892760574572015         // im
        }, { 1.9681391047463626,       // re
          -0.25041300657296522         // im
        }, { 1.9677538370934755,       // re
          -0.25189781815421697         // im
        }, { 1.9673662922223285,       // re
          -0.25338203699557016         // im
        }, { 1.9669764710448521,       // re
          -0.25486565960451457         // im
        }, { 1.9665843744783331,       // re
          -0.25634868248994291         // im
        }, { 1.9661900034454125,       // re
          -0.257831102162159           // im
        }, { 1.9657933588740837,       // re
          -0.25931291513288623         // im
        }, { 1.9653944416976894,       // re
          -0.26079411791527551         // im
        }, { 1.9649932528549203,       // re
          -0.26227470702391359         // im
        }, { 1.9645897932898126,       // re
          -0.26375467897483135         // im
        }, { 1.9641840639517458,       // re
          -0.26523403028551179         // im
        }, { 1.96377606579544,         // re
          -0.26671275747489837         // im
        }, { 1.9633657997809539,       // re
          -0.26819085706340318         // im
        }, { 1.9629532668736838,       // re
          -0.26966832557291509         // im
        }, { 1.9625384680443592,       // re
          -0.271145159526808           // im
        }, { 1.9621214042690416,       // re
          -0.272621355449949           // im
        }, { 1.9617020765291224,       // re
          -0.27409690986870638         // im
        }, { 1.9612804858113206,       // re
          -0.27557181931095814         // im
        }, { 1.9608566331076798,       // re
          -0.2770460803060999          // im
        }, { 1.9604305194155658,       // re
          -0.27851968938505306         // im
        }, { 1.960002145737666,        // re
          -0.27999264308027322         // im
        }, { 1.9595715130819844,       // re
          -0.28146493792575794         // im
        }, { 1.9591386224618419,       // re
          -0.28293657045705539         // im
        }, { 1.9587034748958716,       // re
          -0.28440753721127188         // im
        }, { 1.9582660714080178,       // re
          -0.28587783472708062         // im
        }, { 1.9578264130275329,       // re
          -0.28734745954472951         // im
        }, { 1.9573845007889759,       // re
          -0.28881640820604948         // im
        }, { 1.9569403357322088,       // re
          -0.29028467725446233         // im
        }, { 1.9564939189023951,       // re
          -0.29175226323498926         // im
        }, { 1.9560452513499964,       // re
          -0.29321916269425863         // im
        }, { 1.9555943341307711,       // re
          -0.29468537218051433         // im
        }, { 1.9551411683057709,       // re
          -0.29615088824362379         // im
        }, { 1.9546857549413383,       // re
          -0.2976157074350862          // im
        }, { 1.9542280951091056,       // re
          -0.29907982630804048         // im
        }, { 1.9537681898859902,       // re
          -0.30054324141727345         // im
        }, { 1.9533060403541938,       // re
          -0.30200594931922808         // im
        }, { 1.9528416476011987,       // re
          -0.30346794657201132         // im
        }, { 1.9523750127197659,       // re
          -0.30492922973540237         // im
        }, { 1.9519061368079322,       // re
          -0.30638979537086092         // im
        }, { 1.9514350209690083,       // re
          -0.30784964004153487         // im
        }, { 1.9509616663115752,       // re
          -0.30930876031226873         // im
        }, { 1.9504860739494818,       // re
          -0.31076715274961147         // im
        }, { 1.950008245001843,        // re
          -0.31222481392182488         // im
        }, { 1.9495281805930367,       // re
          -0.31368174039889152         // im
        }, { 1.9490458818527006,       // re
          -0.31513792875252244         // im
        }, { 1.9485613499157304,       // re
          -0.31659337555616585         // im
        }, { 1.9480745859222761,       // re
          -0.31804807738501495         // im
        }, { 1.9475855910177411,       // re
          -0.31950203081601569         // im
        }, { 1.9470943663527773,       // re
          -0.32095523242787521         // im
        }, { 1.9466009130832835,       // re
          -0.32240767880106985         // im
        }, { 1.9461052323704036,       // re
          -0.32385936651785285         // im
        }, { 1.9456073253805213,       // re
          -0.32531029216226293         // im
        }, { 1.9451071932852606,       // re
          -0.32676045232013173         // im
        }, { 1.9446048372614801,       // re
          -0.3282098435790925          // im
        }, { 1.9441002584912725,       // re
          -0.32965846252858749         // im
        }, { 1.9435934581619603,       // re
          -0.33110630575987643         // im
        }, { 1.9430844374660934,       // re
          -0.33255336986604422         // im
        }, { 1.9425731976014469,       // re
          -0.33399965144200938         // im
        }, { 1.9420597397710173,       // re
          -0.3354451470845316          // im
        }, { 1.9415440651830207,       // re
          -0.33688985339222005         // im
        }, { 1.9410261750508893,       // re
          -0.33833376696554113         // im
        }, { 1.9405060705932682,       // re
          -0.33977688440682685         // im
        }, { 1.939983753034014,        // re
          -0.34121920232028236         // im
        }, { 1.93945922360219,         // re
          -0.34266071731199438         // im
        }, { 1.9389324835320645,       // re
          -0.34410142598993881         // im
        }, { 1.9384035340631081,       // re
          -0.34554132496398909         // im
        }, { 1.9378723764399899,       // re
          -0.34698041084592368         // im
        }, { 1.9373390119125751,       // re
          -0.34841868024943456         // im
        }, { 1.9368034417359214,       // re
          -0.34985612979013492         // im
        }, { 1.9362656671702783,       // re
          -0.35129275608556709         // im
        }, { 1.9357256894810804,       // re
          -0.35272855575521073         // im
        }, { 1.9351835099389476,       // re
          -0.35416352542049034         // im
        }, { 1.9346391298196808,       // re
          -0.35559766170478385         // im
        }, { 1.9340925504042588,       // re
          -0.35703096123343            // im
        }, { 1.9335437729788363,       // re
          -0.35846342063373654         // im
        }, { 1.9329927988347388,       // re
          -0.35989503653498811         // im
        }, { 1.9324396292684622,       // re
          -0.36132580556845428         // im
        }, { 1.9318842655816681,       // re
          -0.36275572436739723         // im
        }, { 1.9313267090811803,       // re
          -0.36418478956707989         // im
        }, { 1.9307669610789837,       // re
          -0.36561299780477385         // im
        }, { 1.9302050228922192,       // re
          -0.36704034571976718         // im
        }, { 1.9296408958431812,       // re
          -0.36846682995337232         // im
        }, { 1.9290745812593157,       // re
          -0.3698924471489341          // im
        }, { 1.9285060804732157,       // re
          -0.37131719395183749         // im
        }, { 1.9279353948226179,       // re
          -0.37274106700951576         // im
        }, { 1.927362525650401,        // re
          -0.37416406297145793         // im
        }, { 1.9267874743045819,       // re
          -0.37558617848921722         // im
        }, { 1.9262102421383114,       // re
          -0.37700741021641826         // im
        }, { 1.9256308305098728,       // re
          -0.37842775480876556         // im
        }, { 1.9250492407826776,       // re
          -0.37984720892405116         // im
        }, { 1.9244654743252627,       // re
          -0.38126576922216238         // im
        }, { 1.9238795325112867,       // re
          -0.38268343236508978         // im
        }, { 1.9232914167195276,       // re
          -0.38410019501693504         // im
        }, { 1.9227011283338786,       // re
          -0.38551605384391885         // im
        }, { 1.9221086687433453,       // re
          -0.38693100551438858         // im
        }, { 1.9215140393420418,       // re
          -0.38834504669882625         // im
        }, { 1.9209172415291895,       // re
          -0.38975817406985641         // im
        }, { 1.9203182767091107,       // re
          -0.39117038430225387         // im
        }, { 1.9197171462912275,       // re
          -0.39258167407295147         // im
        }, { 1.9191138516900579,       // re
          -0.3939920400610481          // im
        }, { 1.9185083943252121,       // re
          -0.39540147894781635         // im
        }, { 1.9179007756213906,       // re
          -0.39680998741671031         // im
        }, { 1.917290997008378,        // re
          -0.39821756215337356         // im
        }, { 1.9166790599210426,       // re
          -0.39962419984564679         // im
        }, { 1.9160649657993316,       // re
          -0.40102989718357562         // im
        }, { 1.9154487160882678,       // re
          -0.40243465085941843         // im
        }, { 1.9148303122379462,       // re
          -0.40383845756765407         // im
        }, { 1.9142097557035307,       // re
          -0.40524131400498986         // im
        }, { 1.9135870479452508,       // re
          -0.40664321687036903         // im
        }, { 1.9129621904283982,       // re
          -0.40804416286497869         // im
        }, { 1.9123351846233227,       // re
          -0.40944414869225759         // im
        }, { 1.91170603200543,         // re
          -0.41084317105790391         // im
        }, { 1.9110747340551764,       // re
          -0.41224122666988289         // im
        }, { 1.9104412922580671,       // re
          -0.4136383122384345          // im
        }, { 1.9098057081046522,       // re
          -0.41503442447608163         // im
        }, { 1.9091679830905224,       // re
          -0.41642956009763715         // im
        }, { 1.9085281187163061,       // re
          -0.41782371582021227         // im
        }, { 1.9078861164876662,       // re
          -0.41921688836322391         // im
        }, { 1.9072419779152958,       // re
          -0.42060907444840251         // im
        }, { 1.9065957045149153,       // re
          -0.42200027079979968         // im
        }, { 1.9059472978072685,       // re
          -0.42339047414379605         // im
        }, { 1.9052967593181189,       // re
          -0.42477968120910881         // im
        }, { 1.9046440905782462,       // re
          -0.42616788872679962         // im
        }, { 1.9039892931234434,       // re
          -0.42755509343028208         // im
        }, { 1.9033323684945118,       // re
          -0.42894129205532949         // im
        }, { 1.9026733182372588,       // re
          -0.43032648134008261         // im
        }, { 1.9020121439024931,       // re
          -0.43171065802505726         // im
        }, { 1.901348847046022,        // re
          -0.43309381885315196         // im
        }, { 1.900683429228647,        // re
          -0.43447596056965565         // im
        }, { 1.9000158920161603,       // re
          -0.43585707992225547         // im
        }, { 1.8993462369793415,       // re
          -0.43723717366104409         // im
        }, { 1.8986744656939538,       // re
          -0.43861623853852766         // im
        }, { 1.89800057974074,         // re
          -0.43999427130963326         // im
        }, { 1.8973245807054182,       // re
          -0.44137126873171667         // im
        }, { 1.89664647017868,         // re
          -0.44274722756457            // im
        }, { 1.8959662497561851,       // re
          -0.4441221445704292          // im
        }, { 1.8952839210385575,       // re
          -0.44549601651398174         // im
        }, { 1.8945994856313826,       // re
          -0.44686884016237416         // im
        }, { 1.8939129451452033,       // re
          -0.44824061228521989         // im
        }, { 1.8932243011955152,       // re
          -0.44961132965460654         // im
        }, { 1.8925335554027645,       // re
          -0.45098098904510386         // im
        }, { 1.8918407093923428,       // re
          -0.45234958723377089         // im
        }, { 1.8911457647945831,       // re
          -0.45371712100016387         // im
        }, { 1.890448723244758,        // re
          -0.45508358712634384         // im
        }, { 1.8897495863830729,       // re
          -0.45644898239688392         // im
        }, { 1.8890483558546647,       // re
          -0.45781330359887717         // im
        }, { 1.8883450333095964,       // re
          -0.45917654752194409         // im
        }, { 1.887639620402854,        // re
          -0.46053871095824            // im
        }, { 1.8869321187943422,       // re
          -0.46189979070246273         // im
        }, { 1.8862225301488806,       // re
          -0.46325978355186015         // im
        }, { 1.8855108561362,          // re
          -0.46461868630623782         // im
        }, { 1.8847970984309379,       // re
          -0.46597649576796618         // im
        }, { 1.884081258712635,        // re
          -0.46733320874198842         // im
        }, { 1.8833633386657316,       // re
          -0.46868882203582796         // im
        }, { 1.8826433399795628,       // re
          -0.47004333245959562         // im
        }, { 1.8819212643483549,       // re
          -0.47139673682599764         // im
        }, { 1.881197113471222,        // re
          -0.47274903195034279         // im
        }, { 1.8804708890521606,       // re
          -0.47410021465054997         // im
        }, { 1.8797425928000475,       // re
          -0.47545028174715587         // im
        }, { 1.8790122264286335,       // re
          -0.47679923006332209         // im
        }, { 1.8782797916565417,       // re
          -0.478147056424843           // im
        }, { 1.8775452902072614,       // re
          -0.47949375766015295         // im
        }, { 1.8768087238091455,       // re
          -0.48083933060033396         // im
        }, { 1.8760700941954065,       // re
          -0.48218377207912272         // im
        }, { 1.8753294031041108,       // re
          -0.48352707893291874         // im
        }, { 1.8745866522781762,       // re
          -0.48486924800079106         // im
        }, { 1.873841843465367,        // re
          -0.48621027612448642         // im
        }, { 1.87309497841829,         // re
          -0.487550160148436           // im
        }, { 1.8723460588943914,       // re
          -0.48888889691976317         // im
        }, { 1.871595086655951,        // re
          -0.49022648328829116         // im
        }, { 1.8708420634700791,       // re
          -0.4915629161065499          // im
        }, { 1.8700869911087115,       // re
          -0.49289819222978404         // im
        }, { 1.8693298713486068,       // re
          -0.49423230851595967         // im
        }, { 1.868570705971341,        // re
          -0.49556526182577254         // im
        }, { 1.8678094967633032,       // re
          -0.49689704902265447         // im
        }, { 1.8670462455156926,       // re
          -0.49822766697278181         // im
        }, { 1.8662809540245129,       // re
          -0.49955711254508184         // im
        }, { 1.865513624090569,        // re
          -0.50088538261124071         // im
        }, { 1.8647442575194624,       // re
          -0.50221247404571079         // im
        }, { 1.8639728561215867,       // re
          -0.50353838372571758         // im
        }, { 1.8631994217121242,       // re
          -0.50486310853126759         // im
        }, { 1.8624239561110405,       // re
          -0.50618664534515523         // im
        }, { 1.8616464611430814,       // re
          -0.50750899105297087         // im
        }, { 1.8608669386377672,       // re
          -0.508830142543107           // im
        }, { 1.8600853904293901,       // re
          -0.51015009670676681         // im
        }, { 1.8593018183570085,       // re
          -0.5114688504379703          // im
        }, { 1.8585162242644429,       // re
          -0.512786400633563           // im
        }, { 1.8577286100002721,       // re
          -0.51410274419322166         // im
        }, { 1.8569389774178289,       // re
          -0.51541787801946293         // im
        }, { 1.8561473283751946,       // re
          -0.51673179901764987         // im
        }, { 1.855353664735196,        // re
          -0.51804450409599934         // im
        }, { 1.8545579883654004,       // re
          -0.51935599016558964         // im
        }, { 1.8537603011381114,       // re
          -0.52066625414036716         // im
        }, { 1.8529606049303635,       // re
          -0.52197529293715439         // im
        }, { 1.8521589016239197,       // re
          -0.52328310347565643         // im
        }, { 1.8513551931052652,       // re
          -0.524589682678469           // im
        }, { 1.8505494812656034,       // re
          -0.52589502747108463         // im
        }, { 1.8497417680008525,       // re
          -0.52719913478190128         // im
        }, { 1.8489320552116397,       // re
          -0.52850200154222848         // im
        }, { 1.8481203448032972,       // re
          -0.52980362468629461         // im
        }, { 1.8473066386858583,       // re
          -0.531104001151255           // im
        }, { 1.846490938774052,        // re
          -0.5324031278771979          // im
        }, { 1.8456732469872992,       // re
          -0.533701001807153           // im
        }, { 1.8448535652497071,       // re
          -0.53499761988709715         // im
        }, { 1.8440318954900663,       // re
          -0.53629297906596318         // im
        }, { 1.8432082396418454,       // re
          -0.53758707629564539         // im
        }, { 1.842382599643186,        // re
          -0.53887990853100842         // im
        }, { 1.8415549774368984,       // re
          -0.54017147272989285         // im
        }, { 1.8407253749704582,       // re
          -0.54146176585312344         // im
        }, { 1.8398937941959996,       // re
          -0.54275078486451589         // im
        }, { 1.8390602370703126,       // re
          -0.54403852673088382         // im
        }, { 1.838224705554838,        // re
          -0.54532498842204646         // im
        }, { 1.837387201615662,        // re
          -0.54661016691083486         // im
        }, { 1.836547727223512,        // re
          -0.54789405917310019         // im
        }, { 1.8357062843537526,       // re
          -0.54917666218771966         // im
        }, { 1.83486287498638,         // re
          -0.55045797293660481         // im
        }, { 1.8340175011060182,       // re
          -0.55173798840470734         // im
        }, { 1.8331701647019132,       // re
          -0.55301670558002747         // im
        }, { 1.8323208677679297,       // re
          -0.55429412145362            // im
        }, { 1.8314696123025453,       // re
          -0.55557023301960218         // im
        }, { 1.8306164003088463,       // re
          -0.5568450372751601          // im
        }, { 1.829761233794523,        // re
          -0.5581185312205561          // im
        }, { 1.828904114771865,        // re
          -0.55939071185913614         // im
        }, { 1.8280450452577557,       // re
          -0.560661576197336           // im
        }, { 1.827184027273669,        // re
          -0.56193112124468936         // im
        }, { 1.8263210628456634,       // re
          -0.56319934401383409         // im
        }, { 1.8254561540043777,       // re
          -0.5644662415205195          // im
        }, { 1.8245893027850253,       // re
          -0.56573181078361312         // im
        }, { 1.8237205112273913,       // re
          -0.56699604882510868         // im
        }, { 1.8228497813758264,       // re
          -0.56825895267013149         // im
        }, { 1.8219771152792417,       // re
          -0.56952051934694714         // im
        }, { 1.8211025149911046,       // re
          -0.57078074588696726         // im
        }, { 1.8202259825694347,       // re
          -0.572039629324757           // im
        }, { 1.819347520076797,        // re
          -0.5732971666980422          // im
        }, { 1.8184671295802985,       // re
          -0.57455335504771576         // im
        }, { 1.8175848131515837,       // re
          -0.57580819141784534         // im
        }, { 1.8167005728668277,       // re
          -0.57706167285567944         // im
        }, { 1.8158144108067338,       // re
          -0.57831379641165559         // im
        }, { 1.8149263290565267,       // re
          -0.57956455913940563         // im
        }, { 1.8140363297059485,       // re
          -0.58081395809576453         // im
        }, { 1.8131444148492535,       // re
          -0.58206199034077544         // im
        }, { 1.8122505865852039,       // re
          -0.58330865293769829         // im
        }, { 1.8113548470170637,       // re
          -0.58455394295301533         // im
        }, { 1.8104571982525948,       // re
          -0.58579785745643886         // im
        }, { 1.8095576424040511,       // re
          -0.587040393520918           // im
        }, { 1.808656181588175,        // re
          -0.58828154822264522         // im
        }, { 1.8077528179261904,       // re
          -0.58952131864106394         // im
        }, { 1.8068475535437993,       // re
          -0.59075970185887416         // im
        }, { 1.8059403905711764,       // re
          -0.591996694962041           // im
        }, { 1.8050313311429638,       // re
          -0.5932322950397998          // im
        }, { 1.8041203773982657,       // re
          -0.59446649918466443         // im
        }, { 1.8032075314806448,       // re
          -0.59569930449243336         // im
        }, { 1.8022927955381158,       // re
          -0.59693070806219639         // im
        }, { 1.8013761717231402,       // re
          -0.59816070699634238         // im
        }, { 1.8004576621926227,       // re
          -0.59938929840056454         // im
        }, { 1.799537269107905,        // re
          -0.600616479383869           // im
        }, { 1.7986149946347609,       // re
          -0.60184224705858            // im
        }, { 1.7976908409433912,       // re
          -0.60306659854034816         // im
        }, { 1.7967648102084188,       // re
          -0.604289530948156           // im
        }, { 1.7958369046088836,       // re
          -0.60551104140432555         // im
        }, { 1.794907126328237,        // re
          -0.60673112703452448         // im
        }, { 1.7939754775543371,       // re
          -0.60794978496777363         // im
        }, { 1.7930419604794436,       // re
          -0.60916701233645321         // im
        }, { 1.7921065773002125,       // re
          -0.61038280627630948         // im
        }, { 1.79116933021769,         // re
          -0.61159716392646191         // im
        }, { 1.79023022143731,         // re
          -0.61281008242940971         // im
        }, { 1.7892892531688855,       // re
          -0.61402155893103849         // im
        }, { 1.7883464276266063,       // re
          -0.61523159058062682         // im
        }, { 1.7874017470290315,       // re
          -0.61644017453085365         // im
        }, { 1.7864552135990857,       // re
          -0.61764730793780387         // im
        }, { 1.7855068295640539,       // re
          -0.61885298796097632         // im
        }, { 1.7845565971555752,       // re
          -0.6200572117632891          // im
        }, { 1.7836045186096383,       // re
          -0.62125997651108755         // im
        }, { 1.7826505961665757,       // re
          -0.62246127937415            // im
        }, { 1.7816948320710595,       // re
          -0.62366111752569453         // im
        }, { 1.7807372285720944,       // re
          -0.62485948814238634         // im
        }, { 1.7797777879230146,       // re
          -0.62605638840434352         // im
        }, { 1.7788165123814759,       // re
          -0.62725181549514408         // im
        }, { 1.7778534042094531,       // re
          -0.6284457666018326          // im
        }, { 1.7768884656732324,       // re
          -0.629638238914927           // im
        }, { 1.7759216990434077,       // re
          -0.63082922962842447         // im
        }, { 1.7749531065948738,       // re
          -0.63201873593980906         // im
        }, { 1.773982690606823,        // re
          -0.63320675505005719         // im
        }, { 1.7730104533627369,       // re
          -0.63439328416364549         // im
        }, { 1.7720363971503845,       // re
          -0.63557832048855611         // im
        }, { 1.7710605242618138,       // re
          -0.6367618612362842          // im
        }, { 1.7700828369933479,       // re
          -0.637943903621844           // im
        }, { 1.7691033376455798,       // re
          -0.63912444486377573         // im
        }, { 1.7681220285233654,       // re
          -0.64030348218415167         // im
        }, { 1.7671389119358203,       // re
          -0.641481012808583           // im
        }, { 1.766153990196313,        // re
          -0.64265703396622686         // im
        }, { 1.7651672656224591,       // re
          -0.64383154288979139         // im
        }, { 1.7641787405361167,       // re
          -0.64500453681554393         // im
        }, { 1.7631884172633812,       // re
          -0.64617601298331628         // im
        }, { 1.7621962981345789,       // re
          -0.64734596863651206         // im
        }, { 1.7612023854842618,       // re
          -0.64851440102211244         // im
        }, { 1.7602066816512023,       // re
          -0.64968130739068319         // im
        }, { 1.7592091889783878,       // re
          -0.650846684996381           // im
        }, { 1.7582099098130153,       // re
          -0.6520105310969595          // im
        }, { 1.7572088465064846,       // re
          -0.65317284295377676         // im
        }, { 1.7562060014143945,       // re
          -0.65433361783180044         // im
        }, { 1.7552013768965367,       // re
          -0.65549285299961535         // im
        }, { 1.7541949753168891,       // re
          -0.65665054572942894         // im
        }, { 1.7531867990436125,       // re
          -0.65780669329707864         // im
        }, { 1.7521768504490427,       // re
          -0.65896129298203732         // im
        }, { 1.7511651319096864,       // re
          -0.66011434206742048         // im
        }, { 1.750151645806215,        // re
          -0.66126583783999227         // im
        }, { 1.7491363945234593,       // re
          -0.66241577759017178         // im
        }, { 1.7481193804504036,       // re
          -0.66356415861203977         // im
        }, { 1.7471006059801801,       // re
          -0.66471097820334479         // im
        }, { 1.7460800735100639,       // re
          -0.66585623366550972         // im
        }, { 1.7450577854414659,       // re
          -0.66699992230363747         // im
        }, { 1.7440337441799292,       // re
          -0.66814204142651845         // im
        }, { 1.7430079521351218,       // re
          -0.669282588346636           // im
        }, { 1.7419804117208311,       // re
          -0.67042156038017309         // im
        }, { 1.7409511253549592,       // re
          -0.67155895484701833         // im
        }, { 1.7399200954595162,       // re
          -0.67269476907077286         // im
        }, { 1.7388873244606151,       // re
          -0.673829000378756           // im
        }, { 1.737852814788466,        // re
          -0.674961646102012           // im
        }, { 1.7368165688773698,       // re
          -0.67609270357531592         // im
        }, { 1.7357785891657136,       // re
          -0.67722217013718033         // im
        }, { 1.7347388780959636,       // re
          -0.67835004312986147         // im
        }, { 1.7336974381146604,       // re
          -0.679476319899365           // im
        }, { 1.7326542716724127,       // re
          -0.680600997795453           // im
        }, { 1.7316093812238926,       // re
          -0.68172407417164971         // im
        }, { 1.7305627692278276,       // re
          -0.68284554638524808         // im
        }, { 1.7295144381469969,       // re
          -0.6839654117973154          // im
        }, { 1.7284643904482251,       // re
          -0.68508366777270036         // im
        }, { 1.7274126286023757,       // re
          -0.68620031168003859         // im
        }, { 1.726359155084346,        // re
          -0.687315340891759           // im
        }, { 1.7253039723730608,       // re
          -0.68842875278409044         // im
        }, { 1.7242470829514671,       // re
          -0.68954054473706683         // im
        }, { 1.7231884893065275,       // re
          -0.6906507141345346          // im
        }, { 1.7221281939292155,       // re
          -0.69175925836415775         // im
        }, { 1.721066199314508,        // re
          -0.69286617481742463         // im
        }, { 1.7200025079613817,       // re
          -0.69397146088965389         // im
        }, { 1.7189371223728045,       // re
          -0.69507511398000088         // im
        }, { 1.7178700450557316,       // re
          -0.696177131491463           // im
        }, { 1.7168012785210995,       // re
          -0.69727751083088652         // im
        }, { 1.7157308252838186,       // re
          -0.69837624940897292         // im
        }, { 1.714658687862769,        // re
          -0.69947334464028377         // im
        }, { 1.7135848687807935,       // re
          -0.70056879394324834         // im
        }, { 1.7125093705646925,       // re
          -0.70166259474016845         // im
        }, { 1.7114321957452163,       // re
          -0.7027547444572253          // im
        }, { 1.7103533468570624,       // re
          -0.70384524052448494         // im
        }, { 1.7092728264388657,       // re
          -0.70493408037590488         // im
        }, { 1.7081906370331954,       // re
          -0.70602126144933974         // im
        }, { 1.7071067811865475,       // re
          -0.70710678118654757         // im
        }, { 1.7060212614493397,       // re
          -0.7081906370331954          // im
        }, { 1.7049340803759048,       // re
          -0.70927282643886569         // im
        }, { 1.703845240524485,        // re
          -0.71035334685706242         // im
        }, { 1.7027547444572253,       // re
          -0.71143219574521643         // im
        }, { 1.7016625947401685,       // re
          -0.71250937056469243         // im
        }, { 1.7005687939432483,       // re
          -0.71358486878079352         // im
        }, { 1.6994733446402837,       // re
          -0.71465868786276909         // im
        }, { 1.6983762494089729,       // re
          -0.71573082528381859         // im
        }, { 1.6972775108308866,       // re
          -0.71680127852109954         // im
        }, { 1.6961771314914631,       // re
          -0.71787004505573171         // im
        }, { 1.6950751139800009,       // re
          -0.71893712237280449         // im
        }, { 1.6939714608896539,       // re
          -0.72000250796138165         // im
        }, { 1.6928661748174245,       // re
          -0.72106619931450811         // im
        }, { 1.6917592583641579,       // re
          -0.72212819392921535         // im
        }, { 1.6906507141345346,       // re
          -0.72318848930652746         // im
        }, { 1.6895405447370668,       // re
          -0.724247082951467           // im
        }, { 1.6884287527840904,       // re
          -0.72530397237306077         // im
        }, { 1.6873153408917592,       // re
          -0.726359155084346           // im
        }, { 1.6862003116800386,       // re
          -0.72741262860237577         // im
        }, { 1.6850836677727004,       // re
          -0.7284643904482252          // im
        }, { 1.6839654117973155,       // re
          -0.729514438146997           // im
        }, { 1.6828455463852481,       // re
          -0.73056276922782759         // im
        }, { 1.6817240741716497,       // re
          -0.73160938122389263         // im
        }, { 1.680600997795453,        // re
          -0.73265427167241282         // im
        }, { 1.679476319899365,        // re
          -0.73369743811466037         // im
        }, { 1.6783500431298615,       // re
          -0.7347388780959635          // im
        }, { 1.6772221701371803,       // re
          -0.73577858916571359         // im
        }, { 1.6760927035753159,       // re
          -0.73681656887736979         // im
        }, { 1.674961646102012,        // re
          -0.737852814788466           // im
        }, { 1.6738290003787561,       // re
          -0.73888732446061511         // im
        }, { 1.6726947690707727,       // re
          -0.7399200954595162          // im
        }, { 1.6715589548470184,       // re
          -0.74095112535495922         // im
        }, { 1.6704215603801731,       // re
          -0.74198041172083107         // im
        }, { 1.669282588346636,        // re
          -0.74300795213512172         // im
        }, { 1.6681420414265185,       // re
          -0.74403374417992929         // im
        }, { 1.6669999223036376,       // re
          -0.745057785441466           // im
        }, { 1.6658562336655098,       // re
          -0.74608007351006378         // im
        }, { 1.6647109782033449,       // re
          -0.74710060598018013         // im
        }, { 1.6635641586120398,       // re
          -0.7481193804504036          // im
        }, { 1.6624157775901718,       // re
          -0.74913639452345937         // im
        }, { 1.6612658378399923,       // re
          -0.75015164580621507         // im
        }, { 1.6601143420674205,       // re
          -0.75116513190968637         // im
        }, { 1.6589612929820374,       // re
          -0.7521768504490427          // im
        }, { 1.6578066932970787,       // re
          -0.75318679904361252         // im
        }, { 1.6566505457294289,       // re
          -0.75419497531688917         // im
        }, { 1.6554928529996153,       // re
          -0.75520137689653655         // im
        }, { 1.6543336178318004,       // re
          -0.75620600141439454         // im
        }, { 1.6531728429537766,       // re
          -0.75720884650648457         // im
        }, { 1.6520105310969595,       // re
          -0.75820990981301528         // im
        }, { 1.650846684996381,        // re
          -0.759209188978388           // im
        }, { 1.6496813073906833,       // re
          -0.76020668165120242         // im
        }, { 1.6485144010221124,       // re
          -0.76120238548426178         // im
        }, { 1.6473459686365119,       // re
          -0.7621962981345789          // im
        }, { 1.6461760129833163,       // re
          -0.76318841726338127         // im
        }, { 1.6450045368155439,       // re
          -0.76417874053611679         // im
        }, { 1.6438315428897914,       // re
          -0.765167265622459           // im
        }, { 1.642657033966227,        // re
          -0.76615399019631292         // im
        }, { 1.6414810128085831,       // re
          -0.7671389119358204          // im
        }, { 1.6403034821841516,       // re
          -0.76812202852336542         // im
        }, { 1.6391244448637758,       // re
          -0.7691033376455797          // im
        }, { 1.6379439036218439,       // re
          -0.7700828369933479          // im
        }, { 1.6367618612362842,       // re
          -0.77106052426181382         // im
        }, { 1.6355783204885561,       // re
          -0.77203639715038452         // im
        }, { 1.6343932841636455,       // re
          -0.773010453362737           // im
        }, { 1.6332067550500571,       // re
          -0.7739826906068229          // im
        }, { 1.6320187359398091,       // re
          -0.77495310659487393         // im
        }, { 1.6308292296284246,       // re
          -0.77592169904340769         // im
        }, { 1.6296382389149269,       // re
          -0.77688846567323244         // im
        }, { 1.6284457666018326,       // re
          -0.77785340420945315         // im
        }, { 1.6272518154951441,       // re
          -0.778816512381476           // im
        }, { 1.6260563884043435,       // re
          -0.77977778792301455         // im
        }, { 1.6248594881423863,       // re
          -0.78073722857209449         // im
        }, { 1.6236611175256945,       // re
          -0.78169483207105939         // im
        }, { 1.62246127937415,         // re
          -0.78265059616657573         // im
        }, { 1.6212599765110876,       // re
          -0.78360451860963831         // im
        }, { 1.6200572117632892,       // re
          -0.78455659715557524         // im
        }, { 1.6188529879609763,       // re
          -0.78550682956405393         // im
        }, { 1.617647307937804,        // re
          -0.78645521359908577         // im
        }, { 1.6164401745308536,       // re
          -0.78740174702903143         // im
        }, { 1.6152315905806267,       // re
          -0.78834642762660634         // im
        }, { 1.6140215589310385,       // re
          -0.78928925316888565         // im
        }, { 1.6128100824294096,       // re
          -0.79023022143731            // im
        }, { 1.6115971639264619,       // re
          -0.7911693302176902          // im
        }, { 1.6103828062763095,       // re
          -0.79210657730021239         // im
        }, { 1.6091670123364532,       // re
          -0.79304196047944364         // im
        }, { 1.6079497849677735,       // re
          -0.79397547755433717         // im
        }, { 1.6067311270345246,       // re
          -0.794907126328237           // im
        }, { 1.6055110414043257,       // re
          -0.79583690460888357         // im
        }, { 1.604289530948156,        // re
          -0.79676481020841883         // im
        }, { 1.6030665985403481,       // re
          -0.79769084094339116         // im
        }, { 1.60184224705858,         // re
          -0.79861499463476093         // im
        }, { 1.6006164793838691,       // re
          -0.799537269107905           // im
        }, { 1.5993892984005647,       // re
          -0.80045766219262282         // im
        }, { 1.5981607069963424,       // re
          -0.80137617172314024         // im
        }, { 1.5969307080621964,       // re
          -0.80229279553811572         // im
        }, { 1.5956993044924332,       // re
          -0.80320753148064494         // im
        }, { 1.5944664991846644,       // re
          -0.8041203773982657          // im
        }, { 1.5932322950397997,       // re
          -0.80503133114296366         // im
        }, { 1.591996694962041,        // re
          -0.80594039057117628         // im
        }, { 1.5907597018588742,       // re
          -0.80684755354379933         // im
        }, { 1.5895213186410639,       // re
          -0.80775281792619036         // im
        }, { 1.5882815482226453,       // re
          -0.808656181588175           // im
        }, { 1.5870403935209181,       // re
          -0.80955764240405126         // im
        }, { 1.5857978574564389,       // re
          -0.81045719825259477         // im
        }, { 1.5845539429530153,       // re
          -0.81135484701706373         // im
        }, { 1.5833086529376983,       // re
          -0.81225058658520388         // im
        }, { 1.5820619903407755,       // re
          -0.81314441484925359         // im
        }, { 1.5808139580957645,       // re
          -0.81403632970594841         // im
        }, { 1.5795645591394056,       // re
          -0.81492632905652662         // im
        }, { 1.5783137964116556,       // re
          -0.81581441080673378         // im
        }, { 1.5770616728556794,       // re
          -0.81670057286682785         // im
        }, { 1.5758081914178454,       // re
          -0.81758481315158371         // im
        }, { 1.5745533550477158,       // re
          -0.81846712958029866         // im
        }, { 1.5732971666980422,       // re
          -0.819347520076797           // im
        }, { 1.5720396293247569,       // re
          -0.82022598256943469         // im
        }, { 1.5707807458869674,       // re
          -0.82110251499110465         // im
        }, { 1.569520519346947,        // re
          -0.82197711527924155         // im
        }, { 1.5682589526701314,       // re
          -0.82284978137582643         // im
        }, { 1.5669960488251087,       // re
          -0.82372051122739143         // im
        }, { 1.5657318107836131,       // re
          -0.82458930278502529         // im
        }, { 1.5644662415205195,       // re
          -0.82545615400437755         // im
        }, { 1.5631993440138341,       // re
          -0.82632106284566353         // im
        }, { 1.5619311212446894,       // re
          -0.82718402727366913         // im
        }, { 1.5606615761973361,       // re
          -0.8280450452577558          // im
        }, { 1.5593907118591361,       // re
          -0.82890411477186487         // im
        }, { 1.5581185312205561,       // re
          -0.829761233794523           // im
        }, { 1.55684503727516,         // re
          -0.83061640030884631         // im
        }, { 1.5555702330196022,       // re
          -0.83146961230254524         // im
        }, { 1.5542941214536201,       // re
          -0.83232086776792968         // im
        }, { 1.5530167055800275,       // re
          -0.83317016470191319         // im
        }, { 1.5517379884047073,       // re
          -0.83401750110601813         // im
        }, { 1.5504579729366048,       // re
          -0.83486287498638            // im
        }, { 1.5491766621877197,       // re
          -0.8357062843537526          // im
        }, { 1.5478940591731,          // re
          -0.836547727223512           // im
        }, { 1.5466101669108347,       // re
          -0.83738720161566194         // im
        }, { 1.5453249884220464,       // re
          -0.83822470555483808         // im
        }, { 1.5440385267308838,       // re
          -0.83906023707031274         // im
        }, { 1.5427507848645159,       // re
          -0.83989379419599952         // im
        }, { 1.5414617658531236,       // re
          -0.84072537497045807         // im
        }, { 1.540171472729893,        // re
          -0.84155497743689844         // im
        }, { 1.5388799085310083,       // re
          -0.84238259964318585         // im
        }, { 1.5375870762956454,       // re
          -0.84320823964184544         // im
        }, { 1.5362929790659632,       // re
          -0.84403189549006641         // im
        }, { 1.5349976198870972,       // re
          -0.84485356524970712         // im
        }, { 1.5337010018071529,       // re
          -0.84567324698729907         // im
        }, { 1.5324031278771979,       // re
          -0.84649093877405213         // im
        }, { 1.5311040011512551,       // re
          -0.84730663868585832         // im
        }, { 1.5298036246862945,       // re
          -0.84812034480329723         // im
        }, { 1.5285020015422286,       // re
          -0.84893205521163961         // im
        }, { 1.5271991347819012,       // re
          -0.84974176800085255         // im
        }, { 1.5258950274710847,       // re
          -0.85054948126560348         // im
        }, { 1.5245896826784691,       // re
          -0.8513551931052652          // im
        }, { 1.5232831034756564,       // re
          -0.85215890162391983         // im
        }, { 1.5219752929371544,       // re
          -0.85296060493036363         // im
        }, { 1.5206662541403673,       // re
          -0.85376030113811141         // im
        }, { 1.5193559901655895,       // re
          -0.85455798836540053         // im
        }, { 1.5180445040959993,       // re
          -0.855353664735196           // im
        }, { 1.5167317990176499,       // re
          -0.85614732837519447         // im
        }, { 1.5154178780194629,       // re
          -0.85693897741782876         // im
        }, { 1.5141027441932216,       // re
          -0.85772861000027212         // im
        }, { 1.512786400633563,        // re
          -0.85851622426444274         // im
        }, { 1.5114688504379703,       // re
          -0.85930181835700847         // im
        }, { 1.5101500967067669,       // re
          -0.86008539042939014         // im
        }, { 1.508830142543107,        // re
          -0.86086693863776731         // im
        }, { 1.5075089910529709,       // re
          -0.8616464611430813          // im
        }, { 1.5061866453451551,       // re
          -0.8624239561110405          // im
        }, { 1.5048631085312676,       // re
          -0.86319942171212416         // im
        }, { 1.5035383837257177,       // re
          -0.8639728561215867          // im
        }, { 1.5022124740457108,       // re
          -0.86474425751946238         // im
        }, { 1.5008853826112407,       // re
          -0.86551362409056909         // im
        }, { 1.4995571125450819,       // re
          -0.866280954024513           // im
        }, { 1.4982276669727819,       // re
          -0.86704624551569265         // im
        }, { 1.4968970490226545,       // re
          -0.86780949676330332         // im
        }, { 1.4955652618257727,       // re
          -0.8685707059713409          // im
        }, { 1.4942323085159597,       // re
          -0.86932987134860684         // im
        }, { 1.4928981922297839,       // re
          -0.87008699110871146         // im
        }, { 1.4915629161065498,       // re
          -0.870842063470079           // im
        }, { 1.4902264832882912,       // re
          -0.87159508665595109         // im
        }, { 1.4888888969197631,       // re
          -0.87234605889439154         // im
        }, { 1.487550160148436,        // re
          -0.87309497841829009         // im
        }, { 1.4862102761244864,       // re
          -0.87384184346536686         // im
        }, { 1.484869248000791,        // re
          -0.87458665227817611         // im
        }, { 1.4835270789329187,       // re
          -0.87532940310411089         // im
        }, { 1.4821837720791227,       // re
          -0.8760700941954066          // im
        }, { 1.480839330600334,        // re
          -0.87680872380914565         // im
        }, { 1.479493757660153,        // re
          -0.87754529020726135         // im
        }, { 1.4781470564248429,       // re
          -0.87827979165654158         // im
        }, { 1.4767992300633221,       // re
          -0.87901222642863353         // im
        }, { 1.4754502817471558,       // re
          -0.87974259280004741         // im
        }, { 1.47410021465055,         // re
          -0.88047088905216075         // im
        }, { 1.4727490319503427,       // re
          -0.88119711347122209         // im
        }, { 1.4713967368259977,       // re
          -0.881921264348355           // im
        }, { 1.4700433324595956,       // re
          -0.88264333997956279         // im
        }, { 1.4686888220358281,       // re
          -0.88336333866573158         // im
        }, { 1.4673332087419884,       // re
          -0.884081258712635           // im
        }, { 1.4659764957679662,       // re
          -0.88479709843093779         // im
        }, { 1.4646186863062378,       // re
          -0.8855108561362             // im
        }, { 1.4632597835518601,       // re
          -0.88622253014888064         // im
        }, { 1.4618997907024627,       // re
          -0.88693211879434219         // im
        }, { 1.46053871095824,         // re
          -0.88763962040285393         // im
        }, { 1.459176547521944,        // re
          -0.88834503330959635         // im
        }, { 1.4578133035988772,       // re
          -0.88904835585466457         // im
        }, { 1.4564489823968838,       // re
          -0.88974958638307278         // im
        }, { 1.4550835871263439,       // re
          -0.89044872324475788         // im
        }, { 1.4537171210001638,       // re
          -0.89114576479458318         // im
        }, { 1.4523495872337708,       // re
          -0.89184070939234272         // im
        }, { 1.450980989045104,        // re
          -0.89253355540276458         // im
        }, { 1.4496113296546065,       // re
          -0.89322430119551532         // im
        }, { 1.4482406122852198,       // re
          -0.89391294514520325         // im
        }, { 1.4468688401623742,       // re
          -0.8945994856313827          // im
        }, { 1.4454960165139816,       // re
          -0.89528392103855758         // im
        }, { 1.4441221445704291,       // re
          -0.89596624975618522         // im
        }, { 1.44274722756457,         // re
          -0.89664647017868015         // im
        }, { 1.4413712687317166,       // re
          -0.89732458070541832         // im
        }, { 1.4399942713096332,       // re
          -0.89800057974073988         // im
        }, { 1.4386162385385277,       // re
          -0.89867446569395382         // im
        }, { 1.4372371736610441,       // re
          -0.89934623697934157         // im
        }, { 1.4358570799222554,       // re
          -0.90001589201616017         // im
        }, { 1.4344759605696558,       // re
          -0.900683429228647           // im
        }, { 1.4330938188531519,       // re
          -0.901348847046022           // im
        }, { 1.4317106580250574,       // re
          -0.90201214390249318         // im
        }, { 1.4303264813400827,       // re
          -0.90267331823725883         // im
        }, { 1.4289412920553295,       // re
          -0.90333236849451182         // im
        }, { 1.4275550934302821,       // re
          -0.90398929312344334         // im
        }, { 1.4261678887267997,       // re
          -0.90464409057824624         // im
        }, { 1.4247796812091087,       // re
          -0.90529675931811882         // im
        }, { 1.4233904741437962,       // re
          -0.90594729780726846         // im
        }, { 1.4220002707997996,       // re
          -0.90659570451491533         // im
        }, { 1.4206090744484026,       // re
          -0.90724197791529582         // im
        }, { 1.4192168883632239,       // re
          -0.90788611648766626         // im
        }, { 1.4178237158202123,       // re
          -0.90852811871630612         // im
        }, { 1.4164295600976371,       // re
          -0.90916798309052238         // im
        }, { 1.4150344244760817,       // re
          -0.90980570810465222         // im
        }, { 1.4136383122384344,       // re
          -0.91044129225806725         // im
        }, { 1.4122412266698829,       // re
          -0.91107473405517636         // im
        }, { 1.4108431710579039,       // re
          -0.91170603200542988         // im
        }, { 1.4094441486922575,       // re
          -0.91233518462332275         // im
        }, { 1.4080441628649787,       // re
          -0.91296219042839821         // im
        }, { 1.4066432168703691,       // re
          -0.91358704794525081         // im
        }, { 1.4052413140049897,       // re
          -0.91420975570353069         // im
        }, { 1.4038384575676541,       // re
          -0.9148303122379462          // im
        }, { 1.4024346508594183,       // re
          -0.91544871608826783         // im
        }, { 1.4010298971835757,       // re
          -0.91606496579933172         // im
        }, { 1.3996241998456469,       // re
          -0.9166790599210427          // im
        }, { 1.3982175621533734,       // re
          -0.91729099700837791         // im
        }, { 1.3968099874167104,       // re
          -0.9179007756213905          // im
        }, { 1.3954014789478164,       // re
          -0.91850839432521225         // im
        }, { 1.3939920400610482,       // re
          -0.91911385169005777         // im
        }, { 1.3925816740729515,       // re
          -0.91971714629122736         // im
        }, { 1.3911703843022538,       // re
          -0.92031827670911059         // im
        }, { 1.3897581740698564,       // re
          -0.92091724152918952         // im
        }, { 1.3883450466988263,       // re
          -0.9215140393420419          // im
        }, { 1.3869310055143886,       // re
          -0.92210866874334518         // im
        }, { 1.3855160538439188,       // re
          -0.92270112833387863         // im
        }, { 1.3841001950169352,       // re
          -0.92329141671952764         // im
        }, { 1.3826834323650898,       // re
          -0.92387953251128674         // im
        }, { 1.3812657692221624,       // re
          -0.9244654743252626          // im
        }, { 1.3798472089240512,       // re
          -0.92504924078267758         // im
        }, { 1.3784277548087656,       // re
          -0.92563083050987272         // im
        }, { 1.3770074102164183,       // re
          -0.92621024213831138         // im
        }, { 1.3755861784892172,       // re
          -0.92678747430458175         // im
        }, { 1.374164062971458,        // re
          -0.92736252565040111         // im
        }, { 1.3727410670095157,       // re
          -0.92793539482261789         // im
        }, { 1.3713171939518376,       // re
          -0.92850608047321559         // im
        }, { 1.369892447148934,        // re
          -0.92907458125931586         // im
        }, { 1.3684668299533724,       // re
          -0.92964089584318121         // im
        }, { 1.3670403457197673,       // re
          -0.93020502289221907         // im
        }, { 1.365612997804774,        // re
          -0.93076696107898371         // im
        }, { 1.36418478956708,         // re
          -0.93132670908118043         // im
        }, { 1.3627557243673971,       // re
          -0.93188426558166815         // im
        }, { 1.3613258055684543,       // re
          -0.93243962926846236         // im
        }, { 1.3598950365349882,       // re
          -0.932992798834739           // im
        }, { 1.3584634206337365,       // re
          -0.93354377297883617         // im
        }, { 1.35703096123343,         // re
          -0.93409255040425887         // im
        }, { 1.3555976617047838,       // re
          -0.93463912981968078         // im
        }, { 1.3541635254204905,       // re
          -0.93518350993894761         // im
        }, { 1.3527285557552107,       // re
          -0.93572568948108037         // im
        }, { 1.351292756085567,        // re
          -0.93626566717027826         // im
        }, { 1.349856129790135,        // re
          -0.93680344173592156         // im
        }, { 1.3484186802494347,       // re
          -0.937339011912575           // im
        }, { 1.3469804108459238,       // re
          -0.93787237643998989         // im
        }, { 1.3455413249639891,       // re
          -0.93840353406310806         // im
        }, { 1.3441014259899389,       // re
          -0.9389324835320646          // im
        }, { 1.3426607173119944,       // re
          -0.93945922360218992         // im
        }, { 1.3412192023202825,       // re
          -0.93998375303401394         // im
        }, { 1.339776884406827,        // re
          -0.9405060705932683          // im
        }, { 1.3383337669655411,       // re
          -0.94102617505088926         // im
        }, { 1.33688985339222,         // re
          -0.94154406518302081         // im
        }, { 1.3354451470845317,       // re
          -0.94205973977101731         // im
        }, { 1.3339996514420094,       // re
          -0.94257319760144687         // im
        }, { 1.3325533698660443,       // re
          -0.94308443746609349         // im
        }, { 1.3311063057598764,       // re
          -0.94359345816196039         // im
        }, { 1.3296584625285874,       // re
          -0.94410025849127266         // im
        }, { 1.3282098435790926,       // re
          -0.94460483726148026         // im
        }, { 1.3267604523201317,       // re
          -0.94510719328526061         // im
        }, { 1.3253102921622628,       // re
          -0.94560732538052128         // im
        }, { 1.3238593665178529,       // re
          -0.94610523237040345         // im
        }, { 1.32240767880107,         // re
          -0.94660091308328353         // im
        }, { 1.3209552324278753,       // re
          -0.94709436635277722         // im
        }, { 1.3195020308160157,       // re
          -0.94758559101774109         // im
        }, { 1.3180480773850149,       // re
          -0.94807458592227623         // im
        }, { 1.3165933755561658,       // re
          -0.94856134991573027         // im
        }, { 1.3151379287525224,       // re
          -0.94904588185270056         // im
        }, { 1.3136817403988914,       // re
          -0.94952818059303667         // im
        }, { 1.3122248139218249,       // re
          -0.950008245001843           // im
        }, { 1.3107671527496114,       // re
          -0.9504860739494817          // im
        }, { 1.3093087603122688,       // re
          -0.95096166631157508         // im
        }, { 1.3078496400415349,       // re
          -0.95143502096900834         // im
        }, { 1.306389795370861,        // re
          -0.95190613680793235         // im
        }, { 1.3049292297354023,       // re
          -0.95237501271976588         // im
        }, { 1.3034679465720114,       // re
          -0.95284164760119872         // im
        }, { 1.302005949319228,        // re
          -0.95330604035419386         // im
        }, { 1.3005432414172735,       // re
          -0.95376818988599033         // im
        }, { 1.2990798263080405,       // re
          -0.95422809510910567         // im
        }, { 1.2976157074350863,       // re
          -0.95468575494133834         // im
        }, { 1.2961508882436239,       // re
          -0.95514116830577078         // im
        }, { 1.2946853721805143,       // re
          -0.95559433413077111         // im
        }, { 1.2932191626942586,       // re
          -0.95604525134999641         // im
        }, { 1.2917522632349892,       // re
          -0.9564939189023951          // im
        }, { 1.2902846772544623,       // re
          -0.95694033573220882         // im
        }, { 1.2888164082060496,       // re
          -0.95738450078897586         // im
        }, { 1.2873474595447294,       // re
          -0.95782641302753291         // im
        }, { 1.2858778347270805,       // re
          -0.95826607140801767         // im
        }, { 1.2844075372112718,       // re
          -0.9587034748958716          // im
        }, { 1.2829365704570554,       // re
          -0.95913862246184189         // im
        }, { 1.2814649379257579,       // re
          -0.95957151308198452         // im
        }, { 1.2799926430802733,       // re
          -0.960002145737666           // im
        }, { 1.278519689385053,        // re
          -0.96043051941556579         // im
        }, { 1.2770460803061,          // re
          -0.96085663310767966         // im
        }, { 1.2755718193109582,       // re
          -0.96128048581132064         // im
        }, { 1.2740969098687063,       // re
          -0.96170207652912254         // im
        }, { 1.272621355449949,        // re
          -0.96212140426904158         // im
        }, { 1.271145159526808,        // re
          -0.96253846804435916         // im
        }, { 1.2696683255729151,       // re
          -0.96295326687368388         // im
        }, { 1.2681908570634031,       // re
          -0.963365799780954           // im
        }, { 1.2667127574748984,       // re
          -0.96377606579543984         // im
        }, { 1.2652340302855118,       // re
          -0.96418406395174583         // im
        }, { 1.2637546789748313,       // re
          -0.96458979328981276         // im
        }, { 1.2622747070239135,       // re
          -0.96499325285492032         // im
        }, { 1.2607941179152755,       // re
          -0.9653944416976894          // im
        }, { 1.2593129151328863,       // re
          -0.96579335887408368         // im
        }, { 1.2578311021621591,       // re
          -0.9661900034454125          // im
        }, { 1.2563486824899428,       // re
          -0.96658437447833312         // im
        }, { 1.2548656596045147,       // re
          -0.96697647104485207         // im
        }, { 1.2533820369955702,       // re
          -0.96736629222232851         // im
        }, { 1.2518978181542169,       // re
          -0.96775383709347551         // im
        }, { 1.2504130065729653,       // re
          -0.96813910474636244         // im
        }, { 1.2489276057457201,       // re
          -0.96852209427441727         // im
        }, { 1.2474416191677733,       // re
          -0.96890280477642887         // im
        }, { 1.2459550503357946,       // re
          -0.96928123535654853         // im
        }, { 1.2444679027478243,       // re
          -0.96965738512429245         // im
        }, { 1.2429801799032638,       // re
          -0.970031253194544           // im
        }, { 1.2414918853028694,       // re
          -0.9704028386875555          // im
        }, { 1.2400030224487415,       // re
          -0.97077214072895035         // im
        }, { 1.2385135948443184,       // re
          -0.97113915844972509         // im
        }, { 1.2370236059943671,       // re
          -0.97150389098625178         // im
        }, { 1.2355330594049754,       // re
          -0.9718663374802794          // im
        }, { 1.2340419585835434,       // re
          -0.97222649707893627         // im
        }, { 1.2325503070387753,       // re
          -0.97258436893473221         // im
        }, { 1.2310581082806711,       // re
          -0.97293995220556018         // im
        }, { 1.2295653658205188,       // re
          -0.97329324605469825         // im
        }, { 1.2280720831708858,       // re
          -0.973644249650812           // im
        }, { 1.22657826384561,         // re
          -0.97399296216795583         // im
        }, { 1.2250839113597929,       // re
          -0.97433938278557586         // im
        }, { 1.22358902922979,         // re
          -0.97468351068851067         // im
        }, { 1.2220936209732036,       // re
          -0.97502534506699412         // im
        }, { 1.2205976901088735,       // re
          -0.975364885116657           // im
        }, { 1.2191012401568697,       // re
          -0.97570213003852857         // im
        }, { 1.2176042746384836,       // re
          -0.976037079039039           // im
        }, { 1.2161067970762196,       // re
          -0.97636973133002114         // im
        }, { 1.2146088109937867,       // re
          -0.97670008612871184         // im
        }, { 1.2131103199160913,       // re
          -0.97702814265775439         // im
        }, { 1.2116113273692275,       // re
          -0.97735390014520007         // im
        }, { 1.2101118368804695,       // re
          -0.97767735782450993         // im
        }, { 1.2086118519782634,       // re
          -0.97799851493455714         // im
        }, { 1.2071113761922185,       // re
          -0.97831737071962765         // im
        }, { 1.2056104130530994,       // re
          -0.97863392442942321         // im
        }, { 1.2041089660928168,       // re
          -0.9789481753190622          // im
        }, { 1.2026070388444212,       // re
          -0.979260122649082           // im
        }, { 1.201104634842092,        // re
          -0.97956976568544052         // im
        }, { 1.1996017576211311,       // re
          -0.97987710369951764         // im
        }, { 1.1980984107179535,       // re
          -0.98018213596811743         // im
        }, { 1.1965945976700803,       // re
          -0.98048486177346938         // im
        }, { 1.1950903220161282,       // re
          -0.98078528040323043         // im
        }, { 1.1935855872958037,       // re
          -0.98108339115048671         // im
        }, { 1.1920803970498923,       // re
          -0.98137919331375456         // im
        }, { 1.1905747548202528,       // re
          -0.98167268619698311         // im
        }, { 1.1890686641498063,       // re
          -0.98196386910955524         // im
        }, { 1.1875621285825295,       // re
          -0.98225274136628937         // im
        }, { 1.1860551516634465,       // re
          -0.98253930228744124         // im
        }, { 1.1845477369386197,       // re
          -0.98282355119870524         // im
        }, { 1.1830398879551409,       // re
          -0.98310548743121629         // im
        }, { 1.1815316082611249,       // re
          -0.98338511032155118         // im
        }, { 1.1800229014056995,       // re
          -0.98366241921173025         // im
        }, { 1.1785137709389975,       // re
          -0.98393741344921892         // im
        }, { 1.1770042204121487,       // re
          -0.984210092386929           // im
        }, { 1.1754942533772714,       // re
          -0.98448045538322093         // im
        }, { 1.1739838733874639,       // re
          -0.98474850180190421         // im
        }, { 1.1724730839967958,       // re
          -0.98501423101223984         // im
        }, { 1.1709618887603013,       // re
          -0.98527764238894122         // im
        }, { 1.1694502912339679,       // re
          -0.98553873531217606         // im
        }, { 1.1679382949747312,       // re
          -0.98579750916756748         // im
        }, { 1.166425903540464,        // re
          -0.98605396334619544         // im
        }, { 1.1649131204899699,       // re
          -0.98630809724459867         // im
        }, { 1.1633999493829732,       // re
          -0.98655991026477541         // im
        }, { 1.1618863937801118,       // re
          -0.98680940181418553         // im
        }, { 1.1603724572429284,       // re
          -0.987056571305751           // im
        }, { 1.1588581433338614,       // re
          -0.98730141815785843         // im
        }, { 1.1573434556162383,       // re
          -0.98754394179435923         // im
        }, { 1.1558283976542651,       // re
          -0.98778414164457218         // im
        }, { 1.1543129730130202,       // re
          -0.98802201714328353         // im
        }, { 1.1527971852584433,       // re
          -0.98825756773074946         // im
        }, { 1.1512810379573302,       // re
          -0.98849079285269659         // im
        }, { 1.1497645346773215,       // re
          -0.98872169196032378         // im
        }, { 1.1482476789868961,       // re
          -0.988950264510303           // im
        }, { 1.1467304744553617,       // re
          -0.989176509964781           // im
        }, { 1.1452129246528475,       // re
          -0.98940042779138038         // im
        }, { 1.1436950331502944,       // re
          -0.98962201746320089         // im
        }, { 1.1421768035194479,       // re
          -0.98984127845882053         // im
        }, { 1.1406582393328493,       // re
          -0.99005821026229712         // im
        }, { 1.1391393441638262,       // re
          -0.99027281236316911         // im
        }, { 1.1376201215864861,       // re
          -0.99048508425645709         // im
        }, { 1.1361005751757063,       // re
          -0.99069502544266463         // im
        }, { 1.1345807085071262,       // re
          -0.99090263542778            // im
        }, { 1.1330605251571391,       // re
          -0.99110791372327689         // im
        }, { 1.1315400287028832,       // re
          -0.99131085984611544         // im
        }, { 1.1300192227222334,       // re
          -0.9915114733187439          // im
        }, { 1.1284981107937933,       // re
          -0.99170975366909953         // im
        }, { 1.1269766964968859,       // re
          -0.99190570043060933         // im
        }, { 1.1254549834115462,       // re
          -0.9920993131421918          // im
        }, { 1.1239329751185121,       // re
          -0.99229059134825737         // im
        }, { 1.1224106751992162,       // re
          -0.99247953459871            // im
        }, { 1.1208880872357772,       // re
          -0.992666142448948           // im
        }, { 1.1193652148109914,       // re
          -0.9928504144598651          // im
        }, { 1.1178420615083249,       // re
          -0.99303235019785141         // im
        }, { 1.1163186309119046,       // re
          -0.9932119492347945          // im
        }, { 1.11479492660651,         // re
          -0.99338921114808065         // im
        }, { 1.1132709521775643,       // re
          -0.9935641355205953          // im
        }, { 1.1117467112111266,       // re
          -0.9937367219407246          // im
        }, { 1.110222207293883,        // re
          -0.99390697000235606         // im
        }, { 1.1086974440131387,       // re
          -0.99407487930487937         // im
        }, { 1.1071724249568089,       // re
          -0.9942404494531879          // im
        }, { 1.1056471537134107,       // re
          -0.9944036800576791          // im
        }, { 1.1041216338720545,       // re
          -0.99456457073425542         // im
        }, { 1.1025958690224362,       // re
          -0.9947231211043257          // im
        }, { 1.1010698627548279,       // re
          -0.99487933079480562         // im
        }, { 1.0995436186600693,       // re
          -0.99503319943811863         // im
        }, { 1.0980171403295607,       // re
          -0.99518472667219693         // im
        }, { 1.0964904313552526,       // re
          -0.99533391214048228         // im
        }, { 1.094963495329639,        // re
          -0.99548075549192694         // im
        }, { 1.0934363358457477,       // re
          -0.99562525638099431         // im
        }, { 1.0919089564971327,       // re
          -0.99576741446765982         // im
        }, { 1.090381360877865,        // re
          -0.99590722941741172         // im
        }, { 1.0888535525825247,       // re
          -0.996044700901252           // im
        }, { 1.0873255352061921,       // re
          -0.996179828595697           // im
        }, { 1.08579731234444,         // re
          -0.996312612182778           // im
        }, { 1.084268887593324,        // re
          -0.99644305135004263         // im
        }, { 1.0827402645493758,       // re
          -0.99657114579055484         // im
        }, { 1.0812114468095924,       // re
          -0.99669689520289606         // im
        }, { 1.07968243797143,         // re
          -0.99682029929116567         // im
        }, { 1.0781532416327941,       // re
          -0.99694135776498216         // im
        }, { 1.0766238613920316,       // re
          -0.997060070339483           // im
        }, { 1.0750943008479212,       // re
          -0.99717643673532619         // im
        }, { 1.0735645635996673,       // re
          -0.99729045667869021         // im
        }, { 1.0720346532468894,       // re
          -0.9974021299012753          // im
        }, { 1.0705045733896139,       // re
          -0.99751145614030345         // im
        }, { 1.0689743276282668,       // re
          -0.99761843513851955         // im
        }, { 1.067443919563664,        // re
          -0.99772306664419164         // im
        }, { 1.0659133527970037,       // re
          -0.99782535041111164         // im
        }, { 1.0643826309298574,       // re
          -0.997925286198596           // im
        }, { 1.0628517575641614,       // re
          -0.99802287377148624         // im
        }, { 1.0613207363022086,       // re
          -0.99811811290014918         // im
        }, { 1.0597895707466398,       // re
          -0.99821100336047819         // im
        }, { 1.0582582645004357,       // re
          -0.99830154493389289         // im
        }, { 1.0567268211669076,       // re
          -0.99838973740734016         // im
        }, { 1.05519524434969,         // re
          -0.99847558057329477         // im
        }, { 1.0536635376527306,       // re
          -0.99855907422975931         // im
        }, { 1.0521317046802834,       // re
          -0.99864021818026527         // im
        }, { 1.0505997490368992,       // re
          -0.99871901223387294         // im
        }, { 1.0490676743274181,       // re
          -0.99879545620517241         // im
        }, { 1.0475354841569593,       // re
          -0.99886954991428356         // im
        }, { 1.0460031821309146,       // re
          -0.99894129318685687         // im
        }, { 1.0444707718549386,       // re
          -0.99901068585407338         // im
        }, { 1.0429382569349408,       // re
          -0.99907772775264536         // im
        }, { 1.0414056409770767,       // re
          -0.99914241872481691         // im
        }, { 1.0398729275877399,       // re
          -0.99920475861836389         // im
        }, { 1.0383401203735527,       // re
          -0.99926474728659442         // im
        }, { 1.0368072229413587,       // re
          -0.99932238458834954         // im
        }, { 1.0352742388982139,       // re
          -0.99937767038800285         // im
        }, { 1.0337411718513776,       // re
          -0.99943060455546173         // im
        }, { 1.0322080254083046,       // re
          -0.999481186966167           // im
        }, { 1.0306748031766366,       // re
          -0.99952941750109314         // im
        }, { 1.0291415087641937,       // re
          -0.99957529604674922         // im
        }, { 1.0276081457789656,       // re
          -0.99961882249517864         // im
        }, { 1.0260747178291039,       // re
          -0.99965999674395922         // im
        }, { 1.0245412285229123,       // re
          -0.99969881869620425         // im
        }, { 1.0230076814688394,       // re
          -0.99973528826056168         // im
        }, { 1.0214740802754696,       // re
          -0.99976940535121528         // im
        }, { 1.0199404285515143,       // re
          -0.99980116988788426         // im
        }, { 1.0184067299058048,       // re
          -0.9998305817958234          // im
        }, { 1.0168729879472818,       // re
          -0.99985764100582386         // im
        }, { 1.0153392062849882,       // re
          -0.99988234745421256         // im
        }, { 1.0138053885280605,       // re
          -0.9999047010828529          // im
        }, { 1.01227153828572,         // re
          -0.9999247018391445          // im
        }, { 1.0107376591672645,       // re
          -0.99994234967602391         // im
        }, { 1.0092037547820598,       // re
          -0.9999576445519639          // im
        }, { 1.0076698287395311,       // re
          -0.99997058643097414         // im
        }, { 1.0061358846491544,       // re
          -0.99998117528260111         // im
        }, { 1.0046019261204486,       // re
          -0.9999894110819284          // im
        }, { 1.0030679567629659,       // re
          -0.99999529380957619         // im
        }, { 1.0015339801862848,       // re
          -0.99999882345170188         // im
        } };

      static const double dv[2049] = { 1.0, 0.99999882345170188,
        0.99999529380957619, 0.9999894110819284, 0.99998117528260111,
        0.99997058643097414, 0.9999576445519639, 0.99994234967602391,
        0.9999247018391445, 0.9999047010828529, 0.99988234745421256,
        0.99985764100582386, 0.9998305817958234, 0.99980116988788426,
        0.99976940535121528, 0.99973528826056168, 0.99969881869620425,
        0.99965999674395922, 0.99961882249517864, 0.99957529604674922,
        0.99952941750109314, 0.999481186966167, 0.99943060455546173,
        0.99937767038800285, 0.99932238458834954, 0.99926474728659442,
        0.99920475861836389, 0.99914241872481691, 0.99907772775264536,
        0.99901068585407338, 0.99894129318685687, 0.99886954991428356,
        0.99879545620517241, 0.99871901223387294, 0.99864021818026527,
        0.99855907422975931, 0.99847558057329477, 0.99838973740734016,
        0.99830154493389289, 0.99821100336047819, 0.99811811290014918,
        0.99802287377148624, 0.997925286198596, 0.99782535041111164,
        0.99772306664419164, 0.99761843513851955, 0.99751145614030345,
        0.9974021299012753, 0.99729045667869021, 0.99717643673532619,
        0.997060070339483, 0.99694135776498216, 0.99682029929116567,
        0.99669689520289606, 0.99657114579055484, 0.99644305135004263,
        0.996312612182778, 0.996179828595697, 0.996044700901252,
        0.99590722941741172, 0.99576741446765982, 0.99562525638099431,
        0.99548075549192694, 0.99533391214048228, 0.99518472667219693,
        0.99503319943811863, 0.99487933079480562, 0.9947231211043257,
        0.99456457073425542, 0.9944036800576791, 0.9942404494531879,
        0.99407487930487937, 0.99390697000235606, 0.9937367219407246,
        0.9935641355205953, 0.99338921114808065, 0.9932119492347945,
        0.99303235019785141, 0.9928504144598651, 0.992666142448948,
        0.99247953459871, 0.99229059134825737, 0.9920993131421918,
        0.99190570043060933, 0.99170975366909953, 0.9915114733187439,
        0.99131085984611544, 0.99110791372327689, 0.99090263542778,
        0.99069502544266463, 0.99048508425645709, 0.99027281236316911,
        0.99005821026229712, 0.98984127845882053, 0.98962201746320089,
        0.98940042779138038, 0.989176509964781, 0.988950264510303,
        0.98872169196032378, 0.98849079285269659, 0.98825756773074946,
        0.98802201714328353, 0.98778414164457218, 0.98754394179435923,
        0.98730141815785843, 0.987056571305751, 0.98680940181418553,
        0.98655991026477541, 0.98630809724459867, 0.98605396334619544,
        0.98579750916756748, 0.98553873531217606, 0.98527764238894122,
        0.98501423101223984, 0.98474850180190421, 0.98448045538322093,
        0.984210092386929, 0.98393741344921892, 0.98366241921173025,
        0.98338511032155118, 0.98310548743121629, 0.98282355119870524,
        0.98253930228744124, 0.98225274136628937, 0.98196386910955524,
        0.98167268619698311, 0.98137919331375456, 0.98108339115048671,
        0.98078528040323043, 0.98048486177346938, 0.98018213596811743,
        0.97987710369951764, 0.97956976568544052, 0.979260122649082,
        0.9789481753190622, 0.97863392442942321, 0.97831737071962765,
        0.97799851493455714, 0.97767735782450993, 0.97735390014520007,
        0.97702814265775439, 0.97670008612871184, 0.97636973133002114,
        0.976037079039039, 0.97570213003852857, 0.975364885116657,
        0.97502534506699412, 0.97468351068851067, 0.97433938278557586,
        0.97399296216795583, 0.973644249650812, 0.97329324605469825,
        0.97293995220556018, 0.97258436893473221, 0.97222649707893627,
        0.9718663374802794, 0.97150389098625178, 0.97113915844972509,
        0.97077214072895035, 0.9704028386875555, 0.970031253194544,
        0.96965738512429245, 0.96928123535654853, 0.96890280477642887,
        0.96852209427441727, 0.96813910474636244, 0.96775383709347551,
        0.96736629222232851, 0.96697647104485207, 0.96658437447833312,
        0.9661900034454125, 0.96579335887408368, 0.9653944416976894,
        0.96499325285492032, 0.96458979328981276, 0.96418406395174583,
        0.96377606579543984, 0.963365799780954, 0.96295326687368388,
        0.96253846804435916, 0.96212140426904158, 0.96170207652912254,
        0.96128048581132064, 0.96085663310767966, 0.96043051941556579,
        0.960002145737666, 0.95957151308198452, 0.95913862246184189,
        0.9587034748958716, 0.95826607140801767, 0.95782641302753291,
        0.95738450078897586, 0.95694033573220882, 0.9564939189023951,
        0.95604525134999641, 0.95559433413077111, 0.95514116830577078,
        0.95468575494133834, 0.95422809510910567, 0.95376818988599033,
        0.95330604035419386, 0.95284164760119872, 0.95237501271976588,
        0.95190613680793235, 0.95143502096900834, 0.95096166631157508,
        0.9504860739494817, 0.950008245001843, 0.94952818059303667,
        0.94904588185270056, 0.94856134991573027, 0.94807458592227623,
        0.94758559101774109, 0.94709436635277722, 0.94660091308328353,
        0.94610523237040345, 0.94560732538052128, 0.94510719328526061,
        0.94460483726148026, 0.94410025849127266, 0.94359345816196039,
        0.94308443746609349, 0.94257319760144687, 0.94205973977101731,
        0.94154406518302081, 0.94102617505088926, 0.9405060705932683,
        0.93998375303401394, 0.93945922360218992, 0.9389324835320646,
        0.93840353406310806, 0.93787237643998989, 0.937339011912575,
        0.93680344173592156, 0.93626566717027826, 0.93572568948108037,
        0.93518350993894761, 0.93463912981968078, 0.93409255040425887,
        0.93354377297883617, 0.932992798834739, 0.93243962926846236,
        0.93188426558166815, 0.93132670908118043, 0.93076696107898371,
        0.93020502289221907, 0.92964089584318121, 0.92907458125931586,
        0.92850608047321559, 0.92793539482261789, 0.92736252565040111,
        0.92678747430458175, 0.92621024213831138, 0.92563083050987272,
        0.92504924078267758, 0.9244654743252626, 0.92387953251128674,
        0.92329141671952764, 0.92270112833387863, 0.92210866874334518,
        0.9215140393420419, 0.92091724152918952, 0.92031827670911059,
        0.91971714629122736, 0.91911385169005777, 0.91850839432521225,
        0.9179007756213905, 0.91729099700837791, 0.9166790599210427,
        0.91606496579933172, 0.91544871608826783, 0.9148303122379462,
        0.91420975570353069, 0.91358704794525081, 0.91296219042839821,
        0.91233518462332275, 0.91170603200542988, 0.91107473405517636,
        0.91044129225806725, 0.90980570810465222, 0.90916798309052238,
        0.90852811871630612, 0.90788611648766626, 0.90724197791529582,
        0.90659570451491533, 0.90594729780726846, 0.90529675931811882,
        0.90464409057824624, 0.90398929312344334, 0.90333236849451182,
        0.90267331823725883, 0.90201214390249318, 0.901348847046022,
        0.900683429228647, 0.90001589201616017, 0.89934623697934157,
        0.89867446569395382, 0.89800057974073988, 0.89732458070541832,
        0.89664647017868015, 0.89596624975618522, 0.89528392103855758,
        0.8945994856313827, 0.89391294514520325, 0.89322430119551532,
        0.89253355540276458, 0.89184070939234272, 0.89114576479458318,
        0.89044872324475788, 0.88974958638307278, 0.88904835585466457,
        0.88834503330959635, 0.88763962040285393, 0.88693211879434219,
        0.88622253014888064, 0.8855108561362, 0.88479709843093779,
        0.884081258712635, 0.88336333866573158, 0.88264333997956279,
        0.881921264348355, 0.88119711347122209, 0.88047088905216075,
        0.87974259280004741, 0.87901222642863353, 0.87827979165654158,
        0.87754529020726135, 0.87680872380914565, 0.8760700941954066,
        0.87532940310411089, 0.87458665227817611, 0.87384184346536686,
        0.87309497841829009, 0.87234605889439154, 0.87159508665595109,
        0.870842063470079, 0.87008699110871146, 0.86932987134860684,
        0.8685707059713409, 0.86780949676330332, 0.86704624551569265,
        0.866280954024513, 0.86551362409056909, 0.86474425751946238,
        0.8639728561215867, 0.86319942171212416, 0.8624239561110405,
        0.8616464611430813, 0.86086693863776731, 0.86008539042939014,
        0.85930181835700847, 0.85851622426444274, 0.85772861000027212,
        0.85693897741782876, 0.85614732837519447, 0.855353664735196,
        0.85455798836540053, 0.85376030113811141, 0.85296060493036363,
        0.85215890162391983, 0.8513551931052652, 0.85054948126560348,
        0.84974176800085255, 0.84893205521163961, 0.84812034480329723,
        0.84730663868585832, 0.84649093877405213, 0.84567324698729907,
        0.84485356524970712, 0.84403189549006641, 0.84320823964184544,
        0.84238259964318585, 0.84155497743689844, 0.84072537497045807,
        0.83989379419599952, 0.83906023707031274, 0.83822470555483808,
        0.83738720161566194, 0.836547727223512, 0.8357062843537526,
        0.83486287498638, 0.83401750110601813, 0.83317016470191319,
        0.83232086776792968, 0.83146961230254524, 0.83061640030884631,
        0.829761233794523, 0.82890411477186487, 0.8280450452577558,
        0.82718402727366913, 0.82632106284566353, 0.82545615400437755,
        0.82458930278502529, 0.82372051122739143, 0.82284978137582643,
        0.82197711527924155, 0.82110251499110465, 0.82022598256943469,
        0.819347520076797, 0.81846712958029866, 0.81758481315158371,
        0.81670057286682785, 0.81581441080673378, 0.81492632905652662,
        0.81403632970594841, 0.81314441484925359, 0.81225058658520388,
        0.81135484701706373, 0.81045719825259477, 0.80955764240405126,
        0.808656181588175, 0.80775281792619036, 0.80684755354379933,
        0.80594039057117628, 0.80503133114296366, 0.8041203773982657,
        0.80320753148064494, 0.80229279553811572, 0.80137617172314024,
        0.80045766219262282, 0.799537269107905, 0.79861499463476093,
        0.79769084094339116, 0.79676481020841883, 0.79583690460888357,
        0.794907126328237, 0.79397547755433717, 0.79304196047944364,
        0.79210657730021239, 0.7911693302176902, 0.79023022143731,
        0.78928925316888565, 0.78834642762660634, 0.78740174702903143,
        0.78645521359908577, 0.78550682956405393, 0.78455659715557524,
        0.78360451860963831, 0.78265059616657573, 0.78169483207105939,
        0.78073722857209449, 0.77977778792301455, 0.778816512381476,
        0.77785340420945315, 0.77688846567323244, 0.77592169904340769,
        0.77495310659487393, 0.7739826906068229, 0.773010453362737,
        0.77203639715038452, 0.77106052426181382, 0.7700828369933479,
        0.7691033376455797, 0.76812202852336542, 0.7671389119358204,
        0.76615399019631292, 0.765167265622459, 0.76417874053611679,
        0.76318841726338127, 0.7621962981345789, 0.76120238548426178,
        0.76020668165120242, 0.759209188978388, 0.75820990981301528,
        0.75720884650648457, 0.75620600141439454, 0.75520137689653655,
        0.75419497531688917, 0.75318679904361252, 0.7521768504490427,
        0.75116513190968637, 0.75015164580621507, 0.74913639452345937,
        0.7481193804504036, 0.74710060598018013, 0.74608007351006378,
        0.745057785441466, 0.74403374417992929, 0.74300795213512172,
        0.74198041172083107, 0.74095112535495922, 0.7399200954595162,
        0.73888732446061511, 0.737852814788466, 0.73681656887736979,
        0.73577858916571359, 0.7347388780959635, 0.73369743811466037,
        0.73265427167241282, 0.73160938122389263, 0.73056276922782759,
        0.729514438146997, 0.7284643904482252, 0.72741262860237577,
        0.726359155084346, 0.72530397237306077, 0.724247082951467,
        0.72318848930652746, 0.72212819392921535, 0.72106619931450811,
        0.72000250796138165, 0.71893712237280449, 0.71787004505573171,
        0.71680127852109954, 0.71573082528381859, 0.71465868786276909,
        0.71358486878079352, 0.71250937056469243, 0.71143219574521643,
        0.71035334685706242, 0.70927282643886569, 0.7081906370331954,
        0.70710678118654757, 0.70602126144933974, 0.70493408037590488,
        0.70384524052448494, 0.7027547444572253, 0.70166259474016845,
        0.70056879394324834, 0.69947334464028377, 0.69837624940897292,
        0.69727751083088652, 0.696177131491463, 0.69507511398000088,
        0.69397146088965389, 0.69286617481742463, 0.69175925836415775,
        0.6906507141345346, 0.68954054473706683, 0.68842875278409044,
        0.687315340891759, 0.68620031168003859, 0.68508366777270036,
        0.6839654117973154, 0.68284554638524808, 0.68172407417164971,
        0.680600997795453, 0.679476319899365, 0.67835004312986147,
        0.67722217013718033, 0.67609270357531592, 0.674961646102012,
        0.673829000378756, 0.67269476907077286, 0.67155895484701833,
        0.67042156038017309, 0.669282588346636, 0.66814204142651845,
        0.66699992230363747, 0.66585623366550972, 0.66471097820334479,
        0.66356415861203977, 0.66241577759017178, 0.66126583783999227,
        0.66011434206742048, 0.65896129298203732, 0.65780669329707864,
        0.65665054572942894, 0.65549285299961535, 0.65433361783180044,
        0.65317284295377676, 0.6520105310969595, 0.650846684996381,
        0.64968130739068319, 0.64851440102211244, 0.64734596863651206,
        0.64617601298331628, 0.64500453681554393, 0.64383154288979139,
        0.64265703396622686, 0.641481012808583, 0.64030348218415167,
        0.63912444486377573, 0.637943903621844, 0.6367618612362842,
        0.63557832048855611, 0.63439328416364549, 0.63320675505005719,
        0.63201873593980906, 0.63082922962842447, 0.629638238914927,
        0.6284457666018326, 0.62725181549514408, 0.62605638840434352,
        0.62485948814238634, 0.62366111752569453, 0.62246127937415,
        0.62125997651108755, 0.6200572117632891, 0.61885298796097632,
        0.61764730793780387, 0.61644017453085365, 0.61523159058062682,
        0.61402155893103849, 0.61281008242940971, 0.61159716392646191,
        0.61038280627630948, 0.60916701233645321, 0.60794978496777363,
        0.60673112703452448, 0.60551104140432555, 0.604289530948156,
        0.60306659854034816, 0.60184224705858, 0.600616479383869,
        0.59938929840056454, 0.59816070699634238, 0.59693070806219639,
        0.59569930449243336, 0.59446649918466443, 0.5932322950397998,
        0.591996694962041, 0.59075970185887416, 0.58952131864106394,
        0.58828154822264522, 0.587040393520918, 0.58579785745643886,
        0.58455394295301533, 0.58330865293769829, 0.58206199034077544,
        0.58081395809576453, 0.57956455913940563, 0.57831379641165559,
        0.57706167285567944, 0.57580819141784534, 0.57455335504771576,
        0.5732971666980422, 0.572039629324757, 0.57078074588696726,
        0.56952051934694714, 0.56825895267013149, 0.56699604882510868,
        0.56573181078361312, 0.5644662415205195, 0.56319934401383409,
        0.56193112124468936, 0.560661576197336, 0.55939071185913614,
        0.5581185312205561, 0.5568450372751601, 0.55557023301960218,
        0.55429412145362, 0.55301670558002747, 0.55173798840470734,
        0.55045797293660481, 0.54917666218771966, 0.54789405917310019,
        0.54661016691083486, 0.54532498842204646, 0.54403852673088382,
        0.54275078486451589, 0.54146176585312344, 0.54017147272989285,
        0.53887990853100842, 0.53758707629564539, 0.53629297906596318,
        0.53499761988709715, 0.533701001807153, 0.5324031278771979,
        0.531104001151255, 0.52980362468629461, 0.52850200154222848,
        0.52719913478190128, 0.52589502747108463, 0.524589682678469,
        0.52328310347565643, 0.52197529293715439, 0.52066625414036716,
        0.51935599016558964, 0.51804450409599934, 0.51673179901764987,
        0.51541787801946293, 0.51410274419322166, 0.512786400633563,
        0.5114688504379703, 0.51015009670676681, 0.508830142543107,
        0.50750899105297087, 0.50618664534515523, 0.50486310853126759,
        0.50353838372571758, 0.50221247404571079, 0.50088538261124071,
        0.49955711254508184, 0.49822766697278181, 0.49689704902265447,
        0.49556526182577254, 0.49423230851595967, 0.49289819222978404,
        0.4915629161065499, 0.49022648328829116, 0.48888889691976317,
        0.487550160148436, 0.48621027612448642, 0.48486924800079106,
        0.48352707893291874, 0.48218377207912272, 0.48083933060033396,
        0.47949375766015295, 0.478147056424843, 0.47679923006332209,
        0.47545028174715587, 0.47410021465054997, 0.47274903195034279,
        0.47139673682599764, 0.47004333245959562, 0.46868882203582796,
        0.46733320874198842, 0.46597649576796618, 0.46461868630623782,
        0.46325978355186015, 0.46189979070246273, 0.46053871095824,
        0.45917654752194409, 0.45781330359887717, 0.45644898239688392,
        0.45508358712634384, 0.45371712100016387, 0.45234958723377089,
        0.45098098904510386, 0.44961132965460654, 0.44824061228521989,
        0.44686884016237416, 0.44549601651398174, 0.4441221445704292,
        0.44274722756457, 0.44137126873171667, 0.43999427130963326,
        0.43861623853852766, 0.43723717366104409, 0.43585707992225547,
        0.43447596056965565, 0.43309381885315196, 0.43171065802505726,
        0.43032648134008261, 0.42894129205532949, 0.42755509343028208,
        0.42616788872679962, 0.42477968120910881, 0.42339047414379605,
        0.42200027079979968, 0.42060907444840251, 0.41921688836322391,
        0.41782371582021227, 0.41642956009763715, 0.41503442447608163,
        0.4136383122384345, 0.41224122666988289, 0.41084317105790391,
        0.40944414869225759, 0.40804416286497869, 0.40664321687036903,
        0.40524131400498986, 0.40383845756765407, 0.40243465085941843,
        0.40102989718357562, 0.39962419984564679, 0.39821756215337356,
        0.39680998741671031, 0.39540147894781635, 0.3939920400610481,
        0.39258167407295147, 0.39117038430225387, 0.38975817406985641,
        0.38834504669882625, 0.38693100551438858, 0.38551605384391885,
        0.38410019501693504, 0.38268343236508978, 0.38126576922216238,
        0.37984720892405116, 0.37842775480876556, 0.37700741021641826,
        0.37558617848921722, 0.37416406297145793, 0.37274106700951576,
        0.37131719395183749, 0.3698924471489341, 0.36846682995337232,
        0.36704034571976718, 0.36561299780477385, 0.36418478956707989,
        0.36275572436739723, 0.36132580556845428, 0.35989503653498811,
        0.35846342063373654, 0.35703096123343, 0.35559766170478385,
        0.35416352542049034, 0.35272855575521073, 0.35129275608556709,
        0.34985612979013492, 0.34841868024943456, 0.34698041084592368,
        0.34554132496398909, 0.34410142598993881, 0.34266071731199438,
        0.34121920232028236, 0.33977688440682685, 0.33833376696554113,
        0.33688985339222005, 0.3354451470845316, 0.33399965144200938,
        0.33255336986604422, 0.33110630575987643, 0.32965846252858749,
        0.3282098435790925, 0.32676045232013173, 0.32531029216226293,
        0.32385936651785285, 0.32240767880106985, 0.32095523242787521,
        0.31950203081601569, 0.31804807738501495, 0.31659337555616585,
        0.31513792875252244, 0.31368174039889152, 0.31222481392182488,
        0.31076715274961147, 0.30930876031226873, 0.30784964004153487,
        0.30638979537086092, 0.30492922973540237, 0.30346794657201132,
        0.30200594931922808, 0.30054324141727345, 0.29907982630804048,
        0.2976157074350862, 0.29615088824362379, 0.29468537218051433,
        0.29321916269425863, 0.29175226323498926, 0.29028467725446233,
        0.28881640820604948, 0.28734745954472951, 0.28587783472708062,
        0.28440753721127188, 0.28293657045705539, 0.28146493792575794,
        0.27999264308027322, 0.27851968938505306, 0.2770460803060999,
        0.27557181931095814, 0.27409690986870638, 0.272621355449949,
        0.271145159526808, 0.26966832557291509, 0.26819085706340318,
        0.26671275747489837, 0.26523403028551179, 0.26375467897483135,
        0.26227470702391359, 0.26079411791527551, 0.25931291513288623,
        0.257831102162159, 0.25634868248994291, 0.25486565960451457,
        0.25338203699557016, 0.25189781815421697, 0.25041300657296522,
        0.24892760574572015, 0.24744161916777327, 0.24595505033579459,
        0.24446790274782415, 0.24298017990326387, 0.24149188530286933,
        0.2400030224487415, 0.23851359484431842, 0.2370236059943672,
        0.23553305940497549, 0.23404195858354343, 0.23255030703877524,
        0.23105810828067111, 0.22956536582051887, 0.22807208317088573,
        0.22657826384561, 0.22508391135979283, 0.22358902922979,
        0.22209362097320351, 0.22059769010887351, 0.2191012401568698,
        0.21760427463848364, 0.21610679707621952, 0.21460881099378676,
        0.21311031991609136, 0.21161132736922755, 0.21011183688046961,
        0.20861185197826349, 0.20711137619221856, 0.20561041305309924,
        0.20410896609281687, 0.20260703884442113, 0.2011046348420919,
        0.19960175762113097, 0.19809841071795356, 0.19659459767008022,
        0.19509032201612825, 0.19358558729580361, 0.19208039704989244,
        0.19057475482025274, 0.18906866414980619, 0.1875621285825296,
        0.18605515166344663, 0.18454773693861962, 0.18303988795514095,
        0.18153160826112497, 0.18002290140569951, 0.17851377093899751,
        0.17700422041214875, 0.17549425337727143, 0.17398387338746382,
        0.17247308399679595, 0.17096188876030122, 0.16945029123396796,
        0.16793829497473117, 0.1664259035404641, 0.16491312048996992,
        0.16339994938297323, 0.16188639378011183, 0.16037245724292828,
        0.15885814333386145, 0.15734345561623825, 0.15582839765426523,
        0.1543129730130201, 0.15279718525844344, 0.15128103795733022,
        0.14976453467732151, 0.14824767898689603, 0.14673047445536175,
        0.14521292465284746, 0.14369503315029447, 0.14217680351944803,
        0.14065823933284921, 0.1391393441638262, 0.13762012158648604,
        0.1361005751757062, 0.13458070850712617, 0.13306052515713906,
        0.13154002870288312, 0.13001922272223335, 0.12849811079379317,
        0.12697669649688587, 0.12545498341154623, 0.12393297511851216,
        0.1224106751992162, 0.12088808723577708, 0.11936521481099135,
        0.11784206150832498, 0.11631863091190475, 0.11479492660651008,
        0.11327095217756435, 0.11174671121112659, 0.11022220729388306,
        0.10869744401313872, 0.10717242495680884, 0.10564715371341062,
        0.10412163387205459, 0.10259586902243628, 0.10106986275482782,
        0.099543618660069319, 0.0980171403295606, 0.096490431355252593,
        0.094963495329638992, 0.093436335845747787, 0.091908956497132724,
        0.090381360877864983, 0.0888535525825246, 0.087325535206192059,
        0.0857973123444399, 0.084268887593324071, 0.082740264549375692,
        0.081211446809592441, 0.079682437971430126, 0.078153241632794232,
        0.076623861392031492, 0.0750943008479213, 0.073564563599667426,
        0.072034653246889332, 0.070504573389613856, 0.068974327628266746,
        0.067443919563664051, 0.0659133527970038, 0.064382630929857465,
        0.0628517575641614, 0.061320736302208578, 0.059789570746639868,
        0.058258264500435752, 0.056726821166907748, 0.055195244349689941,
        0.05366353765273052, 0.052131704680283324, 0.050599749036899282,
        0.049067674327418015, 0.0475354841569593, 0.046003182130914623,
        0.044470771854938668, 0.04293825693494082, 0.041405640977076739,
        0.039872927587739811, 0.038340120373552694, 0.036807222941358832,
        0.035274238898213947, 0.03374117185137758, 0.032208025408304586,
        0.030674803176636626, 0.029141508764193722, 0.02760814577896574,
        0.0260747178291039, 0.024541228522912288, 0.023007681468839369,
        0.021474080275469508, 0.019940428551514441, 0.01840672990580482,
        0.01687298794728171, 0.0153392062849881, 0.013805388528060391,
        0.012271538285719925, 0.010737659167264491, 0.00920375478205982,
        0.007669828739531097, 0.0061358846491544753, 0.0046019261204485705,
        0.0030679567629659761, 0.0015339801862847655, 0.0,
        -0.0015339801862847655, -0.0030679567629659761, -0.0046019261204485705,
        -0.0061358846491544753, -0.007669828739531097, -0.00920375478205982,
        -0.010737659167264491, -0.012271538285719925, -0.013805388528060391,
        -0.0153392062849881, -0.01687298794728171, -0.01840672990580482,
        -0.019940428551514441, -0.021474080275469508, -0.023007681468839369,
        -0.024541228522912288, -0.0260747178291039, -0.02760814577896574,
        -0.029141508764193722, -0.030674803176636626, -0.032208025408304586,
        -0.03374117185137758, -0.035274238898213947, -0.036807222941358832,
        -0.038340120373552694, -0.039872927587739811, -0.041405640977076739,
        -0.04293825693494082, -0.044470771854938668, -0.046003182130914623,
        -0.0475354841569593, -0.049067674327418015, -0.050599749036899282,
        -0.052131704680283324, -0.05366353765273052, -0.055195244349689941,
        -0.056726821166907748, -0.058258264500435752, -0.059789570746639868,
        -0.061320736302208578, -0.0628517575641614, -0.064382630929857465,
        -0.0659133527970038, -0.067443919563664051, -0.068974327628266746,
        -0.070504573389613856, -0.072034653246889332, -0.073564563599667426,
        -0.0750943008479213, -0.076623861392031492, -0.078153241632794232,
        -0.079682437971430126, -0.081211446809592441, -0.082740264549375692,
        -0.084268887593324071, -0.0857973123444399, -0.087325535206192059,
        -0.0888535525825246, -0.090381360877864983, -0.091908956497132724,
        -0.093436335845747787, -0.094963495329638992, -0.096490431355252593,
        -0.0980171403295606, -0.099543618660069319, -0.10106986275482782,
        -0.10259586902243628, -0.10412163387205459, -0.10564715371341062,
        -0.10717242495680884, -0.10869744401313872, -0.11022220729388306,
        -0.11174671121112659, -0.11327095217756435, -0.11479492660651008,
        -0.11631863091190475, -0.11784206150832498, -0.11936521481099135,
        -0.12088808723577708, -0.1224106751992162, -0.12393297511851216,
        -0.12545498341154623, -0.12697669649688587, -0.12849811079379317,
        -0.13001922272223335, -0.13154002870288312, -0.13306052515713906,
        -0.13458070850712617, -0.1361005751757062, -0.13762012158648604,
        -0.1391393441638262, -0.14065823933284921, -0.14217680351944803,
        -0.14369503315029447, -0.14521292465284746, -0.14673047445536175,
        -0.14824767898689603, -0.14976453467732151, -0.15128103795733022,
        -0.15279718525844344, -0.1543129730130201, -0.15582839765426523,
        -0.15734345561623825, -0.15885814333386145, -0.16037245724292828,
        -0.16188639378011183, -0.16339994938297323, -0.16491312048996992,
        -0.1664259035404641, -0.16793829497473117, -0.16945029123396796,
        -0.17096188876030122, -0.17247308399679595, -0.17398387338746382,
        -0.17549425337727143, -0.17700422041214875, -0.17851377093899751,
        -0.18002290140569951, -0.18153160826112497, -0.18303988795514095,
        -0.18454773693861962, -0.18605515166344663, -0.1875621285825296,
        -0.18906866414980619, -0.19057475482025274, -0.19208039704989244,
        -0.19358558729580361, -0.19509032201612825, -0.19659459767008022,
        -0.19809841071795356, -0.19960175762113097, -0.2011046348420919,
        -0.20260703884442113, -0.20410896609281687, -0.20561041305309924,
        -0.20711137619221856, -0.20861185197826349, -0.21011183688046961,
        -0.21161132736922755, -0.21311031991609136, -0.21460881099378676,
        -0.21610679707621952, -0.21760427463848364, -0.2191012401568698,
        -0.22059769010887351, -0.22209362097320351, -0.22358902922979,
        -0.22508391135979283, -0.22657826384561, -0.22807208317088573,
        -0.22956536582051887, -0.23105810828067111, -0.23255030703877524,
        -0.23404195858354343, -0.23553305940497549, -0.2370236059943672,
        -0.23851359484431842, -0.2400030224487415, -0.24149188530286933,
        -0.24298017990326387, -0.24446790274782415, -0.24595505033579459,
        -0.24744161916777327, -0.24892760574572015, -0.25041300657296522,
        -0.25189781815421697, -0.25338203699557016, -0.25486565960451457,
        -0.25634868248994291, -0.257831102162159, -0.25931291513288623,
        -0.26079411791527551, -0.26227470702391359, -0.26375467897483135,
        -0.26523403028551179, -0.26671275747489837, -0.26819085706340318,
        -0.26966832557291509, -0.271145159526808, -0.272621355449949,
        -0.27409690986870638, -0.27557181931095814, -0.2770460803060999,
        -0.27851968938505306, -0.27999264308027322, -0.28146493792575794,
        -0.28293657045705539, -0.28440753721127188, -0.28587783472708062,
        -0.28734745954472951, -0.28881640820604948, -0.29028467725446233,
        -0.29175226323498926, -0.29321916269425863, -0.29468537218051433,
        -0.29615088824362379, -0.2976157074350862, -0.29907982630804048,
        -0.30054324141727345, -0.30200594931922808, -0.30346794657201132,
        -0.30492922973540237, -0.30638979537086092, -0.30784964004153487,
        -0.30930876031226873, -0.31076715274961147, -0.31222481392182488,
        -0.31368174039889152, -0.31513792875252244, -0.31659337555616585,
        -0.31804807738501495, -0.31950203081601569, -0.32095523242787521,
        -0.32240767880106985, -0.32385936651785285, -0.32531029216226293,
        -0.32676045232013173, -0.3282098435790925, -0.32965846252858749,
        -0.33110630575987643, -0.33255336986604422, -0.33399965144200938,
        -0.3354451470845316, -0.33688985339222005, -0.33833376696554113,
        -0.33977688440682685, -0.34121920232028236, -0.34266071731199438,
        -0.34410142598993881, -0.34554132496398909, -0.34698041084592368,
        -0.34841868024943456, -0.34985612979013492, -0.35129275608556709,
        -0.35272855575521073, -0.35416352542049034, -0.35559766170478385,
        -0.35703096123343, -0.35846342063373654, -0.35989503653498811,
        -0.36132580556845428, -0.36275572436739723, -0.36418478956707989,
        -0.36561299780477385, -0.36704034571976718, -0.36846682995337232,
        -0.3698924471489341, -0.37131719395183749, -0.37274106700951576,
        -0.37416406297145793, -0.37558617848921722, -0.37700741021641826,
        -0.37842775480876556, -0.37984720892405116, -0.38126576922216238,
        -0.38268343236508978, -0.38410019501693504, -0.38551605384391885,
        -0.38693100551438858, -0.38834504669882625, -0.38975817406985641,
        -0.39117038430225387, -0.39258167407295147, -0.3939920400610481,
        -0.39540147894781635, -0.39680998741671031, -0.39821756215337356,
        -0.39962419984564679, -0.40102989718357562, -0.40243465085941843,
        -0.40383845756765407, -0.40524131400498986, -0.40664321687036903,
        -0.40804416286497869, -0.40944414869225759, -0.41084317105790391,
        -0.41224122666988289, -0.4136383122384345, -0.41503442447608163,
        -0.41642956009763715, -0.41782371582021227, -0.41921688836322391,
        -0.42060907444840251, -0.42200027079979968, -0.42339047414379605,
        -0.42477968120910881, -0.42616788872679962, -0.42755509343028208,
        -0.42894129205532949, -0.43032648134008261, -0.43171065802505726,
        -0.43309381885315196, -0.43447596056965565, -0.43585707992225547,
        -0.43723717366104409, -0.43861623853852766, -0.43999427130963326,
        -0.44137126873171667, -0.44274722756457, -0.4441221445704292,
        -0.44549601651398174, -0.44686884016237416, -0.44824061228521989,
        -0.44961132965460654, -0.45098098904510386, -0.45234958723377089,
        -0.45371712100016387, -0.45508358712634384, -0.45644898239688392,
        -0.45781330359887717, -0.45917654752194409, -0.46053871095824,
        -0.46189979070246273, -0.46325978355186015, -0.46461868630623782,
        -0.46597649576796618, -0.46733320874198842, -0.46868882203582796,
        -0.47004333245959562, -0.47139673682599764, -0.47274903195034279,
        -0.47410021465054997, -0.47545028174715587, -0.47679923006332209,
        -0.478147056424843, -0.47949375766015295, -0.48083933060033396,
        -0.48218377207912272, -0.48352707893291874, -0.48486924800079106,
        -0.48621027612448642, -0.487550160148436, -0.48888889691976317,
        -0.49022648328829116, -0.4915629161065499, -0.49289819222978404,
        -0.49423230851595967, -0.49556526182577254, -0.49689704902265447,
        -0.49822766697278181, -0.49955711254508184, -0.50088538261124071,
        -0.50221247404571079, -0.50353838372571758, -0.50486310853126759,
        -0.50618664534515523, -0.50750899105297087, -0.508830142543107,
        -0.51015009670676681, -0.5114688504379703, -0.512786400633563,
        -0.51410274419322166, -0.51541787801946293, -0.51673179901764987,
        -0.51804450409599934, -0.51935599016558964, -0.52066625414036716,
        -0.52197529293715439, -0.52328310347565643, -0.524589682678469,
        -0.52589502747108463, -0.52719913478190128, -0.52850200154222848,
        -0.52980362468629461, -0.531104001151255, -0.5324031278771979,
        -0.533701001807153, -0.53499761988709715, -0.53629297906596318,
        -0.53758707629564539, -0.53887990853100842, -0.54017147272989285,
        -0.54146176585312344, -0.54275078486451589, -0.54403852673088382,
        -0.54532498842204646, -0.54661016691083486, -0.54789405917310019,
        -0.54917666218771966, -0.55045797293660481, -0.55173798840470734,
        -0.55301670558002747, -0.55429412145362, -0.55557023301960218,
        -0.5568450372751601, -0.5581185312205561, -0.55939071185913614,
        -0.560661576197336, -0.56193112124468936, -0.56319934401383409,
        -0.5644662415205195, -0.56573181078361312, -0.56699604882510868,
        -0.56825895267013149, -0.56952051934694714, -0.57078074588696726,
        -0.572039629324757, -0.5732971666980422, -0.57455335504771576,
        -0.57580819141784534, -0.57706167285567944, -0.57831379641165559,
        -0.57956455913940563, -0.58081395809576453, -0.58206199034077544,
        -0.58330865293769829, -0.58455394295301533, -0.58579785745643886,
        -0.587040393520918, -0.58828154822264522, -0.58952131864106394,
        -0.59075970185887416, -0.591996694962041, -0.5932322950397998,
        -0.59446649918466443, -0.59569930449243336, -0.59693070806219639,
        -0.59816070699634238, -0.59938929840056454, -0.600616479383869,
        -0.60184224705858, -0.60306659854034816, -0.604289530948156,
        -0.60551104140432555, -0.60673112703452448, -0.60794978496777363,
        -0.60916701233645321, -0.61038280627630948, -0.61159716392646191,
        -0.61281008242940971, -0.61402155893103849, -0.61523159058062682,
        -0.61644017453085365, -0.61764730793780387, -0.61885298796097632,
        -0.6200572117632891, -0.62125997651108755, -0.62246127937415,
        -0.62366111752569453, -0.62485948814238634, -0.62605638840434352,
        -0.62725181549514408, -0.6284457666018326, -0.629638238914927,
        -0.63082922962842447, -0.63201873593980906, -0.63320675505005719,
        -0.63439328416364549, -0.63557832048855611, -0.6367618612362842,
        -0.637943903621844, -0.63912444486377573, -0.64030348218415167,
        -0.641481012808583, -0.64265703396622686, -0.64383154288979139,
        -0.64500453681554393, -0.64617601298331628, -0.64734596863651206,
        -0.64851440102211244, -0.64968130739068319, -0.650846684996381,
        -0.6520105310969595, -0.65317284295377676, -0.65433361783180044,
        -0.65549285299961535, -0.65665054572942894, -0.65780669329707864,
        -0.65896129298203732, -0.66011434206742048, -0.66126583783999227,
        -0.66241577759017178, -0.66356415861203977, -0.66471097820334479,
        -0.66585623366550972, -0.66699992230363747, -0.66814204142651845,
        -0.669282588346636, -0.67042156038017309, -0.67155895484701833,
        -0.67269476907077286, -0.673829000378756, -0.674961646102012,
        -0.67609270357531592, -0.67722217013718033, -0.67835004312986147,
        -0.679476319899365, -0.680600997795453, -0.68172407417164971,
        -0.68284554638524808, -0.6839654117973154, -0.68508366777270036,
        -0.68620031168003859, -0.687315340891759, -0.68842875278409044,
        -0.68954054473706683, -0.6906507141345346, -0.69175925836415775,
        -0.69286617481742463, -0.69397146088965389, -0.69507511398000088,
        -0.696177131491463, -0.69727751083088652, -0.69837624940897292,
        -0.69947334464028377, -0.70056879394324834, -0.70166259474016845,
        -0.7027547444572253, -0.70384524052448494, -0.70493408037590488,
        -0.70602126144933974, -0.70710678118654757, -0.7081906370331954,
        -0.70927282643886569, -0.71035334685706242, -0.71143219574521643,
        -0.71250937056469243, -0.71358486878079352, -0.71465868786276909,
        -0.71573082528381859, -0.71680127852109954, -0.71787004505573171,
        -0.71893712237280449, -0.72000250796138165, -0.72106619931450811,
        -0.72212819392921535, -0.72318848930652746, -0.724247082951467,
        -0.72530397237306077, -0.726359155084346, -0.72741262860237577,
        -0.7284643904482252, -0.729514438146997, -0.73056276922782759,
        -0.73160938122389263, -0.73265427167241282, -0.73369743811466037,
        -0.7347388780959635, -0.73577858916571359, -0.73681656887736979,
        -0.737852814788466, -0.73888732446061511, -0.7399200954595162,
        -0.74095112535495922, -0.74198041172083107, -0.74300795213512172,
        -0.74403374417992929, -0.745057785441466, -0.74608007351006378,
        -0.74710060598018013, -0.7481193804504036, -0.74913639452345937,
        -0.75015164580621507, -0.75116513190968637, -0.7521768504490427,
        -0.75318679904361252, -0.75419497531688917, -0.75520137689653655,
        -0.75620600141439454, -0.75720884650648457, -0.75820990981301528,
        -0.759209188978388, -0.76020668165120242, -0.76120238548426178,
        -0.7621962981345789, -0.76318841726338127, -0.76417874053611679,
        -0.765167265622459, -0.76615399019631292, -0.7671389119358204,
        -0.76812202852336542, -0.7691033376455797, -0.7700828369933479,
        -0.77106052426181382, -0.77203639715038452, -0.773010453362737,
        -0.7739826906068229, -0.77495310659487393, -0.77592169904340769,
        -0.77688846567323244, -0.77785340420945315, -0.778816512381476,
        -0.77977778792301455, -0.78073722857209449, -0.78169483207105939,
        -0.78265059616657573, -0.78360451860963831, -0.78455659715557524,
        -0.78550682956405393, -0.78645521359908577, -0.78740174702903143,
        -0.78834642762660634, -0.78928925316888565, -0.79023022143731,
        -0.7911693302176902, -0.79210657730021239, -0.79304196047944364,
        -0.79397547755433717, -0.794907126328237, -0.79583690460888357,
        -0.79676481020841883, -0.79769084094339116, -0.79861499463476093,
        -0.799537269107905, -0.80045766219262282, -0.80137617172314024,
        -0.80229279553811572, -0.80320753148064494, -0.8041203773982657,
        -0.80503133114296366, -0.80594039057117628, -0.80684755354379933,
        -0.80775281792619036, -0.808656181588175, -0.80955764240405126,
        -0.81045719825259477, -0.81135484701706373, -0.81225058658520388,
        -0.81314441484925359, -0.81403632970594841, -0.81492632905652662,
        -0.81581441080673378, -0.81670057286682785, -0.81758481315158371,
        -0.81846712958029866, -0.819347520076797, -0.82022598256943469,
        -0.82110251499110465, -0.82197711527924155, -0.82284978137582643,
        -0.82372051122739143, -0.82458930278502529, -0.82545615400437755,
        -0.82632106284566353, -0.82718402727366913, -0.8280450452577558,
        -0.82890411477186487, -0.829761233794523, -0.83061640030884631,
        -0.83146961230254524, -0.83232086776792968, -0.83317016470191319,
        -0.83401750110601813, -0.83486287498638, -0.8357062843537526,
        -0.836547727223512, -0.83738720161566194, -0.83822470555483808,
        -0.83906023707031274, -0.83989379419599952, -0.84072537497045807,
        -0.84155497743689844, -0.84238259964318585, -0.84320823964184544,
        -0.84403189549006641, -0.84485356524970712, -0.84567324698729907,
        -0.84649093877405213, -0.84730663868585832, -0.84812034480329723,
        -0.84893205521163961, -0.84974176800085255, -0.85054948126560348,
        -0.8513551931052652, -0.85215890162391983, -0.85296060493036363,
        -0.85376030113811141, -0.85455798836540053, -0.855353664735196,
        -0.85614732837519447, -0.85693897741782876, -0.85772861000027212,
        -0.85851622426444274, -0.85930181835700847, -0.86008539042939014,
        -0.86086693863776731, -0.8616464611430813, -0.8624239561110405,
        -0.86319942171212416, -0.8639728561215867, -0.86474425751946238,
        -0.86551362409056909, -0.866280954024513, -0.86704624551569265,
        -0.86780949676330332, -0.8685707059713409, -0.86932987134860684,
        -0.87008699110871146, -0.870842063470079, -0.87159508665595109,
        -0.87234605889439154, -0.87309497841829009, -0.87384184346536686,
        -0.87458665227817611, -0.87532940310411089, -0.8760700941954066,
        -0.87680872380914565, -0.87754529020726135, -0.87827979165654158,
        -0.87901222642863353, -0.87974259280004741, -0.88047088905216075,
        -0.88119711347122209, -0.881921264348355, -0.88264333997956279,
        -0.88336333866573158, -0.884081258712635, -0.88479709843093779,
        -0.8855108561362, -0.88622253014888064, -0.88693211879434219,
        -0.88763962040285393, -0.88834503330959635, -0.88904835585466457,
        -0.88974958638307278, -0.89044872324475788, -0.89114576479458318,
        -0.89184070939234272, -0.89253355540276458, -0.89322430119551532,
        -0.89391294514520325, -0.8945994856313827, -0.89528392103855758,
        -0.89596624975618522, -0.89664647017868015, -0.89732458070541832,
        -0.89800057974073988, -0.89867446569395382, -0.89934623697934157,
        -0.90001589201616017, -0.900683429228647, -0.901348847046022,
        -0.90201214390249318, -0.90267331823725883, -0.90333236849451182,
        -0.90398929312344334, -0.90464409057824624, -0.90529675931811882,
        -0.90594729780726846, -0.90659570451491533, -0.90724197791529582,
        -0.90788611648766626, -0.90852811871630612, -0.90916798309052238,
        -0.90980570810465222, -0.91044129225806725, -0.91107473405517636,
        -0.91170603200542988, -0.91233518462332275, -0.91296219042839821,
        -0.91358704794525081, -0.91420975570353069, -0.9148303122379462,
        -0.91544871608826783, -0.91606496579933172, -0.9166790599210427,
        -0.91729099700837791, -0.9179007756213905, -0.91850839432521225,
        -0.91911385169005777, -0.91971714629122736, -0.92031827670911059,
        -0.92091724152918952, -0.9215140393420419, -0.92210866874334518,
        -0.92270112833387863, -0.92329141671952764, -0.92387953251128674,
        -0.9244654743252626, -0.92504924078267758, -0.92563083050987272,
        -0.92621024213831138, -0.92678747430458175, -0.92736252565040111,
        -0.92793539482261789, -0.92850608047321559, -0.92907458125931586,
        -0.92964089584318121, -0.93020502289221907, -0.93076696107898371,
        -0.93132670908118043, -0.93188426558166815, -0.93243962926846236,
        -0.932992798834739, -0.93354377297883617, -0.93409255040425887,
        -0.93463912981968078, -0.93518350993894761, -0.93572568948108037,
        -0.93626566717027826, -0.93680344173592156, -0.937339011912575,
        -0.93787237643998989, -0.93840353406310806, -0.9389324835320646,
        -0.93945922360218992, -0.93998375303401394, -0.9405060705932683,
        -0.94102617505088926, -0.94154406518302081, -0.94205973977101731,
        -0.94257319760144687, -0.94308443746609349, -0.94359345816196039,
        -0.94410025849127266, -0.94460483726148026, -0.94510719328526061,
        -0.94560732538052128, -0.94610523237040345, -0.94660091308328353,
        -0.94709436635277722, -0.94758559101774109, -0.94807458592227623,
        -0.94856134991573027, -0.94904588185270056, -0.94952818059303667,
        -0.950008245001843, -0.9504860739494817, -0.95096166631157508,
        -0.95143502096900834, -0.95190613680793235, -0.95237501271976588,
        -0.95284164760119872, -0.95330604035419386, -0.95376818988599033,
        -0.95422809510910567, -0.95468575494133834, -0.95514116830577078,
        -0.95559433413077111, -0.95604525134999641, -0.9564939189023951,
        -0.95694033573220882, -0.95738450078897586, -0.95782641302753291,
        -0.95826607140801767, -0.9587034748958716, -0.95913862246184189,
        -0.95957151308198452, -0.960002145737666, -0.96043051941556579,
        -0.96085663310767966, -0.96128048581132064, -0.96170207652912254,
        -0.96212140426904158, -0.96253846804435916, -0.96295326687368388,
        -0.963365799780954, -0.96377606579543984, -0.96418406395174583,
        -0.96458979328981276, -0.96499325285492032, -0.9653944416976894,
        -0.96579335887408368, -0.9661900034454125, -0.96658437447833312,
        -0.96697647104485207, -0.96736629222232851, -0.96775383709347551,
        -0.96813910474636244, -0.96852209427441727, -0.96890280477642887,
        -0.96928123535654853, -0.96965738512429245, -0.970031253194544,
        -0.9704028386875555, -0.97077214072895035, -0.97113915844972509,
        -0.97150389098625178, -0.9718663374802794, -0.97222649707893627,
        -0.97258436893473221, -0.97293995220556018, -0.97329324605469825,
        -0.973644249650812, -0.97399296216795583, -0.97433938278557586,
        -0.97468351068851067, -0.97502534506699412, -0.975364885116657,
        -0.97570213003852857, -0.976037079039039, -0.97636973133002114,
        -0.97670008612871184, -0.97702814265775439, -0.97735390014520007,
        -0.97767735782450993, -0.97799851493455714, -0.97831737071962765,
        -0.97863392442942321, -0.9789481753190622, -0.979260122649082,
        -0.97956976568544052, -0.97987710369951764, -0.98018213596811743,
        -0.98048486177346938, -0.98078528040323043, -0.98108339115048671,
        -0.98137919331375456, -0.98167268619698311, -0.98196386910955524,
        -0.98225274136628937, -0.98253930228744124, -0.98282355119870524,
        -0.98310548743121629, -0.98338511032155118, -0.98366241921173025,
        -0.98393741344921892, -0.984210092386929, -0.98448045538322093,
        -0.98474850180190421, -0.98501423101223984, -0.98527764238894122,
        -0.98553873531217606, -0.98579750916756748, -0.98605396334619544,
        -0.98630809724459867, -0.98655991026477541, -0.98680940181418553,
        -0.987056571305751, -0.98730141815785843, -0.98754394179435923,
        -0.98778414164457218, -0.98802201714328353, -0.98825756773074946,
        -0.98849079285269659, -0.98872169196032378, -0.988950264510303,
        -0.989176509964781, -0.98940042779138038, -0.98962201746320089,
        -0.98984127845882053, -0.99005821026229712, -0.99027281236316911,
        -0.99048508425645709, -0.99069502544266463, -0.99090263542778,
        -0.99110791372327689, -0.99131085984611544, -0.9915114733187439,
        -0.99170975366909953, -0.99190570043060933, -0.9920993131421918,
        -0.99229059134825737, -0.99247953459871, -0.992666142448948,
        -0.9928504144598651, -0.99303235019785141, -0.9932119492347945,
        -0.99338921114808065, -0.9935641355205953, -0.9937367219407246,
        -0.99390697000235606, -0.99407487930487937, -0.9942404494531879,
        -0.9944036800576791, -0.99456457073425542, -0.9947231211043257,
        -0.99487933079480562, -0.99503319943811863, -0.99518472667219693,
        -0.99533391214048228, -0.99548075549192694, -0.99562525638099431,
        -0.99576741446765982, -0.99590722941741172, -0.996044700901252,
        -0.996179828595697, -0.996312612182778, -0.99644305135004263,
        -0.99657114579055484, -0.99669689520289606, -0.99682029929116567,
        -0.99694135776498216, -0.997060070339483, -0.99717643673532619,
        -0.99729045667869021, -0.9974021299012753, -0.99751145614030345,
        -0.99761843513851955, -0.99772306664419164, -0.99782535041111164,
        -0.997925286198596, -0.99802287377148624, -0.99811811290014918,
        -0.99821100336047819, -0.99830154493389289, -0.99838973740734016,
        -0.99847558057329477, -0.99855907422975931, -0.99864021818026527,
        -0.99871901223387294, -0.99879545620517241, -0.99886954991428356,
        -0.99894129318685687, -0.99901068585407338, -0.99907772775264536,
        -0.99914241872481691, -0.99920475861836389, -0.99926474728659442,
        -0.99932238458834954, -0.99937767038800285, -0.99943060455546173,
        -0.999481186966167, -0.99952941750109314, -0.99957529604674922,
        -0.99961882249517864, -0.99965999674395922, -0.99969881869620425,
        -0.99973528826056168, -0.99976940535121528, -0.99980116988788426,
        -0.9998305817958234, -0.99985764100582386, -0.99988234745421256,
        -0.9999047010828529, -0.9999247018391445, -0.99994234967602391,
        -0.9999576445519639, -0.99997058643097414, -0.99998117528260111,
        -0.9999894110819284, -0.99999529380957619, -0.99999882345170188, -1.0 };

      static const double dv1[2049] = { 0.0, -0.0015339801862847655,
        -0.0030679567629659761, -0.0046019261204485705, -0.0061358846491544753,
        -0.007669828739531097, -0.00920375478205982, -0.010737659167264491,
        -0.012271538285719925, -0.013805388528060391, -0.0153392062849881,
        -0.01687298794728171, -0.01840672990580482, -0.019940428551514441,
        -0.021474080275469508, -0.023007681468839369, -0.024541228522912288,
        -0.0260747178291039, -0.02760814577896574, -0.029141508764193722,
        -0.030674803176636626, -0.032208025408304586, -0.03374117185137758,
        -0.035274238898213947, -0.036807222941358832, -0.038340120373552694,
        -0.039872927587739811, -0.041405640977076739, -0.04293825693494082,
        -0.044470771854938668, -0.046003182130914623, -0.0475354841569593,
        -0.049067674327418015, -0.050599749036899282, -0.052131704680283324,
        -0.05366353765273052, -0.055195244349689941, -0.056726821166907748,
        -0.058258264500435752, -0.059789570746639868, -0.061320736302208578,
        -0.0628517575641614, -0.064382630929857465, -0.0659133527970038,
        -0.067443919563664051, -0.068974327628266746, -0.070504573389613856,
        -0.072034653246889332, -0.073564563599667426, -0.0750943008479213,
        -0.076623861392031492, -0.078153241632794232, -0.079682437971430126,
        -0.081211446809592441, -0.082740264549375692, -0.084268887593324071,
        -0.0857973123444399, -0.087325535206192059, -0.0888535525825246,
        -0.090381360877864983, -0.091908956497132724, -0.093436335845747787,
        -0.094963495329638992, -0.096490431355252593, -0.0980171403295606,
        -0.099543618660069319, -0.10106986275482782, -0.10259586902243628,
        -0.10412163387205459, -0.10564715371341062, -0.10717242495680884,
        -0.10869744401313872, -0.11022220729388306, -0.11174671121112659,
        -0.11327095217756435, -0.11479492660651008, -0.11631863091190475,
        -0.11784206150832498, -0.11936521481099135, -0.12088808723577708,
        -0.1224106751992162, -0.12393297511851216, -0.12545498341154623,
        -0.12697669649688587, -0.12849811079379317, -0.13001922272223335,
        -0.13154002870288312, -0.13306052515713906, -0.13458070850712617,
        -0.1361005751757062, -0.13762012158648604, -0.1391393441638262,
        -0.14065823933284921, -0.14217680351944803, -0.14369503315029447,
        -0.14521292465284746, -0.14673047445536175, -0.14824767898689603,
        -0.14976453467732151, -0.15128103795733022, -0.15279718525844344,
        -0.1543129730130201, -0.15582839765426523, -0.15734345561623825,
        -0.15885814333386145, -0.16037245724292828, -0.16188639378011183,
        -0.16339994938297323, -0.16491312048996992, -0.1664259035404641,
        -0.16793829497473117, -0.16945029123396796, -0.17096188876030122,
        -0.17247308399679595, -0.17398387338746382, -0.17549425337727143,
        -0.17700422041214875, -0.17851377093899751, -0.18002290140569951,
        -0.18153160826112497, -0.18303988795514095, -0.18454773693861962,
        -0.18605515166344663, -0.1875621285825296, -0.18906866414980619,
        -0.19057475482025274, -0.19208039704989244, -0.19358558729580361,
        -0.19509032201612825, -0.19659459767008022, -0.19809841071795356,
        -0.19960175762113097, -0.2011046348420919, -0.20260703884442113,
        -0.20410896609281687, -0.20561041305309924, -0.20711137619221856,
        -0.20861185197826349, -0.21011183688046961, -0.21161132736922755,
        -0.21311031991609136, -0.21460881099378676, -0.21610679707621952,
        -0.21760427463848364, -0.2191012401568698, -0.22059769010887351,
        -0.22209362097320351, -0.22358902922979, -0.22508391135979283,
        -0.22657826384561, -0.22807208317088573, -0.22956536582051887,
        -0.23105810828067111, -0.23255030703877524, -0.23404195858354343,
        -0.23553305940497549, -0.2370236059943672, -0.23851359484431842,
        -0.2400030224487415, -0.24149188530286933, -0.24298017990326387,
        -0.24446790274782415, -0.24595505033579459, -0.24744161916777327,
        -0.24892760574572015, -0.25041300657296522, -0.25189781815421697,
        -0.25338203699557016, -0.25486565960451457, -0.25634868248994291,
        -0.257831102162159, -0.25931291513288623, -0.26079411791527551,
        -0.26227470702391359, -0.26375467897483135, -0.26523403028551179,
        -0.26671275747489837, -0.26819085706340318, -0.26966832557291509,
        -0.271145159526808, -0.272621355449949, -0.27409690986870638,
        -0.27557181931095814, -0.2770460803060999, -0.27851968938505306,
        -0.27999264308027322, -0.28146493792575794, -0.28293657045705539,
        -0.28440753721127188, -0.28587783472708062, -0.28734745954472951,
        -0.28881640820604948, -0.29028467725446233, -0.29175226323498926,
        -0.29321916269425863, -0.29468537218051433, -0.29615088824362379,
        -0.2976157074350862, -0.29907982630804048, -0.30054324141727345,
        -0.30200594931922808, -0.30346794657201132, -0.30492922973540237,
        -0.30638979537086092, -0.30784964004153487, -0.30930876031226873,
        -0.31076715274961147, -0.31222481392182488, -0.31368174039889152,
        -0.31513792875252244, -0.31659337555616585, -0.31804807738501495,
        -0.31950203081601569, -0.32095523242787521, -0.32240767880106985,
        -0.32385936651785285, -0.32531029216226293, -0.32676045232013173,
        -0.3282098435790925, -0.32965846252858749, -0.33110630575987643,
        -0.33255336986604422, -0.33399965144200938, -0.3354451470845316,
        -0.33688985339222005, -0.33833376696554113, -0.33977688440682685,
        -0.34121920232028236, -0.34266071731199438, -0.34410142598993881,
        -0.34554132496398909, -0.34698041084592368, -0.34841868024943456,
        -0.34985612979013492, -0.35129275608556709, -0.35272855575521073,
        -0.35416352542049034, -0.35559766170478385, -0.35703096123343,
        -0.35846342063373654, -0.35989503653498811, -0.36132580556845428,
        -0.36275572436739723, -0.36418478956707989, -0.36561299780477385,
        -0.36704034571976718, -0.36846682995337232, -0.3698924471489341,
        -0.37131719395183749, -0.37274106700951576, -0.37416406297145793,
        -0.37558617848921722, -0.37700741021641826, -0.37842775480876556,
        -0.37984720892405116, -0.38126576922216238, -0.38268343236508978,
        -0.38410019501693504, -0.38551605384391885, -0.38693100551438858,
        -0.38834504669882625, -0.38975817406985641, -0.39117038430225387,
        -0.39258167407295147, -0.3939920400610481, -0.39540147894781635,
        -0.39680998741671031, -0.39821756215337356, -0.39962419984564679,
        -0.40102989718357562, -0.40243465085941843, -0.40383845756765407,
        -0.40524131400498986, -0.40664321687036903, -0.40804416286497869,
        -0.40944414869225759, -0.41084317105790391, -0.41224122666988289,
        -0.4136383122384345, -0.41503442447608163, -0.41642956009763715,
        -0.41782371582021227, -0.41921688836322391, -0.42060907444840251,
        -0.42200027079979968, -0.42339047414379605, -0.42477968120910881,
        -0.42616788872679962, -0.42755509343028208, -0.42894129205532949,
        -0.43032648134008261, -0.43171065802505726, -0.43309381885315196,
        -0.43447596056965565, -0.43585707992225547, -0.43723717366104409,
        -0.43861623853852766, -0.43999427130963326, -0.44137126873171667,
        -0.44274722756457, -0.4441221445704292, -0.44549601651398174,
        -0.44686884016237416, -0.44824061228521989, -0.44961132965460654,
        -0.45098098904510386, -0.45234958723377089, -0.45371712100016387,
        -0.45508358712634384, -0.45644898239688392, -0.45781330359887717,
        -0.45917654752194409, -0.46053871095824, -0.46189979070246273,
        -0.46325978355186015, -0.46461868630623782, -0.46597649576796618,
        -0.46733320874198842, -0.46868882203582796, -0.47004333245959562,
        -0.47139673682599764, -0.47274903195034279, -0.47410021465054997,
        -0.47545028174715587, -0.47679923006332209, -0.478147056424843,
        -0.47949375766015295, -0.48083933060033396, -0.48218377207912272,
        -0.48352707893291874, -0.48486924800079106, -0.48621027612448642,
        -0.487550160148436, -0.48888889691976317, -0.49022648328829116,
        -0.4915629161065499, -0.49289819222978404, -0.49423230851595967,
        -0.49556526182577254, -0.49689704902265447, -0.49822766697278181,
        -0.49955711254508184, -0.50088538261124071, -0.50221247404571079,
        -0.50353838372571758, -0.50486310853126759, -0.50618664534515523,
        -0.50750899105297087, -0.508830142543107, -0.51015009670676681,
        -0.5114688504379703, -0.512786400633563, -0.51410274419322166,
        -0.51541787801946293, -0.51673179901764987, -0.51804450409599934,
        -0.51935599016558964, -0.52066625414036716, -0.52197529293715439,
        -0.52328310347565643, -0.524589682678469, -0.52589502747108463,
        -0.52719913478190128, -0.52850200154222848, -0.52980362468629461,
        -0.531104001151255, -0.5324031278771979, -0.533701001807153,
        -0.53499761988709715, -0.53629297906596318, -0.53758707629564539,
        -0.53887990853100842, -0.54017147272989285, -0.54146176585312344,
        -0.54275078486451589, -0.54403852673088382, -0.54532498842204646,
        -0.54661016691083486, -0.54789405917310019, -0.54917666218771966,
        -0.55045797293660481, -0.55173798840470734, -0.55301670558002747,
        -0.55429412145362, -0.55557023301960218, -0.5568450372751601,
        -0.5581185312205561, -0.55939071185913614, -0.560661576197336,
        -0.56193112124468936, -0.56319934401383409, -0.5644662415205195,
        -0.56573181078361312, -0.56699604882510868, -0.56825895267013149,
        -0.56952051934694714, -0.57078074588696726, -0.572039629324757,
        -0.5732971666980422, -0.57455335504771576, -0.57580819141784534,
        -0.57706167285567944, -0.57831379641165559, -0.57956455913940563,
        -0.58081395809576453, -0.58206199034077544, -0.58330865293769829,
        -0.58455394295301533, -0.58579785745643886, -0.587040393520918,
        -0.58828154822264522, -0.58952131864106394, -0.59075970185887416,
        -0.591996694962041, -0.5932322950397998, -0.59446649918466443,
        -0.59569930449243336, -0.59693070806219639, -0.59816070699634238,
        -0.59938929840056454, -0.600616479383869, -0.60184224705858,
        -0.60306659854034816, -0.604289530948156, -0.60551104140432555,
        -0.60673112703452448, -0.60794978496777363, -0.60916701233645321,
        -0.61038280627630948, -0.61159716392646191, -0.61281008242940971,
        -0.61402155893103849, -0.61523159058062682, -0.61644017453085365,
        -0.61764730793780387, -0.61885298796097632, -0.6200572117632891,
        -0.62125997651108755, -0.62246127937415, -0.62366111752569453,
        -0.62485948814238634, -0.62605638840434352, -0.62725181549514408,
        -0.6284457666018326, -0.629638238914927, -0.63082922962842447,
        -0.63201873593980906, -0.63320675505005719, -0.63439328416364549,
        -0.63557832048855611, -0.6367618612362842, -0.637943903621844,
        -0.63912444486377573, -0.64030348218415167, -0.641481012808583,
        -0.64265703396622686, -0.64383154288979139, -0.64500453681554393,
        -0.64617601298331628, -0.64734596863651206, -0.64851440102211244,
        -0.64968130739068319, -0.650846684996381, -0.6520105310969595,
        -0.65317284295377676, -0.65433361783180044, -0.65549285299961535,
        -0.65665054572942894, -0.65780669329707864, -0.65896129298203732,
        -0.66011434206742048, -0.66126583783999227, -0.66241577759017178,
        -0.66356415861203977, -0.66471097820334479, -0.66585623366550972,
        -0.66699992230363747, -0.66814204142651845, -0.669282588346636,
        -0.67042156038017309, -0.67155895484701833, -0.67269476907077286,
        -0.673829000378756, -0.674961646102012, -0.67609270357531592,
        -0.67722217013718033, -0.67835004312986147, -0.679476319899365,
        -0.680600997795453, -0.68172407417164971, -0.68284554638524808,
        -0.6839654117973154, -0.68508366777270036, -0.68620031168003859,
        -0.687315340891759, -0.68842875278409044, -0.68954054473706683,
        -0.6906507141345346, -0.69175925836415775, -0.69286617481742463,
        -0.69397146088965389, -0.69507511398000088, -0.696177131491463,
        -0.69727751083088652, -0.69837624940897292, -0.69947334464028377,
        -0.70056879394324834, -0.70166259474016845, -0.7027547444572253,
        -0.70384524052448494, -0.70493408037590488, -0.70602126144933974,
        -0.70710678118654757, -0.7081906370331954, -0.70927282643886569,
        -0.71035334685706242, -0.71143219574521643, -0.71250937056469243,
        -0.71358486878079352, -0.71465868786276909, -0.71573082528381859,
        -0.71680127852109954, -0.71787004505573171, -0.71893712237280449,
        -0.72000250796138165, -0.72106619931450811, -0.72212819392921535,
        -0.72318848930652746, -0.724247082951467, -0.72530397237306077,
        -0.726359155084346, -0.72741262860237577, -0.7284643904482252,
        -0.729514438146997, -0.73056276922782759, -0.73160938122389263,
        -0.73265427167241282, -0.73369743811466037, -0.7347388780959635,
        -0.73577858916571359, -0.73681656887736979, -0.737852814788466,
        -0.73888732446061511, -0.7399200954595162, -0.74095112535495922,
        -0.74198041172083107, -0.74300795213512172, -0.74403374417992929,
        -0.745057785441466, -0.74608007351006378, -0.74710060598018013,
        -0.7481193804504036, -0.74913639452345937, -0.75015164580621507,
        -0.75116513190968637, -0.7521768504490427, -0.75318679904361252,
        -0.75419497531688917, -0.75520137689653655, -0.75620600141439454,
        -0.75720884650648457, -0.75820990981301528, -0.759209188978388,
        -0.76020668165120242, -0.76120238548426178, -0.7621962981345789,
        -0.76318841726338127, -0.76417874053611679, -0.765167265622459,
        -0.76615399019631292, -0.7671389119358204, -0.76812202852336542,
        -0.7691033376455797, -0.7700828369933479, -0.77106052426181382,
        -0.77203639715038452, -0.773010453362737, -0.7739826906068229,
        -0.77495310659487393, -0.77592169904340769, -0.77688846567323244,
        -0.77785340420945315, -0.778816512381476, -0.77977778792301455,
        -0.78073722857209449, -0.78169483207105939, -0.78265059616657573,
        -0.78360451860963831, -0.78455659715557524, -0.78550682956405393,
        -0.78645521359908577, -0.78740174702903143, -0.78834642762660634,
        -0.78928925316888565, -0.79023022143731, -0.7911693302176902,
        -0.79210657730021239, -0.79304196047944364, -0.79397547755433717,
        -0.794907126328237, -0.79583690460888357, -0.79676481020841883,
        -0.79769084094339116, -0.79861499463476093, -0.799537269107905,
        -0.80045766219262282, -0.80137617172314024, -0.80229279553811572,
        -0.80320753148064494, -0.8041203773982657, -0.80503133114296366,
        -0.80594039057117628, -0.80684755354379933, -0.80775281792619036,
        -0.808656181588175, -0.80955764240405126, -0.81045719825259477,
        -0.81135484701706373, -0.81225058658520388, -0.81314441484925359,
        -0.81403632970594841, -0.81492632905652662, -0.81581441080673378,
        -0.81670057286682785, -0.81758481315158371, -0.81846712958029866,
        -0.819347520076797, -0.82022598256943469, -0.82110251499110465,
        -0.82197711527924155, -0.82284978137582643, -0.82372051122739143,
        -0.82458930278502529, -0.82545615400437755, -0.82632106284566353,
        -0.82718402727366913, -0.8280450452577558, -0.82890411477186487,
        -0.829761233794523, -0.83061640030884631, -0.83146961230254524,
        -0.83232086776792968, -0.83317016470191319, -0.83401750110601813,
        -0.83486287498638, -0.8357062843537526, -0.836547727223512,
        -0.83738720161566194, -0.83822470555483808, -0.83906023707031274,
        -0.83989379419599952, -0.84072537497045807, -0.84155497743689844,
        -0.84238259964318585, -0.84320823964184544, -0.84403189549006641,
        -0.84485356524970712, -0.84567324698729907, -0.84649093877405213,
        -0.84730663868585832, -0.84812034480329723, -0.84893205521163961,
        -0.84974176800085255, -0.85054948126560348, -0.8513551931052652,
        -0.85215890162391983, -0.85296060493036363, -0.85376030113811141,
        -0.85455798836540053, -0.855353664735196, -0.85614732837519447,
        -0.85693897741782876, -0.85772861000027212, -0.85851622426444274,
        -0.85930181835700847, -0.86008539042939014, -0.86086693863776731,
        -0.8616464611430813, -0.8624239561110405, -0.86319942171212416,
        -0.8639728561215867, -0.86474425751946238, -0.86551362409056909,
        -0.866280954024513, -0.86704624551569265, -0.86780949676330332,
        -0.8685707059713409, -0.86932987134860684, -0.87008699110871146,
        -0.870842063470079, -0.87159508665595109, -0.87234605889439154,
        -0.87309497841829009, -0.87384184346536686, -0.87458665227817611,
        -0.87532940310411089, -0.8760700941954066, -0.87680872380914565,
        -0.87754529020726135, -0.87827979165654158, -0.87901222642863353,
        -0.87974259280004741, -0.88047088905216075, -0.88119711347122209,
        -0.881921264348355, -0.88264333997956279, -0.88336333866573158,
        -0.884081258712635, -0.88479709843093779, -0.8855108561362,
        -0.88622253014888064, -0.88693211879434219, -0.88763962040285393,
        -0.88834503330959635, -0.88904835585466457, -0.88974958638307278,
        -0.89044872324475788, -0.89114576479458318, -0.89184070939234272,
        -0.89253355540276458, -0.89322430119551532, -0.89391294514520325,
        -0.8945994856313827, -0.89528392103855758, -0.89596624975618522,
        -0.89664647017868015, -0.89732458070541832, -0.89800057974073988,
        -0.89867446569395382, -0.89934623697934157, -0.90001589201616017,
        -0.900683429228647, -0.901348847046022, -0.90201214390249318,
        -0.90267331823725883, -0.90333236849451182, -0.90398929312344334,
        -0.90464409057824624, -0.90529675931811882, -0.90594729780726846,
        -0.90659570451491533, -0.90724197791529582, -0.90788611648766626,
        -0.90852811871630612, -0.90916798309052238, -0.90980570810465222,
        -0.91044129225806725, -0.91107473405517636, -0.91170603200542988,
        -0.91233518462332275, -0.91296219042839821, -0.91358704794525081,
        -0.91420975570353069, -0.9148303122379462, -0.91544871608826783,
        -0.91606496579933172, -0.9166790599210427, -0.91729099700837791,
        -0.9179007756213905, -0.91850839432521225, -0.91911385169005777,
        -0.91971714629122736, -0.92031827670911059, -0.92091724152918952,
        -0.9215140393420419, -0.92210866874334518, -0.92270112833387863,
        -0.92329141671952764, -0.92387953251128674, -0.9244654743252626,
        -0.92504924078267758, -0.92563083050987272, -0.92621024213831138,
        -0.92678747430458175, -0.92736252565040111, -0.92793539482261789,
        -0.92850608047321559, -0.92907458125931586, -0.92964089584318121,
        -0.93020502289221907, -0.93076696107898371, -0.93132670908118043,
        -0.93188426558166815, -0.93243962926846236, -0.932992798834739,
        -0.93354377297883617, -0.93409255040425887, -0.93463912981968078,
        -0.93518350993894761, -0.93572568948108037, -0.93626566717027826,
        -0.93680344173592156, -0.937339011912575, -0.93787237643998989,
        -0.93840353406310806, -0.9389324835320646, -0.93945922360218992,
        -0.93998375303401394, -0.9405060705932683, -0.94102617505088926,
        -0.94154406518302081, -0.94205973977101731, -0.94257319760144687,
        -0.94308443746609349, -0.94359345816196039, -0.94410025849127266,
        -0.94460483726148026, -0.94510719328526061, -0.94560732538052128,
        -0.94610523237040345, -0.94660091308328353, -0.94709436635277722,
        -0.94758559101774109, -0.94807458592227623, -0.94856134991573027,
        -0.94904588185270056, -0.94952818059303667, -0.950008245001843,
        -0.9504860739494817, -0.95096166631157508, -0.95143502096900834,
        -0.95190613680793235, -0.95237501271976588, -0.95284164760119872,
        -0.95330604035419386, -0.95376818988599033, -0.95422809510910567,
        -0.95468575494133834, -0.95514116830577078, -0.95559433413077111,
        -0.95604525134999641, -0.9564939189023951, -0.95694033573220882,
        -0.95738450078897586, -0.95782641302753291, -0.95826607140801767,
        -0.9587034748958716, -0.95913862246184189, -0.95957151308198452,
        -0.960002145737666, -0.96043051941556579, -0.96085663310767966,
        -0.96128048581132064, -0.96170207652912254, -0.96212140426904158,
        -0.96253846804435916, -0.96295326687368388, -0.963365799780954,
        -0.96377606579543984, -0.96418406395174583, -0.96458979328981276,
        -0.96499325285492032, -0.9653944416976894, -0.96579335887408368,
        -0.9661900034454125, -0.96658437447833312, -0.96697647104485207,
        -0.96736629222232851, -0.96775383709347551, -0.96813910474636244,
        -0.96852209427441727, -0.96890280477642887, -0.96928123535654853,
        -0.96965738512429245, -0.970031253194544, -0.9704028386875555,
        -0.97077214072895035, -0.97113915844972509, -0.97150389098625178,
        -0.9718663374802794, -0.97222649707893627, -0.97258436893473221,
        -0.97293995220556018, -0.97329324605469825, -0.973644249650812,
        -0.97399296216795583, -0.97433938278557586, -0.97468351068851067,
        -0.97502534506699412, -0.975364885116657, -0.97570213003852857,
        -0.976037079039039, -0.97636973133002114, -0.97670008612871184,
        -0.97702814265775439, -0.97735390014520007, -0.97767735782450993,
        -0.97799851493455714, -0.97831737071962765, -0.97863392442942321,
        -0.9789481753190622, -0.979260122649082, -0.97956976568544052,
        -0.97987710369951764, -0.98018213596811743, -0.98048486177346938,
        -0.98078528040323043, -0.98108339115048671, -0.98137919331375456,
        -0.98167268619698311, -0.98196386910955524, -0.98225274136628937,
        -0.98253930228744124, -0.98282355119870524, -0.98310548743121629,
        -0.98338511032155118, -0.98366241921173025, -0.98393741344921892,
        -0.984210092386929, -0.98448045538322093, -0.98474850180190421,
        -0.98501423101223984, -0.98527764238894122, -0.98553873531217606,
        -0.98579750916756748, -0.98605396334619544, -0.98630809724459867,
        -0.98655991026477541, -0.98680940181418553, -0.987056571305751,
        -0.98730141815785843, -0.98754394179435923, -0.98778414164457218,
        -0.98802201714328353, -0.98825756773074946, -0.98849079285269659,
        -0.98872169196032378, -0.988950264510303, -0.989176509964781,
        -0.98940042779138038, -0.98962201746320089, -0.98984127845882053,
        -0.99005821026229712, -0.99027281236316911, -0.99048508425645709,
        -0.99069502544266463, -0.99090263542778, -0.99110791372327689,
        -0.99131085984611544, -0.9915114733187439, -0.99170975366909953,
        -0.99190570043060933, -0.9920993131421918, -0.99229059134825737,
        -0.99247953459871, -0.992666142448948, -0.9928504144598651,
        -0.99303235019785141, -0.9932119492347945, -0.99338921114808065,
        -0.9935641355205953, -0.9937367219407246, -0.99390697000235606,
        -0.99407487930487937, -0.9942404494531879, -0.9944036800576791,
        -0.99456457073425542, -0.9947231211043257, -0.99487933079480562,
        -0.99503319943811863, -0.99518472667219693, -0.99533391214048228,
        -0.99548075549192694, -0.99562525638099431, -0.99576741446765982,
        -0.99590722941741172, -0.996044700901252, -0.996179828595697,
        -0.996312612182778, -0.99644305135004263, -0.99657114579055484,
        -0.99669689520289606, -0.99682029929116567, -0.99694135776498216,
        -0.997060070339483, -0.99717643673532619, -0.99729045667869021,
        -0.9974021299012753, -0.99751145614030345, -0.99761843513851955,
        -0.99772306664419164, -0.99782535041111164, -0.997925286198596,
        -0.99802287377148624, -0.99811811290014918, -0.99821100336047819,
        -0.99830154493389289, -0.99838973740734016, -0.99847558057329477,
        -0.99855907422975931, -0.99864021818026527, -0.99871901223387294,
        -0.99879545620517241, -0.99886954991428356, -0.99894129318685687,
        -0.99901068585407338, -0.99907772775264536, -0.99914241872481691,
        -0.99920475861836389, -0.99926474728659442, -0.99932238458834954,
        -0.99937767038800285, -0.99943060455546173, -0.999481186966167,
        -0.99952941750109314, -0.99957529604674922, -0.99961882249517864,
        -0.99965999674395922, -0.99969881869620425, -0.99973528826056168,
        -0.99976940535121528, -0.99980116988788426, -0.9998305817958234,
        -0.99985764100582386, -0.99988234745421256, -0.9999047010828529,
        -0.9999247018391445, -0.99994234967602391, -0.9999576445519639,
        -0.99997058643097414, -0.99998117528260111, -0.9999894110819284,
        -0.99999529380957619, -0.99999882345170188, -1.0, -0.99999882345170188,
        -0.99999529380957619, -0.9999894110819284, -0.99998117528260111,
        -0.99997058643097414, -0.9999576445519639, -0.99994234967602391,
        -0.9999247018391445, -0.9999047010828529, -0.99988234745421256,
        -0.99985764100582386, -0.9998305817958234, -0.99980116988788426,
        -0.99976940535121528, -0.99973528826056168, -0.99969881869620425,
        -0.99965999674395922, -0.99961882249517864, -0.99957529604674922,
        -0.99952941750109314, -0.999481186966167, -0.99943060455546173,
        -0.99937767038800285, -0.99932238458834954, -0.99926474728659442,
        -0.99920475861836389, -0.99914241872481691, -0.99907772775264536,
        -0.99901068585407338, -0.99894129318685687, -0.99886954991428356,
        -0.99879545620517241, -0.99871901223387294, -0.99864021818026527,
        -0.99855907422975931, -0.99847558057329477, -0.99838973740734016,
        -0.99830154493389289, -0.99821100336047819, -0.99811811290014918,
        -0.99802287377148624, -0.997925286198596, -0.99782535041111164,
        -0.99772306664419164, -0.99761843513851955, -0.99751145614030345,
        -0.9974021299012753, -0.99729045667869021, -0.99717643673532619,
        -0.997060070339483, -0.99694135776498216, -0.99682029929116567,
        -0.99669689520289606, -0.99657114579055484, -0.99644305135004263,
        -0.996312612182778, -0.996179828595697, -0.996044700901252,
        -0.99590722941741172, -0.99576741446765982, -0.99562525638099431,
        -0.99548075549192694, -0.99533391214048228, -0.99518472667219693,
        -0.99503319943811863, -0.99487933079480562, -0.9947231211043257,
        -0.99456457073425542, -0.9944036800576791, -0.9942404494531879,
        -0.99407487930487937, -0.99390697000235606, -0.9937367219407246,
        -0.9935641355205953, -0.99338921114808065, -0.9932119492347945,
        -0.99303235019785141, -0.9928504144598651, -0.992666142448948,
        -0.99247953459871, -0.99229059134825737, -0.9920993131421918,
        -0.99190570043060933, -0.99170975366909953, -0.9915114733187439,
        -0.99131085984611544, -0.99110791372327689, -0.99090263542778,
        -0.99069502544266463, -0.99048508425645709, -0.99027281236316911,
        -0.99005821026229712, -0.98984127845882053, -0.98962201746320089,
        -0.98940042779138038, -0.989176509964781, -0.988950264510303,
        -0.98872169196032378, -0.98849079285269659, -0.98825756773074946,
        -0.98802201714328353, -0.98778414164457218, -0.98754394179435923,
        -0.98730141815785843, -0.987056571305751, -0.98680940181418553,
        -0.98655991026477541, -0.98630809724459867, -0.98605396334619544,
        -0.98579750916756748, -0.98553873531217606, -0.98527764238894122,
        -0.98501423101223984, -0.98474850180190421, -0.98448045538322093,
        -0.984210092386929, -0.98393741344921892, -0.98366241921173025,
        -0.98338511032155118, -0.98310548743121629, -0.98282355119870524,
        -0.98253930228744124, -0.98225274136628937, -0.98196386910955524,
        -0.98167268619698311, -0.98137919331375456, -0.98108339115048671,
        -0.98078528040323043, -0.98048486177346938, -0.98018213596811743,
        -0.97987710369951764, -0.97956976568544052, -0.979260122649082,
        -0.9789481753190622, -0.97863392442942321, -0.97831737071962765,
        -0.97799851493455714, -0.97767735782450993, -0.97735390014520007,
        -0.97702814265775439, -0.97670008612871184, -0.97636973133002114,
        -0.976037079039039, -0.97570213003852857, -0.975364885116657,
        -0.97502534506699412, -0.97468351068851067, -0.97433938278557586,
        -0.97399296216795583, -0.973644249650812, -0.97329324605469825,
        -0.97293995220556018, -0.97258436893473221, -0.97222649707893627,
        -0.9718663374802794, -0.97150389098625178, -0.97113915844972509,
        -0.97077214072895035, -0.9704028386875555, -0.970031253194544,
        -0.96965738512429245, -0.96928123535654853, -0.96890280477642887,
        -0.96852209427441727, -0.96813910474636244, -0.96775383709347551,
        -0.96736629222232851, -0.96697647104485207, -0.96658437447833312,
        -0.9661900034454125, -0.96579335887408368, -0.9653944416976894,
        -0.96499325285492032, -0.96458979328981276, -0.96418406395174583,
        -0.96377606579543984, -0.963365799780954, -0.96295326687368388,
        -0.96253846804435916, -0.96212140426904158, -0.96170207652912254,
        -0.96128048581132064, -0.96085663310767966, -0.96043051941556579,
        -0.960002145737666, -0.95957151308198452, -0.95913862246184189,
        -0.9587034748958716, -0.95826607140801767, -0.95782641302753291,
        -0.95738450078897586, -0.95694033573220882, -0.9564939189023951,
        -0.95604525134999641, -0.95559433413077111, -0.95514116830577078,
        -0.95468575494133834, -0.95422809510910567, -0.95376818988599033,
        -0.95330604035419386, -0.95284164760119872, -0.95237501271976588,
        -0.95190613680793235, -0.95143502096900834, -0.95096166631157508,
        -0.9504860739494817, -0.950008245001843, -0.94952818059303667,
        -0.94904588185270056, -0.94856134991573027, -0.94807458592227623,
        -0.94758559101774109, -0.94709436635277722, -0.94660091308328353,
        -0.94610523237040345, -0.94560732538052128, -0.94510719328526061,
        -0.94460483726148026, -0.94410025849127266, -0.94359345816196039,
        -0.94308443746609349, -0.94257319760144687, -0.94205973977101731,
        -0.94154406518302081, -0.94102617505088926, -0.9405060705932683,
        -0.93998375303401394, -0.93945922360218992, -0.9389324835320646,
        -0.93840353406310806, -0.93787237643998989, -0.937339011912575,
        -0.93680344173592156, -0.93626566717027826, -0.93572568948108037,
        -0.93518350993894761, -0.93463912981968078, -0.93409255040425887,
        -0.93354377297883617, -0.932992798834739, -0.93243962926846236,
        -0.93188426558166815, -0.93132670908118043, -0.93076696107898371,
        -0.93020502289221907, -0.92964089584318121, -0.92907458125931586,
        -0.92850608047321559, -0.92793539482261789, -0.92736252565040111,
        -0.92678747430458175, -0.92621024213831138, -0.92563083050987272,
        -0.92504924078267758, -0.9244654743252626, -0.92387953251128674,
        -0.92329141671952764, -0.92270112833387863, -0.92210866874334518,
        -0.9215140393420419, -0.92091724152918952, -0.92031827670911059,
        -0.91971714629122736, -0.91911385169005777, -0.91850839432521225,
        -0.9179007756213905, -0.91729099700837791, -0.9166790599210427,
        -0.91606496579933172, -0.91544871608826783, -0.9148303122379462,
        -0.91420975570353069, -0.91358704794525081, -0.91296219042839821,
        -0.91233518462332275, -0.91170603200542988, -0.91107473405517636,
        -0.91044129225806725, -0.90980570810465222, -0.90916798309052238,
        -0.90852811871630612, -0.90788611648766626, -0.90724197791529582,
        -0.90659570451491533, -0.90594729780726846, -0.90529675931811882,
        -0.90464409057824624, -0.90398929312344334, -0.90333236849451182,
        -0.90267331823725883, -0.90201214390249318, -0.901348847046022,
        -0.900683429228647, -0.90001589201616017, -0.89934623697934157,
        -0.89867446569395382, -0.89800057974073988, -0.89732458070541832,
        -0.89664647017868015, -0.89596624975618522, -0.89528392103855758,
        -0.8945994856313827, -0.89391294514520325, -0.89322430119551532,
        -0.89253355540276458, -0.89184070939234272, -0.89114576479458318,
        -0.89044872324475788, -0.88974958638307278, -0.88904835585466457,
        -0.88834503330959635, -0.88763962040285393, -0.88693211879434219,
        -0.88622253014888064, -0.8855108561362, -0.88479709843093779,
        -0.884081258712635, -0.88336333866573158, -0.88264333997956279,
        -0.881921264348355, -0.88119711347122209, -0.88047088905216075,
        -0.87974259280004741, -0.87901222642863353, -0.87827979165654158,
        -0.87754529020726135, -0.87680872380914565, -0.8760700941954066,
        -0.87532940310411089, -0.87458665227817611, -0.87384184346536686,
        -0.87309497841829009, -0.87234605889439154, -0.87159508665595109,
        -0.870842063470079, -0.87008699110871146, -0.86932987134860684,
        -0.8685707059713409, -0.86780949676330332, -0.86704624551569265,
        -0.866280954024513, -0.86551362409056909, -0.86474425751946238,
        -0.8639728561215867, -0.86319942171212416, -0.8624239561110405,
        -0.8616464611430813, -0.86086693863776731, -0.86008539042939014,
        -0.85930181835700847, -0.85851622426444274, -0.85772861000027212,
        -0.85693897741782876, -0.85614732837519447, -0.855353664735196,
        -0.85455798836540053, -0.85376030113811141, -0.85296060493036363,
        -0.85215890162391983, -0.8513551931052652, -0.85054948126560348,
        -0.84974176800085255, -0.84893205521163961, -0.84812034480329723,
        -0.84730663868585832, -0.84649093877405213, -0.84567324698729907,
        -0.84485356524970712, -0.84403189549006641, -0.84320823964184544,
        -0.84238259964318585, -0.84155497743689844, -0.84072537497045807,
        -0.83989379419599952, -0.83906023707031274, -0.83822470555483808,
        -0.83738720161566194, -0.836547727223512, -0.8357062843537526,
        -0.83486287498638, -0.83401750110601813, -0.83317016470191319,
        -0.83232086776792968, -0.83146961230254524, -0.83061640030884631,
        -0.829761233794523, -0.82890411477186487, -0.8280450452577558,
        -0.82718402727366913, -0.82632106284566353, -0.82545615400437755,
        -0.82458930278502529, -0.82372051122739143, -0.82284978137582643,
        -0.82197711527924155, -0.82110251499110465, -0.82022598256943469,
        -0.819347520076797, -0.81846712958029866, -0.81758481315158371,
        -0.81670057286682785, -0.81581441080673378, -0.81492632905652662,
        -0.81403632970594841, -0.81314441484925359, -0.81225058658520388,
        -0.81135484701706373, -0.81045719825259477, -0.80955764240405126,
        -0.808656181588175, -0.80775281792619036, -0.80684755354379933,
        -0.80594039057117628, -0.80503133114296366, -0.8041203773982657,
        -0.80320753148064494, -0.80229279553811572, -0.80137617172314024,
        -0.80045766219262282, -0.799537269107905, -0.79861499463476093,
        -0.79769084094339116, -0.79676481020841883, -0.79583690460888357,
        -0.794907126328237, -0.79397547755433717, -0.79304196047944364,
        -0.79210657730021239, -0.7911693302176902, -0.79023022143731,
        -0.78928925316888565, -0.78834642762660634, -0.78740174702903143,
        -0.78645521359908577, -0.78550682956405393, -0.78455659715557524,
        -0.78360451860963831, -0.78265059616657573, -0.78169483207105939,
        -0.78073722857209449, -0.77977778792301455, -0.778816512381476,
        -0.77785340420945315, -0.77688846567323244, -0.77592169904340769,
        -0.77495310659487393, -0.7739826906068229, -0.773010453362737,
        -0.77203639715038452, -0.77106052426181382, -0.7700828369933479,
        -0.7691033376455797, -0.76812202852336542, -0.7671389119358204,
        -0.76615399019631292, -0.765167265622459, -0.76417874053611679,
        -0.76318841726338127, -0.7621962981345789, -0.76120238548426178,
        -0.76020668165120242, -0.759209188978388, -0.75820990981301528,
        -0.75720884650648457, -0.75620600141439454, -0.75520137689653655,
        -0.75419497531688917, -0.75318679904361252, -0.7521768504490427,
        -0.75116513190968637, -0.75015164580621507, -0.74913639452345937,
        -0.7481193804504036, -0.74710060598018013, -0.74608007351006378,
        -0.745057785441466, -0.74403374417992929, -0.74300795213512172,
        -0.74198041172083107, -0.74095112535495922, -0.7399200954595162,
        -0.73888732446061511, -0.737852814788466, -0.73681656887736979,
        -0.73577858916571359, -0.7347388780959635, -0.73369743811466037,
        -0.73265427167241282, -0.73160938122389263, -0.73056276922782759,
        -0.729514438146997, -0.7284643904482252, -0.72741262860237577,
        -0.726359155084346, -0.72530397237306077, -0.724247082951467,
        -0.72318848930652746, -0.72212819392921535, -0.72106619931450811,
        -0.72000250796138165, -0.71893712237280449, -0.71787004505573171,
        -0.71680127852109954, -0.71573082528381859, -0.71465868786276909,
        -0.71358486878079352, -0.71250937056469243, -0.71143219574521643,
        -0.71035334685706242, -0.70927282643886569, -0.7081906370331954,
        -0.70710678118654757, -0.70602126144933974, -0.70493408037590488,
        -0.70384524052448494, -0.7027547444572253, -0.70166259474016845,
        -0.70056879394324834, -0.69947334464028377, -0.69837624940897292,
        -0.69727751083088652, -0.696177131491463, -0.69507511398000088,
        -0.69397146088965389, -0.69286617481742463, -0.69175925836415775,
        -0.6906507141345346, -0.68954054473706683, -0.68842875278409044,
        -0.687315340891759, -0.68620031168003859, -0.68508366777270036,
        -0.6839654117973154, -0.68284554638524808, -0.68172407417164971,
        -0.680600997795453, -0.679476319899365, -0.67835004312986147,
        -0.67722217013718033, -0.67609270357531592, -0.674961646102012,
        -0.673829000378756, -0.67269476907077286, -0.67155895484701833,
        -0.67042156038017309, -0.669282588346636, -0.66814204142651845,
        -0.66699992230363747, -0.66585623366550972, -0.66471097820334479,
        -0.66356415861203977, -0.66241577759017178, -0.66126583783999227,
        -0.66011434206742048, -0.65896129298203732, -0.65780669329707864,
        -0.65665054572942894, -0.65549285299961535, -0.65433361783180044,
        -0.65317284295377676, -0.6520105310969595, -0.650846684996381,
        -0.64968130739068319, -0.64851440102211244, -0.64734596863651206,
        -0.64617601298331628, -0.64500453681554393, -0.64383154288979139,
        -0.64265703396622686, -0.641481012808583, -0.64030348218415167,
        -0.63912444486377573, -0.637943903621844, -0.6367618612362842,
        -0.63557832048855611, -0.63439328416364549, -0.63320675505005719,
        -0.63201873593980906, -0.63082922962842447, -0.629638238914927,
        -0.6284457666018326, -0.62725181549514408, -0.62605638840434352,
        -0.62485948814238634, -0.62366111752569453, -0.62246127937415,
        -0.62125997651108755, -0.6200572117632891, -0.61885298796097632,
        -0.61764730793780387, -0.61644017453085365, -0.61523159058062682,
        -0.61402155893103849, -0.61281008242940971, -0.61159716392646191,
        -0.61038280627630948, -0.60916701233645321, -0.60794978496777363,
        -0.60673112703452448, -0.60551104140432555, -0.604289530948156,
        -0.60306659854034816, -0.60184224705858, -0.600616479383869,
        -0.59938929840056454, -0.59816070699634238, -0.59693070806219639,
        -0.59569930449243336, -0.59446649918466443, -0.5932322950397998,
        -0.591996694962041, -0.59075970185887416, -0.58952131864106394,
        -0.58828154822264522, -0.587040393520918, -0.58579785745643886,
        -0.58455394295301533, -0.58330865293769829, -0.58206199034077544,
        -0.58081395809576453, -0.57956455913940563, -0.57831379641165559,
        -0.57706167285567944, -0.57580819141784534, -0.57455335504771576,
        -0.5732971666980422, -0.572039629324757, -0.57078074588696726,
        -0.56952051934694714, -0.56825895267013149, -0.56699604882510868,
        -0.56573181078361312, -0.5644662415205195, -0.56319934401383409,
        -0.56193112124468936, -0.560661576197336, -0.55939071185913614,
        -0.5581185312205561, -0.5568450372751601, -0.55557023301960218,
        -0.55429412145362, -0.55301670558002747, -0.55173798840470734,
        -0.55045797293660481, -0.54917666218771966, -0.54789405917310019,
        -0.54661016691083486, -0.54532498842204646, -0.54403852673088382,
        -0.54275078486451589, -0.54146176585312344, -0.54017147272989285,
        -0.53887990853100842, -0.53758707629564539, -0.53629297906596318,
        -0.53499761988709715, -0.533701001807153, -0.5324031278771979,
        -0.531104001151255, -0.52980362468629461, -0.52850200154222848,
        -0.52719913478190128, -0.52589502747108463, -0.524589682678469,
        -0.52328310347565643, -0.52197529293715439, -0.52066625414036716,
        -0.51935599016558964, -0.51804450409599934, -0.51673179901764987,
        -0.51541787801946293, -0.51410274419322166, -0.512786400633563,
        -0.5114688504379703, -0.51015009670676681, -0.508830142543107,
        -0.50750899105297087, -0.50618664534515523, -0.50486310853126759,
        -0.50353838372571758, -0.50221247404571079, -0.50088538261124071,
        -0.49955711254508184, -0.49822766697278181, -0.49689704902265447,
        -0.49556526182577254, -0.49423230851595967, -0.49289819222978404,
        -0.4915629161065499, -0.49022648328829116, -0.48888889691976317,
        -0.487550160148436, -0.48621027612448642, -0.48486924800079106,
        -0.48352707893291874, -0.48218377207912272, -0.48083933060033396,
        -0.47949375766015295, -0.478147056424843, -0.47679923006332209,
        -0.47545028174715587, -0.47410021465054997, -0.47274903195034279,
        -0.47139673682599764, -0.47004333245959562, -0.46868882203582796,
        -0.46733320874198842, -0.46597649576796618, -0.46461868630623782,
        -0.46325978355186015, -0.46189979070246273, -0.46053871095824,
        -0.45917654752194409, -0.45781330359887717, -0.45644898239688392,
        -0.45508358712634384, -0.45371712100016387, -0.45234958723377089,
        -0.45098098904510386, -0.44961132965460654, -0.44824061228521989,
        -0.44686884016237416, -0.44549601651398174, -0.4441221445704292,
        -0.44274722756457, -0.44137126873171667, -0.43999427130963326,
        -0.43861623853852766, -0.43723717366104409, -0.43585707992225547,
        -0.43447596056965565, -0.43309381885315196, -0.43171065802505726,
        -0.43032648134008261, -0.42894129205532949, -0.42755509343028208,
        -0.42616788872679962, -0.42477968120910881, -0.42339047414379605,
        -0.42200027079979968, -0.42060907444840251, -0.41921688836322391,
        -0.41782371582021227, -0.41642956009763715, -0.41503442447608163,
        -0.4136383122384345, -0.41224122666988289, -0.41084317105790391,
        -0.40944414869225759, -0.40804416286497869, -0.40664321687036903,
        -0.40524131400498986, -0.40383845756765407, -0.40243465085941843,
        -0.40102989718357562, -0.39962419984564679, -0.39821756215337356,
        -0.39680998741671031, -0.39540147894781635, -0.3939920400610481,
        -0.39258167407295147, -0.39117038430225387, -0.38975817406985641,
        -0.38834504669882625, -0.38693100551438858, -0.38551605384391885,
        -0.38410019501693504, -0.38268343236508978, -0.38126576922216238,
        -0.37984720892405116, -0.37842775480876556, -0.37700741021641826,
        -0.37558617848921722, -0.37416406297145793, -0.37274106700951576,
        -0.37131719395183749, -0.3698924471489341, -0.36846682995337232,
        -0.36704034571976718, -0.36561299780477385, -0.36418478956707989,
        -0.36275572436739723, -0.36132580556845428, -0.35989503653498811,
        -0.35846342063373654, -0.35703096123343, -0.35559766170478385,
        -0.35416352542049034, -0.35272855575521073, -0.35129275608556709,
        -0.34985612979013492, -0.34841868024943456, -0.34698041084592368,
        -0.34554132496398909, -0.34410142598993881, -0.34266071731199438,
        -0.34121920232028236, -0.33977688440682685, -0.33833376696554113,
        -0.33688985339222005, -0.3354451470845316, -0.33399965144200938,
        -0.33255336986604422, -0.33110630575987643, -0.32965846252858749,
        -0.3282098435790925, -0.32676045232013173, -0.32531029216226293,
        -0.32385936651785285, -0.32240767880106985, -0.32095523242787521,
        -0.31950203081601569, -0.31804807738501495, -0.31659337555616585,
        -0.31513792875252244, -0.31368174039889152, -0.31222481392182488,
        -0.31076715274961147, -0.30930876031226873, -0.30784964004153487,
        -0.30638979537086092, -0.30492922973540237, -0.30346794657201132,
        -0.30200594931922808, -0.30054324141727345, -0.29907982630804048,
        -0.2976157074350862, -0.29615088824362379, -0.29468537218051433,
        -0.29321916269425863, -0.29175226323498926, -0.29028467725446233,
        -0.28881640820604948, -0.28734745954472951, -0.28587783472708062,
        -0.28440753721127188, -0.28293657045705539, -0.28146493792575794,
        -0.27999264308027322, -0.27851968938505306, -0.2770460803060999,
        -0.27557181931095814, -0.27409690986870638, -0.272621355449949,
        -0.271145159526808, -0.26966832557291509, -0.26819085706340318,
        -0.26671275747489837, -0.26523403028551179, -0.26375467897483135,
        -0.26227470702391359, -0.26079411791527551, -0.25931291513288623,
        -0.257831102162159, -0.25634868248994291, -0.25486565960451457,
        -0.25338203699557016, -0.25189781815421697, -0.25041300657296522,
        -0.24892760574572015, -0.24744161916777327, -0.24595505033579459,
        -0.24446790274782415, -0.24298017990326387, -0.24149188530286933,
        -0.2400030224487415, -0.23851359484431842, -0.2370236059943672,
        -0.23553305940497549, -0.23404195858354343, -0.23255030703877524,
        -0.23105810828067111, -0.22956536582051887, -0.22807208317088573,
        -0.22657826384561, -0.22508391135979283, -0.22358902922979,
        -0.22209362097320351, -0.22059769010887351, -0.2191012401568698,
        -0.21760427463848364, -0.21610679707621952, -0.21460881099378676,
        -0.21311031991609136, -0.21161132736922755, -0.21011183688046961,
        -0.20861185197826349, -0.20711137619221856, -0.20561041305309924,
        -0.20410896609281687, -0.20260703884442113, -0.2011046348420919,
        -0.19960175762113097, -0.19809841071795356, -0.19659459767008022,
        -0.19509032201612825, -0.19358558729580361, -0.19208039704989244,
        -0.19057475482025274, -0.18906866414980619, -0.1875621285825296,
        -0.18605515166344663, -0.18454773693861962, -0.18303988795514095,
        -0.18153160826112497, -0.18002290140569951, -0.17851377093899751,
        -0.17700422041214875, -0.17549425337727143, -0.17398387338746382,
        -0.17247308399679595, -0.17096188876030122, -0.16945029123396796,
        -0.16793829497473117, -0.1664259035404641, -0.16491312048996992,
        -0.16339994938297323, -0.16188639378011183, -0.16037245724292828,
        -0.15885814333386145, -0.15734345561623825, -0.15582839765426523,
        -0.1543129730130201, -0.15279718525844344, -0.15128103795733022,
        -0.14976453467732151, -0.14824767898689603, -0.14673047445536175,
        -0.14521292465284746, -0.14369503315029447, -0.14217680351944803,
        -0.14065823933284921, -0.1391393441638262, -0.13762012158648604,
        -0.1361005751757062, -0.13458070850712617, -0.13306052515713906,
        -0.13154002870288312, -0.13001922272223335, -0.12849811079379317,
        -0.12697669649688587, -0.12545498341154623, -0.12393297511851216,
        -0.1224106751992162, -0.12088808723577708, -0.11936521481099135,
        -0.11784206150832498, -0.11631863091190475, -0.11479492660651008,
        -0.11327095217756435, -0.11174671121112659, -0.11022220729388306,
        -0.10869744401313872, -0.10717242495680884, -0.10564715371341062,
        -0.10412163387205459, -0.10259586902243628, -0.10106986275482782,
        -0.099543618660069319, -0.0980171403295606, -0.096490431355252593,
        -0.094963495329638992, -0.093436335845747787, -0.091908956497132724,
        -0.090381360877864983, -0.0888535525825246, -0.087325535206192059,
        -0.0857973123444399, -0.084268887593324071, -0.082740264549375692,
        -0.081211446809592441, -0.079682437971430126, -0.078153241632794232,
        -0.076623861392031492, -0.0750943008479213, -0.073564563599667426,
        -0.072034653246889332, -0.070504573389613856, -0.068974327628266746,
        -0.067443919563664051, -0.0659133527970038, -0.064382630929857465,
        -0.0628517575641614, -0.061320736302208578, -0.059789570746639868,
        -0.058258264500435752, -0.056726821166907748, -0.055195244349689941,
        -0.05366353765273052, -0.052131704680283324, -0.050599749036899282,
        -0.049067674327418015, -0.0475354841569593, -0.046003182130914623,
        -0.044470771854938668, -0.04293825693494082, -0.041405640977076739,
        -0.039872927587739811, -0.038340120373552694, -0.036807222941358832,
        -0.035274238898213947, -0.03374117185137758, -0.032208025408304586,
        -0.030674803176636626, -0.029141508764193722, -0.02760814577896574,
        -0.0260747178291039, -0.024541228522912288, -0.023007681468839369,
        -0.021474080275469508, -0.019940428551514441, -0.01840672990580482,
        -0.01687298794728171, -0.0153392062849881, -0.013805388528060391,
        -0.012271538285719925, -0.010737659167264491, -0.00920375478205982,
        -0.007669828739531097, -0.0061358846491544753, -0.0046019261204485705,
        -0.0030679567629659761, -0.0015339801862847655, -0.0 };

      static const short bitrevIndex[2048] = { 1, 1025, 513, 1537, 257, 1281,
        769, 1793, 129, 1153, 641, 1665, 385, 1409, 897, 1921, 65, 1089, 577,
        1601, 321, 1345, 833, 1857, 193, 1217, 705, 1729, 449, 1473, 961, 1985,
        33, 1057, 545, 1569, 289, 1313, 801, 1825, 161, 1185, 673, 1697, 417,
        1441, 929, 1953, 97, 1121, 609, 1633, 353, 1377, 865, 1889, 225, 1249,
        737, 1761, 481, 1505, 993, 2017, 17, 1041, 529, 1553, 273, 1297, 785,
        1809, 145, 1169, 657, 1681, 401, 1425, 913, 1937, 81, 1105, 593, 1617,
        337, 1361, 849, 1873, 209, 1233, 721, 1745, 465, 1489, 977, 2001, 49,
        1073, 561, 1585, 305, 1329, 817, 1841, 177, 1201, 689, 1713, 433, 1457,
        945, 1969, 113, 1137, 625, 1649, 369, 1393, 881, 1905, 241, 1265, 753,
        1777, 497, 1521, 1009, 2033, 9, 1033, 521, 1545, 265, 1289, 777, 1801,
        137, 1161, 649, 1673, 393, 1417, 905, 1929, 73, 1097, 585, 1609, 329,
        1353, 841, 1865, 201, 1225, 713, 1737, 457, 1481, 969, 1993, 41, 1065,
        553, 1577, 297, 1321, 809, 1833, 169, 1193, 681, 1705, 425, 1449, 937,
        1961, 105, 1129, 617, 1641, 361, 1385, 873, 1897, 233, 1257, 745, 1769,
        489, 1513, 1001, 2025, 25, 1049, 537, 1561, 281, 1305, 793, 1817, 153,
        1177, 665, 1689, 409, 1433, 921, 1945, 89, 1113, 601, 1625, 345, 1369,
        857, 1881, 217, 1241, 729, 1753, 473, 1497, 985, 2009, 57, 1081, 569,
        1593, 313, 1337, 825, 1849, 185, 1209, 697, 1721, 441, 1465, 953, 1977,
        121, 1145, 633, 1657, 377, 1401, 889, 1913, 249, 1273, 761, 1785, 505,
        1529, 1017, 2041, 5, 1029, 517, 1541, 261, 1285, 773, 1797, 133, 1157,
        645, 1669, 389, 1413, 901, 1925, 69, 1093, 581, 1605, 325, 1349, 837,
        1861, 197, 1221, 709, 1733, 453, 1477, 965, 1989, 37, 1061, 549, 1573,
        293, 1317, 805, 1829, 165, 1189, 677, 1701, 421, 1445, 933, 1957, 101,
        1125, 613, 1637, 357, 1381, 869, 1893, 229, 1253, 741, 1765, 485, 1509,
        997, 2021, 21, 1045, 533, 1557, 277, 1301, 789, 1813, 149, 1173, 661,
        1685, 405, 1429, 917, 1941, 85, 1109, 597, 1621, 341, 1365, 853, 1877,
        213, 1237, 725, 1749, 469, 1493, 981, 2005, 53, 1077, 565, 1589, 309,
        1333, 821, 1845, 181, 1205, 693, 1717, 437, 1461, 949, 1973, 117, 1141,
        629, 1653, 373, 1397, 885, 1909, 245, 1269, 757, 1781, 501, 1525, 1013,
        2037, 13, 1037, 525, 1549, 269, 1293, 781, 1805, 141, 1165, 653, 1677,
        397, 1421, 909, 1933, 77, 1101, 589, 1613, 333, 1357, 845, 1869, 205,
        1229, 717, 1741, 461, 1485, 973, 1997, 45, 1069, 557, 1581, 301, 1325,
        813, 1837, 173, 1197, 685, 1709, 429, 1453, 941, 1965, 109, 1133, 621,
        1645, 365, 1389, 877, 1901, 237, 1261, 749, 1773, 493, 1517, 1005, 2029,
        29, 1053, 541, 1565, 285, 1309, 797, 1821, 157, 1181, 669, 1693, 413,
        1437, 925, 1949, 93, 1117, 605, 1629, 349, 1373, 861, 1885, 221, 1245,
        733, 1757, 477, 1501, 989, 2013, 61, 1085, 573, 1597, 317, 1341, 829,
        1853, 189, 1213, 701, 1725, 445, 1469, 957, 1981, 125, 1149, 637, 1661,
        381, 1405, 893, 1917, 253, 1277, 765, 1789, 509, 1533, 1021, 2045, 3,
        1027, 515, 1539, 259, 1283, 771, 1795, 131, 1155, 643, 1667, 387, 1411,
        899, 1923, 67, 1091, 579, 1603, 323, 1347, 835, 1859, 195, 1219, 707,
        1731, 451, 1475, 963, 1987, 35, 1059, 547, 1571, 291, 1315, 803, 1827,
        163, 1187, 675, 1699, 419, 1443, 931, 1955, 99, 1123, 611, 1635, 355,
        1379, 867, 1891, 227, 1251, 739, 1763, 483, 1507, 995, 2019, 19, 1043,
        531, 1555, 275, 1299, 787, 1811, 147, 1171, 659, 1683, 403, 1427, 915,
        1939, 83, 1107, 595, 1619, 339, 1363, 851, 1875, 211, 1235, 723, 1747,
        467, 1491, 979, 2003, 51, 1075, 563, 1587, 307, 1331, 819, 1843, 179,
        1203, 691, 1715, 435, 1459, 947, 1971, 115, 1139, 627, 1651, 371, 1395,
        883, 1907, 243, 1267, 755, 1779, 499, 1523, 1011, 2035, 11, 1035, 523,
        1547, 267, 1291, 779, 1803, 139, 1163, 651, 1675, 395, 1419, 907, 1931,
        75, 1099, 587, 1611, 331, 1355, 843, 1867, 203, 1227, 715, 1739, 459,
        1483, 971, 1995, 43, 1067, 555, 1579, 299, 1323, 811, 1835, 171, 1195,
        683, 1707, 427, 1451, 939, 1963, 107, 1131, 619, 1643, 363, 1387, 875,
        1899, 235, 1259, 747, 1771, 491, 1515, 1003, 2027, 27, 1051, 539, 1563,
        283, 1307, 795, 1819, 155, 1179, 667, 1691, 411, 1435, 923, 1947, 91,
        1115, 603, 1627, 347, 1371, 859, 1883, 219, 1243, 731, 1755, 475, 1499,
        987, 2011, 59, 1083, 571, 1595, 315, 1339, 827, 1851, 187, 1211, 699,
        1723, 443, 1467, 955, 1979, 123, 1147, 635, 1659, 379, 1403, 891, 1915,
        251, 1275, 763, 1787, 507, 1531, 1019, 2043, 7, 1031, 519, 1543, 263,
        1287, 775, 1799, 135, 1159, 647, 1671, 391, 1415, 903, 1927, 71, 1095,
        583, 1607, 327, 1351, 839, 1863, 199, 1223, 711, 1735, 455, 1479, 967,
        1991, 39, 1063, 551, 1575, 295, 1319, 807, 1831, 167, 1191, 679, 1703,
        423, 1447, 935, 1959, 103, 1127, 615, 1639, 359, 1383, 871, 1895, 231,
        1255, 743, 1767, 487, 1511, 999, 2023, 23, 1047, 535, 1559, 279, 1303,
        791, 1815, 151, 1175, 663, 1687, 407, 1431, 919, 1943, 87, 1111, 599,
        1623, 343, 1367, 855, 1879, 215, 1239, 727, 1751, 471, 1495, 983, 2007,
        55, 1079, 567, 1591, 311, 1335, 823, 1847, 183, 1207, 695, 1719, 439,
        1463, 951, 1975, 119, 1143, 631, 1655, 375, 1399, 887, 1911, 247, 1271,
        759, 1783, 503, 1527, 1015, 2039, 15, 1039, 527, 1551, 271, 1295, 783,
        1807, 143, 1167, 655, 1679, 399, 1423, 911, 1935, 79, 1103, 591, 1615,
        335, 1359, 847, 1871, 207, 1231, 719, 1743, 463, 1487, 975, 1999, 47,
        1071, 559, 1583, 303, 1327, 815, 1839, 175, 1199, 687, 1711, 431, 1455,
        943, 1967, 111, 1135, 623, 1647, 367, 1391, 879, 1903, 239, 1263, 751,
        1775, 495, 1519, 1007, 2031, 31, 1055, 543, 1567, 287, 1311, 799, 1823,
        159, 1183, 671, 1695, 415, 1439, 927, 1951, 95, 1119, 607, 1631, 351,
        1375, 863, 1887, 223, 1247, 735, 1759, 479, 1503, 991, 2015, 63, 1087,
        575, 1599, 319, 1343, 831, 1855, 191, 1215, 703, 1727, 447, 1471, 959,
        1983, 127, 1151, 639, 1663, 383, 1407, 895, 1919, 255, 1279, 767, 1791,
        511, 1535, 1023, 2047, 2, 1026, 514, 1538, 258, 1282, 770, 1794, 130,
        1154, 642, 1666, 386, 1410, 898, 1922, 66, 1090, 578, 1602, 322, 1346,
        834, 1858, 194, 1218, 706, 1730, 450, 1474, 962, 1986, 34, 1058, 546,
        1570, 290, 1314, 802, 1826, 162, 1186, 674, 1698, 418, 1442, 930, 1954,
        98, 1122, 610, 1634, 354, 1378, 866, 1890, 226, 1250, 738, 1762, 482,
        1506, 994, 2018, 18, 1042, 530, 1554, 274, 1298, 786, 1810, 146, 1170,
        658, 1682, 402, 1426, 914, 1938, 82, 1106, 594, 1618, 338, 1362, 850,
        1874, 210, 1234, 722, 1746, 466, 1490, 978, 2002, 50, 1074, 562, 1586,
        306, 1330, 818, 1842, 178, 1202, 690, 1714, 434, 1458, 946, 1970, 114,
        1138, 626, 1650, 370, 1394, 882, 1906, 242, 1266, 754, 1778, 498, 1522,
        1010, 2034, 10, 1034, 522, 1546, 266, 1290, 778, 1802, 138, 1162, 650,
        1674, 394, 1418, 906, 1930, 74, 1098, 586, 1610, 330, 1354, 842, 1866,
        202, 1226, 714, 1738, 458, 1482, 970, 1994, 42, 1066, 554, 1578, 298,
        1322, 810, 1834, 170, 1194, 682, 1706, 426, 1450, 938, 1962, 106, 1130,
        618, 1642, 362, 1386, 874, 1898, 234, 1258, 746, 1770, 490, 1514, 1002,
        2026, 26, 1050, 538, 1562, 282, 1306, 794, 1818, 154, 1178, 666, 1690,
        410, 1434, 922, 1946, 90, 1114, 602, 1626, 346, 1370, 858, 1882, 218,
        1242, 730, 1754, 474, 1498, 986, 2010, 58, 1082, 570, 1594, 314, 1338,
        826, 1850, 186, 1210, 698, 1722, 442, 1466, 954, 1978, 122, 1146, 634,
        1658, 378, 1402, 890, 1914, 250, 1274, 762, 1786, 506, 1530, 1018, 2042,
        6, 1030, 518, 1542, 262, 1286, 774, 1798, 134, 1158, 646, 1670, 390,
        1414, 902, 1926, 70, 1094, 582, 1606, 326, 1350, 838, 1862, 198, 1222,
        710, 1734, 454, 1478, 966, 1990, 38, 1062, 550, 1574, 294, 1318, 806,
        1830, 166, 1190, 678, 1702, 422, 1446, 934, 1958, 102, 1126, 614, 1638,
        358, 1382, 870, 1894, 230, 1254, 742, 1766, 486, 1510, 998, 2022, 22,
        1046, 534, 1558, 278, 1302, 790, 1814, 150, 1174, 662, 1686, 406, 1430,
        918, 1942, 86, 1110, 598, 1622, 342, 1366, 854, 1878, 214, 1238, 726,
        1750, 470, 1494, 982, 2006, 54, 1078, 566, 1590, 310, 1334, 822, 1846,
        182, 1206, 694, 1718, 438, 1462, 950, 1974, 118, 1142, 630, 1654, 374,
        1398, 886, 1910, 246, 1270, 758, 1782, 502, 1526, 1014, 2038, 14, 1038,
        526, 1550, 270, 1294, 782, 1806, 142, 1166, 654, 1678, 398, 1422, 910,
        1934, 78, 1102, 590, 1614, 334, 1358, 846, 1870, 206, 1230, 718, 1742,
        462, 1486, 974, 1998, 46, 1070, 558, 1582, 302, 1326, 814, 1838, 174,
        1198, 686, 1710, 430, 1454, 942, 1966, 110, 1134, 622, 1646, 366, 1390,
        878, 1902, 238, 1262, 750, 1774, 494, 1518, 1006, 2030, 30, 1054, 542,
        1566, 286, 1310, 798, 1822, 158, 1182, 670, 1694, 414, 1438, 926, 1950,
        94, 1118, 606, 1630, 350, 1374, 862, 1886, 222, 1246, 734, 1758, 478,
        1502, 990, 2014, 62, 1086, 574, 1598, 318, 1342, 830, 1854, 190, 1214,
        702, 1726, 446, 1470, 958, 1982, 126, 1150, 638, 1662, 382, 1406, 894,
        1918, 254, 1278, 766, 1790, 510, 1534, 1022, 2046, 4, 1028, 516, 1540,
        260, 1284, 772, 1796, 132, 1156, 644, 1668, 388, 1412, 900, 1924, 68,
        1092, 580, 1604, 324, 1348, 836, 1860, 196, 1220, 708, 1732, 452, 1476,
        964, 1988, 36, 1060, 548, 1572, 292, 1316, 804, 1828, 164, 1188, 676,
        1700, 420, 1444, 932, 1956, 100, 1124, 612, 1636, 356, 1380, 868, 1892,
        228, 1252, 740, 1764, 484, 1508, 996, 2020, 20, 1044, 532, 1556, 276,
        1300, 788, 1812, 148, 1172, 660, 1684, 404, 1428, 916, 1940, 84, 1108,
        596, 1620, 340, 1364, 852, 1876, 212, 1236, 724, 1748, 468, 1492, 980,
        2004, 52, 1076, 564, 1588, 308, 1332, 820, 1844, 180, 1204, 692, 1716,
        436, 1460, 948, 1972, 116, 1140, 628, 1652, 372, 1396, 884, 1908, 244,
        1268, 756, 1780, 500, 1524, 1012, 2036, 12, 1036, 524, 1548, 268, 1292,
        780, 1804, 140, 1164, 652, 1676, 396, 1420, 908, 1932, 76, 1100, 588,
        1612, 332, 1356, 844, 1868, 204, 1228, 716, 1740, 460, 1484, 972, 1996,
        44, 1068, 556, 1580, 300, 1324, 812, 1836, 172, 1196, 684, 1708, 428,
        1452, 940, 1964, 108, 1132, 620, 1644, 364, 1388, 876, 1900, 236, 1260,
        748, 1772, 492, 1516, 1004, 2028, 28, 1052, 540, 1564, 284, 1308, 796,
        1820, 156, 1180, 668, 1692, 412, 1436, 924, 1948, 92, 1116, 604, 1628,
        348, 1372, 860, 1884, 220, 1244, 732, 1756, 476, 1500, 988, 2012, 60,
        1084, 572, 1596, 316, 1340, 828, 1852, 188, 1212, 700, 1724, 444, 1468,
        956, 1980, 124, 1148, 636, 1660, 380, 1404, 892, 1916, 252, 1276, 764,
        1788, 508, 1532, 1020, 2044, 8, 1032, 520, 1544, 264, 1288, 776, 1800,
        136, 1160, 648, 1672, 392, 1416, 904, 1928, 72, 1096, 584, 1608, 328,
        1352, 840, 1864, 200, 1224, 712, 1736, 456, 1480, 968, 1992, 40, 1064,
        552, 1576, 296, 1320, 808, 1832, 168, 1192, 680, 1704, 424, 1448, 936,
        1960, 104, 1128, 616, 1640, 360, 1384, 872, 1896, 232, 1256, 744, 1768,
        488, 1512, 1000, 2024, 24, 1048, 536, 1560, 280, 1304, 792, 1816, 152,
        1176, 664, 1688, 408, 1432, 920, 1944, 88, 1112, 600, 1624, 344, 1368,
        856, 1880, 216, 1240, 728, 1752, 472, 1496, 984, 2008, 56, 1080, 568,
        1592, 312, 1336, 824, 1848, 184, 1208, 696, 1720, 440, 1464, 952, 1976,
        120, 1144, 632, 1656, 376, 1400, 888, 1912, 248, 1272, 760, 1784, 504,
        1528, 1016, 2040, 16, 1040, 528, 1552, 272, 1296, 784, 1808, 144, 1168,
        656, 1680, 400, 1424, 912, 1936, 80, 1104, 592, 1616, 336, 1360, 848,
        1872, 208, 1232, 720, 1744, 464, 1488, 976, 2000, 48, 1072, 560, 1584,
        304, 1328, 816, 1840, 176, 1200, 688, 1712, 432, 1456, 944, 1968, 112,
        1136, 624, 1648, 368, 1392, 880, 1904, 240, 1264, 752, 1776, 496, 1520,
        1008, 2032, 32, 1056, 544, 1568, 288, 1312, 800, 1824, 160, 1184, 672,
        1696, 416, 1440, 928, 1952, 96, 1120, 608, 1632, 352, 1376, 864, 1888,
        224, 1248, 736, 1760, 480, 1504, 992, 2016, 64, 1088, 576, 1600, 320,
        1344, 832, 1856, 192, 1216, 704, 1728, 448, 1472, 960, 1984, 128, 1152,
        640, 1664, 384, 1408, 896, 1920, 256, 1280, 768, 1792, 512, 1536, 1024,
        2048 };

      static const short iv[2048] = { 1, 2048, 2047, 2046, 2045, 2044, 2043,
        2042, 2041, 2040, 2039, 2038, 2037, 2036, 2035, 2034, 2033, 2032, 2031,
        2030, 2029, 2028, 2027, 2026, 2025, 2024, 2023, 2022, 2021, 2020, 2019,
        2018, 2017, 2016, 2015, 2014, 2013, 2012, 2011, 2010, 2009, 2008, 2007,
        2006, 2005, 2004, 2003, 2002, 2001, 2000, 1999, 1998, 1997, 1996, 1995,
        1994, 1993, 1992, 1991, 1990, 1989, 1988, 1987, 1986, 1985, 1984, 1983,
        1982, 1981, 1980, 1979, 1978, 1977, 1976, 1975, 1974, 1973, 1972, 1971,
        1970, 1969, 1968, 1967, 1966, 1965, 1964, 1963, 1962, 1961, 1960, 1959,
        1958, 1957, 1956, 1955, 1954, 1953, 1952, 1951, 1950, 1949, 1948, 1947,
        1946, 1945, 1944, 1943, 1942, 1941, 1940, 1939, 1938, 1937, 1936, 1935,
        1934, 1933, 1932, 1931, 1930, 1929, 1928, 1927, 1926, 1925, 1924, 1923,
        1922, 1921, 1920, 1919, 1918, 1917, 1916, 1915, 1914, 1913, 1912, 1911,
        1910, 1909, 1908, 1907, 1906, 1905, 1904, 1903, 1902, 1901, 1900, 1899,
        1898, 1897, 1896, 1895, 1894, 1893, 1892, 1891, 1890, 1889, 1888, 1887,
        1886, 1885, 1884, 1883, 1882, 1881, 1880, 1879, 1878, 1877, 1876, 1875,
        1874, 1873, 1872, 1871, 1870, 1869, 1868, 1867, 1866, 1865, 1864, 1863,
        1862, 1861, 1860, 1859, 1858, 1857, 1856, 1855, 1854, 1853, 1852, 1851,
        1850, 1849, 1848, 1847, 1846, 1845, 1844, 1843, 1842, 1841, 1840, 1839,
        1838, 1837, 1836, 1835, 1834, 1833, 1832, 1831, 1830, 1829, 1828, 1827,
        1826, 1825, 1824, 1823, 1822, 1821, 1820, 1819, 1818, 1817, 1816, 1815,
        1814, 1813, 1812, 1811, 1810, 1809, 1808, 1807, 1806, 1805, 1804, 1803,
        1802, 1801, 1800, 1799, 1798, 1797, 1796, 1795, 1794, 1793, 1792, 1791,
        1790, 1789, 1788, 1787, 1786, 1785, 1784, 1783, 1782, 1781, 1780, 1779,
        1778, 1777, 1776, 1775, 1774, 1773, 1772, 1771, 1770, 1769, 1768, 1767,
        1766, 1765, 1764, 1763, 1762, 1761, 1760, 1759, 1758, 1757, 1756, 1755,
        1754, 1753, 1752, 1751, 1750, 1749, 1748, 1747, 1746, 1745, 1744, 1743,
        1742, 1741, 1740, 1739, 1738, 1737, 1736, 1735, 1734, 1733, 1732, 1731,
        1730, 1729, 1728, 1727, 1726, 1725, 1724, 1723, 1722, 1721, 1720, 1719,
        1718, 1717, 1716, 1715, 1714, 1713, 1712, 1711, 1710, 1709, 1708, 1707,
        1706, 1705, 1704, 1703, 1702, 1701, 1700, 1699, 1698, 1697, 1696, 1695,
        1694, 1693, 1692, 1691, 1690, 1689, 1688, 1687, 1686, 1685, 1684, 1683,
        1682, 1681, 1680, 1679, 1678, 1677, 1676, 1675, 1674, 1673, 1672, 1671,
        1670, 1669, 1668, 1667, 1666, 1665, 1664, 1663, 1662, 1661, 1660, 1659,
        1658, 1657, 1656, 1655, 1654, 1653, 1652, 1651, 1650, 1649, 1648, 1647,
        1646, 1645, 1644, 1643, 1642, 1641, 1640, 1639, 1638, 1637, 1636, 1635,
        1634, 1633, 1632, 1631, 1630, 1629, 1628, 1627, 1626, 1625, 1624, 1623,
        1622, 1621, 1620, 1619, 1618, 1617, 1616, 1615, 1614, 1613, 1612, 1611,
        1610, 1609, 1608, 1607, 1606, 1605, 1604, 1603, 1602, 1601, 1600, 1599,
        1598, 1597, 1596, 1595, 1594, 1593, 1592, 1591, 1590, 1589, 1588, 1587,
        1586, 1585, 1584, 1583, 1582, 1581, 1580, 1579, 1578, 1577, 1576, 1575,
        1574, 1573, 1572, 1571, 1570, 1569, 1568, 1567, 1566, 1565, 1564, 1563,
        1562, 1561, 1560, 1559, 1558, 1557, 1556, 1555, 1554, 1553, 1552, 1551,
        1550, 1549, 1548, 1547, 1546, 1545, 1544, 1543, 1542, 1541, 1540, 1539,
        1538, 1537, 1536, 1535, 1534, 1533, 1532, 1531, 1530, 1529, 1528, 1527,
        1526, 1525, 1524, 1523, 1522, 1521, 1520, 1519, 1518, 1517, 1516, 1515,
        1514, 1513, 1512, 1511, 1510, 1509, 1508, 1507, 1506, 1505, 1504, 1503,
        1502, 1501, 1500, 1499, 1498, 1497, 1496, 1495, 1494, 1493, 1492, 1491,
        1490, 1489, 1488, 1487, 1486, 1485, 1484, 1483, 1482, 1481, 1480, 1479,
        1478, 1477, 1476, 1475, 1474, 1473, 1472, 1471, 1470, 1469, 1468, 1467,
        1466, 1465, 1464, 1463, 1462, 1461, 1460, 1459, 1458, 1457, 1456, 1455,
        1454, 1453, 1452, 1451, 1450, 1449, 1448, 1447, 1446, 1445, 1444, 1443,
        1442, 1441, 1440, 1439, 1438, 1437, 1436, 1435, 1434, 1433, 1432, 1431,
        1430, 1429, 1428, 1427, 1426, 1425, 1424, 1423, 1422, 1421, 1420, 1419,
        1418, 1417, 1416, 1415, 1414, 1413, 1412, 1411, 1410, 1409, 1408, 1407,
        1406, 1405, 1404, 1403, 1402, 1401, 1400, 1399, 1398, 1397, 1396, 1395,
        1394, 1393, 1392, 1391, 1390, 1389, 1388, 1387, 1386, 1385, 1384, 1383,
        1382, 1381, 1380, 1379, 1378, 1377, 1376, 1375, 1374, 1373, 1372, 1371,
        1370, 1369, 1368, 1367, 1366, 1365, 1364, 1363, 1362, 1361, 1360, 1359,
        1358, 1357, 1356, 1355, 1354, 1353, 1352, 1351, 1350, 1349, 1348, 1347,
        1346, 1345, 1344, 1343, 1342, 1341, 1340, 1339, 1338, 1337, 1336, 1335,
        1334, 1333, 1332, 1331, 1330, 1329, 1328, 1327, 1326, 1325, 1324, 1323,
        1322, 1321, 1320, 1319, 1318, 1317, 1316, 1315, 1314, 1313, 1312, 1311,
        1310, 1309, 1308, 1307, 1306, 1305, 1304, 1303, 1302, 1301, 1300, 1299,
        1298, 1297, 1296, 1295, 1294, 1293, 1292, 1291, 1290, 1289, 1288, 1287,
        1286, 1285, 1284, 1283, 1282, 1281, 1280, 1279, 1278, 1277, 1276, 1275,
        1274, 1273, 1272, 1271, 1270, 1269, 1268, 1267, 1266, 1265, 1264, 1263,
        1262, 1261, 1260, 1259, 1258, 1257, 1256, 1255, 1254, 1253, 1252, 1251,
        1250, 1249, 1248, 1247, 1246, 1245, 1244, 1243, 1242, 1241, 1240, 1239,
        1238, 1237, 1236, 1235, 1234, 1233, 1232, 1231, 1230, 1229, 1228, 1227,
        1226, 1225, 1224, 1223, 1222, 1221, 1220, 1219, 1218, 1217, 1216, 1215,
        1214, 1213, 1212, 1211, 1210, 1209, 1208, 1207, 1206, 1205, 1204, 1203,
        1202, 1201, 1200, 1199, 1198, 1197, 1196, 1195, 1194, 1193, 1192, 1191,
        1190, 1189, 1188, 1187, 1186, 1185, 1184, 1183, 1182, 1181, 1180, 1179,
        1178, 1177, 1176, 1175, 1174, 1173, 1172, 1171, 1170, 1169, 1168, 1167,
        1166, 1165, 1164, 1163, 1162, 1161, 1160, 1159, 1158, 1157, 1156, 1155,
        1154, 1153, 1152, 1151, 1150, 1149, 1148, 1147, 1146, 1145, 1144, 1143,
        1142, 1141, 1140, 1139, 1138, 1137, 1136, 1135, 1134, 1133, 1132, 1131,
        1130, 1129, 1128, 1127, 1126, 1125, 1124, 1123, 1122, 1121, 1120, 1119,
        1118, 1117, 1116, 1115, 1114, 1113, 1112, 1111, 1110, 1109, 1108, 1107,
        1106, 1105, 1104, 1103, 1102, 1101, 1100, 1099, 1098, 1097, 1096, 1095,
        1094, 1093, 1092, 1091, 1090, 1089, 1088, 1087, 1086, 1085, 1084, 1083,
        1082, 1081, 1080, 1079, 1078, 1077, 1076, 1075, 1074, 1073, 1072, 1071,
        1070, 1069, 1068, 1067, 1066, 1065, 1064, 1063, 1062, 1061, 1060, 1059,
        1058, 1057, 1056, 1055, 1054, 1053, 1052, 1051, 1050, 1049, 1048, 1047,
        1046, 1045, 1044, 1043, 1042, 1041, 1040, 1039, 1038, 1037, 1036, 1035,
        1034, 1033, 1032, 1031, 1030, 1029, 1028, 1027, 1026, 1025, 1024, 1023,
        1022, 1021, 1020, 1019, 1018, 1017, 1016, 1015, 1014, 1013, 1012, 1011,
        1010, 1009, 1008, 1007, 1006, 1005, 1004, 1003, 1002, 1001, 1000, 999,
        998, 997, 996, 995, 994, 993, 992, 991, 990, 989, 988, 987, 986, 985,
        984, 983, 982, 981, 980, 979, 978, 977, 976, 975, 974, 973, 972, 971,
        970, 969, 968, 967, 966, 965, 964, 963, 962, 961, 960, 959, 958, 957,
        956, 955, 954, 953, 952, 951, 950, 949, 948, 947, 946, 945, 944, 943,
        942, 941, 940, 939, 938, 937, 936, 935, 934, 933, 932, 931, 930, 929,
        928, 927, 926, 925, 924, 923, 922, 921, 920, 919, 918, 917, 916, 915,
        914, 913, 912, 911, 910, 909, 908, 907, 906, 905, 904, 903, 902, 901,
        900, 899, 898, 897, 896, 895, 894, 893, 892, 891, 890, 889, 888, 887,
        886, 885, 884, 883, 882, 881, 880, 879, 878, 877, 876, 875, 874, 873,
        872, 871, 870, 869, 868, 867, 866, 865, 864, 863, 862, 861, 860, 859,
        858, 857, 856, 855, 854, 853, 852, 851, 850, 849, 848, 847, 846, 845,
        844, 843, 842, 841, 840, 839, 838, 837, 836, 835, 834, 833, 832, 831,
        830, 829, 828, 827, 826, 825, 824, 823, 822, 821, 820, 819, 818, 817,
        816, 815, 814, 813, 812, 811, 810, 809, 808, 807, 806, 805, 804, 803,
        802, 801, 800, 799, 798, 797, 796, 795, 794, 793, 792, 791, 790, 789,
        788, 787, 786, 785, 784, 783, 782, 781, 780, 779, 778, 777, 776, 775,
        774, 773, 772, 771, 770, 769, 768, 767, 766, 765, 764, 763, 762, 761,
        760, 759, 758, 757, 756, 755, 754, 753, 752, 751, 750, 749, 748, 747,
        746, 745, 744, 743, 742, 741, 740, 739, 738, 737, 736, 735, 734, 733,
        732, 731, 730, 729, 728, 727, 726, 725, 724, 723, 722, 721, 720, 719,
        718, 717, 716, 715, 714, 713, 712, 711, 710, 709, 708, 707, 706, 705,
        704, 703, 702, 701, 700, 699, 698, 697, 696, 695, 694, 693, 692, 691,
        690, 689, 688, 687, 686, 685, 684, 683, 682, 681, 680, 679, 678, 677,
        676, 675, 674, 673, 672, 671, 670, 669, 668, 667, 666, 665, 664, 663,
        662, 661, 660, 659, 658, 657, 656, 655, 654, 653, 652, 651, 650, 649,
        648, 647, 646, 645, 644, 643, 642, 641, 640, 639, 638, 637, 636, 635,
        634, 633, 632, 631, 630, 629, 628, 627, 626, 625, 624, 623, 622, 621,
        620, 619, 618, 617, 616, 615, 614, 613, 612, 611, 610, 609, 608, 607,
        606, 605, 604, 603, 602, 601, 600, 599, 598, 597, 596, 595, 594, 593,
        592, 591, 590, 589, 588, 587, 586, 585, 584, 583, 582, 581, 580, 579,
        578, 577, 576, 575, 574, 573, 572, 571, 570, 569, 568, 567, 566, 565,
        564, 563, 562, 561, 560, 559, 558, 557, 556, 555, 554, 553, 552, 551,
        550, 549, 548, 547, 546, 545, 544, 543, 542, 541, 540, 539, 538, 537,
        536, 535, 534, 533, 532, 531, 530, 529, 528, 527, 526, 525, 524, 523,
        522, 521, 520, 519, 518, 517, 516, 515, 514, 513, 512, 511, 510, 509,
        508, 507, 506, 505, 504, 503, 502, 501, 500, 499, 498, 497, 496, 495,
        494, 493, 492, 491, 490, 489, 488, 487, 486, 485, 484, 483, 482, 481,
        480, 479, 478, 477, 476, 475, 474, 473, 472, 471, 470, 469, 468, 467,
        466, 465, 464, 463, 462, 461, 460, 459, 458, 457, 456, 455, 454, 453,
        452, 451, 450, 449, 448, 447, 446, 445, 444, 443, 442, 441, 440, 439,
        438, 437, 436, 435, 434, 433, 432, 431, 430, 429, 428, 427, 426, 425,
        424, 423, 422, 421, 420, 419, 418, 417, 416, 415, 414, 413, 412, 411,
        410, 409, 408, 407, 406, 405, 404, 403, 402, 401, 400, 399, 398, 397,
        396, 395, 394, 393, 392, 391, 390, 389, 388, 387, 386, 385, 384, 383,
        382, 381, 380, 379, 378, 377, 376, 375, 374, 373, 372, 371, 370, 369,
        368, 367, 366, 365, 364, 363, 362, 361, 360, 359, 358, 357, 356, 355,
        354, 353, 352, 351, 350, 349, 348, 347, 346, 345, 344, 343, 342, 341,
        340, 339, 338, 337, 336, 335, 334, 333, 332, 331, 330, 329, 328, 327,
        326, 325, 324, 323, 322, 321, 320, 319, 318, 317, 316, 315, 314, 313,
        312, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 300, 299,
        298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285,
        284, 283, 282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271,
        270, 269, 268, 267, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257,
        256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243,
        242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229,
        228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215,
        214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201,
        200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187,
        186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173,
        172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159,
        158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145,
        144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131,
        130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117,
        116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103,
        102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86,
        85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68,
        67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
        49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,
        31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
        13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2 };

      double hcostab[1024];
      double hsintab[1024];
      double temp2_im;
      double temp2_re;
      double temp_im;
      double temp_re;
      double y_im;
      double y_re;
      int i;
      int iDelta2;
      int iheight;
      int ix;
      int j;
      int k;
      for (i = 0; i < 1024; i++) {
        ix = ((i + 1) << 1) - 2;
        hcostab[i] = dv[ix];
        hsintab[i] = dv1[ix];
      }

      ix = 0;
      for (i = 0; i < 2048; i++) {
        iDelta2 = bitrevIndex[i] - 1;
        y[iDelta2].re = x[ix];
        y[iDelta2].im = x[ix + 1];
        ix += 2;
      }

      for (i = 0; i <= 2046; i += 2) {
        temp_re = y[i + 1].re;
        temp_im = y[i + 1].im;
        y[i + 1].re = y[i].re - y[i + 1].re;
        y[i + 1].im = y[i].im - y[i + 1].im;
        y[i].re += temp_re;
        y[i].im += temp_im;
      }

      ix = 2;
      iDelta2 = 4;
      k = 512;
      iheight = 2045;
      while (k > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += iDelta2) {
          temp_re_tmp = i + ix;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = k; j < 1024; j += k) {
          int ihi;
          temp2_re = hcostab[j];
          temp2_im = hsintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + ix;
            temp_re = temp2_re * y[temp_re_tmp].re - temp2_im * y[temp_re_tmp].
              im;
            temp_im = temp2_re * y[temp_re_tmp].im + temp2_im * y[temp_re_tmp].
              re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += iDelta2;
          }

          istart++;
        }

        k /= 2;
        ix = iDelta2;
        iDelta2 += iDelta2;
        iheight -= ix;
      }

      temp_re = y[0].re;
      temp_im = y[0].im;
      y_im = -y[0].re + y[0].im;
      y_re = y[0].re;
      temp2_re = -y[0].im;
      y[0].re = 0.5 * ((y[0].re - (-y[0].im)) + (y_re - temp2_re));
      y[0].im = 0.5 * (y_im + (y_re + temp2_re));
      temp2_re = temp_re - temp_im;
      y[2048].re = 0.5 * (temp2_re + temp2_re);
      y[2048].im = 0.5 * ((temp_re + temp_im) + (-temp_re + -temp_im));
      for (i = 0; i < 1023; i++) {
        temp_re = y[i + 1].re;
        temp_im = y[i + 1].im;
        ix = iv[i + 1];
        temp2_re = y[ix - 1].re;
        temp2_im = y[ix - 1].im;
        y_im = y[i + 1].re * reconVar1[i + 1].im + y[i + 1].im * reconVar1[i + 1]
          .re;
        y[i + 1].re = 0.5 * ((y[i + 1].re * reconVar1[i + 1].re - y[i + 1].im *
                              reconVar1[i + 1].im) + (temp2_re * reconVar2[i + 1]
          .re - -temp2_im * reconVar2[i + 1].im));
        y[i + 1].im = 0.5 * (y_im + (temp2_re * reconVar2[i + 1].im + -temp2_im *
          reconVar2[i + 1].re));
        y[i + 2049].re = 0.5 * ((temp_re * reconVar2[i + 1].re - temp_im *
          reconVar2[i + 1].im) + (temp2_re * reconVar1[i + 1].re - -temp2_im *
          reconVar1[i + 1].im));
        y[i + 2049].im = 0.5 * ((temp_re * reconVar2[i + 1].im + temp_im *
          reconVar2[i + 1].re) + (temp2_re * reconVar1[i + 1].im + -temp2_im *
          reconVar1[i + 1].re));
        y[ix - 1].re = 0.5 * ((temp2_re * reconVar1[ix - 1].re - temp2_im *
          reconVar1[ix - 1].im) + (temp_re * reconVar2[ix - 1].re - -temp_im *
          reconVar2[ix - 1].im));
        y[ix - 1].im = 0.5 * ((temp2_re * reconVar1[ix - 1].im + temp2_im *
          reconVar1[ix - 1].re) + (temp_re * reconVar2[ix - 1].im + -temp_im *
          reconVar2[ix - 1].re));
        y[ix + 2047].re = 0.5 * ((temp2_re * reconVar2[ix - 1].re - temp2_im *
          reconVar2[ix - 1].im) + (temp_re * reconVar1[ix - 1].re - -temp_im *
          reconVar1[ix - 1].im));
        y[ix + 2047].im = 0.5 * ((temp2_re * reconVar2[ix - 1].im + temp2_im *
          reconVar2[ix - 1].re) + (temp_re * reconVar1[ix - 1].im + -temp_im *
          reconVar1[ix - 1].re));
      }

      temp_re = y[1024].re;
      temp_im = y[1024].im;
      temp2_re = y[1024].re * 0.0;
      temp2_im = y[1024].im * 0.0;
      y_re = y[1024].re;
      y_im = -y[1024].im;
      y[1024].re = 0.5 * ((temp2_re - temp2_im) + (y_re * 2.0 - y_im * 0.0));
      y[1024].im = 0.5 * ((temp2_re + temp2_im) + (y_re * 0.0 + y_im * 2.0));
      temp2_re = -temp_im * 0.0;
      y[3072].re = 0.5 * ((temp_re * 2.0 - temp_im * 0.0) + (temp_re * 0.0 -
        temp2_re));
      y[3072].im = 0.5 * ((temp_re * 0.0 + temp_im * 2.0) + (temp_re * 0.0 +
        temp2_re));
    }

    void FFTImplementationCallback::doHalfLengthRadix2(const double x_data[],
      const int x_size[1], ::coder::array<creal_T, 1U> &y, int unsigned_nRows,
      const ::coder::array<double, 2U> &costab, const ::coder::array<double, 2U>
      &sintab)
    {
      array<creal_T, 1U> reconVar1;
      array<creal_T, 1U> reconVar2;
      array<double, 2U> hcostab;
      array<double, 2U> hsintab;
      array<int, 2U> wrapIndex;
      array<int, 1U> bitrevIndex;
      double temp_im;
      double temp_re;
      double z;
      int hszCostab;
      int i;
      int istart;
      int ix;
      int j;
      int k;
      int nRows;
      int nRowsD2;
      boolean_T nxeven;
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
        temp_im = sintab[i];
        temp_re = costab[i];
        reconVar1[i].re = temp_im + 1.0;
        reconVar1[i].im = -temp_re;
        reconVar2[i].re = 1.0 - temp_im;
        reconVar2[i].im = temp_re;
        if (i + 1 != 1) {
          wrapIndex[i] = (nRows - i) + 1;
        } else {
          wrapIndex[0] = 1;
        }
      }

      z = static_cast<double>(unsigned_nRows) / 2.0;
      hszCostab = y.size(0);
      if (hszCostab >= nRows) {
        hszCostab = nRows;
      }

      FFTImplementationCallback::get_bitrevIndex((hszCostab - 1), (static_cast<
        int>(z)), (bitrevIndex));
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

      temp_im = static_cast<double>(hszCostab) / 2.0;
      hszCostab = static_cast<int>(temp_im);
      for (i = 0; i < hszCostab; i++) {
        y[bitrevIndex[i] - 1].re = x_data[ix];
        y[bitrevIndex[i] - 1].im = x_data[ix + 1];
        ix += 2;
      }

      if (!nxeven) {
        hszCostab = bitrevIndex[static_cast<int>(temp_im)] - 1;
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
          double twid_im;
          double twid_re;
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
        (wrapIndex), (static_cast<int>(z)));
    }

    void FFTImplementationCallback::dobluesteinfft(const double x_data[], const
      int x_size[1], int n2blue, int nfft, const ::coder::array<double, 2U>
      &costab, const ::coder::array<double, 2U> &sintab, const ::coder::array<
      double, 2U> &sintabinv, ::coder::array<creal_T, 1U> &y)
    {
      array<creal_T, 1U> fv;
      array<creal_T, 1U> fy;
      array<creal_T, 1U> wwc;
      double nt_re;
      int idx;
      int k;
      int nInt2;
      int nInt2m1;
      int rt;
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
          double nt_im;
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }

          nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
            double>(nRows);
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
          double nt_im;
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }

          nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
            double>(nfft);
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
          (sintab), (fy));
        FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (n2blue), (costab),
          (sintab), (fv));
        nInt2m1 = fy.size(0);
        for (rt = 0; rt < nInt2m1; rt++) {
          nt_re = fy[rt].re * fv[rt].im + fy[rt].im * fv[rt].re;
          fy[rt].re = fy[rt].re * fv[rt].re - fy[rt].im * fv[rt].im;
          fy[rt].im = nt_re;
        }

        FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (n2blue), (costab),
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
          y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].
            im;
          y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].
            re;
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

    void FFTImplementationCallback::r2br_r2dit_trig(const ::coder::array<double,
      2U> &x, const double costab_data[], const double sintab_data[], ::coder::
      array<creal_T, 2U> &y)
    {
      array<cuint8_T, 1U> b_y;
      creal_T tmp_data[2048];
      int tmp_size[1];
      int b_loop_ub;
      int i1;
      int loop_ub;
      int nrows;
      int xoff;
      nrows = x.size(0);
      y.set_size(2048, x.size(1));
      if (2048 > x.size(0)) {
        y.set_size(2048, x.size(1));
        loop_ub = 2048 * x.size(1);
        for (int i = 0; i < loop_ub; i++) {
          y[i].re = 0.0;
          y[i].im = 0.0;
        }
      }

      loop_ub = x.size(1) - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(b_y,xoff,i1,tmp_size,b_loop_ub,tmp_data)

      for (int chan = 0; chan <= loop_ub; chan++) {
        xoff = chan * nrows;
        b_y.set_size(2048);
        if (2048 > x.size(0)) {
          b_y.set_size(2048);
          for (i1 = 0; i1 < 2048; i1++) {
            b_y[i1].re = 0U;
            b_y[i1].im = 0U;
          }
        }

        tmp_size[0] = b_y.size(0);
        b_loop_ub = b_y.size(0);
        for (i1 = 0; i1 < b_loop_ub; i1++) {
          tmp_data[i1].re = b_y[i1].re;
          tmp_data[i1].im = b_y[i1].im;
        }

        FFTImplementationCallback::doHalfLengthRadix2((x), (xoff), (tmp_data),
          (tmp_size), (costab_data), (sintab_data));
        for (i1 = 0; i1 < 2048; i1++) {
          y[i1 + 2048 * chan] = tmp_data[i1];
        }
      }
    }

    void FFTImplementationCallback::r2br_r2dit_trig_impl(const ::coder::array<
      creal_T, 1U> &x, int unsigned_nRows, const ::coder::array<double, 2U>
      &costab, const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T,
      1U> &y)
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iDelta2;
      int iheight;
      int ix;
      int iy;
      int ju;
      int k;
      int nRowsD2;
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
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
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
  }
}

// End of code generation (FFTImplementationCallback.cpp)
