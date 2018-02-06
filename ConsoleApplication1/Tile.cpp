#include "stdafx.h"
#include "Tile.h"
#include "graphics.h"
#include "Camera.h"
#include <SDL2/SDL.h>

Tile::Tile()
{
}

Tile::Tile(SDL_Texture * tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) : tileset_(tileset), size_(size), tilesetPosition_(tilesetPosition), 
	position_(Vector2(position.x * Globals::SPRITE_SCALE, position.y * Globals::SPRITE_SCALE)) 
{

}


Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Draw(Graphics & graphics, Camera &camera)
{
	SDL_Rect destRect = { position_.x - camera.GetRectangle().x , position_.y - camera.GetRectangle().y, size_.x * Globals::SPRITE_SCALE, size_.y * Globals::SPRITE_SCALE };
	SDL_Rect sourceRect = { tilesetPosition_.x, tilesetPosition_.y, size_.x, size_.y };

	graphics.BlitSurface(tileset_, &sourceRect, &destRect);
}
