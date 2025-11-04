#include "Vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(glm::vec3 vPos, glm::vec2 vTex, glm::vec3 vColor)
{
	m_vPosition = vPos;
	m_vTex = vTex;
	m_vColor = vColor;
}
