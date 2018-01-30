#pragma once
#include "B2PhysicsComponent.h"

class b2World;
class Entity;

class QuotePhysics :
	public B2PhysicsComponent
{
public:
	QuotePhysics();
	QuotePhysics(b2World &world);
	~QuotePhysics();

	void Update(Entity& entity, World& world) override;
};

