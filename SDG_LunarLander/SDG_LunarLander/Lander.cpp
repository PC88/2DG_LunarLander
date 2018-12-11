#include "Lander.h"
#include <time.h>


Lander::Lander( glm::vec2& acc, glm::vec2& vel, glm::vec2& AABBrad)
	: m_acceleration(acc), m_velocity(vel), m_AABBRadii(AABBrad)
{
	srand(time(NULL));

	float initX = std::rand() % (1000 - 1);
	float initY = 950; // mess with this
	m_position = glm::vec2(initX, initY);

	m_LanderTransform = std::make_shared<Transform>();
	m_LanderTransform->Translate(m_position);
	m_AABB = std::make_unique<AABB>(m_AABBRadii,m_position,m_velocity,m_acceleration,m_LanderTransform);
}


Lander::~Lander()
{
}

void Lander::Update(float dt)
{
	m_AABB->update(dt);
}

void Lander::Draw(int width, int height) // this draw is just appeneded to the transform, and therfore the AABB
{
	m_AABB->draw(width, height);
	glBegin(GL_POLYGON);
	glVertex2f(m_LanderTransform->getPosition().x + (m_AABBRadii.x/2), m_LanderTransform->getPosition().y + m_AABBRadii.y);
	glVertex2f(m_LanderTransform->getPosition().x - (m_AABBRadii.x/2), m_LanderTransform->getPosition().y + m_AABBRadii.y);

	glVertex2f(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y + (2*m_AABBRadii.y/3));
	glVertex2f(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y + (2*m_AABBRadii.y/3));

	glVertex2f(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y + (m_AABBRadii.y / 3));
	glVertex2f(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y + (m_AABBRadii.y / 3));


	glVertex2f(m_LanderTransform->getPosition().x + (m_AABBRadii.x/2), m_LanderTransform->getPosition().y);
	glVertex2f(m_LanderTransform->getPosition().x - (m_AABBRadii.x/2), m_LanderTransform->getPosition().y); // OCT points - PC

	// legs/struts, POINTS - PC

	glVertex2f(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y -  m_AABBRadii.y);
	glVertex2f(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y -  m_AABBRadii.y);
}

void Lander::VelocityVerletSolver(float dt)
{
	move(dt * getVelocity() + 0.5f * dt * dt * m_acceleration);
	vec2 velInBetween = getVelocity() + 0.5f * dt * m_acceleration;
	setVelocity(velInBetween + 0.5f * m_acceleration);
}

void Lander::move(glm::vec2 translation)
{
	m_LanderTransform->Translate(translation);
}
