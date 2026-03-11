#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager(void)
{
	for (auto& texture : textures)
	{
		texture.second.~Texture();
	}
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
	if (textures.find(name) == textures.end())
	{
		sf::Texture texture;
		if (texture.loadFromFile(name))
		{
			textures[name] = texture;
		}
		else
		{
			std::cerr << "Error: Could not load texture: " << name << std::endl;
		}
	}
	return textures[name];
}
