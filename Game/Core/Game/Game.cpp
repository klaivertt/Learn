#include "Game.hpp"
#include "Tools/GameData.hpp"
#include "Tools/Debug/DebugViewer.hpp"
#include "Tools/Debug/Logger.hpp"
#include "Tools/Debug/SFMLDebugDraw.h"
#include "../Menu/Menu.hpp"


Game::Game()
{
	Load();
}

Game::~Game()
{
	Logger::Info("Game Scene Unloaded.", false);
}

void Game::Load()
{
	// Game Data singleton
	data = GameData::GetInstance();

	LoadMainFiles("Assets/persos.txt");

	Logger::Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	
}

void Game::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	
}

void Game::MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window)
{
}

void Game::MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window)
{
}

void Game::Draw(sf::RenderWindow& _window)
{	
	data->debugViewer.Draw(_window);
}

void Game::LoadMainFiles(const std::string _files)
{
	// open file and read Files to load characters

	std::ifstream file(_files);
	if (!file.is_open())
	{
		Logger::Error("Failed to open file: " + _files, true);
		return;
	}

	std::vector<std::string> characterFiles;

	while (file.is_open() && !file.eof())
	{
		std::string line;
		std::getline(file, line);
		// Skip empty lines and comments
		if ( line != "" && line[0] != '#' )
		{
			// file path and extention are extracted
			characterFiles.push_back(line);
			Logger::Info("File to load: " + line, true);
		}
	}

	for (const std::string& characterFile : characterFiles)
	{
		LoadCharacters(characterFile);
	}

}

void Game::LoadCharacters(const std::string _files)
{

}
