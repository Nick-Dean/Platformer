#include "stdafx.h"
#include "QuotePhysics.h"
#include <Box2D/Box2D.h>
#include "Entity.h"


QuotePhysics::QuotePhysics()
{
}

QuotePhysics::QuotePhysics(b2World & world) : B2PhysicsComponent(world)
{
	AddRectangularFixtureToBody(0.5f, 0.5f);
	//AddCircularFixtureToBody(0.5f, 0, 0.5f);
	b2Body_->SetBullet(true);
}


QuotePhysics::~QuotePhysics()
{
}

void QuotePhysics::Update(Entity & entity, World & world)
{
	auto currentVelocity = b2Body_->GetLinearVelocity();
	auto desiredVelocity = 0.0f, xImpulse = 0.0f, yImpulse = 0.0f;

	if (entity.velocity.x > 0)
	{
		desiredVelocity = b2Max(currentVelocity.x + 0.1f, 10.0f);
	}
	else if (entity.velocity.x < 0)
	{
		desiredVelocity = b2Max(currentVelocity.x - 0.1f, -10.0f);
	}
	else
	{
		desiredVelocity = currentVelocity.x * 0.9f;
	}

	if (entity.velocity.y < 0.0f)
	{ 
		yImpulse = b2Body_->GetMass() * 10;
	}

	auto deltaVelocity = desiredVelocity - currentVelocity.x;
	xImpulse = b2Body_->GetMass() * deltaVelocity;
	b2Body_->ApplyLinearImpulseToCenter(b2Vec2(xImpulse, -yImpulse), true);

	entity.x = b2Body_->GetPosition().x * (Globals::PIXELS_PER_METER * Globals::SPRITE_SCALE) - Globals::TILE_SIZE;
	entity.y = b2Body_->GetPosition().y * (Globals::PIXELS_PER_METER * Globals::SPRITE_SCALE) - Globals::TILE_SIZE;
}