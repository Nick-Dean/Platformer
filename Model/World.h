#pragma once
#include <vector>
#include "Entity.h"

using namespace std;

class World
{
public:
	World() = default;

	void GameLoop();

private:
	vector<Entity*> entities_;
	void Update();
};

