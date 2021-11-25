#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Utils/Observer.h"

class Window;

const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera : public Subject<Camera>, public Observer<Window>
{
public:
	Camera(int width, int height, glm::vec3 position, Window* window);

	glm::mat4 getView();
	glm::mat4 getProj();
	void calcOrientation();
	void onResize(int w, int h);
	void calcView();
	void move();
	void rotate(double xoffset, double yoffset, GLboolean constrainPitch = true);
	void updated(Window* window);
	glm::vec3 getPosition();
	glm::vec3 getOrientation();
	bool goUp, goDown, goLeft, goRight, goForward, goBack, shouldRotate;
	double lastX, lastY;
private:
	Window* window;
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat;
	glm::mat4 projMat;
	GLfloat movementSpeed;
	GLfloat sensitivity = 0.05f;
	GLfloat pitch;
	GLfloat yaw;
};