
#ifndef _SMATHLIB_QUATERNION_H_
#define _SMATHLIB_QUATERNION_H_

#include "SMathLib/Config.h"
#include "SMathLib/VectorOnStack.h"

namespace SMathLib {
;

//! A class for storing and manipulating Quaternions.
class SMATHLIB_DLL_API Quaternion
{
public:
	
	//! Define a type for vector.
	typedef VectorOnStackD3 Vector3;
	
	//! Define type of elements stores.
	typedef double value_type;
	
public:  // Constructors.
	
	Quaternion();
	Quaternion(double q0, double q1, double q2, double q3);
	Quaternion(const Vector3& axis, double angle);
	Quaternion(const Vector3& v1, const Vector3& v2);
	Quaternion(const Quaternion& B);
	Quaternion& operator=(const Quaternion& B);
	
public:  // Indexing operator.
	
	inline double  operator[](int i) const {return mQuaternion[i];}
	inline double& operator[](int i)       {return mQuaternion[i];}
	
public:  // Operation on quaternion.
	
	Quaternion  operator *  (const Quaternion& B) const;
	Quaternion& operator *= (const Quaternion& B);
	Quaternion  operator -  () const;
	
	void       Negate();
	Quaternion Inverse() const;
	void       Invert();
	Quaternion Normalized() const;
	double     Normalize();
	Vector3    RotateVector(const Vector3& v) const;
	Vector3    InverseRotateVector(const Vector3& v) const;
	
public:  // Initialize quaternion from other representations.
	
	void SetAxisAngle(const Vector3& axis, double angle);
	void SetRotationMatrix(const double rotationMatrix[3][3]);
	void SetRotatedBasis(const Vector3& X, const Vector3& Y, const Vector3& Z);
	
public:  // Convert quaternion to other representations.
	
	Vector3 GetAxis() const;
	double  GetAngle() const;
	void    GetAxisAngle(Vector3* axis, double* angle) const;
	
	void GetMatrix(double matrix[16]) const;
	void GetRotationMatrix(double matrix[9]) const;
	
	void GetInverseMatrix(double matrix[16]) const;
	void GetInverseRotationMatrix(double matrix[9]) const;
	
public:  // Spherical linear interpolation between two quaternions.
	
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, 
							double time, bool allowFlip);
	
private:
	
	//! Storage space for the quaternion.
	double mQuaternion[4];
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_QUATERNION_H_
