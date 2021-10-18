#include "Engine.h"

void Engine::init() {
	glfwSetErrorCallback([] (int err, const char* description) -> void {
		throw std::runtime_error(description);
	});

	if (!glfwInit()) {
		throw std::runtime_error("failed to init glfw");
	}

	window = std::make_unique<Window>(this, 800, 600, "Gamewindow");

	/*
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3) {
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glEnable(GL_STENCIL_TEST));
	GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
	*/
}

void Engine::startRendering() {
	scene = std::make_unique<Scene>(this);
	double last = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!window->shouldClose()) {
		double current = glfwGetTime();
		float delta = (float) (current - last);
		last = current;

		window->clear();

		scene->update(delta);

		window->swapBuffers();
		glfwPollEvents();
	}
}

void Engine::onKey(int key, int scancode, int action, int mods) {
	/*for(auto i: keyboard) {
		i->onKey(key, scancode, action, mods);
	}*/
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_FORWARD);
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_LEFT);
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_BACKWARD);
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_RIGHT);
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_UP);
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		scene->getCamera()->move(CAM_DOWN);
	}
}

void Engine::onMove(double x, double y) {
	/*for(auto i: mouse) {
		i->onMove(x, y);
	}*/
	printf("move %f %f \n", x, y);
	double xmove, ymove;
	xmove = x - (window->getWidth() / 2);
	ymove = y - (window->getHeight() / 2);

	window->resetCursorPos();

	this->scene->getCamera()->rotate(xmove, ymove);
}

Window* Engine::getWindow() {
	return window.get();
}

void Engine::onClick(int button, int action, double x, double y) {
	if (action != GLFW_PRESS) {
		return;
	}
}

Engine::Engine(){
	init();
}
