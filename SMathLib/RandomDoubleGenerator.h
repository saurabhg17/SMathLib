
#ifndef _SMATHLIB_RANDOMDOUBLEGENERATOR_H_
#define _SMATHLIB_RANDOMDOUBLEGENERATOR_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

struct RandomDoubleGeneratorPriv;

class SMATHLIB_DLL_API RandomDoubleGenerator
{
public:
	
	RandomDoubleGenerator();
	RandomDoubleGenerator(const double minValue, const double maxValue);
	~RandomDoubleGenerator();
	
	double generate() const;

private:
	
	RandomDoubleGeneratorPriv* mPriv;
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_RANDOMDOUBLEGENERATOR_H_
