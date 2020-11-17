//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  irfft.cpp
//
//  Code generation for function 'irfft'
//


// Include files
#include "irfft.h"
#include "DDSPSynth_rtwutil.h"
#include "FFTImplementationCallback.h"
#include "additive.h"
#include "ifft.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cfloat>
#include <cmath>
#include <cstring>

// Function Declarations
static double rt_remd_snf(double u0, double u1);

// Function Definitions
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    double b_u1;
    if (u1 < 0.0) {
      b_u1 = std::ceil(u1);
    } else {
      b_u1 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      b_u1 = std::abs(u0 / u1);
      if (!(std::abs(b_u1 - std::floor(b_u1 + 0.5)) > DBL_EPSILON * b_u1)) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

void b_irfft(const coder::array<creal_T, 2U> &y, double n, coder::array<creal_T,
             2U> &x)
{
  unsigned int u;
  coder::array<creal_T, 1U> t;
  int loop_ub;
  coder::array<creal_T, 2U> v;
  coder::array<int, 2U> idx;
  coder::array<creal_T, 2U> b_v;
  int b_n;
  coder::array<boolean_T, 2U> b;
  coder::array<creal_T, 2U> varargin_2;
  coder::array<double, 2U> c_x;

  // IRFFT    Inverse fft of a conjugate symmetric spectrum X=(Y,N,D)
  //
  //  Inputs:  Y(M)   The first half of a complex spectrum
  //           N      The number of output points to generate (default: 2M-2)
  //           D      The dimension along which to perorm the transform
  //                  (default: first non-singleton dimension of Y)
  //
  //  Outputs: X(N)   Real inverse dft of Y
  //
  //  This routine calculates the inverse DFT of a conjugate-symmetric to give a real-valued 
  //  output of dimension N. Only the first half of the spectrum need be supplied: if N is even, 
  //  this includes the Nyquist term and is of dimension M=N/2 + 1 whereas if N is odd then there is 
  //  no Nyquist term and the input is of dimension M=(N+1)/2.
  //  Note that the default value of N is always even so that N must be given explicitly 
  //  if it is odd.
  //
  //  See also the forward transform: RFFT
  //       Copyright (C) Mike Brookes 2009
  //       Version: $Id: irfft.m 2460 2012-10-29 22:20:45Z dmb $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  u = static_cast<unsigned int>(y.size(1));
  if (u == 1U) {
    x.set_size(1, y.size(1));
    loop_ub = y.size(0) * y.size(1);
    for (int i = 0; i < loop_ub; i++) {
      x[i] = y[i];
    }
  } else {
    int i;
    int input_sizes_idx_0;
    int sizes_idx_0;
    double b_x;
    int nx;
    boolean_T empty_non_axis_sizes;
    int ncolx;
    int nrows;
    int j;
    int b_i;

    //  number of fft's to do
    t.set_size(y.size(1));
    loop_ub = y.size(1);
    for (i = 0; i < loop_ub; i++) {
      t[i] = y[i];
    }

    input_sizes_idx_0 = y.size(1);
    loop_ub = static_cast<int>(static_cast<double>(u) / static_cast<double>(u));
    v.set_size(input_sizes_idx_0, loop_ub);
    sizes_idx_0 = input_sizes_idx_0 * loop_ub;
    for (i = 0; i < sizes_idx_0; i++) {
      v[i] = t[i];
    }

    b_x = n / 2.0;
    if (b_x < 0.0) {
      b_x = std::ceil(b_x);
    } else {
      b_x = std::floor(b_x);
    }

    //  expected input length
    if (b_x + 1.0 > u) {
      if ((input_sizes_idx_0 != 0) && (loop_ub != 0)) {
        nx = loop_ub;
      } else if ((static_cast<int>((b_x + 1.0) - static_cast<double>(u)) != 0) &&
                 (loop_ub != 0)) {
        nx = loop_ub;
      } else {
        if (loop_ub > 0) {
          nx = loop_ub;
        } else {
          nx = 0;
        }

        if (loop_ub > nx) {
          nx = loop_ub;
        }
      }

      empty_non_axis_sizes = (nx == 0);
      if ((!empty_non_axis_sizes) && ((input_sizes_idx_0 == 0) || (loop_ub == 0)))
      {
        input_sizes_idx_0 = 0;
      }

      if (empty_non_axis_sizes || ((static_cast<int>((b_x + 1.0) - static_cast<
             double>(static_cast<unsigned int>(y.size(1)))) != 0) && (loop_ub !=
            0))) {
        sizes_idx_0 = static_cast<int>((b_x + 1.0) - static_cast<double>(
          static_cast<unsigned int>(y.size(1))));
      } else {
        sizes_idx_0 = 0;
      }

      v.set_size((input_sizes_idx_0 + sizes_idx_0), nx);
      for (i = 0; i < nx; i++) {
        for (b_n = 0; b_n < input_sizes_idx_0; b_n++) {
          v[b_n + v.size(0) * i] = t[b_n + input_sizes_idx_0 * i];
        }
      }

      for (i = 0; i < nx; i++) {
        for (b_n = 0; b_n < sizes_idx_0; b_n++) {
          ncolx = b_n + input_sizes_idx_0;
          v[ncolx + v.size(0) * i].re = 0.0;
          v[ncolx + v.size(0) * i].im = 0.0;
        }
      }

      //  zero pad
    } else {
      if (b_x + 1.0 < u) {
        sizes_idx_0 = static_cast<int>(static_cast<double>(u) - ((b_x + 1.0) +
          1.0));
        idx.set_size(1, (sizes_idx_0 + 1));
        for (i = 0; i <= sizes_idx_0; i++) {
          idx[i] = static_cast<int>(((b_x + 1.0) + 1.0) + static_cast<double>(i));
        }

        ncolx = loop_ub - 1;
        if (idx.size(1) == 1) {
          nrows = input_sizes_idx_0 - 1;
          for (j = 0; j <= ncolx; j++) {
            i = idx[0];
            for (b_i = i; b_i <= nrows; b_i++) {
              v[(b_i + v.size(0) * j) - 1] = v[b_i + v.size(0) * j];
            }
          }
        } else {
          b.set_size(1, input_sizes_idx_0);
          for (i = 0; i < input_sizes_idx_0; i++) {
            b[i] = false;
          }

          i = idx.size(1);
          for (sizes_idx_0 = 0; sizes_idx_0 < i; sizes_idx_0++) {
            b[idx[sizes_idx_0] - 1] = true;
          }

          b_n = 0;
          i = b.size(1);
          for (sizes_idx_0 = 0; sizes_idx_0 < i; sizes_idx_0++) {
            b_n += b[sizes_idx_0];
          }

          nrows = input_sizes_idx_0 - b_n;
          b_i = 0;
          for (sizes_idx_0 = 0; sizes_idx_0 < input_sizes_idx_0; sizes_idx_0++)
          {
            if ((sizes_idx_0 + 1 > b.size(1)) || (!b[sizes_idx_0])) {
              for (j = 0; j <= ncolx; j++) {
                v[b_i + v.size(0) * j] = v[sizes_idx_0 + v.size(0) * j];
              }

              b_i++;
            }
          }
        }

        if (1 > nrows) {
          sizes_idx_0 = 0;
        } else {
          sizes_idx_0 = nrows;
        }

        nx = v.size(1) - 1;
        b_v.set_size(sizes_idx_0, v.size(1));
        for (i = 0; i <= nx; i++) {
          for (b_n = 0; b_n < sizes_idx_0; b_n++) {
            b_v[b_n + b_v.size(0) * i] = v[b_n + v.size(0) * i];
          }
        }

        v.set_size(b_v.size(0), b_v.size(1));
        sizes_idx_0 = b_v.size(0) * b_v.size(1);
        for (i = 0; i < sizes_idx_0; i++) {
          v[i] = b_v[i];
        }

        //  or truncate
      }
    }

    if (rt_remd_snf(n, 2.0) != 0.0) {
      //  odd output length
      if (2.0 > b_x + 1.0) {
        i = 0;
        b_n = 1;
        ncolx = -1;
      } else {
        i = static_cast<int>(b_x + 1.0) - 1;
        b_n = -1;
        ncolx = 1;
      }

      loop_ub = v.size(1);
      sizes_idx_0 = div_s32_floor(ncolx - i, b_n);
      varargin_2.set_size((sizes_idx_0 + 1), v.size(1));
      for (ncolx = 0; ncolx < loop_ub; ncolx++) {
        for (nrows = 0; nrows <= sizes_idx_0; nrows++) {
          nx = i + b_n * nrows;
          varargin_2[nrows + varargin_2.size(0) * ncolx].re = v[nx + v.size(0) *
            ncolx].re;
          varargin_2[nrows + varargin_2.size(0) * ncolx].im = -v[nx + v.size(0) *
            ncolx].im;
        }
      }

      if ((v.size(0) != 0) && (v.size(1) != 0)) {
        nx = v.size(1);
      } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
        nx = varargin_2.size(1);
      } else {
        nx = v.size(1);
        if (nx <= 0) {
          nx = 0;
        }

        if (varargin_2.size(1) > nx) {
          nx = varargin_2.size(1);
        }
      }

      empty_non_axis_sizes = (nx == 0);
      if (empty_non_axis_sizes || ((v.size(0) != 0) && (v.size(1) != 0))) {
        input_sizes_idx_0 = v.size(0);
      } else {
        input_sizes_idx_0 = 0;
      }

      if (empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size
            (1) != 0))) {
        sizes_idx_0 = varargin_2.size(0);
      } else {
        sizes_idx_0 = 0;
      }

      b_v.set_size((input_sizes_idx_0 + sizes_idx_0), nx);
      for (i = 0; i < nx; i++) {
        for (b_n = 0; b_n < input_sizes_idx_0; b_n++) {
          b_v[b_n + b_v.size(0) * i] = v[b_n + input_sizes_idx_0 * i];
        }
      }

      for (i = 0; i < nx; i++) {
        for (b_n = 0; b_n < sizes_idx_0; b_n++) {
          b_v[(b_n + input_sizes_idx_0) + b_v.size(0) * i] = varargin_2[b_n +
            sizes_idx_0 * i];
        }
      }

      b_ifft(b_v, varargin_2);
      c_x.set_size(varargin_2.size(0), varargin_2.size(1));
      loop_ub = varargin_2.size(0) * varargin_2.size(1);
      for (i = 0; i < loop_ub; i++) {
        c_x[i] = varargin_2[i].re;
      }

      //  do it the long way
    } else {
      double xtmp_im;
      double xtmp_re;

      //  even output length
      nx = v.size(1) - 1;
      b_v.set_size(1, v.size(1));
      for (i = 0; i <= nx; i++) {
        b_v[i].re = v[(static_cast<int>(b_x + 1.0) + v.size(0) * i) - 1].re;
        b_v[i].im = 0.0;
      }

      sizes_idx_0 = b_v.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        v[(static_cast<int>(b_x + 1.0) + v.size(0) * i) - 1] = b_v[i];
      }

      //  force nyquist element real
      //   t=[cumprod([-0.5i; exp(2i*pi/n)*ones(m-2,1)]); 0.5i];
      xtmp_im = 6.2831853071795862 / n;
      if (rtIsNaN((b_x + 1.0) - 1.0)) {
        c_x.set_size(1, 1);
        c_x[0] = rtNaN;
      } else if ((b_x + 1.0) - 1.0 < 0.0) {
        c_x.set_size(1, 0);
      } else if (rtIsInf((b_x + 1.0) - 1.0) && (0.0 == (b_x + 1.0) - 1.0)) {
        c_x.set_size(1, 1);
        c_x[0] = rtNaN;
      } else {
        sizes_idx_0 = static_cast<int>((b_x + 1.0) - 1.0);
        c_x.set_size(1, (sizes_idx_0 + 1));
        for (i = 0; i <= sizes_idx_0; i++) {
          c_x[i] = i;
        }
      }

      b_v.set_size(1, c_x.size(1));
      sizes_idx_0 = c_x.size(0) * c_x.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        b_v[i].re = c_x[i] * 0.0;
        b_v[i].im = c_x[i] * xtmp_im;
      }

      nx = b_v.size(1);
      for (sizes_idx_0 = 0; sizes_idx_0 < nx; sizes_idx_0++) {
        if (b_v[sizes_idx_0].im == 0.0) {
          b_v[sizes_idx_0].re = std::exp(b_v[sizes_idx_0].re);
          b_v[sizes_idx_0].im = 0.0;
        } else if (rtIsInf(b_v[sizes_idx_0].im) && rtIsInf(b_v[sizes_idx_0].re) &&
                   (b_v[sizes_idx_0].re < 0.0)) {
          b_v[sizes_idx_0].re = 0.0;
          b_v[sizes_idx_0].im = 0.0;
        } else {
          xtmp_im = std::exp(b_v[sizes_idx_0].re / 2.0);
          b_v[sizes_idx_0].re = xtmp_im * (xtmp_im * std::cos(b_v[sizes_idx_0].
            im));
          b_v[sizes_idx_0].im = xtmp_im * (xtmp_im * std::sin(b_v[sizes_idx_0].
            im));
        }
      }

      t.set_size(b_v.size(1));
      sizes_idx_0 = b_v.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        t[i].re = -0.0 * b_v[i].re - -0.5 * b_v[i].im;
        t[i].im = -0.0 * b_v[i].im + -0.5 * b_v[i].re;
      }

      x.set_size(v.size(0), v.size(1));
      sizes_idx_0 = v.size(0) * v.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        x[i] = v[i];
      }

      nx = v.size(0) - 1;
      b_n = v.size(1);
      sizes_idx_0 = v.size(0) >> 1;
      for (j = 0; j < b_n; j++) {
        for (b_i = 0; b_i < sizes_idx_0; b_i++) {
          xtmp_re = x[b_i + x.size(0) * j].re;
          xtmp_im = x[b_i + x.size(0) * j].im;
          nrows = nx - b_i;
          x[b_i + x.size(0) * j] = x[nrows + x.size(0) * j];
          x[nrows + x.size(0) * j].re = xtmp_re;
          x[nrows + x.size(0) * j].im = xtmp_im;
        }
      }

      sizes_idx_0 = t.size(0);
      b_v.set_size(t.size(0), loop_ub);
      for (i = 0; i < loop_ub; i++) {
        for (b_n = 0; b_n < sizes_idx_0; b_n++) {
          double x_re;
          double x_im;
          xtmp_im = t[b_n].re + 0.5;
          xtmp_re = t[b_n].im;
          x_re = x[b_n + x.size(0) * i].re - v[b_n + v.size(0) * i].re;
          x_im = -x[b_n + x.size(0) * i].im - v[b_n + v.size(0) * i].im;
          b_v[b_n + b_v.size(0) * i].re = (xtmp_im * x_re - xtmp_re * x_im) +
            v[b_n + v.size(0) * i].re;
          b_v[b_n + b_v.size(0) * i].im = (xtmp_im * x_im + xtmp_re * x_re) +
            v[b_n + v.size(0) * i].im;
        }
      }

      nx = static_cast<int>(b_x + 1.0);
      sizes_idx_0 = b_v.size(0) - 2;
      ncolx = b_v.size(1);
      nrows = b_v.size(0) - 1;
      for (j = 0; j < ncolx; j++) {
        for (b_i = nx; b_i <= nrows; b_i++) {
          b_v[(b_i + b_v.size(0) * j) - 1] = b_v[b_i + b_v.size(0) * j];
        }
      }

      if (1 > nrows) {
        sizes_idx_0 = -1;
      }

      nx = b_v.size(1) - 1;
      x.set_size((sizes_idx_0 + 1), b_v.size(1));
      for (i = 0; i <= nx; i++) {
        for (b_n = 0; b_n <= sizes_idx_0; b_n++) {
          x[b_n + x.size(0) * i] = b_v[b_n + b_v.size(0) * i];
        }
      }

      b_v.set_size(x.size(0), x.size(1));
      sizes_idx_0 = x.size(0) * x.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        b_v[i] = x[i];
      }

      b_ifft(b_v, varargin_2);
      v.set_size(varargin_2.size(0), varargin_2.size(1));
      sizes_idx_0 = varargin_2.size(0) * varargin_2.size(1);
      for (i = 0; i < sizes_idx_0; i++) {
        v[i] = varargin_2[i];
      }

      i = static_cast<int>(n);
      c_x.set_size(i, loop_ub);
      loop_ub *= i;
      for (i = 0; i < loop_ub; i++) {
        c_x[i] = 0.0;
      }

      if (1.0 > n) {
        i = 1;
      } else {
        i = 2;
      }

      loop_ub = v.size(1);
      for (b_n = 0; b_n < loop_ub; b_n++) {
        sizes_idx_0 = v.size(0);
        for (ncolx = 0; ncolx < sizes_idx_0; ncolx++) {
          c_x[i * ncolx + c_x.size(0) * b_n] = v[ncolx + v.size(0) * b_n].re;
        }
      }

      if (2.0 > n) {
        i = 0;
        b_n = 1;
      } else {
        i = 1;
        b_n = 2;
      }

      loop_ub = v.size(1);
      for (ncolx = 0; ncolx < loop_ub; ncolx++) {
        sizes_idx_0 = v.size(0);
        for (nrows = 0; nrows < sizes_idx_0; nrows++) {
          c_x[(i + b_n * nrows) + c_x.size(0) * ncolx] = v[nrows + v.size(0) *
            ncolx].im;
        }
      }
    }

    //  change output dimension
    input_sizes_idx_0 = static_cast<int>(n);
    nx = y.size(0);
    x.set_size(nx, input_sizes_idx_0);
    for (i = 0; i < input_sizes_idx_0; i++) {
      for (b_n = 0; b_n < nx; b_n++) {
        x[b_n + x.size(0) * i].re = c_x[i + input_sizes_idx_0 * b_n];
        x[b_n + x.size(0) * i].im = 0.0;
      }
    }
  }
}

