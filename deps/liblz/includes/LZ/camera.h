#ifndef CAMERA_H
# define CAMERA_H

# include "transform.h"
# include "maths.h"
# include "input.h"

namespace lz
{
	class Camera
	{
	private:
		Transform	 	m_transform;
		maths::mat4		m_viewMatrix;
		maths::mat4		m_projectionMatrix;

	public:
		Camera(maths::vec3 pos);
		Camera(maths::vec3 pos, maths::quat rot);
		Camera(Transform trs);
		~Camera();

		void update();
		void perspective(float fov, float w, float h, float near, float far);
		void mouseLook(Input *input, float speed);
		void control(Input *input, float speed);

		inline maths::mat4 getViewMatrix() { return (m_viewMatrix); };
		inline maths::mat4 getProjectionMatrix() { return (m_projectionMatrix); };
		inline Transform getTransform() { return (m_transform); }
		inline void setTransform(Transform trs) { m_transform = trs; }
	};
}

#endif
