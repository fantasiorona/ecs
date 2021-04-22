#include "ECSSystem.h"

ECSSystem::ECSSystem() {}

void ECSSystem::initialize() {
  componentTypeFilter = initializeTypeFilter();
}

void ECSSystem::registerEntity(EntityId id) {
  entities.insert(id);
}

void ECSSystem::unregisterEntity(EntityId id) {
  entities.erase(id);
}
