#pragma once
#include <memory>
#include "../glm/glm.hpp"

class Texture
{
public:
	static std::shared_ptr<Texture> load(const char* filename);
	uint32_t getId() const;
	const glm::ivec2& getSize() const;
	void bind() const;

private:
	uint32_t m_texId;
	glm::ivec2 m_vSize;

};