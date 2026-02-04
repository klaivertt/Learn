#include "Game.h"
#include "../../Tools/GameData.h"
#include "../../Tools/Debug/DebugViewer.h"
#include "../../Tools/Debug/Logger.h"
#include "../../Tools/Debug/SFMLDebugDraw.h"
#include "../../Core/Menu/Menu.h"
#include "Food.h"
#include "Rabbit.h"
#include "DayNightCycle.h"


Game::Game()
{
	Load();
}

Game::~Game()
{
	// cleanup
	background.getTexture()->~Texture();
	data->logger->Info("Game Scene Unloaded.", false);
}

void Game::Load()
{
	// Game Data singleton
	data = GameData::GetInstance();

	//Sprites
	background = LoadSprite("Assets/background.png", { 0.0f, 0.0f });

	for (int i = 0; i < NB_OF_RABBITS; i++)
	{

		for (int i = 0; i < NB_FOOD_BY_RABBITS; i++)
		{
			sf::Vector2f randPos = sf::Vector2f(RandF(0, data->screen.width), RandF(0, data->screen.height));
			foods.push_back(new Food(randPos, RandF(FOOD_MIN_NUTRITION, FOOD_MAX_NUTRITION)));
		}
		sf::Vector2f randPos = sf::Vector2f(RandF(0, data->screen.width), RandF(0, data->screen.height));
		rabits.push_back(new Rabbit(randPos, &foods, &rabits));
	}

	dayCycle = new DayNightCycle(data->screen.width, data->screen.height);
	dayCount = CreateText("Day : 0", data->font, 20, Anchor::TOP_RIGHT);

	data->logger->Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	MoveCamera(_dt);

	dayCycle->Update(_dt);
	if (dayCycle->GetIsNewDay())
	{
		SpawnFood();
		ResetRabbitBread();
		SetText(dayCount, "Day : " + std::to_string(dayCycle->GetDayCount()));
	}

	for (int i = rabits.size() - 1; i >= 0; i--)
	{
		rabits[i]->Update(_dt);
		CheckRabbitColideWithMap(*rabits[i]);

		for (int j = foods.size() - 1; j >= 0; j--)
		{
			CheckRabbitColideWithFood(*rabits[i], *foods[j]);

			if (foods[j]->GetEated())
			{
				delete foods[j];
				foods.erase(foods.begin() + j);
			}
		}

		if (rabits[i]->IsDead())
		{
			delete rabits[i];
			rabits.erase(rabits.begin() + i);
		}
	}

	//data->logger->Log(LogLevel::WARNING, data->logger->Vec2(playerWorldPos, "player pos"), false);
}

void Game::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	if (_key.code == sf::Keyboard::F1)
	{
		data->debugViewer->ToggleFPS();
		data->screen.isDebugMode = !data->screen.isDebugMode;
	}

	if (_key.code == sf::Keyboard::Escape)
	{
		data->currentScene = new Menu();
		delete this;
	}

	if (_key.code == sf::Keyboard::Space)
	{
		if (isGameOver)
		{
			data->currentScene = new Game();
			delete this;
		}
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
	//Draw Ground
	_window.draw(background);

	for (int i = 0; i < foods.size(); i++)
	{
		foods[i]->Draw(_window);
	}

	for (int i = 0; i < rabits.size(); i++)
	{
		rabits[i]->Draw(_window);
	}

	dayCycle->Draw(_window);

	_window.draw(dayCount);


	data->debugViewer->Draw(_window);
}

void Game::MoveCamera(float _dt)
{
	float pixelsToMeters = 1.f / ZOOM;

	data->cam.x += (0 - data->cam.x);
	data->cam.y += (0 - data->cam.y);
}

void Game::ResetRabbitBread(void)
{
	for (int i = 0; i < rabits.size(); i++)
	{
		rabits[i]->SetBreadable(true);
	}
}

void Game::CheckRabbitColideWithMap(Rabbit& _rabbit)
{
	sf::Vector2f pos = _rabbit.GetPos();

	if (pos.x < 0 || pos.x > data->screen.width)
	{
		sf::Vector2f velocity = _rabbit.GetVelocity();
		_rabbit.SetVelocity({ velocity.x * -1,velocity.y });
	}
	if (pos.y < 0 || pos.y > data->screen.height)
	{
		sf::Vector2f velocity = _rabbit.GetVelocity();
		_rabbit.SetVelocity({ velocity.x,velocity.y * -1 });
	}
}

void Game::CheckRabbitColideWithFood(Rabbit& _rabbit, Food& _food)
{
	if (_rabbit.GetHungry())
	{
		sf::FloatRect rabbitBound = _rabbit.GetBound();
		sf::FloatRect foodBound = _food.GetBound();


		if (rabbitBound.intersects(foodBound))
		{
			_rabbit.SetEnergie(_food.GetNutritionValue());
		}
	}
}

void Game::SpawnFood(void)
{
	int nbFood = RandI(rabits.size() * MIN_FOOD_DAY, rabits.size() * MAX_FOOD_DAY);
	for (int i = 0; i < nbFood; i++)
	{
		sf::Vector2f randPos = sf::Vector2f(RandF(0, data->screen.width), RandF(0, data->screen.height));
		foods.push_back(new Food(randPos, RandF(FOOD_MIN_NUTRITION, FOOD_MAX_NUTRITION)));

		if (foods.size() > (rabits.size() * 0.75f) * MAX_FOOD_DAY * 2)
		{
			return;
		}
	}
}