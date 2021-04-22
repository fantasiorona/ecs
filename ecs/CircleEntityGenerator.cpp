#include "CircleEntityGenerator.h"
#include "ColorPicker.h"
#include "RandomNumberGenerator.h"

MovingCircleEntity* CircleEntityGenerator::generateInBounds(const sf::Rect<float>& bounds)
{
    auto& rng = RandomNumberGenerator::getInstance();

    // create the entity with random color, radius, and velocity
	// always start from center position
    const sf::Vector2f position((bounds.left + bounds.width) / 2.f, (bounds.top + bounds.height) / 2.f);
    const auto color = ColorPicker::generateRandomColor();
	const auto radius = rng.generateFloat(8.f, 32.f);

    const auto twoPi = static_cast<float>(atan(1.0) * 4 * 2);
    const auto angle = rng.generateFloat(0.f, twoPi);
    const auto v = rng.generateFloat(5.f, 100.f);

    // scale the unit vector by velocity
    const sf::Vector2f velocity(cos(angle) * v, sin(angle) * v);

	// create the entity
    return new MovingCircleEntity(position, radius, color, velocity, bounds);
}

