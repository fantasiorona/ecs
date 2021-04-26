#pragma once

#include <array>

typedef int EntityId;

// Generic container that holds components 
// Loosely based on https://austinmorlan.com/posts/entity_component_system/#the-component-array.

// All components of type T indexed by the Entity ID (fastest way of indexing). The components use a linear memory layout.
// This method of indexing is much faster than using a hash map, but comes at the cost of more memory usage 
// (unnecessary space is reserved for all entities, even if they don't have the component).
// This is ideal for the use case, however, since almost all entities have all components.
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
    components[id].~T();
  }

  T& getComponent(EntityId entityId) {
    return components[entityId];
  }

private:
  std::array<T, Size> components;
};
