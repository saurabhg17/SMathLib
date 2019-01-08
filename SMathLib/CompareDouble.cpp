
#include "CompareDouble.h"
#include "FPMaths.h"
#include <cfloat>
#include <cmath>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool glCompareDouble(double A, double B, double maxRelErr, double maxAbsErr, int checks)
{
	// If two numbers are exactly same then no point
	// doing anything else. Also this ensures +0
	// and -0 are compared as same number.
	if(A == B)
	{
		return true;
	}
	
	// There are several optional checks that can be done, depending
	// on what behavior is expected from floating point comparisons.
	// These checks should not be necessary and they are included
	// mainly for completeness.
	
	if(checks & eMaths_InfinityCheck)
	{
		// If A or B are infinity (positive or negative) then
		// only return true if they are exactly equal to each other -
		// that is, if they are both infinities of the same sign.
		// This check is only needed if you will be generating
		// infinities and you don't want them 'close' to numbers
		// near DOUBLE_MAX.
		if(glIsInfinite(A) || glIsInfinite(B))
		{
			return A == B;
		}
	}
	
	if(checks & eMaths_NanCheck)
	{
		// If A or B are a NAN, return false. NANs are 
		// equal to nothing, not even themselves! This 
		// check is only needed if you will be generating 
		// NANs or you want to ensure that a NAN does not 
		// equal itself.
		if(glIsNan(A) || glIsNan(B))
		{
			return false;
		}
	}
	
	// Check for absolute error, this ensure very 
	// small number are checked correctly.
	if(fabs(A-B) <= maxAbsErr)
	{
		return true;
	}
	
	// Check for relative error.
	double relativeError;
	if(fabs(B) > fabs(A))
	{
		relativeError = fabs((A - B) / B);
	}
	else
	{
		relativeError = fabs((A - B) / A);
	}
	
	if(relativeError <= maxRelErr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool glCompareArray(const double* array1, const double* array2, size_t length, double maxAbsError, double maxRelError, int checks)
{
	for(size_t i=0 ; i<length ; ++i)
	{
		if(!glCompareDouble(array1[i], array2[i], maxAbsError, maxRelError, checks))
		{
			return false;
		}
	}
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool glCompareArray(double scalar, const double* array1, size_t length, double maxAbsError, double maxRelError, int checks)
{
	for(size_t i=0 ; i<length ; ++i)
	{
		if(!glCompareDouble(scalar, array1[i], maxAbsError, maxRelError, checks))
		{
			return false;
		}
	}
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
