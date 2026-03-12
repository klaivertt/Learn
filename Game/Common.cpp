#include "Common.hpp"

float RandF(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

int RandI(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float DistF(sf::Vector2f _a, sf::Vector2f _b)
{
	return static_cast<float>(sqrt(pow(_b.x - _a.x, 2) + pow(_b.y - _a.y, 2)));
}

int DistI(sf::Vector2i _a, sf::Vector2i _b)
{
	return static_cast<int>(sqrt(pow(_b.x - _a.x, 2) + pow(_b.y - _a.y, 2)));
}

sf::Vector2f Normalize(int _x, int _y)
{
	float length = static_cast<float>(sqrt(_x * _x + _y * _y));
	return sf::Vector2f(_x / length, _y / length);
}

sf::Vector2f Normalize(sf::Vector2f _vec)
{
	float length = sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
	return sf::Vector2f(_vec.x / length, _vec.y / length);
}

sf::Vector2i NormalizeI(float _x, float _y)
{
	int length = static_cast<int>(sqrt(_x * _x + _y * _y));
	return sf::Vector2i(static_cast<int>(_x / length), static_cast<int>(_y / length));
}

sf::Vector2f World2Screen(b2Vec2 _worldPos, sf::Vector2f _cam)
{
	sf::Vector2f screenPos = sf::Vector2f(_worldPos.x - _cam.x, _worldPos.y - _cam.y);

	screenPos.y = -screenPos.y; //Inversion de l'axe Y pour coller à box2D
	screenPos.x *= ZOOM;
	screenPos.y *= ZOOM;

	return screenPos;
}
