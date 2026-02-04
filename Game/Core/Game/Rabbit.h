#pragma once

#include "../../Tools/Common.h"


#define ENERGY_REMOVE 4.f
#define MAX_ENERGY 100.f
#define MAX_SPEED 150.f
#define BREADABLE_COST 35.f

class Food;

class Rabbit
{
public:
	enum State
	{
		WANDER,
		HUNGRY,
		BREEDABLE
	};


private:
	sf::CircleShape shape;
	float energy = 0.f;
	sf::Vector2f velocity;
	float speed = 0.f;
	float wanderTime = 0.f;
	bool hungry = false;
	bool breedable = false;
	State state = WANDER;
	//rabbit Gui
	sf::RectangleShape backDisplayBar;
	sf::RectangleShape displayBar;
	bool foodFinded = false;
	//Copy of food vector
	std::vector<Food*>* food = nullptr;
	std::vector<Rabbit*>* rabits = nullptr;
	bool rabbitFind = false;

	sf::Vector2f foodPos;
	sf::Vector2f rabbitPos;
	void UpdateDisplayBar();
	void FindClosestFood(void);
	void FoodDirection(void);
	void NewWanderingDirection(void);
	void TryReproduce(void);
	void FindClosestBreadableRabbit(void);
	void RabbitDirection(void);
public:
	Rabbit(sf::Vector2f _startPos, std::vector<Food*>* _food, std::vector<Rabbit*>* _rabits, float _energy = MAX_ENERGY);
	~Rabbit();

	void Update(float _dt);

	void Draw(sf::RenderWindow& _render);

	bool IsDead(void);

	void SetVelocity(sf::Vector2f _velocity);

	void SetEnergie(float _amount);

	void UpdateState(void);

	void ResetBreadable(void);

	bool GetIsBreadable(void);
	void SetBreadable(bool _bool);

	sf::Vector2f GetVelocity(void);
	sf::Vector2f GetPos(void);
	sf::FloatRect GetBound(void);
	bool GetHungry(void);
protected:
};