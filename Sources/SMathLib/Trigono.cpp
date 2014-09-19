
#include "Trigono.h"
#include "Constants.h"
#include "SUtils/Exceptions/InvalidOperationException.h"
#include <cmath>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
double glDegreeToRadian(double x)
{
	return (x*gcPi)/180.0;
}
double glRadianToDegree(double x)
{
	return (x*180.0)/gcPi;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
double glTanInverse(double x, double y, double epsilon)
{
	// x==0 and y==0 => return 0.0;
	if(fabs(x)<epsilon && fabs(y)<epsilon)
	{
		return 0.0;
	}
	
	// Point lies on positive x-axis.
	if(x>epsilon && fabs(y)<epsilon)
	{
		return 0.0;
	}
	
	// Point lies on positive y-axis.
	if(fabs(x)<epsilon && y>epsilon)
	{
		return gcPiBy2;
	}
	
	// Point lies on negative x-axis.
	if(x<-epsilon && fabs(y)<epsilon)
	{
		return gcPi;
	}
	
	// Point lies on negative y-axis.
	if(fabs(x)<epsilon && y<-epsilon)
	{
		return gc3PiBy2;
	}
	
	double _temp = atan(fabs(y/x));
	
	// First quadrant.
	if(x>epsilon && y>epsilon)
	{
		return _temp;
	}
	
	// Second quadrant.
	if(x<-epsilon && y>epsilon)
	{
		return gcPiBy2 + _temp;
	}
	
	// Third quadrant.
	if(x<-epsilon && y<-epsilon)
	{
		return gcPi + _temp;
	}
	
	// Fourth quadrant.
	if(x>epsilon && y<-epsilon)
	{
		return gc3PiBy2 + _temp;
	}
	
	// This line should never be executed as all the cases are handled above.
	char _msg[] = "Internal error in _TanInverse";
	throw SUtils::Exceptions::InvalidOperationException(_msg);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
double glCosInverse(double x, double epsilon)
{
	if(x>1 && x<=1+epsilon)
	{
		x = 1.0;
	}
	
	if(x<-1 && x>=-1-epsilon)
	{
		x = -1.0;
	}
	
	if(x>1 || x<-1)
	{
		char _msg[] = "Value out of range in cosine inverse.";
		throw SUtils::Exceptions::InvalidOperationException(_msg);
	}
	
	return acos(x);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
