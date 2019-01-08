
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute square of the euclidean distance between two points in given dimension.
//! \param TND A class representing N-Dimensional point.
//! \param p1 [in] First Point.
//! \param p2 [in] Second Point.
//! \return Square of euclidean distance between two ND-points.
template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glPointsDistance2(const TND& p1, const TND& p2, unsigned int dim)
{
	typedef PointAccessor<TND>              PA;
	typedef SUtils::IteratorTraits<TND>::value_type CT;
	
	CT _distance = 0;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		CT x1 = PA::get(p1, i);
		CT x2 = PA::get(p2, i);
		_distance += (x2-x1)*(x2-x1);
	}
	return _distance;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute euclidean distance between two points in given dimension.
//! \param TND A class representing N-Dimensional point.
//! \param point1 [in] First Point.
//! \param point2 [in] Second Point.
//! \return Euclidean distance between two ND-points.
template<typename TND>
double glPointsDistance(const TND& p1, const TND& p2, unsigned int dim)
{
	return sqrt(glPointsDistance2<TND>(p1, p2, dim));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute smaller angle between two 3D vectors.
//! Compute smaller angle between two 3D vectors. It throws an exception if
//! computed value of cos(angle) is not within [-1, +1].
//! \param vect1 [in] First vector.
//! \param vect2 [in] Second vector.
//! \param normalized If true then vectors are normalized else they are not.
//! \return Smaller angle in radians between two vectors.
template<typename TND>
double glComputeSmallerAngle(const TND& v1, const TND& v2, unsigned int dim, AngleType type, bool normalized)
{
	double _mag1   = normalized ? 1.0 : glVectorMagnitude<TND>(v1, dim);
	double _mag2   = normalized ? 1.0 : glVectorMagnitude<TND>(v2, dim);
	double _dotP   = glDotProduct<TND>(v1, v2, dim);
	double _cosAng = (_dotP) / (_mag1*_mag2);
	
	if(_cosAng>1+1e-8 || _cosAng<-1-1e-8)
	{
		std::ostringstream stream;
		stream << "ComputeSmallerAngle3D: Invalid argument in acos ";
		stream << _cosAng;
		throw SUtils::Exceptions::InvalidArgumentException(stream.str().c_str());
	}
	
	if(_cosAng >  1) _cosAng = +1;
	if(_cosAng < -1) _cosAng = -1;
	double _angle = acos(_cosAng);
	return type==eDegree ? glRadianToDegree(_angle) : _angle;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute signed area of a 2D triangle.
//! \param T2D A class representing 2D vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param v1Coords [in] Coordinates of the first vertex.
//! \param v2Coords [in] Coordinates of the second vertex.
//! \param v3Coords [in] Coordinates of the third vertex.
//! \return Area of the triangle given by v1Coords, v2Coords, and v3Coords.
template<typename T2D>
double glTriangleArea2D(const T2D& v1, const T2D& v2, const T2D& v3)
{
	// Area of a 2D triangle is give by : 
	//        1   | p10 p11 1 |
	// area = - * | p20 p21 1 |
	//        2   | p30 p31 1 |
	double v1x = PointAccessor<T2D>::get(v1, 0);
	double v1y = PointAccessor<T2D>::get(v1, 1);
	double v2x = PointAccessor<T2D>::get(v2, 0);
	double v2y = PointAccessor<T2D>::get(v2, 1);
	double v3x = PointAccessor<T2D>::get(v3, 0);
	double v3y = PointAccessor<T2D>::get(v3, 1);
	
	double _area = 0.0;
	_area += v1x*v2y - v1x*v3y;
	_area += v1y*v3x - v1y*v2x;
	_area += v2x*v3y - v3x*v2y;
	return _area/2.0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute area of a 3D triangle.
//! Compute area of a 3D triangle. For a single triangle in 3D signed area
//! cannot be computed since a 3D is not oriented.
//! \param T3D A class representing 3D vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param v1Coords [in] Coordinates of the first vertex.
//! \param v2Coords [in] Coordinates of the second vertex.
//! \param v3Coords [in] Coordinates of the third vertex.
//! \return Area of the triangle given by v1Coords, v2Coords, and v3Coords.
template<typename T3D>
double glTriangleArea3D(const T3D& v1, const T3D& v2, const T3D& v3)
{
	// In 3D area of a parallelogram formed by two vectors v1 and v2
	// is given by : area = || CrossProducr3D(v1, v2) ||.
	// So for a triangle in 3D its area can be defined as,
	// area = 1/2 * || CrossProducr3D(p2-p1, p3-p1) ||.
	return 0.5 * glVectorMagnitude<T3D>(glCrossProduct3D<T3D>(v2-v1, v3-v1), 3);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute normal of a 3D triangle.
//! \param T3D A class representing 3D vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param v1Coords [in] Coordinates of the first vertex.
//! \param v2Coords [in] Coordinates of the second vertex.
//! \param v3Coords [in] Coordinates of the third vertex.
//! \param normalize If true the normalize the normal.
//! \return Normal of the triangle given by v1Coords, v2Coords, and v3Coords.
template<typename T3D>
T3D glTriangleNormal3D(const T3D& v1, const T3D& v2, const T3D& v3, bool normalize)
{
	T3D normal = glCrossProduct3D<T3D>(v2-v1, v3-v1);
	if(normalize)
	{
		glVectorNormalize<T3D>(&normal, 3);
	}
	return normal;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute area of an arbitrary 2D polygon.
//! \param T2D A class representing 2D vector.
//! \param begin [in] A random-access iterator pointing to the first point 
// of the polygon. 
//! \param end [in] A random-access iterator pointing to the last point 
// of the polygon.
//! \return Area of the polygon defined by all the points between begin and end.
template<typename TIterator>
double glPolygonArea2D(const TIterator& begin, const TIterator& end)
{
	// Area of a 2D polygon can be computed by adding areas of all the 
	// triangles formed by an arbitrary point and each edge of the polygon. 
	// For simplicity we choose that arbitrary point to be (0,0).
	// Area of a 2D triangle in that case becomes : 
	//        1   |  0         0    1 |           
	// area = - * | x_{i}    y_{i}  1 | => 
	//        2   | y_{i+1} y_{i+1} 1 |           
	// 2*area = summation( x_{i}*y_{i+1} - x_{i+1}*y_{i} )
	// which can be simplified to
	// 2*area = summation [x_{i} * (y_{i+1} - y_{i})].
	
	double area = 0.0;
	
	TIterator k = begin;          // k points to first point.
	TIterator i = begin;	++i;  // i points to second point.
	TIterator j = i;		++j;  // j points to third point.
	
	if(i==end || j==end || k==end)
	{
		return 0.0;
	}
	
	typedef PointAccessor<TIterator::value_type> PA;
	bool done = false;
	while(!done)
	{
		area += PA::get(*i,0) * (PA::get(*j,1) - PA::get(*k,1));
		
		if(i == begin)
		{
			done = true;
			continue;
		}
		
		i++, j++, k++;
		
		if(i == end)	i = begin;
		if(j == end)	j = begin;
	}
	
	return area / 2.0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute Plucker coordinates for a directed line segment.
//! \param T3D A class representing 3D vector.
//! \param p1 [in] First end-point of the line segment.
//! \param p2 [in] Second end-point of the line segment.
//! \param plucker [out] Computed Plucker coordinates of the line segment between 
//! point1 and point2. It is assumed that plucker is not NULL and points to an 
//! array of size at least 6.
//! \param normalizeCoords [in] If true then Plucker coordinates are normalized 
// such that maximum coordinate has a value of 1.0.
template<typename T3D>
void glPluckerCoordinates3D(const T3D& p1, const T3D& p2, double* plucker, bool normalizeCoords)
{
	// Plucker's coordinates map a directed line segment to
	// a point in 6D space.
	// Plucker's coordinates are given by 2x2 determinants of
	// following matrices :  
	// px    py    pz    1 
	// qx    qy    qz    1
	// 
	// L[0] =  px*qy - qx*py
	// L[1] =  px*qz - qx*pz
	// L[2] =  px    - qx
	// L[3] =  py*qz - qy*pz
	// L[4] =  pz    - qz
	// L[5] =     qy -    py
	
	double px = PointAccessor<T3D>::get(p1, 0);
	double py = PointAccessor<T3D>::get(p1, 1);
	double pz = PointAccessor<T3D>::get(p1, 2);
	double qx = PointAccessor<T3D>::get(p2, 0);
	double qy = PointAccessor<T3D>::get(p2, 1);
	double qz = PointAccessor<T3D>::get(p2, 2);
	plucker[0] = px*qy - qx*py;
	plucker[1] = px*qz - qx*pz;
	plucker[2] = px    - qx   ;
	plucker[3] = py*qz - qy*pz;
	plucker[4] = pz    - qz   ;
	plucker[5] =    qy -    py;
	
	// Normalize plucker coordinates.
	if(normalizeCoords == true)
	{
		// This is done to avoid comparing huge 
		// number in the side operator.
		Int32 maxIndex = -1;
		double maxVal = 0.0;
		for(Int32 i=0 ; i<6 ; ++i)
		{
			if(fabs(maxVal) < fabs(plucker[i]))
			{
				maxIndex = i;
				maxVal   = plucker[i];
			}
		}
		
		if(maxIndex != -1)
		{
			for(Int32 i=0 ; i<6 ; ++i)
			{
				if(i != maxIndex)
				{
					plucker[i] = plucker[i] / fabs(maxVal);
				}
			}
			
			plucker[maxIndex] = plucker[maxIndex]/fabs(maxVal);
		}
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
