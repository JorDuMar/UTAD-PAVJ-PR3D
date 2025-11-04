#pragma once
#include "../lib/glm/glm.hpp"

class Entity
{
public:
	Entity();
	virtual ~Entity() {}

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getRotation() const; // puede ser quat
	const void setRotation(const glm::vec3& rot); // puede ser quat
	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);
	void move(const glm::vec3& vec); // ver en las diapositivas
	virtual void update(float deltaTime) {}
	virtual void draw() {}

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};