#ifndef SCENE_H
#define SCENE_H

#include "Common.hpp"
#include "Tools/GameData.hpp"

class Scene
{
public:
	Scene() {};
	~Scene() {};
	virtual void Load() = 0;
	virtual void Update(float dt, sf::RenderWindow& window) = 0;
	virtual void KeyPressed(sf::Event::KeyEvent key, sf::RenderWindow& window) = 0;
	virtual void MousePressed(sf::Event::MouseButtonEvent mouse, sf::RenderWindow& window) = 0;
	virtual void MouseMoved(sf::Event::MouseMoveEvent mouse, sf::RenderWindow& window) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

protected:

	void ChangeScene(Scene* _thisScene ,Scene* _newScene)
	{
		GameData& data = *GameData::GetInstance();
		data.currentScene = _newScene;
		delete _thisScene;
	}
};

#endif // !SCENE_H
