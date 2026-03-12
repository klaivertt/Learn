#include "Particle.h"

void Particle::Create(ParticleType _type, sf::Vector2f _position, sf::Vector2f _direction, float _angle, float _speed, float _lifetime)
{
	type = _type;
	pos = _position;
	dir = _direction;
	speed = _speed;
	lifetime = _lifetime;
	maxLifetime = _lifetime;
	angle = _angle;

	if (type == ParticleType::FIRE)
	{
		currentFrame = 0;
	}
}

sf::Vector2f Particle::GetPosition(void)
{
	return pos;
}

float Particle::GetLifetimeRatio(void)
{
	return static_cast<float>(pow(lifetime / maxLifetime, 2));
}

int Particle::getCurrentFrame(void)
{
	return currentFrame;
}

ParticleType Particle::GetType(void)
{
	return type;
}

float Particle::GetAngle(void)
{
	return angle;
}

float Particle::GetSpeed(void)
{
	return speed;
}

void Particle::Draw(sf::RenderWindow& _render, sf::Sprite& _sprite)
{
	if (type == ParticleType::SMOKE)
	{
		sf::Color tempColor = sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * lifetime));

		_sprite.setPosition(pos);
		_sprite.setColor(tempColor);
		_sprite.setRotation(angle);
		_render.draw(_sprite);
	}
	else if (type == ParticleType::FIRE)
	{
		//sf::Color tempColor = sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * _data.particles[i]->GetLifetimeRatio()));
		_sprite.setPosition(pos);

		sf::Vector2u sizeU = _sprite.getTexture()->getSize();
		sf::Vector2f size = sf::Vector2f(static_cast<float>(sizeU.x / MAX_FRAMES_FIRE), static_cast<float>(sizeU.y));

		sf::IntRect frameRect;
		frameRect.left = static_cast<int>(size.x * currentFrame);
		frameRect.top = 0;
		frameRect.width = static_cast<int>(size.x);
		frameRect.height = static_cast<int>(size.y);
		_sprite.setTextureRect(frameRect);
		_sprite.setRotation(angle);
		_render.draw(_sprite);
	}
	else if (type == ParticleType::SPARK || type == ParticleType::BIG_SPARK || type == ParticleType::FIREWORK)
	{
		// Make sparks scale with speed

		_sprite.setPosition(pos);

		//make from base color based on lifetime
		sf::Color tempColor;

		tempColor.r = static_cast<sf::Uint8>(color.r * (lifetime / maxLifetime));
		tempColor.g = static_cast<sf::Uint8>(color.g * (lifetime / maxLifetime));
		tempColor.b = static_cast<sf::Uint8>(color.b * (lifetime / maxLifetime));

		// Scale to make animation to stretch in the direction of the spark
		sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
		if (type != ParticleType::FIREWORK)
		{
			tempColor.a = static_cast<sf::Uint8>(255 * (lifetime / maxLifetime));

			scale.x = 0.5f + (speed / 70.f);

			if (scale.x < 2.f)
			{
				scale.x = 1.f;
			}
		}

		_sprite.setScale(scale);
		_sprite.setRotation(angle);
		_sprite.setColor(tempColor);
		if (type != ParticleType::FIREWORK)
		{
			_render.draw(_sprite, sf::BlendAdd);
		}
		else
		{
			_render.draw(_sprite);
		}
	}
}

void Particle::SetPosition(sf::Vector2f _position)
{
	pos = _position;
}

void Particle::Update(float _dt)
{
	lifetime -= _dt;
	pos += dir * speed * _dt;

	if (type == ParticleType::FIRE)
	{
		currentFrame = static_cast<int>(((maxLifetime - lifetime) / maxLifetime) * MAX_FRAMES_FIRE);
	}
	else if (type == ParticleType::SPARK)
	{
		// si la vitesse et trop basse en absolut on applique pas la gravite
		dir.y += GRAVITY * _dt;

		speed *= 1.0f - (FRICTION * _dt);

	}
	if (type == ParticleType::BIG_SPARK || type == ParticleType::FIREWORK)
	{
		if (lifetime < 0.f)
		{
			exploded = true;
		}
	}
}

bool Particle::IsAlive(void)
{
	return lifetime > 0.f;
}

std::string ParticleTypeToString(ParticleType _type)
{
	switch (_type)
	{
	case ParticleType::SMOKE:
		return "SMOKE";
		break;
	case ParticleType::FIRE:
		return "FIRE";
		break;
	case ParticleType::SPARK:
		return "SPARK";
		break;
	case ParticleType::BIG_SPARK:
		return "BIG_SPARK";
	case ParticleType::FIREWORK:
		return "FIREWORK";
	default:
		return "";
		break;
	}
	return "";
}

