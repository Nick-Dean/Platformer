#pragma once
#include "Globals.h"
#include <SDL2/SDL.h>

class Entity;
class Level;

class Camera
{
public:
	Camera();

	void Update(Entity& player);

	void SetLevelSize(Vector2 &levelSize);

	SDL_Rect GetRectangle() { return rectangle_; }

private:
	int levelWidth_;
	int levelHeight_;
	SDL_Rect rectangle_;
};

