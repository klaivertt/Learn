#ifndef COMMON__H
#define COMMON__H

#pragma region Include
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>

//SFML
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/OpenGL.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>

//Box 2D0
#include "box2d/box2d.h"
#include "box2d/types.h" 

//Json 
#include "json/json.h"

//Other
#include "Tools/Miscellaneous/Vec2.hpp"

#pragma endregion


#pragma region GameDefines
#define ZOOM 64
#define RAD_TO_DEG 180.0f / M_PI

#pragma endregion

typedef enum Anchor
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_LEFT,
	CENTER,
	CENTER_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
}Anchor;

typedef enum Direction
{
	RIGHT,
	DOWN,
	LEFT,
	UP,

	NB_DIRECTIONS // Keep last
}Direction;

class GameData;

#pragma region ToolFunctions

// Generate a random float number between min and max
// @param min: Minimum value
// @param max: Maximum value
float RandF(float min, float max);

// Generate a random integer number between min and max
// @param min: Minimum value
// @param max: Maximum value
int RandI(int min, int max);

// Calculate the distance between two 2D float vectors
// @param _a: First vector
// @param _b: Second vector
float DistF(sf::Vector2f _a, sf::Vector2f _b);

// Calculate the distance between two 2D integer vectors 
// @param _a: First vector
// @param _b: Second vector
int DistI(sf::Vector2i _a, sf::Vector2i _b);

// Normalize a 2D vector given its x and y components
// @param _x: X component
// @param _y: Y component
sf::Vector2f Normalize(int _x, int _y);

// Normalize a 2D float vector
// @param _vec: Vector to normalize
// @return Normalized vector
sf::Vector2f Normalize(sf::Vector2f _vec);

// Normalize a 2D integer vector given its x and y components
// @param _x: X component
// @param _y: Y component
sf::Vector2i NormalizeI(float _x, float _y);

sf::Vector2f World2Screen(b2Vec2 _worldPos, sf::Vector2f _cam);
#pragma endregion

#endif //COMMON__H