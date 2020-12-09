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
#include <string.h>

// Function Definitions
namespace coder
{
  void fft(const ::coder::array<double, 2U> &x, ::coder::array<creal_T, 2U> &y)
  {
    array<double, 2U> costab;
    array<double, 2U> costab1q;
    array<double, 2U> sintab;
    if ((x.size(0) == 0) || (x.size(1) == 0)) {
      int n;
      y.set_size(2048, x.size(1));
      n = x.size(1) << 11;
      for (int i = 0; i < n; i++) {
        y[i].re = 0.0;
        y[i].im = 0.0;
      }
    } else {
      int i;
      int k;
      int n;
      int n2;
      costab1q.set_size(1, 513);
      costab1q[0] = 1.0;
      for (k = 0; k < 256; k++) {
        costab1q[k + 1] = std::cos(0.0030679615757712823 * (static_cast<double>
          (k) + 1.0));
      }

      for (k = 0; k < 255; k++) {
        costab1q[k + 257] = std::sin(0.0030679615757712823 * (512.0 - (
          static_cast<double>(k) + 257.0)));
      }

      costab1q[512] = 0.0;
      n = costab1q.size(1) - 1;
      n2 = (costab1q.size(1) - 1) << 1;
      costab.set_size(1, (n2 + 1));
      sintab.set_size(1, (n2 + 1));
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab[k + 1] = costab1q[k + 1];
        sintab[k + 1] = -costab1q[(n - k) - 1];
      }

      i = costab1q.size(1);
      for (k = i; k <= n2; k++) {
        costab[k] = -costab1q[n2 - k];
        sintab[k] = -costab1q[k - n];
      }

      internal::FFTImplementationCallback::r2br_r2dit_trig((x), ((double *)
        costab.data()), ((double *)sintab.data()), (y));
    }
  }

  void fft(const double x_data[], const int x_size[1], double varargin_1, ::
           coder::array<creal_T, 1U> &y)
  {
    array<double, 2U> costab;
    array<double, 2U> costab1q;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    double twid_im;
    double twid_re;
    int i;
    int iDelta2;
    int ihi;
    int ix;
    int j;
    int ju;
    int k;
    int nd2;
    if ((x_size[0] == 0) || (0 == static_cast<int>(varargin_1))) {
      y.set_size((static_cast<int>(varargin_1)));
      nd2 = static_cast<int>(varargin_1);
      for (ix = 0; ix < nd2; ix++) {
        y[ix].re = 0.0;
        y[ix].im = 0.0;
      }
    } else {
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(varargin_1) > 0) && ((static_cast<int>
        (varargin_1) & (static_cast<int>(varargin_1) - 1)) == 0));
      internal::FFTImplementationCallback::get_algo_sizes((static_cast<int>
        (varargin_1)), (useRadix2), (&iDelta2), (&nd2));
      twid_re = 6.2831853071795862 / static_cast<double>(nd2);
      ihi = nd2 / 2 / 2;
      costab1q.set_size(1, (ihi + 1));
      costab1q[0] = 1.0;
      nd2 = ihi / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(twid_re * (static_cast<double>(k) + 1.0));
      }

      ix = nd2 + 2;
      nd2 = ihi - 1;
      for (k = ix; k <= nd2; k++) {
        costab1q[k] = std::sin(twid_re * static_cast<double>(ihi - k));
      }

      costab1q[ihi] = 0.0;
      if (!useRadix2) {
        ihi = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (nd2 + 1));
        for (k = 0; k < ihi; k++) {
          sintabinv[k + 1] = costab1q[(ihi - k) - 1];
        }

        ix = costab1q.size(1);
        for (k = ix; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - ihi];
        }

        for (k = 0; k < ihi; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(ihi - k) - 1];
        }

        ix = costab1q.size(1);
        for (k = ix; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - ihi];
        }
      } else {
        ihi = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < ihi; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(ihi - k) - 1];
        }

        ix = costab1q.size(1);
        for (k = ix; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - ihi];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > x_size[0]) {
          nd2 = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (ix = 0; ix < nd2; ix++) {
            y[ix].re = 0.0;
            y[ix].im = 0.0;
          }
        }

        if (static_cast<int>(varargin_1) != 1) {
          internal::FFTImplementationCallback::doHalfLengthRadix2((x_data),
            (x_size), (y), (static_cast<int>(varargin_1)), (costab), (sintab));
        } else {
          double temp_im;
          double temp_re;
          int nRowsD2;
          nd2 = x_size[0];
          j = static_cast<int>(varargin_1);
          if (nd2 < j) {
            j = nd2;
          }

          iDelta2 = static_cast<int>(varargin_1) - 2;
          nRowsD2 = static_cast<int>(varargin_1) / 2;
          k = nRowsD2 / 2;
          ix = 0;
          nd2 = 0;
          ju = 0;
          for (i = 0; i <= j - 2; i++) {
            y[nd2].re = x_data[ix];
            y[nd2].im = 0.0;
            ihi = static_cast<int>(varargin_1);
            useRadix2 = true;
            while (useRadix2) {
              ihi >>= 1;
              ju ^= ihi;
              useRadix2 = ((ju & ihi) == 0);
            }

            nd2 = ju;
            ix++;
          }

          y[nd2].re = x_data[ix];
          y[nd2].im = 0.0;
          if (static_cast<int>(varargin_1) > 1) {
            for (i = 0; i <= iDelta2; i += 2) {
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

          nd2 = 2;
          iDelta2 = 4;
          ix = ((k - 1) << 2) + 1;
          while (k > 0) {
            int temp_re_tmp;
            for (i = 0; i < ix; i += iDelta2) {
              temp_re_tmp = i + nd2;
              temp_re = y[temp_re_tmp].re;
              temp_im = y[temp_re_tmp].im;
              y[temp_re_tmp].re = y[i].re - temp_re;
              y[temp_re_tmp].im = y[i].im - temp_im;
              y[i].re = y[i].re + temp_re;
              y[i].im = y[i].im + temp_im;
            }

            ju = 1;
            for (j = k; j < nRowsD2; j += k) {
              twid_re = costab[j];
              twid_im = sintab[j];
              i = ju;
              ihi = ju + ix;
              while (i < ihi) {
                temp_re_tmp = i + nd2;
                temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp]
                  .im;
                temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp]
                  .re;
                y[temp_re_tmp].re = y[i].re - temp_re;
                y[temp_re_tmp].im = y[i].im - temp_im;
                y[i].re = y[i].re + temp_re;
                y[i].im = y[i].im + temp_im;
                i += iDelta2;
              }

              ju++;
            }

            k /= 2;
            nd2 = iDelta2;
            iDelta2 += iDelta2;
            ix -= nd2;
          }
        }
      } else {
        internal::FFTImplementationCallback::dobluesteinfft((x_data), (x_size),
          (iDelta2), (static_cast<int>(varargin_1)), (costab), (sintab),
          (sintabinv), (y));
      }
    }
  }
}

// End of code generation (fft.cpp)
