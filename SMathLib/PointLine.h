
#ifndef _SMATHLIB_POINTLINE_H_
#define _SMATHLIB_POINTLINE_H_

#include "SMathLib/CompareDouble.h"
#include "SMathLib/PointAccessor.h"
#include "SMathLib/VectorAlgo.h"

namespace SMathLib {
;

template<typename TND>
double glDistancePointLine(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim);

template<typename TND>
double glDistancePointLine2(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim);

template<typename TND>
bool glIsPointOnLine(const TND& ln1, const TND& ln2, const TND& point, unsigned int dim, double maxRelErr, double maxAbsErr);
	
template<typename T3D>
double glDistancePointLineSeg3D(const T3D& ls1, const T3D& ls2, const T3D& point, double* paramVal=NULL);

template<typename T3D>
double glDistancePointRay3D(const T3D& ls1, const T3D& ls2, const T3D& point, double* paramVal=NULL);

template<typename TND>
double glDistancePointLineSeg(const TND& ls1, const TND& ls2, const TND& point, unsigned int dim, double* paramVal=NULL);

#include "SMathLib/Impl/PointLine.hpp"

};	// end namespace SMathLib.

#endif // _SMATHLIB_POINTLINE_H_