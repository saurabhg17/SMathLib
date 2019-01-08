
#ifndef _SMATHLIB_HELPERS_H_
#define _SMATHLIB_HELPERS_H_

#include "SUtils/Types.h"

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Round a single precision floating point number.
//! \param x Input value which should be rounded to int.
//! \return Round(x) = int(x + 0.5).
inline int glRound(float x)
{
	return int(x + 0.5);
}
//! Round a double precision floating point number.
//! \param x Input value which should be rounded to int.
//! \return Round(x) = int(x + 0.5).
inline SUtils::Int64 glRound(double x)
{
	return SUtils::Int64(x + 0.5);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.

#endif // _SMATHLIB_HELPERS_H_
