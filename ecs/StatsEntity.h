#pragma once

#include "Entity.h"

class StatsEntity : public Entity
{
public:
	StatsEntity();
	virtual ~StatsEntity() = default;

	void update(const sf::Time & dt) override;
	void draw(sf::RenderWindow & window) override;

private:
	sf::Font _font;
	sf::Text _stats;
};
