// (c) Marco Gilardi, 2017
#pragma once
#include <vector>
#include "GameWindow.h"

// Include Grid.h here

using namespace std;

class Game
{
private:
	GameWindow* window;


	void CheckCollisions();

public:
	void Load();
	void Render();
	void Inputs();
	void Update(float dt);
	void ReshapeWindow(int weigth, int height);

	Game() {};

	virtual ~Game()
	{


		delete window;
	}
};

