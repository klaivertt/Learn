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
	virtual void HandleEvents(sf::RenderWindow& window) = 0;
	virtual void KeyPressed(sf::Event::KeyEvent key, sf::RenderWindow& window) = 0;
	virtual void MousePressed(sf::Event::MouseButtonEvent mouse, sf::RenderWindow& window) = 0;
	virtual void MouseMoved(sf::Event::MouseMoveEvent mouse, sf::RenderWindow& window) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	// Finalize scene change at the end of frame
	static void FinalizeSceneChange(Scene* _oldScene)
	{
		GameData& data = *GameData::GetInstance();
		if (data.isSceneChanging && data.nextScene != nullptr)
		{
			data.currentScene = data.nextScene;
			delete _oldScene;
			data.isSceneChanging = false;
			data.nextScene = nullptr;
		}
	}

protected:

	void ChangeScene(Scene* _newScene)
	{
		GameData& data = *GameData::GetInstance();
		data.isSceneChanging = true;
		data.nextScene = _newScene;
	}
};

#endif // !SCENE_H
