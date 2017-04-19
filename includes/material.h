#ifndef MATERIAL_H
# define MATERIAL_H

#include <LZ/lz.h>

using namespace lz;
using namespace maths;

class Material
{
protected:
	std::map<const char *, Texture *> m_textures;
	const char	*m_name;
	vec3 		m_color;
	float 		m_specularFactor;
	float 		m_specularPower;

public:
	Material(const char *name);
	~Material();

	void bind(Shader *shader);
	void addTexture(const char *name, Texture *texture);
	void removeTexture(const char *name);

	inline void setColor(vec3 color) { m_color = color; }
	inline void setSpeculatFactor(float sf) { m_specularFactor = sf; }
	inline void setSpecularPower(float sp) { m_specularPower = sp; }

	inline std::map<const char *, Texture *> getTextures() { return m_textures; }
	inline const char *getName() { return m_name; }
	inline vec3 getColor() { return m_color; }
	inline float getSpeculatFactor() { return m_specularFactor; }
	inline float getSpecularPower() { return m_specularPower; }
};

#endif
