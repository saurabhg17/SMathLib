
#ifndef _SMATHLIB_SPHERICAL_H_
#define _SMATHLIB_SPHERICAL_H_

#include "SUtils/Exceptions/InvalidArgumentException.h"
#include "SMathLib/PointAccessor.h"
#include "SMathLib/Types.h"
#include "SMathLib/Trigono.h"
#include <cmath>

namespace SMathLib {
;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Convert Cartesian coordinates to spherical coordinates.
//! \param T Any type supporting an indexing operator.
//! \param coords Cartesian coordinates in (x, y, z) order.
//! \param type If type is Angle then spherical coordinates are in degree and if
//! type is Radian then spherical coordinates are in radians.
//! \return Spherical Coordinates in the order (r, theta, phi), where r is 
//! radius, theta is the angle in the x-y plane from x-axis (0, 360), and
//! phi is the angle from z-axis (0, 180).
template<typename T>
T glCartesianToSpherical(const T& coords, AngleType type)
{
	typedef PointAccessor<T> PA;
	
	double x = PA::get(coords, 0);
	double y = PA::get(coords, 1);
	double z = PA::get(coords, 2);
	double r, t, p;
	glSphericalToCartesian(x, y, z, &r, &t, &p, type);
	
	T _coords;
	PA::set(_coords, 0, r);
	PA::set(_coords, 1, t);
	PA::set(_coords, 2, p);
	return _coords;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Convert Cartesian coordinates to spherical coordinates.
//! This is a helper function provided for convenience.
//! \param x x-coordinate.
//! \param y y-coordinate.
//! \param z z-coordinate.
//! \param r Output: Radius of the spherical coordinates.
//! \param t Output: Angle in x-y plane from x-axis (0<=t<=2PI).
//! \param p Output: Angle in from z-axis (0<=p<=PI).
//! \param type The type of spherical coordinates to return.
void glCartesianToSpherical(double  x, double  y, double  z,
							double* r, double* t, double* p,
							AngleType type)
{
	if(r==NULL || t==NULL || p==NULL)
	{
		char _msg[] = "glCartesianToSpherical: Null argument";
		throw SUtils::Exceptions::InvalidArgumentException(_msg);
	}
	
	// Compute angles in radians.
	*r = sqrt(x*x+y*y+z*z);     // r
	*t = glTanInverse(x, y);    // y/x
	*p = glCosInverse(z/x);     // z/r
	
	// Convert angle to degrees.
	if(type == eDegree)
	{
		*t = glRadianToDegree(*t);   // y/x
		*p = glRadianToDegree(*p);   // z/r
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Convert spherical coordinates into Cartesian coordinates.
//! \param T Any type supporting an indexing operator.
//! \param coords Spherical Coordinates in the order (r, theta, phi), where r is 
//! radius, theta is the angle in the x-y plane from x-axis (0, 360), and
//! phi is the angle from z-axis (0, 180).
//! \param type If type is Angle then spherical coordinates are in degree and if
//! type is Radian then spherical coordinates are in radians.
//! \return Cartesian coordinates in (x, y, z) order.
template<typename T>
T glSphericalToCartesian(const T& coords, AngleType type)
{
	typedef PointAccessor<T> PA;
	
	double r = PA::get(coords, 0);
	double t = PA::get(coords, 1);
	double p = PA::get(coords, 2);
	double x, y, z;
	glSphericalToCartesian(r, t, p, &x, &y, &z, type);
	
	T _coords;
	PA::set(_coords, 0, x);
	PA::set(_coords, 1, y);
	PA::set(_coords, 2, z);
	return _coords;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Convert spherical coordinates to Cartesian coordinates.
//! This is a helper function provided for convenience.
//! \param r Radius of the spherical coordinates.
//! \param t Theta: Angle in x-y plane from x-axis (0<=t<=2PI).
//! \param p Phi: Angle in from z-axis (0<=p<=PI).
//! \param x Output: x-coordinate.
//! \param y Output: y-coordinate.
//! \param z Output: z-coordinate.
//! \param type The type of spherical coordinates.
void glSphericalToCartesian(double r , double t , double p,
							double* x, double* y, double* z,
							AngleType type)
{
	if(x==NULL || y==NULL || z==NULL)
	{
		char _msg[] = "glSphericalToCartesian: Null argument";
		throw SUtils::Exceptions::InvalidArgumentException(_msg);
	}
	
	// If angles are in degrees then convert them to radians.
	if(type == eDegree)
	{
		t = glDegreeToRadian(t);
		p = glDegreeToRadian(p);
	}
	
	*x = r*cos(t)*sin(p);
	*y = r*sin(t)*sin(p);
	*z = r*cos(p);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.

#endif // _SMATHLIB_SPHERICAL_H_
