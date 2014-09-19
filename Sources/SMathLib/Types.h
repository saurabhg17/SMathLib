
#ifndef _SMATHLIB_TYPES_H_
#define _SMATHLIB_TYPES_H_

namespace SMathLib {
;

//! For representing sign of a number.
enum Sign
{
	eSign_Negative = -1,    ///< Negative number.
	eSign_Zero     =  0,    ///< Zero.
	eSign_Positive =  1     ///< Positive number.
};

//! Types of angles.
enum AngleType
{
	eDegree = 1,    ///< Angle in degrees.
	eRadian = 2,    ///< Angle in radians.
};

//! Distance metric to use for computing distance
//! between 2 N-Dimensional points.
enum DistanceMetric
{
	eRectilinear  = 1,
	eCityBlock    = 1, 
	eManhattan    = 1,
	eL1Norm       = 1,
	eL2Norm       = 2,
	eEuclidean    = 2,
	eLPNorm       = 3,
	eInfinityNorm = 4,
	eMaximumNorm  = 4,
	eHamming      = 5,
	eCosAngle     = 6,
};

//! Options for error checking during comparing two doubles.
enum MathsCompareChecks
{
	eMaths_NoChecks      = 0,   ///< Perform no checks.
	eMaths_InfinityCheck = 1,   ///< Check if numbers are infinity.
	eMaths_NanCheck      = 2,   ///< Check if number are NAN.
	eMaths_AllChecks     = 7,   ///< Perform all the checks.
};

//! Options for specifying type of bias for computing variance.
enum BiasTypes
{
	eBiased   = 1,
	eUnBiased = 2,
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_TYPES_H_
