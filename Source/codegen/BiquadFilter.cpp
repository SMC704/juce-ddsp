//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  BiquadFilter.cpp
//
//  Code generation for function 'BiquadFilter'
//


// Include files
#include "BiquadFilter.h"
#include "rt_nonfinite.h"
#include "setup.h"

// Function Definitions
namespace coder
{
  namespace dspcodegen
  {
    void BiquadFilter::setupAndReset()
    {
      this->setup();

      // System object Initialization function: dsp.BiquadFilter
      for (int i = 0; i < 6; i++) {
        this->cSFunObject.W0_FILT_STATES[i] = this->cSFunObject.P0_ICRTP;
      }
    }

    BiquadFilter::BiquadFilter()
    {
      this->matlabCodegenIsDeleted = true;
    }

    BiquadFilter::~BiquadFilter()
    {
      this->matlabCodegenDestructor();
    }

    BiquadFilter *BiquadFilter::init()
    {
      BiquadFilter *obj;
      obj = this;
      obj->isInitialized = 0;

      // System object Constructor function: dsp.BiquadFilter
      obj->cSFunObject.P0_ICRTP = 0.0;
      obj->matlabCodegenIsDeleted = false;
      return obj;
    }

    void BiquadFilter::matlabCodegenDestructor()
    {
      if (!this->matlabCodegenIsDeleted) {
        this->matlabCodegenIsDeleted = true;
        this->release();
      }
    }

    void BiquadFilter::release()
    {
      if (this->isInitialized == 1) {
        this->isInitialized = 2;
      }
    }

    void BiquadFilter::reset()
    {
      if (this->isInitialized == 1) {
        // System object Initialization function: dsp.BiquadFilter
        for (int i = 0; i < 6; i++) {
          this->cSFunObject.W0_FILT_STATES[i] = this->cSFunObject.P0_ICRTP;
        }
      }
    }

    void BiquadFilter::setup()
    {
      this->isSetupComplete = false;
      this->isInitialized = 1;
      this->isSetupComplete = true;
    }

    void BiquadFilter::step(const double varargin_1[2048], const double
      varargin_2[9], const double varargin_3[6], const double varargin_4[4],
      double varargout_1[2048])
    {
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      Outputs(&this->cSFunObject, varargin_1, varargin_2, varargin_3, varargin_4,
              varargout_1);
    }
  }
}

// End of code generation (BiquadFilter.cpp)
