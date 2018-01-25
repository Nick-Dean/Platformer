#pragma once

class Entity;

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void Update(Entity& entity) = 0;
};