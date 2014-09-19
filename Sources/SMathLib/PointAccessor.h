
#ifndef _SMATHLIB_POINTACCESSORTYPE_H_
#define _SMATHLIB_POINTACCESSORTYPE_H_

#include "SUtils/IteratorTraits.h"
#include "SMathLib/Constants.h"
#include "SMathLib/Types.h"

namespace SMathLib {
;

//! The structure for accessing coordinates using indexing operator.
template<typename PointType> 
struct PointAccessor
{
	typedef typename SUtils::IteratorTraits<PointType>::value_type CoordType;
	
	static CoordType get(const PointType& p, int index)
	{
		return p[index];
	}
	static void set(PointType& p, int index, CoordType value)
	{
		p[index] = value;
	}
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_POINTACCESSORTYPE_H_
