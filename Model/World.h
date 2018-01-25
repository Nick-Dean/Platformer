#pragma once
#include <list>
#include "Entity.h"

using namespace std;

class World
{
public:
	World() {}
	~World() {}

	void GameLoop();
	int GetEntityCount() { return entities_.size(); }

private:
	list<Entity*> entities_;
	void Update();
};

