
#ifndef _SMATHLIB_RANDOMINT64GENERATOR_H_
#define _SMATHLIB_RANDOMINT64GENERATOR_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

struct RandomInt64GeneratorPriv;

class SMATHLIB_DLL_API RandomInt64Generator
{
public:
	
	RandomInt64Generator();
	RandomInt64Generator(const long long minValue, const long long maxValue);
	~RandomInt64Generator();

	long long generate() const;

private:
	
	RandomInt64GeneratorPriv* mPriv;
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_RANDOMINT64GENERATOR_H_
