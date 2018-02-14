#include "stdafx.h"
#include "PlayerInputComponent.h"
#include "Entity.h"
#include "Input.h"

PlayerInputComponent::PlayerInputComponent()
{
}


PlayerInputComponent::~PlayerInputComponent()
{
}

void PlayerInputComponent::Update(Input & input, Entity & entity)
{
	entity.velocity.x = 0.0f;
	entity.velocity.y = 0.0f;

	if (input.IsKeyHeld(SDL_SCANCODE_A))
	{
		entity.velocity.x = -2.6f;
	}
	if (input.IsKeyHeld(SDL_SCANCODE_D))
	{
		entity.velocity.x = 2.6f;
	}
	if (input.IsKeyHeld(SDL_SCANCODE_SPACE))
	{
		entity.velocity.y = -10.0f;
	}
}
