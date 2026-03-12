#include "Common.hpp"
#include "Core/Init.hpp"
#include "Tools/GameData.hpp"
#include "Tools/Scene.hpp"

int main()
{
	GameData *data = GameData::GetInstance();

	Init(*data);
	sf::Clock deltaTime;

	while (data->window.isOpen())
	{
		float dt = deltaTime.restart().asSeconds();

		if (data->currentScene != nullptr && !data->isSceneChanging)
		{
			data->currentScene->HandleEvents(data->window);

			data->currentScene->Update(dt, data->window);
		}

		data->window.clear(sf::Color::Black);

		if (data->currentScene != nullptr)
		{
			data->currentScene->Draw(data->window);
		}
		
		data->window.display();

		if (data->isSceneChanging && data->nextScene != nullptr && data->currentScene != nullptr)
		{
			Scene::FinalizeSceneChange(data->currentScene);
		}
	}

	return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////
