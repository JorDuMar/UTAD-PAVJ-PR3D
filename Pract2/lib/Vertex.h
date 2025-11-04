#pragma once
#include "../glm/glm.hpp"

struct Vertex
{
	Vertex();
	Vertex(glm::vec3 vPos, glm::vec3 vColor);
	
	glm::vec3 m_vPosition = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_vColor = glm::vec3(0, 0, 0);
};