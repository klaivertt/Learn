#include "Game.h"
#include "../../Tools/GameData.h"
#include "../../Tools/Debug/DebugViewer.h"
#include "../../Tools/Debug/Logger.h"
#include "../../Tools/Debug/SFMLDebugDraw.h"
#include "../../Core/Menu/Menu.h"


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
		sf::Vector2f randPos = sf::Vector2f(RandF(0, data->screen.width), RandF(0, data->screen.height));
		rabits.push_back(new Rabbit(randPos)); 
		
		for (int i = 0; i < NB_FOOD_BY_RABBITS; i++)
		{
			sf::Vector2f randPos = sf::Vector2f(RandF(0, data->screen.width), RandF(0, data->screen.height));
			foods.push_back(new Food(randPos, RandF(FOOD_MIN_NUTRITION, FOOD_MAX_NUTRITION)));
		}
	}

	data->logger->Success("Game Scene Loaded.", true);
}

void Game::Update(float _dt, sf::RenderWindow& _window)
{
	MoveCamera(_dt);

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


	data->debugViewer->Draw(_window);
}

void Game::MoveCamera(float _dt)
{
	float pixelsToMeters = 1.f / ZOOM;

	data->cam.x += (0 - data->cam.x);
	data->cam.y += (0 - data->cam.y);
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
	sf::FloatRect rabbitBound = _rabbit.GetBound();
	sf::FloatRect foodBound = _food.GetBound();

	if (rabbitBound.intersects(foodBound))
	{
		_rabbit.SetEnergie(_food.GetNutritionValue());
	}
}

#pragma region Rabbit

void Rabbit::UpdateDisplayBar()
{
	sf::Vector2f pos = shape.getPosition();

	pos.y -= 35.f;

	backDisplayBar.setPosition(pos);
	displayBar.setPosition(pos);

	float width = backDisplayBar.getLocalBounds().width * (energy / MAX_ENERGY);

	displayBar.setSize({ width, backDisplayBar.getLocalBounds().height });
}

Rabbit::Rabbit(sf::Vector2f _startPos)
{
	shape.setRadius(20.f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(_startPos);
	shape.setOrigin({ 20,20 });
	energy = 100.f;
	velocity = sf::Vector2f(RandF(-1, 1), RandF(-1, 1));


	sf::Vector2f size = sf::Vector2f(50, 10);
	backDisplayBar.setSize(size);
	backDisplayBar.setOrigin({ size.x / 2, size.y / 2 });
	backDisplayBar.setFillColor(sf::Color(50, 50, 50));

	displayBar.setSize(size);
	displayBar.setOrigin({ size.x / 2, size.y / 2 });
	displayBar.setFillColor(sf::Color(170, 200, 50));
}

Rabbit::~Rabbit()
{
}

void Rabbit::Update(float _dt)
{
	shape.move(velocity);
	energy -= ENERGY_REMOVE * _dt;

	if (energy < 30)
	{
		shape.setFillColor(sf::Color::Red);
	}

	UpdateDisplayBar();
}

void Rabbit::Draw(sf::RenderWindow& _render)
{
	_render.draw(shape);

	_render.draw(backDisplayBar);
	_render.draw(displayBar);
}

bool Rabbit::IsDead(void)
{
	return energy <= 0;
}

void Rabbit::SetVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}

void Rabbit::SetEnergie(float _amount)
{
	energy += _amount;
	if (energy >= MAX_ENERGY)
	{
		energy = MAX_ENERGY;
	}
}

sf::Vector2f Rabbit::GetVelocity(void)
{
	return velocity;
}

sf::Vector2f Rabbit::GetPos(void)
{
	return shape.getPosition();
}

sf::FloatRect Rabbit::GetBound(void)
{
	return shape.getGlobalBounds();
}

#pragma endregion

#pragma region Food
Food::Food(sf::Vector2f _pos, float _nutrition)
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color(75, 120, 75));
	shape.setPosition(_pos);
	nutrition = _nutrition;
}

Food::~Food()
{
}

void Food::Draw(sf::RenderWindow& _render)
{
	_render.draw(shape);
}

sf::Vector2f Food::GetPos(void)
{
	return shape.getPosition();
}

sf::FloatRect Food::GetBound(void)
{
	return shape.getGlobalBounds();
}
float Food::GetNutritionValue(void)
{
	if (!eated)
	{
		eated = true;
		return nutrition;
	}
	return 0.0f;
}
bool Food::GetEated(void)
{
	return eated;
}
#pragma endregion