
#ifndef _SMATHLIB_VECTOR3D_H_
#define _SMATHLIB_VECTOR3D_H_

#include "SMathLib/Config.h"
#include <iostream>
#include <vector>

namespace SMathLib {
;

class Matrix;

class SMATHLIB_DLL_API Vector3D
{
	// For standard IO.
	SMATHLIB_DLL_API friend std::ostream& operator <<(std::ostream& out, const Vector3D &B);
	SMATHLIB_DLL_API friend std::istream& operator >>(std::istream& in , Vector3D &B);
	
	// For sorting.
	SMATHLIB_DLL_API friend bool v3DLesserX(const Vector3D &v1, const Vector3D &v2);
	SMATHLIB_DLL_API friend bool v3DLesserY(const Vector3D &v1, const Vector3D &v2);
	
public:
	
	typedef double value_type;
	
	// functions
	Vector3D CrossProduct(const Vector3D &B, bool bNormalize=true) const;
	double	  DotProduct(const Vector3D &B) const;
	double    Distance(const Vector3D &B) const;
	double	  Magnitude() const;
	double	  Magnitude2() const;
	void	  Normalize();
	
	// logical operators.
	bool operator ==(const Vector3D &B) const;
	bool operator !=(const Vector3D &B) const;
	bool operator < (const Vector3D &B) const;
	bool operator > (const Vector3D &B) const;
	bool operator <=(const Vector3D &B) const;
	bool operator >=(const Vector3D &B) const;
	bool Equal(const Vector3D &B, double tolerance) const;
	bool NotEqual(const Vector3D &B, double tolerance) const;
	
	// arithmetic operators.
	Vector3D  operator + (const Vector3D &B) const;
	Vector3D  operator - (const Vector3D &B) const;
	Vector3D  operator * (double s) const;
	Vector3D  operator / (double s) const;
	Vector3D& operator +=(const Vector3D &B);
	Vector3D& operator -=(const Vector3D &B);
	Vector3D& operator *=(double s);
	Vector3D& operator /=(double s);
	
	// unary operators.
	Vector3D operator -() const;
	
	// assignment, indexing and casting operators.
	double&	operator [](const int index);
	double 	operator [](const int index) const;
	Vector3D& operator =(const Vector3D &B);
	
	Matrix operator * (const Vector3D &B) const;
	
	//constructors and destructor.
	Vector3D();
	Vector3D(double data[3]);
	Vector3D(double x, double y, double z);
	Vector3D(const Vector3D &B);
	virtual ~Vector3D();
	
public:
	
	// point coordinates.
	double x;
	double y;
	double z;
};

typedef std::vector<Vector3D> Vector3DArray;

// for file IO.
std::ostream& operator <<(std::ostream& fout, const std::vector<Vector3D>& B);
std::istream& operator >>(std::istream& fin, std::vector<Vector3D>& B);

};	// End namespace SMathLib.

#endif // _SMATHLIB_VECTOR3D_H_
