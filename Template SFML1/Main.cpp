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
	bool isGameOver = false;
	sf::Text gameOverText;
	sf::Text playerWin;
	sf::Text restart;
	sf::Font font;
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

void ChangePlayerWinText(sf::Text& _text, const int& const _playerId);

void DrawMap(sf::RenderWindow& _window, sf::Sprite& _sprite);
void DrawGameOver(sf::RenderWindow& _window, sf::Text& _gameOverText, sf::Text& _playerWinText, sf::Text& _restart);

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

	_data.font.loadFromFile("poppins.ttf");

	_data.gameOverText.setFont(_data.font);
	_data.gameOverText.setCharacterSize(30);

	sf::Vector2f pos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	_data.gameOverText.setPosition(pos);
	_data.gameOverText.setString("Game Over");
	_data.gameOverText.setFillColor(sf::Color::White);
	sf::FloatRect bound = _data.gameOverText.getGlobalBounds();
	_data.gameOverText.setOrigin(sf::Vector2f(bound.width / 2, bound.height / 2));


	_data.playerWin.setFont(_data.font);
	_data.playerWin.setCharacterSize(20);
	pos.y += 65.f;

	_data.playerWin.setPosition(pos);
	_data.playerWin.setString("Player . Win");
	_data.playerWin.setFillColor(sf::Color::White);
	bound = _data.playerWin.getGlobalBounds();
	_data.playerWin.setOrigin(sf::Vector2f(bound.width / 2, bound.height / 2));

	_data.restart.setFont(_data.font);
	_data.restart.setCharacterSize(20);
	pos.y += 30.f;

	_data.restart.setPosition(pos);
	_data.restart.setString("Press 'Space' to restart");
	_data.restart.setFillColor(sf::Color::White);
	bound = _data.restart.getGlobalBounds();
	_data.restart.setOrigin(sf::Vector2f(bound.width / 2, bound.height / 2));

	_data.isGameOver = false;
}

void Update(GameData& _data, float _dt)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (!_data.isGameOver)
		{
			Player& actualPlayer = _data.player[i];
			if (actualPlayer.alive)
			{
				PlayerKeyPressed(actualPlayer);
				PlayerUpdatePos(actualPlayer);
				PlayerCheckCollision(_data.image, actualPlayer);
				PlayerDrawPixelAtPos(_data.image, actualPlayer);
			}
			else
			{
				if (!_data.isGameOver && !_data.player[i].alive)
				{
					ChangePlayerWinText(_data.playerWin, (i == 0 ? 2 : 1));
					_data.isGameOver = true;
					//std::cout << "game over";
				}
			}
		}
	}

	ChangeTexture(_data.image, _data.texture);
}

void Display(GameData& _data, sf::RenderWindow& _window)
{
	_window.clear(sf::Color::Black);

	DrawMap(_window, _data.sprite);

	if (_data.isGameOver)
	{
		DrawGameOver(_window, _data.gameOverText, _data.playerWin, _data.restart);
	}

	_window.display();
}

void PlayerKeyPressed(Player& _player)
{
	if (sf::Keyboard::isKeyPressed(_player.key[0]))
	{
		if (_player.dir != DOWN)
		{
			_player.dir = Dir::UP;
		}
	}
	if (sf::Keyboard::isKeyPressed(_player.key[1]))
	{
		if (_player.dir != UP)
		{
			_player.dir = Dir::DOWN;
		}
	}
	if (sf::Keyboard::isKeyPressed(_player.key[2]))
	{
		if (_player.dir != RIGHT)
		{
			_player.dir = Dir::LEFT;
		}
	}
	if (sf::Keyboard::isKeyPressed(_player.key[3]))
	{
		if (_player.dir != LEFT)
		{
			_player.dir = Dir::RIGHT;
		}
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
	//std::cout << _player.pos.x << " : " << _player.pos.y << std::endl;
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

void ChangePlayerWinText(sf::Text& _text, const int& const _playerId)
{
	_text.setString("Player " + std::to_string(_playerId) + " Win");
}

void DrawMap(sf::RenderWindow& _window, sf::Sprite& _sprite)
{
	_window.draw(_sprite);
}

void DrawGameOver(sf::RenderWindow& _window, sf::Text& _gameOverText, sf::Text& _playerWinText, sf::Text& _restart)
{
	_window.draw(_gameOverText);
	_window.draw(_playerWinText);
	_window.draw(_restart);
}
