#include "RenderSystem.h"

#include "TextureManager.h"

RenderSystem::RenderSystem(sf::RenderWindow* window) : window(window) {
}

void RenderSystem::onUpdate(ECSManager& manager, float deltaTime) {
  window->clear();

  const auto& texture = TextureManager::getInstance().getCircleTexture();
  const auto textureSize = static_cast<float>(texture.getSize().x);

  // the texture coordinates
  const sf::Vector2f uvTl(0.f, 0.f);
  const sf::Vector2f uvTr(textureSize, 0.f);
  const sf::Vector2f uvBr(textureSize, textureSize);
  const sf::Vector2f uvBl(0.f, textureSize);

  auto entities = getEntities();

  // write the vertices (position, color, texture coordinates)
  vertices.clear();
  vertices.reserve(_kNumVertices * entities.size());

  for (auto& entity: entities) {
    auto [transform, color, collision] = manager.getComponents<
      TransformComponent, ColorComponent, CircleCollisionComponent>(entity);

    // generate the corner coordinates
    const sf::Vector2f tl(transform.position.x - collision.radius, transform.position.y - collision.radius);
    const sf::Vector2f tr(transform.position.x + collision.radius, transform.position.y - collision.radius);
    const sf::Vector2f bl(transform.position.x - collision.radius, transform.position.y + collision.radius);
    const sf::Vector2f br(transform.position.x + collision.radius, transform.position.y + collision.radius);

    vertices.push_back(sf::Vertex(tl, color.color, uvTl));
    vertices.push_back(sf::Vertex(tr, color.color, uvTr));
    vertices.push_back(sf::Vertex(br, color.color, uvBr));
    vertices.push_back(sf::Vertex(bl, color.color, uvBl));
  }

  // draw using the circle texture
  window->draw(vertices.data(), _kNumVertices * entities.size(), sf::Quads, &texture);
}
