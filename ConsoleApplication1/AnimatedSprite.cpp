#include "stdafx.h"
#include "AnimatedSprite.h"
#include "graphics.h"


AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(Graphics & graphics, const string & filePath, int sourceX, int sourceY, int width, int height, float timeToUpdate) : 
	Sprite(graphics, filePath, sourceX, sourceY, width, height), 
	frameIndex_(0),
	timeToUpdate_(timeToUpdate),
	visible_(true),
	currentAnimationOnce_(false),
	currentAnimation_("")
{
}

void AnimatedSprite::AddAnimation(int frames, int x, int y, string name, int width, int height, Vector2 offset)
{
	vector<SDL_Rect> rectangles;

	for (auto i = 0; i < frames; ++i)
	{
		SDL_Rect newRect = { (i + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}

	animations_.insert(pair<string, vector<SDL_Rect>>(name, rectangles));
	offsets_.insert(pair<string, Vector2>(name, offset));
}

void AnimatedSprite::ResetAnimations()
{
	animations_.clear();
	offsets_.clear();
}

void AnimatedSprite::StopAnimation()
{
	frameIndex_ = 0;
	AnimationDone(currentAnimation_);
}

void AnimatedSprite::SetVisible(bool visible)
{
	visible_ = visible;
}

void AnimatedSprite::AnimationDone(string currentAnimation)
{

}

void AnimatedSprite::PlayAnimation(string animation, bool once)
{
	currentAnimationOnce_ = once;

	if (currentAnimation_ != animation)
	{
		currentAnimation_ = animation;
		frameIndex_ = 0;
	}
}

void AnimatedSprite::Update(Entity & entity)
{
	Sprite::Update(entity);

	timeElapsed_ += Globals::MS_PER_FRAME;
	
	if (timeElapsed_ >= timeToUpdate_)
	{
		timeElapsed_ -= timeToUpdate_;

		if (frameIndex_ < animations_[currentAnimation_].size() - 1)
		{
			frameIndex_++;
		}
		else
		{
			if (currentAnimationOnce_)
			{
				SetVisible(false);
			}
			frameIndex_ = 0;
			AnimationDone(currentAnimation_);
		}
	}
}

void AnimatedSprite::Draw(Graphics& graphics, int x, int y)
{
	if (visible_)
	{
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + offsets_[currentAnimation_].x;
		destinationRectangle.y = y + offsets_[currentAnimation_].y;
		destinationRectangle.w = sourceRectangle_.w * Globals::SPRITE_SCALE;
		destinationRectangle.h = sourceRectangle_.h * Globals::SPRITE_SCALE;

		SDL_Rect sourceRect = animations_[currentAnimation_][frameIndex_];
		graphics.BlitSurface(spriteSheet_, &sourceRect, &destinationRectangle);
	}
}
