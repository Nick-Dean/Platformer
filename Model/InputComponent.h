#pragma once
#include "Entity.h"

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(Entity& entity) = 0;
};