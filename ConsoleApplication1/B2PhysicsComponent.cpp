#include "stdafx.h"
#include "B2PhysicsComponent.h"
#include <Box2D/Box2D.h>
#include "Entity.h"

enum FilterCategory
{
	LEVEL = 0x01,
	SOLID_OBJECT = 0x02,
	NONSOLID_OBJECT = 0x04
};


B2PhysicsComponent::B2PhysicsComponent() : scale_(1.0f)
{
}

B2PhysicsComponent::B2PhysicsComponent(b2World & world) : B2PhysicsComponent()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;

	b2Body_ = world.CreateBody(&bodyDef);
}


B2PhysicsComponent::~B2PhysicsComponent()
{
}

void B2PhysicsComponent::SetUserData(Entity & entity)
{
	b2Body_->SetUserData(&entity);
}

void B2PhysicsComponent::SetPosition(Entity & entity)
{
	b2Body_->SetTransform(b2Vec2(entity.x, entity.y), 0.0f);
}

void B2PhysicsComponent::Update(Entity & entity, World & world)
{
	entity.x = b2Body_->GetPosition().x;
	entity.y = b2Body_->GetPosition().y;
}

void B2PhysicsComponent::AddCircularFixtureToBody(float radius, float x, float y)
{
	b2CircleShape circle;
	circle.m_radius = radius * scale_;
	circle.m_p = b2Vec2(x, y);
	CreateFixture(&circle);
}

void B2PhysicsComponent::AddRectangularFixtureToBody(float width, float height)
{
	b2PolygonShape rectangle;
	rectangle.SetAsBox(width * scale_, height * scale_);
	CreateFixture(&rectangle);
}

void B2PhysicsComponent::CreateFixture(b2Shape * shape)
{
	b2FixtureDef fixtureDef;
	fixtureDef.shape = shape;
	fixtureDef.density = 1.0f;
	b2Body_->CreateFixture(&fixtureDef);
}
