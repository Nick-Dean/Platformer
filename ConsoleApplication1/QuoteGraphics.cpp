#include "stdafx.h"
#include "QuoteGraphics.h"
#include "graphics.h"
#include "Entity.h"

QuoteGraphics::QuoteGraphics()
{
}

QuoteGraphics::QuoteGraphics(Graphics & graphics) :
	AnimatedSprite(graphics, "Content/MyChar.png", 0, 0, 16, 16, 100)
{
	graphics.LoadImage("Content/MyChar.png");
	SetupAnimations();
	facing_ = Direction::RIGHT;
	PlayAnimation("IdleRight");
}

void QuoteGraphics::Draw(Graphics & graphics, int x, int y)
{
	AnimatedSprite::Draw(graphics, x, y);
}

void QuoteGraphics::Update(Entity & entity)
{
	if (entity.velocity.x > 0.0f)
	{
		facing_ = Direction::RIGHT;
		PlayAnimation("RunRight");
	}
	else if (entity.velocity.x < 0.0f)
	{
		facing_ = Direction::LEFT;
		PlayAnimation("RunLeft");
	}
	else
	{
		PlayAnimation(facing_ == Direction::RIGHT ? "IdleRight" : "IdleLeft");
	}

	AnimatedSprite::Update(entity);
}

void QuoteGraphics::AnimationDone(string currentAnimation)
{
}

void QuoteGraphics::SetupAnimations()
{
	AddAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	AddAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	AddAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	AddAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}
