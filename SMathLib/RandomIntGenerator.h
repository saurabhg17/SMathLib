// 
// This file is part of SLogLib; you can redistribute it and/or 
// modify it under the terms of the MIT License.
// Author: Saurabh Garg (saurabhgarg@mysoc.net)
// 

#ifndef _SMATHLIB_RANDOMINTGENERATOR_H_
#define _SMATHLIB_RANDOMINTGENERATOR_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

struct RandomIntGeneratorPriv;

class SMATHLIB_DLL_API RandomIntGenerator
{
public:
	
	RandomIntGenerator();
	RandomIntGenerator(const int minValue, const int maxValue);
	~RandomIntGenerator();

	int generate() const;

private:
	
	RandomIntGeneratorPriv* mPriv;
};

};	// End namespace SMathLib.

#endif // _SMATHLIB_RANDOMINTGENERATOR_H_
