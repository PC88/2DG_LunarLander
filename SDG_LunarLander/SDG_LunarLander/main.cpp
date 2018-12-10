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


void ReshapeWindow(int width, int height)
{
	game->ReshapeWindow(width, height);
}

void reshape(int width, int height)
{
	ReshapeWindow(width, height);
}

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

void update(int value) // value not used here as I am using the global "Display/Update ElapsedDeltaTime" to go over GLUTS API in the timer and display callbacks -PC
{

	glutPostRedisplay();						// Post a paint request to activate display()
	glutTimerFunc(refreshMillis, update, 0);
	oldTime = timer.getTime();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);	// Clear the color buffer
	glMatrixMode(GL_MODELVIEW);		// To operate on the model-view matrix

	glutSwapBuffers();				// Swap front and back buffers (of double buffered mode)
}


void GLUTRenderer()
{
	initGL();
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