#include "Mesh.h"
#include "State.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader)
{
	m_listBuffers.emplace_back(buffer, shader);
}

size_t Mesh::getNumBuffers() const
{
	return m_listBuffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
	return m_listBuffers[index].first;
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return m_listBuffers[index].first;
}

void Mesh::draw()
{
	for (unsigned i = 0; i < m_listBuffers.size(); i++)
	{
		if (m_listBuffers[i].second) //If shader
		{
			m_listBuffers[i].second->use();
			int locMVP = m_listBuffers[i].second->getLocation("mvp");	
			glm::mat4 MVP = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
			m_listBuffers[i].second->setMatrix(locMVP, MVP);
			if (m_listBuffers[i].first)
			{
				m_listBuffers[i].first->draw(*m_listBuffers[i].second);
			}
		}
		else
		{
			State::defaultShader->use();
			int locMVP = State::defaultShader->getLocation("mvp");
			glm::mat4 MVP = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
			State::defaultShader->setMatrix(locMVP, MVP);
			if (m_listBuffers[i].first)
			{
				m_listBuffers[i].first->draw(*State::defaultShader);
			}
		}

	}
}
