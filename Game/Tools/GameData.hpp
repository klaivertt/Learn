#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Common.h"

struct Screen
{
	std::string name = {};
	int width = 0;
	int height =0;
	bool fullscreen = false;
	int maxFps = 60;
	bool vSync = true;
	std::string iconPath = {};
	bool isDebugMode = false;
};

class DebugViewer;
class Scene;
class AssetManager;

class GameData
{
protected:
	GameData(void) {};
	~GameData(void) {};

	static GameData* instance;
public:
	static GameData* GetInstance(void);
public:
	// Debug System
	DebugViewer* debugViewer = nullptr;

	// Common Font
	sf::Font font;

	AssetManager* assetManager = nullptr;

	Scene* currentScene = nullptr;

	Screen screen;

	sf::RenderWindow window;

	b2DebugDraw debugDraw = { 0 };
	sf::Vector2f cam;
};

#endif // !GAME_DATA_H