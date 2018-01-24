#include "World.h"
#include <chrono>

using namespace std;

constexpr chrono::microseconds TIMESTEP(16);

void World::GameLoop()
{
	using clock = chrono::high_resolution_clock;

	auto previous = clock::now();
	chrono::microseconds lag(0);

	while (true)
	{
		auto current = clock::now();
		auto elapsed = current - previous;
		previous = current;
		lag += chrono::duration_cast<chrono::microseconds>(elapsed);

		//processInput();

		while (lag >= TIMESTEP)
		{
			Update();
			lag -= TIMESTEP;
		}
		
		//render(lag / TIMESTEP);
	}
}

void World::Update()
{
	for (auto entity : entities_)
	{
		entity->Update();
	}
}
