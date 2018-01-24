#pragma once
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class Entity
{
public:
	double velocity;
	double x, y;

	Entity(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics)
		: input_(input),
		physics_(physics),
		graphics_(graphics)
	{}

	void Update(World& world)
	{
		input_->Update(*this);
		physics_->Update(*this, world);
		graphics_->Update(*this);
	}

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};
