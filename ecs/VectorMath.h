#pragma once

#include <SFML/System.hpp>

class VectorMath
{
public:
	static void normalize(sf::Vector2f& v);
	static float magnitude(const sf::Vector2f& v);
	static float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
	static float dot(const sf::Vector3f& v1, const sf::Vector3f& v2);
};

