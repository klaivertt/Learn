#ifndef GAME_H
#define GAME_H

#include "../../Tools/Common.h"
#include "../../Tools/Scene.h"
#define PHYSISCS_PRECSION 8

// defines Game
#define DEAD_TIMER 2.5f
#define DEAD_Y -10

#define ENERGY_REMOVE 2.5f
#define MAX_ENERGY 100.f

#define NB_OF_RABBITS 10
#define NB_FOOD_BY_RABBITS 3
#define FOOD_MIN_NUTRITION 2.f
#define FOOD_MAX_NUTRITION 6.f

class Rabbit
{
public:
	enum State
	{
		WANDER,
		HUNGRY,
	};


private:
	sf::CircleShape shape;
	float energy = 0.f;
	sf::Vector2f velocity;
	State state = WANDER;
	//rabbit Gui
	sf::RectangleShape backDisplayBar;
	sf::RectangleShape displayBar;

	void UpdateDisplayBar();
public:
	Rabbit(sf::Vector2f _startPos);
	~Rabbit();

	void Update(float _dt);

	void Draw(sf::RenderWindow& _render);

	bool IsDead(void);

	void SetVelocity(sf::Vector2f _velocity);

	void SetEnergie(float _amount);

	void UpdateState(void);

	sf::Vector2f GetVelocity(void);
	sf::Vector2f GetPos(void);
	sf::FloatRect GetBound(void);
protected:
};

class Food
{
private:
	sf::CircleShape shape;
	float nutrition = 0.f;
	bool eated = false;
public:
	Food(sf::Vector2f _pos, float _nutrition);
	~Food();

	void Draw(sf::RenderWindow& _render);

	sf::Vector2f GetPos();
	sf::FloatRect GetBound(void);

	float GetNutritionValue(void);

	bool GetEated(void);
};

// Game Scene
class Game : public Scene
{
public:
	Game();
	~Game();
	void Load() override;
	void Update(float _dt, sf::RenderWindow& _window) override;
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window) override;
	void Draw(sf::RenderWindow& _window) override;

private:
	GameData* data = nullptr;

	sf::Sprite background;

	// Game Systems
	bool isGameOver = false;

	std::vector<Rabbit*> rabits;
	std::vector<Food*> foods;

	// Camera functions
	void MoveCamera(float _dt);
	void CheckRabbitColideWithMap(Rabbit& _rabbit);
	void CheckRabbitColideWithFood(Rabbit& _rabbit, Food& _food);
};

#endif // !GAME_H
