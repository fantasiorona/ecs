#include "ECSManager.h"

#include <iostream>

ECSManager::ECSManager() {}

ECSManager::~ECSManager() {
  // TODO: implement destructor and free memory
  // Remove all entities etc.
}

EntityId ECSManager::createEntity() {
  auto entityId = ++currentEntityId;
  return entityId;
}

void ECSManager::removeEntity(EntityId id) {
  // TODO: implement
}

void ECSManager::updateEntityRegistration() {
  for (auto& system: systems) {
    for (auto entityId: dirtyEntities) {
      // The system should handle the entity if the entity contains components of every type that the system handles
      auto& typeFilter = system->getTypeFilter();
      bool hasAllTypes = true;

      for (auto& typeHash: typeFilter) {
        if (typesByEntity[entityId].count(typeHash) <= 0) {
          hasAllTypes = false;
        }
      }

      if (hasAllTypes) {
        system->registerEntity(entityId);
      } else {
        system->unregisterEntity(entityId);
      }
    }
  }

  dirtyEntities.clear();
} 

void ECSManager::update(float deltaTime) {
  if (dirtyEntities.size() > 0) {
    updateEntityRegistration();
  }

  // Call the update method on all systems
  for (auto& system: systems) {
    system->onUpdate(*this, deltaTime);
  }
}
