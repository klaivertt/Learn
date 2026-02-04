#ifndef GAME_H
#define GAME_H

#include "../../Tools/Common.h"
#include "../../Tools/Scene.h"
#define PHYSISCS_PRECSION 8

#define NB_OF_RABBITS 10

class Food;
class Rabbit;
class DayNightCycle;

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

	DayNightCycle* dayCycle = nullptr;
	sf::Text dayCount;

	// Camera functions
	void MoveCamera(float _dt);
	void ResetRabbitBread(void);
	void CheckRabbitColideWithMap(Rabbit& _rabbit);
	void CheckRabbitColideWithFood(Rabbit& _rabbit, Food& _food);
	void SpawnFood(void);
};

#endif // !GAME_H
