#pragma once

namespace Globals
{
	const float GAVITY_CONSTANT = 9.81f;
	const int MS_PER_FRAME = 16;
	const int TILE_SIZE = 16;
	const int SPRITE_SCALE = 2;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 512;
	const int PIXELS_PER_METER = 5;
}

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2
{
	int x, y; 
	Vector2() : x(0), y(0) {};
	Vector2(int x, int y) : x(x), y(y) {};

	Vector2 Zero() { return Vector2(0, 0); }
};

struct Vector2f
{
	float x, y;
	Vector2f() : x(0.0f), y(0.0f) {};
	Vector2f(float x, float y) : x(x), y(y) {};

	Vector2f Zero() { return Vector2f(0.0f, 0.0f); }
};
