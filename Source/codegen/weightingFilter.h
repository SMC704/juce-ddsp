//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  weightingFilter.h
//
//  Code generation for function 'weightingFilter'
//


#ifndef WEIGHTINGFILTER_H
#define WEIGHTINGFILTER_H

// Include files
#include "BiquadFilter.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_3
{
  unsigned int f1[8];
};

namespace coder
{
  class weightingFilter
  {
   public:
    weightingFilter *init(double varargin_2);
    boolean_T isLockedAndNotReleased() const;
    void set_SampleRate(double value);
    void step(const double varargin_1[2048], double varargout_1[2048]);
    void setupAndReset();
    void setup();
    double get_SampleRate() const;
    void checkTunableProps();
    void matlabCodegenDestructor();
    void release();
    void releaseWrapper();
    ~weightingFilter();
    weightingFilter();
   protected:
    void designFilter();
   public:
    boolean_T matlabCodegenIsDeleted;
    boolean_T TunablePropsChanged;
    dspcodegen::BiquadFilter pFilter;
   protected:
    double pSampleRateDialog;
    double pNumMatrix[9];
    double pDenMatrix[6];
    double pScaleValues[4];
    double pNumChannels;
   private:
    int isInitialized;
    boolean_T isSetupComplete;
    cell_wrap_3 inputVarSize[1];
  };
}

#endif

// End of code generation (weightingFilter.h)
