
#ifndef _SMATHLIB_POINTCONVERTER_H_
#define _SMATHLIB_POINTCONVERTER_H_

#include "SUtils/IteratorTraits.h"
#include "SMathLib/Types.h"
#include "SMathLib/PointAccessor.h"

namespace SMathLib {
;

// fill is used to fill the coordinates when input type have less dimensions 
// then output type.
template<typename InputType, typename OutputType>
void glConvertPoint(const InputType& in, unsigned int inDim, OutputType& out, unsigned int outDim, double fill=0)
{
	// Output vector is of smaller dimension then input vector.
	// So truncate the input vector.
	if(inDim > outDim)
	{
		for(unsigned int i=0 ; i<outDim ; ++i)
		{
			IteratorTraits<InputType>::value_type x = PointAccessor<InputType>::get(in, i);
			PointAccessor<OutputType>::set(out, i, x);
		}
	}
	else
	{
		for(unsigned int i=0 ; i<inDim ; ++i)
		{
			IteratorTraits<InputType>::value_type x = PointAccessor<InputType>::get(in, i);
			PointAccessor<OutputType>::set(out, i, x);
		}
		for(unsigned int i=inDim ; i<outDim ; ++i)
		{
			PointAccessor<OutputType>::set(out, i, fill);
		}
	}
}

};	// End namespace SMathLib.

#endif // _SMATHLIB_POINTCONVERTER_H_
