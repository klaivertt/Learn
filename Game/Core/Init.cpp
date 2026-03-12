#include "Init.hpp"
#include "Tools/Debug/DebugViewer.hpp"
#include "Tools/Debug/Logger.hpp"
#include "Tools/GameData.hpp"
#include "Core/Menu/Menu.hpp"
#include "Core/Game/Game.hpp"
#include "Tools/Debug/SFMLDebugDraw.h"

// Forward declarations
void LoadRenderWindow(sf::RenderWindow& _render, Screen& _screen);
//void LoadParticleSystem(GameData& _data);
Screen WindowInitFile(const std::string& _path);
//////////////////////////////////////

void Init(GameData& _data)
{
	Logger::SetLogLevel(LogLevel::DEBUG);
	Screen newScreen = WindowInitFile(static_cast<std::string>("config.ini"));
	LoadRenderWindow(_data.window, newScreen);

	_data.screen = newScreen;

	//_renderWindow->setIcon(32, 32, sf::Image().loadFromFile(newScreen.iconPath).getPixelsPtr());

	srand((unsigned int)(time(NULL)));

	_data.currentScene = new Game();
	//_data->currentScene->Load();
	//Configuration affichage de debug
	_data.debugDraw.context = (void*)&_data; //Pointeur qui permet aux fonctions de dessin de SFMLDebugDraw d'accéder au gameData parce que besoin de divers infos dedans
	_data.debugDraw.DrawPointFcn = &DebugDrawPoint;
	_data.debugDraw.DrawPolygonFcn = &DebugDrawPolygon;
	_data.debugDraw.DrawSolidPolygonFcn = &DebugDrawSolidPolygon;
	_data.debugDraw.DrawCircleFcn = &DebugDrawCircle;
	_data.debugDraw.DrawSolidCircleFcn = &DebugDrawSolidCircle;
	_data.debugDraw.DrawSegmentFcn = &DebugDrawSegment;
	_data.debugDraw.DrawTransformFcn = &DebugDrawTransform;
	_data.debugDraw.DrawStringFcn = &DebugDrawString;
	_data.debugDraw.drawJoints = true; //Dessine les joints
	_data.debugDraw.drawShapes = true; //Dessine les colliders
	_data.debugDraw.drawMass = true; //Dessine les centres de gravité des bodies
}

void LoadRenderWindow( sf::RenderWindow& _render, Screen& _screen)
{
	_render.create(sf::VideoMode(_screen.width, _screen.height), _screen.name,
		_screen.fullscreen ? sf::Style::None : sf::Style::Default);
	if (!_render.isOpen())
	{
		Logger::Error("Failed to create render window!", true);
	}
	else
	{
		Logger::Success("Render window created successfully.", true);
	}

	_render.setFramerateLimit(_screen.maxFps);
	if (_screen.maxFps > 0)
	{
		Logger::Success("Max FPS set to: " + std::to_string(_screen.maxFps), true);
	}
	else
	{
		Logger::Warning("Max FPS is set to 0 or less, which may cause high CPU usage.", true);
	}
	_render.setVerticalSyncEnabled(_screen.vSync);
	if (_screen.vSync)
	{
		Logger::Success("V-Sync enabled.", true);
	}
	else
	{
		Logger::Warning("V-Sync disabled.", true);
	}
}

Screen WindowInitFile(const std::string& _path)
{
	// read config file for window settings (if exists)
	Screen tempScreen = Screen("Screen Name", 1920, 1080, false, 60, true, "");

	std::fstream file(_path, std::ios::in);
	while (!file.eof())
	{
		std::string tempString;
		file >> tempString;
		if (tempString == "RESOLUTION")
		{
			int w, h;
			file >> w >> h;
			tempScreen.width = w;
			tempScreen.height = h;
			Logger::Success("Loaded resolution: " + std::to_string(w) + "x" + std::to_string(h), true);
		}
		else if (tempString == "TITLE")
		{
			std::string title;
			file >> title;
			// Remove the _ characters and replace them with spaces
			for (char& c : title)
			{
				if (c == '_')
				{
					c = ' ';
				}
			}
			tempScreen.name = title;
			Logger::Success("Loaded window title: " + title, true);
		}
		else if (tempString == "FULLSCREEN")
		{
			bool fullscreen;
			file >> fullscreen;
			tempScreen.fullscreen = fullscreen;
			Logger::Success("Loaded fullscreen: " + std::to_string(fullscreen), true);
		}
		else if (tempString == "MAX_FPS")
		{
			int maxFps;
			file >> maxFps;
			tempScreen.maxFps = maxFps;
			Logger::Success("Loaded max fps: " + std::to_string(maxFps), true);
		}
		else if (tempString == "V_SYNC")
		{
			bool vs;
			file >> vs;
			tempScreen.vSync = vs;
			Logger::Success("Loaded vsync: " + std::to_string(vs), true);
		}
		else if (tempString == "WINDOW_ICON")
		{
			std::string iconPath;
			file >> iconPath;
			tempScreen.iconPath = iconPath;
			Logger::Success("Loaded icon path: " + iconPath, true);
		}
		else if (tempString == "DEBUG_MODE")
		{
			bool isDebug;
			file >> isDebug;
			tempScreen.isDebugMode = isDebug;
			Logger::Success("Loaded debug mode: " + std::to_string(isDebug), true);
		}
		else
		{
			Logger::Warning("Unknown config key: " + tempString, true);
		}
	}
	file.close();
	return tempScreen;
}