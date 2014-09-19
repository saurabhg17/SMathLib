
#ifndef _SMATHLIB_GEOMETRYALGO_H_
#define _SMATHLIB_GEOMETRYALGO_H_

#include "SUtils/IteratorTraits.h"
#include "SUtils/Exceptions/InvalidArgumentException.h"
#include "SMathLib/PointAccessor.h"
#include "SMathLib/VectorAlgo.h"
#include "SMathLib/Types.h"
#include "SMathLib/Trigono.h"
#include <sstream>

namespace SMathLib {
;

template<typename TND>
typename SUtils::IteratorTraits<TND>::value_type glPointsDistance2(const TND& p1, const TND& p2, unsigned int dim);

template<typename TND>
double glPointsDistance(const TND& p1, const TND& p2, unsigned int dim);

template<typename TND>
double glComputeSmallerAngle(const TND& v1, const TND& v2, unsigned int dim, AngleType type, bool normalized);

template<typename T2D>
double glTriangleArea2D(const T2D& p1, const T2D& p2, const T2D& p3);

template<typename T3D>
double glTriangleArea3D(const T3D& p1, const T3D& p2, const T3D& p3);

template<typename T3D>
T3D glTriangleNormal3D(const T3D& p1, const T3D& p2, const T3D& p3, bool normalize);

template<typename TIterator>
double glPolygonArea2D(const TIterator& begin, const TIterator& end);

template<typename T3D>
void glPluckerCoordinates3D(const T3D& p1, const T3D& p2, double* plucker, bool normalizeCoords);

// Include implementation.
#include "Impl/GeometryAlgo.hpp"

};	// End namespace SMathLib.

#endif // _SMATHLIB_GEOMETRYALGO_H_