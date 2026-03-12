#ifndef MENU_H
#define MENU_H

#include "Common.hpp"
#include "Tools/Scene.hpp"
#include "Tools/Miscellaneous/Sprite.hpp"

class Menu : public Scene
{
public:
	Menu();
	~Menu();
	void Load() override;
	void Update(float _dt, sf::RenderWindow& _window) override;
	void HandleEvents(sf::RenderWindow& _window) override;
	void KeyPressed(sf::Event::KeyEvent _key, sf::RenderWindow& _window) override;
	void MousePressed(sf::Event::MouseButtonEvent _mouse, sf::RenderWindow& _window) override;
	void MouseMoved(sf::Event::MouseMoveEvent _mouse, sf::RenderWindow& _window) override;
	void Draw(sf::RenderWindow& _window) override;
private:
	GameData* data = nullptr;

	Sprite background;

	Text titleText;

	Text startText;
	Text exitText;
	sf::RectangleShape startButton;
	sf::RectangleShape exitButton;

	void LoadButtons(void);
	void CheckButtonHover(sf::Vector2i _mousePos);
	void CheckButtonClick(sf::Vector2i _mousePos);
};

#endif // !MENU_H
