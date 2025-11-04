#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Texture.h"
#include "../lib/glew/GL/glew.h"

std::shared_ptr<Texture> Texture::load(const char* filename)
{
	int xTex, yTex;
	stbi_uc* ucBytesTexture = stbi_load(filename, &xTex, &yTex, nullptr, 4);
	if (ucBytesTexture)
	{
		std::shared_ptr<Texture> pTexture = std::make_shared<Texture>();
		pTexture->m_vSize = glm::ivec2(xTex, yTex);
		glGenTextures(1, &(pTexture->m_texId));
		glBindTexture(GL_TEXTURE_2D, pTexture->m_texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, xTex, 1 - yTex, 0, GL_RGBA, GL_UNSIGNED_BYTE, ucBytesTexture);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(ucBytesTexture);
		return pTexture;
	}
	else 
	{
		return nullptr;
	}

}

uint32_t Texture::getId() const
{
	return m_texId;
}

const glm::ivec2& Texture::getSize() const
{
	return m_vSize;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texId);
}
