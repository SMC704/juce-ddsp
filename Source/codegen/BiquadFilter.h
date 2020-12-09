//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  BiquadFilter.h
//
//  Code generation for function 'BiquadFilter'
//


#ifndef BIQUADFILTER_H
#define BIQUADFILTER_H

// Include files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_BiquadFilter_0
{
  int S0_isInitialized;
  double W0_FILT_STATES[6];
  int W1_PreviousNumChannels;
  double P0_ICRTP;
};

namespace coder
{
  namespace dspcodegen
  {
    class BiquadFilter
    {
     public:
      BiquadFilter *init();
      void setup();
      void reset();
      void step(const double varargin_1[2048], const double varargin_2[9], const
                double varargin_3[6], const double varargin_4[4], double
                varargout_1[2048]);
      void setupAndReset();
      void matlabCodegenDestructor();
      void release();
      ~BiquadFilter();
      BiquadFilter();
      boolean_T matlabCodegenIsDeleted;
     private:
      int isInitialized;
      boolean_T isSetupComplete;
      dsp_BiquadFilter_0 cSFunObject;
    };
  }
}

#endif

// End of code generation (BiquadFilter.h)
