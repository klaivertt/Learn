#ifndef ANIMATION_H
#define ANIMATION_H

#include "Common.hpp"

typedef enum class AnimType
{
	LOOP,
	LOOP_ONCE,
	BOOMERANG,
	BOOMERANG_ONCE,

	NB_OF_DIFF_ANIM_TYPE // Keep last
}AnimType;

typedef enum class AnimDirection
{
	HORIZONTAL,
	VERTICAL
}AnimDirection;

typedef class Animation
{
public:

	// Create an animation
	// @param _sprite: Pointer to the sprite to animate
	// @param _frameCount: Total number of frames in the animation
	// @param _frameRate: Frame rate of the animation (frames per second)
	// @param _type: Type of animation (LOOP, LOOP_ONCE, BOOMERANG, BOOMERANG_ONCE)
	// @param _dir: Direction of animation frames (HORIZONTAL or VERTICAL)
	// @param _firstFrame: Rectangle defining the first frame of the animation
	void Create(sf::Sprite* _sprite, int _frameCount, int _frameRate, AnimType _type, AnimDirection _dir, sf::IntRect _firstFrame);
	
	// Update the animation based on the elapsed time
	void Update(float _dt);
	
	// Force the animation to a specific frame
	// @param _frame: Frame number to force the animation to
	void ForceFrame(int _frame);

	// Reset the animation to the first frame and initial state
	void Reset(void);
	bool isFinished = false;
private:
	void UpdateLoopAnim(float _dt);
	void UpdateLoopOnceAnim(float _dt);
	void UpdateBoomerangAnim(float _dt);
	void UpdateBoomerangOnceAnim(float _dt);

private:
	sf::Sprite* sprite = nullptr;
	sf::IntRect start;
	int currentFrame = 1;
	int maxFrame = 0;
	int frameRate = 0;
	float timer = 0.f;

	AnimDirection direction = AnimDirection::HORIZONTAL;
	AnimType type = AnimType::LOOP;
	bool reversed = false;
}Animation;

// Get the first frame rectangle from a sprite sheet
// @param _path: Path to the image file
// @param _frameNumber: Number of frames in (x, y) directions
// @param _startFrame: Starting frame index (x, y)
sf::IntRect GetFirstFrame(const char* _path, sf::Vector2i _frameNumber, sf::Vector2i _startFrame);

// Get the first frame rectangle from a sprite sheet
// @param _texture: Reference to the texture
// @param _frameNumber: Number of frames in (x, y) directions
// @param _startFrame: Starting frame index (x, y)
sf::IntRect GetFirstFrame(sf::Texture& _texture, sf::Vector2i _frameNumber, sf::Vector2i _startFrame);

#endif // !ANIMATION_H

////////////////////////////////////////////////////
//// Developped by Alex Mathieu  ///////////////////
////////////////////////////////////////////////////