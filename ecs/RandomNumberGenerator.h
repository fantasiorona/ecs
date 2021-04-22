#pragma once

class RandomNumberGenerator
{
public:
	RandomNumberGenerator(RandomNumberGenerator const&) = delete;
	void operator=(RandomNumberGenerator const&) = delete;
	
	static RandomNumberGenerator& getInstance()
	{
		static RandomNumberGenerator instance;
		return instance;
	};
	
	int generateInt(int min, int max);
	float generateFloat(float min, float max);

private:
	RandomNumberGenerator();
};

