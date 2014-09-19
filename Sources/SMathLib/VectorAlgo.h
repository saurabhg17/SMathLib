
#ifndef _SMATHLIB_ALGOVECTOR_H_
#define _SMATHLIB_ALGOVECTOR_H_

#include "SUtils/IteratorTraits.h"
#include "SMathLib/Types.h"
#include "SMathLib/CompareDouble.h"
#include "SMathLib/PointAccessor.h"
#include <cmath>

namespace SMathLib {
;

template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glVectorMagnitude2(const TND& v, unsigned int dim);

template<typename TND>
double glVectorMagnitude(const TND& v, unsigned int dim);

template<typename TND>
void glVectorNormalize(TND* v, unsigned int dim);

template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glDotProduct(const TND& v1, const TND& v2, unsigned int dim);

template<typename T3D>
T3D glCrossProduct3D(const T3D& v1, const T3D& v2);

template<typename TND>
bool glVectorEqual(const TND& v1, const TND& v2, unsigned int dim, double relErr, double absErr);

template<typename TND>
bool glVectorNotEqual(const TND& v1, const TND& v2, unsigned int dim, double relErr, double absErr);

// Include implementation.
#include "Impl/VectorAlgo.hpp"

};	// End namespace SMathLib.

#endif // _SMATHLIB_ALGOVECTOR_H_
