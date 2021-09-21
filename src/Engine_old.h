#pragma once
#include <vector>
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Utils/utils.h"
#include <memory>
#include <string>
//Include GLM
#include <glm/vec3.hpp>					// Color
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>			// glm::value_ptr
//Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utils/Color.h"

class Engine
{
public:
	void startRendering();

	void onKey(int key, int scancode, int action, int mods);
	void onMove(double x, double y);
	void onClick(int button, int action, double x, double y);

	void addMouse(MouseListener *m)
	{
		mouse.push_back(m);
	}

	void addKeyboard(KeyListener *key)
	{
		keyboard.push_back(key);
	}

	Engine() = delete;
	Engine(int width = 800, int height = 600, const char *title = "test");
	~Engine();
	bool shouldClose() const;
	void swapBuffers() const;

	int getWindowWidth();
	int getWindowHeight();

	void setViewport();

	GLFWwindow* getWindow();

private:
	GLFWwindow* window;
	std::vector<MouseListener *> mouse;
	std::vector<KeyListener *> keyboard;
	int windowWidth, windowHeight;
	std::string windowTitle;
};
