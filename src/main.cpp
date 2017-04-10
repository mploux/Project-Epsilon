#include <LZ/lz.h>

using namespace lz::maths;

int main(int ac, char **av)
{
	(void) ac;
	(void) av;
	lz::Display display		= lz::Display("Planet !", 1280, 720);
	lz::Shader 	shader		= lz::Shader("data/shaders/main_v.glsl", "data/shaders/main_f.glsl");
	lz::Camera	camera		= lz::Camera(vec3(0, 0, 0));
	lz::Input	input		= lz::Input(display.getWindow());
	lz::Timer	timer		= lz::Timer();
	lz::Mesh	*gun_model	= lz::Resources::loadObj((char *)"data/models/Cerberus.obj")->getMesh();
	lz::Texture texture 	= lz::Texture("data/textures/Cerberus_A.dds");

	double updatedTime	= 0;
	int frames;
	double elapsed = 0;
	double delta = 0;
	double fps = 0;

	int i = 0;
	while (!display.isClosed())
	{
		elapsed = timer.elapsed() - updatedTime;
		delta = elapsed / 60.0;
		updatedTime = timer.elapsed();
		fps = 1000.0 / elapsed;

		texture.bind();

		camera.update();
		camera.control(&input, delta * 0.5f);
		camera.mouseLook(&input, 0.5);
		input.updateMouseMovement(&display);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.perspective(70.0, display.getWidth(), display.getHeight(), 0.1, 1000.0);
		shader.bind();
		shader.setUniform((char*)"projectionMatrix", camera.getProjectionMatrix());
		shader.setUniform((char*)"viewMatrix", camera.getViewMatrix());
		shader.setUniform((char*)"modelMatrix", mat4::rotate(i, i, i));

		gun_model->draw();

		display.update();
		if (display.wasResized())
			glViewport(0, 0, display.getWidth(), display.getHeight());
		frames++;

	}
	delete gun_model;
	return (0);
}
