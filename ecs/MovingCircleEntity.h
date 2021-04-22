#pragma once

#include "Entity.h"

class MovingCircleEntity : public Entity
{
public:
	MovingCircleEntity(const sf::Vector2f& position,
		float radius,
		const sf::Color& color,
		const sf::Vector2f& velocity, 
		const sf::Rect<float>& worldBounds);
	virtual ~MovingCircleEntity() = default;
	
	void update(const sf::Time& dt) override;
	void draw(sf::RenderWindow& window) override;
	
private:
	static const size_t _kNumVertices = 4;
	
	sf::Color _color;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	float _radius = 0.f;

	std::vector<std::pair<sf::Vector2f, float>> _bounds;
};

