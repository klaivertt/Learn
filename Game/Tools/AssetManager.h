#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Common.h"


class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	sf::Texture& GetTexture(const std::string& name);
private:
	std::map<std::string, sf::Texture> textures;
};



#endif // !ASSET_MANAGER_H
