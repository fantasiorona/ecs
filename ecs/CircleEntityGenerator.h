#pragma once

#include <SFML/Graphics.hpp>

#include "MovingCircleEntity.h"

class CircleEntityGenerator
{
public:
	static MovingCircleEntity* generateInBounds(const sf::Rect<float>& bounds);
};

