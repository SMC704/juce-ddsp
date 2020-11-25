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

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

// End of code generation (DDSPSynth_types.h)
