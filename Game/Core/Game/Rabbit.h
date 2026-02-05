#pragma once

#include "../../Tools/Common.h"


#define ENERGY_REMOVE 3.1f
#define MAX_ENERGY 100.f
#define MAX_SPEED 150.f
#define BREADABLE_COST 40.f
#define GROW_COST 10.f
#define RADIUS_AGE 6.5f

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
	bool isAdult = false;
	Growth growthState = NEW_BORN;

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
	Rabbit(sf::Vector2f _startPos, std::vector<Food*>* _food, std::vector<Rabbit*>* _rabits, float _energy = MAX_ENERGY, Growth _growth = NEW_BORN);
	~Rabbit();

	void Update(float _dt);

	void Draw(sf::RenderWindow& _render);

	bool IsDead(void);

	void SetVelocity(sf::Vector2f _velocity);

	void SetEnergie(float _amount);

	void UpdateState(void);

	void ResetBreadable(void);

	bool GetIsBreadable(void);
	bool GetIsAdulte(void);
	void SetBreadable(bool _bool);
	void GrowthChangeState(void);

	sf::Vector2f GetVelocity(void);
	sf::Vector2f GetPos(void);
	sf::FloatRect GetBound(void);
	bool GetHungry(void);
protected:
};