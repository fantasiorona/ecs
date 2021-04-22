#include <SFML/Graphics.hpp>

#include "RandomNumberGenerator.h"
#include "ColorPicker.h"

#include "ECSManager.h"
#include "CircleMoveSystem.h"
#include "RenderSystem.h"
#include "CircleComponents.h"

#include "StatsEntity.h"

int main()
{
    const unsigned int windowWidth = 1024;
    const unsigned int windowHeight = 768;
    const unsigned int numEntities = 100000;
    const sf::Rect<float> bounds(0.f, 0.f, windowWidth, windowHeight);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ECS Moving Circles");

    ECSManager manager;
    manager.addSystem<CircleMoveSystem>();
    manager.addSystem<RenderSystem>(&window);

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

        // Create the entity and components
        auto entity = manager.createEntity();

        auto& transform = manager.addComponent<TransformComponent>(entity);
        transform.position = position;
        transform.velocity = velocity;

        auto& radiusComponent = manager.addComponent<RadiusComponent>(entity);
        radiusComponent.radius = radius;

        auto& colorComponent = manager.addComponent<ColorComponent>(entity);
        colorComponent.color = color;

        auto& boundsComponent = manager.addComponent<BoundsComponent>(entity);
        boundsComponent.bounds = {
            std::make_pair(sf::Vector2f(0.f, 1.f), bounds.top),
            std::make_pair(sf::Vector2f(-1.f, 0.f), bounds.left + bounds.width),
            std::make_pair(sf::Vector2f(0.f, -1.f), bounds.top + bounds.height),
            std::make_pair(sf::Vector2f(1.f, 0.f), bounds.left)
        };
    }

    // TODO: adapt StatsEntity to ECS
    auto stats = new StatsEntity();

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
        stats->update(dt);
        stats->draw(window);

        window.display();
    }

    delete stats;

    /*std::vector<Entity*> entities;

    for (unsigned int i = 0; i < numEntities; ++i)
    {
        auto entity = CircleEntityGenerator::generateInBounds(bounds);
        entities.push_back(entity);
    }

    auto stats = new StatsEntity();
    entities.push_back(stats);
	
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

        for (auto entity : entities)
        {
            entity->update(dt);
        }

        window.clear();

        for (auto entity : entities)
        {
            entity->draw(window);
        }
    	
        window.display();
    }

    for (auto entity : entities)
    {
        delete entity;
    }
    entities.clear();*/

    return 0;
}
