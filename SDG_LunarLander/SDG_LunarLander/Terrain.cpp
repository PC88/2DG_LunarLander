#include "Terrain.h"
#include "AABB.h"


Terrain::Terrain(float minH, float maxH)
	: m_minHeight(minH), m_maxHeight(maxH)
{
	float widthInterval = 60;
	float start = -50;
	for (int i = 0; i < 20; i++)
	{
		float Yrand = std::rand() % (200 - 1); // apparently lerp does not exist in glm - it does, but.. it does not -, so im doing this instead -PC
		points[i] = glm::vec2(start += widthInterval,Yrand);
	}
}

Terrain::~Terrain()
{
}

glm::vec2 Terrain::ToGlutRefSystem(glm::vec2 p, int width, int height)
{
	glm::vec2 v((p.x / (width*0.5)) - 1, (p.y / (height*0.5)) - 1);
	return v;
}

void Terrain::Draw(int width, int height)
{

	glLoadIdentity();
	glColor3f(0, 1, 0);
	glm::vec2 refsystPoints[20];
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 20; i++)
	{
		refsystPoints[i] = ToGlutRefSystem(points[i], width, height);
	}
	for (int i = 0; i < 20; i++)
	{
		glVertex2f(refsystPoints[i].x, refsystPoints[i].y);
	}
	glEnd();
	glFlush();
}
