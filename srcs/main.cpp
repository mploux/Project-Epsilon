#include <LZ/lz.h>
#include "material.h"
#include "light.h"

using namespace lz::maths;

int main(int ac, const char **av)
{
	(void) ac;
	(void) av;
	lz::Display display		= lz::Display("Planet !", 1280, 720);
	lz::Shader 	shader		= lz::Shader("data/shaders/main_v.glsl", "data/shaders/main_f.glsl");
	lz::Camera	camera		= lz::Camera(vec3(0, 0, 0));
	lz::Input	input		= lz::Input(display.getWindow());
	lz::Timer	timer		= lz::Timer();
	lz::Mesh	*gun_model	= lz::Resources::loadObj("data/models/Cerberus.obj")->getMesh();
	const char *env_map_paths[6]	= {
		"data/cubemaps/church/posx.dds",
		"data/cubemaps/church/negx.dds",
		"data/cubemaps/church/posy.dds",
		"data/cubemaps/church/negy.dds",
		"data/cubemaps/church/posz.dds",
		"data/cubemaps/church/negz.dds"
	};
	lz::Cubemap env_map		= lz::Cubemap(env_map_paths);

	Material 	mat 		= Material("PBR");
	Light		light		= Light(vec3(-5, -3, 2), vec3(1, 1, 1), 1.0);

	mat.addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/Cerberus_A.dds"));
	mat.addTexture("normal_texture", lz::Resources::loadTexture("data/textures/Cerberus_N.dds"));
	mat.addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/Cerberus_R.dds"));
	mat.addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/Cerberus_M.dds"));

	double updatedTime	= 0;
	int frames;
	double elapsed = 0;
	double delta = 0;
	// double fps = 0;

	int i = 0;
	while (!display.isClosed())
	{
		elapsed = timer.elapsed() - updatedTime;
		delta = elapsed / 60.0;
		updatedTime = timer.elapsed();
		// fps = 1000.0 / elapsed;

		camera.update();
		camera.control(&input, delta * 0.1f);
		camera.mouseLook(&input, 0.1);
		input.updateMouseMovement(&display);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.perspective(70.0, display.getWidth(), display.getHeight(), 0.1, 1000.0);
		shader.bind();
		mat.bind(&shader);
		light.bind(&shader);
		glActiveTexture(GL_TEXTURE5);
		shader.setUniform("env_map", 5);
		env_map.bind();
		shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		shader.setUniform("viewMatrix", camera.getViewMatrix());
		shader.setUniform("modelMatrix", mat4::rotate(i, i, i));
		shader.setUniform("cam_pos", camera.getTransform().getPosition());

		gun_model->draw();
		display.update();
		if (display.wasResized())
			glViewport(0, 0, display.getWidth(), display.getHeight());
		frames++;

	}
	delete gun_model;
	return (0);
}
