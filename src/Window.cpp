#include <stdexcept>
#include "Window.h"
#include "Engine.h"

Window::Window(Engine* engine, int width, int height, const char *title) : engine(engine), width(width), height(height) {
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("could not create window");
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onKey(key, scancode, action, mods);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onMove(x, y);
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		win->getEngine()->onClick(button, action, xpos, ypos);
	});
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) -> void {
		GL_CHECK(glViewport(0, 0, w, h));
		Window *win = (Window *) glfwGetWindowUserPointer(window);
		win->width = w;
		win->height = h;
		win->notify();
	});
}

Engine* Window::getEngine(){
	return this->engine;
}

bool Window::shouldClose() const {
	return (bool) glfwWindowShouldClose(window);
}

void Window::swapBuffers() const {
	glfwSwapBuffers(window);

}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

void Window::setViewport() {
	GL_CHECK(glViewport(0, 0, width, height));

}

Window::~Window() {
	glfwDestroyWindow(window);
}
