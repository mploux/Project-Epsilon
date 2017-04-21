#include <LZ/lz.h>
#include "material.h"
#include "light.h"

using namespace lz::maths;

int main(int ac, const char **av)
{
	(void) ac;
	(void) av;
	const char *env_map_paths[6]	= {
		"data/cubemaps/church/posx.dds",
		"data/cubemaps/church/negx.dds",
		"data/cubemaps/church/posy.dds",
		"data/cubemaps/church/negy.dds",
		"data/cubemaps/church/posz.dds",
		"data/cubemaps/church/negz.dds"
	};
	lz::Display display		= lz::Display("Planet !", 1280, 720);
	lz::Shader 	shader		= lz::Shader("data/shaders/main_v.glsl", "data/shaders/main_f.glsl");
	lz::Shader 	sky_shader	= lz::Shader("data/shaders/skybox_v.glsl", "data/shaders/skybox_f.glsl");
	lz::Camera	camera		= lz::Camera(vec3(0, 0, 0));
	lz::Input	input		= lz::Input(display.getWindow());
	lz::Timer	timer		= lz::Timer();
	lz::Mesh	*gun_model	= lz::Resources::loadObj("data/models/Cerberus.obj")->getMesh();
	lz::Mesh	*toilet		= lz::Resources::loadObj("data/models/Toilet.obj")->getMesh();
	lz::Mesh	*sphere		= lz::Resources::loadObj("data/models/Sphere.obj")->getMesh();
	lz::Mesh	*plane		= lz::Resources::loadObj("data/models/Plane.obj")->getMesh();
	lz::Mesh	*skybox		= lz::Resources::loadObj("data/models/Cube.obj")->getMesh();
	lz::Cubemap env_map		= lz::Cubemap(env_map_paths);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	Light		light		= Light(vec3(-5, 3, 2), vec3(1, 1, 1), 1.0);
	Material 	mat 		= Material("PBR");
	mat.addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/Iron_A.dds"));
	mat.addTexture("normal_texture", lz::Resources::loadTexture("data/textures/Iron_N.dds"));
	mat.addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/Iron_R.dds"));
	mat.addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/Iron_M.dds"));
	Material 	gun_mat		= Material("PBR_gun");
	gun_mat.addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/Cerberus_A.dds"));
	gun_mat.addTexture("normal_texture", lz::Resources::loadTexture("data/textures/Cerberus_N.dds"));
	gun_mat.addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/Cerberus_R.dds"));
	gun_mat.addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/Cerberus_M.dds"));

	double updatedTime	= 0;
	int frames = 0;
	double elapsed = 0;
	double delta = 0;

	int i = 0;
	while (!display.isClosed())
	{
		elapsed = timer.elapsed() - updatedTime;
		delta = elapsed / 60.0;
		updatedTime = timer.elapsed();

		camera.update();
		camera.control(&input, delta * 0.5);
		camera.mouseLook(&input, 0.1);
		input.updateMouseMovement(&display);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		camera.perspective(70.0, display.getWidth(), display.getHeight(), 0.1, 1000.0);

		// sky_shader.bind();
		// env_map.bind();
		// sky_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		// sky_shader.setUniform("viewMatrix", mat4::cameraView(camera.getTransform().getForward(), camera.getTransform().getUp()));
		// sky_shader.setUniform("modelMatrix", mat4::identity());
		// glDepthMask(GL_FALSE);
		// glCullFace(GL_BACK);
		// skybox->draw();
		// glCullFace(GL_FRONT);
		// glDepthMask(GL_TRUE);

		shader.bind();
		mat.bind(&shader);
		light.bind(&shader);
		glActiveTexture(GL_TEXTURE5);
		shader.setUniform("env_map", 5);
		env_map.bind();
		shader.setUniform("use_textures", 1);
		shader.setUniform("cam_pos", camera.getTransform().getPosition());
		shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		shader.setUniform("viewMatrix", camera.getViewMatrix());

		shader.setUniform("use_textures", 0);
		shader.setUniform("albedo_color", vec3(1.00, 0.71, 0.29));
		for (int x = 0; x < 6; x++)
		{
			for (int y = 0; y < 6; y++)
			{
				shader.setUniform("modelMatrix", mat4::translate(x * 1.2 - 3, y * 1.2, -3).mul(mat4::scale(0.5, 0.5, 0.5)));
				shader.setUniform("roughness_factor", (GLfloat)((GLfloat)x / 6.0 + 0.1));
				shader.setUniform("metalic_factor", (GLfloat)((GLfloat)y / 6.0 + 0.1));
				sphere->draw();
			}
		}
		shader.setUniform("use_textures", 1);

		shader.setUniform("roughness_factor", (GLfloat)0.8);
		shader.setUniform("modelMatrix", mat4::translate(0, 0, 2));
		toilet->draw();

		gun_mat.bind(&shader);
		shader.setUniform("modelMatrix", mat4::translate(0, 3, 0).mul(mat4::rotate(0, 90, 0).mul(mat4::scale(2, 2, 2))));
		gun_model->draw();

		display.update();
		if (display.wasResized())
			glViewport(0, 0, display.getWidth(), display.getHeight());
		frames++;
	}
	delete gun_model;
	return (0);
}
