#include "Tools/Common.h"
#include "Core/Init.h"
#include "Core/PollEvent.h"
#include "Core/Game/Game.h"
#include "Core/Menu/Menu.h"
#include "Tools/GameData.h"


int main()
{
	GameData* data = GameData::GetInstance();

    Init(data);
	sf::Clock deltaTime;
	while (data->window.isOpen())
	{
		float dt = deltaTime.restart().asSeconds();

		PollEvent(&data->window, data->currentScene);

		data->currentScene->Update(dt, data->window);

		data->window.clear(sf::Color::Black);
		data->currentScene->Draw(data->window);
		data->window.display();
	}

	return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////
