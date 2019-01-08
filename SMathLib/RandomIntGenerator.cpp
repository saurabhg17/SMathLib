
#include "RandomIntGenerator.h"
#include <random>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct RandomIntGeneratorPriv
{
	RandomIntGeneratorPriv()
		: mGenerator(mRandomDevice()), mDistribution(1, 100)
	{}

	RandomIntGeneratorPriv(const int minValue, const int maxValue)
		: mGenerator(mRandomDevice()), mDistribution(minValue, maxValue)
	{}

	std::random_device              mRandomDevice;
	std::mt19937                    mGenerator;
	std::uniform_int_distribution<> mDistribution;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
RandomIntGenerator::RandomIntGenerator()
	: mPriv(new RandomIntGeneratorPriv)
{
}
RandomIntGenerator::RandomIntGenerator(const int minValue, const int maxValue)
	: mPriv(new RandomIntGeneratorPriv(minValue, maxValue))
{
}
RandomIntGenerator::~RandomIntGenerator()
{
	delete mPriv;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int RandomIntGenerator::generate() const
{
	return mPriv->mDistribution(mPriv->mGenerator);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
