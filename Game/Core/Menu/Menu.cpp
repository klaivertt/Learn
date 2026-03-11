#include "Menu.h"
#include "../../Tools/GameData.h"
#include "../../Tools/Debug/DebugViewer.h"
#include "../Game/Game.h"
#include "../../Tools/Debug/Logger.h"
#include "../../Tools/AssetManager.h"

Menu::Menu()
{
	Load();
}

Menu::~Menu()
{
	// Cleanup if necessary
	backgroundTexture.~Texture();

	_data->logger->Info("Menu Scene Unloaded.", false);
}

void Menu::Load()
{
	_data = GameData::GetInstance();
	titleText = CreateText(_data->screen.name, _data->font, 40, sf::Vector2f(800.f, 100.f), sf::Vector2f(0.5f, 0.5f));

	LoadButtons();

	backgroundTexture.loadFromFile("Assets/Background.png");
	background = LoadSprite(backgroundTexture, sf::Vector2f(0.f, 0.f));

	_data->logger->Success("Menu Scene Loaded.", true);
}

void Menu::Update(float _dt, sf::RenderWindow& _window)
{
	_data->debugViewer->Update(_dt);

	if (changeScene)
	{
		Scene* temp = _data->currentScene;
		_data->currentScene = new Game();
		temp->~Scene();
	}
}

void Menu::KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_data->logger->Info("Changing to Game Scene.", false);
		// Change to Game Scene
		changeScene = true;
		_data->currentScene = new Game();
		delete this;
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
	_window.draw(background);
	_window.draw(titleText);
	_window.draw(startButton);
	_window.draw(startText);
	_window.draw(exitButton);
	_window.draw(exitText);

	_data->debugViewer->Draw(_window);
}

void Menu::LoadButtons(void)
{
	startText = CreateText("START", _data->font, 30, sf::Vector2f(_data->screen.width / 2, _data->screen.height / 2 - 7.f), sf::Vector2f(0.5f, 0.5f));
	exitText = CreateText("EXIT", _data->font, 30, sf::Vector2f(_data->screen.width / 2, _data->screen.height / 2 + 93.f), sf::Vector2f(0.5f, 0.5f));

	sf::Vector2f buttonSize = sf::Vector2f(startText.getLocalBounds().width + 20.f, startText.getLocalBounds().height + 20.f);

	startButton.setSize(buttonSize);
	startButton.setFillColor(sf::Color(100, 100, 100));
	startButton.setOutlineThickness(2.f);
	startButton.setOutlineColor(sf::Color::White);

	//center the button
	startButton.setOrigin(buttonSize.x / 2, buttonSize.y / 2);

	sf::Vector2f startButtonPos = sf::Vector2f(_data->screen.width / 2, _data->screen.height / 2);
	startButton.setPosition(startButtonPos);


	buttonSize = sf::Vector2f(exitText.getLocalBounds().width + 20.f, exitText.getLocalBounds().height + 20.f);
	exitButton.setSize(buttonSize);
	exitButton.setFillColor(sf::Color(100, 100, 100));
	exitButton.setOutlineThickness(2.f);
	exitButton.setOutlineColor(sf::Color::White);

	//center the button
	exitButton.setOrigin(buttonSize.x / 2, buttonSize.y / 2);

	sf::Vector2f exitButtonPos = sf::Vector2f(_data->screen.width / 2, _data->screen.height / 2 + 100.f);
	exitButton.setPosition(exitButtonPos);

	_data->logger->Rect(startButton.getGlobalBounds(), "Start Button Bounds");
}

void Menu::CheckButtonHover(sf::Vector2i _mousePos)
{
	if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		startButton.setFillColor(sf::Color(150, 150, 150));
	}
	else
	{
		startButton.setFillColor(sf::Color(100, 100, 100));
	}

	if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		exitButton.setFillColor(sf::Color(150, 150, 150));
	}
	else
	{
		exitButton.setFillColor(sf::Color(100, 100, 100));
	}
}

void Menu::CheckButtonClick(sf::Vector2i _mousePos)
{
	if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		_data->logger->Info("Start Button Clicked. Changing to Game Scene.", false);
		// Change to Game Scene
		changeScene = true;
		_data->currentScene = new Game();
		delete this;
		//gameScene->Load();
	}
	if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
	{
		_data->logger->Info("Exit Button Clicked. Exiting Game.", false);
		exit(EXIT_SUCCESS);
	}
}
