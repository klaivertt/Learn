#include "Common.h"

#define MAX_PLAYER 2


enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Sonuc
{
public:
	Sonuc();
	~Sonuc();

private:
	sf::Texture texture;
	sf::Sprite sprite;
};

Sonuc::Sonuc()
{

}

Sonuc::~Sonuc()
{

}


struct GameData
{
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	Sonuc player[MAX_PLAYER];
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

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
	

	_data.image.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	_data.texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	_data.sprite.setTexture(_data.texture);

	sf::Vector2f pos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

}

void Update(GameData& _data, float _dt)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		
	}

	ChangeTexture(_data.image, _data.texture);
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	
	_window.display();
}