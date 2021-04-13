// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_CONSTANTS_H_
#define _SMATHLIB_CONSTANTS_H_

#include "SMathLib/Types.h"

namespace SMathLib {
;

//! Value of PI.
const double gcPi = 3.141592653589793238462643383279502884197169399375105820974944592308L;

const double gcPiBy2  = gcPi/2.0;         ///< Value of Pi/2;
const double gcPiBy4  = gcPi/4.0;         ///< Value of Pi/4;
const double gcPiBy6  = gcPi/6.0;         ///< Value of Pi/6;
const double gcPiBy8  = gcPi/8.0;         ///< Value of Pi/8;
const double gc2Pi    = 2.0*gcPi;         ///< Value of 2*Pi;
const double gc3PiBy2 = (3.0*gcPi)/2.0;   ///< Value of 3Pi/2;
const double gcPiInv  = 1.0/gcPi;         ///< value of 1/Pi;


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Bias of the following array, it defines a number such that 
//! gc2Pow[bias - p] = 2^p. For example gc2Pow[bias] will give 2^0.
const int gc2PowBias = 52;

//! Powers from 2^-52 to 2^52.
const double gc2Pow[] = 
{
	2.2204460492503131e-016, 4.4408920985006262e-016, 8.8817841970012523e-016,
	1.7763568394002505e-015, 3.5527136788005009e-015, 7.1054273576010019e-015,
	1.4210854715202004e-014, 2.8421709430404007e-014, 5.6843418860808015e-014,
	1.1368683772161603e-013, 2.2737367544323206e-013, 4.5474735088646412e-013,
	9.0949470177292824e-013, 1.8189894035458565e-012, 3.637978807091713e-012 ,
	7.2759576141834259e-012, 1.4551915228366852e-011, 2.9103830456733704e-011,
	5.8207660913467407e-011, 1.1641532182693481e-010, 2.3283064365386963e-010,
	4.6566128730773926e-010, 9.3132257461547852e-010, 1.862645149230957e-009 ,
	3.7252902984619141e-009, 7.4505805969238281e-009, 1.4901161193847656e-008,
	2.9802322387695313e-008, 5.9604644775390625e-008, 1.1920928955078125e-007,
	2.384185791015625e-007 , 4.76837158203125e-007  , 9.5367431640625e-007   ,
	1.9073486328125e-006   , 3.814697265625e-006    , 7.62939453125e-006     ,
	1.52587890625e-005     , 3.0517578125e-005      , 6.103515625e-005       ,
	0.0001220703125        , 0.000244140625         , 0.00048828125          ,
	0.0009765625           , 0.001953125            , 0.00390625             ,
	0.0078125              , 0.015625               , 0.03125                ,
	0.0625, 0.125, 0.25, 0.5, 
	
	1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 
	2048.0, 4096.0, 8192.0, 16384.0, 32768.0, 65536.0, 131072.0, 262144.0, 524288.0, 1048576.0, 
	2097152.0, 4194304.0, 8388608.0, 16777216.0, 33554432.0, 67108864.0, 134217728.0, 
	268435456.0, 536870912.0, 1073741824.0, 2147483648.0, 4294967296.0, 8589934592.0, 
	17179869184.0, 34359738368.0, 68719476736.0, 137438953472.0, 274877906944.0, 
	549755813888.0, 1099511627776.0, 2199023255552.0, 4398046511104.0, 8796093022208.0, 
	17592186044416.0, 35184372088832.0, 70368744177664.0, 140737488355328.0, 
	281474976710656.0, 562949953421312.0, 1125899906842624.0, 2251799813685248.0
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Bias of the following array.
const int gcBiasOrder2Pow = 52;

//! Number of digits on the left of decimal point for powers of 2.
const int gcOrder2Pow[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// exponent = [-52, -1]
	
	1,  1,  1, 1, 	// exponent = [0 , 3]
	2,  2,  2,		// exponent = [4 , 6]
	3,  3,  3,		// exponent = [7 , 9]
	4,  4,  4, 4,	// exponent = [10, 13]
	5,  5,  5, 		// exponent = [14, 16]
	6,  6,  6, 		// exponent = [17, 19]
	7,  7,  7, 7,	// exponent = [20, 23]
	8,  8,  8,		// exponent = [24, 26]
	9,  9,  9,		// exponent = [27, 29]
	10, 10, 10		// exponent = [30, 32]
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Bias of the following array, gives an index in the following array 
//! corresponding to 10^0 = 1.
const int gc10PowBias = 40;

//! Powers of 10 from 1e-40 to 1e+40.
const double gc10Pow[] = 
{
	1e-40, 1e-39, 1e-38, 1e-37, 1e-36, 1e-35, 1e-34, 1e-33, 1e-32, 1e-31,
	1e-30, 1e-29, 1e-28, 1e-27, 1e-26, 1e-25, 1e-24, 1e-23, 1e-22, 1e-21,
	1e-20, 1e-19, 1e-18, 1e-17, 1e-16, 1e-15, 1e-14, 1e-13, 1e-12, 1e-11,
	1e-10, 1e-09, 1e-08, 1e-07, 1e-06, 1e-05, 1e-04, 1e-03, 1e-02, 1e-01,
	1.0,
	1e+01, 1e+02, 1e+03, 1e+04, 1e+05, 1e+06, 1e+07, 1e+08, 1e+09, 1e+10,
	1e+11, 1e+12, 1e+13, 1e+14, 1e+15, 1e+16, 1e+17, 1e+18, 1e+19, 1e+20,
	1e+21, 1e+22, 1e+23, 1e+24, 1e+25, 1e+26, 1e+27, 1e+28, 1e+29, 1e+30,
	1e+31, 1e+32, 1e+33, 1e+34, 1e+35, 1e+36, 1e+37, 1e+38, 1e+39, 1e+40
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.

#endif // _SMATHLIB_CONSTANTS_H_
