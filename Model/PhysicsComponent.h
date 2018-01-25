#pragma once

class Entity;
class World;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(Entity& entity, World& world) = 0;
};