#pragma once
#include "Vertex.h"
#include "Shader.h"

class Buffer
{
public:
	Buffer(Vertex* vertex, size_t numVertex, uint16_t* index, size_t numIndex);
	~Buffer();

	void draw(const Shader& shader) const;
private:
	uint32_t* m_buffersIds = nullptr;
	Vertex* m_vertex = nullptr;
	size_t m_numVertex = 0;
	uint16_t* m_index = nullptr;
	size_t m_numIndex = 0;

};