#include "PollEvent.hpp"

void PollEvent(sf::RenderWindow& const _renderWindow, Scene& _scene)
{
	sf::Event event;
	while (_renderWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_renderWindow.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			_scene.KeyPressed(event.key, _renderWindow);
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			_scene.MousePressed(event.mouseButton, _renderWindow);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			_scene.MouseMoved(event.mouseMove, _renderWindow);
		}
	}
}

