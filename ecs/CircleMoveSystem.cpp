#include "CircleMoveSystem.h"

#include "VectorMath.h"

void CircleMoveSystem::onUpdate(ECSManager& manager, float deltaTime) {
  for (auto& entity: getEntities()) {
    auto [transform, collision] = manager.getComponents<TransformComponent, CircleCollisionComponent>(entity);

    // calculate the next position
    auto nextPosition = transform.position + transform.velocity * deltaTime;

    // check for a potential collision against all bounds
    for (auto bound : collision.bounds)
    {
      const sf::Vector3f l(bound.first.x, bound.first.y, bound.second - collision.radius);
      const sf::Vector3f p1(nextPosition.x, nextPosition.y, 1.f);

      const auto distance = VectorMath::dot(p1, l);

      // we have an intersection between circle and boundary
      if (distance <= 0.f)
      {
        const sf::Vector3f p0(transform.position.x, transform.position.y, 1.f);
        const sf::Vector3f v(transform.velocity.x, transform.velocity.y, 0.f);

        // calculate the exact time of collision
        const auto t = -VectorMath::dot(l, p0) / VectorMath::dot(l, v);

        // move the circle forward until it collides
        transform.position += transform.velocity * t;

        // calculate remaining time
        float remainingSeconds = deltaTime - t;

        // invert the movement direction
        const auto reverse = -transform.velocity;

        // calculate the reflection vector and take it as the new velocity
        transform.velocity = 2.f * VectorMath::dot(bound.first, reverse) * bound.first - reverse;

        // for the remaining time, move into the new direction
        nextPosition = transform.position + transform.velocity * std::max(remainingSeconds, 0.f);

        break;
      }
    }

    transform.position = nextPosition;
  }
}
