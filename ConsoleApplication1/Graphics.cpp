#include "stdafx.h"
#include "graphics.h"
#include "Globals.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0, &window_, &renderer_);
	SDL_SetWindowTitle(window_, "Platformer");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
}

SDL_Surface * Graphics::LoadImage(const string & filePath)
{
	if (spriteSheets_.count(filePath) == 0)
	{
		spriteSheets_[filePath] = IMG_Load(filePath.c_str());
	}

	return spriteSheets_[filePath];
}

void Graphics::BlitSurface(SDL_Texture * texture, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle)
{
	SDL_RenderCopy(renderer_, texture, sourceRectangle, destinationRectangle);
}

void Graphics::Flip()
{
	SDL_RenderPresent(renderer_);
}

void Graphics::Clear()
{
	SDL_RenderClear(renderer_);
}

SDL_Renderer* Graphics::GetRenderer() const
{
	return renderer_;
}

