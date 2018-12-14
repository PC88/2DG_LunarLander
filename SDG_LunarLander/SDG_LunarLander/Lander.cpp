#include "Lander.h"
#include <time.h>


Lander::Lander( glm::vec2& acc, glm::vec2& vel, glm::vec2& AABBrad)
	: m_acceleration(acc), m_velocity(vel), m_AABBRadii(AABBrad)
{
	srand(time(NULL));

	float initX = 500; // this is not seeding properly but it will do - PC
	float initY = 900.0f; // this remains fixed
	m_position = glm::vec2(initX, initY);
	m_colour = glm::vec3(1, 1, 1);
	m_fuel = 150;
	m_LanderTransform = std::make_shared<Transform>();
	m_LanderTransform->Translate(m_position);
	m_AABB = std::make_shared<AABB>(m_AABBRadii,m_position,m_velocity,m_acceleration,m_LanderTransform);
}


Lander::~Lander()
{
}

void Lander::Update(float dt)
{
	VelocityVerletSolver(dt);
	std::cout << m_velocity.y << std::endl;
}

void Lander::Draw(int width, int height) // this draw is just appended to the transform, and therefore the AABB
{
	m_position = m_LanderTransform->getPosition();
	m_AABB->draw(width, height);

	glLoadIdentity();

	glBegin(GL_LINE_LOOP);

	//body points - PC
	glm::vec2 bpt1(m_LanderTransform->getPosition().x + (m_AABBRadii.x / 2), m_LanderTransform->getPosition().y + m_AABBRadii.y);
	glm::vec2 bpum1(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y + (2 * m_AABBRadii.y / 3));
	glm::vec2 bplm1(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y + (m_AABBRadii.y / 3));
	glm::vec2 bpb1(m_LanderTransform->getPosition().x + (m_AABBRadii.x / 2), m_LanderTransform->getPosition().y);
	glm::vec2 sp1(m_LanderTransform->getPosition().x + (m_AABBRadii.x), m_LanderTransform->getPosition().y - m_AABBRadii.y);
	glm::vec2 sp2(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y - m_AABBRadii.y);
	glm::vec2 bpb2(m_LanderTransform->getPosition().x - (m_AABBRadii.x / 2), m_LanderTransform->getPosition().y);
	glm::vec2 bpt2(m_LanderTransform->getPosition().x - (m_AABBRadii.x / 2), m_LanderTransform->getPosition().y + m_AABBRadii.y);
	glm::vec2 bplm2(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y + (m_AABBRadii.y / 3));
	glm::vec2 bpum2(m_LanderTransform->getPosition().x - (m_AABBRadii.x), m_LanderTransform->getPosition().y + (2 * m_AABBRadii.y / 3));


	//strut points -PC

	// conversion 
	glm::vec2 t1(ToGlutRefSystem(bpt1, width, height));
	glm::vec2 t2(ToGlutRefSystem(bpt2, width, height));

	glm::vec2 mt1(ToGlutRefSystem(bpum1, width, height));
	glm::vec2 mt2(ToGlutRefSystem(bpum2, width, height));

	glm::vec2 mb1(ToGlutRefSystem(bplm1, width, height));
	glm::vec2 mb2(ToGlutRefSystem(bplm2, width, height));

	glm::vec2 b1(ToGlutRefSystem(bpb1, width, height));
	glm::vec2 b2(ToGlutRefSystem(bpb2, width, height));

	glm::vec2 s1(ToGlutRefSystem(sp1, width, height));
	glm::vec2 s2(ToGlutRefSystem(sp2, width, height));
	glColor3f(m_colour.r, m_colour.g, m_colour.b);


	//Draw - these need to be drawn in ORDER, to keep shape

	glVertex2f(t1.x, t1.y);
	glVertex2f(mt1.x,mt1.y);
	glVertex2f(mb1.x, mb1.y);
	glVertex2f(b1.x, b1.y);
	glVertex2f(b2.x, b2.y);
	glVertex2f(mb2.x, mb2.y);
	glVertex2f(mt2.x, mt2.y);
	glVertex2f(t2.x, t2.y);
	glVertex2f(s1.x,s1.y);
	glVertex2f(s2.x, s2.y);
	glVertex2f(t1.x, t1.y);
	glVertex2f(t2.x, t2.y);
	glEnd();
	glFlush();
}

void Lander::MoveLeft()
{
	m_velocity = glm::vec2(m_velocity.x - 40, m_velocity.y);
}

void Lander::MoveRight()
{
	m_velocity = glm::vec2(m_velocity.x + 40, m_velocity.y);
}

void Lander::MoveUp()
{
	if (m_fuel > 0)
	{
		m_velocity = glm::vec2(m_velocity.x, m_velocity.y+ 90);
		m_fuel -= 10;
	}
	else
	{
		return;
	}
}

void Lander::Win()
{
	m_colour = glm::vec3(0, 1, 0);
	m_velocity = glm::vec2(0, 0);
	m_acceleration = glm::vec2(0, 0);
	std::cout << "YOU WIN!" << "\n";
}

void Lander::Lose()
{
	glm::vec2 cent(0, 700);
	move(cent);
	m_fuel = 150;
	std::cout << "YOU LOSE!" << "\n";
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

glm::vec2 Lander::ToGlutRefSystem(glm::vec2 p, int width, int height)
{
	glm::vec2 v((p.x / (width*0.5)) - 1, (p.y / (height*0.5)) - 1);
	return v;
}

glm::vec2 Lander::getRadii()
{
	return m_AABB->getRadii();
}
