// (c) Marco Gilardi, 2017
#include "Game.h"
#include <glm\glm.hpp>
#include <GL\glut.h>
#include <iostream>
#include <time.h>


void Game::Load()
{
	char title[] = "2DG app";
	char* ptrTitle = title;
	width = 1000;
	height = 1000;
	window = new GameWindow(title, width, height, 0, 0);
	glm::vec2 radii(30, 30);
	glm::vec2 vel(30, 20);
	glm::vec2 acc(0, m_gravity); // this is fixed at -5, acceleration is a constant multiplier hence the same as classic integration when applying the gravity continuously to velocity.

	float min = 0;
	float max = 200;
	lander = std::make_shared<Lander>(acc,vel,radii);
	terrain = std::make_shared<Terrain>(min, max);
	glm::vec2 zeroVec = glm::vec2(0.0f,0.0f);
	float AAx = 700;
	glm::vec2 LZradii(60, 30);
	glm::vec2 AABBcen = glm::vec2(AAx, max + 20);
	landingZone = std::make_shared<SAABB>(LZradii, AABBcen, zeroVec, zeroVec);
}

void Game::CheckCollisions()
{
	if (lander->getHeight() < 200  )
	{
		if (AABBAABBCollision(landingZone, lander) && glm::abs(lander->getVelocity().y) < m_breakUpVelocity ) // checks values
		{
			lander->Win();
		}
		lander->Lose();
	}
}

bool Game::AABBAABBCollision(std::shared_ptr<SAABB> a, std::shared_ptr<Lander> b)
{
	if (abs(a->getCentre().x - b->getPosition().x) > (a->getRadii().x + b->getRadii()).x)
	{
		return false;
	}
	if (abs(a->getCentre().y - b->getPosition().y) > (a->getRadii().y + b->getRadii().y))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Game::WinCondition()
{
	lander->Win();
}

void Game::LoseCondition()
{
	lander->Lose();
}


void Game::Update(float dt)
{
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
	terrain->Draw(width, height);
	landingZone->draw(width, height);
}

void Game::MoveLanderLeft()
{
	lander->MoveLeft();
}

void Game::MoveLanderRight()
{
	lander->MoveRight();
}

void Game::MoveLanderUp()
{
	lander->MoveUp();
}




