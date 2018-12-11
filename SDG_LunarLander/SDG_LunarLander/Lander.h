#pragma once
#include <glm\vec2.hpp>
#include <memory>
#include "Transform.h"
#include "AABB.h"
class Lander
{
public:
	Lander(glm::vec2& acc, glm::vec2& vel, glm::vec2& AABBrad);
	virtual ~Lander();

	void Update(float dt);

	void Draw(int width, int height);

	void VelocityVerletSolver(float dt);

	void move(glm::vec2 translation);

	// Accessor functions -PC

	float getHeight() const { return m_height; }
	void setHeight(float val) { m_height = val; }

	glm::vec2 getPosition() const { return m_position; }
	void setPosition(glm::vec2 val) { m_position = val; }

	glm::vec2 getAcceleration() const { return m_acceleration; }
	void setAcceleration(glm::vec2 val) { m_acceleration = val; }

	glm::vec2 getVelocity() const { return m_velocity; }
	void setVelocity(glm::vec2 val) { m_velocity = val; }
private:

	float m_fuel;
	float m_height;
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	glm::vec2 m_AABBRadii;

	std::unique_ptr<AABB> m_AABB;
	std::shared_ptr<Transform> m_LanderTransform;

};

