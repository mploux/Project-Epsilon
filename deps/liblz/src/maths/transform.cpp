#include "transform.h"

using namespace lz;

maths::mat4 Transform::toMatrix()
{
	maths::mat4 translationMatrix = maths::mat4::translate(m_pos.x, m_pos.y, m_pos.z);
	maths::mat4 rotationMatrix = m_rot.to_matrix();
	maths::mat4 scaleMatrix = maths::mat4::scale(m_scale.x, m_scale.y, m_scale.z);
	maths::mat4 parentMatrix = maths::mat4::identity();

	maths::mat4 transformationMatrix = parentMatrix.mul(translationMatrix.mul(rotationMatrix.mul(scaleMatrix)));

	return (transformationMatrix);
}

void Transform::rotate(maths::vec3 axis, float angle)
{
	m_rot = maths::quat(axis, TO_RADIANS(angle)).mul(m_rot).normalize();
}

void Transform::translate(maths::vec3 axis, float speed)
{
	m_pos.add(axis.mul(speed));
}
