#pragma once

#include "ECSSystem.h"
#include "CircleComponents.h"
#include "ECSManager.h"

class CircleMoveSystem : public ECSSystem
{
public:
  ENTITY_TYPE_FILTER(TransformComponent, RadiusComponent, BoundsComponent)

	virtual void onUpdate(ECSManager& manager, float deltaTime) override;

};