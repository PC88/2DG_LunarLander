#include <GL\glut.h>
#include <iostream>
#include <memory>
#include "Transform.h"
#include <algorithm>

class AABB 
{

public:

	AABB(glm::vec2& radii, glm::vec2& center, glm::vec2& vel, glm::vec2& acc, std::shared_ptr<Transform> tran);
	virtual ~AABB();

	glm::vec2 getPosition();
	glm::vec2 getRadii();

	void setColor(float r, float g, float b);
	void update(float dt);
	void draw(int width, int height);

private:

	glm::vec2 m_radii;
	glm::vec2 m_center;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	glm::vec3 m_color;
	std::shared_ptr<Transform> m_AABBTransform;

	void VelocityVerletSolver(float dt);
	void move(vec2 traslation);
};

