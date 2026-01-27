#ifndef SCENE_H
#define SCENE_H

#include "Common.h"

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
private:
};

#endif // !SCENE_H
