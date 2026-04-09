#include "Common.h"

#define MAX_PLAYER 2


enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Player
{
	int pixelPosed = 0;
	sf::Vector2i pos;
	sf::Color color;
	bool alive = true;
	Dir dir = Dir::UP;
	sf::Keyboard::Key key[4];
};


struct GameData
{
	sf::Image image;
	sf::Sprite sprite;
	sf::Texture texture;
	Player player[MAX_PLAYER];
};

// Prototypes
void Init(GameData& _data);
void Update(GameData& _data, float _dt);
void Display(GameData& _data, sf::RenderWindow& _window);

void PlayerKeyPressed(Player& _player);
void PlayerUpdatePos(Player& _player);
void PlayerCheckCollision(sf::Image& _image, Player& _player);
void PlayerDrawPixelAtPos(sf::Image& _image, Player& _player);
void ChangeTexture(sf::Image& _image, sf::Texture& _texture);

void DrawMap(sf::RenderWindow& _window, sf::Sprite& _sprite);


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
		}

		Update(data, dt);
		Display(data, window);
	}
}



///////////////////////////////////////////////////////////////////
void Init(GameData& _data)
{
	Player& player1 = _data.player[0];
	player1.alive = true;
	player1.color = sf::Color(150, 120, 70);
	player1.pos = sf::Vector2i(0, SCREEN_HEIGHT / 2);
	player1.pixelPosed = 0;
	player1.dir = Dir::RIGHT;
	player1.key[0] = sf::Keyboard::Z;
	player1.key[1] = sf::Keyboard::S;
	player1.key[2] = sf::Keyboard::Q;
	player1.key[3] = sf::Keyboard::D;

	Player& player2 = _data.player[1];
	player2.alive = true;
	player2.color = sf::Color(50, 120, 200);
	player2.pos = sf::Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	player2.pixelPosed = 0;
	player2.dir = Dir::LEFT;
	player2.key[0] = sf::Keyboard::Up;
	player2.key[1] = sf::Keyboard::Down;
	player2.key[2] = sf::Keyboard::Left;
	player2.key[3] = sf::Keyboard::Right;

	_data.image.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	_data.texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	_data.sprite.setTexture(_data.texture);
}

void Update(GameData& _data, float _dt)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player& actualPlayer = _data.player[i];
		if (actualPlayer.alive)
		{
			PlayerKeyPressed(actualPlayer);
			PlayerUpdatePos(actualPlayer);
			PlayerCheckCollision(_data.image, actualPlayer);
			PlayerDrawPixelAtPos(_data.image, actualPlayer);
		}
	}

	ChangeTexture(_data.image, _data.texture);
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	DrawMap(_window, _data.sprite);

	_window.display();
}

void PlayerKeyPressed(Player& _player)
{
	if (sf::Keyboard::isKeyPressed(_player.key[0]))
	{
		_player.dir = Dir::UP;
	}
	if (sf::Keyboard::isKeyPressed(_player.key[1]))
	{
		_player.dir = Dir::DOWN;
	}
	if (sf::Keyboard::isKeyPressed(_player.key[2]))
	{
		_player.dir = Dir::LEFT;
	}
	if (sf::Keyboard::isKeyPressed(_player.key[3]))
	{
		_player.dir = Dir::RIGHT;
	}
}

void PlayerUpdatePos(Player& _player)
{
	switch (_player.dir)
	{
	case Dir::RIGHT:
		_player.pos += sf::Vector2i(1, 0);
		break;
	case Dir::LEFT:
		_player.pos += sf::Vector2i(-1, 0);
		break;
	case Dir::UP:
		_player.pos += sf::Vector2i(0, -1);
		break;
	case Dir::DOWN:
		_player.pos += sf::Vector2i(0, 1);
		break;
	default:
		break;
	}
	std::cout << _player.pos.x << " : " << _player.pos.y << std::endl;
	_player.pixelPosed++;
}

void PlayerCheckCollision(sf::Image& _image, Player& _player)
{
	if ((_player.pos.x >= 0 && _player.pos.x <= SCREEN_WIDTH) && (_player.pos.y > 0 && _player.pos.y < SCREEN_HEIGHT))
	{
		if (_image.getPixel(_player.pos.x, _player.pos.y) != sf::Color::Black)
		{
			_player.alive = false;
		}
	}
}

void PlayerDrawPixelAtPos(sf::Image& _image, Player& _player)
{
	if (_player.alive)
	{
		if ((_player.pos.x >= 0 && _player.pos.x <= SCREEN_WIDTH) && (_player.pos.y > 0 && _player.pos.y < SCREEN_HEIGHT))
		{
			_image.setPixel(_player.pos.x, _player.pos.y, _player.color);
		}
	}
}

void ChangeTexture(sf::Image& _image, sf::Texture& _texture)
{
	_texture.update(_image);
}

void DrawMap(sf::RenderWindow& _window, sf::Sprite& _sprite)
{
	_window.draw(_sprite);
}
