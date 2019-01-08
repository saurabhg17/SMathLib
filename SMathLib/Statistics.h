
#ifndef _SMATHLIB_STATISTICS_H_
#define _SMATHLIB_STATISTICS_H_

#include "SMathLib/Config.h"
#include "SMathLib/Types.h"
#include "SMathLib/FPMaths.h"
#include <cmath>
#include <limits>
#include <iterator>
#include <vector>
#include <algorithm>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! The Statistics structure stores descriptive statistics.
template<typename T>
struct Statistics
{
	Statistics()
	{
		mMin      = T();
		mMax      = T();
		mMean     = 0;
		mVariance = 0;
		mStdDev   = 0;
	}
	
	T      mMin;
	T      mMax;
	double mMean;
	double mVariance;
	double mStdDev;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Functions to compute descriptive statistics.
template<typename Iterator>
Statistics<typename std::iterator_traits<Iterator>::value_type> glComputeStatistics(const Iterator& begin, const Iterator& end, BiasTypes bias);

template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type glMin(const Iterator& begin, const Iterator& end);

template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type glMax(const Iterator& begin, const Iterator& end);

template<typename Iterator>
double glMean(const Iterator& begin, const Iterator& end);

template<typename Iterator>
double glVariance(const Iterator& begin, const Iterator& end, BiasTypes bias=eUnBiased);

template<typename Iterator>
double glVariance(const Iterator& begin, const Iterator& end, double mean, BiasTypes bias=eUnBiased);

template<typename Iterator>
double glStdDev(const Iterator& begin, const Iterator& end, BiasTypes bias=eUnBiased);
inline double glStdDev(double var);

// values must be sorted.
// Return the value of pth-percentile.
inline double glPercentile(const std::vector<double>& values, int p);

// Compute the pth-percentiles for values.
inline std::vector<double> glPercentiles(std::vector<double>& values, const std::vector<int>& p);
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

#include "SMathLib/Impl/Statistics.hpp"

};	// End namespace SMathLib.

#endif // _SMATHLIB_STATISTICS_H_
