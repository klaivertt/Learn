#include "PollEvent.h"
#include "../Tools/Debug/DebugViewer.h"
#include "../Tools/Debug/Logger.h"
#include "../Tools/Particle.h"
// Forward declarations

void KeyPressed(sf::RenderWindow* const _renderWindow, sf::Event::KeyEvent _key);
//////////////////////////////////////////////////////////////////////////////////////////////////


void PollEvent(sf::RenderWindow* const _renderWindow, Scene* _scene)
{
	sf::Event event;
	while (_renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_renderWindow->close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			_scene->KeyPressed(event.key, *_renderWindow);
			KeyPressed(_renderWindow, event.key);
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			_scene->MousePressed(event.mouseButton, *_renderWindow);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			_scene->MouseMoved(event.mouseMove, *_renderWindow);
		}
	}
}

void KeyPressed(sf::RenderWindow* const _renderWindow, sf::Event::KeyEvent _key)
{
}

