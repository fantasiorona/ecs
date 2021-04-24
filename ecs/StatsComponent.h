#pragma once

#include <SFML/Graphics.hpp>

// Replacement for StatsEntity
struct StatsComponent
{
	sf::Font font = {};
	sf::Text text = {};
};
