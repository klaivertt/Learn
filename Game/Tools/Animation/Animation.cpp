#include "Animation.hpp"

void Animation::Create(sf::Sprite* _sprite, int _frameCount, int _frameRate, AnimType _type, AnimDirection _dir, sf::IntRect _firstFrame)
{
	sprite = _sprite;
	start = _firstFrame;
	currentFrame = 1;
	maxFrame = _frameCount;
	frameRate = _frameRate;
	timer = 0.f;

	direction = _dir;
	type = _type;
	isFinished = false;
	reversed = false;

	_sprite->setTextureRect(_firstFrame);
}

void Animation::Update(float _dt)
{
	if (isFinished == false)
	{
		timer += _dt;
		float delay = 1.f / frameRate;
		if (timer >= delay)
		{
			switch (type)
			{
			case AnimType::LOOP:
				UpdateLoopAnim(_dt);
				break;
			case AnimType::LOOP_ONCE:
				UpdateLoopOnceAnim(_dt);
				break;
			case AnimType::BOOMERANG:
				UpdateBoomerangAnim(_dt);
				break;
			case AnimType::BOOMERANG_ONCE:
				UpdateBoomerangOnceAnim(_dt);
				break;
			default:
				break;
			}

			sf::IntRect spriteRect = sprite->getTextureRect();
			sf::IntRect newRect = spriteRect;
			if (direction == AnimDirection::HORIZONTAL)
			{
				newRect.left = start.left + (start.width * (currentFrame - 1));
				newRect.top = start.top;
			}
			else if (direction == AnimDirection::VERTICAL)
			{
				newRect.left = start.left;
				newRect.top = start.top + (start.height * (currentFrame - 1));
			}
			sprite->setTextureRect(newRect);
			timer -= delay;
		}
	}
}

void Animation::ForceFrame(int _frame)
{
	currentFrame = _frame;

	if (currentFrame >= 1 && currentFrame <= maxFrame)
	{
		if (currentFrame > maxFrame)
		{
			currentFrame = 1;
		}
		else if (currentFrame < 1)
		{
			currentFrame = maxFrame;
		}

		sf::IntRect spriteRect = sprite->getTextureRect();
		sf::IntRect newRect = spriteRect;
		if (direction == AnimDirection::HORIZONTAL)
		{
			newRect.left = start.left + (start.width * (currentFrame - 1));
			newRect.top = start.top;
		}
		else if (direction == AnimDirection::VERTICAL)
		{
			newRect.left = start.left;
			newRect.top = start.top + (start.height * (currentFrame - 1));
		}
	}
	else
	{
		std::cout << "In ForceAnimationFrame(" << _frame << ") The frame is out of range. ";
		std::cout << "So the function is cancelled" << std::endl;
	}
}

void Animation::Reset(void)
{
	currentFrame = 1;
	timer = 0.f;

	isFinished = false;
	reversed = false;
}

// Update Anim

void Animation::UpdateLoopAnim(float _dt)
{
	if (reversed)
	{
		currentFrame--;
	}
	else
	{
		currentFrame++;
	}

	if (currentFrame > maxFrame)
	{
		currentFrame = 1;
	}
	else if (currentFrame < 1)
	{
		currentFrame = maxFrame;
	}
}

void Animation::UpdateLoopOnceAnim(float _dt)
{
	if (reversed)
	{
		currentFrame--;
	}
	else
	{
		currentFrame++;
	}

	if (currentFrame > maxFrame)
	{
		currentFrame = maxFrame;
		isFinished = true;
	}
	else if (currentFrame < 1)
	{
		currentFrame = 1;
		isFinished = true;
	}
}

void Animation::UpdateBoomerangAnim(float _dt)
{
	if (reversed)
	{
		currentFrame--;
	}
	else
	{
		currentFrame++;
	}

	if (currentFrame > maxFrame)
	{
		currentFrame = maxFrame;
		reversed = true;
	}
	else if (currentFrame < 1)
	{
		currentFrame = 1;
		reversed = false;
	}
}

void Animation::UpdateBoomerangOnceAnim(float _dt)
{
	if (reversed)
	{
		currentFrame--;
	}
	else
	{
		currentFrame++;
	}

	if (currentFrame > maxFrame)
	{
		currentFrame = maxFrame;
		reversed = true;
	}
	else if (currentFrame < 1)
	{
		currentFrame = 1;
		isFinished = true;
	}
}


sf::IntRect GetFirstFrame(const char* _path, sf::Vector2i _frameNumber, sf::Vector2i _startFrame)
{
	sf::IntRect start = { 0,0,0,0 };

	sf::Texture texture;
	if (!texture.loadFromFile(_path))
	{
		return start;
	}

	sf::Vector2u textureRect = texture.getSize();
	start.left = (textureRect.x / _frameNumber.x) * _startFrame.x;
	start.top = (textureRect.y / _frameNumber.y) * _startFrame.y;
	start.width = (textureRect.x / _frameNumber.x);
	start.height = (textureRect.y / _frameNumber.y);

	return start;
}

sf::IntRect GetFirstFrame(sf::Texture& _texture, sf::Vector2i _frameNumber, sf::Vector2i _startFrame)
{
	sf::IntRect start = { 0,0,0,0 };

	sf::Vector2u textureRect = _texture.getSize();
	start.left = (textureRect.x / _frameNumber.x) * _startFrame.x;
	start.top = (textureRect.y / _frameNumber.y) * _startFrame.y;
	start.width = (textureRect.x / _frameNumber.x);
	start.height = (textureRect.y / _frameNumber.y);

	return start;
}
