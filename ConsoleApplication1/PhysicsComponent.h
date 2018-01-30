#pragma once

class Entity;
class World;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}

	virtual void SetUserData(Entity& entity) = 0;
	virtual void SetPosition(Entity& entity) = 0;
	virtual void Update(Entity& entity, World& world) = 0;
};