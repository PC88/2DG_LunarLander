// (c) Marco Gilardi, 2017
#include "Game.h"
#include <glm\glm.hpp>
#include <GL\glut.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace glm;

void Game::Load()
{
	char title[] = "2DG app";
	char* ptrTitle = title;
	width = 1000;
	height = 1000;
	window = new GameWindow(title, width, height, 0, 0);
	

	srand(time(NULL)); // maybe use this - PC
}

void Game::CheckCollisions()
{
	
}


void Game::Update(float dt)
{
	// update bs here - PC
	
	lander->Update(dt);
	CheckCollisions();
}

void Game::ReshapeWindow(int width, int height)
{
	window->Reshape(width, height);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
	lander->Draw(width,height);
	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}

void Game::Inputs()
{
}
