
#ifndef _SMATHLIB_AXISANGLE_H_
#define _SMATHLIB_AXISANGLE_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

//! Compute a 4x4 rotation matrix from axis angles.
//! \param x The x-coordinate of the axis.
//! \param y The y-coordinate of the axis.
//! \param z The z-coordinate of the axis.
//! \param r The angle about the axis.
//! \param rotMat Output: The 4x4 rotation matrix.
SMATHLIB_DLL_API void glAxisAngleToRotationMatrix(double x, double y, double z, 
												  double r, double* rotMat);

};	// End namespace SMathLib.

#endif // _SMATHLIB_AXISANGLE_H_
