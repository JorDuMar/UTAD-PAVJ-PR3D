#include "Vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(glm::vec3 vPos, glm::vec3 vColor)
{
	m_vPosition = vPos;
	m_vColor = vColor;
}
