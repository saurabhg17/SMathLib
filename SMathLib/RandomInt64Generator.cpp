
#include "RandomInt64Generator.h"
#include <random>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct RandomInt64GeneratorPriv
{
	RandomInt64GeneratorPriv()
		: mGenerator(mRandomDevice()), mDistribution(1, 100)
	{}

	RandomInt64GeneratorPriv(const long long minValue, const long long maxValue)
		: mGenerator(mRandomDevice()), mDistribution(minValue, maxValue)
	{}

	std::random_device                       mRandomDevice;
	std::mt19937                             mGenerator;
	std::uniform_int_distribution<long long> mDistribution;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
RandomInt64Generator::RandomInt64Generator()
	: mPriv(new RandomInt64GeneratorPriv)
{
}
RandomInt64Generator::RandomInt64Generator(const long long minValue, const long long maxValue)
	: mPriv(new RandomInt64GeneratorPriv(minValue, maxValue))
{
}
RandomInt64Generator::~RandomInt64Generator()
{
	delete mPriv;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
long long RandomInt64Generator::generate() const
{
	return mPriv->mDistribution(mPriv->mGenerator);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
