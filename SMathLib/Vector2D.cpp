// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "Vector2D.h"
#include <cassert>
#include <cmath>

namespace SMathLib {
;

// ------------------------------------------------------------------------- //
// default constructor.
Vector2D::Vector2D()
{
	x = y = 0;
}
// construct point using two numbers.
Vector2D::Vector2D(double a, double b)
{
	x = a;
	y = b;
}
// construct point using an array.
Vector2D::Vector2D(double data[2])
{
	x = data[0];
	y = data[1];
}
// copy constructor.
Vector2D::Vector2D(const Vector2D &B)
{
	x = B.x;
	y = B.y;
}
// destructor.
Vector2D::~Vector2D()
{
	//nothing to destruct.
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// index operator.
double& Vector2D::operator [](int index)
{
	assert(index==0 || index==1);
	
	if(index == 0)
		return x;
	else
		return y;
}
// const version of indexing operator.
double Vector2D::operator [](int index) const
{
	assert(index==0 || index==1);
	
	if(index == 0)
		return x;
	else
		return y;
}
// assignment operator.
Vector2D& Vector2D::operator =(const Vector2D &B)
{
	x = B.x;
	y = B.y;
	return *this;
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// Point addition.
Vector2D Vector2D::operator +(const Vector2D &B) const
{
	return Vector2D(x+B.x, y+B.y);
}
// Point addition.
Vector2D& Vector2D::operator +=(const Vector2D &B)
{
	x = x + B.x;
	y = y + B.y;
	return *this;
}
// Vector subtraction.
Vector2D Vector2D::operator -(const Vector2D &B) const
{
	return Vector2D(x-B.x, y-B.y);
}
// Vector subtraction.
Vector2D& Vector2D::operator -=(const Vector2D &B)
{
	x = x - B.x;
	y = y - B.y;
	return *this;
}
// Scalar multiplication.
Vector2D Vector2D::operator *(double s) const
{
	return Vector2D(x*s, y*s);
}
// Scalar multiplication.
Vector2D& Vector2D::operator *=(double s)
{
	x = x * s;
	y = y * s;
	return *this;
}
// Scalar division.
Vector2D Vector2D::operator /(double s) const
{
	return Vector2D(x/s, y/s);
}
// Scalar division.
Vector2D& Vector2D::operator /=(double s)
{
	x = x / s;
	y = y / s;
	return *this;
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// Check if two vectors are equal with tolerance.
bool Vector2D::Equal(const Vector2D &B, double tolerance) const
{
	if(fabs(x-B.x)<=tolerance && fabs(y-B.y)<=tolerance)
		return true;
	else
		return false;
}
// Check if two vectors are not equal with tolerance.
bool Vector2D::NotEqual(const Vector2D &B, double tolerance) const
{
	if(fabs(x-B.x)<=tolerance && fabs(y-B.y)<=tolerance)
		return false;
	else
		return true;
}
// Equality check
bool Vector2D::operator ==(const Vector2D &B) const
{
	if(x == B.x && y == B.y)
		 return true;
	else
		return false;
}
// Equality check
bool Vector2D::operator !=(const Vector2D &B) const
{
	if(x == B.x && y == B.y)
		 return false;
	else
		return true;
}
// Greater then operator.
bool Vector2D::operator >(const Vector2D &B) const
{
	if(x>B.x && y>B.y)
		return true;
	else
		return false;
}
// Less then operator.
bool Vector2D::operator <(const Vector2D &B) const
{
	if(x<B.x && y<B.y)
		return true;
	else
		return false;
}
// Less then equal to operator.
bool Vector2D::operator <=(const Vector2D &B) const
{
	if(x<=B.x && y<=B.y)
		return true;
	else
		return false;
}
// Greater then equal to operator.
bool Vector2D::operator >=(const Vector2D &B) const
{
	if(x>=B.x && y>=B.y)
		return true;
	else
		return false;
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// Compute magnitude.
double Vector2D::Magnitude() const
{
	return sqrt(x*x + y*y);
}
// Compute square of magnitude.
double Vector2D::Magnitude2() const
{
	return x*x + y*y;
}
// Normalize vector.
void Vector2D::Normalize()
{
	double mag = sqrt(x*x + y*y);
	if(mag != 0)
	{
		x = x/mag;
		y = y/mag;
	}
}
// Dot product
double Vector2D::DotProduct(const Vector2D &B) const
{
	return x*B.x + y*B.y;
}
// Euclidean distance between two points.
double Vector2D::Distance(const Vector2D &B) const
{
	return sqrt( (B.x-x)*(B.x-x) + (B.y-y)*(B.y-y) );
}
// ------------------------------------------------------------------------- //




// ------------------------------------------------------------------------- //
// standard output.
std::ostream& operator <<(std::ostream& out, const Vector2D &B)
{
	out << B.x << " " << B.y;
	return out;
}
// standard input.
std::istream& operator >>(std::istream& in, Vector2D &B)
{
	in >> B.x >> B.y;
	return in;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
bool v2DEqual(const Vector2D& v1, const Vector2D &v2)
{
	if(v1 == v2)
		return true;
	else
		return false;
}
// Predicate for sorting points in decreasing order of X coordinate.
bool v2DLesserX(const Vector2D &v1, const Vector2D &v2)
{
	if(v1[0] < v2[0])
		return true;
	else
		return false;
}
// Predicate for sorting points in decreasing order of Y coordinate.
bool v2DLesserY(const Vector2D &v1, const Vector2D &v2)
{
	if(v1[1] < v2[1])
		return true;
	else
		return false;
}
// Predicate for sorting points in decreasing order of XY coordinate.
bool v2DLesserXY(const Vector2D &v1, const Vector2D &v2)
{
	// first point X-coordinate less then second point X-coordinate 
	// so v1 is 'smaller' point then v2.
	if(v1[0] < v2[0])
		return true;
	
	// second point X-coordinate less then first point X-coordinate 
	// so v2 is 'smaller' point then v1.
	else if(v1[0] > v2[0])
		return false;
	
	// both coordinates equal so check in Y-dir.
	else
	{
		if(v1[1] < v2[1])
			return true;
		
		else
			return false;
	}
}
// Predicate for sorting points in decreasing order of YX coordinate.
bool v2DLesserYX_T(const Vector2D &v1, const Vector2D &v2)
{
	// first point X-coordinate less then second point X-coordinate 
	// so v1 is 'smaller' point then v2.
	if(fabs(v1[1]-v2[1]) < 4)
		return true;
	
	// second point X-coordinate less then first point X-coordinate 
	// so v2 is 'smaller' point then v1.
	else if(fabs(v1[1]-v2[1]) > 4)
		return false;
	
	// both coordinates equal so check in Y-dir.
	else
	{
		if(v1[0] < v2[0])
			return true;
		
		else
			return false;
	}
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// Output stream.
std::ostream& operator <<(std::ostream& fout, const std::vector<Vector2D>& B)
{
	fout << B.size() << std::endl;
	
	for(size_t i=0 ; i<B.size() ; i++)
		fout << B[i] << std::endl;
	
	return fout;
}
// Input stream.
std::istream& operator >>(std::istream& fin, std::vector<Vector2D>& B)
{
	int size;
	fin >> size;
	
	for(int i=0 ; i<size ; i++)
	{
		Vector2D p;
		fin >> p;
		B.push_back(p);
	}
	
	return fin;
}
// ------------------------------------------------------------------------- //

};	// End namespace SMathLib.
