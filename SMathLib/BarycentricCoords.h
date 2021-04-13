// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_BARYCENTRICCOORDS_H_
#define _SMATHLIB_BARYCENTRICCOORDS_H_

#include "SMathLib/GeometryAlgo.h"
#include "SMathLib/VectorAlgo.h"

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute Barycentric Coordinates of a 2D point w.r.t 2D triangle.
template<typename T3D, typename T2D>
inline T3D glBarycentricCoords2D(const T2D& p, const T2D& v1, const T2D& v2, const T2D& v3)
{
	double _A  = glTriangleArea2D(v1, v2, v3);
	double _A1 = glTriangleArea2D( p, v2, v3);
	double _A2 = glTriangleArea2D(v1,  p, v3);
	double _A3 = glTriangleArea2D(v1, v2,  p);
	
	T3D _bc;
	_bc[0] = _A1/_A;
	_bc[1] = _A2/_A;
	_bc[2] = _A3/_A;
	
	return _bc;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute Barycentric Coordinates of a 3D point w.r.t. 3D triangle.
template<typename T3D>
inline T3D glBarycentricCoords3D(const T3D& p, const T3D& v1, const T3D& v2, const T3D& v3)
{
	// Normal of the triangle.
	T3D _cp = glCrossProduct3D(v2-v1, v3-v1);
	
	// Compute area of four triangles.
	double _A  = glTriangleArea3D(v1, v2, v3);
	double _A1 = glTriangleArea3D(p , v2, v3);
	double _A2 = glTriangleArea3D(p , v3, v1);
	double _A3 = glTriangleArea3D(p , v1, v2);
	
	// Compute normals of triangle for sign determination.
	T3D _cp1 = glCrossProduct3D(v2-p, v3-p);
	T3D _cp2 = glCrossProduct3D(v3-p, v1-p);
	T3D _cp3 = glCrossProduct3D(v1-p, v2-p);
	
	// Determine sign for each area.
	double _sign1 = glDotProduct(_cp, _cp1, 3)>=0 ? 1 : -1;
	double _sign2 = glDotProduct(_cp, _cp2, 3)>=0 ? 1 : -1;
	double _sign3 = glDotProduct(_cp, _cp3, 3)>=0 ? 1 : -1;
	
	T3D _bc;
	_bc[0] = _sign1*_A1/_A;
	_bc[1] = _sign2*_A2/_A;
	_bc[2] = _sign3*_A3/_A;
	return _bc;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// end namespace SMathLib.

#endif // _SMATHLIB_BARYCENTRICCOORDS_H_
