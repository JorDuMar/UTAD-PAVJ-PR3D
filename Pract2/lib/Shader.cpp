#include "Shader.h"
#include "Vertex.h"
#include <cstring>
#include "../lib/glm/gtc/type_ptr.hpp"

Shader::Shader(const char* pVertex, const char* pFragment)
{
	m_cError = new char[1024];
	bool error = false;
	m_idProgram = 0;
	m_attribVcolor = -1;
	m_attribVpos = -1;

	uint32_t vertexCode = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentCode = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexCode, 1, &pVertex, nullptr);
	glShaderSource(fragmentCode, 1, &pFragment, nullptr);

	int retCode;
	glCompileShader(vertexCode);
	glGetShaderiv(vertexCode, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(vertexCode, sizeof(m_cError), nullptr, m_cError);
		glDeleteShader(vertexCode);
		error = true;
	}

	glCompileShader(fragmentCode);
	glGetShaderiv(fragmentCode, GL_COMPILE_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentCode, sizeof(m_cError), nullptr, m_cError);
		glDeleteShader(fragmentCode);
		error = true;
	}
	
	if (!error)
	{
		m_idProgram = glCreateProgram();
		glAttachShader(m_idProgram, vertexCode);
		glAttachShader(m_idProgram, fragmentCode);

		glLinkProgram(m_idProgram);
		glDeleteShader(vertexCode);
		glDeleteShader(fragmentCode);

		glGetProgramiv(m_idProgram, GL_LINK_STATUS, &retCode);
		if(retCode == GL_FALSE) 
		{
			glGetProgramInfoLog(m_idProgram, sizeof(m_cError),
				nullptr, m_cError);
			glDeleteProgram(m_idProgram);
			m_idProgram = 0;
		}
		else
		{
			m_attribVpos = glGetAttribLocation(m_idProgram, "vpos");
			m_attribVcolor = glGetAttribLocation(m_idProgram, "vcolor");
			delete[] m_cError;
			m_cError = nullptr;
		}
	}
	
}

Shader::Shader(Shader& other)
{
	m_idProgram = other.getId();
	if (other.getError())
	{
		m_cError = new char[1024];
		strcpy_s(m_cError, 1024, other.getError());
	}
	else
	{
		m_cError = nullptr;
	}
	m_attribVpos = other.getAttribPos();
	m_attribVcolor = other.getAttribColor();
}

Shader& Shader::operator=(Shader& other)
{
	m_idProgram = other.getId();
	if (m_cError)
	{
		if (other.getError())
		{
			strcpy_s(m_cError, 1024, other.getError());
		}
		else
		{
			delete[] m_cError;
			m_cError = nullptr;
		}
	}
	else
	{
		if (other.getError())
		{
			m_cError = new char[1024];
			strcpy_s(m_cError, 1024, other.getError());
		}
		else
		{
			m_cError = nullptr;
		}
	}

	m_attribVpos = other.getAttribPos();
	m_attribVcolor = other.getAttribColor();

	return *this;
}

Shader::~Shader()
{
	if (m_idProgram != 0)
	{
		glDeleteProgram(m_idProgram);
	}

	if (m_cError)
	{
		delete[] m_cError;
	}
}

uint32_t Shader::getId() const
{
	return m_idProgram;
}

const char* Shader::getError() const
{
	return m_cError;
}

GLint Shader::getAttribPos() const
{
	return m_attribVpos;
}

GLint Shader::getAttribColor() const
{
	return m_attribVcolor;
}

void Shader::use() const
{
	if (m_idProgram != 0) { glUseProgram(m_idProgram); }
}

void Shader::setupAttribs() const
{
	if (m_attribVpos != -1)
	{
		glEnableVertexAttribArray(m_attribVpos);
		glVertexAttribPointer(m_attribVpos, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const
			void*>(offsetof(Vertex, m_vPosition)));
	}
	
	if (m_attribVcolor != -1)
	{
		glEnableVertexAttribArray(m_attribVcolor);
		glVertexAttribPointer(m_attribVcolor, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const
			void*>(offsetof(Vertex, m_vColor)));
	}
	
}

int Shader::getLocation(const char* name) const
{
	return glGetUniformLocation(m_idProgram, name);
}

void Shader::setInt(int loc, int val)
{
	if (loc != -1)
	{
		glUniform1i(loc, val);
	}
}

void Shader::setFloat(int loc, float val)
{
	if (loc != -1)
	{
		glUniform1f(loc, val);
	}
}

void Shader::setVec3(int loc, const glm::vec3& vec)
{
	if (loc != -1)
	{
		glUniform3f(loc, vec[0], vec[1], vec[2]);
	}
}

void Shader::setVec4(int loc, const glm::vec4& vec)
{
	if (loc != -1)
	{
		glUniform4f(loc, vec[0], vec[1], vec[2], vec[3]);
	}
}

void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix)/*&matrix[0][0]*/);
	}
}
