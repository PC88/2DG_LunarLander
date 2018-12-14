#include <iostream>
#include <windows.h> // I actually know nothing about anything ever -PC
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <string>
#include <cmath>
#include <glm\glm.hpp>

#include "Game.h"
#include "GameWindow.h"
#include "Terrain.h"
#include "Lander.h"
#include "Timer.h"
#include "Transform.h"

int refreshMillis = 16;      // Refresh period in milliseconds
int width = 1000;
int height = 1000;


Game* game;
LowResTimer timer;
double oldTime = 0;

// input stuff;
bool mouseActive = false;
bool clearScreen = true;
float mouseX, mouseY;
float lastX, lastY;
float posx = 140, posy = 90 ;
float size = 30;
std::string message = "";

void ReshapeWindow(int width, int height)
{
	game->ReshapeWindow(width, height);
}

void reshape(int width, int height)
{
	ReshapeWindow(width, height);
}


void special_keys(int value, int x, int y)
{
	std::cout << value;
	switch (value) {
	case GLUT_KEY_LEFT:	// Left
		game->MoveLanderLeft();
		break;
	case GLUT_KEY_RIGHT:	// Right
		game->MoveLanderRight();
		break;
	case GLUT_KEY_UP:		// Up
		game->MoveLanderUp();
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == VK_ESCAPE)
		exit(0);
	else
		message += key;
}



void update(int value) // value not used here as I am using the global "Display/Update ElapsedDeltaTime" to go over GLUTS API in the timer and display callbacks -PC
{
	game->Update(timer.getTime() - oldTime);
	glutPostRedisplay();						// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, update, 0);
	oldTime = timer.getTime();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix
	game->Render();
	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}


void GLUTRenderer()
{
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	glutReshapeFunc(reshape);		// Register callback handler for window re-shape
	glutDisplayFunc(display);
	glutTimerFunc(0, update, 0);	// First timer call immediately
	glutMainLoop();					// Enter event-processing loop 
}

int main(int argc, char** argv)
{
	game = new Game();
	game->Load();
	GLUTRenderer(); // This in a similar form - although not the same as LAB`s hence the Param. -PC

	delete game;

	return 0;
}