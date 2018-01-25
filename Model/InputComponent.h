#pragma once

class Entity;

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(Entity& entity) = 0;
};