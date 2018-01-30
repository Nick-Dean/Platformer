#include "stdafx.h"
#include "QuotePhysics.h"
#include <Box2D/Box2D.h>
#include "Entity.h"


QuotePhysics::QuotePhysics()
{
}

QuotePhysics::QuotePhysics(b2World & world) : B2PhysicsComponent(world)
{
	AddRectangularFixtureToBody(1.0f, 0.5f);
	AddCircularFixtureToBody(1.0f, 0, -0.5f);
	b2Body_->SetBullet(true);
}


QuotePhysics::~QuotePhysics()
{
}

void QuotePhysics::Update(Entity & entity, World & world)
{
	b2Body_->ApplyLinearImpulseToCenter(b2Vec2(entity.velocity.x, entity.velocity.y), true);

	entity.x = b2Body_->GetPosition().x;
	entity.y = b2Body_->GetPosition().y;
}
