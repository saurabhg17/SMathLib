
#ifndef _SMATHLIB_VECTOR2D_H_
#define _SMATHLIB_VECTOR2D_H_

#include "SMathLib/Config.h"
#include <iostream>
#include <vector>

namespace SMathLib {
;

class SMATHLIB_DLL_API Vector2D
{
	// Standard IO.
	SMATHLIB_DLL_API friend std::ostream& operator <<(std::ostream& out, const Vector2D &B);
	SMATHLIB_DLL_API friend std::istream& operator >>(std::istream& in , Vector2D &B);
	
	// For sorting.
	SMATHLIB_DLL_API friend bool v2DLesserX   (const Vector2D &v1, const Vector2D &v2);
	SMATHLIB_DLL_API friend bool v2DEqual     (const Vector2D &v1, const Vector2D &v2);
	SMATHLIB_DLL_API friend bool v2DLesserY   (const Vector2D &v1, const Vector2D &v2);
	SMATHLIB_DLL_API friend bool v2DLesserXY  (const Vector2D &v1, const Vector2D &v2);
	SMATHLIB_DLL_API friend bool v2DLesserYX_T(const Vector2D &v1, const Vector2D &v2);
	
public:
	
	typedef double value_type;
	
	// Functions.
	double Distance(const Vector2D &B) const;
	double DotProduct(const Vector2D &B) const ;
	double Magnitude() const;
	double Magnitude2() const;
	void   Normalize();
	
	// Logical operators.
	bool operator ==(const Vector2D &B) const;
	bool operator !=(const Vector2D &B) const;
	bool operator  >(const Vector2D &B) const;
	bool operator  <(const Vector2D &B) const;
	bool operator <=(const Vector2D &B) const;
	bool operator >=(const Vector2D &B) const;
	bool Equal(const Vector2D &B, double tolerance) const;
	bool NotEqual(const Vector2D &B, double tolerance) const;
	
	// Arithmetic operators.
	Vector2D  operator - (const Vector2D &B) const;
	Vector2D  operator + (const Vector2D &B) const;
	Vector2D  operator * (double s) const;
	Vector2D  operator / (double s) const;
	Vector2D& operator -=(const Vector2D &B);
	Vector2D& operator +=(const Vector2D &B);
	Vector2D& operator *=(double s);
	Vector2D& operator /=(double s);
	
	// Assignment, indexing and casting operators.
	double& operator [](int index);
	double  operator [](int index) const;
	Vector2D& operator =(const Vector2D &B);
	
	// Constructors and destructor.
	Vector2D();
	Vector2D(const Vector2D &B);
	Vector2D(double a, double b);
	Vector2D(double point[2]);
	virtual ~Vector2D();
	
public:
	
	double x;	// x coordinate.
	double y;	// y coordinate.
};

typedef std::vector<Vector2D> Vector2DArray;

// for file IO.
std::ostream& operator <<(std::ostream& fout, const std::vector<Vector2D>& B);
std::istream& operator >>(std::istream& fin , std::vector<Vector2D>& B);

};	// End namespace SMathLib.

#endif // _SMATHLIB_VECTOR2D_H_
