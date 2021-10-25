#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) : position(position)
{
	yaw = -90.0f;
	pitch = 0.0f;
	movementSpeed = 0.1f;
	viewMat = glm::lookAt(position, position + orientation, worldUp);
	projMat = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	calcOrientation();
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

glm::mat4 Camera::getView(){
	return viewMat;
}

glm::vec3 Camera::getPosition(){
	return position;
}

glm::mat4 Camera::getProj(){
	return projMat;
}

void Camera::move(Camera_movement direction)
{
	GLfloat velocity = movementSpeed;
	switch (direction)
	{
	case CAM_FORWARD:
		position += orientation * velocity;
		break;
	case CAM_BACKWARD:
		position -= orientation * velocity;
		break;
	case CAM_LEFT:
		position -= right * velocity;
		break;
	case CAM_RIGHT:
		position += right * velocity;
		break;
	case CAM_UP:
		position += up * velocity;
		break;
	case CAM_DOWN:
		position -= up * velocity;
		break;
	}
	calcView();
}

void Camera::rotate(double xoffset, double yoffset, GLboolean constrainPitch)
{
	yaw += xoffset * sensitivity * 0.1f;
	pitch -= yoffset * sensitivity * 0.1f;

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
