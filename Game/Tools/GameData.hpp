#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Common.hpp"
#include "Tools/Debug/DebugViewer.hpp"
#include "Tools/AssetsManager.hpp"
#include "Tools/Miscellaneous/Text.hpp"

struct Screen
{
	std::string name = "";
	int width = 0;
	int height =0;
	bool fullscreen = false;
	int maxFps = 60;
	bool vSync = true;
	std::string iconPath = "";
	bool isDebugMode = false;
};

class Debug::DebugViewer;
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
	Debug::DebugViewer debugViewer;
	AssetsManager assets;
	// Common Font
	sf::Font font;

	Scene* currentScene = nullptr;

	Screen screen;

	sf::RenderWindow window;

	b2DebugDraw debugDraw = { 0 };
	sf::Vector2f cam;
};

#endif // !GAME_DATA_H