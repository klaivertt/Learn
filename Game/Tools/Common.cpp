#include "Common.h"
#include "GameData.h"

sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _divide)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTex = new sf::Texture();

	tempTex->loadFromFile(_path);
	tempSprite.setTexture(*tempTex);

	sf::Vector2u tempTaille = tempTex->getSize();
	sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x * _divide.x, tempTaille.y * _divide.y);
	tempSprite.setOrigin(tempOrigin);
	return tempSprite;
}

sf::Sprite LoadSprite(sf::Texture& _texture, sf::Vector2f _divide)
{
	sf::Sprite tempSprite;

	tempSprite.setTexture(_texture);

	sf::Vector2u tempTaille = _texture.getSize();
	sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x * _divide.x, tempTaille.y * _divide.y);
	tempSprite.setOrigin(tempOrigin);

	return tempSprite;
}

sf::Sprite LoadSprite(sf::Texture& _texture)
{
	sf::Sprite tempSprite;
	tempSprite.setTexture(_texture);
	return tempSprite;
}

sf::Sprite LoadSprite(const std::string _path)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTex = new sf::Texture();
	tempTex->loadFromFile(_path);
	tempSprite.setTexture(*tempTex);
	return tempSprite;
}

sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _divide, sf::IntRect _rect)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTex = new sf::Texture();
	tempTex->loadFromFile(_path);
	tempSprite.setTexture(*tempTex);
	tempSprite.setTextureRect(_rect);
	sf::Vector2f tempOrigin = sf::Vector2f(_rect.width * _divide.x, _rect.height * _divide.y);
	tempSprite.setOrigin(tempOrigin);
	return tempSprite;
}

sf::Sprite LoadSprite(sf::Texture& _texture, sf::Vector2f _pos, sf::Vector2f _divide)
{
	sf::Sprite tempSprite;
	tempSprite.setTexture(_texture);
	sf::Vector2u tempTaille = _texture.getSize();
	sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x * _divide.x, tempTaille.y * _divide.y);
	tempSprite.setOrigin(tempOrigin);
	tempSprite.setPosition(_pos);
	return tempSprite;
}

sf::Sprite LoadSprite(const std::string _path, sf::Vector2f _pos, sf::Vector2f _divide)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTex = new sf::Texture();
	tempTex->loadFromFile(_path);
	tempSprite.setTexture(*tempTex);
	sf::Vector2u tempTaille = tempTex->getSize();
	sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x * _divide.x, tempTaille.y * _divide.y);
	tempSprite.setOrigin(tempOrigin);
	tempSprite.setPosition(_pos);
	return tempSprite;
}

sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, Anchor _anchor, sf::Vector2f _decal)
{
	sf::Text text;
	text.setFont(_font);
	text.setString(_str);
	sf::Vector2f pos;
	GameData* gameData = GameData::GetInstance();
	Screen screen = gameData->screen;
	switch (_anchor)
	{
	case TOP_LEFT:
		pos = sf::Vector2f(20, 20);
		break;
	case TOP_CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, 20);
		break;
	case TOP_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, 20);
		break;
	case CENTER_LEFT:
		pos = sf::Vector2f(20, screen.width / 2 - text.getLocalBounds().height / 2);
		break;
	case CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, screen.height / 2 - text.getLocalBounds().height / 2);
		break;
	case CENTER_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, screen.height / 2 - text.getLocalBounds().height / 2);
		break;
	case BOTTOM_LEFT:
		pos = sf::Vector2f(20, screen.width - text.getLocalBounds().height - 20);
		break;
	case BOTTOM_CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, screen.height - text.getLocalBounds().height - 20);
		break;
	case BOTTOM_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, screen.height - text.getLocalBounds().height - 20);
		break;
	default:
		pos = sf::Vector2f(20, 20);
		break;
	}
	text.setPosition(pos + _decal);

	return text;
}

sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, sf::Vector2f _pos, sf::Vector2f _divide)
{
	sf::Text text;
	text.setFont(_font);
	text.setString(_str);
	text.setCharacterSize(_size);
	//set Origin
	sf::Vector2f origin = sf::Vector2f(text.getLocalBounds().width * _divide.x, text.getLocalBounds().height * _divide.y);
	text.setOrigin(origin);
	text.setPosition(_pos);
	return text;
}

