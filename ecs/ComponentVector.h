#pragma once

#include <unordered_map>
#include <array>

typedef int EntityId;

// Generic container that holds components 
// Loosely based on https://austinmorlan.com/posts/entity_component_system/#the-component-array
class ComponentVectorBase {
public:
  virtual void removeComponent(EntityId id) = 0;
};

template <typename T, size_t Size>
class ComponentVector : public ComponentVectorBase {
public:
  T& addComponent(EntityId entityId) {
    components[entityId] = T();
    return components[entityId];
  }

  virtual void removeComponent(EntityId id) override {
    // TODO: implement
  }

  T& getComponent(EntityId entityId) {
    return components[entityId];
  }

private:
  std::array<T, Size> components;
};
