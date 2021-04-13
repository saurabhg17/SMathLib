// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_COMPAREDOUBLE_H_
#define _SMATHLIB_COMPAREDOUBLE_H_

#include "SMathLib/Config.h"
#include "SMathLib/Types.h"
#include <cstddef>

namespace SMathLib {
;

//! Compare two double numbers using both absolute and relative errors. 
//! \param A First double number.
//! \param B Second double numbers.
//! \param maxAbsErr Maximum permissible absolute error between two numbers.
//! \param maxRelErr Maximum permissible relative error between two numbers.
//! \param checks Type of checks which should be performed when comparing.
//! \return true if two numbers are equal, false otherwise.
//! maxRelativeError is defined in term of percentage of error, if desired 
//! accuracy is X% then maxRelativeError = (100.0-X)/100.0. In general relative 
//! error of P% means x will be compared equal to all numbers in the range 
//! [ x - (Px)/100, x + (Px)/100 ]. For example if P = 50 the range is 
//! [ x/2, 3x/2].
//! Also relative error can be defined in terms of number of digits required 
//! in precision. For example if relative error is 1e-8 that means two numbers 
//! will be compared using 8 most significant digits in their decimal 
//! representation.
SMATHLIB_DLL_API bool glCompareDouble(double A, double B, double maxRelErr, 
									  double maxAbsErr, int checks = eMaths_NoChecks);


SMATHLIB_DLL_API bool glCompareArray(const double* array1, const double* array2, size_t length, double maxAbsError, double maxRelError, int checks = eMaths_NoChecks);
SMATHLIB_DLL_API bool glCompareArray(double  scalar      , const double* array1, size_t length, double maxAbsError, double maxRelError, int checks = eMaths_NoChecks);

};	// End namespace SMathLib.

#endif // _SMATHLIB_COMPAREDOUBLE_H_
