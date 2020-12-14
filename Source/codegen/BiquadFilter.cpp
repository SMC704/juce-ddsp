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
      dsp_BiquadFilter_0 *obj;
      double d;
      double d1;
      double d10;
      double d11;
      double d12;
      double d13;
      double d14;
      double d15;
      double d16;
      double d17;
      double d18;
      double d2;
      double d3;
      double d4;
      double d5;
      double d6;
      double d7;
      double d8;
      double d9;
      int ioIdx;
      if (this->isInitialized != 1) {
        this->setupAndReset();
      }

      obj = &this->cSFunObject;

      // System object Outputs function: dsp.BiquadFilter
      ioIdx = 0;
      d = varargin_4[0];
      d1 = varargin_4[1];
      d2 = varargin_4[2];
      d3 = varargin_4[3];
      d4 = varargin_2[0];
      d5 = varargin_2[1];
      d6 = varargin_2[2];
      d7 = varargin_2[3];
      d8 = varargin_2[4];
      d9 = varargin_2[5];
      d10 = varargin_2[6];
      d11 = varargin_2[7];
      d12 = varargin_2[8];
      d13 = varargin_3[0];
      d14 = varargin_3[1];
      d15 = varargin_3[2];
      d16 = varargin_3[3];
      d17 = varargin_3[4];
      d18 = varargin_3[5];
      for (int i = 0; i < 2048; i++) {
        double numAccum;
        double stageIn;
        double stageOut;
        stageIn = d * varargin_1[ioIdx];
        numAccum = obj->W0_FILT_STATES[0];
        stageOut = numAccum + d4 * stageIn;
        numAccum = obj->W0_FILT_STATES[1];
        obj->W0_FILT_STATES[0] = (numAccum + d5 * stageIn) - d13 * stageOut;
        obj->W0_FILT_STATES[1] = d6 * stageIn - d14 * stageOut;
        stageIn = d1 * stageOut;
        numAccum = obj->W0_FILT_STATES[2];
        stageOut = numAccum + d7 * stageIn;
        numAccum = obj->W0_FILT_STATES[3];
        obj->W0_FILT_STATES[2] = (numAccum + d8 * stageIn) - d15 * stageOut;
        obj->W0_FILT_STATES[3] = d9 * stageIn - d16 * stageOut;
        stageIn = d2 * stageOut;
        numAccum = obj->W0_FILT_STATES[4];
        stageOut = numAccum + d10 * stageIn;
        numAccum = obj->W0_FILT_STATES[5];
        obj->W0_FILT_STATES[4] = (numAccum + d11 * stageIn) - d17 * stageOut;
        obj->W0_FILT_STATES[5] = d12 * stageIn - d18 * stageOut;
        varargout_1[ioIdx] = d3 * stageOut;
        ioIdx++;
      }
    }
  }
}

// End of code generation (BiquadFilter.cpp)
