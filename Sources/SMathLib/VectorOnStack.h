
#ifndef _SMATHLIB_VECTORONSTACK_H_
#define _SMATHLIB_VECTORONSTACK_H_

#include "SUtils/NoBoundChecking.h"
#include "SUtils/StaticCheck.h"
//#include "SUtils/BinaryIO.h"
#include "SMathLib/Types.h"

namespace SMathLib {
;

//! Class for creating N-Dimensional Vector on a stack.
//! \param ET The type of the elements stored in the vector.
//! \param DIM The dimension of the vector.
//! \param CP Bound checking policy for element access.
template<typename ET, unsigned int DIM, typename CP = SUtils::NoBoundChecking>
class VectorOnStack
{
public:    // Typedefs.
	
	//! Define the type of elements stored in vector.
	typedef ET ValueType;
	typedef ET value_type;
	
	//! Define the type of this vector.
	typedef VectorOnStack<ET, DIM, CP> VectorType;
	
	//! Size of the ValueType in bytes.
	static const unsigned int VALUE_TYPE_SIZE = sizeof(ValueType);
	
public: // Constructors.
	
	VectorOnStack();
	VectorOnStack(const ValueType& x1);
	VectorOnStack(const ValueType& x1, const ValueType& x2);
	VectorOnStack(const ValueType& x1, const ValueType& x2, const ValueType& x3);
	VectorOnStack(const ValueType& x1, const ValueType& x2, const ValueType& x3, const ValueType& x4);
	VectorOnStack(const ValueType* const data);
	VectorOnStack(const VectorOnStack& B);
	VectorOnStack& operator = (const VectorOnStack& B);
	
public: // Indexing operators.
	
	ValueType& operator [] (unsigned int index);
	const ValueType& operator [] (unsigned int index) const;
	
public:	// Logical operators.
	
	bool operator == (const VectorType& v2) const;
	bool operator != (const VectorType& v2) const;
	bool operator <  (const VectorType& v2) const;
	bool operator >  (const VectorType& v2) const;
	bool operator <= (const VectorType& v2) const;
	bool operator >= (const VectorType& v2) const;
	
public:	// Vector-Vector arithmetic operators.
	
	VectorType  operator +  (const VectorType& v2) const;
	VectorType  operator -  (const VectorType& v2) const;
	VectorType& operator += (const VectorType& v2);
	VectorType& operator -= (const VectorType& v2);
	VectorType  operator -  () const;
	
public:	// Vector-Scalar arithmetic operators.
	
	template<typename ST> VectorType  operator *  (const ST& s) const;
	template<typename ST> VectorType  operator /  (const ST& s) const;
	template<typename ST> VectorType& operator *= (const ST& s);
	template<typename ST> VectorType& operator /= (const ST& s);
	
public: // Scalar-Vector arithmetic operations.
	
	template<typename ST, typename ET1, unsigned int DIM1, typename CP1> 
	friend VectorType operator * (const ST& s, const VectorType& B);
	
public: // IO functions.
	
	void Write(std::ostream& out) const;
	void Read(std::istream& in);
	
	template<typename ET1, unsigned int DIM1, typename CP1> 
	friend std::ostream& operator << (std::ostream& out, const VectorType& B);
	
	template<typename ET1, unsigned int DIM1, typename CP1> 
	friend std::istream& operator >> (std::istream& in, VectorType& B);
	
public: // Inline functions.
	
	//! Get the const pointer to the internal array.
	//! \return The const pointer to the internal array storing the vector.
	inline const ValueType* const ConstData() const {return mVectorData;}
	
	//! Get the pointer to the internal array.
	//! \return The pointer to the internal array storing the vector.
	inline ValueType* Data() {return mVectorData;}
	
	//! The function to access the dimension of the vector from the derived class.
	//! \return The dimension of the vector.
	inline unsigned int Dimension() const {return DIM;}
	
private: // Variables.
	
	//! Storage space for the vector.
	ValueType mVectorData[DIM];
};

// Include implementation.
#include "Impl/VectorOnStack.hpp"

// Define some commonly used type of vectors.
typedef VectorOnStack<unsigned int, 2> VectorOnStackI2;
typedef VectorOnStack<unsigned int, 3> VectorOnStackI3;
typedef VectorOnStack<unsigned int, 4> VectorOnStackI4;
typedef VectorOnStack<double, 2> VectorOnStackD2;
typedef VectorOnStack<double, 3> VectorOnStackD3;
typedef VectorOnStack<double, 4> VectorOnStackD4;

};	// End namespace SMathLib.

#endif // _SMATHLIB_VECTORONSTACK_H_
