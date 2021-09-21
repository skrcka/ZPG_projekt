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
	double last = glfwGetTime();
	while (!window->shouldClose()) {
		double current = glfwGetTime();
		float delta = (float) (current - last);
		last = current;

		//TODO

		window->swapBuffers();
		glfwPollEvents();
	}
}

void Engine::onKey(int key, int scancode, int action, int mods) {
	for(auto i: keyboard) {
		i->onKey(key, scancode, action, mods);
	}
}

void Engine::onMove(double x, double y) {
	for(auto i: mouse) {
		i->onMove(x, y);
	}
}

Window &Engine::getWindow() {
	return *window;
}

void Engine::onClick(int button, int action, double x, double y) {
	if (action != GLFW_PRESS) {
		return;
	}
}

Engine::Engine(){
	init();
}
