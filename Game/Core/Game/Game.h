#ifndef GAME_H
#define GAME_H

#include "../../Tools/Common.h"
#include "../../Tools/Scene.h"
#define PHYSISCS_PRECSION 8

// defines Motorbike
#define TYPE_OF_BIKER 2
#define MOTO_STARTX 3
#define MOTO_STARTY 5
#define MOTO_MAXSPEED 55.f
#define FRAME_RADIUS 0.264f

// defines Bridge
#define BRIDGE_PLANK_COUNT 28
#define PLANK_HALF_WIDTH 0.5f
#define PLANK_HALF_HEIGHT 0.1f
#define PLANK_SPACING 1.f

#define FIRST_BRIDGE_START_X 190.f
#define FIRST_BRIDGE_END_X 192.f
#define FIRST_BRIDGE_Y 0.06f

// defines Ground
#define SEGMENT_COUNT 6

// defines Game
#define DEAD_TIMER 2.5f
#define DEAD_Y -10

#define ENERGY_REMOVE 1.f

class Rabbit
{
private:
	sf::CircleShape shape;
	float energy = 0.f;
	sf::Vector2f velocity;

public:
	Rabbit(sf::Vector2f startPos)
	{
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::White);
		shape.setPosition(startPos);
		energy = 100.f;
		velocity = sf::Vector2f(RandF(-1, 1), RandF(-1, 1));
	}

	~Rabbit()
	{
	}

	void Update(float _dt)
	{
		shape.move(velocity);
		energy = -ENERGY_REMOVE * _dt;

		if (energy < 30)
		{
			shape.setFillColor(sf::Color::Red);
		}
	}

	void Draw(sf::RenderWindow & _render)
	{
		_render.draw(shape);
	}

	bool IsDead(void)
	{
		return energy <= 0;
	}

protected:
};

// Game Scene
class Game : public Scene
{
public:
	Game();
	~Game();
	void Load() override;
	void Update(float _dt, sf::RenderWindow &_window) override;
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow &_window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow &_window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow &_window) override;
	void Draw(sf::RenderWindow &_window) override;

private:
	GameData *data = nullptr;

	sf::Sprite background;

	// Game Systems
	bool isGameOver = false;

	std::vector<Rabbit*> rabits;
	// Functions
	void ContactEvent(void);

	// Camera functions
	void MoveCamera(float _dt);
};

#endif // !GAME_H
