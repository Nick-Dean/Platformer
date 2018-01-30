#pragma once

class Entity;
class Graphics;

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void Update(Entity& entity) = 0;
	virtual void Draw(Graphics &graphics, int x, int y) = 0;
};