// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_FPMATHS_H_
#define _SMATHLIB_FPMATHS_H_

#include "SMathLib/Config.h"
#include "SMathLib/Types.h"
#include <iostream>

namespace SMathLib {
;

//! Find the exponent of a double precision floating point number.
SMATHLIB_DLL_API int glExponentOfDouble(double x);

//! Check if a number is infinite.
SMATHLIB_DLL_API bool glIsInfinite(double A);

//! Check if a number is Not-a-Number.
SMATHLIB_DLL_API bool glIsNan(double A);

//! Determine sign of a number.
SMATHLIB_DLL_API Sign glSign(double A);

//! Add val to sum using Kahan summation algorithm. rError is the current 
//! error value, and should be maintained by the calling function. Don't 
//! change value of rError during the summation. If you are performing several
//! summations in same loop then create an error variable for each summation.
SMATHLIB_DLL_API void glKahanSum(double& rSum, const double& val, double& rError);

#if defined(SMathLib_OS_WINDOWS)
	//! This function prints the status of the floating point control word.
	SMATHLIB_DLL_API void glPrintFpuControlWord(std::ostream& fp);
#endif

}; // end namespace SMathLib.

#endif // _SMATHLIB_FPMATHS_H_
