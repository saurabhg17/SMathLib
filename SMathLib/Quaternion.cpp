// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#include "Quaternion.h"
#include "VectorAlgo.h"
#include "Constants.h"

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! The default constructor, initializes to a unit Quaternion.
Quaternion::Quaternion()
{
	mQuaternion[0] = 0.0;
	mQuaternion[1] = 0.0;
	mQuaternion[2] = 0.0;
	mQuaternion[3] = 1.0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Construct from the four values of a Quaternion. 
//! First three values are axis*sin(angle/2) and last one is cos(angle/2).
Quaternion::Quaternion(double q0, double q1, double q2, double q3)
{
	mQuaternion[0] = q0;
	mQuaternion[1] = q1;
	mQuaternion[2] = q2;
	mQuaternion[3] = q3;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Construct from rotation axis and angle in radians.
Quaternion::Quaternion(const Vector3& axis, double angle)
{
	SetAxisAngle(axis, angle);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Construct a quaternion that will rotate vector v1 to vector v2.
//! This rotation is not uniquely defined. The selected axis is usually 
//! orthogonal to v1 and v2 minimizing the rotation angle.
//! This method is robust and can handle small or almost identical vectors.
Quaternion::Quaternion(const Vector3& v1, const Vector3& v2)
{
	double _epsilon = 1e-8;
	double _v1MagSq = glVectorMagnitude2(v1, 3);
	double _v2MagSq = glVectorMagnitude2(v2, 3);
	
	// If either of input vectors have very small magnitude then
	// create a unit quaternion. 
	// Note that normalizing a vector with very small magnitude 
	// is not stable.
	if((_v1MagSq<_epsilon) || (_v2MagSq<_epsilon))
	{
		mQuaternion[0] = 0.0;
		mQuaternion[1] = 0.0;
		mQuaternion[2] = 0.0;
		mQuaternion[3] = 1.0;
	}
	else
	{
		// Find a vector orthogonal to v1 and v2.
		Vector3 _axis      = glCrossProduct3D(v1, v2);
		double  _axisMagSq = glVectorMagnitude2(_axis, 3);
		
		// The angle between two vectors.
		double _angle = asin(sqrt(_axisMagSq/(_v1MagSq*_v2MagSq)));
		if(glDotProduct(v1, v2, 3) < 0.0)
		{
			_angle = gcPi - _angle;
		}
		
		// If v1 and v2 are nearly parallel then _axisMagSq will be 
		// very small.
		if(_axisMagSq < _epsilon)
		{
			// Don't know how to handle this case.
		}
		
		SetAxisAngle(_axis, _angle);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Copy constructor.
Quaternion::Quaternion(const Quaternion& B)
{
	*this = B;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Assignment operator.
Quaternion& Quaternion::operator=(const Quaternion& B)
{
	mQuaternion[0] = B.mQuaternion[0];
	mQuaternion[1] = B.mQuaternion[1];
	mQuaternion[2] = B.mQuaternion[2];
	mQuaternion[3] = B.mQuaternion[3];
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Multiply two quaternions.
//! Note that quaternion multiplication is in general not commutative.
Quaternion Quaternion::operator * (const Quaternion& B) const
{
	double x0 = mQuaternion[0];
	double y0 = mQuaternion[1];
	double z0 = mQuaternion[2];
	double w0 = mQuaternion[3];
	double x1 = B.mQuaternion[0];
	double y1 = B.mQuaternion[1];
	double z1 = B.mQuaternion[2];
	double w1 = B.mQuaternion[3];
	
	return Quaternion(w0*x1 + x0*w1 + y0*z1 - z0*y1,
					  w0*y1 - x0*z1 + y0*w1 + z0*x1,
					  w0*z1 + x0*y1 - y0*x1 + z0*w1,
					  w0*w1 - x0*x1 - y0*y1 - z0*z1);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Multiple two quaternions and modify the first quaternion.
//! Note that quaternion multiplication is in general not commutative.
Quaternion& Quaternion::operator *= (const Quaternion& B)
{
	*this = (*this) * B;
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Negates all the coefficients of a Quaternion.
//! The effect is that quaternion remains same but the direction of axis is 
//! and sign of angle are reversed.
Quaternion Quaternion::operator - () const
{
	return Quaternion(-mQuaternion[0], -mQuaternion[1], -mQuaternion[2], -mQuaternion[3]);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Negates all the coefficients of a Quaternion.
//! The effect of quaternion remains same but the direction of axis is 
//! and sign of angle are reversed.
void Quaternion::Negate()
{
	mQuaternion[0] = -mQuaternion[0];
	mQuaternion[1] = -mQuaternion[1];
	mQuaternion[2] = -mQuaternion[2];
	mQuaternion[3] = -mQuaternion[3];
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute the inverse of a quaternion and return a new quaternion.
//! Inverting a quaternion inverts the direction of the axis of quaternion 
//! and angle remains same.
Quaternion Quaternion::Inverse() const
{
	return Quaternion(-mQuaternion[0], -mQuaternion[1], -mQuaternion[2], +mQuaternion[3]);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute the inverse of a quaternion.
//! Inverting a quaternion inverts the direction of the axis of quaternion 
//! and angle remains same.
void Quaternion::Invert()
{
	mQuaternion[0] = -mQuaternion[0];
	mQuaternion[1] = -mQuaternion[1];
	mQuaternion[2] = -mQuaternion[2];
	mQuaternion[3] = +mQuaternion[3];
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute a normalized quaternion.
Quaternion Quaternion::Normalized() const
{
	Quaternion _temp = *this;
	_temp.Normalize();
	return _temp;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Normalize the quaternion.
double Quaternion::Normalize()
{
	double _magnitude = glVectorMagnitude<double*>(mQuaternion, 4);
	mQuaternion[0] /= _magnitude;
	mQuaternion[1] /= _magnitude;
	mQuaternion[2] /= _magnitude;
	mQuaternion[3] /= _magnitude;
	return _magnitude;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Rotate a vector v by the quaternion.
Quaternion::Vector3 Quaternion::RotateVector(const Vector3& v) const
{
	double q00 = 2.0 * mQuaternion[0] * mQuaternion[0];
	double q01 = 2.0 * mQuaternion[0] * mQuaternion[1];
	double q02 = 2.0 * mQuaternion[0] * mQuaternion[2];
	double q03 = 2.0 * mQuaternion[0] * mQuaternion[3];
	double q11 = 2.0 * mQuaternion[1] * mQuaternion[1];
	double q12 = 2.0 * mQuaternion[1] * mQuaternion[2];
	double q13 = 2.0 * mQuaternion[1] * mQuaternion[3];
	double q22 = 2.0 * mQuaternion[2] * mQuaternion[2];
	double q23 = 2.0 * mQuaternion[2] * mQuaternion[3];
	
	double x = (1.0 - q11 - q22)*v[0] + (      q01 - q23)*v[1] + (      q02 + q13)*v[2];
	double y = (      q01 + q23)*v[0] + (1.0 - q22 - q00)*v[1] + (      q12 - q03)*v[2];
	double z = (      q02 - q13)*v[0] + (      q12 + q03)*v[1] + (1.0 - q11 - q00)*v[2];
	return Vector3(x, y, z);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Rotate a vector v by inverse of the quaternion.
Quaternion::Vector3 Quaternion::InverseRotateVector(const Vector3& v) const
{
	return Inverse().RotateVector(v);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Set the quaternion using an axis and angle.
void Quaternion::SetAxisAngle(const Vector3& axis, double angle)
{
	double _magnitude = glVectorMagnitude(axis, 3);
	if(_magnitude<1e-8)
	{
		mQuaternion[0] = 0.0;
		mQuaternion[1] = 0.0;
		mQuaternion[2] = 0.0;
		mQuaternion[3] = 1.0;
	}
	else
	{
		double _sinAngleBy2 = sin(angle/2.0);
		mQuaternion[0] = _sinAngleBy2*axis[0]/_magnitude;
		mQuaternion[1] = _sinAngleBy2*axis[1]/_magnitude;
		mQuaternion[2] = _sinAngleBy2*axis[2]/_magnitude;
		mQuaternion[3] = cos(angle/2.0);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Set the Quaternion from a 3x3 rotation matrix.
//! The matrix is expressed in European format: its three columns are the 
//! images by the rotation of the three vectors of an orthogonal basis. 
//! Note that OpenGL uses a symmetric representation for its matrices.
void Quaternion::SetRotationMatrix(const double rotMat[3][3])
{
	// Compute one plus the trace of the matrix
	double _onePlusTrace = 1.0 + rotMat[0][0] + rotMat[1][1] + rotMat[2][2];
	
	if(_onePlusTrace > 1E-5)
	{
		double s = sqrt(_onePlusTrace) * 2.0;
		mQuaternion[0] = (rotMat[2][1] - rotMat[1][2]) / s;
		mQuaternion[1] = (rotMat[0][2] - rotMat[2][0]) / s;
		mQuaternion[2] = (rotMat[1][0] - rotMat[0][1]) / s;
		mQuaternion[3] = 0.25 * s;
	}
	else
	{
		if((rotMat[0][0] > rotMat[1][1])&(rotMat[0][0] > rotMat[2][2]))
		{ 
			double s = sqrt(1.0 + rotMat[0][0] - rotMat[1][1] - rotMat[2][2]) * 2.0; 
			mQuaternion[0] = 0.25 * s;
			mQuaternion[1] = (rotMat[0][1] + rotMat[1][0]) / s; 
			mQuaternion[2] = (rotMat[0][2] + rotMat[2][0]) / s; 
			mQuaternion[3] = (rotMat[1][2] - rotMat[2][1]) / s;
		}
		else if(rotMat[1][1] > rotMat[2][2])
		{ 
			double s = sqrt(1.0 + rotMat[1][1] - rotMat[0][0] - rotMat[2][2]) * 2.0; 
			mQuaternion[0] = (rotMat[0][1] + rotMat[1][0]) / s; 
			mQuaternion[1] = 0.25 * s;
			mQuaternion[2] = (rotMat[1][2] + rotMat[2][1]) / s; 
			mQuaternion[3] = (rotMat[0][2] - rotMat[2][0]) / s;
		}
		else
		{ 
			double s = sqrt(1.0 + rotMat[2][2] - rotMat[0][0] - rotMat[1][1]) * 2.0; 
			mQuaternion[0] = (rotMat[0][2] + rotMat[2][0]) / s; 
			mQuaternion[1] = (rotMat[1][2] + rotMat[2][1]) / s; 
			mQuaternion[2] = 0.25 * s;
			mQuaternion[3] = (rotMat[0][1] - rotMat[1][0]) / s;
		}
	}
	
	Normalize();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Quaternion::SetRotatedBasis(const Vector3& X, const Vector3& Y, const Vector3& Z)
{
	double _rotMat[3][3];
	double _normX = glVectorMagnitude(X, 3);
	double _normY = glVectorMagnitude(Y, 3);
	double _normZ = glVectorMagnitude(Z, 3);
	
	for(int i=0; i<3; ++i)
	{
		_rotMat[i][0] = X[i]/_normX;
		_rotMat[i][1] = Y[i]/_normY;
		_rotMat[i][2] = Z[i]/_normZ;
	}
	
	SetRotationMatrix(_rotMat);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
Quaternion::Vector3 Quaternion::GetAxis() const
{
	Vector3 _axis(mQuaternion[0], mQuaternion[1], mQuaternion[2]);
	double  _mag = glVectorMagnitude(_axis, 3);
	if(_mag > 1e-8)
	{
		_axis /= _mag;
	}
	
	// If angle is larger then PI then invert the axis.
	return (acos(mQuaternion[3]) <= gcPiBy2) ? _axis : -_axis;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
double Quaternion::GetAngle() const
{
	double _angle = 2.0 * acos(mQuaternion[3]);
	return (_angle <= gcPi) ? _angle : 2.0*gcPi-_angle;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Quaternion::GetAxisAngle(Vector3* axis, double* angle) const
{
	*axis  = GetAxis();
	*angle = GetAngle();
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Row major order.
void Quaternion::GetMatrix(double rotMat[16]) const
{
	double q00 = 2.0 * mQuaternion[0] * mQuaternion[0];
	double q01 = 2.0 * mQuaternion[0] * mQuaternion[1];
	double q02 = 2.0 * mQuaternion[0] * mQuaternion[2];
	double q03 = 2.0 * mQuaternion[0] * mQuaternion[3];
	double q11 = 2.0 * mQuaternion[1] * mQuaternion[1];
	double q12 = 2.0 * mQuaternion[1] * mQuaternion[2];
	double q13 = 2.0 * mQuaternion[1] * mQuaternion[3];
	double q22 = 2.0 * mQuaternion[2] * mQuaternion[2];
	double q23 = 2.0 * mQuaternion[2] * mQuaternion[3];
	
	rotMat[4*0+0] = 1.0 - q11 - q22;
	rotMat[4*0+1] =       q01 - q23;
	rotMat[4*0+2] =       q02 + q13;
	rotMat[4*0+3] = 0.0;
	
	rotMat[4*1+0] =       q01 + q23;
	rotMat[4*1+1] = 1.0 - q22 - q00;
	rotMat[4*1+2] =       q12 - q03;
	rotMat[4*1+3] = 0.0;
	
	rotMat[4*2+0] =       q02 - q13;
	rotMat[4*2+1] =       q12 + q03;
	rotMat[4*2+2] = 1.0 - q11 - q00;
	rotMat[4*2+3] = 0.0;
	
	rotMat[4*3+0] = 0.0;
	rotMat[4*3+1] = 0.0;
	rotMat[4*3+2] = 0.0;
	rotMat[4*3+3] = 1.0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Row major order.
void Quaternion::GetRotationMatrix(double rotMat[9]) const
{
	double q00 = 2.0 * mQuaternion[0] * mQuaternion[0];
	double q01 = 2.0 * mQuaternion[0] * mQuaternion[1];
	double q02 = 2.0 * mQuaternion[0] * mQuaternion[2];
	double q03 = 2.0 * mQuaternion[0] * mQuaternion[3];
	double q11 = 2.0 * mQuaternion[1] * mQuaternion[1];
	double q12 = 2.0 * mQuaternion[1] * mQuaternion[2];
	double q13 = 2.0 * mQuaternion[1] * mQuaternion[3];
	double q22 = 2.0 * mQuaternion[2] * mQuaternion[2];
	double q23 = 2.0 * mQuaternion[2] * mQuaternion[3];
	
	rotMat[3*0+0] = 1.0 - q11 - q22;
	rotMat[3*0+1] =       q01 - q23;
	rotMat[3*0+2] =       q02 + q13;
	
	rotMat[3*1+0] =       q01 + q23;
	rotMat[3*1+1] = 1.0 - q22 - q00;
	rotMat[3*1+2] =       q12 - q03;
	
	rotMat[3*2+0] =       q02 - q13;
	rotMat[3*2+1] =       q12 + q03;
	rotMat[3*2+2] = 1.0 - q11 - q00;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Quaternion::GetInverseMatrix(double rotMat[16]) const
{
	Inverse().GetMatrix(rotMat);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void Quaternion::GetInverseRotationMatrix(double rotMat[9]) const
{
	Inverse().GetRotationMatrix(rotMat);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, 
							 double time, bool allowFlip)
{
	double _cosAngle = glDotProduct(q1, q2, 4);
	double c1 = 0;
	double c2 = 0;
	
	// Linear interpolation for close orientations
	if((1.0 - fabs(_cosAngle)) < 0.01)
	{
		c1 = 1.0 - time;
		c2 = time;
	}
	// Spherical interpolation
	else
	{	
		double _angle    = acos(fabs(_cosAngle));
		double _sinAngle = sin(_angle);
		c1 = sin(_angle * (1.0 - time))/_sinAngle;
		c2 = sin(_angle * time)/_sinAngle;
	}
	
	// Use the shortest path
	if(allowFlip && (_cosAngle < 0.0))
	{
		c1 = -c1;
	}
	
	double a0 = c1*q1.mQuaternion[0] + c2*q2.mQuaternion[0];
	double a1 = c1*q1.mQuaternion[1] + c2*q2.mQuaternion[1];
	double a2 = c1*q1.mQuaternion[2] + c2*q2.mQuaternion[2];
	double a3 = c1*q1.mQuaternion[3] + c2*q2.mQuaternion[3];
	return Quaternion(a0, a1, a2, a3);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
