#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "GraphicsComponent.h"

class Graphics;

using namespace std;

class Sprite : public GraphicsComponent
{
public:
	Sprite();
	Sprite(Graphics &graphics, const string &filePath, int sourceX, int sourceY, int width, int height);
	~Sprite();
	
	void Update(Entity& entity) override;

	void Draw(Graphics &graphics, int x, int y) override;

protected:
	double x_, y_;
	SDL_Rect sourceRectangle_;
	SDL_Texture* spriteSheet_;

private:
};

