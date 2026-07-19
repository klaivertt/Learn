#include "Common.h"

// Game and Data 

#define MAX_BAR 2

struct GameData
{
	sf::Sprite background;
	sf::Texture bgTexture;
	sf::Sprite bar[MAX_BAR];
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

bool CheckCollisionRectRect(sf::FloatRect _rect1, sf::FloatRect _rect2);
void CheckPlayerInput(GameData& _data);

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
	
}

void Update(GameData& _data, float _dt)
{

	CheckPlayerInput(_data);

}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	_window.draw(_data.background);


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

void CheckPlayerInput(GameData& _data)
{

}