void irfft(const double y[1024], double x[2046])
{
  double b_x[1024];
  int i;
  double xtmp;
  creal_T tmp_data[1023];
  creal_T zz_data[1023];
  int zz_size[1];
  static const creal_T dcv[1024] = { { 0.5,// re
      -0.5                             // im
    }, { 0.50153547786688046,          // re
      -0.49999764230216159             // im
    }, { 0.50307094125298957,          // re
      -0.49999056923088125             // im
    }, { 0.5046063756776924,           // re
      -0.49997878085286374             // im
    }, { 0.50614176666062738,          // re
      -0.49996227727928277             // im
    }, { 0.50767709972184238,          // re
      -0.49994105866578                // im
    }, { 0.50921236038193174,          // re
      -0.49991512521246384             // im
    }, { 0.51074753416217245,          // re
      -0.49988447716390727             // im
    }, { 0.51228260658466085,          // re
      -0.49984911480914562             // im
    }, { 0.51381756317244942,          // re
      -0.49980903848167391             // im
    }, { 0.51535238944968254,          // re
      -0.49976424855944357             // im
    }, { 0.516887070941734,            // re
      -0.499714745464859               // im
    }, { 0.518421593175343,            // re
      -0.49966052966477364             // im
    }, { 0.51995594167875026,          // re
      -0.49960160167048534             // im
    }, { 0.52149010198183521,          // re
      -0.49953796203773176             // im
    }, { 0.5230240596162522,           // re
      -0.49946961136668488             // im
    }, { 0.524557800115567,            // re
      -0.4993965503019458              // im
    }, { 0.52609130901539258,          // re
      -0.499318779532538               // im
    }, { 0.52762457185352685,          // re
      -0.49923629979190148             // im
    }, { 0.52915757417008769,          // re
      -0.49914911185788546             // im
    }, { 0.53069030150765018,          // re
      -0.4990572165527411              // im
    }, { 0.53222273941138254,          // re
      -0.49896061474311393             // im
    }, { 0.5337548734291826,           // re
      -0.49885930734003536             // im
    }, { 0.53528668911181432,          // re
      -0.49875329529891443             // im
    }, { 0.53681817201304338,          // re
      -0.49864257961952863             // im
    }, { 0.53834930768977418,          // re
      -0.49852716134601438             // im
    }, { 0.5398800817021856,           // re
      -0.49840704156685728             // im
    }, { 0.54141047961386735,          // re
      -0.498282221414882               // im
    }, { 0.542940486991956,            // re
      -0.49815270206724127             // im
    }, { 0.544470089407271,            // re
      -0.49801848474540511             // im
    }, { 0.54599927243445157,          // re
      -0.49787957071514904             // im
    }, { 0.54752802165209136,          // re
      -0.49773596128654229             // im
    }, { 0.54905632264287541,          // re
      -0.49758765781393544             // im
    }, { 0.5505841609937161,           // re
      -0.49743466169594758             // im
    }, { 0.55211152229588867,          // re
      -0.49727697437545315             // im
    }, { 0.5536383921451673,           // re
      -0.49711459733956842             // im
    }, { 0.555164756141961,            // re
      -0.49694753211963733             // im
    }, { 0.55669059989144953,          // re
      -0.49677578029121705             // im
    }, { 0.55821590900371876,          // re
      -0.49659934347406332             // im
    }, { 0.55974066909389675,          // re
      -0.49641822333211494             // im
    }, { 0.56126486578228918,          // re
      -0.49623242157347813             // im
    }, { 0.562788484694515,            // re
      -0.49604193995041052             // im
    }, { 0.56431151146164238,          // re
      -0.49584678025930456             // im
    }, { 0.56583393172032348,          // re
      -0.49564694434067058             // im
    }, { 0.56735573111293047,          // re
      -0.49544243407911942             // im
    }, { 0.56887689528769092,          // re
      -0.49523325140334473             // im
    }, { 0.57039740989882282,          // re
      -0.49501939828610464             // im
    }, { 0.57191726060667014,          // re
      -0.49480087674420331             // im
    }, { 0.57343643307783787,          // re
      -0.49457768883847181             // im
    }, { 0.57495491298532764,          // re
      -0.49434983667374865             // im
    }, { 0.576472686008672,            // re
      -0.49411732239886014             // im
    }, { 0.57798973783407037,          // re
      -0.49388014820659981             // im
    }, { 0.5795060541545235,           // re
      -0.493638316333708               // im
    }, { 0.58102162066996854,          // re
      -0.49339182906085072             // im
    }, { 0.58253642308741393,          // re
      -0.49314068871259792             // im
    }, { 0.58405044712107412,          // re
      -0.4928848976574019              // im
    }, { 0.58556367849250424,          // re
      -0.49262445830757468             // im
    }, { 0.58707610293073509,          // re
      -0.49235937311926542             // im
    }, { 0.58858770617240741,          // re
      -0.49208964459243726             // im
    }, { 0.59009847396190618,          // re
      -0.49181527527084368             // im
    }, { 0.59160839205149574,          // re
      -0.49153626774200443             // im
    }, { 0.59311744620145368,          // re
      -0.49125262463718133             // im
    }, { 0.59462562218020509,          // re
      -0.49096434863135335             // im
    }, { 0.596132905764457,            // re
      -0.49067144244319133             // im
    }, { 0.59763928273933242,          // re
      -0.49037390883503246             // im
    }, { 0.59914473889850439,          // re
      -0.490071750612854               // im
    }, { 0.60064926004433006,          // re
      -0.48976497062624724             // im
    }, { 0.6021528319879843,           // re
      -0.48945357176839016             // im
    }, { 0.60365544054959386,          // re
      -0.4891375569760204              // im
    }, { 0.605157071558371,            // re
      -0.48881692922940756             // im
    }, { 0.60665771085274678,          // re
      -0.488491691552325               // im
    }, { 0.60815734428050527,          // re
      -0.48816184701202148             // im
    }, { 0.60965595769891656,          // re
      -0.4878273987191919              // im
    }, { 0.61115353697487007,          // re
      -0.48748834982794842             // im
    }, { 0.61265006798500821,          // re
      -0.48714470353579031             // im
    }, { 0.614145536615859,            // re
      -0.48679646308357416             // im
    }, { 0.61563992876397022,          // re
      -0.48644363175548294             // im
    }, { 0.61713323033604106,          // re
      -0.48608621287899534             // im
    }, { 0.618625427249056,            // re
      -0.48572420982485415             // im
    }, { 0.6201165054304173,           // re
      -0.48535762600703464             // im
    }, { 0.62160645081807786,          // re
      -0.48498646488271241             // im
    }, { 0.6230952493606734,           // re
      -0.48461072995223048             // im
    }, { 0.62458288701765552,          // re
      -0.48423042475906664             // im
    }, { 0.62606934975942408,          // re
      -0.48384555288979975             // im
    }, { 0.62755462356745884,          // re
      -0.48345611797407617             // im
    }, { 0.62903869443445259,          // re
      -0.48306212368457535             // im
    }, { 0.63052154836444263,          // re
      -0.48266357373697516             // im
    }, { 0.63200317137294282,          // re
      -0.48226047188991705             // im
    }, { 0.63348354948707586,          // re
      -0.48185282194497042             // im
    }, { 0.63496266874570439,          // re
      -0.48144062774659685             // im
    }, { 0.63644051519956357,          // re
      -0.48102389318211386             // im
    }, { 0.63791707491139171,          // re
      -0.48060262218165806             // im
    }, { 0.63939233395606221,          // re
      -0.48017681871814849             // im
    }, { 0.64086627842071486,          // re
      -0.47974648680724868             // im
    }, { 0.6423388944048869,           // re
      -0.47931163050732917             // im
    }, { 0.64381016802064439,          // re
      -0.47887225391942895             // im
    }, { 0.64528008539271275,          // re
      -0.47842836118721693             // im
    }, { 0.64674863265860782,          // re
      -0.47797995649695291             // im
    }, { 0.648215795968767,            // re
      -0.47752704407744789             // im
    }, { 0.649681561486679,            // re
      -0.47706962820002441             // im
    }, { 0.65114591538901512,          // re
      -0.47660771317847628             // im
    }, { 0.65260884386575924,          // re
      -0.47614130336902755             // im
    }, { 0.65407033312033813,          // re
      -0.47567040317029191             // im
    }, { 0.65553036936975162,          // re
      -0.4751950170232308              // im
    }, { 0.65698893884470233,          // re
      -0.47471514941111193             // im
    }, { 0.658446027789726,            // re
      -0.47423080485946645             // im
    }, { 0.65990162246332085,          // re
      -0.47374198793604688             // im
    }, { 0.66135570913807706,          // re
      -0.47324870325078366             // im
    }, { 0.66280827410080667,          // re
      -0.47275095545574164             // im
    }, { 0.66425930365267261,          // re
      -0.47224874924507643             // im
    }, { 0.66570878410931789,          // re
      -0.47174208935499012             // im
    }, { 0.66715670180099473,          // re
      -0.47123098056368634             // im
    }, { 0.66860304307269358,          // re
      -0.47071542769132546             // im
    }, { 0.67004779428427153,          // re
      -0.47019543559997906             // im
    }, { 0.67149094181058144,          // re
      -0.46967100919358407             // im
    }, { 0.67293247204160023,          // re
      -0.46914215341789656             // im
    }, { 0.67437237138255679,          // re
      -0.46860887326044487             // im
    }, { 0.67581062625406108,          // re
      -0.468071173750483               // im
    }, { 0.67724722309223129,          // re
      -0.46752905995894284             // im
    }, { 0.67868214834882257,          // re
      -0.46698253699838643             // im
    }, { 0.68011538849135411,          // re
      -0.4664316100229578              // im
    }, { 0.68154693000323729,          // re
      -0.46587628422833421             // im
    }, { 0.68297675938390268,          // re
      -0.46531656485167749             // im
    }, { 0.68440486314892768,          // re
      -0.46475245717158425             // im
    }, { 0.6858312278301637,           // re
      -0.46418396650803628             // im
    }, { 0.68725583997586315,          // re
      -0.46361109822235053             // im
    }, { 0.68867868615080607,          // re
      -0.46303385771712813             // im
    }, { 0.69009975293642689,          // re
      -0.46245225043620392             // im
    }, { 0.69151902693094147,          // re
      -0.46186628186459477             // im
    }, { 0.69293649474947272,          // re
      -0.46127595752844813             // im
    }, { 0.69435214302417747,          // re
      -0.46068128299498956             // im
    }, { 0.69576595840437228,          // re
      -0.46008226387247048             // im
    }, { 0.6971779275566593,           // re
      -0.4594789058101153              // im
    }, { 0.69858803716505191,          // re
      -0.45887121449806806             // im
    }, { 0.69999627393110064,          // re
      -0.45825919566733864             // im
    }, { 0.70140262457401847,          // re
      -0.457642855089749               // im
    }, { 0.70280707583080582,          // re
      -0.45702219857787846             // im
    }, { 0.704209614456376,            // re
      -0.45639723198500914             // im
    }, { 0.70561022722367983,          // re
      -0.45576796120507063             // im
    }, { 0.70700890092383051,          // re
      -0.45513439217258428             // im
    }, { 0.70840562236622817,          // re
      -0.45449653086260744             // im
    }, { 0.70980037837868437,          // re
      -0.45385438329067712             // im
    }, { 0.71119315580754627,          // re
      -0.453207955512753               // im
    }, { 0.71258394151782034,          // re
      -0.45255725362516058             // im
    }, { 0.71397272239329679,          // re
      -0.45190228376453367             // im
    }, { 0.715359485336673,            // re
      -0.45124305210775634             // im
    }, { 0.71674421726967708,          // re
      -0.45057956487190476             // im
    }, { 0.71812690513319088,          // re
      -0.44991182831418863             // im
    }, { 0.71950753588737371,          // re
      -0.44923984873189216             // im
    }, { 0.720886096511785,            // re
      -0.44856363246231451             // im
    }, { 0.7222625740055072,           // re
      -0.44788318588271031             // im
    }, { 0.72363695538726824,          // re
      -0.4471985154102292              // im
    }, { 0.72500922769556408,          // re
      -0.44650962750185558             // im
    }, { 0.72637937798878083,          // re
      -0.44581652865434757             // im
    }, { 0.727747393345317,            // re
      -0.44511922540417581             // im
    }, { 0.7291132608637052,           // re
      -0.44441772432746174             // im
    }, { 0.73047696766273384,          // re
      -0.44371203203991566             // im
    }, { 0.73183850088156854,          // re
      -0.44300215519677433             // im
    }, { 0.73319784767987373,          // re
      -0.44228810049273809             // im
    }, { 0.73455499523793333,          // re
      -0.44156987466190789             // im
    }, { 0.73590993075677191,          // re
      -0.44084748447772171             // im
    }, { 0.73726264145827525,          // re
      -0.4401209367528906              // im
    }, { 0.738613114585311,            // re
      -0.4393902383393346              // im
    }, { 0.73996133740184877,          // re
      -0.43865539612811794             // im
    }, { 0.74130729719308064,          // re
      -0.43791641704938428             // im
    }, { 0.74265098126554052,          // re
      -0.43717330807229104             // im
    }, { 0.74399237694722431,          // re
      -0.436426076204944               // im
    }, { 0.74533147158770929,          // re
      -0.435674728494331               // im
    }, { 0.74666825255827307,          // re
      -0.43491927202625547             // im
    }, { 0.74800270725201357,          // re
      -0.43415971392526975             // im
    }, { 0.74933482308396671,          // re
      -0.43339606135460784             // im
    }, { 0.75066458749122611,          // re
      -0.4326283215161178              // im
    }, { 0.75199198793306132,          // re
      -0.43185650165019385             // im
    }, { 0.75331701189103539,          // re
      -0.43108060903570811             // im
    }, { 0.7546396468691241,           // re
      -0.43030065098994191             // im
    }, { 0.75595988039383266,          // re
      -0.42951663486851693             // im
    }, { 0.75727770001431438,          // re
      -0.4287285680653255              // im
    }, { 0.75859309330248736,          // re
      -0.42793645801246133             // im
    }, { 0.75990604785315186,          // re
      -0.42714031218014903             // im
    }, { 0.76121655128410737,          // re
      -0.42634013807667381             // im
    }, { 0.76252459123626981,          // re
      -0.42553594324831062             // im
    }, { 0.763830155373787,            // re
      -0.42472773527925328             // im
    }, { 0.765133231384156,            // re
      -0.42391552179154229             // im
    }, { 0.766433806978339,            // re
      -0.42309931044499377             // im
    }, { 0.76773186989087872,          // re
      -0.42227910893712656             // im
    }, { 0.76902740788001478,          // re
      -0.4214549250030899              // im
    }, { 0.77032040872779883,          // re
      -0.4206267664155906              // im
    }, { 0.77161086024020942,          // re
      -0.41979464098481944             // im
    }, { 0.77289875024726773,          // re
      -0.41895855655837777             // im
    }, { 0.77418406660315164,          // re
      -0.41811852102120339             // im
    }, { 0.77546679718631106,          // re
      -0.4172745422954961              // im
    }, { 0.77674692989958127,          // re
      -0.41642662834064326             // im
    }, { 0.778024452670298,            // re
      -0.41557478715314439             // im
    }, { 0.77929935345041024,          // re
      -0.41471902676653605             // im
    }, { 0.78057162021659487,          // re
      -0.41385935525131584             // im
    }, { 0.78184124097036944,          // re
      -0.41299578071486653             // im
    }, { 0.78310820373820555,          // re
      -0.41212831130137934             // im
    }, { 0.78437249657164188,          // re
      -0.41125695519177735             // im
    }, { 0.78563410754739615,          // re
      -0.41038172060363814             // im
    }, { 0.78689302476747858,          // re
      -0.40950261579111663             // im
    }, { 0.78814923635930378,          // re
      -0.40861964904486675             // im
    }, { 0.789402730475802,            // re
      -0.40773282869196376             // im
    }, { 0.79065349529553208,          // re
      -0.40684216309582527             // im
    }, { 0.79190151902279171,          // re
      -0.4059476606561328              // im
    }, { 0.79314678988772969,          // re
      -0.40504932980875213             // im
    }, { 0.79438929614645615,          // re
      -0.40414717902565411             // im
    }, { 0.79562902608115393,          // re
      -0.40324121681483455             // im
    }, { 0.79686596800018861,          // re
      -0.402331451720234               // im
    }, { 0.79810011023821925,          // re
      -0.4014178923216572              // im
    }, { 0.7993314411563075,           // re
      -0.40050054723469231             // im
    }, { 0.80055994914202877,          // re
      -0.39957942511062944             // im
    }, { 0.80178562260958031,          // re
      -0.39865453463637912             // im
    }, { 0.80300844999989152,          // re
      -0.39772588453439039             // im
    }, { 0.80422841978073234,          // re
      -0.39679348356256877             // im
    }, { 0.80544552044682227,          // re
      -0.39585734051419308             // im
    }, { 0.80665974051993916,          // re
      -0.39491746421783325             // im
    }, { 0.80787106854902646,          // re
      -0.39397386353726643             // im
    }, { 0.80907949311030258,          // re
      -0.39302654737139375             // im
    }, { 0.81028500280736737,          // re
      -0.3920755246541564              // im
    }, { 0.81148758627131068,          // re
      -0.39112080435445112             // im
    }, { 0.8126872321608184,           // re
      -0.39016239547604592             // im
    }, { 0.81388392916228081,          // re
      -0.38920030705749492             // im
    }, { 0.81507766598989784,          // re
      -0.38823454817205327             // im
    }, { 0.81626843138578686,          // re
      -0.38726512792759155             // im
    }, { 0.81745621412008762,          // re
      -0.3862920554665098              // im
    }, { 0.81864100299106912,          // re
      -0.38531533996565126             // im
    }, { 0.81982278682523479,          // re
      -0.38433499063621623             // im
    }, { 0.82100155447742762,          // re
      -0.38335101672367455             // im
    }, { 0.822177294830936,            // re
      -0.382363427507679               // im
    }, { 0.82334999679759813,          // re
      -0.38137223230197725             // im
    }, { 0.824519649317906,            // re
      -0.3803774404543247              // im
    }, { 0.82568624136111113,          // re
      -0.37937906134639549             // im
    }, { 0.82684976192532711,          // re
      -0.37837710439369476             // im
    }, { 0.82801020003763437,          // re
      -0.37737157904546947             // im
    }, { 0.82916754475418331,          // re
      -0.37636249478461947             // im
    }, { 0.83032178516029731,          // re
      -0.37534986112760776             // im
    }, { 0.83147291037057569,          // re
      -0.37433368762437114             // im
    }, { 0.83262090952899714,          // re
      -0.37331398385822989             // im
    }, { 0.83376577180902078,          // re
      -0.37229075944579748             // im
    }, { 0.83490748641368961,          // re
      -0.37126402403688974             // im
    }, { 0.83604604257573134,          // re
      -0.37023378731443429             // im
    }, { 0.83718142955766028,          // re
      -0.36920005899437852             // im
    }, { 0.83831363665187864,          // re
      -0.36816284882559869             // im
    }, { 0.83944265318077771,          // re
      -0.36712216658980734             // im
    }, { 0.84056846849683808,          // re
      -0.36607802210146162             // im
    }, { 0.84169107198273041,          // re
      -0.36503042520767026             // im
    }, { 0.84281045305141544,          // re
      -0.36397938578810107             // im
    }, { 0.84392660114624385,          // re
      -0.36292491375488739             // im
    }, { 0.845039505741056,            // re
      -0.3618670190525351              // im
    }, { 0.84614915634028065,          // re
      -0.36080571165782832             // im
    }, { 0.84725554247903456,          // re
      -0.35974100157973571             // im
    }, { 0.84835865372322106,          // re
      -0.3586728988593158              // im
    }, { 0.849458479669628,            // re
      -0.35760141356962261             // im
    }, { 0.8505550099460264,           // re
      -0.35652655581561016             // im
    }, { 0.8516482342112679,           // re
      -0.35544833573403783             // im
    }, { 0.85273814215538279,          // re
      -0.35436676349337415             // im
    }, { 0.85382472349967653,          // re
      -0.35328184929370132             // im
    }, { 0.854907967996827,            // re
      -0.35219360336661876             // im
    }, { 0.85598786543098171,          // re
      -0.35110203597514672             // im
    }, { 0.85706440561785313,          // re
      -0.35000715741362959             // im
    }, { 0.8581375784048153,           // re
      -0.34890897800763854             // im
    }, { 0.85920737367099953,          // re
      -0.34780750811387456             // im
    }, { 0.86027378132739007,          // re
      -0.34670275812007023             // im
    }, { 0.86133679131691865,          // re
      -0.34559473844489241             // im
    }, { 0.86239639361456,             // re
      -0.34448345953784332             // im
    }, { 0.86345257822742572,          // re
      -0.34336893187916256             // im
    }, { 0.86450533519485928,          // re
      -0.34225116597972788             // im
    }, { 0.86555465458852932,          // re
      -0.34113017238095633             // im
    }, { 0.86660052651252362,          // re
      -0.34000596165470459             // im
    }, { 0.8676429411034422,           // re
      -0.3388785444031695              // im
    }, { 0.86868188853049055,          // re
      -0.33774793125878788             // im
    }, { 0.86971735899557234,          // re
      -0.3366141328841365              // im
    }, { 0.87074934273338167,          // re
      -0.33547715997183108             // im
    }, { 0.871777830011495,            // re
      -0.3343370232444261              // im
    }, { 0.87280281113046365,          // re
      -0.33319373345431308             // im
    }, { 0.87382427642390448,          // re
      -0.33204730138361954             // im
    }, { 0.87484221625859138,          // re
      -0.33089773784410703             // im
    }, { 0.8758566210345462,           // re
      -0.32974505367706958             // im
    }, { 0.87686748118512925,          // re
      -0.32858925975323094             // im
    }, { 0.87787478717712908,          // re
      -0.32743036697264255             // im
    }, { 0.87887852951085343,          // re
      -0.32626838626458038             // im
    }, { 0.8798786987202174,           // re
      -0.325103328587442               // im
    }, { 0.8808752853728341,           // re
      -0.32393520492864336             // im
    }, { 0.88186828007010276,          // re
      -0.32276402630451495             // im
    }, { 0.88285767344729738,          // re
      -0.32158980376019797             // im
    }, { 0.88384345617365556,          // re
      -0.32041254836954025             // im
    }, { 0.88482561895246614,          // re
      -0.31923227123499176             // im
    }, { 0.88580415252115685,          // re
      -0.31804898348749988             // im
    }, { 0.88677904765138171,          // re
      -0.31686269628640451             // im
    }, { 0.88775029514910819,          // re
      -0.3156734208193327              // im
    }, { 0.88871788585470379,          // re
      -0.31448116830209322             // im
    }, { 0.88968181064302243,          // re
      -0.31328594997857084             // im
    }, { 0.89064206042349059,          // re
      -0.31208777712062014             // im
    }, { 0.891598626140193,            // re
      -0.31088666102795942             // im
    }, { 0.89255149877195783,          // re
      -0.30968261302806388             // im
    }, { 0.89350066933244221,          // re
      -0.308475644476059               // im
    }, { 0.89444612887021657,          // re
      -0.30726576675461342             // im
    }, { 0.89538786846884921,          // re
      -0.30605299127383145             // im
    }, { 0.8963258792469907,           // re
      -0.30483732947114556             // im
    }, { 0.89726015235845691,          // re
      -0.30361879281120868             // im
    }, { 0.898190678992313,            // re
      -0.3023973927857857              // im
    }, { 0.89911745037295665,          // re
      -0.30117314091364544             // im
    }, { 0.90004045776020014,          // re
      -0.29994604874045194             // im
    }, { 0.90095969244935348,          // re
      -0.29871612783865537             // im
    }, { 0.90187514577130612,          // re
      -0.2974833898073832              // im
    }, { 0.90278680909260867,          // re
      -0.29624784627233058             // im
    }, { 0.90369467381555468,          // re
      -0.29500950888565081             // im
    }, { 0.90459873137826152,          // re
      -0.29376838932584531             // im
    }, { 0.90549897325475048,          // re
      -0.29252449929765384             // im
    }, { 0.90639539095502886,          // re
      -0.29127785053194361             // im
    }, { 0.90728797602516775,          // re
      -0.29002845478559913             // im
    }, { 0.90817672004738415,          // re
      -0.28877632384141089             // im
    }, { 0.90906161464011825,          // re
      -0.28752146950796464             // im
    }, { 0.90994265145811382,          // re
      -0.28626390361952969             // im
    }, { 0.91081982219249658,          // re
      -0.28500363803594775             // im
    }, { 0.91169311857085233,          // re
      -0.28374068464252034             // im
    }, { 0.912562532357305,            // re
      -0.28247505534989759             // im
    }, { 0.91342805535259464,          // re
      -0.28120676209396511             // im
    }, { 0.91428967939415462,          // re
      -0.27993581683573221             // im
    }, { 0.91514739635618825,          // re
      -0.27866223156121822             // im
    }, { 0.91600119814974568,          // re
      -0.2773860182813403              // im
    }, { 0.91685107672280064,          // re
      -0.27610718903179948             // im
    }, { 0.91769702406032527,          // re
      -0.27482575587296765             // im
    }, { 0.91853903218436717,          // re
      -0.27354173088977357             // im
    }, { 0.919377093154123,            // re
      -0.272255126191589               // im
    }, { 0.9202111990660149,           // re
      -0.27096595391211431             // im
    }, { 0.92104134205376376,          // re
      -0.26967422620926429             // im
    }, { 0.92186751428846458,          // re
      -0.26837995526505348             // im
    }, { 0.92268970797865923,          // re
      -0.26708315328548105             // im
    }, { 0.92350791537041066,          // re
      -0.26578383250041593             // im
    }, { 0.92432212874737552,          // re
      -0.26448200516348119             // im
    }, { 0.92513234043087733,          // re
      -0.2631776835519391              // im
    }, { 0.92593854277997889,          // re
      -0.26187087996657443             // im
    }, { 0.92674072819155406,          // re
      -0.26056160673157924             // im
    }, { 0.92753888910035953,          // re
      -0.25924987619443607             // im
    }, { 0.92833301797910628,          // re
      -0.25793570072580213             // im
    }, { 0.92912310733853065,          // re
      -0.256619092719392               // im
    }, { 0.92990914972746463,          // re
      -0.25530006459186105             // im
    }, { 0.93069113773290657,          // re
      -0.25397862878268823             // im
    }, { 0.93146906398009044,          // re
      -0.25265479775405919             // im
    }, { 0.93224292113255658,          // re
      -0.25132858399074803             // im
    }, { 0.9330127018922193,           // re
      -0.25000000000000006             // im
    }, { 0.933778398999437,            // re
      -0.24866905831141364             // im
    }, { 0.93454000523308012,          // re
      -0.24733577147682209             // im
    }, { 0.93529751341059886,          // re
      -0.24600015207017553             // im
    }, { 0.9360509163880919,           // re
      -0.24466221268742183             // im
    }, { 0.936800207060373,            // re
      -0.24332196594638814             // im
    }, { 0.93754537836103813,          // re
      -0.24197942448666174             // im
    }, { 0.938286423262532,            // re
      -0.24063460096947123             // im
    }, { 0.93902333477621491,          // re
      -0.23928750807756649             // im
    }, { 0.93975610595242831,          // re
      -0.23793815851509956             // im
    }, { 0.94048472988056,             // re
      -0.23658656500750447             // im
    }, { 0.94120919968910954,          // re
      -0.23523274030137781             // im
    }, { 0.94192950854575352,          // re
      -0.23387669716435783             // im
    }, { 0.94264564965740938,          // re
      -0.23251844838500441             // im
    }, { 0.9433576162702999,           // re
      -0.23115800677267828             // im
    }, { 0.94406540167001607,          // re
      -0.22979538515742062             // im
    }, { 0.94476899918158175,          // re
      -0.22843059638983154             // im
    }, { 0.94546840216951566,          // re
      -0.22706365334094911             // im
    }, { 0.946163604037894,            // re
      -0.22569456890212791             // im
    }, { 0.94685459823041307,          // re
      -0.22432335598491782             // im
    }, { 0.9475413782304507,           // re
      -0.2229500275209417              // im
    }, { 0.94822393756112811,          // re
      -0.22157459646177372             // im
    }, { 0.94890226978537084,          // re
      -0.22019707577881714             // im
    }, { 0.94957636850596883,          // re
      -0.21881747846318231             // im
    }, { 0.950246227365638,            // re
      -0.21743581752556354             // im
    }, { 0.95091184004707907,          // re
      -0.21605210599611688             // im
    }, { 0.95157320027303793,          // re
      -0.21466635692433694             // im
    }, { 0.95223030180636381,          // re
      -0.21327858337893432             // im
    }, { 0.95288313845006978,          // re
      -0.21188879844771163             // im
    }, { 0.95353170404738929,          // re
      -0.21049701523744058             // im
    }, { 0.95417599248183571,          // re
      -0.20910324687373819             // im
    }, { 0.95481599767725922,          // re
      -0.20770750650094322             // im
    }, { 0.95545171359790415,          // re
      -0.20630980728199186             // im
    }, { 0.95608313424846658,          // re
      -0.20491016239829382             // im
    }, { 0.95671025367415008,          // re
      -0.20350858504960784             // im
    }, { 0.957333065960722,            // re
      -0.2021050884539177              // im
    }, { 0.9579515652345697,           // re
      -0.2006996858473068              // im
    }, { 0.95856574566275565,          // re
      -0.19929239048383393             // im
    }, { 0.95917560145307224,          // re
      -0.19788321563540795             // im
    }, { 0.95978112685409678,          // re
      -0.19647217459166302             // im
    }, { 0.96038231615524572,          // re
      -0.19505928065983269             // im
    }, { 0.960979163686828,            // re
      -0.19364454716462487             // im
    }, { 0.96157166382009929,          // re
      -0.19222798744809588             // im
    }, { 0.96215981096731418,          // re
      -0.19080961486952502             // im
    }, { 0.9627435995817798,           // re
      -0.18938944280528805             // im
    }, { 0.96332302415790749,          // re
      -0.18796748464873139             // im
    }, { 0.963898079231265,            // re
      -0.18654375381004573             // im
    }, { 0.96446875937862808,          // re
      -0.18511826371613946             // im
    }, { 0.965035059218031,            // re
      -0.18369102781051244             // im
    }, { 0.96559697340881823,          // re
      -0.18226205955312857             // im
    }, { 0.96615449665169439,          // re
      -0.18083137242028938             // im
    }, { 0.96670762368877416,          // re
      -0.17939897990450659             // im
    }, { 0.96725634930363169,          // re
      -0.17796489551437536             // im
    }, { 0.96780066832135025,          // re
      -0.17652913277444626             // im
    }, { 0.96834057560857079,          // re
      -0.17509170522509812             // im
    }, { 0.96887606607354027,          // re
      -0.17365262642241014             // im
    }, { 0.96940713466615991,          // re
      -0.17221190993803445             // im
    }, { 0.96993377637803246,          // re
      -0.17076956935906754             // im
    }, { 0.97045598624251006,          // re
      -0.16932561828792242             // im
    }, { 0.97097375933474028,          // re
      -0.16788007034220029             // im
    }, { 0.97148709077171325,          // re
      -0.16643293915456242             // im
    }, { 0.97199597571230711,          // re
      -0.16498423837260104             // im
    }, { 0.97250040935733417,          // re
      -0.16353398165871089             // im
    }, { 0.97300038694958624,          // re
      -0.16208218268996039             // im
    }, { 0.97349590377387862,          // re
      -0.16062885515796288             // im
    }, { 0.97398695515709588,          // re
      -0.15917401276874701             // im
    }, { 0.97447353646823442,          // re
      -0.15771766924262781             // im
    }, { 0.974955643118448,            // re
      -0.15625983831407705             // im
    }, { 0.97543327056108886,          // re
      -0.15480053373159433             // im
    }, { 0.97590641429175251,          // re
      -0.15333976925757653             // im
    }, { 0.97637506984831912,          // re
      -0.15187755866818867             // im
    }, { 0.97683923281099583,          // re
      -0.15041391575323357             // im
    }, { 0.97729889880235876,          // re
      -0.14894885431602242             // im
    }, { 0.97775406348739369,          // re
      -0.14748238817324386             // im
    }, { 0.97820472257353752,          // re
      -0.14601453115483407             // im
    }, { 0.97865087181071841,          // re
      -0.14454529710384628             // im
    }, { 0.979092506991396,            // re
      -0.14307469987632043             // im
    }, { 0.97952962395060106,          // re
      -0.14160275334115208             // im
    }, { 0.97996221856597465,          // re
      -0.14012947137996185             // im
    }, { 0.98039028675780737,          // re
      -0.13865486788696441             // im
    }, { 0.98081382448907739,          // re
      -0.1371789567688379              // im
    }, { 0.98123282776548859,          // re
      -0.13570175194459197             // im
    }, { 0.98164729263550865,          // re
      -0.1342232673454371              // im
    }, { 0.9820572151904059,           // re
      -0.132743516914653               // im
    }, { 0.982462591564286,            // re
      -0.13126251460745744             // im
    }, { 0.98286341793412912,          // re
      -0.12978027439087406             // im
    }, { 0.98325969051982542,          // re
      -0.12829681024360107             // im
    }, { 0.98365140558421071,          // re
      -0.12681213615587933             // im
    }, { 0.98403855943310214,          // re
      -0.12532626612936026             // im
    }, { 0.98442114841533246,          // re
      -0.12383921417697434             // im
    }, { 0.98479916892278463,          // re
      -0.12235099432279808             // im
    }, { 0.98517261739042628,          // re
      -0.12086162060192247             // im
    }, { 0.98554149029634286,          // re
      -0.11937110706032017             // im
    }, { 0.98590578416177088,          // re
      -0.11787946775471364             // im
    }, { 0.98626549555113086,          // re
      -0.11638671675244185             // im
    }, { 0.98662062107205983,          // re
      -0.114892868131328               // im
    }, { 0.98697115737544316,          // re
      -0.11339793597954669             // im
    }, { 0.987317101155446,            // re
      -0.11190193439549131             // im
    }, { 0.9876584491495447,           // re
      -0.11040487748764059             // im
    }, { 0.98799519813855763,          // re
      -0.10890677937442586             // im
    }, { 0.9883273449466754,           // re
      -0.10740765418409773             // im
    }, { 0.98865488644149058,          // re
      -0.10590751605459331             // im
    }, { 0.98897781953402775,          // re
      -0.10440637913340219             // im
    }, { 0.9892961411787724,           // re
      -0.10290425757743348             // im
    }, { 0.98960984837369947,          // re
      -0.10140116555288203             // im
    }, { 0.98991893816030174,          // re
      -0.099897117235095353            // im
    }, { 0.990223407623618,            // re
      -0.098392126808439187            // im
    }, { 0.99052325389226037,          // re
      -0.096886208466164261            // im
    }, { 0.99081847413844115,          // re
      -0.095379376410272124            // im
    }, { 0.99110906557799971,          // re
      -0.093871644851381733            // im
    }, { 0.9913950254704289,           // re
      -0.092363028008594708            // im
    }, { 0.99167635111890085,          // re
      -0.090853540109361752            // im
    }, { 0.9919530398702916,           // re
      -0.089343195389348165            // im
    }, { 0.99222508911520768,          // re
      -0.087832008092300115            // im
    }, { 0.99249249628800917,          // re
      -0.086319992469909554            // im
    }, { 0.992755258866835,            // re
      -0.084807162781680365            // im
    }, { 0.993013374373626,            // re
      -0.083293533294793581            // im
    }, { 0.9932668403741487,           // re
      -0.081779118283973287            // im
    }, { 0.99351565447801815,          // re
      -0.080263932031351376            // im
    }, { 0.99375981433872052,          // re
      -0.078747988826333243            // im
    }, { 0.99399931765363492,          // re
      -0.077231302965462864            // im
    }, { 0.99423416216405569,          // re
      -0.07571388875228835             // im
    }, { 0.99446434565521324,          // re
      -0.07419576049722644             // im
    }, { 0.994689865956295,            // re
      -0.072676932517427947            // im
    }, { 0.9949107209404664,           // re
      -0.071157419136642558            // im
    }, { 0.99512690852488972,          // re
      -0.069637234685084135            // im
    }, { 0.99533842667074524,          // re
      -0.068116393499294936            // im
    }, { 0.99554527338324927,          // re
      -0.066594909922010892            // im
    }, { 0.99574744671167381,          // re
      -0.065072798302026044            // im
    }, { 0.99594494474936424,          // re
      -0.063550072994057724            // im
    }, { 0.99613776563375778,          // re
      -0.062026748358610481            // im
    }, { 0.996325907546401,            // re
      -0.060502838761841121            // im
    }, { 0.9965093687129668,           // re
      -0.0589783585754231              // im
    }, { 0.996688147403271,            // re
      -0.057453322176410852            // im
    }, { 0.99686224193128936,          // re
      -0.055927743947104695            // im
    }, { 0.99703165065517241,          // re
      -0.054401638274914496            // im
    }, { 0.99719637197726207,          // re
      -0.052875019552224428            // im
    }, { 0.99735640434410566,          // re
      -0.051347902176257024            // im
    }, { 0.99751174624647154,          // re
      -0.049820300548937865            // im
    }, { 0.99766239621936259,          // re
      -0.04829222907675905             // im
    }, { 0.99780835284203029,          // re
      -0.0467637021706438              // im
    }, { 0.99794961473798827,          // re
      -0.045234734245810357            // im
    }, { 0.998086180575025,            // re
      -0.0437053397216364              // im
    }, { 0.9982180490652165,           // re
      -0.042175533021522493            // im
    }, { 0.99834521896493866,          // re
      -0.040645328572756434            // im
    }, { 0.99846768907487871,          // re
      -0.039114740806376988            // im
    }, { 0.99858545824004652,          // re
      -0.037583784157038252            // im
    }, { 0.99869852534978576,          // re
      -0.036052473062872854            // im
    }, { 0.99880688933778394,          // re
      -0.034520821965356212            // im
    }, { 0.998910549182083,            // re
      -0.032988845309170151            // im
    }, { 0.99900950390508858,          // re
      -0.031456557542067089            // im
    }, { 0.99910375257357931,          // re
      -0.029923973114733143            // im
    }, { 0.99919329429871584,          // re
      -0.028391106480652278            // im
    }, { 0.99927812823604856,          // re
      -0.026857972095969785            // im
    }, { 0.99935825358552632,          // re
      -0.025324584419356384            // im
    }, { 0.999433669591504,            // re
      -0.0237909579118712              // im
    }, { 0.99950437554274862,          // re
      -0.02225710703682585             // im
    }, { 0.99957037077244726,          // re
      -0.020723046259647788            // im
    }, { 0.9996316546582128,           // re
      -0.019188790047744347            // im
    }, { 0.99968822662208945,          // re
      -0.017654352870365639            // im
    }, { 0.999740086130559,            // re
      -0.016119749198468526            // im
    }, { 0.99978723269454517,          // re
      -0.014584993504579938            // im
    }, { 0.99982966586941846,          // re
      -0.013050100262660824            // im
    }, { 0.99986738525500063,          // re
      -0.011515083947968987            // im
    }, { 0.99990039049556789,          // re
      -0.0099799590369230185           // im
    }, { 0.9999286812798549,           // re
      -0.0084447400069655419           // im
    }, { 0.999952257341057,            // re
      -0.0069094413364271358           // im
    }, { 0.99997111845683329,          // re
      -0.0053740775043891144           // im
    }, { 0.99998526444930858,          // re
      -0.0038386629905474315           // im
    }, { 0.99999469518507489,          // re
      -0.0023032122750758963           // im
    }, { 0.999999410575193,            // re
      -0.00076773983849006279          // im
    }, { 0.999999410575193,            // re
      0.00076773983849000153           // im
    }, { 0.99999469518507489,          // re
      0.0023032122750758352            // im
    }, { 0.99998526444930858,          // re
      0.0038386629905472593            // im
    }, { 0.99997111845683329,          // re
      0.0053740775043890536            // im
    }, { 0.999952257341057,            // re
      0.0069094413364270742            // im
    }, { 0.9999286812798549,           // re
      0.0084447400069654812            // im
    }, { 0.99990039049556789,          // re
      0.009979959036922845             // im
    }, { 0.99986738525500063,          // re
      0.011515083947968926             // im
    }, { 0.99982966586941846,          // re
      0.013050100262660761             // im
    }, { 0.99978723269454517,          // re
      0.014584993504579875             // im
    }, { 0.999740086130559,            // re
      0.016119749198468356             // im
    }, { 0.99968822662208945,          // re
      0.01765435287036558              // im
    }, { 0.9996316546582128,           // re
      0.019188790047744288             // im
    }, { 0.99957037077244726,          // re
      0.020723046259647725             // im
    }, { 0.99950437554274862,          // re
      0.02225710703682568              // im
    }, { 0.999433669591504,            // re
      0.023790957911871139             // im
    }, { 0.99935825358552632,          // re
      0.025324584419356321             // im
    }, { 0.99927812823604856,          // re
      0.026857972095969723             // im
    }, { 0.99919329429871584,          // re
      0.028391106480652108             // im
    }, { 0.99910375257357931,          // re
      0.02992397311473308              // im
    }, { 0.99900950390508858,          // re
      0.031456557542067026             // im
    }, { 0.998910549182083,            // re
      0.032988845309170088             // im
    }, { 0.99880688933778394,          // re
      0.034520821965356038             // im
    }, { 0.99869852534978576,          // re
      0.036052473062872792             // im
    }, { 0.99858545824004652,          // re
      0.03758378415703819              // im
    }, { 0.99846768907487871,          // re
      0.039114740806376926             // im
    }, { 0.99834521896493866,          // re
      0.04064532857275626              // im
    }, { 0.9982180490652165,           // re
      0.042175533021522431             // im
    }, { 0.998086180575025,            // re
      0.043705339721636344             // im
    }, { 0.99794961473798827,          // re
      0.045234734245810294             // im
    }, { 0.99780835284203029,          // re
      0.046763702170643635             // im
    }, { 0.99766239621936259,          // re
      0.048292229076758987             // im
    }, { 0.99751174624647154,          // re
      0.0498203005489378               // im
    }, { 0.99735640434410566,          // re
      0.051347902176256968             // im
    }, { 0.99719637197726207,          // re
      0.052875019552224255             // im
    }, { 0.99703165065517241,          // re
      0.054401638274914434             // im
    }, { 0.99686224193128936,          // re
      0.05592774394710464              // im
    }, { 0.99668814740327116,          // re
      0.05745332217641079              // im
    }, { 0.9965093687129668,           // re
      0.058978358575422926             // im
    }, { 0.996325907546401,            // re
      0.060502838761841066             // im
    }, { 0.99613776563375778,          // re
      0.062026748358610419             // im
    }, { 0.99594494474936424,          // re
      0.063550072994057669             // im
    }, { 0.99574744671167381,          // re
      0.065072798302025989             // im
    }, { 0.99554527338324927,          // re
      0.066594909922010725             // im
    }, { 0.99533842667074524,          // re
      0.068116393499294881             // im
    }, { 0.99512690852488972,          // re
      0.069637234685084065             // im
    }, { 0.9949107209404664,           // re
      0.0711574191366425               // im
    }, { 0.99468986595629516,          // re
      0.072676932517427781             // im
    }, { 0.99446434565521324,          // re
      0.074195760497226385             // im
    }, { 0.99423416216405569,          // re
      0.0757138887522883               // im
    }, { 0.99399931765363492,          // re
      0.0772313029654628               // im
    }, { 0.99375981433872052,          // re
      0.078747988826333076             // im
    }, { 0.99351565447801815,          // re
      0.0802639320313513               // im
    }, { 0.9932668403741487,           // re
      0.081779118283973232             // im
    }, { 0.993013374373626,            // re
      0.083293533294793526             // im
    }, { 0.992755258866835,            // re
      0.0848071627816802               // im
    }, { 0.99249249628800928,          // re
      0.0863199924699095               // im
    }, { 0.99222508911520768,          // re
      0.087832008092300046             // im
    }, { 0.9919530398702916,           // re
      0.08934319538934811              // im
    }, { 0.99167635111890085,          // re
      0.090853540109361586             // im
    }, { 0.991395025470429,            // re
      0.092363028008594653             // im
    }, { 0.99110906557799971,          // re
      0.093871644851381664             // im
    }, { 0.99081847413844115,          // re
      0.095379376410272068             // im
    }, { 0.99052325389226037,          // re
      0.0968862084661641               // im
    }, { 0.990223407623618,            // re
      0.098392126808439132             // im
    }, { 0.98991893816030174,          // re
      0.0998971172350953               // im
    }, { 0.98960984837369947,          // re
      0.10140116555288198              // im
    }, { 0.98929614117877251,          // re
      0.10290425757743331              // im
    }, { 0.98897781953402786,          // re
      0.10440637913340213              // im
    }, { 0.98865488644149058,          // re
      0.10590751605459325              // im
    }, { 0.9883273449466754,           // re
      0.10740765418409766              // im
    }, { 0.98799519813855774,          // re
      0.10890677937442568              // im
    }, { 0.9876584491495447,           // re
      0.11040487748764054              // im
    }, { 0.987317101155446,            // re
      0.11190193439549126              // im
    }, { 0.98697115737544316,          // re
      0.11339793597954663              // im
    }, { 0.98662062107205983,          // re
      0.11489286813132783              // im
    }, { 0.98626549555113086,          // re
      0.11638671675244178              // im
    }, { 0.98590578416177088,          // re
      0.11787946775471358              // im
    }, { 0.98554149029634286,          // re
      0.11937110706032011              // im
    }, { 0.98517261739042628,          // re
      0.12086162060192229              // im
    }, { 0.98479916892278463,          // re
      0.12235099432279803              // im
    }, { 0.98442114841533246,          // re
      0.12383921417697427              // im
    }, { 0.98403855943310214,          // re
      0.12532626612936021              // im
    }, { 0.98365140558421071,          // re
      0.12681213615587916              // im
    }, { 0.98325969051982542,          // re
      0.128296810243601                // im
    }, { 0.98286341793412912,          // re
      0.129780274390874                // im
    }, { 0.982462591564286,            // re
      0.13126251460745739              // im
    }, { 0.9820572151904059,           // re
      0.13274351691465294              // im
    }, { 0.98164729263550865,          // re
      0.13422326734543694              // im
    }, { 0.9812328277654887,           // re
      0.13570175194459189              // im
    }, { 0.98081382448907739,          // re
      0.13717895676883782              // im
    }, { 0.98039028675780737,          // re
      0.13865486788696435              // im
    }, { 0.97996221856597476,          // re
      0.14012947137996168              // im
    }, { 0.97952962395060106,          // re
      0.14160275334115202              // im
    }, { 0.979092506991396,            // re
      0.14307469987632038              // im
    }, { 0.97865087181071853,          // re
      0.1445452971038462               // im
    }, { 0.97820472257353752,          // re
      0.1460145311548339               // im
    }, { 0.9777540634873938,           // re
      0.1474823881732438               // im
    }, { 0.97729889880235876,          // re
      0.14894885431602237              // im
    }, { 0.97683923281099594,          // re
      0.15041391575323351              // im
    }, { 0.97637506984831912,          // re
      0.1518775586681885               // im
    }, { 0.97590641429175251,          // re
      0.15333976925757647              // im
    }, { 0.97543327056108886,          // re
      0.15480053373159428              // im
    }, { 0.974955643118448,            // re
      0.156259838314077                // im
    }, { 0.97447353646823454,          // re
      0.15771766924262764              // im
    }, { 0.97398695515709588,          // re
      0.15917401276874696              // im
    }, { 0.97349590377387862,          // re
      0.16062885515796282              // im
    }, { 0.97300038694958624,          // re
      0.16208218268996033              // im
    }, { 0.97250040935733428,          // re
      0.16353398165871072              // im
    }, { 0.97199597571230711,          // re
      0.16498423837260098              // im
    }, { 0.97148709077171325,          // re
      0.16643293915456236              // im
    }, { 0.97097375933474028,          // re
      0.16788007034220023              // im
    }, { 0.97045598624251017,          // re
      0.16932561828792225              // im
    }, { 0.96993377637803246,          // re
      0.17076956935906745              // im
    }, { 0.96940713466615991,          // re
      0.1722119099380344               // im
    }, { 0.96887606607354027,          // re
      0.17365262642241008              // im
    }, { 0.96834057560857079,          // re
      0.17509170522509795              // im
    }, { 0.96780066832135025,          // re
      0.17652913277444621              // im
    }, { 0.96725634930363169,          // re
      0.1779648955143753               // im
    }, { 0.96670762368877416,          // re
      0.17939897990450654              // im
    }, { 0.96615449665169451,          // re
      0.18083137242028921              // im
    }, { 0.96559697340881834,          // re
      0.18226205955312852              // im
    }, { 0.965035059218031,            // re
      0.18369102781051236              // im
    }, { 0.96446875937862808,          // re
      0.1851182637161394               // im
    }, { 0.963898079231265,            // re
      0.18654375381004557              // im
    }, { 0.96332302415790749,          // re
      0.18796748464873134              // im
    }, { 0.9627435995817798,           // re
      0.189389442805288                // im
    }, { 0.96215981096731418,          // re
      0.19080961486952497              // im
    }, { 0.96157166382009929,          // re
      0.19222798744809583              // im
    }, { 0.96097916368682812,          // re
      0.19364454716462473              // im
    }, { 0.96038231615524572,          // re
      0.19505928065983263              // im
    }, { 0.95978112685409678,          // re
      0.19647217459166297              // im
    }, { 0.95917560145307235,          // re
      0.19788321563540789              // im
    }, { 0.95856574566275565,          // re
      0.19929239048383379              // im
    }, { 0.95795156523456981,          // re
      0.20069968584730674              // im
    }, { 0.957333065960722,            // re
      0.20210508845391764              // im
    }, { 0.95671025367415008,          // re
      0.20350858504960778              // im
    }, { 0.95608313424846669,          // re
      0.20491016239829365              // im
    }, { 0.95545171359790426,          // re
      0.2063098072819918               // im
    }, { 0.95481599767725922,          // re
      0.20770750650094316              // im
    }, { 0.95417599248183571,          // re
      0.20910324687373821              // im
    }, { 0.95353170404738929,          // re
      0.21049701523744052              // im
    }, { 0.95288313845006978,          // re
      0.21188879844771158              // im
    }, { 0.95223030180636392,          // re
      0.21327858337893427              // im
    }, { 0.95157320027303793,          // re
      0.21466635692433689              // im
    }, { 0.95091184004707918,          // re
      0.21605210599611674              // im
    }, { 0.95024622736563813,          // re
      0.2174358175255634               // im
    }, { 0.949576368505969,            // re
      0.21881747846318214              // im
    }, { 0.94890226978537084,          // re
      0.2201970757788172               // im
    }, { 0.94822393756112822,          // re
      0.22157459646177366              // im
    }, { 0.9475413782304507,           // re
      0.22295002752094165              // im
    }, { 0.94685459823041307,          // re
      0.22432335598491776              // im
    }, { 0.946163604037894,            // re
      0.22569456890212786              // im
    }, { 0.94546840216951566,          // re
      0.22706365334094894              // im
    }, { 0.94476899918158186,          // re
      0.22843059638983138              // im
    }, { 0.94406540167001607,          // re
      0.22979538515742048              // im
    }, { 0.94335761627029979,          // re
      0.23115800677267831              // im
    }, { 0.94264564965740938,          // re
      0.23251844838500435              // im
    }, { 0.94192950854575352,          // re
      0.23387669716435777              // im
    }, { 0.94120919968910965,          // re
      0.23523274030137775              // im
    }, { 0.94048472988056,             // re
      0.23658656500750441              // im
    }, { 0.93975610595242842,          // re
      0.23793815851509939              // im
    }, { 0.93902333477621514,          // re
      0.23928750807756635              // im
    }, { 0.93828642326253209,          // re
      0.24063460096947106              // im
    }, { 0.93754537836103813,          // re
      0.24197942448666179              // im
    }, { 0.936800207060373,            // re
      0.24332196594638808              // im
    }, { 0.936050916388092,            // re
      0.24466221268742178              // im
    }, { 0.935297513410599,            // re
      0.24600015207017548              // im
    }, { 0.93454000523308012,          // re
      0.24733577147682204              // im
    }, { 0.933778398999437,            // re
      0.2486690583114135               // im
    }, { 0.93301270189221941,          // re
      0.24999999999999989              // im
    }, { 0.93224292113255669,          // re
      0.25132858399074787              // im
    }, { 0.93146906398009066,          // re
      0.25265479775405908              // im
    }, { 0.93069113773290646,          // re
      0.25397862878268829              // im
    }, { 0.92990914972746463,          // re
      0.255300064591861                // im
    }, { 0.92912310733853065,          // re
      0.25661909271939193              // im
    }, { 0.92833301797910639,          // re
      0.25793570072580208              // im
    }, { 0.92753888910035964,          // re
      0.259249876194436                // im
    }, { 0.92674072819155418,          // re
      0.26056160673157908              // im
    }, { 0.92593854277997911,          // re
      0.26187087996657432              // im
    }, { 0.92513234043087744,          // re
      0.26317768355193893              // im
    }, { 0.92432212874737552,          // re
      0.26448200516348125              // im
    }, { 0.92350791537041066,          // re
      0.26578383250041587              // im
    }, { 0.92268970797865935,          // re
      0.267083153285481                // im
    }, { 0.9218675142884647,           // re
      0.26837995526505343              // im
    }, { 0.92104134205376387,          // re
      0.26967422620926423              // im
    }, { 0.9202111990660149,           // re
      0.2709659539121142               // im
    }, { 0.91937709315412308,          // re
      0.27225512619158887              // im
    }, { 0.91853903218436717,          // re
      0.27354173088977346              // im
    }, { 0.91769702406032527,          // re
      0.27482575587296765              // im
    }, { 0.91685107672280064,          // re
      0.27610718903179943              // im
    }, { 0.91600119814974568,          // re
      0.27738601828134024              // im
    }, { 0.91514739635618825,          // re
      0.27866223156121817              // im
    }, { 0.91428967939415462,          // re
      0.2799358168357321               // im
    }, { 0.91342805535259475,          // re
      0.28120676209396506              // im
    }, { 0.912562532357305,            // re
      0.28247505534989742              // im
    }, { 0.91169311857085233,          // re
      0.28374068464252017              // im
    }, { 0.91081982219249658,          // re
      0.28500363803594775              // im
    }, { 0.90994265145811382,          // re
      0.28626390361952969              // im
    }, { 0.90906161464011825,          // re
      0.28752146950796459              // im
    }, { 0.90817672004738415,          // re
      0.28877632384141083              // im
    }, { 0.90728797602516786,          // re
      0.290028454785599                // im
    }, { 0.90639539095502886,          // re
      0.29127785053194355              // im
    }, { 0.90549897325475071,          // re
      0.29252449929765373              // im
    }, { 0.90459873137826152,          // re
      0.2937683893258452               // im
    }, { 0.90369467381555468,          // re
      0.29500950888565081              // im
    }, { 0.90278680909260867,          // re
      0.29624784627233058              // im
    }, { 0.90187514577130612,          // re
      0.2974833898073832               // im
    }, { 0.90095969244935348,          // re
      0.29871612783865531              // im
    }, { 0.90004045776020014,          // re
      0.29994604874045189              // im
    }, { 0.89911745037295665,          // re
      0.30117314091364533              // im
    }, { 0.89819067899231309,          // re
      0.30239739278578559              // im
    }, { 0.89726015235845691,          // re
      0.30361879281120852              // im
    }, { 0.8963258792469907,           // re
      0.30483732947114561              // im
    }, { 0.89538786846884921,          // re
      0.30605299127383145              // im
    }, { 0.89444612887021657,          // re
      0.30726576675461342              // im
    }, { 0.89350066933244232,          // re
      0.30847564447605896              // im
    }, { 0.89255149877195783,          // re
      0.30968261302806382              // im
    }, { 0.89159862614019314,          // re
      0.31088666102795931              // im
    }, { 0.89064206042349081,          // re
      0.31208777712062                 // im
    }, { 0.88968181064302265,          // re
      0.31328594997857068              // im
    }, { 0.8887178858547039,           // re
      0.31448116830209305              // im
    }, { 0.88775029514910808,          // re
      0.3156734208193327               // im
    }, { 0.88677904765138171,          // re
      0.31686269628640451              // im
    }, { 0.88580415252115685,          // re
      0.31804898348749983              // im
    }, { 0.88482561895246614,          // re
      0.3192322712349917               // im
    }, { 0.88384345617365567,          // re
      0.32041254836954014              // im
    }, { 0.88285767344729749,          // re
      0.32158980376019786              // im
    }, { 0.88186828007010276,          // re
      0.32276402630451484              // im
    }, { 0.88087528537283422,          // re
      0.32393520492864325              // im
    }, { 0.8798786987202174,           // re
      0.325103328587442                // im
    }, { 0.87887852951085343,          // re
      0.32626838626458032              // im
    }, { 0.87787478717712919,          // re
      0.32743036697264249              // im
    }, { 0.87686748118512925,          // re
      0.32858925975323089              // im
    }, { 0.87585662103454631,          // re
      0.32974505367706952              // im
    }, { 0.87484221625859149,          // re
      0.330897737844107                // im
    }, { 0.87382427642390459,          // re
      0.33204730138361943              // im
    }, { 0.87280281113046376,          // re
      0.33319373345431297              // im
    }, { 0.871777830011495,            // re
      0.3343370232444261               // im
    }, { 0.87074934273338156,          // re
      0.33547715997183108              // im
    }, { 0.86971735899557234,          // re
      0.33661413288413644              // im
    }, { 0.86868188853049055,          // re
      0.33774793125878788              // im
    }, { 0.86764294110344231,          // re
      0.33887854440316945              // im
    }, { 0.86660052651252373,          // re
      0.34000596165470454              // im
    }, { 0.86555465458852954,          // re
      0.34113017238095622              // im
    }, { 0.8645053351948595,           // re
      0.34225116597972777              // im
    }, { 0.86345257822742572,          // re
      0.34336893187916256              // im
    }, { 0.86239639361456,             // re
      0.34448345953784332              // im
    }, { 0.86133679131691876,          // re
      0.34559473844489236              // im
    }, { 0.86027378132739019,          // re
      0.34670275812007018              // im
    }, { 0.85920737367099964,          // re
      0.34780750811387445              // im
    }, { 0.8581375784048153,           // re
      0.34890897800763848              // im
    }, { 0.85706440561785313,          // re
      0.35000715741362948              // im
    }, { 0.85598786543098182,          // re
      0.35110203597514661              // im
    }, { 0.854907967996827,            // re
      0.35219360336661876              // im
    }, { 0.85382472349967653,          // re
      0.35328184929370132              // im
    }, { 0.85273814215538279,          // re
      0.35436676349337415              // im
    }, { 0.8516482342112679,           // re
      0.35544833573403778              // im
    }, { 0.8505550099460264,           // re
      0.3565265558156101               // im
    }, { 0.84945847966962806,          // re
      0.35760141356962249              // im
    }, { 0.84835865372322106,          // re
      0.35867289885931575              // im
    }, { 0.84725554247903467,          // re
      0.3597410015797356               // im
    }, { 0.84614915634028076,          // re
      0.36080571165782821              // im
    }, { 0.845039505741056,            // re
      0.3618670190525351               // im
    }, { 0.84392660114624385,          // re
      0.36292491375488739              // im
    }, { 0.84281045305141555,          // re
      0.36397938578810096              // im
    }, { 0.84169107198273041,          // re
      0.36503042520767021              // im
    }, { 0.84056846849683819,          // re
      0.36607802210146151              // im
    }, { 0.83944265318077782,          // re
      0.36712216658980723              // im
    }, { 0.83831363665187886,          // re
      0.36816284882559858              // im
    }, { 0.83718142955766039,          // re
      0.36920005899437841              // im
    }, { 0.83604604257573134,          // re
      0.37023378731443429              // im
    }, { 0.83490748641368961,          // re
      0.37126402403688974              // im
    }, { 0.83376577180902089,          // re
      0.37229075944579743              // im
    }, { 0.83262090952899714,          // re
      0.37331398385822984              // im
    }, { 0.8314729103705758,           // re
      0.37433368762437108              // im
    }, { 0.83032178516029731,          // re
      0.37534986112760765              // im
    }, { 0.82916754475418342,          // re
      0.37636249478461936              // im
    }, { 0.82801020003763459,          // re
      0.37737157904546936              // im
    }, { 0.82684976192532711,          // re
      0.37837710439369476              // im
    }, { 0.82568624136111113,          // re
      0.37937906134639543              // im
    }, { 0.82451964931790611,          // re
      0.38037744045432464              // im
    }, { 0.82334999679759813,          // re
      0.38137223230197725              // im
    }, { 0.82217729483093616,          // re
      0.38236342750767893              // im
    }, { 0.82100155447742784,          // re
      0.3833510167236745               // im
    }, { 0.81982278682523491,          // re
      0.38433499063621612              // im
    }, { 0.81864100299106934,          // re
      0.3853153399656512               // im
    }, { 0.81745621412008762,          // re
      0.38629205546650974              // im
    }, { 0.81626843138578686,          // re
      0.38726512792759155              // im
    }, { 0.815077665989898,            // re
      0.38823454817205327              // im
    }, { 0.81388392916228081,          // re
      0.38920030705749487              // im
    }, { 0.81268723216081851,          // re
      0.39016239547604586              // im
    }, { 0.81148758627131068,          // re
      0.39112080435445107              // im
    }, { 0.81028500280736759,          // re
      0.39207552465415629              // im
    }, { 0.80907949311030269,          // re
      0.39302654737139364              // im
    }, { 0.80787106854902646,          // re
      0.39397386353726638              // im
    }, { 0.80665974051993916,          // re
      0.39491746421783319              // im
    }, { 0.80544552044682238,          // re
      0.39585734051419308              // im
    }, { 0.80422841978073234,          // re
      0.39679348356256872              // im
    }, { 0.80300844999989152,          // re
      0.39772588453439039              // im
    }, { 0.80178562260958031,          // re
      0.398654534636379                // im
    }, { 0.80055994914202877,          // re
      0.39957942511062933              // im
    }, { 0.79933144115630772,          // re
      0.40050054723469219              // im
    }, { 0.79810011023821925,          // re
      0.40141789232165709              // im
    }, { 0.79686596800018861,          // re
      0.402331451720234                // im
    }, { 0.79562902608115393,          // re
      0.40324121681483455              // im
    }, { 0.79438929614645626,          // re
      0.40414717902565411              // im
    }, { 0.7931467898877298,           // re
      0.40504932980875208              // im
    }, { 0.79190151902279182,          // re
      0.40594766065613275              // im
    }, { 0.79065349529553219,          // re
      0.40684216309582522              // im
    }, { 0.78940273047580223,          // re
      0.40773282869196364              // im
    }, { 0.7881492363593039,           // re
      0.40861964904486664              // im
    }, { 0.78689302476747858,          // re
      0.40950261579111663              // im
    }, { 0.78563410754739615,          // re
      0.41038172060363814              // im
    }, { 0.78437249657164188,          // re
      0.4112569551917773               // im
    }, { 0.78310820373820567,          // re
      0.41212831130137934              // im
    }, { 0.78184124097036956,          // re
      0.41299578071486648              // im
    }, { 0.78057162021659487,          // re
      0.41385935525131579              // im
    }, { 0.77929935345041035,          // re
      0.41471902676653594              // im
    }, { 0.77802445267029807,          // re
      0.41557478715314428              // im
    }, { 0.77674692989958127,          // re
      0.41642662834064326              // im
    }, { 0.77546679718631106,          // re
      0.4172745422954961               // im
    }, { 0.77418406660315175,          // re
      0.41811852102120334              // im
    }, { 0.77289875024726773,          // re
      0.41895855655837771              // im
    }, { 0.77161086024020942,          // re
      0.41979464098481939              // im
    }, { 0.77032040872779883,          // re
      0.42062676641559055              // im
    }, { 0.769027407880015,            // re
      0.42145492500308984              // im
    }, { 0.76773186989087883,          // re
      0.42227910893712645              // im
    }, { 0.766433806978339,            // re
      0.42309931044499377              // im
    }, { 0.76513323138415612,          // re
      0.42391552179154229              // im
    }, { 0.763830155373787,            // re
      0.42472773527925323              // im
    }, { 0.76252459123626992,          // re
      0.42553594324831062              // im
    }, { 0.76121655128410759,          // re
      0.4263401380766737               // im
    }, { 0.75990604785315186,          // re
      0.427140312180149                // im
    }, { 0.75859309330248736,          // re
      0.42793645801246127              // im
    }, { 0.75727770001431449,          // re
      0.42872856806532544              // im
    }, { 0.75595988039383266,          // re
      0.42951663486851693              // im
    }, { 0.7546396468691241,           // re
      0.43030065098994191              // im
    }, { 0.7533170118910355,           // re
      0.43108060903570811              // im
    }, { 0.75199198793306143,          // re
      0.43185650165019379              // im
    }, { 0.75066458749122633,          // re
      0.43262832151611774              // im
    }, { 0.74933482308396682,          // re
      0.43339606135460779              // im
    }, { 0.74800270725201368,          // re
      0.4341597139252697               // im
    }, { 0.74666825255827329,          // re
      0.43491927202625535              // im
    }, { 0.7453314715877094,           // re
      0.43567472849433092              // im
    }, { 0.74399237694722431,          // re
      0.436426076204944                // im
    }, { 0.74265098126554052,          // re
      0.43717330807229104              // im
    }, { 0.74130729719308064,          // re
      0.43791641704938422              // im
    }, { 0.73996133740184888,          // re
      0.43865539612811794              // im
    }, { 0.73861311458531109,          // re
      0.43939023833933455              // im
    }, { 0.73726264145827536,          // re
      0.44012093675289055              // im
    }, { 0.735909930756772,            // re
      0.4408474844777216               // im
    }, { 0.73455499523793355,          // re
      0.44156987466190778              // im
    }, { 0.73319784767987373,          // re
      0.44228810049273809              // im
    }, { 0.73183850088156865,          // re
      0.44300215519677433              // im
    }, { 0.73047696766273384,          // re
      0.44371203203991566              // im
    }, { 0.7291132608637052,           // re
      0.44441772432746168              // im
    }, { 0.72774739334531713,          // re
      0.44511922540417576              // im
    }, { 0.72637937798878094,          // re
      0.44581652865434751              // im
    }, { 0.7250092276955642,           // re
      0.44650962750185547              // im
    }, { 0.72363695538726847,          // re
      0.44719851541022909              // im
    }, { 0.7222625740055072,           // re
      0.44788318588271031              // im
    }, { 0.720886096511785,            // re
      0.44856363246231451              // im
    }, { 0.71950753588737371,          // re
      0.44923984873189216              // im
    }, { 0.71812690513319088,          // re
      0.44991182831418863              // im
    }, { 0.71674421726967719,          // re
      0.4505795648719047               // im
    }, { 0.71535948533667315,          // re
      0.45124305210775628              // im
    }, { 0.713972722393297,            // re
      0.45190228376453362              // im
    }, { 0.71258394151782056,          // re
      0.45255725362516053              // im
    }, { 0.71119315580754627,          // re
      0.453207955512753                // im
    }, { 0.70980037837868437,          // re
      0.45385438329067712              // im
    }, { 0.70840562236622828,          // re
      0.45449653086260744              // im
    }, { 0.70700890092383051,          // re
      0.45513439217258422              // im
    }, { 0.70561022722367994,          // re
      0.45576796120507057              // im
    }, { 0.70420961445637609,          // re
      0.45639723198500909              // im
    }, { 0.70280707583080593,          // re
      0.4570221985778784               // im
    }, { 0.70140262457401858,          // re
      0.45764285508974889              // im
    }, { 0.69999627393110064,          // re
      0.45825919566733864              // im
    }, { 0.69858803716505191,          // re
      0.45887121449806806              // im
    }, { 0.6971779275566593,           // re
      0.4594789058101153               // im
    }, { 0.69576595840437239,          // re
      0.46008226387247048              // im
    }, { 0.69435214302417758,          // re
      0.4606812829949895               // im
    }, { 0.69293649474947283,          // re
      0.46127595752844808              // im
    }, { 0.69151902693094158,          // re
      0.46186628186459472              // im
    }, { 0.690099752936427,            // re
      0.46245225043620386              // im
    }, { 0.68867868615080619,          // re
      0.463033857717128                // im
    }, { 0.68725583997586315,          // re
      0.46361109822235053              // im
    }, { 0.68583122783016381,          // re
      0.46418396650803628              // im
    }, { 0.68440486314892768,          // re
      0.46475245717158425              // im
    }, { 0.68297675938390268,          // re
      0.46531656485167749              // im
    }, { 0.68154693000323741,          // re
      0.46587628422833421              // im
    }, { 0.68011538849135422,          // re
      0.46643161002295774              // im
    }, { 0.67868214834882279,          // re
      0.46698253699838638              // im
    }, { 0.67724722309223151,          // re
      0.46752905995894278              // im
    }, { 0.67581062625406108,          // re
      0.468071173750483                // im
    }, { 0.67437237138255679,          // re
      0.46860887326044487              // im
    }, { 0.67293247204160023,          // re
      0.4691421534178965               // im
    }, { 0.67149094181058155,          // re
      0.46967100919358407              // im
    }, { 0.67004779428427164,          // re
      0.470195435599979                // im
    }, { 0.66860304307269369,          // re
      0.47071542769132541              // im
    }, { 0.667156701800995,            // re
      0.47123098056368629              // im
    }, { 0.66570878410931811,          // re
      0.47174208935499007              // im
    }, { 0.66425930365267261,          // re
      0.47224874924507643              // im
    }, { 0.66280827410080667,          // re
      0.47275095545574164              // im
    }, { 0.66135570913807706,          // re
      0.47324870325078361              // im
    }, { 0.659901622463321,            // re
      0.47374198793604688              // im
    }, { 0.65844602778972616,          // re
      0.47423080485946645              // im
    }, { 0.65698893884470255,          // re
      0.47471514941111187              // im
    }, { 0.65553036936975173,          // re
      0.4751950170232308               // im
    }, { 0.65407033312033835,          // re
      0.47567040317029186              // im
    }, { 0.65260884386575924,          // re
      0.47614130336902755              // im
    }, { 0.65114591538901512,          // re
      0.47660771317847628              // im
    }, { 0.649681561486679,            // re
      0.47706962820002441              // im
    }, { 0.64821579596876711,          // re
      0.47752704407744784              // im
    }, { 0.64674863265860794,          // re
      0.47797995649695285              // im
    }, { 0.64528008539271287,          // re
      0.47842836118721688              // im
    }, { 0.6438101680206445,           // re
      0.47887225391942889              // im
    }, { 0.64233889440488712,          // re
      0.47931163050732911              // im
    }, { 0.64086627842071486,          // re
      0.47974648680724868              // im
    }, { 0.63939233395606221,          // re
      0.48017681871814849              // im
    }, { 0.63791707491139171,          // re
      0.48060262218165806              // im
    }, { 0.63644051519956357,          // re
      0.4810238931821138               // im
    }, { 0.63496266874570451,          // re
      0.48144062774659685              // im
    }, { 0.633483549487076,            // re
      0.48185282194497042              // im
    }, { 0.632003171372943,            // re
      0.482260471889917                // im
    }, { 0.63052154836444285,          // re
      0.4826635737369751               // im
    }, { 0.62903869443445259,          // re
      0.48306212368457535              // im
    }, { 0.627554623567459,            // re
      0.48345611797407617              // im
    }, { 0.62606934975942408,          // re
      0.48384555288979975              // im
    }, { 0.62458288701765563,          // re
      0.48423042475906658              // im
    }, { 0.6230952493606734,           // re
      0.48461072995223042              // im
    }, { 0.62160645081807786,          // re
      0.48498646488271235              // im
    }, { 0.62011650543041752,          // re
      0.48535762600703464              // im
    }, { 0.61862542724905611,          // re
      0.48572420982485409              // im
    }, { 0.61713323033604128,          // re
      0.48608621287899528              // im
    }, { 0.61563992876397022,          // re
      0.48644363175548294              // im
    }, { 0.61414553661585913,          // re
      0.48679646308357416              // im
    }, { 0.61265006798500821,          // re
      0.48714470353579031              // im
    }, { 0.61115353697487018,          // re
      0.48748834982794836              // im
    }, { 0.60965595769891667,          // re
      0.48782739871919184              // im
    }, { 0.6081573442805055,           // re
      0.48816184701202142              // im
    }, { 0.60665771085274689,          // re
      0.488491691552325                // im
    }, { 0.60515707155837106,          // re
      0.48881692922940756              // im
    }, { 0.60365544054959386,          // re
      0.4891375569760204               // im
    }, { 0.6021528319879843,           // re
      0.48945357176839016              // im
    }, { 0.60064926004433006,          // re
      0.48976497062624724              // im
    }, { 0.5991447388985045,           // re
      0.490071750612854                // im
    }, { 0.59763928273933253,          // re
      0.4903739088350324               // im
    }, { 0.5961329057644571,           // re
      0.49067144244319133              // im
    }, { 0.5946256221802052,           // re
      0.4909643486313533               // im
    }, { 0.5931174462014539,           // re
      0.49125262463718128              // im
    }, { 0.59160839205149574,          // re
      0.49153626774200443              // im
    }, { 0.59009847396190618,          // re
      0.49181527527084362              // im
    }, { 0.58858770617240741,          // re
      0.49208964459243726              // im
    }, { 0.5870761029307352,           // re
      0.49235937311926542              // im
    }, { 0.58556367849250435,          // re
      0.49262445830757462              // im
    }, { 0.58405044712107423,          // re
      0.49288489765740184              // im
    }, { 0.582536423087414,            // re
      0.49314068871259792              // im
    }, { 0.58102162066996876,          // re
      0.49339182906085066              // im
    }, { 0.5795060541545235,           // re
      0.493638316333708                // im
    }, { 0.57798973783407037,          // re
      0.49388014820659981              // im
    }, { 0.576472686008672,            // re
      0.49411732239886008              // im
    }, { 0.57495491298532764,          // re
      0.49434983667374865              // im
    }, { 0.573436433077838,            // re
      0.49457768883847181              // im
    }, { 0.57191726060667025,          // re
      0.49480087674420331              // im
    }, { 0.57039740989882293,          // re
      0.49501939828610464              // im
    }, { 0.56887689528769114,          // re
      0.49523325140334473              // im
    }, { 0.56735573111293047,          // re
      0.49544243407911942              // im
    }, { 0.56583393172032348,          // re
      0.49564694434067058              // im
    }, { 0.56431151146164238,          // re
      0.49584678025930456              // im
    }, { 0.562788484694515,            // re
      0.49604193995041052              // im
    }, { 0.56126486578228918,          // re
      0.49623242157347808              // im
    }, { 0.55974066909389686,          // re
      0.49641822333211494              // im
    }, { 0.55821590900371887,          // re
      0.49659934347406332              // im
    }, { 0.55669059989144976,          // re
      0.49677578029121705              // im
    }, { 0.55516475614196126,          // re
      0.49694753211963733              // im
    }, { 0.5536383921451673,           // re
      0.49711459733956842              // im
    }, { 0.55211152229588867,          // re
      0.49727697437545315              // im
    }, { 0.5505841609937161,           // re
      0.49743466169594758              // im
    }, { 0.54905632264287552,          // re
      0.49758765781393544              // im
    }, { 0.54752802165209147,          // re
      0.49773596128654229              // im
    }, { 0.54599927243445168,          // re
      0.49787957071514904              // im
    }, { 0.54447008940727126,          // re
      0.49801848474540511              // im
    }, { 0.54294048699195607,          // re
      0.49815270206724127              // im
    }, { 0.54141047961386723,          // re
      0.498282221414882                // im
    }, { 0.5398800817021856,           // re
      0.49840704156685728              // im
    }, { 0.53834930768977418,          // re
      0.49852716134601432              // im
    }, { 0.53681817201304349,          // re
      0.49864257961952863              // im
    }, { 0.53528668911181443,          // re
      0.49875329529891443              // im
    }, { 0.53375487342918282,          // re
      0.49885930734003536              // im
    }, { 0.53222273941138265,          // re
      0.49896061474311387              // im
    }, { 0.5306903015076504,           // re
      0.4990572165527411               // im
    }, { 0.52915757417008769,          // re
      0.49914911185788546              // im
    }, { 0.52762457185352685,          // re
      0.49923629979190148              // im
    }, { 0.52609130901539269,          // re
      0.499318779532538                // im
    }, { 0.524557800115567,            // re
      0.4993965503019458               // im
    }, { 0.52302405961625231,          // re
      0.49946961136668488              // im
    }, { 0.52149010198183532,          // re
      0.49953796203773176              // im
    }, { 0.51995594167875037,          // re
      0.49960160167048534              // im
    }, { 0.51842159317534309,          // re
      0.49966052966477364              // im
    }, { 0.516887070941734,            // re
      0.499714745464859                // im
    }, { 0.51535238944968254,          // re
      0.49976424855944357              // im
    }, { 0.51381756317244942,          // re
      0.49980903848167391              // im
    }, { 0.512282606584661,            // re
      0.49984911480914562              // im
    }, { 0.51074753416217256,          // re
      0.49988447716390727              // im
    }, { 0.50921236038193185,          // re
      0.49991512521246384              // im
    }, { 0.5076770997218425,           // re
      0.49994105866578                 // im
    }, { 0.50614176666062749,          // re
      0.49996227727928272              // im
    }, { 0.5046063756776924,           // re
      0.49997878085286374              // im
    }, { 0.50307094125298957,          // re
      0.49999056923088125              // im
    }, { 0.50153547786688046,          // re
      0.49999764230216159              // im
    }, { 0.50000000000000011,          // re
      0.5                              // im
    } };

  // IRFFT    Inverse fft of a conjugate symmetric spectrum X=(Y,N,D)
  //
  //  Inputs:  Y(M)   The first half of a complex spectrum
  //           N      The number of output points to generate (default: 2M-2)
  //           D      The dimension along which to perorm the transform
  //                  (default: first non-singleton dimension of Y)
  //
  //  Outputs: X(N)   Real inverse dft of Y
  //
  //  This routine calculates the inverse DFT of a conjugate-symmetric to give a real-valued 
  //  output of dimension N. Only the first half of the spectrum need be supplied: if N is even, 
  //  this includes the Nyquist term and is of dimension M=N/2 + 1 whereas if N is odd then there is 
  //  no Nyquist term and the input is of dimension M=(N+1)/2.
  //  Note that the default value of N is always even so that N must be given explicitly 
  //  if it is odd.
  //
  //  See also the forward transform: RFFT
  //       Copyright (C) Mike Brookes 2009
  //       Version: $Id: irfft.m 2460 2012-10-29 22:20:45Z dmb $
  //
  //    VOICEBOX is a MATLAB toolbox for speech processing.
  //    Home page: http://www.ee.ic.ac.uk/hp/staff/dmb/voicebox/voicebox.html
  //
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  //    This program is free software; you can redistribute it and/or modify
  //    it under the terms of the GNU General Public License as published by
  //    the Free Software Foundation; either version 2 of the License, or
  //    (at your option) any later version.
  //
  //    This program is distributed in the hope that it will be useful,
  //    but WITHOUT ANY WARRANTY; without even the implied warranty of
  //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //    GNU General Public License for more details.
  //
  //    You can obtain a copy of the GNU General Public License from
  //    http://www.gnu.org/copyleft/gpl.html or by writing to
  //    Free Software Foundation, Inc.,675 Mass Ave, Cambridge, MA 02139, USA.
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  //  number of fft's to do
  //  expected input length
  //  even output length
  //  force nyquist element real
  //   t=[cumprod([-0.5i; exp(2i*pi/n)*ones(m-2,1)]); 0.5i];
  std::memcpy(&b_x[0], &y[0], 1024U * sizeof(double));
  for (i = 0; i < 512; i++) {
    xtmp = b_x[i];
    b_x[i] = b_x[1023 - i];
    b_x[1023 - i] = xtmp;
  }

  for (i = 0; i < 1023; i++) {
    xtmp = b_x[i] - y[i];
    tmp_data[i].re = dcv[i].re * xtmp + y[i];
    tmp_data[i].im = dcv[i].im * xtmp;
  }

  ifft(tmp_data, zz_data, zz_size);
  for (i = 0; i < 1023; i++) {
    int x_tmp;
    x_tmp = i << 1;
    x[x_tmp] = zz_data[i].re;
    x[x_tmp + 1] = zz_data[i].im;
  }

  //  change output dimension
}

// End of code generation (irfft.cpp)
