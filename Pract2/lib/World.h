#pragma once
#include <memory>
#include "Entity.h"
#include <vector>

class Camera;

class World 
{
public:
	~World();
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();
private:
	std::vector<std::shared_ptr<Entity>> m_vEntities;
	std::vector<std::shared_ptr<Camera>> m_vCameras;
};