#include "stdafx.h"
#include "World.h"
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "graphics.h"
#include "Input.h"
#include "Entity.h"
#include "AnimatedSprite.h"
#include "QuoteGraphics.h"
#include "QuotePhysics.h"
#include "PlayerInputComponent.h"
#include "Level.h"
#include "DebugDraw.h"
#include "Camera.h"

using namespace std;

World::World()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	b2World_ = new b2World(b2Vec2(0.0f, Globals::GAVITY_CONSTANT));
	b2World_->SetAllowSleeping(true);
	b2World_->SetContinuousPhysics(true);

	GameLoop();
}

World::~World()
{
	
}


void World::GameLoop()
{
	using clock = chrono::high_resolution_clock;

	Graphics graphics;
	Input input;

	DebugDraw drawer(&graphics);
	b2World_->SetDebugDraw(&drawer);
	drawer.SetFlags(b2Draw::e_shapeBit);

	auto previous = SDL_GetTicks();
	Uint32 lag = 0;
	
	auto qInput = new PlayerInputComponent();
	auto qPhysics = new QuotePhysics(*b2World_);
	auto qSprite = new QuoteGraphics(graphics);

	auto player = new Entity(qInput, qPhysics, qSprite);
	entities_.push_back(player);
	player_ = player;

	level_ = new Level("Map1", Vector2(100, 100), graphics, *b2World_);
	camera_ = new Camera();
	camera_->SetLevelSize(level_->GetSize());

	while (true)
	{
		auto const current = SDL_GetTicks();
		auto const elapsed = current - previous;
		previous = current;
		lag += elapsed;

		ProcessInput(input);

		while (lag >= Globals::MS_PER_FRAME)
		{
			Update(input);
			lag -= Globals::MS_PER_FRAME;
		}
		
		Render(chrono::milliseconds(lag / Globals::MS_PER_FRAME), graphics, *camera_);
	}
}

void World::ProcessInput(Input& input)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				if (event.key.repeat == 0)
				{
					input.KeyDownEvent(event);
				}
			}
			break;

			case SDL_KEYUP:
			{
				input.KeyUpEvent(event);
			}
			break;

			case SDL_QUIT:
			{
				return;
			}
			break;

			default:
				break;
		}
	}
}


void World::Update(Input& input)
{
	camera_->Update(*player_);
	level_->Update();

	for (auto entity : entities_)
	{
		entity->Update(input, *this);
	}

	b2World_->Step(0.016f, 8, 3);
}

void World::Render(chrono::milliseconds interpolation, Graphics &graphics, Camera &camera)
{
	SDL_SetRenderDrawColor(graphics.GetRenderer(), 255, 255, 255, 255);
	graphics.Clear();

	
	level_->Draw(graphics, camera);
	for (auto entity : entities_)
	{
		entity->Draw(graphics, camera);
	}

	b2World_->DrawDebugData();
	
	graphics.Flip();
}

