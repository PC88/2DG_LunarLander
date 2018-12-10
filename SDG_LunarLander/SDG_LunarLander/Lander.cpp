#include "Lander.h"



Lander::Lander()
{
}


Lander::~Lander()
{
}

void Lander::Update(float dt)
{
	m_AABB->update(dt);
}

void Lander::Draw(int width, int height)
{
	m_AABB->draw(width, height);
}

void Lander::VelocityVerletSolver(float dt)
{
	move(dt * m_velocity + 0.5f * dt * dt * m_acceleration);
	vec2 velInBetween = m_velocity + 0.5f * dt * m_acceleration;
	m_velocity = velInBetween + 0.5f * m_acceleration;
}

void Lander::move(glm::vec2 translation)
{
	m_LanderTransform->Translate(translation);
}
