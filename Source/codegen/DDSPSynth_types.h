//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  DDSPSynth_types.h
//
//  Code generation for function 'DDSPSynth_types'
//


#ifndef DDSPSYNTH_TYPES_H
#define DDSPSYNTH_TYPES_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
class FFTImplementationCallback
{
 public:
  static void get_algo_sizes(int nfft, boolean_T useRadix2, int *n2blue, int
    *nRows);
  static void generate_twiddle_tables(int nRows, double costab_data[], int
    costab_size[2], double sintab_data[], int sintab_size[2], double
    sintabinv_data[], int sintabinv_size[2]);
  static void dobluesteinfft(const creal_T x_data[], int n2blue, const double
    costab_data[], const int costab_size[2], const double sintab_data[], const
    int sintab_size[2], const double sintabinv_data[], const int sintabinv_size
    [2], creal_T y_data[], int y_size[1]);
  static void dobluesteinfft(const coder::array<double, 1U> &x, int n2blue, int
    nfft, const coder::array<double, 2U> &costab, const coder::array<double, 2U>
    &sintab, const coder::array<double, 2U> &sintabinv, coder::array<creal_T, 1U>
    &y);
  static void r2br_r2dit_trig(const coder::array<creal_T, 2U> &x, int
    n1_unsigned, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, coder::array<creal_T, 2U> &y);
  static void dobluesteinfft(const coder::array<creal_T, 2U> &x, int n2blue, int
    nfft, const coder::array<double, 2U> &costab, const coder::array<double, 2U>
    &sintab, const coder::array<double, 2U> &sintabinv, coder::array<creal_T, 2U>
    &y);
  static void doHalfLengthRadix2(const coder::array<double, 1U> &x, coder::array<
    creal_T, 1U> &y, int unsigned_nRows, const coder::array<double, 2U> &costab,
    const coder::array<double, 2U> &sintab);
 protected:
  static void r2br_r2dit_trig_impl(const coder::array<creal_T, 1U> &x, int
    unsigned_nRows, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, coder::array<creal_T, 1U> &y);
  static void doHalfLengthBluestein(const coder::array<double, 1U> &x, coder::
    array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const coder::array<
    creal_T, 1U> &wwc, const coder::array<double, 2U> &costab, const coder::
    array<double, 2U> &sintab, const coder::array<double, 2U> &costabinv, const
    coder::array<double, 2U> &sintabinv);
};

#define MAX_THREADS                    omp_get_max_threads()
#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

// End of code generation (DDSPSynth_types.h)
