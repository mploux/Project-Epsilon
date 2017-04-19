#ifndef LIGHT_H
# define LIGHT_H

#include <LZ/lz.h>

using namespace lz::maths;

class Light
{
private:
	vec3			m_position;
	vec3			m_color;
	float			m_intensity;

public:
	Light(vec3 pos, vec3 color, float intensity);
	~Light();

	void bind(lz::Shader *shader);

	inline vec3 getPosition() { return m_position; }
	inline vec3 getColor() { return m_color; }
	inline float getIntensity() { return m_intensity; }
};

#endif
