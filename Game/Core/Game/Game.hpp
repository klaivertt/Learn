#ifndef GAME_H
#define GAME_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"

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
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window) override;
	void Draw(sf::RenderWindow& _window) override;
private:
	GameData* data = nullptr;

	Sprite test;

	void LoadMainFiles(const std::string _files);
	void LoadCharacters(const std::string _files);
};

#endif // !GAME_H
