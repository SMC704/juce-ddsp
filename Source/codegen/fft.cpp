//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  fft.cpp
//
//  Code generation for function 'fft'
//


// Include files
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
namespace coder
{
  void fft(const double x[65], double varargin_1, ::coder::array<creal_T, 1U> &y)
  {
    array<creal_T, 1U> fv;
    array<creal_T, 1U> fy;
    array<creal_T, 1U> wwc;
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    double twid_im;
    double twid_re;
    int N2blue;
    int idx;
    int k;
    int minNrowsNx;
    int nInt2;
    int nInt2m1;
    int nfft;
    int rt;
    nfft = static_cast<int>(varargin_1);
    if (0 == static_cast<int>(varargin_1)) {
      y.set_size((static_cast<int>(varargin_1)));
      minNrowsNx = static_cast<int>(varargin_1);
      for (int ihi = 0; ihi < minNrowsNx; ihi++) {
        y[ihi].re = 0.0;
        y[ihi].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(varargin_1) > 0) && ((static_cast<int>
        (varargin_1) & (static_cast<int>(varargin_1) - 1)) == 0));
      internal::FFTImplementationCallback::get_algo_sizes((static_cast<int>
        (varargin_1)), (useRadix2), (&N2blue), (&minNrowsNx));
      internal::FFTImplementationCallback::generate_twiddle_tables((minNrowsNx),
        (useRadix2), (costab), (sintab), (sintabinv));
      if (useRadix2) {
        int ihi;
        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > 65) {
          minNrowsNx = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (ihi = 0; ihi < minNrowsNx; ihi++) {
            y[ihi].re = 0.0;
            y[ihi].im = 0.0;
          }
        }

        if (static_cast<int>(varargin_1) != 1) {
          internal::FFTImplementationCallback::doHalfLengthRadix2((x), (y), (
            static_cast<int>(varargin_1)), (costab), (sintab));
        } else {
          double nt_im;
          double nt_re;
          int b_y;
          if (65 < static_cast<int>(varargin_1)) {
            b_y = 63;
          } else {
            b_y = static_cast<int>(varargin_1) - 2;
          }

          nInt2m1 = static_cast<int>(varargin_1) - 2;
          nfft = static_cast<int>(varargin_1) / 2;
          k = nfft / 2;
          rt = 0;
          minNrowsNx = 0;
          nInt2 = 0;
          for (N2blue = 0; N2blue <= b_y; N2blue++) {
            y[minNrowsNx].re = x[rt];
            y[minNrowsNx].im = 0.0;
            minNrowsNx = static_cast<int>(varargin_1);
            useRadix2 = true;
            while (useRadix2) {
              minNrowsNx >>= 1;
              nInt2 ^= minNrowsNx;
              useRadix2 = ((nInt2 & minNrowsNx) == 0);
            }

            minNrowsNx = nInt2;
            rt++;
          }

          y[minNrowsNx].re = x[rt];
          y[minNrowsNx].im = 0.0;
          if (static_cast<int>(varargin_1) > 1) {
            for (N2blue = 0; N2blue <= nInt2m1; N2blue += 2) {
              nt_re = y[N2blue + 1].re;
              nt_im = y[N2blue + 1].im;
              twid_im = y[N2blue].re;
              twid_re = y[N2blue].im;
              y[N2blue + 1].re = y[N2blue].re - y[N2blue + 1].re;
              y[N2blue + 1].im = y[N2blue].im - y[N2blue + 1].im;
              twid_im += nt_re;
              twid_re += nt_im;
              y[N2blue].re = twid_im;
              y[N2blue].im = twid_re;
            }
          }

          minNrowsNx = 2;
          nInt2m1 = 4;
          rt = ((k - 1) << 2) + 1;
          while (k > 0) {
            for (N2blue = 0; N2blue < rt; N2blue += nInt2m1) {
              b_y = N2blue + minNrowsNx;
              nt_re = y[b_y].re;
              nt_im = y[b_y].im;
              y[b_y].re = y[N2blue].re - nt_re;
              y[b_y].im = y[N2blue].im - nt_im;
              y[N2blue].re = y[N2blue].re + nt_re;
              y[N2blue].im = y[N2blue].im + nt_im;
            }

            nInt2 = 1;
            for (idx = k; idx < nfft; idx += k) {
              twid_re = costab[idx];
              twid_im = sintab[idx];
              N2blue = nInt2;
              ihi = nInt2 + rt;
              while (N2blue < ihi) {
                b_y = N2blue + minNrowsNx;
                nt_re = twid_re * y[b_y].re - twid_im * y[b_y].im;
                nt_im = twid_re * y[b_y].im + twid_im * y[b_y].re;
                y[b_y].re = y[N2blue].re - nt_re;
                y[b_y].im = y[N2blue].im - nt_im;
                y[N2blue].re = y[N2blue].re + nt_re;
                y[N2blue].im = y[N2blue].im + nt_im;
                N2blue += nInt2m1;
              }

              nInt2++;
            }

            k /= 2;
            minNrowsNx = nInt2m1;
            nInt2m1 += nInt2m1;
            rt -= minNrowsNx;
          }
        }
      } else {
        int b_y;
        int ihi;
        if ((static_cast<int>(varargin_1) != 1) && ((static_cast<int>(varargin_1)
              & 1) == 0)) {
          minNrowsNx = static_cast<int>(varargin_1) / 2;
          nInt2m1 = (minNrowsNx + minNrowsNx) - 1;
          wwc.set_size(nInt2m1);
          idx = minNrowsNx;
          rt = 0;
          wwc[minNrowsNx - 1].re = 1.0;
          wwc[minNrowsNx - 1].im = 0.0;
          nInt2 = minNrowsNx << 1;
          for (k = 0; k <= minNrowsNx - 2; k++) {
            double nt_im;
            double nt_re;
            b_y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= b_y) {
              rt += b_y - nInt2;
            } else {
              rt += b_y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(minNrowsNx);
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
          ihi = nInt2m1 - 1;
          for (k = ihi; k >= minNrowsNx; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        } else {
          nInt2m1 = (static_cast<int>(varargin_1) + static_cast<int>(varargin_1))
            - 1;
          wwc.set_size(nInt2m1);
          idx = static_cast<int>(varargin_1);
          rt = 0;
          wwc[static_cast<int>(varargin_1) - 1].re = 1.0;
          wwc[static_cast<int>(varargin_1) - 1].im = 0.0;
          nInt2 = static_cast<int>(varargin_1) << 1;
          ihi = static_cast<int>(varargin_1);
          for (k = 0; k <= ihi - 2; k++) {
            double nt_im;
            double nt_re;
            b_y = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= b_y) {
              rt += b_y - nInt2;
            } else {
              rt += b_y;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(static_cast<int>(varargin_1));
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
          ihi = nInt2m1 - 1;
          for (k = ihi; k >= nfft; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        }

        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > 65) {
          minNrowsNx = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (ihi = 0; ihi < minNrowsNx; ihi++) {
            y[ihi].re = 0.0;
            y[ihi].im = 0.0;
          }
        }

        if ((N2blue != 1) && ((static_cast<int>(varargin_1) & 1) == 0)) {
          internal::FFTImplementationCallback::doHalfLengthBluestein((x), (y), (
            static_cast<int>(varargin_1)), (N2blue), (wwc), (costab), (sintab),
            (costab), (sintabinv));
        } else {
          if (static_cast<int>(varargin_1) < 65) {
            minNrowsNx = static_cast<int>(varargin_1) - 1;
          } else {
            minNrowsNx = 64;
          }

          nInt2m1 = 0;
          for (k = 0; k <= minNrowsNx; k++) {
            b_y = (static_cast<int>(varargin_1) + k) - 1;
            y[k].re = wwc[b_y].re * x[nInt2m1];
            y[k].im = wwc[b_y].im * -x[nInt2m1];
            nInt2m1++;
          }

          ihi = minNrowsNx + 2;
          for (k = ihi; k <= nfft; k++) {
            y[k - 1].re = 0.0;
            y[k - 1].im = 0.0;
          }

          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((y), (N2blue),
            (costab), (sintab), (fy));
          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
            (N2blue), (costab), (sintab), (fv));
          minNrowsNx = fy.size(0);
          for (ihi = 0; ihi < minNrowsNx; ihi++) {
            twid_re = fy[ihi].re * fv[ihi].im + fy[ihi].im * fv[ihi].re;
            fy[ihi].re = fy[ihi].re * fv[ihi].re - fy[ihi].im * fv[ihi].im;
            fy[ihi].im = twid_re;
          }

          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((fy),
            (N2blue), (costab), (sintabinv), (fv));
          if (fv.size(0) > 1) {
            twid_re = 1.0 / static_cast<double>(fv.size(0));
            minNrowsNx = fv.size(0);
            for (ihi = 0; ihi < minNrowsNx; ihi++) {
              fv[ihi].re = twid_re * fv[ihi].re;
              fv[ihi].im = twid_re * fv[ihi].im;
            }
          }

          idx = 0;
          ihi = static_cast<int>(varargin_1);
          minNrowsNx = wwc.size(0);
          for (k = ihi; k <= minNrowsNx; k++) {
            y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1]
              .im;
            y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1]
              .re;
            idx++;
          }
        }
      }
    }
  }

  void fft(const double x_data[], const int x_size[1], double varargin_1, ::
           coder::array<creal_T, 1U> &y)
  {
    array<creal_T, 1U> fv;
    array<creal_T, 1U> fy;
    array<creal_T, 1U> wwc;
    array<double, 2U> costab;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    double twid_im;
    double twid_re;
    int N2blue;
    int j;
    int k;
    int nInt2;
    int nInt2m1;
    int nfft;
    int rt;
    int xidx;
    nfft = static_cast<int>(varargin_1);
    if ((x_size[0] == 0) || (0 == static_cast<int>(varargin_1))) {
      y.set_size((static_cast<int>(varargin_1)));
      xidx = static_cast<int>(varargin_1);
      for (int nt_re_tmp = 0; nt_re_tmp < xidx; nt_re_tmp++) {
        y[nt_re_tmp].re = 0.0;
        y[nt_re_tmp].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(varargin_1) > 0) && ((static_cast<int>
        (varargin_1) & (static_cast<int>(varargin_1) - 1)) == 0));
      internal::FFTImplementationCallback::get_algo_sizes((static_cast<int>
        (varargin_1)), (useRadix2), (&N2blue), (&xidx));
      internal::FFTImplementationCallback::generate_twiddle_tables((xidx),
        (useRadix2), (costab), (sintab), (sintabinv));
      if (useRadix2) {
        int nt_re_tmp;
        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > x_size[0]) {
          xidx = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (nt_re_tmp = 0; nt_re_tmp < xidx; nt_re_tmp++) {
            y[nt_re_tmp].re = 0.0;
            y[nt_re_tmp].im = 0.0;
          }
        }

        if (static_cast<int>(varargin_1) != 1) {
          internal::FFTImplementationCallback::doHalfLengthRadix2((x_data),
            (x_size), (y), (static_cast<int>(varargin_1)), (costab), (sintab));
        } else {
          double nt_im;
          double nt_re;
          xidx = x_size[0];
          j = static_cast<int>(varargin_1);
          if (xidx < j) {
            j = xidx;
          }

          nInt2m1 = static_cast<int>(varargin_1) - 2;
          nfft = static_cast<int>(varargin_1) / 2;
          k = nfft / 2;
          rt = 0;
          xidx = 0;
          nInt2 = 0;
          for (N2blue = 0; N2blue <= j - 2; N2blue++) {
            y[xidx].re = x_data[rt];
            y[xidx].im = 0.0;
            xidx = static_cast<int>(varargin_1);
            useRadix2 = true;
            while (useRadix2) {
              xidx >>= 1;
              nInt2 ^= xidx;
              useRadix2 = ((nInt2 & xidx) == 0);
            }

            xidx = nInt2;
            rt++;
          }

          y[xidx].re = x_data[rt];
          y[xidx].im = 0.0;
          if (static_cast<int>(varargin_1) > 1) {
            for (N2blue = 0; N2blue <= nInt2m1; N2blue += 2) {
              nt_re = y[N2blue + 1].re;
              nt_im = y[N2blue + 1].im;
              twid_im = y[N2blue].re;
              twid_re = y[N2blue].im;
              y[N2blue + 1].re = y[N2blue].re - y[N2blue + 1].re;
              y[N2blue + 1].im = y[N2blue].im - y[N2blue + 1].im;
              twid_im += nt_re;
              twid_re += nt_im;
              y[N2blue].re = twid_im;
              y[N2blue].im = twid_re;
            }
          }

          xidx = 2;
          nInt2m1 = 4;
          rt = ((k - 1) << 2) + 1;
          while (k > 0) {
            for (N2blue = 0; N2blue < rt; N2blue += nInt2m1) {
              nt_re_tmp = N2blue + xidx;
              nt_re = y[nt_re_tmp].re;
              nt_im = y[nt_re_tmp].im;
              y[nt_re_tmp].re = y[N2blue].re - nt_re;
              y[nt_re_tmp].im = y[N2blue].im - nt_im;
              y[N2blue].re = y[N2blue].re + nt_re;
              y[N2blue].im = y[N2blue].im + nt_im;
            }

            nInt2 = 1;
            for (j = k; j < nfft; j += k) {
              int idx;
              twid_re = costab[j];
              twid_im = sintab[j];
              N2blue = nInt2;
              idx = nInt2 + rt;
              while (N2blue < idx) {
                nt_re_tmp = N2blue + xidx;
                nt_re = twid_re * y[nt_re_tmp].re - twid_im * y[nt_re_tmp].im;
                nt_im = twid_re * y[nt_re_tmp].im + twid_im * y[nt_re_tmp].re;
                y[nt_re_tmp].re = y[N2blue].re - nt_re;
                y[nt_re_tmp].im = y[N2blue].im - nt_im;
                y[N2blue].re = y[N2blue].re + nt_re;
                y[N2blue].im = y[N2blue].im + nt_im;
                N2blue += nInt2m1;
              }

              nInt2++;
            }

            k /= 2;
            xidx = nInt2m1;
            nInt2m1 += nInt2m1;
            rt -= xidx;
          }
        }
      } else {
        int idx;
        int nt_re_tmp;
        if ((static_cast<int>(varargin_1) != 1) && ((static_cast<int>(varargin_1)
              & 1) == 0)) {
          xidx = static_cast<int>(varargin_1) / 2;
          nInt2m1 = (xidx + xidx) - 1;
          wwc.set_size(nInt2m1);
          idx = xidx;
          rt = 0;
          wwc[xidx - 1].re = 1.0;
          wwc[xidx - 1].im = 0.0;
          nInt2 = xidx << 1;
          for (k = 0; k <= xidx - 2; k++) {
            double nt_im;
            double nt_re;
            j = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= j) {
              rt += j - nInt2;
            } else {
              rt += j;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(xidx);
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
          nt_re_tmp = nInt2m1 - 1;
          for (k = nt_re_tmp; k >= xidx; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        } else {
          nInt2m1 = (static_cast<int>(varargin_1) + static_cast<int>(varargin_1))
            - 1;
          wwc.set_size(nInt2m1);
          idx = static_cast<int>(varargin_1);
          rt = 0;
          wwc[static_cast<int>(varargin_1) - 1].re = 1.0;
          wwc[static_cast<int>(varargin_1) - 1].im = 0.0;
          nInt2 = static_cast<int>(varargin_1) << 1;
          nt_re_tmp = static_cast<int>(varargin_1);
          for (k = 0; k <= nt_re_tmp - 2; k++) {
            double nt_im;
            double nt_re;
            j = ((k + 1) << 1) - 1;
            if (nInt2 - rt <= j) {
              rt += j - nInt2;
            } else {
              rt += j;
            }

            nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
              double>(static_cast<int>(varargin_1));
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
          nt_re_tmp = nInt2m1 - 1;
          for (k = nt_re_tmp; k >= nfft; k--) {
            wwc[k] = wwc[idx];
            idx++;
          }
        }

        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > x_size[0]) {
          xidx = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (nt_re_tmp = 0; nt_re_tmp < xidx; nt_re_tmp++) {
            y[nt_re_tmp].re = 0.0;
            y[nt_re_tmp].im = 0.0;
          }
        }

        if ((N2blue != 1) && ((static_cast<int>(varargin_1) & 1) == 0)) {
          internal::FFTImplementationCallback::doHalfLengthBluestein((x_data),
            (x_size), (y), (x_size[0]), (static_cast<int>(varargin_1)), (N2blue),
            (wwc), (costab), (sintab), (costab), (sintabinv));
        } else {
          xidx = static_cast<int>(varargin_1);
          nInt2m1 = x_size[0];
          if (xidx < nInt2m1) {
            nInt2m1 = xidx;
          }

          xidx = 0;
          for (k = 0; k < nInt2m1; k++) {
            nt_re_tmp = (static_cast<int>(varargin_1) + k) - 1;
            y[k].re = wwc[nt_re_tmp].re * x_data[xidx];
            y[k].im = wwc[nt_re_tmp].im * -x_data[xidx];
            xidx++;
          }

          nt_re_tmp = nInt2m1 + 1;
          for (k = nt_re_tmp; k <= nfft; k++) {
            y[k - 1].re = 0.0;
            y[k - 1].im = 0.0;
          }

          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((y), (N2blue),
            (costab), (sintab), (fy));
          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
            (N2blue), (costab), (sintab), (fv));
          xidx = fy.size(0);
          for (nt_re_tmp = 0; nt_re_tmp < xidx; nt_re_tmp++) {
            twid_re = fy[nt_re_tmp].re * fv[nt_re_tmp].im + fy[nt_re_tmp].im *
              fv[nt_re_tmp].re;
            fy[nt_re_tmp].re = fy[nt_re_tmp].re * fv[nt_re_tmp].re -
              fy[nt_re_tmp].im * fv[nt_re_tmp].im;
            fy[nt_re_tmp].im = twid_re;
          }

          internal::FFTImplementationCallback::r2br_r2dit_trig_impl((fy),
            (N2blue), (costab), (sintabinv), (fv));
          if (fv.size(0) > 1) {
            twid_re = 1.0 / static_cast<double>(fv.size(0));
            xidx = fv.size(0);
            for (nt_re_tmp = 0; nt_re_tmp < xidx; nt_re_tmp++) {
              fv[nt_re_tmp].re = twid_re * fv[nt_re_tmp].re;
              fv[nt_re_tmp].im = twid_re * fv[nt_re_tmp].im;
            }
          }

          idx = 0;
          nt_re_tmp = static_cast<int>(varargin_1);
          xidx = wwc.size(0);
          for (k = nt_re_tmp; k <= xidx; k++) {
            y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1]
              .im;
            y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1]
              .re;
            idx++;
          }
        }
      }
    }
  }
}

// End of code generation (fft.cpp)
