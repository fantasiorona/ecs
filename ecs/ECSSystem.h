#pragma once

#include <vector>
#include <set>
#include <typeinfo>

#include "robin_hood.h"

typedef size_t TypeHash;
typedef int EntityId;

class ECSManager; // Forward reference

class ECSSystem
{
public:
  ECSSystem();
  ECSSystem(ECSSystem&) = delete;

  // Set of all types that the system handles
  virtual std::set<TypeHash> initializeTypeFilter() = 0;

  // Internal initialization
  void initialize();

  // Called on each frame on each system
  virtual void onUpdate(ECSManager& manager, float deltaTime) = 0;

  // Register an entity with the system (internal, called by ECSManager)
  void registerEntity(EntityId entityId);

  // Unregister an entity with the system (internal, called by ECSManager)
  void unregisterEntity(EntityId entityId);

  // Fast access to the type filter (initializeTypeFilter creates the std::set on each call)
  inline std::set<TypeHash>& getTypeFilter() { return componentTypeFilter; }

  // All entities that are handled by the system
  inline std::vector<EntityId>& getEntities() { return entities; }
  
private:
  std::set<TypeHash> componentTypeFilter;

  // Two data structures to get the best of both worlds
  // The vector can be iterated much faster than the map
  std::vector<EntityId> entities;

  // Duplicate map for O(1) check if an entity is registered and O(1) deletion
  robin_hood::unordered_map<EntityId, size_t> entityIdMap;
  
};

// Helper macros for type filter.
// Usage: ENTITY_TYPE_FILTER(ComponentType1, ComponentType2, ...), up to 5 arguments
#ifndef ENTITY_TYPE_FILTER
  // Macro with a variable number of arguments, see https://stackoverflow.com/a/41177384
  #define NUM_ARGS_(_1, _2, _3, _4, _5, _6, TOTAL, ...) TOTAL
  #define NUM_ARGS(...) NUM_ARGS_(__VA_ARGS__, 6, 5, 4, 3, 2, 1)

  #define CONCATE_(X, Y) X##Y
  #define CONCATE(MACRO, NUMBER) CONCATE_(MACRO, NUMBER)
  #define VA_MACRO(MACRO, ...) CONCATE(MACRO, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

  #define ENTITY_TYPE_FILTER(...) VA_MACRO(ENTITY_TYPE_FILTER, __VA_ARGS__)

  #define ENTITY_TYPE_FILTER1(a) inline virtual std::set<TypeHash> initializeTypeFilter() override \
    { return std::set<TypeHash>{typeid(a).hash_code()}; }
  #define ENTITY_TYPE_FILTER2(a, b) inline virtual std::set<TypeHash> initializeTypeFilter() override \
    { return std::set<TypeHash>{typeid(a).hash_code(), typeid(b).hash_code()}; }
  #define ENTITY_TYPE_FILTER3(a, b, c) inline virtual std::set<TypeHash> initializeTypeFilter() override \
    { return std::set<TypeHash>{typeid(a).hash_code(), typeid(b).hash_code(), typeid(c).hash_code()}; }
  #define ENTITY_TYPE_FILTER4(a, b, c, d) inline virtual std::set<TypeHash> initializeTypeFilter() override \
    { return std::set<TypeHash>{typeid(a).hash_code(), typeid(b).hash_code(), typeid(c).hash_code(), typeid(d).hash_code()}; }
  #define ENTITY_TYPE_FILTER5(a, b, c, d, e) inline virtual std::set<TypeHash> initializeTypeFilter() override \
    { return std::set<TypeHash>{typeid(a).hash_code(), typeid(b).hash_code(), typeid(c).hash_code(), typeid(d).hash_code(), typeid(e).hash_code()}; }
#endif
