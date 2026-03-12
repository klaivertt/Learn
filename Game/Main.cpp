#include "Common.hpp"
#include "Core/Init.hpp"
#include "Core/PollEvent.hpp"
#include "Tools/GameData.hpp"
#include "Tools/Scene.hpp"


int main()
{
	GameData* data = GameData::GetInstance();

    Init(*data);
	sf::Clock deltaTime;
	while (data->window.isOpen())
	{
		float dt = deltaTime.restart().asSeconds();

		if (data->currentScene != nullptr)
		{
		PollEvent(data->window, *data->currentScene);
		}

		data->currentScene->Update(dt, data->window);

		data->window.clear(sf::Color::Black);
		data->currentScene->Draw(data->window);
		data->window.display();
	}

	return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////
