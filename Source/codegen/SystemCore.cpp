//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  SystemCore.cpp
//
//  Code generation for function 'SystemCore'
//


// Include files
#include "SystemCore.h"
#include "ColoredNoise.h"
#include "additive.h"
#include "rt_nonfinite.h"
#include "subtractive.h"
#include <cstring>

// Function Definitions
void c_dsp_ColoredNoise::setup()
{
  this->isSetupComplete = false;
  this->isInitialized = 1;
  this->isSetupComplete = true;
}

void b_dsp_ColoredNoise::setup()
{
  this->isSetupComplete = false;
  this->isInitialized = 1;
  this->isSetupComplete = true;
}

void dsp_ColoredNoise::setup()
{
  this->isSetupComplete = false;
  this->isInitialized = 1;
  this->isSetupComplete = true;
}

void c_dsp_ColoredNoise::setupAndReset()
{
  this->setup();
  std::memset(&this->pFilterStates[0], 0, 255U * sizeof(double));
}

void b_dsp_ColoredNoise::setupAndReset()
{
  this->setup();
  std::memset(&this->pFilterStates[0], 0, 10U * sizeof(double));
}

void dsp_ColoredNoise::setupAndReset()
{
  this->setup();
}

void c_dsp_ColoredNoise::release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
  }
}

void b_dsp_ColoredNoise::release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
  }
}

void dsp_ColoredNoise::release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
  }
}

void c_dsp_ColoredNoise::step(double varargout_1[4096])
{
  if (this->isInitialized != 1) {
    this->setupAndReset();
  }

  this->stepImpl(varargout_1);
}

void b_dsp_ColoredNoise::step(double varargout_1[4096])
{
  if (this->isInitialized != 1) {
    this->setupAndReset();
  }

  this->stepImpl(varargout_1);
}

void dsp_ColoredNoise::step(double varargout_1[4096])
{
  if (this->isInitialized != 1) {
    this->setupAndReset();
  }

  dsp_ColoredNoise::stepImpl((varargout_1));
}

// End of code generation (SystemCore.cpp)
