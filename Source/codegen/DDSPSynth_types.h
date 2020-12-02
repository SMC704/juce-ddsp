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
  static void dobluesteinfft(const double x_data[], const int x_size[1], int
    n2blue, int nfft, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, const coder::array<double, 2U> &sintabinv, coder::array<
    creal_T, 1U> &y);
  static void dobluesteinfft(const coder::array<double, 1U> &x, int n2blue, int
    nfft, const coder::array<double, 2U> &costab, const coder::array<double, 2U>
    &sintab, const coder::array<double, 2U> &sintabinv, coder::array<creal_T, 1U>
    &y);
  static void doHalfLengthRadix2(const double x_data[], const int x_size[1],
    coder::array<creal_T, 1U> &y, int unsigned_nRows, const coder::array<double,
    2U> &costab, const coder::array<double, 2U> &sintab);
  static void doHalfLengthRadix2(const coder::array<double, 1U> &x, coder::array<
    creal_T, 1U> &y, int unsigned_nRows, const coder::array<double, 2U> &costab,
    const coder::array<double, 2U> &sintab);
 protected:
  static void get_bitrevIndex(int nRowsM1, int nfftLen, coder::array<int, 1U>
    &bitrevIndex);
  static void generate_twiddle_tables(int nRows, coder::array<double, 2U>
    &costab, coder::array<double, 2U> &sintab, coder::array<double, 2U>
    &sintabinv);
  static void get_half_twiddle_tables(const coder::array<double, 2U> &costab,
    const coder::array<double, 2U> &sintab, const coder::array<double, 2U>
    &costabinv, const coder::array<double, 2U> &sintabinv, coder::array<double,
    2U> &hcostab, coder::array<double, 2U> &hsintab, coder::array<double, 2U>
    &hcostabinv, coder::array<double, 2U> &hsintabinv);
  static void r2br_r2dit_trig_impl(const coder::array<creal_T, 1U> &x, int
    unsigned_nRows, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, coder::array<creal_T, 1U> &y);
  static void getback_radix2_fft(coder::array<creal_T, 1U> &y, const coder::
    array<creal_T, 1U> &reconVar1, const coder::array<creal_T, 1U> &reconVar2,
    const coder::array<int, 2U> &wrapIndex, int hnRows);
  static void doHalfLengthBluestein(const double x_data[], const int x_size[1],
    coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const coder::
    array<creal_T, 1U> &wwc, const coder::array<double, 2U> &costab, const coder::
    array<double, 2U> &sintab, const coder::array<double, 2U> &costabinv, const
    coder::array<double, 2U> &sintabinv);
  static void doHalfLengthBluestein(const coder::array<double, 1U> &x, coder::
    array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const coder::array<
    creal_T, 1U> &wwc, const coder::array<double, 2U> &costab, const coder::
    array<double, 2U> &sintab, const coder::array<double, 2U> &costabinv, const
    coder::array<double, 2U> &sintabinv);
};

class b_dsp_ColoredNoise
{
 public:
  b_dsp_ColoredNoise *init();
  void step(double varargout_1[4096]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  void stepImpl(double out[4096]);
  double pFilterStates[10];
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

class c_dsp_ColoredNoise
{
 public:
  c_dsp_ColoredNoise *init();
  void step(double varargout_1[4096]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  void stepImpl(double out[4096]);
  double pFilterStates[255];
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

class dsp_ColoredNoise
{
 public:
  dsp_ColoredNoise *init();
  void step(double varargout_1[4096]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  static void stepImpl(double out[4096]);
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

// End of code generation (DDSPSynth_types.h)
