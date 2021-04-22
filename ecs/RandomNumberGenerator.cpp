#include <cstdlib>
#include <ctime>
#include <cassert>

#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}


int RandomNumberGenerator::generateInt(int min, int max)
{
	assert(max >= min);
	
	const auto range = (max - min) + 1;
	
	if (range <= 0)
	{
		return min;
	}

	return min + (std::rand() % range);
}

float RandomNumberGenerator::generateFloat(float min, float max)
{
	assert(max >= min);

	const auto range = max - min;

	if (range <= 0)
	{
		return min;
	}
	
	const auto randVal = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	return min + randVal * range;
}

