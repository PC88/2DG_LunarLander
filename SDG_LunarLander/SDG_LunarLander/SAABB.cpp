#include "SAABB.h"
#include <iostream>

SAABB::SAABB(glm::vec2& radii, glm::vec2& center, glm::vec2& vel, glm::vec2& acc)
	:m_radii(radii),m_center(center), m_velocity(vel), m_acceleration(acc)
{
	m_color = glm::vec3(1, 1, 1);
}


SAABB::~SAABB()
{
}

void SAABB::draw(int width, int height)
{


	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (m_center.x - (0.5f * width)) / (0.5f * width),
		(m_center.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_POLYGON);
	glColor3f(m_color.r, m_color.g, m_color.b);
	glVertex2f(2 * m_radii.x * aspectRatio / width, 2 * m_radii.y / height);
	glVertex2f(-2 * m_radii.x * aspectRatio / width, 2 * m_radii.y / height);
	glVertex2f(-2 * m_radii.x * aspectRatio / width, -2 * m_radii.y / height);
	glVertex2f(2 * m_radii.x * aspectRatio / width, -2 * m_radii.y / height);
	glEnd();
	glFlush();
}

void SAABB::setColor(float r, float g, float b)
{
	m_color = glm::vec3(r, g, b);
}

glm::vec2 SAABB::getRadii()
{
	return m_radii;
}

glm::vec2 SAABB::getCentre()
{
	return m_center;
}

