// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_MINMAX_H_
#define _SMATHLIB_MINMAX_H_

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Function to compute maximum of two values.
//! \param T Any type supporting greater than (>) operator.
//! \param a First value.
//! \param b Second value.
//! \return Larger of a and b.
template<typename T>
T glMax(const T& a, const T& b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
//! Function to compute maximum of three values.
//! \param T Any type supporting greater than (>) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \return Larger of a, b, and c.
template<typename T>
T glMax(const T& a, const T& b, const T& c)
{
	return glMax(a, glMax(b, c));
}
//! Function to compute maximum of four values.
//! \param T Any type supporting greater than (>) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \param d Fourth value.
//! \return Larger of a, b, c, and d.
template<typename T>
T glMax(const T& a, const T& b, const T& c, const T& d)
{
	return glMax(a, glMax(b, c, d));
}
//! Function to compute maximum of five values.
//! \param T Any type supporting greater than (>) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \param d Fourth value.
//! \param e Fifth value.
//! \return Larger of a, b, c, d, and e.
template<typename T>
T glMax(const T& a, const T& b, const T& c, const T& d, const T& e)
{
	return glMax(a, glMax(b, c, d, e));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Function to compute minimum of two values.
//! \param T Any type supporting less than (<) operator.
//! \param a First value.
//! \param b Second value.
//! \return Smaller of a and b.
template<typename T>
T glMin(const T& a, const T& b)
{
	if(a < b)
	{
		return a;
	}
	else 
	{
		return b;
	}
}
//! Function to compute minimum of three values.
//! \param T Any type supporting lesser than (<) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \return Smaller of a, b, and c.
template<typename T>
T glMin(const T& a, const T& b, const T& c)
{
	return glMin(a, glMin(b, c));
}
//! Function to compute minimum of four values.
//! \param T Any type supporting lesser than (<) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \param d Fourth value.
//! \return Smaller of a, b, c, and d.
template<typename T>
T glMin(const T& a, const T& b, const T& c, const T& d)
{
	return glMin(a, glMin(b, c, d));
}
//! Function to compute minimum of five values.
//! \param T Any type supporting lesser than (<) operator.
//! \param a First value.
//! \param b Second value.
//! \param c Third value.
//! \param d Fourth value.
//! \param e Fifth value.
//! \return Smaller of a, b, c, d, and e.
template<typename T>
T glMin(const T& a, const T& b, const T& c, const T& d, const T& e)
{
	return glMin(a, glMin(b, c, d, e));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.

#endif // _SMATHLIB_MINMAX_H_
