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
      static void generate_twiddle_tables(int nRows, boolean_T useRadix2, ::
        coder::array<double, 2U> &costab, ::coder::array<double, 2U> &sintab, ::
        coder::array<double, 2U> &sintabinv);
      static void r2br_r2dit_trig_impl(const ::coder::array<creal_T, 1U> &x, int
        unsigned_nRows, const ::coder::array<double, 2U> &costab, const ::coder::
        array<double, 2U> &sintab, ::coder::array<creal_T, 1U> &y);
      static void doHalfLengthRadix2(const double x_data[], const int x_size[1],
        creal_T y[2048]);
      static void doHalfLengthRadix2(const double x[4096], creal_T y[4096]);
      static void doHalfLengthRadix2(const double x_data[], const int x_size[1],
        ::coder::array<creal_T, 1U> &y, int unsigned_nRows, const ::coder::array<
        double, 2U> &costab, const ::coder::array<double, 2U> &sintab);
      static void doHalfLengthBluestein(const double x_data[], const int x_size
        [1], ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft,
        const ::coder::array<creal_T, 1U> &wwc, const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, const ::coder::array<
        double, 2U> &costabinv, const ::coder::array<double, 2U> &sintabinv);
      static void doHalfLengthRadix2(const double x[65], ::coder::array<creal_T,
        1U> &y, int unsigned_nRows, const ::coder::array<double, 2U> &costab,
        const ::coder::array<double, 2U> &sintab);
      static void doHalfLengthBluestein(const double x[65], ::coder::array<
        creal_T, 1U> &y, int nRows, int nfft, const ::coder::array<creal_T, 1U>
        &wwc, const ::coder::array<double, 2U> &costab, const ::coder::array<
        double, 2U> &sintab, const ::coder::array<double, 2U> &costabinv, const ::
        coder::array<double, 2U> &sintabinv);
     protected:
      static void get_bitrevIndex(int nRowsM1, int nfftLen, ::coder::array<int,
        1U> &bitrevIndex);
      static void b_generate_twiddle_tables(int nRows, ::coder::array<double, 2U>
        &costab, ::coder::array<double, 2U> &sintab, ::coder::array<double, 2U>
        &sintabinv);
      static void get_half_twiddle_tables(const ::coder::array<double, 2U>
        &costab, const ::coder::array<double, 2U> &sintab, const ::coder::array<
        double, 2U> &costabinv, const ::coder::array<double, 2U> &sintabinv, ::
        coder::array<double, 2U> &hcostab, ::coder::array<double, 2U> &hsintab, ::
        coder::array<double, 2U> &hcostabinv, ::coder::array<double, 2U>
        &hsintabinv);
      static void getback_radix2_fft(::coder::array<creal_T, 1U> &y, const ::
        coder::array<creal_T, 1U> &reconVar1, const ::coder::array<creal_T, 1U>
        &reconVar2, const ::coder::array<int, 2U> &wrapIndex, int hnRows);
    };
  }
}

#endif

// End of code generation (FFTImplementationCallback.h)
