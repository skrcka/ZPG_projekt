#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utils/Observer.h"

class Engine;

class Window : public Subject<Window> {
public:
	Window(Engine* engine, int width, int height, const char *title);
	~Window();
	bool shouldClose() const;
	void swapBuffers() const;

	int getWidth();
	int getHeight();

	void setViewport();
	Engine* getEngine();
	
private:
	Engine* engine;
	GLFWwindow *window;
	int width, height;
};


