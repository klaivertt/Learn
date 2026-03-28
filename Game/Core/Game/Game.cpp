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

	Logger::Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	data->debugViewer.Update(_dt);
}

void Game::HandleEvents(sf::RenderWindow& _window)
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed(event.key, _window);
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed(event.mouseButton, _window);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved(event.mouseMove, _window);
		}
	}
}

void Game::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	switch (_key.code)
	{
	case sf::Keyboard::F1:
		data->debugViewer.ToggleFPS();
		break;
	case sf::Keyboard::Escape:
		ChangeScene(new Menu());
		break;
	default:
		break;
	}
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

void Snake::Load(void)
{
}

void Snake::ChangeDir(Direction _dir)
{
}

void Snake::CreateNewRectangle(void)
{
	sf::RectangleShape newRect;
	if (shapes.size() == 0)
	{
		newRect.setSize(Vec2(HEAD_SIZE));
	}
	else
	{
		newRect.setSize(Vec2(TAILS_SIZE))
	}
	shapes.push_back(newRect);
}

void Snake::ClampSizeBetweenHeadAndTails(void)
{
}
