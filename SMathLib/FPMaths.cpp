
#include "FPMaths.h"
#include "Constants.h"
#include "SUtils/Types.h"
#include <cfloat>
#include <algorithm>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Double precision IEEE 754 number format.
// 1  bit for sign.
// 11 bits for exponent. [0, 2047]
// 52 bits for mantissa. 
// Exponent range = [-1022, +1023].
//    Exponent value of 0 (all zeros) is reserved for denormalized numbers.
//    Exponent value of 2047 (all ones) is reserved for NaN's and Inf's.
//    A bias of 1023 is added the to exponent so that they are 
//    lexicographically ordered from 1 to 2046.
int glExponentOfDouble(double x)
{
	return int((((*(__int64*)&x & 0x7FF0000000000000LL) >> 52) - 1023));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool glIsInfinite(double A)
{
	// Representation of infinity for double precision number.
	static const __int64 _kInfAsInt = 0x7FF0000000000000LL;
	
	// An infinity has an exponent of 1023 (shift left 52 positions) and
	// a zero mantissa. There are two infinities - positive and negative.
	if ((*(__int64*)&A & 0x7FFFFFFFFFFFFFFFLL) == _kInfAsInt)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
bool glIsNan(double A)
{
	// A NAN has an exponent of 1023 (shifted left 52 positions) and
	// a non-zero mantissa. There are two Nan's - positive and negative.
	__int64 _exp      = *(__int64*)&A & 0x7FF0000000000000LL;
	__int64 _mantissa = *(__int64*)&A & 0xFFFFFFFFFFFFFLL;
	
	if(_exp == 0x7FF0000000000000LL && _mantissa != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
Sign glSign(double A)
{
	// The sign bit of a number is the highest bit.
	if(((*(__int64*)&A) & 0x8000000000000000LL) > 0)
	{
		return eSign_Negative;
	}
	else
	{
		return eSign_Positive;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
void glKahanSum(double& rSum, const double& val, double& rError)
{
	double y = val - rError;
	double t = rSum + y;
	rError   = (t-rSum) - y;
	rSum     = t;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
#if defined(SMathLib_OS_WINDOWS)
//! This function prints the status of the floating point control word.
void glPrintFpuControlWord(std::ostream& fp)
{
	Uint controlWord;
	int err = _controlfp_s(&controlWord, 0, 0);
	if(err)
	{
		fp << "Error obtaining Fpu control word." << std::endl;
		return;
	}
	
	// De-normal control.
	int denorm = controlWord & _MCW_DN;
	fp << "De-normal (_MCW_DN) control status is           :  ";
	if(denorm == _DN_SAVE)
	{
		fp << "_DN_SAVE" << std::endl;
	}
	else if(denorm == _DN_FLUSH)
	{
		fp << "_DN_FLUSH" << std::endl;
	}
	else
	{
		fp << "Cannot determine" << std::endl;
	}
	
	// Interrupt exception mask.
	int interrupt = controlWord & _MCW_EM;
	fp << "Interrupt exception (_MCW_EM) control status is :  ";
	if(interrupt == _EM_INVALID)
	{
		fp << "_EM_INVALID" << std::endl;
	}
	else if(interrupt == _EM_DENORMAL)
	{
		fp << "_EM_DENORMAL" << std::endl;
	}
	else if(interrupt == _EM_ZERODIVIDE)
	{
		fp << "_EM_ZERODIVIDE" << std::endl;
	}
	else if(interrupt == _EM_OVERFLOW)
	{
		fp << "_EM_OVERFLOW" << std::endl;
	}
	else if(interrupt == _EM_UNDERFLOW)
	{
		fp << "_EM_UNDERFLOW" << std::endl;
	}
	else if(interrupt == _EM_INEXACT)
	{
		fp << "_EM_INEXACT" << std::endl;
	}
	else
	{
		fp << "Exceptions Disabled" << std::endl;
	}
	
	// Infinity control.
	int infinity = controlWord & _MCW_IC;
	fp << "Infinity (_MCW_IC) control status is            :  ";
	if(infinity == _IC_AFFINE)
	{
		fp << "_IC_AFFINE" << std::endl;
	}
	else if(infinity == _IC_PROJECTIVE)
	{
		fp << "_IC_PROJECTIVE" << std::endl;
	}
	else
	{
		fp << "Cannot determine" << std::endl;
	}
	
	// Rounding control.
	int round = controlWord & _MCW_RC;
	fp << "Rounding (_MCW_RC) control status is            :  ";
	if(round == RC_CHOP)
	{
		fp << "RC_CHOP" << std::endl;
	}
	else if(round == _RC_UP)
	{
		fp << "_RC_UP" << std::endl;
	}
	else if(round == _RC_DOWN)
	{
		fp << "_RC_DOWN" << std::endl;
	}
	else if(round == _RC_NEAR)
	{
		fp << "_RC_NEAR" << std::endl;
	}
	else
	{
		fp << "Cannot determine" << std::endl;
	}
	
	// Precision control.
	int precision = controlWord & _MCW_PC;
	fp << "Precision (_MCW_PC) control status is           :  ";
	if(precision == _PC_24)
	{
		fp << "_PC_24" << std::endl;
	}
	else if(precision == _PC_53)
	{
		fp << "_PC_53" << std::endl;
	}
	else if(precision == _PC_64)
	{
		fp << "_PC_64" << std::endl;
	}
	else
	{
		fp << "Cannot determine" << std::endl;
	}
}
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

}; // end namespace SMathLib.
