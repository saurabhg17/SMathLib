
#include "RandomDoubleGenerator.h"
#include <random>

namespace SMathLib {
;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
struct RandomDoubleGeneratorPriv
{
	RandomDoubleGeneratorPriv()
		: mGenerator(mRandomDevice()), mDistribution(1, 100)
	{}

	RandomDoubleGeneratorPriv(const double minValue, const double maxValue)
		: mGenerator(mRandomDevice()), mDistribution(minValue, maxValue)
	{}

	std::random_device               mRandomDevice;
	std::mt19937                     mGenerator;
	std::uniform_real_distribution<> mDistribution;
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
RandomDoubleGenerator::RandomDoubleGenerator()
	: mPriv(new RandomDoubleGeneratorPriv)
{
}
RandomDoubleGenerator::RandomDoubleGenerator(double minValue, double maxValue)
	: mPriv(new RandomDoubleGeneratorPriv(minValue, maxValue))
{
}
RandomDoubleGenerator::~RandomDoubleGenerator()
{
	delete mPriv;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
double RandomDoubleGenerator::generate() const
{
	return mPriv->mDistribution(mPriv->mGenerator);
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

};	// End namespace SMathLib.
