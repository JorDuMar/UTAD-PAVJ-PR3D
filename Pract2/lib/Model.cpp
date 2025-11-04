#include "Model.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "State.h"

Model::Model(const std::shared_ptr<Mesh>& mesh)
{
	m_mesh = *mesh;
	angle = 0.f;
}

void Model::draw()
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(), getPosition());
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), getScale());

	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[0]), glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 yawMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[1]), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 rollMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[2]), glm::vec3(0.f, 0.f, 1.f));

	glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

	glm::mat4 modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
	State::modelMatrix = modelMatrix;

	m_mesh.draw();
}

void Model::update(float deltaTime)
{
	angle += 32.f * deltaTime;
	angle = fmod(angle, 360.f);
	if (angle < 0.f) { angle += 360.f; }

	setRotation(glm::vec3(0.f, angle, 0.f));

}
