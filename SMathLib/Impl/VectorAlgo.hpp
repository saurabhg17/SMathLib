
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute square of the magnitude of a vector of any dimension.
//! \param TND A class representing N-Dimensional vector.
//! \param v Input vector.
//! \param dim Dimension of the vector.
//! \return Square of the magnitude of the vector.
template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glVectorMagnitude2(const TND& v, unsigned int dim)
{
	typedef PointAccessor<TND>              PA;
	typedef SUtils::IteratorTraits<TND>::value_type CT;
	
	CT _magnitude = 0;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		_magnitude += (PA::get(v,i) * PA::get(v,i));
	}
	return _magnitude;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute magnitude of a vector of any dimension.
//! \param TND A class representing N-Dimensional vector.
//! \param v Input vector.
//! \param dim Dimension of the vector.
//! \return Magnitude of the vector.
template<typename TND>
double glVectorMagnitude(const TND& v, unsigned int dim)
{
	return sqrt(glVectorMagnitude2<TND>(v, dim));
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Normalize a vector.
//! \param TND A class representing N-Dimensional vector.
//! \param v [in] Input vector.
//! \param dim [in] Dimension of the vector.
template<typename TND>
void glVectorNormalize(TND* v, unsigned int dim)
{
	typedef PointAccessor<TND>              PA;
	typedef SUtils::IteratorTraits<TND>::value_type CT;
	
	CT _magnitude = glVectorMagnitude<TND>(*v, dim);
	if(_magnitude != 0)
	{
		for(unsigned int i=0 ; i<dim ; i++)
		{
			PA::set(*v, i, PA::get(*v,i)/_magnitude);
		}
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute dot product of 2 vectors in any dimension.
//! \param TND A class representing N-Dimensional vector. There are two 
//! requirements on the class. First, it must support indexing operator []. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE.
//! \param vect1 [in] First vector.
//! \param vect2 [in] Second vector.
//! \return Dot product of vect1 with vect2.
template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glDotProduct(const TND& v1, const TND& v2, unsigned int dim)
{
	typedef PointAccessor<TND>              PA;
	typedef SUtils::IteratorTraits<TND>::value_type CT;
	
	CT _dotProduct = 0;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		_dotProduct += (PA::get(v1,i) * PA::get(v2,i));
	}
	return _dotProduct;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compute cross-product of 2 3D vectors.
//! \param T3D A class representing 3D vector. There are two 
//! requirements on the class. First, it must support indexing operator [ ]. 
//! Second, PointTraits must be defined for the class. ADD CROSS REFERENCE LATER.
//! \param vect1 [in] First vector.
//! \param vect2 [in] Second vector.
//! \return Cross product of vect1 with vect2.
template<typename T3D>
T3D glCrossProduct3D(const T3D& v1, const T3D& v2)
{
	// cross-product is given by.
	//                |  i   j   k  |
	// xi + yj + zk = | p10 p11 p12 |
	//                | p20 p21 p22 |
	
	typedef PointAccessor<T3D>              PA;
	typedef SUtils::IteratorTraits<T3D>::value_type CT;
	
	CT x = PA::get(v1,1)*PA::get(v2,2) - PA::get(v2,1)*PA::get(v1,2);
	CT y = PA::get(v2,0)*PA::get(v1,2) - PA::get(v1,0)*PA::get(v2,2);
	CT z = PA::get(v1,0)*PA::get(v2,1) - PA::get(v2,0)*PA::get(v1,1);
	
	T3D cp;
	PA::set(cp, 0, x);
	PA::set(cp, 1, y);
	PA::set(cp, 2, z);
	return cp;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compare two vectors using robust compareDouble function.
template<typename TND>
bool glVectorEqual(const TND& v1, const TND& v2, unsigned int dim, double relErr, double absErr)
{
	typedef PointAccessor<TND> PA;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		if(!glCompareDouble(PA::get(v1,i), PA::get(v2,i), relErr, absErr))
		{
			return false;
		}
	}
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Compare two vectors using robust compareDouble function.
template<typename TND>
bool glVectorNotEqual(const TND& v1, const TND& v2, unsigned int dim, double relErr, double absErr)
{
	typedef PointAccessor<TND> PA;
	for(unsigned int i=0 ; i<dim ; ++i)
	{
		if(!glCompareDouble(PA::get(v1,i), PA::get(v2,i), relErr, absErr))
		{
			return true;
		}
	}
	return false;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
