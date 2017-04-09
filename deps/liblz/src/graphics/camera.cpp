#include "camera.h"

using namespace lz;

Camera::Camera(maths::vec3 pos)
{
	m_transform = Transform(pos);
}

Camera::Camera(maths::vec3 pos, maths::quat rot)
{
	m_transform = Transform(pos, rot);
}

Camera::Camera(Transform trs)
{
	m_transform = trs;
}

Camera::~Camera()
{

}

void Camera::mouseLook(Input *input, float speed)
{
	m_transform.rotate(maths::vec3(0, 1, 0), input->getDX() * speed);
	m_transform.rotate(m_transform.getRight(), input->getDY() * speed);
}

void Camera::control(Input *input, float speed)
{
	if (input->getKey(GLFW_KEY_W))
		m_transform.translate(m_transform.getForward(), speed);
	if (input->getKey(GLFW_KEY_S))
		m_transform.translate(m_transform.getForward(), -speed);
	if (input->getKey(GLFW_KEY_A))
		m_transform.translate(m_transform.getRight(), -speed);
	if (input->getKey(GLFW_KEY_D))
		m_transform.translate(m_transform.getRight(), speed);
}

void Camera::update()
{
	maths::mat4 translationMatrix = maths::mat4::translate(m_transform.getPosition().mul(-1));
	maths::mat4 rotationMatrix = maths::mat4::cameraView(m_transform.getForward(), m_transform.getUp());
	m_viewMatrix = rotationMatrix.mul(translationMatrix);
}

void Camera::perspective(float fov, float w, float h, float near, float far)
{
	m_projectionMatrix = maths::mat4::perspective(fov, w / h, near, far);
}
