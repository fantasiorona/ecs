#pragma once

#include <unordered_map>
#include <memory>
#include <tuple>

#include "ECSSystem.h"
#include "ComponentVector.h"

class ECSManager final
{
public:
  ECSManager();
  ECSManager(ECSManager&) = delete;

  EntityId createEntity();
  // void removeEntity(EntityId id);

  void update(float deltaTime);

  template<typename T>
  T& addComponent(EntityId entityId) {
    auto typeInfo = &typeid(T);
    typesByEntity[entityId].insert(typeInfo);

    auto components = static_cast<ComponentVector<T>*>(componentsByType[typeInfo]);
    if (components == nullptr) {
      components = new ComponentVector<T>();
      componentsByType[typeInfo] = components;
    }

    auto& component = components->addComponent(entityId);

    // Mark the entity as dirty to register it with systems later
    dirtyEntities.insert(entityId);
    return component;
  }

  template<typename T, typename... ConstructorArgs>
  T& addSystem(ConstructorArgs... args) {
    std::shared_ptr<T> system = std::make_shared<T>(args...);
    systems.push_back(system);

    system->initialize();

    return *system;
  }

  template<typename T>
  T& getComponent(EntityId entityId) {
    auto typeInfo = &typeid(T);
    return static_cast<ComponentVector<T>*>(componentsByType[typeInfo])->getComponent(entityId);
  }

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
	std::unordered_map<const std::type_info*, ComponentVectorBase*> componentsByType;
	std::unordered_map<EntityId, std::set<const std::type_info*> > typesByEntity;
  std::vector<std::shared_ptr<ECSSystem> > systems;

  // Entities that need to be registered or unregistered with systems because
  // components were added or removed
  std::set<EntityId> dirtyEntities;

  EntityId currentEntityId = 0;

  void updateEntityRegistration();

};
