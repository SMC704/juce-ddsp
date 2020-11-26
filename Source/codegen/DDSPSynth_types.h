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
  static void dobluesteinfft(const double x_data[], const int x_size[1], const
    double costab[257], const double sintab[257], const double sintabinv[257],
    creal_T y[131]);
  static void dobluesteinfft(const double x_data[], const int x_size[1], int
    n2blue, int nfft, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, const coder::array<double, 2U> &sintabinv, coder::array<
    creal_T, 1U> &y);
  static void doHalfLengthRadix2(const double x_data[], const int x_size[1],
    coder::array<creal_T, 1U> &y, int unsigned_nRows, const coder::array<double,
    2U> &costab, const coder::array<double, 2U> &sintab);
 protected:
  static void r2br_r2dit_trig_impl(const creal_T x[131], const double costab[257],
    const double sintab[257], creal_T y[512]);
  static void r2br_r2dit_trig(const creal_T x[261], const double costab[257],
    const double sintab[257], creal_T y[512]);
  static void b_r2br_r2dit_trig(const creal_T x[512], const double costab[257],
    const double sintab[257], creal_T y[512]);
  static void r2br_r2dit_trig_impl(const coder::array<creal_T, 1U> &x, int
    unsigned_nRows, const coder::array<double, 2U> &costab, const coder::array<
    double, 2U> &sintab, coder::array<creal_T, 1U> &y);
  static void doHalfLengthBluestein(const double x_data[], const int x_size[1],
    coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int nfft, const coder::
    array<creal_T, 1U> &wwc, const coder::array<double, 2U> &costab, const coder::
    array<double, 2U> &sintab, const coder::array<double, 2U> &costabinv, const
    coder::array<double, 2U> &sintabinv);
};

class b_dsp_ColoredNoise
{
 public:
  b_dsp_ColoredNoise *init();
  void step(double varargout_1[4161]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  void stepImpl(double out[4161]);
  double pFilterStates[10];
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

class c_dsp_ColoredNoise
{
 public:
  c_dsp_ColoredNoise *init();
  void step(double varargout_1[4161]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  void stepImpl(double out[4161]);
  double pFilterStates[255];
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

class dsp_ColoredNoise
{
 public:
  dsp_ColoredNoise *init();
  void step(double varargout_1[4161]);
  void setupAndReset();
  void setup();
  void release();
 protected:
  static void stepImpl(double out[4161]);
 private:
  int isInitialized;
  boolean_T isSetupComplete;
};

#define MAX_THREADS                    omp_get_max_threads()
#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

// End of code generation (DDSPSynth_types.h)
