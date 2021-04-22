#include <cassert>

#include "TextureManager.h"

TextureManager::TextureManager()
{
	// load the texture, assume success
	const auto success = _circleTexture.loadFromFile("textures/circle.png");
	assert(success);
}

