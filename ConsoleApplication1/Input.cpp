#include "stdafx.h"
#include "Input.h"

void Input::BeginNewFrame()
{
	pressedKeys_.clear();
	releasedKeys_.clear();
}

void Input::KeyDownEvent(const SDL_Event& event)
{
	pressedKeys_[event.key.keysym.scancode] = true;
	heldKeys_[event.key.keysym.scancode] = true;
}

void Input::KeyUpEvent(const SDL_Event& event)
{
	releasedKeys_[event.key.keysym.scancode] = true;
	heldKeys_[event.key.keysym.scancode] = false;
}

bool Input::WasKeyPressed(SDL_Scancode key)
{
	return pressedKeys_[key];
}

bool Input::IsKeyHeld(SDL_Scancode key)
{
	return heldKeys_[key];
	
}

bool Input::WasKeyReleased(SDL_Scancode key)
{
	return releasedKeys_[key];
}

