#pragma once

#include <SFML/Graphics.hpp>
#include <array>

struct TransformComponent
{
	sf::Vector2f position = {};
	sf::Vector2f velocity = {};
};

struct ColorComponent
{
	sf::Color color = {};
};

struct RadiusComponent
{
	float radius = 1.f;
};

struct BoundsComponent
{
	std::array<std::pair<sf::Vector2f, float>, 4> bounds;
};
