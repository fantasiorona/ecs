#pragma once

#include "ECSSystem.h"
#include "StatsComponent.h"
#include "ECSManager.h"

#include <SFML/Graphics.hpp>

class StatsSystem : public ECSSystem
{
public:
  ENTITY_TYPE_FILTER(StatsComponent)

  StatsSystem(sf::RenderWindow* window);

	virtual void onUpdate(ECSManager& manager, float deltaTime) override;

private:
  sf::RenderWindow* window;
};
