#pragma once

#include <SFML/Graphics.hpp>

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
	std::vector<std::pair<sf::Vector2f, float>> bounds;
};
