#ifndef GAME_H
#define GAME_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"

#define MAX_TRUNC 7
#define MAX_TIME 5.f

class Animation
{
public:
	sf::Texture* texture = nullptr;
	Animation(){};
	~Animation() {};
};

enum class LogTyppe
{
	LEFT,
	RIGHT,
	NORMAL,
	VAR,

	ALL_TYPE
};

class TimeBar
{
private:
	Sprite bar;
	Sprite barBack; 
	Vec2 size;
	float time = MAX_TIME;
public:
	void Load(void);
	void Update(float _dt);
	void Draw(sf::RenderTarget& _target);
	void AddTime(float _time);
};

// Game Scene
class Game : public Scene
{
public:
	Game();
	~Game();
	void Load() override;
	void Update(float _dt, sf::RenderWindow& _window) override;
	void HandleEvents(sf::RenderWindow& _window) override;
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window) override;
	void Draw(sf::RenderWindow& _window) override;
private:
	GameData* data = nullptr;
	Sprite background;

	Sprite trunk[MAX_TRUNC];
	Sprite stump;

	TimeBar timeBar;

	sf::Texture trunkTexture[static_cast<int>(LogTyppe::ALL_TYPE)];

	int score[2] = { 0 };

	void LoadTrunk(void);
};

#endif // !GAME_H
