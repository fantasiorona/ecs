#pragma once

#include "ECSSystem.h"
#include "CircleComponents.h"
#include "ECSManager.h"

#include <SFML/Graphics.hpp>

class RenderSystem : public ECSSystem
{
public:
  ENTITY_TYPE_FILTER(TransformComponent, ColorComponent, CircleCollisionComponent)

  RenderSystem(sf::RenderWindow* window);

	virtual void onUpdate(ECSManager& manager, float deltaTime) override;

private:
  static const size_t _kNumVertices = 4;

  sf::RenderWindow* window;
  std::vector<sf::Vertex> vertices;
};
