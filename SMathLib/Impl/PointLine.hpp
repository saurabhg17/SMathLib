
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute distance of a point from line.
//! Compute distance of a point from line. This function is not very efficient
//! for 2D.
//! \param TND A class representing N-Dimensional vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param point [in] Point whose orientation is to be found. 
//! \param ln1 [in] First point on the line.
//! \param ln2 [in] Second point on the line.
//! \return Return distance of the point from the line defined by ln1-ln2.
template<typename TND>
double glDistancePointLine(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim)
{
	TND w = point - ln1;
	TND v = ln2 - ln1;
	return glVectorMagnitude<TND>(w - v * (glDotProduct<TND>(w, v, dim)/glDotProduct<TND>(v, v, dim)), dim);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute square of the distance of a point from line. 
//! Compute square of the distance of a point from line. This function is not 
//! very efficient for 2D.
//! \param TND A class representing N-Dimensional vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param point [in] Point whose orientation is to be found. 
//! \param ln1 [in] First point on the line.
//! \param ln2 [in] Second point on the line.
//! \return Return square of the distance of the point from the line defined 
//! by ln1-ln2.
template<typename TND>
double glDistancePointLine2(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim)
{
	TND w = point - ln1;
	TND v = ln2 - ln1;
	return glVectorMagnitude2<TND>(w - v * (glDotProduct<TND>(w, v, dim)/glDotProduct<TND>(v, v, dim)), dim);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if a point lies on a line.
//! \param TND A class representing N-Dimensional vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param point [in] Point whose orientation is to be found. 
//! \param ln1 [in] First point on the line.
//! \param ln2 [in] Second point on the line.
//! \return Return true of point lies on the line defined by ln1-ln2.
//! \param maxRelErr [in] Maximum relative error to use for comparing.
//! \param maxAbsErr [in] Maximum absolute error to use for comparing.
template<typename TND>
bool glIsPointOnLine(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim, 
					 double maxRelErr, double maxAbsErr)
{
	TND w = point - ln1;
	TND v = ln2   - ln1;
	TND t = v * (glDotProduct<TND>(w, v, dim)/glDotProduct<TND>(v, v, dim));
	
	typedef PointAccessor<TND> PA;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		if(glCompareDouble(fabs(PA::get(w,i)), fabs(PA::get(t,i)), maxRelErr, maxAbsErr) == false)
		{
			return false;
		}
	}
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Compute closest distance of a point from a line segment.
template<typename T3D>
double glDistancePointLineSeg3D(const T3D& ls1, const T3D& ls2, const T3D& point,double* paramVal)
{
	T3D _direction = ls2 - ls1;
	double t = glDotProduct<T3D>(_direction, point - ls1, 3) / glVectorMagnitude2<T3D>(_direction, 3);
	
	if(paramVal)
	{
		*paramVal = t;
	}
	
	if(t <= 0.0)
	{
		return glPointsDistance<T3D>(point, ls1, 3);
	}
	else if(t >= 1.0)
	{
		return glPointsDistance<T3D>(point, ls2, 3);
	}
	else
	{
		return glPointsDistance<T3D>(point, ls1+_direction*t, 3);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Compute closest distance of a point from a ray.
template<typename T3D>
double glDistancePointRay3D(const T3D& ls1, const T3D& ls2, const T3D& point, double* paramVal)
{
	T3D _direction = ls2 - ls1;
	double t = glDotProduct<T3D>(_direction, point - ls1, 3) / glVectorMagnitude2<T3D>(_direction, 3);
	
	if(paramVal)
	{
		*paramVal = t;
	}
	
	if(t <= 0.0)
	{
		return glPointsDistance<T3D>(point, ls1, 3);
	}
	else
	{
		return glPointsDistance<T3D>(point, ls1+_direction*t, 3);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Compute closest distance of a point from a line segment.
template<typename TND>
double glDistancePointLineSeg(const TND& ls1, const TND& ls2, const TND& point, int dim, double* paramVal)
{
	TND _direction = ls2 - ls1;
	double t = glDotProduct<TND>(_direction, point - ls1, dim) / glVectorMagnitude2<TND>(_direction, dim);
	
	if(paramVal)
	{
		*paramVal = t;
	}
	
	if(t <= 0.0)
	{
		return glPointsDistance<TND>(point, ls1, dim);
	}
	else if(t >= 1.0)
	{
		return glPointsDistance<TND>(point, ls2, dim);
	}
	else
	{
		return glPointsDistance<TND>(point, ls1+_direction*t, dim);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
