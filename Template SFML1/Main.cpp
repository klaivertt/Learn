#include "Common.h"


enum class Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	MAX_DIR,
	NONE
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
	void Move(sf::Vector2f _pos);

	void Update(float _dt);
	void Draw(sf::RenderTarget& _render);

	void SetDir(Dir _dir);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	sf::Vector2f pos;
	Dir dir = Dir::NONE;
	float speed = 200.f;

	void UpdatePos(float _dt);
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
	return sf::FloatRect(pos.x - size.x / 2, pos.y - size.y, size.x, size.y);
}

void Sonuc::SetPosition(sf::Vector2f _pos)
{
	pos = _pos;
	sprite.setPosition(pos);
}

void Sonuc::Move(sf::Vector2f _pos)
{
	pos += _pos;
	sprite.setPosition(pos);
}

void Sonuc::Update(float _dt)
{
	//// unused for now
	//(void)_dt;

	UpdatePos(_dt);
	sprite.setPosition(pos);

}

void Sonuc::Draw(sf::RenderTarget& _render)
{
	_render.draw(sprite);
}

void Sonuc::SetDir(Dir _dir = Dir::NONE)
{
	dir = _dir;
	//std::cout << int(_dir) << std::endl;
}

void Sonuc::UpdatePos(float _dt)
{
	sf::Vector2f move = sf::Vector2f(0, 0);
	switch (dir)
	{
	case Dir::UP:
		move.y = -speed * _dt;
		break;
	case Dir::DOWN:
		move.y = speed * _dt;
		break;
	case Dir::LEFT:
		move.x = -speed * _dt;
		break;
	case Dir::RIGHT:
		move.x = speed * _dt;
		break;
	default:
		break;
	}

	pos += move;
	std::cout << "x :" << pos.x << " y :" << pos.y << std::endl;
}


// Game and Data 
struct GameData
{
	sf::Image image;
	sf::Sprite background;
	sf::Texture bgTexture;
	sf::Texture texture;
	Sonuc sonuc;
	sf::FloatRect* collision = nullptr;
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

void CheckMapCollision(GameData& _data);
void CheckPlayerInput(GameData& _data);

sf::Vector2f ResolveColision(sf::FloatRect _rect1, sf::FloatRect _rect2);


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
	_data.sonuc.SetPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	_data.collision = new sf::FloatRect[4];

	_data.collision[0] = sf::FloatRect(0, 0, SCREEN_WIDTH, 10);
	_data.collision[1] = sf::FloatRect(SCREEN_WIDTH - 10, 0, 10, SCREEN_HEIGHT);
	_data.collision[2] = sf::FloatRect(0, SCREEN_HEIGHT - 10, SCREEN_WIDTH, 10);
	_data.collision[3] = sf::FloatRect(0, 0, 10, SCREEN_HEIGHT);
}

void Update(GameData& _data, float _dt)
{
	CheckMapCollision(_data);
	CheckPlayerInput(_data);

	_data.sonuc.Update(_dt);

	CheckMapCollision(_data);
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	_window.draw(_data.background);

	_data.sonuc.Draw(_window);

	_window.display();
}

void CheckMapCollision(GameData& _data)
{
	for (size_t i = 0; i < 4; i++)
	{
		_data.sonuc.Move(ResolveColision(_data.sonuc.GetRect(), _data.collision[i]));
	}
}

void CheckPlayerInput(GameData& _data)
{
	Dir tempDir = Dir::NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		tempDir = Dir::UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		tempDir = Dir::LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		tempDir = Dir::DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		tempDir = Dir::RIGHT;
	}
	_data.sonuc.SetDir(tempDir);
}

sf::Vector2f ResolveColision(sf::FloatRect _rect1, sf::FloatRect _rect2)
{
	sf::Vector2f correction = sf::Vector2f(0, 0);

	if (_rect1.left + _rect1.width >= _rect2.left &&
		_rect1.left <= _rect2.left + _rect2.width &&
		_rect1.top + _rect1.height >= _rect2.top &&
		_rect1.top <= _rect2.top + _rect2.height
		)
	{

		float overlapLeft = (_rect1.left + _rect1.width) - _rect2.left;
		float overlapRight = (_rect2.left + _rect2.width) - _rect1.left;
		float overlapTop = (_rect1.top + _rect1.height) - _rect2.top;
		float overlapBottom = (_rect2.top + _rect2.height) - _rect1.top;

		float minX = std::min(overlapLeft, overlapRight);
		float minY = std::min(overlapTop, overlapBottom);


		if (minX < minY)
			if (overlapLeft < overlapRight)
			{
				correction += sf::Vector2f(-overlapLeft, 0.f);
			}
			else
			{
				correction += sf::Vector2f(overlapRight, 0.f);
			}
		else
		{
			if (overlapTop < overlapBottom)
			{
				correction += sf::Vector2f(0.f, -overlapTop);
			}
			else
			{
				correction += sf::Vector2f(0.f, overlapBottom);
			}
		}

	}
	return correction;
}

