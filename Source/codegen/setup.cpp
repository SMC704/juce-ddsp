//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  setup.cpp
//
//  Code generation for function 'setup'
//


// Include files
#include "setup.h"
#include "BiquadFilter.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder
{
  void Outputs(dsp_BiquadFilter_0 *obj, const double U0[2048], const double U1[9],
               const double U2[6], const double U3[4], double Y0[2048])
  {
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

    // System object Outputs function: dsp.BiquadFilter
    ioIdx = 0;
    d = U3[0];
    d1 = U3[1];
    d2 = U3[2];
    d3 = U3[3];
    d4 = U1[0];
    d5 = U1[1];
    d6 = U1[2];
    d7 = U1[3];
    d8 = U1[4];
    d9 = U1[5];
    d10 = U1[6];
    d11 = U1[7];
    d12 = U1[8];
    d13 = U2[0];
    d14 = U2[1];
    d15 = U2[2];
    d16 = U2[3];
    d17 = U2[4];
    d18 = U2[5];
    for (int i = 0; i < 2048; i++) {
      double stageIn;
      double stageOut;
      stageIn = d * U0[ioIdx];
      stageOut = obj->W0_FILT_STATES[0] + d4 * stageIn;
      obj->W0_FILT_STATES[0] = (obj->W0_FILT_STATES[1] + d5 * stageIn) - d13 *
        stageOut;
      obj->W0_FILT_STATES[1] = d6 * stageIn - d14 * stageOut;
      stageIn = d1 * stageOut;
      stageOut = obj->W0_FILT_STATES[2] + d7 * stageIn;
      obj->W0_FILT_STATES[2] = (obj->W0_FILT_STATES[3] + d8 * stageIn) - d15 *
        stageOut;
      obj->W0_FILT_STATES[3] = d9 * stageIn - d16 * stageOut;
      stageIn = d2 * stageOut;
      stageOut = obj->W0_FILT_STATES[4] + d10 * stageIn;
      obj->W0_FILT_STATES[4] = (obj->W0_FILT_STATES[5] + d11 * stageIn) - d17 *
        stageOut;
      obj->W0_FILT_STATES[5] = d12 * stageIn - d18 * stageOut;
      Y0[ioIdx] = d3 * stageOut;
      ioIdx++;
    }
  }
}

// End of code generation (setup.cpp)
