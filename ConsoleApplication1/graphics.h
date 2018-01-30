#pragma once
#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

using namespace std;

class Graphics
{
public:
	Graphics();
	~Graphics();

	SDL_Surface* LoadImage(const string &filePath);

	void BlitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	void Flip();

	void Clear();

	SDL_Renderer* GetRenderer() const;

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	map<string, SDL_Surface*> spriteSheets_;
};