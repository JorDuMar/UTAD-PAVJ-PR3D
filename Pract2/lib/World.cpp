#include "World.h"
#include "Camera.h"
#include "Model.h"

World::~World()
{
	m_vCameras.clear();
	m_vEntities.clear();
}

void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	m_vEntities.push_back(entity);
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity);
	if (camera)
	{
		m_vCameras.push_back(camera);
	}
}

void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
	for (unsigned int i = 0; i < m_vEntities.size(); i++)
	{
		if (entity == m_vEntities[i])
		{
			m_vEntities.erase(m_vEntities.begin() + i);
			break;
		}
	}
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(entity);
	if(camera)
	{
		for (unsigned int i = 0; i < m_vCameras.size(); i++)
		{
			if (camera == m_vCameras[i])
			{
				m_vCameras.erase(m_vCameras.begin() + i);
				break;
			}
		}
	}
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
	return m_vEntities[index];
}

std::shared_ptr<Entity>& World::getEntity(size_t index)
{
	return m_vEntities[index];
}

void World::update(float deltaTime)
{
	for (unsigned int i = 0; i < m_vEntities.size(); i++)
	{
		m_vEntities[i]->update(deltaTime);
	}
}

void World::draw()
{
	for (unsigned int i = 0; i < m_vCameras.size(); i++)
	{
		m_vCameras[i]->prepare();
		for (unsigned int j = 0; j < m_vEntities.size(); j++)
		{
			m_vEntities[j]->draw();
		}
	}
}
