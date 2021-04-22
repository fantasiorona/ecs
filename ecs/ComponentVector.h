#pragma once

#include <unordered_map>
#include <vector>

typedef int EntityId;

// Generic container that holds components 
// Based on https://austinmorlan.com/posts/entity_component_system/#the-component-array
class ComponentVectorBase {
public:
  virtual void removeComponent(EntityId id) = 0;
};

template <typename T>
class ComponentVector : public ComponentVectorBase {
public:
  T& addComponent(EntityId entityId) {
    // Ensure that there's only one component per entity
    assert(componentsByEntity.find(entityId) == componentsByEntity.end());

    components.push_back(T());
    size_t index = components.size() - 1;
    auto& component = components[index];

    componentsByEntity[entityId] = index;
    return component;
  }

  virtual void removeComponent(EntityId id) override {
    // TODO: implement
  }

  T& getComponent(EntityId entityId) {
    auto componentIndex = componentsByEntity[entityId];
    return components[componentIndex];
  }

private:
  std::vector<T> components;
  std::unordered_map<EntityId, size_t> componentsByEntity;
};
