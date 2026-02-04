#ifndef COMMON__H
#define COMMON__H

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
#include <cmath>
#include "json/json.h"
#include <map>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"
#include "box2d/box2d.h"
#include "box2d/types.h" 



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

#pragma region SpriteLoadingFunctions
// Load a sprite from a file and set its origin based on division factors
// @param _path: File path to the image
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _divide);

// Load a sprite from an existing texture and set its origin based on division factors
// @param _texture: Reference to the sf::Texture object
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
sf::Sprite LoadSprite(sf::Texture& _texture, sf::Vector2f _divide);

// Load a sprite from an existing texture
// @param _texture: Reference to the sf::Texture object
sf::Sprite LoadSprite(sf::Texture& _texture);

// Load a sprite from a file
// @param _path: File path to the image
sf::Sprite LoadSprite(const std::string _path);

// Load a sprite from a file, set its origin based on division factors, and apply a texture rectangle
// @param _path: File path to the image
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
// @param _rect: Texture rectangle to apply
sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _divide, sf::IntRect _rect);

// Load a sprite from an existing texture, set its origin based on division factors, and apply a texture rectangle
// @param _texture: Reference to the sf::Texture object
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
sf::Sprite LoadSprite(sf::Texture& _texture, sf::Vector2f _pos, sf::Vector2f _divide);

// Load a sprite from a file, set its position, and set its origin based on division factors
// @param _path: File path to the image
// @param _pos: Position to place the sprite
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _pos, sf::Vector2f _divide);
#pragma endregion

#pragma region TextFunctions
// Set text properties like string, font, anchor, and decal
// @param _text: Reference to the sf::Text object to set
// @param str: The string to display
// @param _font: Reference to the font to use
// @param _anchor: Anchor position for text alignment
// @param _decal: Positional decal to adjust text position
// @return Configured sf::Text object
sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, Anchor _anchor, sf::Vector2f _decal = sf::Vector2f(0, 0));

// Set text properties like string, font, position, and origin division
// @param str: The string to display
// @param _font: Reference to the font to use
// @param _pos: Position to place the text
// @param _divide: Division factors for setting the origin like (0.5f, 0.5f) for center
// @return Configured sf::Text object
sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, sf::Vector2f _pos, sf::Vector2f _divide);

// Set text properties like string, font, and position
// @param str: The string to display
// @param _font: Reference to the font to use
// @param _pos: Position to place the text
// @return Configured sf::Text object
sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, sf::Vector2f _pos);


// @brief Sets text properties like string, anchor, and decal
// @param _text: Reference to the sf::Text object to set
// @param str: The string to display
// @param _anchor: Anchor position for text alignment
// @param _decal: Positional decal to adjust text position
void SetText(sf::Text& _text, const std::string& _str, Anchor _anchor, sf::Vector2f _decal);

// @brief Sets text properties like string, position, and origin division
// @param _text: Reference to the sf::Text object to set
// @param str: The string to display
// @param _pos: Position to place the text
void SetText(sf::Text& _text, const std::string& _str, sf::Vector2f _pos, sf::Vector2f _divide);

// @brief Sets text properties like string and position
// @param _text: Reference to the sf::Text object to set
// @param str: The string to display
// @param _pos: Position to place the text
void SetText(sf::Text& _text, const std::string& _str, sf::Vector2f _pos);

// @brief Sets text string
// @param _text: Reference to the sf::Text object to set
void SetText(sf::Text& _text, const std::string& _str);
#pragma endregion


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

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _scale, float _angle, sf::RenderWindow& _render);
void BlitText(sf::Text _text, sf::Vector2f _pos, float _angle, sf::RenderWindow& _render);

sf::Vector2f World2Screen(b2Vec2 _worldPos, sf::Vector2f _cam);
#pragma endregion

#endif //COMMON__H