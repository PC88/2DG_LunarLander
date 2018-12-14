// (c) Marco Gilardi, 2017
#pragma once
#include <vector>
#include "GameWindow.h"
#include "Lander.h"
#include "Terrain.h"
#include "SAABB.h"

// Include Grid.h here

using namespace std;

class Game
{
private:
	GameWindow* window;
	std::shared_ptr<Lander> lander;
	std::shared_ptr<Terrain> terrain;
	std::shared_ptr<SAABB> landingZone; 

	int width, height;

	void CheckCollisions();
	bool AABBAABBCollision(std::shared_ptr<SAABB> a, std::shared_ptr<Lander> b);
	void WinCondition();
	void LoseCondition();
public:
	void Load();
	void Render();
	void MoveLanderLeft();
	void MoveLanderRight();
	void MoveLanderUp();
	void Update(float dt);
	void ReshapeWindow(int weigth, int height);

	Game() {};

	virtual ~Game()
	{
		delete window;
	}
};

