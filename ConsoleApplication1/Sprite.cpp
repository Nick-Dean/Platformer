#include "stdafx.h"
#include "Sprite.h"
#include "graphics.h"
#include "Entity.h"
#include "Globals.h"


Sprite::Sprite()
{
}

Sprite::Sprite(Graphics & graphics, const string & filePath, int sourceX, int sourceY, int width, int height)
{
	sourceRectangle_.x = sourceX;
	sourceRectangle_.y = sourceY;
	sourceRectangle_.w = width;
	sourceRectangle_.h = height;

	spriteSheet_ = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(filePath));
	if (spriteSheet_ == nullptr)
	{
		//throw exception
	}
}

Sprite::~Sprite()
{
	
}

void Sprite::Draw(Graphics& graphics, int x, int y)
{
	SDL_Rect destinationRectangle = { x, y, sourceRectangle_.w * Globals::SPRITE_SCALE, sourceRectangle_.h * Globals::SPRITE_SCALE };
	graphics.BlitSurface(spriteSheet_, &sourceRectangle_, &destinationRectangle);
}


void Sprite::Update(Entity& entity)
{
	x_ = entity.x;
	y_ = entity.y;
}
