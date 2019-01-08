
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Default constructor.
//! Initializes each element of vector with 0.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack()
{
	for(unsigned int i=0 ; i<DIM ; ++i)
	{
		mVectorData[i] = 0;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Initialize first coordinate of the vector.
//! \param x1 First coordinate of the vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const ValueType& x1)
{
	SUTILS_STATIC_ASSERT(DIM==1, VectorOnStack_Too_Many_Arguments);
	mVectorData[0] = x1;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Initialize first and second coordinates of vector.
//! \param x1 First coordinate of the vector.
//! \param x2 Second coordinate of the vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const ValueType& x1, 
										  const ValueType& x2)
{
	SUTILS_STATIC_ASSERT(DIM==2, VectorOnStack_Too_Many_Arguments);
	mVectorData[0] = x1;
	mVectorData[1] = x2;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Initialize first three coordinates of vector.
//! \param x1 First coordinate of the vector.
//! \param x2 Second coordinate of the vector.
//! \param x3 Third coordinate of the vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const ValueType& x1, 
										  const ValueType& x2, 
										  const ValueType& x3)
{
	SUTILS_STATIC_ASSERT(DIM==3, VectorOnStack_Too_Many_Arguments);
	mVectorData[0] = x1;
	mVectorData[1] = x2;
	mVectorData[2] = x3;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Initialize first four coordinates of vector.
//! \param x1 First coordinate of the vector.
//! \param x2 Second coordinate of the vector.
//! \param x3 Third coordinate of the vector.
//! \param x4 Fourth coordinate of the vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const ValueType& x1, const ValueType& x2, 
										  const ValueType& x3, const ValueType& x4)
{
	SUTILS_STATIC_ASSERT(DIM==4, VectorOnStack_Too_Many_Arguments);
	mVectorData[0] = x1;
	mVectorData[1] = x2;
	mVectorData[2] = x3;
	mVectorData[3] = x4;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Initialize vector with a given array of values.
//! \param data The array to use for initializing the vector.
//! The size of the array must be at least 2.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const ValueType* const data)
{
	if(data != 0)
	{
		memcpy(mVectorData, data, VALUE_TYPE_SIZE * DIM);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Copy constructor.
//! \param B The vector from which to create a copy.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>::VectorOnStack(const VectorOnStack<ET, DIM, CP> &B)
{
	memcpy(mVectorData, B.mVectorData, VALUE_TYPE_SIZE * DIM);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ // 
//! Assignment operator.
//! \param B The vector from which to create a copy.
//! \return The reference to this vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>& 
VectorOnStack<ET, DIM, CP>::operator = (const VectorOnStack<ET, DIM, CP>& B)
{
	// Self-assignment.
	if(&B == this)
	{
		return *this;
	}
	else
	{
		memcpy(mVectorData, B.mVectorData, VALUE_TYPE_SIZE* DIM);
		return *this;
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename ET, unsigned int DIM, typename CP>
ET& VectorOnStack<ET, DIM, CP>::operator [] (unsigned int index)
{
	CP::Check(index, 0, DIM-1, "Vector: Index out of bounds.");
	return mVectorData[index];
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
template<typename ET, unsigned int DIM, typename CP>
const ET& VectorOnStack<ET, DIM, CP>::operator [] (unsigned int index) const
{
	CP::Check(index, 0, DIM-1, "Vector: Index out of bounds.");
	return mVectorData[index];
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if two vectors are equal, v1 == v2.
//! \param v2 Vector on the R.H.S. of the == sign.
//! \return True if two vectors are equal, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator == (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] != v2.mVectorData[i])
		{
			return false;
		}
	}
	
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if two vectors are unequal, v1 != v2.
//! \param v2 Vector on the R.H.S. of the != sign.
//! \return True if two vectors are unequal, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator != (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] != v2.mVectorData[i])
		{
			return true;
		}
	}
	
	return false;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if first vector is less then second vector, v1 < v2.
//! \param v2 Vector on the R.H.S. of the < sign.
//! \return True if first vector is less then second vector, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator < (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] >= v2.mVectorData[i])
		{
			return false;
		}
	}
	
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if first vector is greater then second vector, v1 > v2.
//! \param v2 Vector on the R.H.S. of the > sign.
//! \return True if first vector is greater then second vector, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator > (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] <= v2.mVectorData[i])
		{
			return false;
		}
	}
	
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Checking if first vector is less then or equal to second vector, v1 <= v2.
//! \param v2 Vector on the R.H.S. of the <= sign.
//! \return True if first vector is less then or equal to second vector, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator <= (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] > v2.mVectorData[i])
		{
			return false;
		}
	}
	
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Check if first vector is greater then or equal to second vector, v1 >= v2.
//! \param v2 Vector on the R.H.S. of the >= sign.
//! \return True if first vector is greater then or equal to second vector, false otherwise.
template<typename ET, unsigned int DIM, typename CP>
bool VectorOnStack<ET, DIM, CP>::operator >= (const VectorOnStack<ET, DIM, CP>& v2) const
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		if(mVectorData[i] < v2.mVectorData[i])
		{
			return false;
		}
	}
	
	return true;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Add two vectors v1 and v2, v3 = v1 + v2.
//! \param v2 Vector on the R.H.S. of the + sign.
//! \return A vector v3 = v1 + v2.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>
VectorOnStack<ET, DIM, CP>::operator + (const VectorOnStack<ET, DIM, CP>& B) const
{
	VectorOnStack<ET, DIM, CP> C;
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		C.mVectorData[i] = mVectorData[i] + B.mVectorData[i];
	}
	return C;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Subtract a vector v2 from v1, v3 = v1 - v2.
//! \param v2 Vector on the R.H.S. of the - sign.
//! \return A vector v3 = v1 - v2.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>
VectorOnStack<ET, DIM, CP>::operator - (const VectorOnStack<ET, DIM, CP>& B) const
{
	VectorOnStack<ET, DIM, CP> C;
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		C.mVectorData[i] = mVectorData[i] - B.mVectorData[i];
	}
	return C;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Add a vector v2 to itself, v1 += v2.
//! \param v2 Vector on the R.H.S. of the += sign.
//! \return A vector v1 = v1 + v2.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>&
VectorOnStack<ET, DIM, CP>::operator += (const VectorOnStack<ET, DIM, CP>& B)
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		mVectorData[i] = mVectorData[i] + B.mVectorData[i];
	}
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Subtract a vector v2 from v1, v1 -= v2.
//! \param v2 Vector on the R.H.S. of the -= sign.
//! \return A vector v1 = v1 - v2.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>& 
VectorOnStack<ET, DIM, CP>::operator -= (const VectorOnStack<ET, DIM, CP>& B)
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		mVectorData[i] = mVectorData[i] - B.mVectorData[i];
	}
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Negate a vector, v1 = -v1.
//! \param v1 Vector on the R.H.S. of the - sign.
//! \return Result of negating a vector.
template<typename ET, unsigned int DIM, typename CP>
VectorOnStack<ET, DIM, CP>
VectorOnStack<ET, DIM, CP>::operator - () const
{
	VectorOnStack<ET, DIM, CP> C;
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		C.mVectorData[i] = -mVectorData[i];
	}
	return C;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Multiply a vector with a scalar, v2 = v1 * s.
//! \param ST Type of the scalar.
//! \param s The scalar with which to multiply the vector.
//! \return Result of multiplying a vector with scalar.
template<typename ET, unsigned int DIM, typename CP>
template<typename ST>
VectorOnStack<ET, DIM, CP> VectorOnStack<ET, DIM, CP>::operator * (const ST& s) const
{
	VectorOnStack<ET, DIM, CP> C;
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		C.mVectorData[i] = mVectorData[i] * s;
	}
	return C;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Divide a vector with a scalar, v2 = v1 / s.
//! \param ST Type of the scalar.
//! \param s The scalar with which to divide the vector.
//! \return Result of dividing a vector with scalar.
template<typename ET, unsigned int DIM, typename CP>
template<typename ST>
VectorOnStack<ET, DIM, CP> VectorOnStack<ET, DIM, CP>::operator / (const ST& s) const
{
	VectorOnStack<ET, DIM, CP> C;
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		C.mVectorData[i] = mVectorData[i] / s;
	}
	return C;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Multiply a vector with a scalar, v1 *= s.
//! \param ST Type of the scalar.
//! \param s The scalar with which to multiply the vector.
//! \return Result of multiplying a vector with scalar.
template<typename ET, unsigned int DIM, typename CP>
template<typename ST>
VectorOnStack<ET, DIM, CP>& VectorOnStack<ET, DIM, CP>::operator *= (const ST& s)
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		mVectorData[i] *= s;
	}
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Divide a vector with a scalar, v1 /= s.
//! \param ST Type of the scalar.
//! \param s The scalar with which to divide the vector..
//! \return Result of dividing a vector with scalar.
template<typename ET, unsigned int DIM, typename CP>
template<typename ST>
VectorOnStack<ET, DIM, CP>& VectorOnStack<ET, DIM, CP>::operator /= (const ST& s)
{
	for(unsigned int i=0 ; i<DIM ; i++)
	{
		mVectorData[i] /= s;
	}
	return *this;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Multiply a scalar with a vector, v1 = s * v2.
//! \param ST Type of input scalar.
//! \param s The scalar with which to multiply the vector.
//! \param B The vector with which to multiply the scalar.
//! \return Result of multiplying scalar with vector.
template<typename ST, typename ET1, unsigned int DIM1, typename CP1> 
VectorOnStack<ET1, DIM1, CP1> operator * (const ST& s, const VectorOnStack<ET1, DIM1, CP1>& v2)
{
	VectorOnStack<ET1, DIM1, CP1> v1;
	for(unsigned int i=0 ; i<DIM1 ; i++)
	{
		v1.mVectorData[i] = s * v2.mVectorData[i];
	}
	return v1;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Stream vector to a output character stream, out << v.
//! \param out Output character stream.
//! \param B Vector which should be streamed to the stream.
//! \return Reference to output stream so that streaming can be chained.
template<typename ET1, unsigned int DIM1, typename CP1> 
std::ostream& operator << (std::ostream& out, const VectorOnStack<ET1, DIM1, CP1>& B)
{
	for(unsigned int i=0 ; i<DIM1 ; ++i)
	{
		out << B.mVectorData[i] << " ";
	}
	return out;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Stream vector from a input character stream, in >> v.
//! \param in Input stream.
//! \param B  Reference to vector which will be read from the stream.
//! \return Reference to input stream so that streaming can be chained.
template<typename ET1, unsigned int DIM1, typename CP1>
std::istream& operator >> (std::istream& in, VectorOnStack<ET1, DIM1, CP1>& B)
{
	for(unsigned int i=0 ; i<DIM1 ; ++i)
	{
		in >> B.mVectorData[i];
	}
	return in;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
