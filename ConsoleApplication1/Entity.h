#pragma once
#include "Globals.h"

class World;
class Input;
class Graphics;
class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class Entity
{
public:
	Vector2f velocity;
	double x, y;

	Entity();
	Entity(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics);

	void Update(Input& input, World& world);

	void Draw(Graphics &graphics);

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};

