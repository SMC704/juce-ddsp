//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  iseven.cpp
//
//  Code generation for function 'iseven'
//


// Include files
#include "iseven.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder
{
  namespace signalwavelet
  {
    namespace internal
    {
      boolean_T iseven(double x)
      {
        double r;
        if (rtIsNaN(x) || rtIsInf(x)) {
          r = rtNaN;
        } else if (x == 0.0) {
          r = 0.0;
        } else {
          r = std::fmod(x, 2.0);
          if (r == 0.0) {
            r = 0.0;
          } else {
            if (x < 0.0) {
              r += 2.0;
            }
          }
        }

        return r == 0.0;
      }
    }
  }
}

// End of code generation (iseven.cpp)
