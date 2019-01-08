
#ifndef _SMATHLIB_RANDOM_H_
#define _SMATHLIB_RANDOM_H_

#include "SMathLib/Config.h"

namespace SMathLib {
;

// Forward declaration.
class RandomPriv;

//! Class for generating random numbers.
class SMATHLIB_DLL_API Random
{
public:
	
	//! Constructor.
	Random();
	
	//! Destructor.
	~Random();
	
	//! Generate a double precision uniform random number between [0.0, 1.0].
	//! \return Uniform random number between [0.0, 1.0].
	double UniformRand();
	
	//! Generate a double precision uniform random number between [minN, maxN].
	//! \return Uniform random number between [minN, maxN].
	double UniformRand(double minN, double maxN);
	
	//! Generate a integer uniform random number between [N, M).
	//! \return Uniform random number between [N, M).
	int UniformRand(int N, int M);
	
private:
	
	RandomPriv* mRandomPriv;
};

};	// end namespace SMathLib.

#endif // _SMATHLIB_RANDOM_H_
