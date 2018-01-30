#pragma once
#include <map>
#include <SDL2/SDL.h>

using namespace std;

class Input
{
public:
	void BeginNewFrame();
	void KeyUpEvent(const SDL_Event& event);
	void KeyDownEvent(const SDL_Event& event);

	bool WasKeyPressed(SDL_Scancode key);
	bool WasKeyReleased(SDL_Scancode key);
	bool IsKeyHeld(SDL_Scancode key);

private:
	map<SDL_Scancode, bool> heldKeys_;
	map<SDL_Scancode, bool> pressedKeys_;
	map<SDL_Scancode, bool> releasedKeys_;
};

