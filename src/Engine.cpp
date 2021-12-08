#include "Engine.h"
#include <IL/il.h>

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
		else if (key == GLFW_KEY_LEFT_SHIFT)
		{
			scene->getCamera()->shouldRotate = true;
		}
		else if (key == GLFW_KEY_F)
		{
			scene->getFlashlight()->toggle();
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
		else if (key == GLFW_KEY_LEFT_SHIFT)
		{
			scene->getCamera()->shouldRotate = false;
		}
	}
}

void Engine::onMove(double x, double y)
{
	Camera *cam = this->scene->getCamera();

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

void Engine::onResize(int w, int h)
{
	this->scene->getCamera()->onResize(w, h);
}

void Engine::onClick(int button, int action, double x, double y)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			scene->getCamera()->shouldRotate = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			int newy = window->getHeight() - y;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			if (depth >= 1.0)
				return;

			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::mat4 view = scene->getCamera()->getView();
			glm::mat4 projection = scene->getCamera()->getProj();
			glm::vec4 viewPort = glm::vec4(0, 0, window->getWidth(), window->getHeight());
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

			scene->addObjectOnPos(pos.x, pos.y, pos.z);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			scene->getCamera()->shouldRotate = false;
		}
	}
}

Engine::Engine()
{
	glfwSetErrorCallback([](int err, const char *description) -> void
						 { throw std::runtime_error(description); });

	if (!glfwInit())
	{
		throw std::runtime_error("failed to init glfw");
	}

	window = std::make_unique<Window>(this, 800, 600, "Gamewindow");

	ilInit();
	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glEnable(GL_STENCIL_TEST));
	GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
	glStencilMask(0xFF);			   // enable writing to the stencil buffer
	/*
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3) {
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	
	GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
	*/
}
