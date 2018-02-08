#include "stdafx.h"
#include "Entity.h"
#include "World.h"
#include "Input.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "Camera.h"

Entity::Entity()
{
}

Entity::Entity(InputComponent * input, PhysicsComponent * physics, GraphicsComponent * graphics)
	: velocity(0.0f, 0.0f), x(100), y(100),
	input_(input),
	physics_(physics),
	graphics_(graphics)
{
	physics_->SetUserData(*this);
	physics_->SetPosition(*this);
}

void Entity::Update(Input& input, World & world)
{
	input_->Update(input, *this);
	physics_->Update(*this, world);
	graphics_->Update(*this);
}

void Entity::Draw(Graphics & graphics, Camera &camera)
{
	graphics_->Draw(graphics, x - camera.GetRectangle().x, y - camera.GetRectangle().y);
}
