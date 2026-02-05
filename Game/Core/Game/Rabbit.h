#pragma once

#include "../../Tools/Common.h"

#define ENERGY_REMOVE 3.1f
#define MAX_ENERGY 100.f
#define MAX_SPEED 150.f
#define BREADABLE_COST 40.f
#define GROW_COST 10.f
#define RADIUS_AGE 6.5f
#define OPORTUNISME_RANGE 100.f

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

	enum Growth
	{
		NEW_BORN,
		KIT,
		JUVENILE,
		ADULT
	};

private:
	// DRAWABLE
	sf::CircleShape shape;
	sf::CircleShape vision;
	sf::CircleShape smellZone;
	// rabbit Gui
	sf::RectangleShape backDisplayBar;
	sf::RectangleShape displayBar;
	// Basic
	float energy = 0.f;
	sf::Vector2f velocity;
	float speed = 0.f;
	Growth growthState = NEW_BORN;
	sf::Vector2f foodPos;
	sf::Vector2f rabbitPos;

	// wander parameters
	float wanderTime = 0.f;
	State state = WANDER;

	// Attributes
	float viewRange = 150.f;
	float smellRange = 300.f;

	// flag
	bool hungry = false;
	bool breedable = false;
	bool foodFinded = false;
	bool rabbitFind = false;
	bool isAdult = false;

	// Copy of Game vector food and rabbits
	std::vector<Food *> *food = nullptr;
	std::vector<Rabbit *> *rabits = nullptr;

	void UpdateDisplay();
	// Food part
	void FindClosestFood(void);
	void FoodDirection(void);
	// wander function
	void NewWanderingDirection(void);

	// bread function
	void TryReproduce(void);
	void FindClosestBreadableRabbit(void);
	void RabbitDirection(void);

	void UpdateState(void);

public:
	Rabbit(sf::Vector2f _startPos, std::vector<Food *> *_food, std::vector<Rabbit *> *_rabits, float _energy = MAX_ENERGY, Growth _growth = NEW_BORN);
	~Rabbit();

	// basic Global function
	void Update(float _dt);
	void Draw(sf::RenderWindow &_render);

	void GrowthChangeState(void);
	void ResetBreadable(void);

	void SetBreadable(bool _bool);
	bool GetIsBreadable(void);
	bool GetIsAdulte(void);

	void SetVelocity(sf::Vector2f _velocity);
	void SetEnergie(float _amount);

	sf::Vector2f GetVelocity(void);
	sf::Vector2f GetPos(void);
	sf::FloatRect GetBound(void);
	bool GetHungry(void);

	bool IsDead(void);

protected:
};