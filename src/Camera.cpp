#include "Camera.h"
#include "Window.h"

Camera::Camera(int width, int height, glm::vec3 position, Window* window)
	: position(position), goUp(false), goDown(false), goForward(false), goBack(false), goLeft(false), goRight(false), shouldRotate(false), lastY(0), lastX(0), window(window)
{
	yaw = -90.0f;
	pitch = 0.0f;
	movementSpeed = 0.1f;
	viewMat = glm::lookAt(position, position + orientation, worldUp);
	projMat = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	calcOrientation();
	window->addListener(this);
	updated(window);
}

void Camera::updated(Window* window){
	int width = window->getWidth();
	int height = window->getHeight();
	projMat = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	notify();
}

void Camera::onResize(int w, int h){
	projMat = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);
}

void Camera::calcOrientation()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	orientation = glm::normalize(front);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(orientation, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, orientation));
}

void Camera::calcView()
{
	viewMat = glm::lookAt(position, position + orientation, worldUp);
}

glm::mat4 Camera::getView()
{
	return viewMat;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::mat4 Camera::getProj()
{
	return projMat;
}

void Camera::move()
{
	if (goForward)
		position += orientation * static_cast<GLfloat>(movementSpeed);
	if (goBack)
		position -= orientation * static_cast<GLfloat>(movementSpeed);
	if (goLeft)
		position -= right * static_cast<GLfloat>(movementSpeed);
	if (goRight)
		position += right * static_cast<GLfloat>(movementSpeed);
	if (goUp)
		position += up * static_cast<GLfloat>(movementSpeed);
	if (goDown)
		position -= up * static_cast<GLfloat>(movementSpeed);
	calcView();
}

void Camera::rotate(double xoffset, double yoffset, GLboolean constrainPitch)
{
	if (shouldRotate)
	{
		yaw += xoffset * sensitivity;
		pitch -= yoffset * sensitivity;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}
		calcOrientation();
		calcView();
	}
}
