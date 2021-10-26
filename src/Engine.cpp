#include "Engine.h"

void Engine::init()
{
	glfwSetErrorCallback([](int err, const char *description) -> void
						 { throw std::runtime_error(description); });

	if (!glfwInit())
	{
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

void Engine::startRendering()
{
	scene = std::make_unique<Scene>(this);
	double last = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!window->shouldClose())
	{
		double current = glfwGetTime();
		float delta = (float)(current - last);
		last = current;

		window->clear();

		scene->update(delta);

		window->swapBuffers();
		glfwPollEvents();
	}
}

void Engine::onKey(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
		{
			scene->getCamera()->goForward = true;
		}
		else if (key == GLFW_KEY_S)
		{
			scene->getCamera()->goBack = true;
		}
		else if (key == GLFW_KEY_D)
		{
			scene->getCamera()->goRight = true;
		}
		else if (key == GLFW_KEY_A)
		{
			scene->getCamera()->goLeft = true;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			scene->getCamera()->goUp = true;
		}
		else if (key == GLFW_KEY_LEFT_CONTROL)
		{
			scene->getCamera()->goDown = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W)
		{
			scene->getCamera()->goForward = false;
		}
		else if (key == GLFW_KEY_S)
		{
			scene->getCamera()->goBack = false;
		}
		else if (key == GLFW_KEY_D)
		{
			scene->getCamera()->goRight = false;
		}
		else if (key == GLFW_KEY_A)
		{
			scene->getCamera()->goLeft = false;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			scene->getCamera()->goUp = false;
		}
		else if (key == GLFW_KEY_LEFT_CONTROL)
		{
			scene->getCamera()->goDown = false;
		}
	}
}

void Engine::onMove(double x, double y)
{
	Camera* cam = this->scene->getCamera();

	double horChange = cam->lastX - x;
	double vertChange = cam->lastY - y;

	cam->lastX = x;
	cam->lastY = y;

	this->scene->getCamera()->rotate(horChange, vertChange);
}

Window *Engine::getWindow()
{
	return window.get();
}

void Engine::onClick(int button, int action, double x, double y)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			printf("camera should move\n");
			scene->getCamera()->shouldRotate = true;
		}
	} else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			printf("camera shouldnt move\n");
			scene->getCamera()->shouldRotate = false;
		}
	}
}

Engine::Engine()
{
	init();
}
