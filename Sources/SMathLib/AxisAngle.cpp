
#include "AxisAngle.h"
#include "SUtils/Exceptions/InvalidArgumentException.h"
#include <cmath>

namespace SMathLib {
;

void glAxisAngleToRotationMatrix(double x, double y, double z, double r, double* rotMat)
{
	if(rotMat == 0)
	{
		char _msg[] = "NULL argument passed in axisAngle2RotationMatrix";
		throw SUtils::Exceptions::InvalidArgumentException(_msg);
	}
	
	double c = cos(r);
	double s = sin(r);
	double t = 1 - c;
	
	// Normalize axis.
	double m = sqrt(x*x + y*y + z*z);
	x = x / m;
	y = y / m; 
	z = z / m;
	
	// First row.
	rotMat[0 ] = t*x*x + c  ;
	rotMat[1 ] = t*x*y - z*s;
	rotMat[2 ] = t*x*z + y*s;
	rotMat[3 ] = 0.0;
	
	// Second row.
	rotMat[4 ] = t*x*y + z*s;
	rotMat[5 ] = t*y*y + c  ;
	rotMat[6 ] = t*y*z - x*s;
	rotMat[7 ] = 0.0;
	
	// Third row.
	rotMat[8 ] = t*x*z - y*s;
	rotMat[9 ] = t*y*z + x*s;
	rotMat[10] = t*z*z + c  ;
	rotMat[11] = 0.0;
	
	// Fourth row.
	rotMat[12] = 0.0;
	rotMat[13] = 0.0;
	rotMat[14] = 0.0;
	rotMat[15] = 1.0;
}

};	// End namespace SMathLib.
