#pragma once
#include "AnimatedSprite.h"
#include "Globals.h"

class QuoteGraphics :
	public AnimatedSprite
{
public:
	QuoteGraphics();
	QuoteGraphics(Graphics &graphics);

	void Draw(Graphics& graphics, int x, int y) override;
	void Update(Entity& entity) override;

	void AnimationDone(string currentAnimation) override;
	void SetupAnimations() override;

private:
	Direction facing_;
};

