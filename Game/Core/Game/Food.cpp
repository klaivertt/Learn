#include "Food.h"
#include "Rabbit.h"

Food::Food(sf::Vector2f _pos, float _nutrition)
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color(75, 120, 75));
	shape.setPosition(_pos);
	nutrition = _nutrition;
}

Food::~Food()
{
}

void Food::Draw(sf::RenderWindow& _render)
{
	_render.draw(shape);
}

sf::Vector2f Food::GetPos(void)
{
	return shape.getPosition();
}

sf::FloatRect Food::GetBound(void)
{
	return shape.getGlobalBounds();
}

float Food::GetNutritionValue(void)
{
	if (!eated)
	{
		eated = true;
		return nutrition;
	}
	return 0.0f;
}
bool Food::GetEated(void)
{
	return eated;
}