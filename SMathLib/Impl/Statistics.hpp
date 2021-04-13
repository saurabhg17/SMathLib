// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
Statistics<typename std::iterator_traits<Iterator>::value_type>
glComputeStatistics(const Iterator& begin, const Iterator& end, BiasTypes bias)
{
	Statistics<typename std::iterator_traits<Iterator>::value_type> _statistics;
	_statistics.mMin  = std::numeric_limits<double>::max();
	_statistics.mMax  = std::numeric_limits<double>::lowest();
	
	_statistics.mMean = 0;
	int    _count = 0;
	double _error = 0;
	
	for(Iterator _iter=begin ; _iter!=end ; ++_iter, ++_count)
	{
		if(_statistics.mMin > *_iter)
		{
			_statistics.mMin = *_iter;
		}
		if(_statistics.mMax < *_iter)
		{
			_statistics.mMax = *_iter;
		}
		
		glKahanSum(_statistics.mMean, *_iter, _error); // This is more accurate the direct summing.
	}
	_statistics.mMean /= _count;
	
	_statistics.mVariance = glVariance(begin, end, _statistics.mMean, bias);
	_statistics.mStdDev   = glStdDev(_statistics.mVariance);
	
	return _statistics;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type glMin(const Iterator& begin, const Iterator& end)
{
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	value_type _min  = std::numeric_limits<value_type>::max();
	for(Iterator _iter=begin ; _iter!=end ; ++_iter)
	{
		if(_min > *_iter)
		{
			_min = *_iter;
		}
	}
	return _min;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type glMax(const Iterator& begin, const Iterator& end)
{
	typedef typename std::iterator_traits<Iterator>::value_type value_type;
	value_type _max  = std::numeric_limits<value_type>::lowest();
	for(Iterator _iter=begin ; _iter!=end ; ++_iter)
	{
		if(_max < *_iter)
		{
			_max = *_iter;
		}
	}
	return _max;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
double glMean(const Iterator& begin, const Iterator& end)
{
	double _mean  = 0.0;
	int    _count = 0;
	double _error = 0.0;
	for(Iterator _iter=begin ; _iter!=end ; ++_iter, ++_count)
	{
		glKahanSum(_mean, *_iter, _error); // This is more accurate the direct summing.
	}
	return _mean/_count;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
double glVariance(const Iterator& begin, const Iterator& end, BiasTypes bias)
{
	return glVariance(begin, end, glMean(begin, end), bias);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename Iterator>
double glVariance(const Iterator& begin, const Iterator& end, double mean, BiasTypes bias)
{
	double _var   = 0.0;
	int    _count = 0;
	for(Iterator _iter=begin ; _iter!=end ; ++_iter, ++_count)
	{
		_var += (*_iter-mean)*(*_iter-mean);
	}
	return bias==eUnBiased ? _var/(_count-1) : _var/_count;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// A large standard deviation indicates that the data points are far from the 
// mean and a small standard deviation indicates that they are clustered 
// closely around the mean.
template<typename Iterator>
double glStdDev(const Iterator& begin, const Iterator& end, BiasTypes bias)
{
	return sqrt(glVariance(begin, end, bias));
}
double glStdDev(double var)
{
	return sqrt(var);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// values must be sorted.
// Return the value if pth-percentile.
double glPercentile(const std::vector<double>& values, int p)
{
	const size_t N = values.size();
	if(p == 1)
	{
		return values[0];
	}
	else if(p == 100)
	{
		return values[N-1];
	}
	else
	{
		double _rank  = (N + 1) * p/100.0; // Use NIIST formula to compute rank.
		int    _rankI = int(_rank);        // Integer part of the rank.
		double _rankF = _rank - _rankI;    // Fractional part of the rank.
		double v1     = values[_rankI-1];  // value at _rankI; -1 is use because arrays are 0 based.
		double v2     = values[_rankI];    // value next to _rankI.
		return v1 + _rankF*(v2-v1);        // Interpolate v1 and v2.
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
std::vector<double> glPercentiles(std::vector<double>& values, const std::vector<int>& p)
{
	// First sort the values.
	std::sort(values.begin(), values.end());
	
	// For all elements in p, store value of p-th percentile in _percentiles.
	std::vector<double> _percentiles;
	for(size_t i=0 ; i<p.size() ; ++i)
	{
		_percentiles.push_back(glPercentile(values, p[i]));
	}
	return _percentiles;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //