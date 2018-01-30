#pragma once
#include "Sprite.h"
#include <string>
#include <map>
#include <vector>
#include "Globals.h"

class Graphics;

using namespace std;

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const string &filePath, int sourceX, int sourceY, int width, int height, float timeToUpdate);

	// Once = true is for looping animations
	void PlayAnimation(string animation, bool once = false);

	void Update(Entity& entity) override;

	void Draw(Graphics &graphics, int x, int y) override;

protected:
	double timeToUpdate_;
	bool currentAnimationOnce_;
	string currentAnimation_;

	void AddAnimation(int frames, int x, int y, string name, int width, int height, Vector2 offset);

	virtual void SetupAnimations() = 0;

	void ResetAnimations();

	void StopAnimation();

	void SetVisible(bool visible);

	virtual void AnimationDone(string currentAnimation) = 0;

private:
	map<string, vector<SDL_Rect>> animations_;
	map<string, Vector2> offsets_;

	int frameIndex_;
	double timeElapsed_;
	bool visible_;
};

