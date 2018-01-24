#pragma once
#include "World.h"
#include "Entity.h"

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(Entity& entity, World& world) = 0;
};