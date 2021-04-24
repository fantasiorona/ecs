#pragma once

#include "ECSSystem.h"
#include "CircleComponents.h"
#include "ECSManager.h"

class CircleMoveSystem : public ECSSystem
{
public:

  // Specify which components the system uses. It will only operate on entities that have all these components.
  // This macro generates the following code:
  /*
    inline virtual std::set<TypeHash> initializeTypeFilter() override {
      return std::set<TypeHash>{typeid(TransformComponent).hash_code(), typeid(CircleCollisionComponent).hash_code()};
    }
  */
  ENTITY_TYPE_FILTER(TransformComponent, CircleCollisionComponent)

	virtual void onUpdate(ECSManager& manager, float deltaTime) override;

};
