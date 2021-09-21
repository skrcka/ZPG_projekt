#include "Engine.h"

Engine::Engine(int width, int height, const char *title) : windowHeight(height), windowWidth(width), windowTitle(title)
{
	// Window
	if (!glfwInit())
		exit(EXIT_FAILURE);
	/*
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		throw std::runtime_error("Could not initialize glew");
	}
	if (!GLEW_VERSION_3_3)
	{
		throw std::runtime_error("At least GLEW 3.3 is required");
	}

	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glEnable(GL_STENCIL_TEST));
	GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
	*/
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		throw std::runtime_error("could not create window");
	}

	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
					   {
						   Engine *Engine = static_cast<Engine *>(glfwGetWindowUserPointer(window));
						   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
							   glfwSetWindowShouldClose(window, GL_TRUE);
						   printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
					   });
	glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y)
							 { printf("cursor_callback \n"); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
							   {
								   if (action == GLFW_PRESS)
									   printf("button_callback [%d,%d,%d]\n", button, action, mods);
							   });
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) -> void
							  {
								  Engine *Engine = static_cast<Engine *>(glfwGetWindowUserPointer(window));
								  printf("resize %d, %d \n", w, h);
								  glfwGetFramebufferSize(Engine->getWindow(), &Engine->windowWidth, &Engine->windowHeight);
								  float ratio = Engine->windowWidth / (float)Engine->windowHeight;
								  glViewport(0, 0, Engine->windowWidth, Engine->windowHeight);

								  glMatrixMode(GL_PROJECTION);
								  glLoadIdentity();
								  glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
							  });

	glfwSetErrorCallback([](int err, const char *description) -> void
						 { throw std::runtime_error(description); });

	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	float ratio = windowWidth / (float)windowHeight;
	glViewport(0, 0, windowWidth, windowHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glClearColor(255,255,255,255);

}

GLFWwindow* Engine::getWindow(){
	return this->window;
}

void Engine::startRendering()
{
	double last = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double current = glfwGetTime();
		float delta = (float)(current - last);
		last = current;

		glClear(GL_COLOR_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		
		glBegin(GL_POLYGON);
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, 0.6f, 0.f);
			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, 0.6f, 0.f);
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(0.6f, -0.6f, 0.f);
			glColor3f(1.f, 1.f, 0.f);
			glVertex3f(-0.6f, -0.6f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Engine::onKey(int key, int scancode, int action, int mods)
{
	for (auto i : keyboard)
	{
		i->onKey(key, scancode, action, mods);
	}
}

void Engine::onMove(double x, double y)
{
	for (auto i : mouse)
	{
		i->onMove(x, y);
	}
}

void Engine::onClick(int button, int action, double x, double y)
{
	if (action != GLFW_PRESS)
	{
		return;
	}

	int newY = this->getWindowHeight() - y;
	float depth;

	glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	int index;
	glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	glm::vec3 screenX = glm::vec3(x, newY, depth);

	glm::vec4 viewPort = glm::vec4(0, 0, this->getWindowWidth(), this->getWindowHeight());
}

// Window
bool Engine::shouldClose() const
{
	return (bool)glfwWindowShouldClose(window);
}

void Engine::swapBuffers() const
{
	glfwSwapBuffers(window);
}

int Engine::getWindowWidth()
{
	return windowWidth;
}

int Engine::getWindowHeight()
{
	return windowHeight;
}

void Engine::setViewport()
{
	GL_CHECK(glViewport(0, 0, windowWidth, windowHeight));
}

Engine::~Engine()
{
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
