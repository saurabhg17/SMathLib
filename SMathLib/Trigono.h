// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_TRIGONO_H_
#define _SMATHLIB_TRIGONO_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

//! Convert angle in degrees into radians.
//! \param x Angle in degrees.
//! \return Angle in radians.
SMATHLIB_DLL_API double glDegreeToRadian(double x);

//! Convert angle in radians into degrees.
//! \param x Angle in radians.
//! \return Angle in degrees.
SMATHLIB_DLL_API double glRadianToDegree(double x);

//! Compute the inverse tangent of y/x.
//! \param x X-coordinate.
//! \param y Y-coordinate.
//! \param epsilon A absolute error threshold used for finding the sign of x 
//! and y. If |x| < epsilon then x = 0, if x > epsilon then x is positive, and
//! if x < -epsilon then x is negative. Similarly for y.
//! \return Inverse tangent of (y/x) in the range 0 to 2*PI.
SMATHLIB_DLL_API double glTanInverse(double x, double y, double epsilon = 1e-6);

//! Compute the inverse cosine.
//! \param x Number of which inverse cosine is to be computed.
//! \param epsilon A absolute error threshold used for checking is x is greater
//! then +1 or less then -1. If x>1+epsilon or x<-1-epsilon then an exception is 
//! thrown.
//! Range of result is strictly [0, PI].
SMATHLIB_DLL_API double glCosInverse(double x, double epsilon = 1e-6);

};	// End namespace SMathLib.

#endif // _SMATHLIB_TRIGONO_H_
