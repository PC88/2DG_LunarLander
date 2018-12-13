#include "AABB.h"
#include <iostream>

AABB::AABB(glm::vec2& radii, glm::vec2& center, glm::vec2& vel, glm::vec2& acc, std::shared_ptr<Transform> tran)
	:m_radii(radii), m_velocity(vel), m_acceleration(acc), m_AABBTransform(tran)
{
	move(vel);
	m_color = glm::vec3(0, 0, 1);
}

AABB::~AABB()
{
}

void AABB::VelocityVerletSolver(float dt)
{
	move(dt * m_velocity + 0.5f * dt * dt * m_acceleration);
	vec2 velInBetween = m_velocity + 0.5f * dt * m_acceleration;
	m_velocity = velInBetween + 0.5f * m_acceleration;
}

void AABB::move(vec2 traslation)
{
	m_AABBTransform->Translate(traslation);
}

void AABB::update(float dt)
{
	VelocityVerletSolver(dt);
}

void AABB::draw(int width, int height)
{
	vec2 position = m_AABBTransform->getPosition();

	glLoadIdentity();				// Reset model-view matrix
	float aspectRatio = (width / (float)height);
	glTranslatef(aspectRatio * (position.x - (0.5f * width)) / (0.5f * width),
		(position.y - (0.5f * height)) / (0.5f * height), 0.0f);  // Translate to (xPos, yPos)

	glBegin(GL_LINE_LOOP);
	glColor3f(m_color.r, m_color.g, m_color.b);
	glVertex2f(2 * m_radii.x * aspectRatio / width, 2 * m_radii.y / height);
	glVertex2f(-2 * m_radii.x * aspectRatio / width, 2 * m_radii.y / height);
	glVertex2f(-2 * m_radii.x * aspectRatio / width, -2 * m_radii.y / height);
	glVertex2f(2 * m_radii.x * aspectRatio / width, -2 * m_radii.y / height);
	glEnd();
	glFlush();
}

void AABB::setColor(float r, float g, float b)
{
	m_color = vec3(r, g, b);
}

vec2 AABB::getPosition()
{
	return m_AABBTransform->getPosition();
}

vec2 AABB::getRadii()
{
	return m_radii;
}