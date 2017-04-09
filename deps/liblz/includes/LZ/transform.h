#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "maths.h"

namespace lz
{
	class Transform
	{
	private:
		maths::vec3 m_pos;
		maths::quat m_rot;
		maths::vec3 m_scale;

	public:
		Transform()
		{
			m_pos = maths::vec3();
			m_rot = maths::quat();
			m_scale = maths::vec3(1, 1, 1);
		}

		Transform(maths::vec3 pos, maths::quat rot, maths::vec3 scale)
		{
			m_pos = pos;
			m_rot = rot;
			m_scale = scale;
		}

		Transform(maths::vec3 pos, maths::quat rot)
		{
			m_pos = pos;
			m_rot = rot;
			m_scale = maths::vec3(1, 1, 1);
		}

		Transform(maths::vec3 pos)
		{
			m_pos = pos;
			m_rot = maths::quat();
			m_scale = maths::vec3(1, 1, 1);
		}

		Transform(Transform* t)
		{
			m_pos = t->m_pos;
			m_rot = t->m_rot;
			m_scale = t->m_scale;
		}

		maths::mat4 toMatrix();

		void rotate(maths::vec3 axis, float angle);
		void translate(maths::vec3 axis, float speed);

		inline maths::vec3 getPosition() { return (m_pos); };
		inline maths::quat getRotation() { return (m_rot); };
		inline maths::vec3 getScale() { return (m_scale); };

		inline void setPosition(maths::vec3 pos) { m_pos = pos; };
		inline void setRotation(maths::quat rot) { m_rot = rot; };
		inline void setScale(maths::vec3 scale) { m_scale = scale; };

		inline maths::vec3 getForward() { return (m_rot.getForward()); }
		inline maths::vec3 getUp() { return (m_rot.getUp()); }
		inline maths::vec3 getRight() { return (m_rot.getRight()); }
	};
}

#endif
