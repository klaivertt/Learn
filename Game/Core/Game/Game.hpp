#ifndef GAME_H
#define GAME_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"

#define BALL_SPEED 600.f
#define PLAYER_SPEED 700.f

class Animation
{
public:
	sf::Texture* texture = nullptr;
	Animation(){};
	~Animation() {};
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
	Sprite paddle[2];
	Sprite ball;
	Vec2 ballVelocity;
	int playerDir[2] = {0};
	Text scoreText;

	int score[2] = { 0 };

	void LoadPaddle(void);
	void LoadBall(void);
	void UpdateBall(float _dt);
	void UpdatePlayer(float _dt);
	void CheckColision();
	void ResetBall();
	void SetNewScore();
	void PlayerInput();
};

#endif // !GAME_H
