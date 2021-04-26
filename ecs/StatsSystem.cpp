#include "StatsSystem.h"

#include "TextureManager.h"

StatsSystem::StatsSystem(sf::RenderWindow* window) : window(window) {
}

void StatsSystem::onUpdate(ECSManager& manager, float deltaTime) {
  for (auto& entity: getEntities()) {
    auto& stats = manager.getComponent<StatsComponent>(entity);

    // we output frametime in milliseconds
	// 16 ms -> 60 frames per second, our gold standard
    const auto text = "frametime: " + std::to_string((int) (deltaTime * 1000)) + " ms";
    stats.text.setString(text);

    window->draw(stats.text);
  }
}
