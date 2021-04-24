#include "ECSSystem.h"

ECSSystem::ECSSystem() {}

void ECSSystem::initialize() {
  componentTypeFilter = initializeTypeFilter();
}

void ECSSystem::registerEntity(EntityId id) {
  if (entityIdMap.count(id) == 0) {
    entities.push_back(id);
    entityIdMap[id] = entities.size() -1;
  }
}

void ECSSystem::unregisterEntity(EntityId id) {
  if (entityIdMap.count(id) != 0) {
    // Delete the ID in O(1) by swapping and removing the last element
    std::swap(entities[entityIdMap[id]], entities[entities.size() - 1]);
    entities.pop_back();
    entityIdMap.erase(id);
  }
}
