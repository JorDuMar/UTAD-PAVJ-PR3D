#include "Camera.h"
#include "State.h"
#include "../lib/glm/gtc/matrix_transform.hpp"


Camera::Camera()
{
	m_projMatrix = glm::mat4();
	m_viewPort = glm::ivec4();
	m_vColor = glm::vec3();
}

const glm::mat4& Camera::getProjection() const
{
	return m_projMatrix;
}

void Camera::setProjection(const glm::mat4& proj)
{
	m_projMatrix = proj;
}

const glm::ivec4& Camera::getViewport() const
{
	return m_viewPort;
}

void Camera::setViewport(const glm::ivec4& vp)
{
	m_viewPort = vp;
}

const glm::vec3& Camera::getClearColor() const
{
	return m_vColor;
}

void Camera::setClearColor(const glm::vec3& color)
{
	m_vColor;
}


//Prepare Viewmatrix and set projMatrix
void Camera::prepare()
{
	State::projectionMatrix = m_projMatrix;
	glm::mat4 transMatrix = glm::translate(glm::mat4(), getPosition() * -1.f);

	glm::mat4 pitchMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[0]) * -1, glm::vec3(1.f, 0.f, 0.f));
	glm::mat4 yawMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[1]) * -1, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 rollMatrix = glm::rotate(glm::mat4(), glm::radians(getRotation()[2]) * -1, glm::vec3(0.f, 0.f, 1.f));
	glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

	glm::mat4 viewMatrix = rotationMatrix * transMatrix;
	State::viewMatrix = viewMatrix;
	glViewport(m_viewPort[0], m_viewPort[1], m_viewPort[2], m_viewPort[3]);
	glScissor(m_viewPort[0], m_viewPort[1], m_viewPort[2], m_viewPort[3]);

	glClearColor(m_vColor[0], m_vColor[1], m_vColor[2], 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

