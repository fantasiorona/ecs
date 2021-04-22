#include "MovingCircleEntity.h"

#include "TextureManager.h"
#include "VectorMath.h" 

MovingCircleEntity::MovingCircleEntity(const sf::Vector2f& position, float radius, const sf::Color& color, const sf::Vector2f& velocity, const sf::Rect<float>& worldBounds)
	: _position(position), _radius(radius), _color(color), _velocity(velocity)
{
	// each entry represents the normal of a rectangle line (inwards facing) plus the line offset in normal direction
	// order of line representations: top, right, bottom, left
	_bounds = {
		std::make_pair(sf::Vector2f(0.f, 1.f), worldBounds.top),
		std::make_pair(sf::Vector2f(-1.f, 0.f), worldBounds.left + worldBounds.width),
		std::make_pair(sf::Vector2f(0.f, -1.f), worldBounds.top + worldBounds.height),
		std::make_pair(sf::Vector2f(1.f, 0.f), worldBounds.left)
	};
}

void MovingCircleEntity::update(const sf::Time& dt)
{
	auto seconds = dt.asSeconds();

	// calculate the next position
	auto nextPosition = _position + _velocity * seconds;

	// check for a potential collision against all bounds
	for (auto bound : _bounds)
	{
		const sf::Vector3f l(bound.first.x, bound.first.y, bound.second - _radius);
		const sf::Vector3f p1(nextPosition.x, nextPosition.y, 1.f);

		const auto distance = VectorMath::dot(p1, l);

		// we have an intersection between circle and boundary
		if (distance <= 0.f)
		{
			const sf::Vector3f p0(_position.x, _position.y, 1.f);
			const sf::Vector3f v(_velocity.x, _velocity.y, 0.f);

			// calculate the exact time of collision
			const auto t = -VectorMath::dot(l, p0) / VectorMath::dot(l, v);

			// move the circle forward until it collides
			_position += _velocity * t;

			// calculate remaining time
			seconds -= t;

			// invert the movement direction
			const auto reverse = -_velocity;

			// calculate the reflection vector and take it as the new velocity
			_velocity = 2.f * VectorMath::dot(bound.first, reverse) * bound.first - reverse;

			// for the remaining time, move into the new direction
			nextPosition = _position + _velocity * std::max(seconds, 0.f);

			break;
		}
	}

	_position = nextPosition;
}

void MovingCircleEntity::draw(sf::RenderWindow& window)
{
	const auto& texture = TextureManager::getInstance().getCircleTexture();
	const auto textureSize = static_cast<float>(texture.getSize().x);

	// the texture coordinates
	const sf::Vector2f uvTl(0.f, 0.f);
	const sf::Vector2f uvTr(textureSize, 0.f);
	const sf::Vector2f uvBr(textureSize, textureSize);
	const sf::Vector2f uvBl(0.f, textureSize);

	// generate the corner coordinates
	const sf::Vector2f tl(_position.x - _radius, _position.y - _radius);
	const sf::Vector2f tr(_position.x + _radius, _position.y - _radius);
	const sf::Vector2f bl(_position.x - _radius, _position.y + _radius);
	const sf::Vector2f br(_position.x + _radius, _position.y + _radius);

	// write the vertices (position, color, texture coordinates)
	sf::Vertex vertices[_kNumVertices];

	// array pointer for quick iteration
	auto* v = vertices;

	*v++ = sf::Vertex(tl, _color, uvTl);
	*v++ = sf::Vertex(tr, _color, uvTr);
	*v++ = sf::Vertex(br, _color, uvBr);
	*v++ = sf::Vertex(bl, _color, uvBl);

	// draw using the circle texture
	window.draw(vertices, _kNumVertices, sf::Quads, &texture);
}
