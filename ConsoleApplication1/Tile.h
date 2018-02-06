#pragma once
#include "Globals.h"

struct SDL_Texture;
class Graphics;
class Camera;

class Tile
{
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	~Tile();

	void Update();
	void Draw(Graphics &graphics, Camera &camera);

	Vector2 GetPosition() { return position_; }

private:
	SDL_Texture * tileset_;
	Vector2 size_;
	Vector2 tilesetPosition_;
	Vector2 position_;
};

