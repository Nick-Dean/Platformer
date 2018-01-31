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
	if (input.IsKeyHeld(SDL_SCANCODE_A))
	{
		entity.velocity.x = -100000.0f;
	}
	else if (input.IsKeyHeld(SDL_SCANCODE_D))
	{
		entity.velocity.x = 100000.0f;
	}
	else
	{
		entity.velocity.x = 0.0f;
	}
}
