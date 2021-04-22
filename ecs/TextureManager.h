#pragma once

#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	};

	const sf::Texture& getCircleTexture() const { return _circleTexture;  };

private:
	TextureManager();

	sf::Texture _circleTexture;
};

