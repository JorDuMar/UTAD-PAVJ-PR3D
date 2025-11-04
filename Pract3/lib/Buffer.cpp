#include "Buffer.h"

Buffer::Buffer(Vertex* vertex, size_t numVertex, uint16_t* index, size_t numIndex)
{
	m_buffersIds = new uint32_t[2];
	glGenBuffers(2, m_buffersIds);
	m_index = index;
	m_numIndex = numIndex;
	m_vertex = vertex;
	m_numVertex = numVertex;

}

Buffer::~Buffer()
{
	glDeleteBuffers(2, m_buffersIds);
	delete[] m_buffersIds;
	m_buffersIds = nullptr;
}

void Buffer::draw(const Shader& shader) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffersIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffersIds[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_numVertex, m_vertex,
		GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_numIndex, m_index,
		GL_STATIC_DRAW);

	shader.setupAttribs();

	glDrawElements(GL_TRIANGLES, m_numIndex, GL_UNSIGNED_SHORT, nullptr);
}
