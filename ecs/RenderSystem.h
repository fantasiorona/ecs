#pragma once

#include "ECSSystem.h"
#include "CircleComponents.h"
#include "ECSManager.h"

#include <SFML/Graphics.hpp>

class RenderSystem : public ECSSystem
{
public:
  // Specify which components the system uses. It will only operate on entities that have all these components.
  // This macro generates the following code:
  /*
    inline virtual std::set<TypeHash> initializeTypeFilter() override {
      return std::set<TypeHash> {
        typeid(TransformComponent).hash_code(), typeid(ColorComponent).hash_code(), typeid(CircleCollisionComponent).hash_code() 
      };
    }
  */
  ENTITY_TYPE_FILTER(TransformComponent, ColorComponent, CircleCollisionComponent)

  RenderSystem(sf::RenderWindow* window);

	virtual void onUpdate(ECSManager& manager, float deltaTime) override;

private:
  static const size_t _kNumVertices = 4;

  sf::RenderWindow* window;
  std::vector<sf::Vertex> vertices;
};