sf::Text CreateText(const std::string& _str, sf::Font& _font, int _size, sf::Vector2f _pos)
{
	sf::Text text;
	text.setFont(_font);
	text.setString(_str);
	text.setPosition(_pos);
	text.setCharacterSize(_size);
	return text;
}

void SetText(sf::Text& _text, const std::string& _str, Anchor _anchor, sf::Vector2f _decal)
{
	sf::Text& text = _text;

	text.setString(_str);

	sf::Vector2f pos;	
	GameData* gameData = GameData::GetInstance();
	Screen screen = gameData->screen;
	switch (_anchor)
	{
	case TOP_LEFT:
		pos = sf::Vector2f(20, 20);
		break;
	case TOP_CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, 20);
		break;
	case TOP_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, 20);
		break;
	case CENTER_LEFT:
		pos = sf::Vector2f(20, screen.width / 2 - text.getLocalBounds().height / 2);
		break;
	case CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, screen.height / 2 - text.getLocalBounds().height / 2);
		break;
	case CENTER_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, screen.height / 2 - text.getLocalBounds().height / 2);
		break;
	case BOTTOM_LEFT:
		pos = sf::Vector2f(20, screen.width - text.getLocalBounds().height - 20);
		break;
	case BOTTOM_CENTER:
		pos = sf::Vector2f(screen.width / 2 - text.getLocalBounds().width / 2, screen.height - text.getLocalBounds().height - 20);
		break;
	case BOTTOM_RIGHT:
		pos = sf::Vector2f(screen.width - text.getLocalBounds().width - 20, screen.height - text.getLocalBounds().height - 20);
		break;
	default:
		pos = sf::Vector2f(20, 20);
		break;
	}
	text.setPosition(pos + _decal);
}

void SetText(sf::Text& _text, const std::string& _str, sf::Vector2f _pos, sf::Vector2f _divide)
{
	sf::Text& text = _text;
	text.setString(_str);

	//set Origin
	sf::Vector2f origin = sf::Vector2f(text.getLocalBounds().width * _divide.x, text.getLocalBounds().height * _divide.y);
	text.setOrigin(origin);
	text.setPosition(_pos);
}

void SetText(sf::Text& _text, const std::string& _str, sf::Vector2f _pos)
{
	sf::Text& text = _text;
	text.setString(_str);
	text.setPosition(_pos);
}

void SetText(sf::Text& _text, const std::string& _str)
{
	sf::Text& text = _text;
	text.setString(_str);
}

float RandF(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

int RandI(int min, int max)
{
	return min + rand() % (max - min + 1);
}

float DistF(sf::Vector2f _a, sf::Vector2f _b)
{
	return static_cast<float>(sqrt(pow(_b.x - _a.x, 2) + pow(_b.y - _a.y, 2)));
}

int DistI(sf::Vector2i _a, sf::Vector2i _b)
{
	return static_cast<int>(sqrt(pow(_b.x - _a.x, 2) + pow(_b.y - _a.y, 2)));
}

sf::Vector2f Normalize(int _x, int _y)
{
	float length = static_cast<float>(sqrt(_x * _x + _y * _y));
	return sf::Vector2f(_x / length, _y / length);
}

sf::Vector2f Normalize(sf::Vector2f _vec)
{
	float length = sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
	return sf::Vector2f(_vec.x / length, _vec.y / length);
}

sf::Vector2i NormalizeI(float _x, float _y)
{
	int length = static_cast<int>(sqrt(_x * _x + _y * _y));
	return sf::Vector2i(static_cast<int>(_x / length), static_cast<int>(_y / length));
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _scale, float _angle, sf::RenderWindow& _render)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_sprite.setScale(sf::Vector2f(_scale, _scale));
	_render.draw(_sprite);
}

// copy/paste of the blitsprite :)
void BlitText(sf::Text _text, sf::Vector2f _pos, float _angle, sf::RenderWindow& _render)
{
	_text.setRotation(_angle);
	_text.setPosition(_pos);
	_render.draw(_text);
}

sf::Vector2f World2Screen(b2Vec2 _worldPos, sf::Vector2f _cam)
{
	sf::Vector2f screenPos = sf::Vector2f(_worldPos.x - _cam.x, _worldPos.y - _cam.y);

	screenPos.y = -screenPos.y; //Inversion de l'axe Y pour coller à box2D
	screenPos.x *= ZOOM;
	screenPos.y *= ZOOM;

	return screenPos;
}
