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

	background.SetTexture("Assets/background.png");
	LoadPaddle();
	LoadBall();

	scoreText.Create(FontType::BOLD, Vec2(0.5f), sf::Color::White, 32);
	scoreText.SetPosition(Vec2(data->screen.width / 2, 30.f));
	scoreText.SetString("Score J1 : " + std::to_string(score[0]) + " || Score J2 : " + std::to_string(score[1]));

	Logger::Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	PlayerInput();
	UpdateBall(_dt);
	UpdatePlayer(_dt);
	CheckColision();
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

	for (int i = 0; i < 2; i++)
	{
		paddle[i].Draw(&_window);
	}

	ball.Draw(&_window);

	scoreText.Draw(_window);

	data->debugViewer.Draw(_window);
}

void Game::LoadPaddle(void)
{
	for (int i = 0; i < 2; i++)
	{
		paddle[i].SetTexture("Assets/Barre.png");
		paddle[i].SetPosition(Vec2((i == 0 ? 20.f : data->screen.width - 20.f), (data->screen.height / 2)));
		paddle[i].SetOrigin(Vec2(0.5f));
	}
}

void Game::LoadBall(void)
{
	ball.SetTexture("Assets/Balle.png");
	ball.SetPosition(Vec2(data->screen.width / 2, data->screen.height / 2));
	ball.SetOrigin(Vec2(0.5f));
	ballVelocity = Vec2((rand() % 2) * 2 - 1, (rand() % 2) * 2 - 1);
}

void Game::UpdateBall(float _dt)
{
	Vec2 dir = Vec2((BALL_SPEED * _dt) * ballVelocity);
	dir.Normalize();
	ball.Move(dir);
}

void Game::UpdatePlayer(float _dt)
{
	for (int i = 0; i < 2; i++)
	{
		Vec2 dir = Vec2(0);
		dir.y = playerDir[i] * PlAYER_SPEED * _dt;
		paddle[i].Move(dir);
		playerDir[i] = 0;
	}
}

void Game::CheckColision()
{
	for (int i = 0; i < 2; i++)
	{
		if (paddle[i].GetGlobalBounds().intersects(ball.GetGlobalBounds()))
		{
			ballVelocity.x *= -1;
		}
	}

	if (ball.GetPosition().x <= 5.f)
	{
		score[1]++;
		ResetBall();
		SetNewScore();
	}
	else if (ball.GetPosition().x >= data->screen.width - 5.f)
	{
		score[0]++;
		ResetBall();
		SetNewScore();
	}

	if (ball.GetPosition().y <= 5.f)
	{
		ballVelocity.y *= -1;
	}
	else if (ball.GetPosition().y >= data->screen.height - 5.f)
	{
		ballVelocity.y *= -1;
	}
}

void Game::ResetBall()
{
	ball.SetPosition(Vec2(data->screen.width / 2, data->screen.height / 2)); 
	ballVelocity = Vec2((rand() % 2) * 2 - 1, (rand() % 2) * 2 - 1);
}

void Game::SetNewScore()
{
	scoreText.SetString("Score J1 : " + std::to_string(score[0]) + " || Score J2 : " + std::to_string(score[1]));
}

void Game::PlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		playerDir[0] = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerDir[0] = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerDir[1] = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerDir[1] = 1;
	}
}
