
#include "Random.h"
#include "MinMax.h"
#include <ctime>
#include <cmath>

#if defined(SMATHLIB_USE_BOOST_RAND)
	#include "boost/random/mersenne_twister.hpp"
	#include "boost/random/uniform_int_distribution.hpp"
	#include "boost/random/uniform_real_distribution.hpp"
#elif defined(SMATHLIB_USE_GSL_RAND)
	#include "gsl/gsl_rng.h"
	#include <string>
#else
	#define SMATHLIB_USE_CRT_RND
	#include <cstdlib>
	// The standard library function rand() generates a uniform random number 
	// between 0 - RAND_MAX which is 32767.
#endif

#if defined(SMATHLIB_OS_WINDOWS)
	#include <windows.h>
#elif defined(SMATHLIB_OS_LINUX)
	#include <sys/time.h>
#endif

namespace SMathLib {
;

//! Class RandomPriv hides the implement of random number generator from GSL.
//! This makes the interface of class Random independent GSL.
//! Thus clients of Random don't have to worry about it.
class RandomPriv
{
private:
	
	friend class Random;
	
	#if defined(SMATHLIB_USE_BOOST_RAND)
		boost::random::mt19937 mBoostRandom;
	#elif defined(SMATHLIB_USE_GSL_RAND)
		gsl_rng* mGslRandom;
	#endif
};



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Constructor.
Random::Random()
{
	#if defined(SMATHLIB_USE_BOOST_RAND)
		mRandomPriv = new RandomPriv;
		// Determine seed.
		int _seed = static_cast<unsigned int>(std::time(0));
		#if defined(SMATHLIB_OS_WINDOWS)
			SYSTEMTIME st;
			GetSystemTime(&st);
			_seed = st.wSecond * 100 + st.wMilliseconds;
		#elif defined(SMATHLIB_OS_LINUX)
			struct timeval tv;
			gettimeofday(&tv, NULL);
			_seed = tv.tv_sec * 100 + (tv.tv_usec / 1000);
		#endif
		mRandomPriv->mBoostRandom.seed(_seed);
	#elif defined(SMATHLIB_USE_GSL_RAND)
		mRandomPriv = new RandomPriv;
		mRandomPriv->mGslRandom = NULL;
		
		const gsl_rng_type** t0 = gsl_rng_types_setup();
		const gsl_rng_type** t;
		
		for(t = t0; *t != 0; t++)
		{
			if(std::string((*t)->name) == "taus")
			{
				break;
			}
		}
		
		if(*t == NULL)
		{
			return;
		}
		
		mRandomPriv->mGslRandom = gsl_rng_alloc(*t);
		gsl_rng_set(mRandomPriv->mGslRandom, (unsigned)time(NULL));
	#else
		mRandomPriv = NULL;
		srand((unsigned)time(NULL));
	#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Destructor.
Random::~Random()
{
	#if defined(SMATHLIB_USE_GSL_RAND)
		if(mRandomPriv)
		{
			if(mRandomPriv->mGslRandom)
			{
				gsl_rng_free(mRandomPriv->mGslRandom);
			}
			delete mRandomPriv;
		}
	#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Generate a double precision uniform random number between [0.0, 1.0].
double Random::UniformRand()
{
	#if defined(SMATHLIB_USE_BOOST_RAND)
		boost::random::uniform_real_distribution<double> _random(0, 1);
		return _random(mRandomPriv->mBoostRandom);
	#elif defined(SMATHLIB_USE_GSL_RAND)
		return gsl_rng_uniform(mRandomPriv->mGslRandom);
	#else
		return double(rand()%1000)/1000.0;
	#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Generate a double precision uniform random number between [minN, maxN].
double Random::UniformRand(double minN, double maxN)
{
	#if defined(SMATHLIB_USE_BOOST_RAND)
		boost::random::uniform_real_distribution<double> _random(minN, maxN);
		return _random(mRandomPriv->mBoostRandom);
	#elif defined(SMATHLIB_USE_GSL_RAND)
		return minN + gsl_rng_uniform(mRandomPriv->mGslRandom)*fabs(maxN - minN);
	#else
		return minN + UniformRand()*fabs(maxN - minN);
	#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Generate a integer uniform random number between [N, M).
int Random::UniformRand(int N, int M)
{
	#if defined(SMATHLIB_USE_BOOST_RAND)
		boost::random::uniform_int_distribution<int> _random(N, M);
		return _random(mRandomPriv->mBoostRandom);
	#elif defined(SMATHLIB_USE_GSL_RAND)
		return N + gsl_rng_uniform_int(mRandomPriv->mGslRandom, M-N);
	#else
		return N + int((M-N)*UniformRand());
	#endif
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// end namespace SMathLib.
