#pragma once

#include <vector>
#include <set>
#include <typeinfo>

typedef int EntityId;

class ECSManager; // Forward reference

class ECSSystem
{
public:
  ECSSystem();
  ECSSystem(ECSSystem&) = delete;

  virtual std::set<const std::type_info*> initializeTypeFilter() = 0;

  void initialize();

	virtual void onUpdate(ECSManager& manager, float deltaTime) = 0;

  void registerEntity(EntityId entityId);

  inline std::set<const std::type_info*>& getTypeFilter() { return componentTypeFilter; }
  inline std::vector<EntityId>& getEntities() { return entities; }
  
private:
  std::set<const std::type_info*> componentTypeFilter;

  // Vector for fast iteration
  std::vector<EntityId> entities;

  // Duplicate set for O(1) check if an entity is registered
  std::set<EntityId> entitiesSet;
};

// Helper macros for type filter
#ifndef ENTITY_TYPE_FILTER
  // Macro with a variable number of arguments, see https://stackoverflow.com/a/41177384
  #define NUM_ARGS_(_1, _2, _3, _4, _5, _6, TOTAL, ...) TOTAL
  #define NUM_ARGS(...) NUM_ARGS_(__VA_ARGS__, 6, 5, 4, 3, 2, 1)

  #define CONCATE_(X, Y) X##Y
  #define CONCATE(MACRO, NUMBER) CONCATE_(MACRO, NUMBER)
  #define VA_MACRO(MACRO, ...) CONCATE(MACRO, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)

  #define ENTITY_TYPE_FILTER(...) VA_MACRO(ENTITY_TYPE_FILTER, __VA_ARGS__)

  #define ENTITY_TYPE_FILTER1(a) inline virtual std::set<const std::type_info*> initializeTypeFilter() override \
    { return std::set<const std::type_info*>{&typeid(a)}; }
  #define ENTITY_TYPE_FILTER2(a, b) inline virtual std::set<const std::type_info*> initializeTypeFilter() override \
    { return std::set<const std::type_info*>{&typeid(a), &typeid(b)}; }
  #define ENTITY_TYPE_FILTER3(a, b, c) inline virtual std::set<const std::type_info*> initializeTypeFilter() override \
    { return std::set<const std::type_info*>{&typeid(a), &typeid(b), &typeid(c)}; }
  #define ENTITY_TYPE_FILTER4(a, b, c, d) inline virtual std::set<const std::type_info*> initializeTypeFilter() override \
    { return std::set<const std::type_info*>{&typeid(a), &typeid(b), &typeid(c), &typeid(d)}; }
  #define ENTITY_TYPE_FILTER5(a, b, c, d, e) inline virtual std::set<const std::type_info*> initializeTypeFilter() override \
    { return std::set<const std::type_info*>{&typeid(a), &typeid(b), &typeid(c), &typeid(d), &typeid(e)}; }
#endif
