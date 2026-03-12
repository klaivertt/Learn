#include "Menu.hpp"
#include "Tools/GameData.hpp"
#include "Tools/Debug/DebugViewer.hpp"
#include "../Game/Game.hpp"
#include "Tools/Debug/Logger.hpp"
#include "Tools/Miscellaneous/Text.hpp"

Menu::Menu()
{
	Load();
}

Menu::~Menu()
{
	Logger::Info("Menu Scene Unloaded.", false);
}

void Menu::Load()
{
	data = GameData::GetInstance();

	titleText.Create(FontType::BOLD, Vec2(0.5f), sf::Color::White, 44);
	titleText.SetString(data->screen.name);
	titleText.SetPosition(Vec2(data->screen.width / 2, data->screen.height * 0.2f));

	LoadButtons();

	Logger::Success("Menu Scene Loaded.", true);
}

void Menu::Update(float _dt, sf::RenderWindow& _window)
{
	data->debugViewer.Update(_dt);
}

void Menu::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Logger::Info("Changing to Game Scene.", false);
		// Change to Game Scene
		changeScene = true;
	}
}

void Menu::MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window)
{
	if (_mouse.button == sf::Mouse::Left)
	{
		CheckButtonClick(sf::Vector2i(_mouse.x, _mouse.y));
		//_data->logger->Info("Mouse Left Button Clicked at (" + std::to_string(mouse.x) + ", " + std::to_string(mouse.y) + ")", false);
	}
	else if (_mouse.button == sf::Mouse::Right)
	{
		// Right click actions (if any)
	}
}

void Menu::MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window)
{
	CheckButtonHover(sf::Vector2i(_mouse.x, _mouse.y));
}

void Menu::Draw(sf::RenderWindow& _window)
{
	background.Draw(&_window);
	titleText.Draw(_window);
	_window.draw(exitButton);
	_window.draw(startButton);
	startText.Draw(_window);
	exitText.Draw(_window);

	data->debugViewer.Draw(_window);
}

void Menu::LoadButtons(void)
{
	startText.Create(FontType::NORMAL, Vec2(0.5f),sf::Color::White, 22);
	startText.SetString("START");
	startText.SetPosition(Vec2(data->screen.width / 2, (data->screen.height / 2) - 8.f));

	exitText.Create(FontType::NORMAL, Vec2(0.5f),sf::Color::White, 22);
	exitText.SetPosition(Vec2(data->screen.width / 2, data->screen.height / 2 + 70.f));
	exitText.SetString("EXIT");

	sf::Vector2f buttonSize = sf::Vector2f(startText.GetLocalBounds().width + 20.f, startText.GetLocalBounds().height + 20.f);

	startButton.setSize(buttonSize);
	startButton.setFillColor(sf::Color(100, 100, 100));
	startButton.setOutlineThickness(2.f);
	startButton.setOutlineColor(sf::Color::White);

	//center the button
	startButton.setOrigin(buttonSize.x / 2, buttonSize.y / 2);

	sf::Vector2f startButtonPos = Vec2(startText.GetPosition());
	startButtonPos.y += buttonSize.y / 4;
	startButton.setPosition(startButtonPos);


	buttonSize = sf::Vector2f(exitText.GetLocalBounds().width + 20.f, exitText.GetLocalBounds().height + 20.f);
	exitButton.setSize(buttonSize);
	exitButton.setFillColor(sf::Color(100, 100, 100));
	exitButton.setOutlineThickness(2.f);
	exitButton.setOutlineColor(sf::Color::White);

	//center the button
	exitButton.setOrigin(buttonSize.x / 2, buttonSize.y / 2);

	sf::Vector2f exitButtonPos = Vec2(exitText.GetPosition());
	exitButtonPos.y += buttonSize.y / 4;
	exitButton.setPosition(exitButtonPos);
}

void Menu::CheckButtonHover(sf::Vector2i _mousePos)
{
	
}

void Menu::CheckButtonClick(sf::Vector2i _mousePos)
{
	if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		Logger::Info("Start Button Clicked. Changing to Game Scene.", false);
		// Change to Game Scene
		changeScene = true;
	}
	if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		Logger::Info("Exit Button Clicked. Exiting Game.", false);
		exit(EXIT_SUCCESS);
	}
}
