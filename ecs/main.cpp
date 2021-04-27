#include <SFML/Graphics.hpp>
#include <cassert>

#include "RandomNumberGenerator.h"
#include "ColorPicker.h"

#include "ECSManager.h"

#include "CircleMoveSystem.h"
#include "RenderSystem.h"
#include "StatsSystem.h"

#include "CircleComponents.h"
#include "StatsComponent.h"


/**
* 2.6 GHz Quad-Core Intel Core i7
* In release build the old code ran smoothly with 33ms when there were 100.000 entities,
* whilst the new code could handle 155000 entites. There was a 55% improvement.
* 
* Intel Core i7-8550U CPU @ 1.80GHz 1.99 GHz
* In release build the old code ran smoothly with 33ms when there were 85.000 entities,
* whilst the new code could handle 135000 entites. There was a 58% improvement.
*/
int main()
{
    const unsigned int windowWidth = 1024;
    const unsigned int windowHeight = 768;
    const unsigned int numEntities = 155000;
    const sf::Rect<float> bounds(0.f, 0.f, windowWidth, windowHeight);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ECS Moving Circles");

    // The ECSManager coordinates entities, components and systems
    ECSManager manager;

    // Register systems with the manager
    manager.addSystem<CircleMoveSystem>();
    manager.addSystem<RenderSystem>(&window);
    manager.addSystem<StatsSystem>(&window);

    // Generate circle entities
    auto& rng = RandomNumberGenerator::getInstance();

    for (unsigned int i = 0; i < numEntities; i++) {
        // create the entity with random color, radius, and velocity
        // always start from center position
        const sf::Vector2f position((bounds.left + bounds.width) / 2.f, (bounds.top + bounds.height) / 2.f);
        const auto color = ColorPicker::generateRandomColor();
        const auto radius = rng.generateFloat(8.f, 32.f);

        const auto twoPi = static_cast<float>(atan(1.0) * 4 * 2);
        const auto angle = rng.generateFloat(0.f, twoPi);
        const auto v = rng.generateFloat(5.f, 100.f);

        // scale the unit vector by velocity
        const sf::Vector2f velocity(cos(angle) * v, sin(angle) * v);

        // --------------------------------
        // Create the entity and components
        auto entity = manager.createEntity();

        auto& transform = manager.addComponent<TransformComponent>(entity);
        transform.position = position;
        transform.velocity = velocity;

        auto& colorComponent = manager.addComponent<ColorComponent>(entity);
        colorComponent.color = color;

        auto& collisionComponent = manager.addComponent<CircleCollisionComponent>(entity);
        collisionComponent.radius = radius;
        collisionComponent.bounds = {
            std::make_pair(sf::Vector2f(0.f, 1.f), bounds.top),
            std::make_pair(sf::Vector2f(-1.f, 0.f), bounds.left + bounds.width),
            std::make_pair(sf::Vector2f(0.f, -1.f), bounds.top + bounds.height),
            std::make_pair(sf::Vector2f(1.f, 0.f), bounds.left)
        };
    }

    // Entity for stats display
    auto statsEntity = manager.createEntity();
    auto& statsComponent = manager.addComponent<StatsComponent>(statsEntity);

    const auto success = statsComponent.font.loadFromFile("fonts/JetBrainsMono-Regular.ttf");
	assert(success);

	// configure the font
	statsComponent.text.setFont(statsComponent.font);
	statsComponent.text.setCharacterSize(24);
	statsComponent.text.setFillColor(sf::Color::Yellow);

    sf::Clock clock;
    while (window.isOpen())
    {
        const auto dt = clock.restart();
    	
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        manager.update(dt.asSeconds());

        window.display();
    }

    return 0;
}
