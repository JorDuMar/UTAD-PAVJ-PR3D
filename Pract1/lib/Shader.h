#pragma once
#include "../lib/glew/GL/glew.h"
#include <cstdint>
#include "../lib/glm/glm.hpp"
#include "Vertex.h"
#include <cstring>


class Shader
{
public:

	Shader(const char* pCodeVertex, const char* pCodeFragment);
	Shader(Shader& other);
	Shader& operator=(Shader& other);
	~Shader();

	// Devuelve el identificador de OpenGL del programa
	uint32_t getId() const;

	// Obtiene el mensaje de error generado al compilar o enlazar
	const char* getError() const;

	GLint getAttribPos() const;

	GLint getAttribColor() const;

	// Activa el uso de este programa
	void use() const;

	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void setupAttribs() const;

	// Obtiene la localización de una variable uniform
		int getLocation(const char* name) const;

	// Da valor a una variable uniform
	void setInt(int loc, int val);
	void setFloat(int loc, float val);
	void setVec3(int loc, const glm::vec3& vec);
	void setVec4(int loc, const glm::vec4& vec);
	void setMatrix(int loc, const glm::mat4& matrix);

private:
	uint32_t m_idProgram;
	char* m_cError;
	GLint m_attribVpos;
	GLint m_attribVcolor;

};