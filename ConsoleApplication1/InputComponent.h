#pragma once

class Entity;
class Input;

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void Update(Input& input, Entity& entity) = 0;
};