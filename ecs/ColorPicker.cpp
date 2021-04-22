#include "ColorPicker.h"
#include "RandomNumberGenerator.h"

sf::Color ColorPicker::generateRandomColor()
{
	// use HSV
	const auto hue = static_cast<float>(RandomNumberGenerator::getInstance().generateInt(0, 360));
	return HSVToRGB(hue, 1.0, 1.0);
}

sf::Color ColorPicker::HSVToRGB(float h, float s, float v)
{
	const auto c = s * v;
	const auto x = static_cast<float>(c * (1 - abs(fmod(h / 60.0, 2) - 1)));
	const auto m = v - c;
	float rs, gs, bs;

	if (h >= 0 && h < 60) {
		rs = c;
		gs = x;
		bs = 0;
	}
	else if (h >= 60 && h < 120) {
		rs = x;
		gs = c;
		bs = 0;
	}
	else if (h >= 120 && h < 180) {
		rs = 0;
		gs = c;
		bs = x;
	}
	else if (h >= 180 && h < 240) {
		rs = 0;
		gs = x;
		bs = c;
	}
	else if (h >= 240 && h < 300) {
		rs = x;
		gs = 0;
		bs = c;
	}
	else {
		rs = c;
		gs = 0;
		bs = x;
	}

	const auto r = static_cast<sf::Uint8>((rs + m) * 255);
	const auto g = static_cast<sf::Uint8>((gs + m) * 255);
	const auto b = static_cast<sf::Uint8>((bs + m) * 255);
	
	return sf::Color(r, g, b);
}

