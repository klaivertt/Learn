#include "Common.h"

// Game and Data 

#define MAX_BAR 2
#define MARGIN_BAR 30.f
#define BAR_SPEED 600.f
#define BALL_SPEED 400.f

struct GameData
{
	sf::Sprite background;
	sf::Texture bgTexture;
	sf::Sprite bar[MAX_BAR];
	sf::Sprite ball;
	sf::Texture barTexture;
	sf::Texture ballTexture;
	float barHeigth = 0.f;
	sf::Vector2f balldir = sf::Vector2f(0,0);
	int score1 = 0;
	int score2 = 0;
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

bool CheckCollisionRectRect(sf::FloatRect _rect1, sf::FloatRect _rect2);
void CheckPlayerInput(GameData& _data,float _dt);
void UpdateBall(GameData& _data, float _dt);
void ResetBall(GameData& _data);

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Template SFML");
	window.setFramerateLimit(100);

	GameData data;
	Init(data);

	sf::Clock deltaTime;
	while (window.isOpen())
	{
		float dt = deltaTime.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					Init(data);
				}
			}

		}

		Update(data, dt);
		Display(data, window);
	}
}



///////////////////////////////////////////////////////////////////
void Init(GameData& _data)
{
	_data.bgTexture.loadFromFile("pongbackground.png");
	_data.background.setTexture(_data.bgTexture);

	_data.barTexture.loadFromFile("Barre.png");

	sf::Vector2f size = sf::Vector2f(_data.barTexture.getSize());
	_data.barHeigth = size.y;
	for (size_t i = 0; i < MAX_BAR; i++)
	{
		_data.bar[i].setTexture(_data.barTexture);
		if (i == 1)
		{
			_data.bar[i].setScale(sf::Vector2f(-1, 1));
		}
		_data.bar[i].setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
		_data.bar[i].setPosition(i == 1 ? sf::Vector2f(SCREEN_WIDTH - MARGIN_BAR, SCREEN_HEIGHT / 2) : sf::Vector2f(MARGIN_BAR, SCREEN_HEIGHT / 2));
	}
	
	_data.ballTexture.loadFromFile("Ball.png");
	_data.ball.setTexture(_data.ballTexture);

	size = sf::Vector2f(_data.ballTexture.getSize());
	_data.ball.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	ResetBall(_data);
}

void Update(GameData& _data, float _dt)
{
	CheckPlayerInput(_data, _dt);
	UpdateBall(_data, _dt);
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	_window.draw(_data.background);

	for (size_t i = 0; i < MAX_BAR; i++)
	{
		_window.draw(_data.bar[i]);
	}

	_window.draw(_data.ball);

	_window.display();
}

bool CheckCollisionRectRect(sf::FloatRect _rect1, sf::FloatRect _rect2)
{
	if (_rect1.left + _rect1.width >= _rect2.left &&
		_rect1.left <= _rect2.left + _rect2.width &&
		_rect1.top + _rect1.height >= _rect2.top &&
		_rect1.top <= _rect2.top + _rect2.height
		)
		return true;
	
	return false;
}

void CheckPlayerInput(GameData& _data, float _dt)
{
	sf::Vector2f newPos = sf::Vector2f(0, 0);
	newPos = _data.bar[0].getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		newPos.y += -BAR_SPEED * _dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		newPos.y += BAR_SPEED * _dt;
		
	}
	
	if (newPos.y - ((_data.barHeigth / 2) - 10.f) >= 0 && newPos.y + ((_data.barHeigth / 2) - 10.f) <= SCREEN_HEIGHT)
	{
		_data.bar[0].setPosition(newPos);
	}


	newPos = _data.bar[1].getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		newPos.y += -BAR_SPEED * _dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		newPos.y += BAR_SPEED * _dt;
	}

	if (newPos.y - ((_data.barHeigth / 2) - 10.f) >= 0 && newPos.y + ((_data.barHeigth / 2) - 10.f) <= SCREEN_HEIGHT)
	{
		_data.bar[1].setPosition(newPos);
	}
}

void UpdateBall(GameData& _data, float _dt)
{
	sf::Vector2f newPos = sf::Vector2f(0, 0);
	newPos = _data.ball.getPosition();
	newPos += _data.balldir * BALL_SPEED * _dt;
	
	if (newPos.y <= 0 || newPos.y >= SCREEN_HEIGHT)
	{
		_data.balldir.y *= -1;
	}

	_data.ball.setPosition(newPos);
	for (size_t i = 0; i < MAX_BAR; i++)
	{
		if (CheckCollisionRectRect(_data.bar[i].getGlobalBounds(), _data.ball.getGlobalBounds()))
		{
			_data.balldir.x *= -1;
		}
	}
	_data.ball.setPosition(newPos);

	if (newPos.x < 0)
	{
		_data.score2 += 1;
		ResetBall(_data);
	}
	
	if (newPos.x > SCREEN_WIDTH)
	{
		_data.score1 += 1;
		ResetBall(_data);
	}
}

void ResetBall(GameData& _data)
{
	_data.ball.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	_data.balldir = sf::Vector2f(
		(rand() % 2 == 0 ? -1 : 1),
		(rand() % 2 == 0 ? -1 : 1)
	);
}

