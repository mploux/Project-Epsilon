#include <LZ/lz.h>
#include "material.h"
#include "light.h"
#include "mesh_renderer.h"
#include "skybox.h"

using namespace lz::maths;

int main(int ac, const char **av)
{
	const char *path = "data/environments/Outside.dds";
	if (ac == 2)
		path = av[1];
	lz::Display display		= lz::Display("Planet !", 1280, 720);
	lz::Shader 	shader		= lz::Shader("data/shaders/main_v.glsl", "data/shaders/main_f.glsl");
	lz::Shader 	debug		= lz::Shader("data/shaders/debug_v.glsl", "data/shaders/debug_g.glsl", "data/shaders/debug_f.glsl");
	lz::Shader 	sky_shader	= lz::Shader("data/shaders/skybox_v.glsl", "data/shaders/skybox_f.glsl");
	lz::Camera	camera		= lz::Camera(vec3(0, 0, 0));
	lz::Input	input		= lz::Input(display.getWindow());
	lz::Timer	timer		= lz::Timer();
	lz::Texture *bref_lut	= lz::Resources::loadTexture("data/environments/BRDF_LUT.dds");

	lz::Cubemap env_map		= lz::Cubemap(path, 512);
	Skybox		skybox		= Skybox(&env_map);
	Light		light		= Light(vec3(-5, 3, 2), vec3(1, 1, 1), 3.0);

	lz::Mesh	*gun_mesh = lz::Resources::loadObj("data/models/R2D2.obj")->getMesh();
	Material 	*gun_material = new Material("gun_material");
	gun_material->addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/R2D2_Diffuse.dds"));
	gun_material->addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/R2D2_R.dds"));
	gun_material->addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/R2D2_M.dds"));
	MeshRenderer *gun = new MeshRenderer(gun_mesh, gun_material);

	lz::Mesh	*terrain_mesh = lz::Resources::loadObj("data/models/X-Fighter.obj")->getMesh();
	Material 	*terrain_material = new Material("terrain_material");
	terrain_material->addTexture("albedo_texture", lz::Resources::loadTexture("data/textures/XWing_Diffuse_01.dds"));
	terrain_material->addTexture("roughness_texture", lz::Resources::loadTexture("data/textures/XWing_R.dds"));
	terrain_material->addTexture("metalic_texture", lz::Resources::loadTexture("data/textures/XWing_M.dds"));
	MeshRenderer *terrain = new MeshRenderer(terrain_mesh, terrain_material);
	terrain->setPosition(lz::maths::vec3(0, -3, 0));

	lz::Mesh	*sphere_mesh = lz::Resources::loadObj("data/models/Sphere.obj")->getMesh();

	double updatedTime = 0;
	int frames = 0;
	double elapsed = 0;
	double delta = 0;

	while (!display.isClosed())
	{
		elapsed = timer.elapsed() - updatedTime;
		delta = elapsed / 60.0;
		updatedTime = timer.elapsed();

	glEnable(GL_MULTISAMPLE);

		camera.update();
		camera.control(&input, delta * 0.5);
		camera.mouseLook(&input, 0.1);
		input.updateMouseMovement(&display);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		camera.perspective(70.0, display.getWidth(), display.getHeight(), 0.1, 1000.0);

		skybox.render(&camera);

		shader.bind();
		shader.setUniform("use_textures", 1);
		light.bind(&shader);
		shader.setUniform("cam_pos", camera.getTransform().getPosition());
		shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
		shader.setUniform("viewMatrix", camera.getViewMatrix());

		glActiveTexture(GL_TEXTURE5);
		shader.setUniform("env_map", 5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env_map.getID());

		glActiveTexture(GL_TEXTURE6);
		shader.setUniform("irradiance_map", 6);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env_map.getIrradianceID());

		glActiveTexture(GL_TEXTURE7);
		shader.setUniform("brdf_lut", 7);
		bref_lut->bind();

		gun->render(&shader);
		terrain->render(&shader);

		shader.setUniform("modelMatrix", mat4::translate(5, 2, 0));
		sphere_mesh->draw();

		display.update();
		if (display.wasResized())
			glViewport(0, 0, display.getWidth(), display.getHeight());
		frames++;
	}

	delete gun_mesh;
	delete gun_material;
	delete gun;
	delete terrain_mesh;
	delete terrain_material;
	delete terrain;
	lz::Resources::clear();

	return (0);
}
