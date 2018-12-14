#pragma once
#include <glm\glm.hpp>
#include <memory>
#include <GL\glut.h>
#include "Transform.h"

class AABB;

class Terrain
{
public:
	Terrain(float minH, float maxH);
	~Terrain();

	glm::vec2 ToGlutRefSystem(glm::vec2 p, int width, int height);

	void Draw(int width, int height);


private:
	float m_maxHeight;
	float m_minHeight;

	glm::vec2 points[20];
	glm::vec2 AABBtl;
	glm::vec2 AABBtr;
	std::shared_ptr<AABB> landingZone;
};

