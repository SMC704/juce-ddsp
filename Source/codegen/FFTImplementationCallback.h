//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  FFTImplementationCallback.h
//
//  Code generation for function 'FFTImplementationCallback'
//


#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace internal
  {
    class FFTImplementationCallback
    {
     public:
      static void get_algo_sizes(int nfft, boolean_T useRadix2, int *n2blue, int
        *nRows);
      static void r2br_r2dit_trig(const ::coder::array<double, 2U> &x, const
        double costab_data[], const double sintab_data[], ::coder::array<creal_T,
        2U> &y);
      static void dobluesteinfft(const double x_data[], const int x_size[1], int
        n2blue, int nfft, const ::coder::array<double, 2U> &costab, const ::
        coder::array<double, 2U> &sintab, const ::coder::array<double, 2U>
        &sintabinv, ::coder::array<creal_T, 1U> &y);
      static void dobluesteinfft(const ::coder::array<double, 1U> &x, int n2blue,
        int nfft, const ::coder::array<double, 2U> &costab, const ::coder::array<
        double, 2U> &sintab, const ::coder::array<double, 2U> &sintabinv, ::
        coder::array<creal_T, 1U> &y);
      static void doHalfLengthRadix2(const double x[4096], creal_T y[4096]);
      static void doHalfLengthRadix2(const double x_data[], const int x_size[1],
        ::coder::array<creal_T, 1U> &y, int unsigned_nRows, const ::coder::array<
        double, 2U> &costab, const ::coder::array<double, 2U> &sintab);
      static void doHalfLengthRadix2(const ::coder::array<double, 1U> &x, ::
        coder::array<creal_T, 1U> &y, int unsigned_nRows, const ::coder::array<
        double, 2U> &costab, const ::coder::array<double, 2U> &sintab);
     protected:
      static void get_bitrevIndex(int nRowsM1, int nfftLen, ::coder::array<int,
        1U> &bitrevIndex);
      static void r2br_r2dit_trig_impl(const ::coder::array<creal_T, 1U> &x, int
        unsigned_nRows, const ::coder::array<double, 2U> &costab, const ::coder::
        array<double, 2U> &sintab, ::coder::array<creal_T, 1U> &y);
      static void generate_twiddle_tables(int nRows, ::coder::array<double, 2U>
        &costab, ::coder::array<double, 2U> &sintab, ::coder::array<double, 2U>
        &sintabinv);
      static void get_half_twiddle_tables(const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, const ::coder::array<
        double, 2U> &costabinv, const ::coder::array<double, 2U> &sintabinv, ::
        coder::array<double, 2U> &hcostab, ::coder::array<double, 2U> &hsintab, ::
        coder::array<double, 2U> &hcostabinv, ::coder::array<double, 2U>
        &hsintabinv);
      static void doHalfLengthRadix2(const ::coder::array<double, 2U> &x, int
        xoffInit, creal_T y_data[], int y_size[1], const double costab_data[],
        const double sintab_data[]);
      static void getback_radix2_fft(::coder::array<creal_T, 1U> &y, const ::
        coder::array<creal_T, 1U> &reconVar1, const ::coder::array<creal_T, 1U>
        &reconVar2, const ::coder::array<int, 2U> &wrapIndex, int hnRows);
      static void doHalfLengthBluestein(const double x_data[], const int x_size
        [1], ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft,
        const ::coder::array<creal_T, 1U> &wwc, const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, const ::coder::array<
        double, 2U> &costabinv, const ::coder::array<double, 2U> &sintabinv);
      static void doHalfLengthBluestein(const ::coder::array<double, 1U> &x, ::
        coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const ::
        coder::array<creal_T, 1U> &wwc, const ::coder::array<double, 2U> &costab,
        const ::coder::array<double, 2U> &sintab, const ::coder::array<double,
        2U> &costabinv, const ::coder::array<double, 2U> &sintabinv);
    };
  }
}

#endif

// End of code generation (FFTImplementationCallback.h)
