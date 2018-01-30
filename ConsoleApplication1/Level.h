#pragma once
#include <string>
#include "Globals.h"
#include "Tile.h"
#include <vector>

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;


using namespace std;

class Level
{
public:
	Level();
	Level(string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();

	void Update();
	void Draw(Graphics &graphics);

private:
	string mapName_;
	Vector2 spawnPoint_;

	Vector2 size_;
	Vector2 tileSize_;

	SDL_Texture* backgroundTexture_;

	vector<Tile> tileList_;
	vector<Tileset> tileSets_;


	void LoadMap(string mapName, Graphics &graphics);
};

struct Tileset
{
	SDL_Texture* texture;
	int firstGid;

	Tileset()
	{
		firstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid)
	{
		this->texture = texture;
		this->firstGid = firstGid;
	}
};
