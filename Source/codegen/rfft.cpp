//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  rfft.cpp
//
//  Code generation for function 'rfft'
//


// Include files
#include "rfft.h"
#include "additive.h"
#include "fft.h"
#include "ifft.h"
#include "irfft.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cmath>

// Function Definitions
void rfft(const coder::array<double, 2U> &x, double n, coder::array<creal_T, 2U>
          &y)
{
  int ncols;
  coder::array<int, 2U> idx;
  coder::array<boolean_T, 2U> b;

  // RFFT     Calculate the DFT of real data Y=(X,N,D)
  //  Data is truncated/padded to length N if specified.
  //    N even:	(N+2)/2 points are returned with
  //  			the first and last being real
  //    N odd:	(N+1)/2 points are returned with the
  //  			first being real
  //  In all cases fix(1+N/2) points are returned
  //  D is the dimension along which to do the DFT
  //       Copyright (C) Mike Brookes 1998
  //       Version: $Id: rfft.m 713 2011-10-16 14:45:43Z dmb $
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
  if (x.size(1) == 1) {
    y.set_size(1, x.size(1));
    ncols = x.size(0) * x.size(1);
    for (int i = 0; i < ncols; i++) {
      y[i].re = x[i];
      y[i].im = 0.0;
    }
  } else {
    int i;
    double b_x;
    int ncolx;
    fft(x, n, y);

    // y=reshape(y,prod(s(1:d-1)),n,prod(s(d+1:end)));
    // we probably don't need this ^
    b_x = n / 2.0;
    if (b_x < 0.0) {
      b_x = std::ceil(b_x);
    } else {
      b_x = std::floor(b_x);
    }

    idx.set_size(1, (static_cast<int>(static_cast<double>(y.size(1)) - ((b_x +
      1.0) + 1.0)) + 1));
    ncols = static_cast<int>(static_cast<double>(y.size(1)) - ((b_x + 1.0) + 1.0));
    for (i = 0; i <= ncols; i++) {
      idx[i] = static_cast<int>(((b_x + 1.0) + 1.0) + static_cast<double>(i));
    }

    ncolx = y.size(1);
    if (idx.size(1) == 1) {
      ncols = y.size(1) - 1;
      i = idx[0];
      for (int j = i; j <= ncols; j++) {
        y[j - 1] = y[j];
      }
    } else {
      int j;
      int k;
      b.set_size(1, y.size(1));
      ncols = y.size(1);
      for (i = 0; i < ncols; i++) {
        b[i] = false;
      }

      i = idx.size(1);
      for (k = 0; k < i; k++) {
        b[idx[k] - 1] = true;
      }

      ncols = 0;
      i = b.size(1);
      for (k = 0; k < i; k++) {
        ncols += b[k];
      }

      ncols = y.size(1) - ncols;
      j = 0;
      for (k = 0; k < ncolx; k++) {
        if ((k + 1 > b.size(1)) || (!b[k])) {
          y[j] = y[k];
          j++;
        }
      }
    }

    if (1 > ncols) {
      ncols = 0;
    }

    y.set_size(y.size(0), ncols);

    //  y=real(reshape(y,s));
    //  And this ^
    i = y.size(0) * y.size(1);
    y.set_size(1, y.size(1));
    ncols = i - 1;
    for (i = 0; i <= ncols; i++) {
      y[i].im = 0.0;
    }
  }
}

// End of code generation (rfft.cpp)
