#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager(): ResourceManager("textures.cfg"){}

	sf::Texture* load(const std::string& pPath)
	{
		auto texture = new sf::Texture();
		if(!texture->loadFromFile(Utils::getWorkingDirectory() + pPath))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "FAILED TO LOAD TEXTURE: " << pPath << std::endl;
		}
		return texture;
	}
};
