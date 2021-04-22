#include <cassert>

#include "StatsEntity.h"

StatsEntity::StatsEntity()
{
	// load the font, assume success
	const auto success = _font.loadFromFile("fonts/JetBrainsMono-Regular.ttf");
	assert(success);

	// configure the font
	_stats.setFont(_font);
	_stats.setCharacterSize(24);
	_stats.setFillColor(sf::Color::Yellow);
}

void StatsEntity::update(const sf::Time& dt)
{
	// we output frametime in milliseconds
	// 16 ms -> 60 frames per second, our gold standard
	const auto text = "frametime: " + std::to_string(dt.asMilliseconds()) + " ms";
	_stats.setString(text);
}

void StatsEntity::draw(sf::RenderWindow& window)
{
	window.draw(_stats);
}


