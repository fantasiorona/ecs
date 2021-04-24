#include "ECSSystem.h"

ECSSystem::ECSSystem() {}

void ECSSystem::initialize() {
  componentTypeFilter = initializeTypeFilter();
}

void ECSSystem::registerEntity(EntityId id) {
  if (entitiesSet.count(id) == 0) {
    entitiesSet.insert(id);
    entities.push_back(id);
  }
}

