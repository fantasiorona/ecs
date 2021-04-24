#pragma once

#include <memory>
#include <tuple>

// robin_hood.h contains a much faster hash map implementation compared
// to "std::unordered_map" (see https://github.com/martinus/robin-hood-hashing)
#include "robin_hood.h"
#include "ECSSystem.h"
#include "ComponentVector.h"

const size_t MAX_ENTITIES = 500000;

typedef size_t TypeHash;

class ECSManager final
{
public:
  ECSManager();
  ECSManager(ECSManager&) = delete;

  ~ECSManager();

  // Update all systems
  void update(float deltaTime);

  // Creates a new entity and returns its ID
  EntityId createEntity();

  // Removes the entity with the given ID and all its components
  void removeEntity(EntityId id);

  template<typename T, typename... ConstructorArgs>
  T& addSystem(ConstructorArgs... args) {
    T* system = new T(args...);
    systems.push_back(system);

    // Cache the component type IDs that the system handles
    system->initialize();

    return *system;
  }

  template<typename T>
  T& addComponent(EntityId entityId) {
    // The component type is used as an index
    auto typeHash = typeid(T).hash_code();
    typesByEntity[entityId].insert(typeHash);

    // Retrieve the component array for the component type and cast it to the right type or create a new one
    auto components = static_cast<ComponentVector<T, MAX_ENTITIES>*>(componentsByType[typeHash]);
    if (components == nullptr) {
      components = new ComponentVector<T, MAX_ENTITIES>();
      componentsByType[typeHash] = components;
    }

    auto& component = components->addComponent(entityId);

    // Mark the entity as dirty to register it with systems later
    dirtyEntities.insert(entityId);
    return component;
  }

  template<typename T>
  void removeComponent(EntityId entityId) {
    // TODO: implement
  }

  template<typename T>
  T& getComponent(EntityId entityId) {
    // Get the hash code of the component type
    auto typeHash = typeid(T).hash_code();

    // Get the component array for the type and retrieve the entity
    return static_cast<ComponentVector<T, MAX_ENTITIES>*>(componentsByType[typeHash])->getComponent(entityId);
  }

  // Convenience templates for getting multiple components. Can be called with up to five type arguments.
  // Supports C++17 structured bindings since it returns an std::tuple. Usage example:
  // auto [transform, collision] = manager.getComponents<TransformComponent, CircleCollisionComponent>(entityId);
  template<typename T1, typename T2>
  std::tuple<T1&, T2&> getComponents(EntityId entityId) {
    return std::forward_as_tuple(getComponent<T1>(entityId), getComponent<T2>(entityId));
  }

  template<typename T1, typename T2, typename T3>
  std::tuple<T1&, T2&, T3&> getComponents(EntityId entityId) {
    return std::forward_as_tuple(getComponent<T1>(entityId), getComponent<T2>(entityId), getComponent<T3>(entityId));
  }

  template<typename T1, typename T2, typename T3, typename T4>
  std::tuple<T1&, T2&, T3&, T4&> getComponents(EntityId entityId) {
    return std::forward_as_tuple(getComponent<T1>(entityId), getComponent<T2>(entityId),
      getComponent<T3>(entityId), getComponent<T4>(entityId));
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  std::tuple<T1&, T2&, T3&, T4&> getComponents(EntityId entityId) {
    return std::forward_as_tuple(getComponent<T1>(entityId), getComponent<T2>(entityId), getComponent<T3>(entityId),
      getComponent<T4>(entityId), getComponent<T5>(entityId));
  }

private:
  // The key is a hash of std::type_info
	robin_hood::unordered_map<TypeHash, ComponentVectorBase*> componentsByType;

  // Map of component types used by each entity to speed up registering entities with systems
	robin_hood::unordered_map<EntityId, std::set<TypeHash> > typesByEntity;
  std::vector<ECSSystem* > systems;

  // Entities that need to be registered or unregistered with systems because components were added or removed
  std::set<EntityId> dirtyEntities;

  // Incremented whenever an entity is created
  EntityId currentEntityId = 0;

  // Updates the registration status of all dirty entities on all systems
  void updateEntityRegistration();

};
