#include "Common.h"


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

	sf::Vector2f GetPosition(void);
	sf::Vector2f GetSize(void);

	sf::FloatRect GetRect(void);

	void SetPosition(sf::Vector2f _pos);
	
	void Update(float _dt);
	void Draw(sf::RenderTarget& _render);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	sf::Vector2f pos;
};

Sonuc::Sonuc()
{
	texture.loadFromFile("Seaunaique.png");
	sprite.setTexture(texture);

	size = sf::Vector2f(texture.getSize());
	sprite.setOrigin(sf::Vector2f(size.x / 2, size.y));
}

Sonuc::~Sonuc()
{

}

sf::Vector2f Sonuc::GetPosition(void)
{
	return pos;
}

sf::Vector2f Sonuc::GetSize(void)
{
	return size;
}

sf::FloatRect Sonuc::GetRect(void)
{
	return sf::FloatRect(pos);
}

void Sonuc::SetPosition(sf::Vector2f _pos)
{
	sprite.setPosition(_pos);
}

void Sonuc::Update(float _dt)
{
	// unused for now
	(void)_dt; 
	pos = sprite.getPosition();
}

void Sonuc::Draw(sf::RenderTarget& _render)
{
	_render.draw(sprite);
}


// Game and Data 
struct GameData
{
	sf::Image image;
	sf::Sprite background;
	sf::Texture bgTexture;
	sf::Texture texture;
	Sonuc sonuc;
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

void ResolveColision(sf::FloatRect _rect1, sf::FloatRect _rect2);


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
	_data.texture.loadFromImage(_data.image);

	_data.bgTexture.loadFromFile("Decor.jpg");
	_data.background.setTexture(_data.bgTexture);
	
	_data.sonuc = Sonuc();

}

void Update(GameData& _data, float _dt)
{
	ResolveColision(_data.sonuc, sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	_window.draw(_data.background);

	_data.sonuc.Draw(_window);
	
	_window.display();
}

void ResolveColision(sf::FloatRect _rect1, sf::FloatRect _rect2)
{

}

