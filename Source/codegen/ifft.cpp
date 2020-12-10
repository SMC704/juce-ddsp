//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ifft.cpp
//
//  Code generation for function 'ifft'
//


// Include files
#include "ifft.h"
#include "DDSPSynth_data.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder
{
  void ifft(const ::coder::array<creal_T, 1U> &x, double varargin_1, ::coder::
            array<creal_T, 1U> &y)
  {
    array<creal_T, 1U> fv;
    array<creal_T, 1U> fy;
    array<creal_T, 1U> wwc;
    array<double, 2U> costab;
    array<double, 2U> costab1q;
    array<double, 2U> sintab;
    array<double, 2U> sintabinv;
    int N2blue;
    int nd2;
    int nfft;
    int rt;
    nfft = static_cast<int>(varargin_1);
    if ((x.size(0) == 0) || (0 == static_cast<int>(varargin_1))) {
      y.set_size((static_cast<int>(varargin_1)));
      nd2 = static_cast<int>(varargin_1);
      for (int i = 0; i < nd2; i++) {
        y[i].re = 0.0;
        y[i].im = 0.0;
      }
    } else {
      double nt_re;
      int i;
      int k;
      int nInt2;
      boolean_T useRadix2;
      useRadix2 = ((static_cast<int>(varargin_1) > 0) && ((static_cast<int>
        (varargin_1) & (static_cast<int>(varargin_1) - 1)) == 0));
      internal::FFTImplementationCallback::get_algo_sizes((static_cast<int>
        (varargin_1)), (useRadix2), (&N2blue), (&nd2));
      nt_re = 6.2831853071795862 / static_cast<double>(nd2);
      nInt2 = nd2 / 2 / 2;
      costab1q.set_size(1, (nInt2 + 1));
      costab1q[0] = 1.0;
      nd2 = nInt2 / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(nt_re * (static_cast<double>(k) + 1.0));
      }

      i = nd2 + 2;
      nd2 = nInt2 - 1;
      for (k = i; k <= nd2; k++) {
        costab1q[k] = std::sin(nt_re * static_cast<double>(nInt2 - k));
      }

      costab1q[nInt2] = 0.0;
      if (!useRadix2) {
        nInt2 = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (nd2 + 1));
        for (k = 0; k < nInt2; k++) {
          sintabinv[k + 1] = costab1q[(nInt2 - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          sintabinv[k] = costab1q[k - nInt2];
        }

        for (k = 0; k < nInt2; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(nInt2 - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = -costab1q[k - nInt2];
        }
      } else {
        nInt2 = costab1q.size(1) - 1;
        nd2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (nd2 + 1));
        sintab.set_size(1, (nd2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < nInt2; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = costab1q[(nInt2 - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= nd2; k++) {
          costab[k] = -costab1q[nd2 - k];
          sintab[k] = costab1q[k - nInt2];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((x), (
          static_cast<int>(varargin_1)), (costab), (sintab), (y));
        if (y.size(0) > 1) {
          nt_re = 1.0 / static_cast<double>(y.size(0));
          nd2 = y.size(0);
          for (i = 0; i < nd2; i++) {
            y[i].re = nt_re * y[i].re;
            y[i].im = nt_re * y[i].im;
          }
        }
      } else {
        double nt_im;
        int idx;
        nd2 = (static_cast<int>(varargin_1) + static_cast<int>(varargin_1)) - 1;
        wwc.set_size(nd2);
        idx = static_cast<int>(varargin_1);
        rt = 0;
        wwc[static_cast<int>(varargin_1) - 1].re = 1.0;
        wwc[static_cast<int>(varargin_1) - 1].im = 0.0;
        nInt2 = static_cast<int>(varargin_1) << 1;
        i = static_cast<int>(varargin_1);
        for (k = 0; k <= i - 2; k++) {
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }

          nt_im = 3.1415926535897931 * static_cast<double>(rt) / static_cast<
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
        i = nd2 - 1;
        for (k = i; k >= nfft; k--) {
          wwc[k] = wwc[idx];
          idx++;
        }

        y.set_size((static_cast<int>(varargin_1)));
        if (static_cast<int>(varargin_1) > x.size(0)) {
          nd2 = static_cast<int>(varargin_1);
          y.set_size((static_cast<int>(varargin_1)));
          for (i = 0; i < nd2; i++) {
            y[i].re = 0.0;
            y[i].im = 0.0;
          }
        }

        nd2 = static_cast<int>(varargin_1);
        rt = x.size(0);
        if (nd2 < rt) {
          rt = nd2;
        }

        nd2 = 0;
        for (k = 0; k < rt; k++) {
          nInt2 = (static_cast<int>(varargin_1) + k) - 1;
          nt_re = wwc[nInt2].re;
          nt_im = wwc[nInt2].im;
          y[k].re = nt_re * x[nd2].re + nt_im * x[nd2].im;
          y[k].im = nt_re * x[nd2].im - nt_im * x[nd2].re;
          nd2++;
        }

        i = rt + 1;
        for (k = i; k <= nfft; k++) {
          y[k - 1].re = 0.0;
          y[k - 1].im = 0.0;
        }

        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((y), (N2blue),
          (costab), (sintab), (fy));
        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (N2blue),
          (costab), (sintab), (fv));
        nd2 = fy.size(0);
        for (i = 0; i < nd2; i++) {
          nt_re = fy[i].re * fv[i].im + fy[i].im * fv[i].re;
          fy[i].re = fy[i].re * fv[i].re - fy[i].im * fv[i].im;
          fy[i].im = nt_re;
        }

        internal::FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (N2blue),
          (costab), (sintabinv), (fv));
        if (fv.size(0) > 1) {
          nt_re = 1.0 / static_cast<double>(fv.size(0));
          nd2 = fv.size(0);
          for (i = 0; i < nd2; i++) {
            fv[i].re = nt_re * fv[i].re;
            fv[i].im = nt_re * fv[i].im;
          }
        }

        idx = 0;
        i = static_cast<int>(varargin_1);
        nd2 = wwc.size(0);
        for (k = i; k <= nd2; k++) {
          double ai;
          y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].
            im;
          y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].
            re;
          nt_re = y[idx].re;
          ai = y[idx].im;
          if (ai == 0.0) {
            nt_im = nt_re / static_cast<double>(static_cast<int>(varargin_1));
            nt_re = 0.0;
          } else if (nt_re == 0.0) {
            nt_im = 0.0;
            nt_re = ai / static_cast<double>(static_cast<int>(varargin_1));
          } else {
            nt_im = nt_re / static_cast<double>(static_cast<int>(varargin_1));
            nt_re = ai / static_cast<double>(static_cast<int>(varargin_1));
          }

          y[idx].re = nt_im;
          y[idx].im = nt_re;
          idx++;
        }
      }
    }
  }
}

// End of code generation (ifft.cpp)
