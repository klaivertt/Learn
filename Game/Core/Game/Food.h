#pragma once

#include "../../Tools/Common.h"

#define NB_FOOD_BY_RABBITS 5
#define MIN_FOOD_DAY 5
#define MAX_FOOD_DAY 8
#define FOOD_MIN_NUTRITION 8.f
#define FOOD_MAX_NUTRITION 20.f

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