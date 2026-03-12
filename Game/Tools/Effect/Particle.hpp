#ifndef PARTICLE_H
#define PARTICLE_H

#include "Common.h"

#define MAX_FRAMES_FIRE 10
#define NB_OF_SPARKS 2000
#define NB_OF_BIG_SPARKS 8
#define GRAVITY 1.2f
#define FRICTION 5.f

enum class ParticleType
{
	SMOKE,
	FIRE,
	SPARK,
	BIG_SPARK,
	FIREWORK,
	NB_PARTICLE_TYPES
};

enum class SparkColor
{
	YELLOW,
	ORANGE,
	RED_ORANGE,
	RED,
	PURPLE,
	GREEN,
	BLUE,
	BLUE_AND_GREEN,
	RED_AND_PURPLE,
	RED_AND_GREEN,
	RAINBOW,
	CYAN,
	MAGENTA,
	NB_SPARK_COLORS
};

class Animation;

class Particle
{
public:
	void Create(ParticleType _type, sf::Vector2f _position, sf::Vector2f _direction, float _angle, float _speed, float _lifetime);
	void Update(float _dt);
	bool IsAlive(void);
	sf::Vector2f GetPosition(void);
	float GetLifetimeRatio(void);
	int getCurrentFrame(void);
	ParticleType GetType(void);
	float GetAngle(void);
	float GetSpeed(void);
	void Draw(sf::RenderWindow& _render, sf::Sprite& _sprite);

	void SetPosition(sf::Vector2f _position);
	SparkColor sparkColor = {};
	sf::Color color;
	bool exploded = false;
private:
	sf::Vector2f pos;
	sf::Vector2f dir;
	float speed = 0;
	float lifetime = 0;
	float maxLifetime = 0;
	ParticleType type = ParticleType::SMOKE;
	float angle = 0;

	// For animated particles like FIRE
	int currentFrame = 0;

	// For colored particles like SPARK
};

std::string ParticleTypeToString(ParticleType _type);
//
//void CreateSparkExplosion(sf::Vector2f _position, GameData& _data, bool _hasColor, SparkColor _color);
//void CreateBigSparkExplosion(sf::Vector2f _position, GameData& _data, bool _hasColor, SparkColor _color);
//void SetSparkColor(Particle& _particle, SparkColor _color);
#endif // !PARTICLE_H

////////////////////////////////////////////////////
/// Developped by Alexandre Bosio //////////////////
////////////////////////////////////////////////////