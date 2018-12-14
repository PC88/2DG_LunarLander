#include <GL\glut.h>
#include <glm\glm.hpp>
#include <iostream>
#include <memory>
#include <algorithm>

class SAABB
{

public:

	SAABB(glm::vec2& radii, glm::vec2& center, glm::vec2& vel, glm::vec2& acc);
	virtual ~SAABB();

	glm::vec2 getRadii();
	glm::vec2 getCentre();

	void setColor(float r, float g, float b);
	void draw(int width, int height);

private:

	glm::vec2 m_radii;
	glm::vec2 m_center;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	glm::vec3 m_color;
};