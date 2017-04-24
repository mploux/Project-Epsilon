#include <LZ/lz.h>
#include "material.h"
#include "light.h"

using namespace lz::maths;

int main(int ac, const char **av)
{
	if (ac != 2)
		sever("Usage: renderer env_map");
	lz::Display display		= lz::Display("Planet !", 1280, 720);
	lz::Shader 	shader		= lz::Shader("data/shaders/main_v.glsl", "data/shaders/main_f.glsl");
	lz::Shader 	debug		= lz::Shader("data/shaders/debug_v.glsl", "data/shaders/debug_g.glsl", "data/shaders/debug_f.glsl");
	lz::Shader 	sky_shader	= lz::Shader("data/shaders/skybox_v.glsl", "data/shaders/skybox_f.glsl");
	lz::Camera	camera		= lz::Camera(vec3(0, 0, 0));
	lz::Input	input		= lz::Input(display.getWindow());
	lz::Timer	timer		= lz::Timer();
	lz::Mesh	*gun_model	= lz::Resources::loadObj("data/models/Cerberus.obj")->getMesh();
	lz::Mesh	*toilet		= lz::Resources::loadObj("data/models/Toilet.obj")->getMesh();
	lz::Mesh	*sphere		= lz::Resources::loadObj("data/models/Sphere.obj")->getMesh();
	lz::Mesh	*plane		= lz::Resources::loadObj("data/models/Plane.obj")->getMesh();
	lz::Mesh	*skybox		= lz::Resources::loadObj("data/models/Cube.obj")->getMesh();
	lz::Mesh	*terrain	= lz::Resources::loadObj("data/models/Terrain.obj")->getMesh();
	lz::Cubemap env_map		= lz::Cubemap(av[1], 512);
	lz::Texture *bref_lut	= lz::Resources::loadTexture("data/environments/BRDF_LUT.dds");

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	Light		light		= Light(vec3(-5, 3, 2), vec3(1, 1, 1), 1.0);
	Material 	mat 		= Material("PBR");
	mat.addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/Grass_A.dds"));
	mat.addTexture("normal_texture", lz::Resources::loadTexture("data/textures/Grass_N.dds"));
	mat.addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/Grass_R.dds"));
	mat.addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/Grass_M.dds"));
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

		sky_shader.bind();
		glActiveTexture(GL_TEXTURE0);
		sky_shader.setUniform("env_map", 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env_map.getID());
		sky_shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		sky_shader.setUniform("viewMatrix", mat4::cameraView(camera.getTransform().getForward(), camera.getTransform().getUp()));
		sky_shader.setUniform("modelMatrix", mat4::identity());
		glDepthMask(GL_FALSE);
		glCullFace(GL_BACK);
		skybox->draw();
		glCullFace(GL_FRONT);
		glDepthMask(GL_TRUE);
		env_map.unbind();

		shader.bind();
		mat.bind(&shader);
		light.bind(&shader);

		glActiveTexture(GL_TEXTURE5);
		shader.setUniform("env_map", 5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env_map.getID());

		glActiveTexture(GL_TEXTURE6);
		shader.setUniform("irradiance_map", 6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env_map.getIrradianceID());

		glActiveTexture(GL_TEXTURE7);
		shader.setUniform("brdf_lut", 7);
		bref_lut->bind();

		shader.setUniform("use_textures", 1);
		shader.setUniform("cam_pos", camera.getTransform().getPosition());
		shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		shader.setUniform("viewMatrix", camera.getViewMatrix());

		shader.setUniform("use_textures", 1);
		shader.setUniform("albedo_color", vec3(1.00, 0.71, 0.29));
		for (int x = 0; x < 6; x++)
		{
			for (int y = 0; y < 6; y++)
			{
				shader.setUniform("modelMatrix", mat4::translate(x * 1.2 - 3, y * 1.2, -3).mul(mat4::scale(0.5, 0.5, 0.5)));
				shader.setUniform("roughness_factor", (GLfloat)((GLfloat)x / 6.0 + 0.02));
				shader.setUniform("metalic_factor", (GLfloat)((GLfloat)y / 6.0));
				sphere->draw();
			}
		}
		shader.setUniform("use_textures", 1);

		shader.setUniform("roughness_factor", (GLfloat)0.8);
		shader.setUniform("modelMatrix", mat4::translate(0, 0, 2));
		sphere->draw();

		gun_mat.bind(&shader);
		shader.setUniform("modelMatrix", mat4::translate(0, 3, 0).mul(mat4::rotate(0, 90, 0).mul(mat4::scale(4, 4, 4))));
		gun_model->draw();

		mat.bind(&shader);
		shader.setUniform("modelMatrix", mat4::translate(0, -1, 0));
		terrain->draw();

		debug.bind();
		debug.setUniform("projectionMatrix", camera.getProjectionMatrix());
		debug.setUniform("viewMatrix", camera.getViewMatrix());
		debug.setUniform("modelMatrix", mat4::translate(0, 0, 2));
		sphere->draw();

		display.update();
		if (display.wasResized())
			glViewport(0, 0, display.getWidth(), display.getHeight());
		frames++;
	}
	delete gun_model;
	return (0);
}
