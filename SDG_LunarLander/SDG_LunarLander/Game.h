// (c) Marco Gilardi, 2017
#pragma once
#include <vector>
#include "GameWindow.h"
#include "Lander.h"

// Include Grid.h here

using namespace std;

class Game
{
private:
	GameWindow* window;
	std::shared_ptr<Lander> lander;

	int width, height;

	void CheckCollisions();

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

