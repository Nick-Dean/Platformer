#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include "Entity.h"
#include "Level.h"
#include <SDL2\SDL.h>

Camera::Camera()
{
	rectangle_.h = Globals::SCREEN_HEIGHT;
	rectangle_.w = Globals::SCREEN_WIDTH;
	rectangle_.x = 0;
	rectangle_.y = 0;
}

void Camera::SetLevelSize(Vector2 &levelSize)
{
	levelWidth_ = levelSize.x * 16 * 2;
	levelHeight_ = levelSize.y * 16 * 2;
}

void Camera::Update(Entity& player)
{
	rectangle_.x = player.x + 8 - Globals::SCREEN_WIDTH / 2;
	rectangle_.y = player.y + 8 - Globals::SCREEN_HEIGHT / 2;;

	if (rectangle_.x < 0)
	{
		rectangle_.x = 0;
	}
	if (rectangle_.y < 0)
	{
		rectangle_.y = 0;
	}
	if (rectangle_.x > levelWidth_ - rectangle_.w)
	{
		rectangle_.x = levelWidth_ - rectangle_.w;
	}
	if (rectangle_.y > levelHeight_ - rectangle_.h)
	{
		rectangle_.y = levelHeight_ - rectangle_.h;
	}
}
