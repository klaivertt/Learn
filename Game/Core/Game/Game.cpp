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
	player.Load();
	timeBar.Load();

	text.Create(FontType::BOLD, Vec2(0.5f), sf::Color::White, 32);
	text.SetString(std::to_string(player.GetScore()));
	text.SetPosition(data->screen.width / 2, 100.f);

	Logger::Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{

	if (!player.isDead)
	{
		player.Update(_dt);
		timeBar.Update(_dt);
	}

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
	case sf::Keyboard::D:
		CutTree(-1);
		break;
	case sf::Keyboard::Q:
		CutTree(1);
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

	for (int i = 0; i < MAX_TRUNKS; i++)
	{
		trunk[i].Draw(&_window);
	}
	player.Draw(_window);
	timeBar.Draw(_window);
	text.Draw(_window);

	data->debugViewer.Draw(_window);
}

void Game::LoadTrunk(void)
{
	stump.SetTexture(SPRITE_PATH + std::string("Stump.png"));
	stump.SetOrigin(Vec2(0.5f, 1.f));

	Vec2 stumpPos = Vec2(data->screen.width / 2, data->screen.height - 40.f);
	stump.SetPosition(stumpPos);


	trunkTexture[static_cast<int>(LogType::RIGHT)] = *data->assets.GetTexture(SPRITE_PATH + std::string("BranchRight.png"));
	trunkTexture[static_cast<int>(LogType::LEFT)] = *data->assets.GetTexture(SPRITE_PATH + std::string("BranchLeft.png"));
	trunkTexture[static_cast<int>(LogType::NORMAL)] = *data->assets.GetTexture(SPRITE_PATH + std::string("Trunk1.png"));
	trunkTexture[static_cast<int>(LogType::VAR)] = *data->assets.GetTexture(SPRITE_PATH + std::string("Trunk2.png"));

	Vec2 stumpSize = stump.GetTexture()->getSize();
	Vec2 logSize = trunkTexture[static_cast<int>(LogType::NORMAL)].getSize();
	for (int i = 0; i < MAX_TRUNKS; i++)
	{
		trunk[i].SetTexture(&trunkTexture[static_cast<int>(LogType::NORMAL)]);
		trunk[i].SetOrigin(Vec2(0.5f, 1.f));

		trunk[i].SetPosition(stumpPos - Vec2(0.f, (stumpSize.y + logSize.y * i)));
	}
}

void Game::ReplaceTrunk(void)
{
	sf::Texture* texture;

	for (int i = 0; i < MAX_TRUNKS - 1; i++)
	{
		texture = trunk[i + 1].GetTexture();
		trunk[i].SetTexture(texture);
	}

	unsigned int randTexture = 0;
	if (texture == &trunkTexture[static_cast<int>(LogType::RIGHT)] || texture == &trunkTexture[static_cast<int>(LogType::LEFT)])
	{
		randTexture = rand() % 2;
	}
	else
	{
		randTexture = rand() % 4;
	}

	switch (randTexture)
	{
	case 0:
		texture = &trunkTexture[static_cast<int>(LogType::NORMAL)];
		break;
	case 1:
		texture = &trunkTexture[static_cast<int>(LogType::VAR)];
		break;
	case 2:
		texture = &trunkTexture[static_cast<int>(LogType::LEFT)];
		break;
	case 3:
		texture = &trunkTexture[static_cast<int>(LogType::RIGHT)];
		break;
	default:
		break;
	}

	trunk[MAX_TRUNKS - 1].SetTexture(texture);

}

void Game::CutTree(int _dir)
{
	if (!player.isDead)
	{
		player.ChangeDir(_dir);
		TestCollision();
		ReplaceTrunk();
		timeBar.AddTime(TIME_ADD);
		player.Cut();
		TestCollision();
		player.AddScore(1);
		text.SetString(std::to_string(player.GetScore()));
	}
}

void Game::TestCollision()
{
	if (trunk[0].GetTexture() == &trunkTexture[static_cast<int>(LogType::RIGHT)] && player.dir == -1)
	{
		player.isDead = true;
	}

	if (trunk[0].GetTexture() == &trunkTexture[static_cast<int>(LogType::LEFT)] && player.dir == 1)
	{
		player.isDead = true;
	}

	//Logger::Log(Logger::Bool("isDead : ", player.isDead));
}

void TimeBar::Load(void)
{
	bar.SetTexture(SPRITE_PATH + std::string("TimeBar.png"));
	barBack.SetTexture(SPRITE_PATH + std::string("TimeContainer.png"));
	size = bar.GetTexture()->getSize();

	bar.SetOrigin(Vec2(0.f, 0.5f));
	barBack.SetOrigin(Vec2(0.f, 0.5f));

	GameData* data = GameData::GetInstance();

	Vec2 pos = Vec2((data->screen.width / 2 - size.x / 2), 40.f);
	bar.SetPosition(pos + Vec2(16.f, 0));
	barBack.SetPosition(pos);
}

void TimeBar::Update(float _dt)
{
	time -= _dt;
	if (time > 0.f)
	{
		bar.SetTextureRect(sf::IntRect(0, 0, size.x * time / MAX_TIME, size.y));
	}
	else
	{
		time = 0.f;
	}
}

void TimeBar::Draw(sf::RenderTarget& _target)
{
	barBack.Draw(&_target);
	bar.Draw(&_target);
}

void TimeBar::AddTime(float _time)
{
	time += _time;
	if (time > MAX_TIME)
	{
		time = MAX_TIME;
	}
}

void Player::Load()
{
	state = IDLE;
	sprite.SetTexture(SPRITE_PATH + std::string("Man.png"));
	sprite.SetOrigin(Vec2(0.25f, 1.f));
	sf::IntRect firstFrame = GetFirstFrame(*sprite.GetTexture(), Vec2(4, 1), Vec2(0, 0));
	cut.Create(&sprite.sprite, 2, 20, AnimType::LOOP_ONCE, AnimDirection::HORIZONTAL, firstFrame);
	firstFrame = GetFirstFrame(*sprite.GetTexture(), Vec2(4, 1), Vec2(2, 0));
	idle.Create(&sprite.sprite, 2, 6, AnimType::LOOP, AnimDirection::HORIZONTAL, firstFrame);

	data = GameData::GetInstance();
	Vec2 pos = Vec2((data->screen.width / 2), data->screen.height - 40.f);
	sprite.SetPosition(pos);

	tombStone.SetTexture(SPRITE_PATH + std::string("RIP.png"));
	tombStone.SetPosition(pos);
	tombStone.SetOrigin(Vec2(0.5f, 1.f));
}

void Player::Update(float _dt)
{
	Animation& current = (state == State::CUT) ? cut : idle;
	current.Update(_dt);

	if (current.isFinished)
	{
		state = IDLE;
	}
}

void Player::Draw(sf::RenderTarget& _target)
{
	if (isDead)
	{
		tombStone.Draw(&_target);
	}
	else
	{
		sprite.Draw(&_target);
	}
}

void Player::ChangeDir(int _dir)
{
	dir = _dir;
	sprite.SetScale(Vec2(dir, 1));
	Vec2 pos = Vec2((data->screen.width / 2 + (180.f * -dir)), data->screen.height - 40.f);
	tombStone.SetPosition(pos);
}

void Player::Cut()
{
	state = CUT;
	cut.Reset();
}

void Player::AddScore(int _score)
{
	score += _score;
}

int Player::GetScore(void)
{
	return score;
}
