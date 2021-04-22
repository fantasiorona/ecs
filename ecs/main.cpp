#include <SFML/Graphics.hpp>

#include "CircleEntityGenerator.h"
#include "StatsEntity.h"

int main()
{
    const unsigned int windowWidth = 1024;
    const unsigned int windowHeight = 768;
    const unsigned int numEntities = 100000;
    const sf::Rect<float> bounds(0.f, 0.f, windowWidth, windowHeight);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ECS Moving Circles");

    std::vector<Entity*> entities;

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
    entities.clear();

    return 0;
}
