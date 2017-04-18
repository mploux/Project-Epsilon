#ifndef MATERIAL_H
# define MATERIAL_H

#include <LZ/lz.h>

using namespace lz;
using namespace maths;

class Material
{
protected:
	Shader	*m_shader;
	char	*m_name;
	vec3 	m_color;
	std::map<char *, Texture *texture> *m_textures;
	vec3 	m_specularFactor;
	vec3 	m_specularPower;

public:
	Material(char *name, Shader *shader);
	~Material();

	void bind();
	void addTexture(char *name, Texture *texture);
	void removeTexture(char *name);

	inline void setColor(vec3 color) { m_color = color; }
	inline void setSpeculatFactor(float sf) { m_specularFactor = sf; }
	inline void setSpecularPower(float sp) { m_specularPower = sp; }

	inline std::map<char *, Texture *texture> getTextures() { return m_texture; }
	inline char *getName() { return m_name; }
	inline char getColor() { return m_color; }
	inline char getSpeculatFactor() { return m_specularFactor; }
	inline char getSpecularPower() { return m_specularPower; }
};

#endif
