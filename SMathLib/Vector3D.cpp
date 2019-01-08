
#include "Vector3D.h"
#include "Matrix.h"
#include <cassert>
#include <cmath>

namespace SMathLib {
;

// constructors and destructor.
// ------------------------------------------------------------------------- //
// default constructor.
Vector3D::Vector3D()
{
	x = y = z = 0.0;
}
// construct a vector from given point (a, b, c).
Vector3D::Vector3D(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}
// construct a vector from an array.
Vector3D::Vector3D(double data[3])
{
	x = data[0];
	y = data[1];
	z = data[2];
}
// copy constructor.
Vector3D::Vector3D(const Vector3D &B)
{
	x = B.x;
	y = B.y;
	z = B.z;
}
// destructor
Vector3D::~Vector3D()
{
	//nothing to destruct!!
}
// ------------------------------------------------------------------------- //



// assignment, indexing and casting operators.
// ------------------------------------------------------------------------- //

// assignment operator.
Vector3D& Vector3D::operator =(const Vector3D &B)
{
	x = B.x;
	y = B.y;
	z = B.z;
	return *this;
}
// index operator.
double& Vector3D::operator [](const int index)
{
	assert(index == 0 || index == 1 || index == 2);
	
	if(index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}
double Vector3D::operator [](const int index) const
{
	assert(index == 0 || index == 1 || index == 2);
	
	if(index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}
// ------------------------------------------------------------------------- //



// arithmetic operators.
// ------------------------------------------------------------------------- //

// add two vectors.
Vector3D Vector3D::operator +(const Vector3D &B) const
{
	return Vector3D(x+B.x, y+B.y, z+B.z);
}
// add two vectors.
Vector3D& Vector3D::operator +=(const Vector3D &B)
{
	x = x + B.x;
	y = y + B.y;
	z = z + B.z;
	return *this;
}
// subtract two vectors.
Vector3D Vector3D::operator -(const Vector3D &B) const
{
	return Vector3D(x-B.x, y-B.y, z-B.z);
}
// subtract two vectors.
Vector3D& Vector3D::operator -=(const Vector3D &B)
{
 	x = x - B.x;
	y = y - B.y;
	z = z - B.z;
 	return *this;
}
// scalar multiple of a vector.
Vector3D Vector3D::operator *(double s) const
{
	return Vector3D(x*s, y*s, z*s);
}
// scalar multiple of a vector.
Vector3D& Vector3D::operator *=(double s)
{
	x = x*s;
	y = y*s;
	z = z*s;
	return *this;
}
Matrix Vector3D::operator *(const Vector3D &B) const
{
	Matrix A(3,1), At(1,3);
	
	A (0,0) = x;	 A(1,0) = y;		A (2,0) = z;
	At(0,0) = B.x;	At(0,1) = B.y;		At(0,2) = B.z;
	
	return A * At;
}
// scalar division.
Vector3D Vector3D::operator /(double s) const
{
	return Vector3D(x/s, y/s, z/s);
}
// scalar division.
Vector3D& Vector3D::operator /= (double s)
{
	x = x/s;
	y = y/s;
	z = z/s;
	return *this;
}
// ------------------------------------------------------------------------- //



// logical operators.
// ------------------------------------------------------------------------- //

// checks for equivalence of two vectors.
bool Vector3D::Equal(const Vector3D &B, double tolerance) const
{
	if(fabs(x-B.x)<=tolerance && fabs(y-B.y)<=tolerance && fabs(z-B.z)<=tolerance)
		 return true;	// vectors are Equal.
	else
		return false;	// vectors are not Equal.
}
// checks for equivalence of two vectors.
bool Vector3D::NotEqual(const Vector3D &B, double tolerance) const
{
	if(fabs(x-B.x)<=tolerance && fabs(y-B.y)<=tolerance && fabs(z-B.z)<=tolerance)
		 return false;	// vectors are Equal.
	else
		return true;	// vectors are not Equal.
}
// check if two vectors ar Equal.
bool Vector3D::operator ==(const Vector3D &B) const
{
	if(x==B.x && y==B.y && z==B.z)
		 return true;
	else
		return false;
}
// check if two vectors are not Equal.
bool Vector3D::operator !=(const Vector3D &B) const
{
	if(x==B.x && y==B.y && z==B.z)
		return false;
	else
		return true;
}
// less then operator.
bool Vector3D::operator <(const Vector3D &B) const
{
	if(x<B.x && y<B.y && z<B.z)
		return true;
	else
		return false;
}
// less then operator.
bool Vector3D::operator >(const Vector3D &B) const
{
	if(x>B.x && y>B.y && z>B.z)
		return true;
	else
		return false;
}
// less then operator.
bool Vector3D::operator <=(const Vector3D &B) const
{
	if(x<=B.x && y<=B.y && z<=B.z)
		return true;
	else
		return false;
}
// less then operator.
bool Vector3D::operator >=(const Vector3D &B) const
{
	if(x>=B.x && y>=B.y && z>=B.z)
		return true;
	else
		return false;
}
// ------------------------------------------------------------------------- //



// unary operators.
// ------------------------------------------------------------------------- //
Vector3D Vector3D::operator -() const
{
	return Vector3D(-x, -y, -z);
}
// ------------------------------------------------------------------------- //



// functions.
// ------------------------------------------------------------------------- //

// computes Magnitude of the vector.
double Vector3D::Magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}
// computes Magnitude of the vector.
double Vector3D::Magnitude2() const
{
	return x*x + y*y + z*z;
}
// Normalize vector.
void Vector3D::Normalize()
{
	double mag = sqrt(x*x + y*y + z*z);
	if(mag != 0)
	{
		x = x/mag;
		y = y/mag;
		z = z/mag;
	}
}
// dot product of two vectors OR inner product.
double Vector3D::DotProduct(const Vector3D &B) const
{
	return (x*B.x + y*B.y + z*B.z);
}
// compute cross-product of two vectors.
Vector3D Vector3D::CrossProduct(const Vector3D &B, bool bNormalize) const
{
	Vector3D A = *this;	// make a local copy.
	
	Vector3D temp;
	temp.x = A[1]*B.z - A[2]*B.y;
	temp.y = A[2]*B.x - A[0]*B.z;
	temp.z = A[0]*B.y - A[1]*B.x;
	
	if(bNormalize)
		temp.Normalize();
	
	return temp;
}
// euclidean Distance between two points.
double Vector3D::Distance(const Vector3D &B) const
{
	return sqrt((B.x-x)*(B.x-x) + (B.y-y)*(B.y-y) + (B.z-z)*(B.z-z) );
}
// ------------------------------------------------------------------------- //



// ------------------------------------------------------------------------- //
// for standard IO.
std::ostream& operator <<(std::ostream& out, const Vector3D& B)
{
	out << B.x << " " << B.y << " " << B.z;
	return out;
}
std::istream& operator >>(std::istream& in, Vector3D &B)
{
	in >> B.x >> B.y >> B.z;
	return in;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
// predicate for sorting points in decreasing order of X coordinate.
bool v3DLesserX(const Vector3D &v1, const Vector3D &v2)
{
	if(v1[0]<v2[0])
		return true;
	else
		return false;
}
// predicate for sorting points in decreasing order of Y coordinate.
bool v3DLesserY(const Vector3D &v1, const Vector3D &v2)
{
	if(v1[1]<v2[1])
		return true;
	else
		return false;
}
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
// output stream.
std::ostream& operator <<(std::ostream& fout, const std::vector<Vector3D>& B)
{
	fout << B.size();
	
	for(size_t i=0 ; i<B.size() ; i++)
		fout << std::endl << B[i];
	
	return fout;
}
// input stream.
std::istream& operator >>(std::istream& fin, std::vector<Vector3D>& B)
{
	int size;
	fin >> size;
	
	for(int i=0 ; i<size ; i++)
	{
		Vector3D p;
		fin >> p;
		B.push_back(p);
	}
	
	return fin;
}
// ------------------------------------------------------------------------- //

};	// End namespace SMathLib.
