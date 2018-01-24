#pragma once
#include "Entity.h"

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void Update(Entity& entity) = 0;
};