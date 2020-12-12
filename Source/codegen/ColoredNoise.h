//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  ColoredNoise.h
//
//  Code generation for function 'ColoredNoise'
//


#ifndef COLOREDNOISE_H
#define COLOREDNOISE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace dsp
  {
    class ColoredNoise
    {
     public:
      ColoredNoise *init();
      void step(double varargout_1[4096]);
      void setupAndReset();
      void setup();
      void release();
     private:
      int isInitialized;
      boolean_T isSetupComplete;
    };

    class b_ColoredNoise
    {
     public:
      b_ColoredNoise *init();
      void step(double varargout_1[4096]);
      void setupAndReset();
      void setup();
      void release();
     protected:
      double pFilterStates[10];
     private:
      int isInitialized;
      boolean_T isSetupComplete;
    };

    class c_ColoredNoise
    {
     public:
      c_ColoredNoise *init();
      void step(double varargout_1[4096]);
      void setupAndReset();
      void setup();
      void release();
     protected:
      double pFilterStates[255];
     private:
      int isInitialized;
      boolean_T isSetupComplete;
    };
  }
}

#endif

// End of code generation (ColoredNoise.h)
