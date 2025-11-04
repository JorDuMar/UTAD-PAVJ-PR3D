#include "Entity.h"

Entity::Entity()
{
  m_position = glm::vec3();
  m_rotation = glm::vec3();
  m_scale = glm::vec3(1.f);
}

const glm::vec3& Entity::getPosition() const
{
  return m_position;
}

void Entity::setPosition(const glm::vec3& pos)
{
  m_position = pos;
}

const glm::vec3& Entity::getRotation() const
{
  return m_rotation;
}

const void Entity::setRotation(const glm::vec3& rot)
{
  m_rotation = rot;
}

const glm::vec3& Entity::getScale() const
{
  return m_scale;
}

void Entity::setScale(const glm::vec3& scale)
{
  m_scale = scale;
}

void Entity::move(const glm::vec3& vec)
{
  m_position += vec;
}
