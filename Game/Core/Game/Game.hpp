#ifndef GAME_H
#define GAME_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"

#define GRID_WIDTH 17
#define GRID_HEIGHT 15

#define CELL_SIZE 32

#define HEAD_SIZE 28
#define TAILS_SIZE 10

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake
{
private:
	int score;
	std::vector<sf::RectangleShape> shapes;
public:

	void Load(void);
	void Update(float _dt);
	void Draw(sf::RenderTarget& _render);

	void ChangeDir(Direction _dir);
private:
	void CreateNewRectangle(void);
	void ClampSizeBetweenHeadAndTails(void);
};

struct Cell
{
	sf::RectangleShape shape;
	bool isOccupate = false;
};

class Board
{
private:

public:
private:
};

// Game Scene
class Game : public Scene
{
public:
	Game();
	~Game();
	void Load() override;
	void Update(float _dt, sf::RenderWindow& _window) override;
	void HandleEvents(sf::RenderWindow& _window) override;
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window) override;
	void Draw(sf::RenderWindow& _window) override;
private:
	GameData* data = nullptr;
};

#endif // !GAME_H
