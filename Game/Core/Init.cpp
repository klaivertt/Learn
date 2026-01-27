#include "Init.h"
#include "../Tools/Debug/DebugViewer.h"
#include "../Tools/Debug/Logger.h"
#include "../Tools/GameData.h"
#include "../Core/Menu/Menu.h"
#include "../Core/Game/Game.h"
#include "../Tools/AssetManager.h"
#include "../Tools/Debug/SFMLDebugDraw.h"

// Forward declarations
void LoadRenderWindow(sf::RenderWindow& _render, Screen _screen, Logger* _log);
//void LoadParticleSystem(GameData& _data);
Screen WindowInitFile(std::string _path, Logger* _log);
//////////////////////////////////////

void Init(GameData* _data)
{
	_data->logger = new Logger();
	_data->logger->SetLogLevel(LogLevel::NO_PRINT);
	Screen newScreen = WindowInitFile("config.ini", _data->logger);
	LoadRenderWindow(_data->window, newScreen, _data->logger);

	_data->screen = newScreen;

	_data->assetManager = new AssetManager();

	//_renderWindow->setIcon(32, 32, sf::Image().loadFromFile(newScreen.iconPath).getPixelsPtr());

	_data->font.loadFromFile("Assets/poppins.ttf");

	_data->debugViewer = new DebugViewer();
	_data->debugViewer->Init(_data->font);
	srand((unsigned int)(time(NULL)));

	_data->currentScene = new Game();
	//_data->currentScene->Load();
	//Configuration affichage de debug
	_data->debugDraw.context = (void*)_data; //Pointeur qui permet aux fonctions de dessin de SFMLDebugDraw d'accéder au gameData parce que besoin de divers infos dedans
	_data->debugDraw.DrawPointFcn = &DebugDrawPoint;
	_data->debugDraw.DrawPolygonFcn = &DebugDrawPolygon;
	_data->debugDraw.DrawSolidPolygonFcn = &DebugDrawSolidPolygon;
	_data->debugDraw.DrawCircleFcn = &DebugDrawCircle;
	_data->debugDraw.DrawSolidCircleFcn = &DebugDrawSolidCircle;
	_data->debugDraw.DrawSegmentFcn = &DebugDrawSegment;
	_data->debugDraw.DrawTransformFcn = &DebugDrawTransform;
	_data->debugDraw.DrawStringFcn = &DebugDrawString;
	_data->debugDraw.drawJoints = true; //Dessine les joints
	_data->debugDraw.drawShapes = true; //Dessine les colliders
	_data->debugDraw.drawMass = true; //Dessine les centres de gravité des bodies
}

void LoadRenderWindow(sf::RenderWindow& _render, Screen _screen, Logger* _log)
{
	_render.create(sf::VideoMode(_screen.width, _screen.height), _screen.name,
		_screen.fullscreen ? sf::Style::None : sf::Style::Default);
	if (!_render.isOpen())
	{
		_log->Error("Failed to create render window!", true);
	}
	else
	{
		_log->Success("Render window created successfully.", true);
	}

	_render.setFramerateLimit(_screen.maxFps);
	if (_screen.maxFps > 0)
	{
		_log->Success("Max FPS set to: " + std::to_string(_screen.maxFps), true);
	}
	else
	{
		_log->Warning("Max FPS is set to 0 or less, which may cause high CPU usage.", true);
	}
	_render.setVerticalSyncEnabled(_screen.vSync);
	if (_screen.vSync)
	{
		_log->Success("V-Sync enabled.", true);
	}
	else
	{
		_log->Warning("V-Sync disabled.", true);
	}
}

Screen WindowInitFile(std::string _path, Logger* _log)
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
			_log->Success("Loaded resolution: " + std::to_string(w) + "x" + std::to_string(h), true);
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
			_log->Success("Loaded window title: " + title, true);
		}
		else if (tempString == "FULLSCREEN")
		{
			bool fullscreen;
			file >> fullscreen;
			tempScreen.fullscreen = fullscreen;
			_log->Success("Loaded fullscreen: " + std::to_string(fullscreen), true);
		}
		else if (tempString == "MAX_FPS")
		{
			int maxFps;
			file >> maxFps;
			tempScreen.maxFps = maxFps;
			_log->Success("Loaded max fps: " + std::to_string(maxFps), true);
		}
		else if (tempString == "V_SYNC")
		{
			bool vs;
			file >> vs;
			tempScreen.vSync = vs;
			_log->Success("Loaded vsync: " + std::to_string(vs), true);
		}
		else if (tempString == "WINDOW_ICON")
		{
			std::string iconPath;
			file >> iconPath;
			tempScreen.iconPath = iconPath;
			_log->Success("Loaded icon path: " + iconPath, true);
		}
		else if (tempString == "DEBUG_MODE")
		{
			bool isDebug;
			file >> isDebug;
			tempScreen.isDebugMode = isDebug;
			_log->Success("Loaded debug mode: " + std::to_string(isDebug), true);
		}
		else
		{
			_log->Warning("Unknown config key: " + tempString, true);
		}
	}
	file.close();
	return tempScreen;
}