//void CreateSparkExplosion(sf::Vector2f _position, GameData& _data, bool _hasColor, SparkColor _color)
//{
//	SparkColor randColor = _hasColor ? _color : (SparkColor)(rand() % (int)(SparkColor::NB_SPARK_COLORS));
//	for (int i = 0; i < NB_OF_SPARKS; ++i)
//	{
//		//make a firework effect
//		Particle* newParticle = new Particle();
//		float angle = RandF(0.f, 360.f);
//		sf::Vector2f dir = sf::Vector2f(static_cast<float>(cos(angle * M_PI / 180.f)), static_cast<float>(sin(angle * M_PI / 180.f)));
//		float speed = RandF(20.f, 2500.f);
//		float lifetime = RandF(1.f, 2.f);
//		newParticle->Create(ParticleType::SPARK, _position, dir, angle, speed, lifetime);
//		SetSparkColor(*newParticle, randColor);
//		_data.particles.push_back(newParticle);
//	}
//}
//
//void CreateBigSparkExplosion(sf::Vector2f _position, GameData& _data, bool _hasColor, SparkColor _color)
//{
//	SparkColor randColor = _hasColor ? _color : (SparkColor)(rand() % (int)(SparkColor::NB_SPARK_COLORS));
//	for (int i = 0; i < NB_OF_BIG_SPARKS; ++i)
//	{
//		//make a firework effect
//		Particle* newParticle = new Particle();
//		float angle = RandF(0.f, 360.f);
//		sf::Vector2f dir = sf::Vector2f(static_cast<float>(cos(angle * M_PI / 180.f)), static_cast<float>(sin(angle * M_PI / 180.f)));
//		float speed = RandF(40.f, 2100.f);
//		float lifetime = RandF(0.1f, 0.7f);
//		newParticle->Create(ParticleType::BIG_SPARK, _position, dir, angle, speed, lifetime);
//		newParticle->sparkColor = randColor;
//		SetSparkColor(*newParticle, randColor);
//		_data.particles.push_back(newParticle);
//	}
//}


inline uint8_t VaryChannel(uint8_t base, int amplitude = 10)
{
	int offset = (rand() % (amplitude * 2 + 1)) - amplitude; // [-amp ; +amp]
	int value = base + offset;

	if (value < 0) value = 0;
	if (value > 255) value = 255;

	return static_cast<uint8_t>(value);
}


void SetSparkColor(Particle& _particle, SparkColor _color)
{
	switch (_color)
	{
	case SparkColor::YELLOW:
		_particle.color = sf::Color(
			VaryChannel(255, 8),
			VaryChannel(255, 12),
			VaryChannel(20, 5)
		);
		break;

	case SparkColor::ORANGE:
		_particle.color = sf::Color(
			VaryChannel(255, 8),
			VaryChannel(165, 10),
			VaryChannel(20, 5)
		);
		break;

	case SparkColor::RED:
		_particle.color = sf::Color(
			VaryChannel(255, 10),
			VaryChannel(10, 5),
			VaryChannel(10, 5)
		);
		break;

	case SparkColor::RED_ORANGE:
		_particle.color = sf::Color(
			VaryChannel(255, 8),
			VaryChannel(69, 10),
			VaryChannel(20, 5)
		);
		break;

	case SparkColor::PURPLE:
		_particle.color = sf::Color(
			VaryChannel(128, 10),
			VaryChannel(0, 5),
			VaryChannel(128, 10)
		);
		break;

	case SparkColor::GREEN:
		_particle.color = sf::Color(
			VaryChannel(20, 5),
			VaryChannel(255, 10),
			VaryChannel(20, 5)
		);
		break;

	case SparkColor::BLUE:
		_particle.color = sf::Color(
			VaryChannel(20, 5),
			VaryChannel(20, 5),
			VaryChannel(255, 10)
		);
		break;

	case SparkColor::BLUE_AND_GREEN:
	{
		int randValue = rand() % 2;
		if (randValue == 0)
		{
			SetSparkColor(_particle, SparkColor::BLUE);
		}
		else
		{
			SetSparkColor(_particle, SparkColor::GREEN);
		}
		break;
	}

	case SparkColor::RED_AND_PURPLE:
	{
		int randValue = rand() % 2;
		if (randValue == 0)
		{
			SetSparkColor(_particle, SparkColor::RED);
		}
		else
		{
			SetSparkColor(_particle, SparkColor::PURPLE);
		}
		break;
	}

	case SparkColor::RED_AND_GREEN:
	{
		int randValue = rand() % 2;
		if (randValue == 0)
		{
			SetSparkColor(_particle, SparkColor::RED);
		}
		else
		{
			SetSparkColor(_particle, SparkColor::GREEN);
		}
		break;
	}

	case SparkColor::RAINBOW:
		_particle.color = sf::Color(
			static_cast<uint8_t>(rand() % 256),
			static_cast<uint8_t>(rand() % 256),
			static_cast<uint8_t>(rand() % 256)
		);
		break;

	case SparkColor::CYAN:
		_particle.color = sf::Color(
			VaryChannel(20, 5),
			VaryChannel(255, 10),
			VaryChannel(255, 10)
		);
		break;

	case SparkColor::MAGENTA:
		_particle.color = sf::Color(
			VaryChannel(255, 10),
			VaryChannel(20, 5),
			VaryChannel(255, 10)
		);
		break;

	default:
		SetSparkColor(_particle, SparkColor::YELLOW);
		break;
	}
}
