#pragma once
#include "PhysicsComponent.h"
#include "Globals.h"

class b2Shape;
class Entity;
class b2Body;
class b2World;

class B2PhysicsComponent :
	public PhysicsComponent
{
public:
	B2PhysicsComponent();
	B2PhysicsComponent(b2World &world);
	~B2PhysicsComponent();

	void SetUserData(Entity& entity) override;
	void SetPosition(Entity& entity) override;

	void Update(Entity& entity, World& world) override;

	void AddCircularFixtureToBody(float radius, float x, float y);
	void AddRectangularFixtureToBody(float width, float height);

protected:
	float scale_;
	b2Body* b2Body_;

	void CreateFixture(b2Shape* shape);
};

