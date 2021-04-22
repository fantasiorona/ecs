#include "VectorMath.h"

void VectorMath::normalize(sf::Vector2f& v)
{
	const auto invLength = 1.f / magnitude(v);
	v.x *= invLength;
	v.y *= invLength;
}

float VectorMath::magnitude(const sf::Vector2f& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float VectorMath::dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float VectorMath::dot(const sf::Vector3f& v1, const sf::Vector3f& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


