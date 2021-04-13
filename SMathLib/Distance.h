// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_DISTANCE_H_
#define _SMATHLIB_DISTANCE_H_

#include "SMathLib/Constants.h"
#include "SUtils/IteratorTraits.h"
#include <cmath>

namespace SMathLib {
;

//! Compute distance between two N-Dimensional points.
//! \param InputIterator Iterator for input arrays, should be model of 
//! random access iterator in the standard library.
//! \param x1 InputIterator at beginning of first point.
//! \param x2 InputIterator at one past last element of first point.
//! \param y1 InputIterator at beginning of second point.
//! \param y2 InputIterator at one past last element of second point.
//! \param metric Type of distance to compute between two points.
//! \param p Value of p when distance metric is DistanceMetric::LPNorm.
template<typename InputIterator>
double glDistance(InputIterator x1, InputIterator x2, 
				  InputIterator y1, InputIterator y2,
				  DistanceMetric metric, 
				  double p = 0.0)
{
	if( metric==eRectilinear || metric==eCityBlock || 
		metric==eManhattan   || metric==eL1Norm)
	{
		double _distance = 0.0;
		while(x1 != x2)
		{
			_distance += abs(*x1 - *y1);
			x1++;
			y1++;
		}
		return _distance;
	}
	
	else if(metric==eL2Norm || metric==eEuclidean)
	{
		double _distance = 0.0;
		while(x1!=x2)
		{
			_distance += ((*x1 - *y1) * (*x1 - *y1));
			x1++;
			y1++;
		}
		return sqrt(_distance);
	}
	
	else if(metric==eLPNorm)
	{
		double _distance = 0.0;
		while(x1!=x2)
		{
			_distance += pow((*x1 - *y1), p);
			x1++;
			y1++;
		}
		return pow(_distance, 1.0/p);
	}
	
	else if(metric==eInfinityNorm || metric==eMaximumNorm)
	{
		double _distance = std::numeric_limits<double>::max();
		while(x1!=x2)
		{
			if(_distance < abs(*x1 - *y1))
			{
				_distance = abs(*x1 - *y1);
			}
			x1++;
			y1++;
		}
		return _distance;
	}
	
	else if(metric == eHamming)
	{
		double _distance = 0.0;
		while(x1!=x2)
		{
			if(*x1 != *y1)
			{
				_distance++;
			}
			x1++;
			y1++;
		}
		return _distance;
	}
	
	else if(metric == eCosAngle)
	{
		double _distance = 0.0;
		double _mag1     = 0.0;
		double _mag2     = 0.0;
		
		while(x1!=x2)
		{
			_distance += (*x1 * *y1);
			_mag1     += (*x1 * *x1);
			_mag2     += (*y1 * *y1);
			x1++;
			y1++;
		}
		return _distance/(sqrt(_mag1)*sqrt(_mag2));
	}
	
	return std::numeric_limits<double>::quiet_NaN();
}

};	// End namespace SMathLib.

#endif // _SMATHLIB_DISTANCE_H_
