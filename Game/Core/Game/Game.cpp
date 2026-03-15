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

	background.SetTexture(SPRITE_PATH + std::string("Background.png"));
	LoadTrunk();
	timeBar.Load();

	Logger::Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	timeBar.Update(_dt);

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
	background.Draw(&_window);

	stump.Draw(&_window);

	for (int i = 0; i < MAX_TRUNC; i++)
	{
		trunk[i].Draw(&_window);
	}

	timeBar.Draw(_window);

	data->debugViewer.Draw(_window);
}

void Game::LoadTrunk(void)
{
	stump.SetTexture(SPRITE_PATH + std::string("Stump.png"));
	stump.SetOrigin(Vec2(0.5f, 1.f));

	Vec2 stumpPos = Vec2(data->screen.width / 2, data->screen.height - 40.f);
	stump.SetPosition(stumpPos);


	trunkTexture[static_cast<int>(LogTyppe::RIGHT)] = *data->assets.GetTexture(SPRITE_PATH + std::string("BranchRight.png"));
	trunkTexture[static_cast<int>(LogTyppe::LEFT)] = *data->assets.GetTexture(SPRITE_PATH + std::string("BranchLeft.png"));
	trunkTexture[static_cast<int>(LogTyppe::NORMAL)] = *data->assets.GetTexture(SPRITE_PATH + std::string("Trunk1.png"));
	trunkTexture[static_cast<int>(LogTyppe::VAR)] = *data->assets.GetTexture(SPRITE_PATH + std::string("Trunk2.png"));

	Vec2 stumpSize = stump.GetTexture()->getSize();
	Vec2 logSize = trunkTexture[static_cast<int>(LogTyppe::NORMAL)].getSize();
	for (int i = 0; i < MAX_TRUNC; i++)
	{
		trunk[i].SetTexture(&trunkTexture[static_cast<int>(LogTyppe::NORMAL)]);
		trunk[i].SetOrigin(Vec2(0.5f, 1.f));

		trunk[i].SetPosition(stumpPos - Vec2(0.f, (stumpSize.y + logSize.y * i)));
	}
}

void TimeBar::Load(void)
{
	bar.SetTexture(SPRITE_PATH + std::string("TimeBar.png"));
	barBack.SetTexture(SPRITE_PATH + std::string("TimeContainer.png"));
	size = bar.GetTexture()->getSize();

	bar.SetOrigin(Vec2(0.f,0.5f));
	barBack.SetOrigin(Vec2(0.f, 0.5f));

	GameData* data = GameData::GetInstance();

	Vec2 pos = Vec2((data->screen.width / 2 - size.x / 2), 40.f);
	bar.SetPosition(pos + Vec2(10.f,0));
	barBack.SetPosition(pos);

}

void TimeBar::Update(float _dt)
{

	time -= _dt;
	bar.SetTextureRect(sf::IntRect(0,0, size.x * time/MAX_TIME, size.y));
}

void TimeBar::Draw(sf::RenderTarget& _target)
{
	barBack.Draw(&_target);
	bar.Draw(&_target);
}

void TimeBar::AddTime(float _time)
{
	time += _time;
}
