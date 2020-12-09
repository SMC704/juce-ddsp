//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  SystemProp.h
//
//  Code generation for function 'SystemProp'
//


#ifndef SYSTEMPROP_H
#define SYSTEMPROP_H

// Include files
#include "rtwtypes.h"
#include "omp.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder
{
  class weightingFilter;
}

// Type Definitions
namespace coder
{
  namespace matlab
  {
    namespace system
    {
      namespace coder
      {
        class SystemProp
        {
         public:
          static void matlabCodegenNotifyAnyProp(weightingFilter *obj);
        };
      }
    }
  }
}

#endif

// End of code generation (SystemProp.h)
