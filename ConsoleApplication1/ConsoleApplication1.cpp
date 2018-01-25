// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

int main(int argc, char** argv)
{
	//gound body
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	auto groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	auto body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	//timestep
	auto timestep = 1.0f / 60.0f;

	auto velocityIterations = 8;
	auto positionIterations = 3;

	for (auto i = 0; i < 60; ++i)
	{
		world.Step(timestep, velocityIterations, positionIterations);
		auto position = body->GetPosition();
		auto angle = body->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	auto i = 0;
	std::cin >> i;
	return 0;
}

