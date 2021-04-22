#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual ~Entity() = default;
	virtual void update(const sf::Time& dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};
