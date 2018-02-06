#pragma once
#include <chrono>
#include <vector>

class Entity;
class Input;
class Graphics;
class b2World;
class Level;
class Camera;

using namespace std;

class World
{
public:
	World();
	~World();
	void GameLoop();

private:
	b2World* b2World_;
	Entity* player_;
	Camera* camera_;
	Level* level_;
	vector<Entity*> entities_;

	void ProcessInput(Input& input);
	void Update(Input& input);
	void Render(chrono::milliseconds interpolation, Graphics &graphics, Camera &camera);
};

