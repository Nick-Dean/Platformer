#pragma once

class Entity;

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Entity& entity) = 0;
};