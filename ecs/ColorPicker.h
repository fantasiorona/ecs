#pragma once

#include <SFML/Graphics.hpp>

class ColorPicker
{
public:
	static sf::Color generateRandomColor();

private:
	static sf::Color HSVToRGB(float h, float s, float v);
};

