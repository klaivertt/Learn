#ifndef GAME_H
#define GAME_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"
#include "Tools/Animation/Animation.hpp"

#define MAX_TRUNKS 7
#define MAX_TIME 5.f
#define TIME_ADD 0.2f


enum class LogType
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

class Player
{
private:
	enum State
	{
		IDLE,
		CUT,
	};
	GameData* data = nullptr;
	Sprite sprite;
	Sprite tombStone;
	State state = IDLE;
	Animation idle;
	Animation cut;
	int score = 0;
public:
	bool isDead = false;
	int dir = 1;
	void Load();
	void Update(float _dt);
	void Draw(sf::RenderTarget& _target);
	void ChangeDir(int _dir);
	void Cut();
	void AddScore(int _score);
	int GetScore(void);
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

	Sprite trunk[MAX_TRUNKS];
	Sprite stump;

	Text text;

	TimeBar timeBar;
	Player player;
	sf::Texture trunkTexture[static_cast<int>(LogType::ALL_TYPE)];

	int score[2] = { 0 };

	void LoadTrunk(void);
	void ReplaceTrunk(void);
	void CutTree(int _dir);
	void TestCollision();
};

#endif // !GAME_H
