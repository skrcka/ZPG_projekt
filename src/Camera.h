#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

enum Camera_movement {
	CAM_FORWARD,
	CAM_BACKWARD,
	CAM_LEFT,
	CAM_RIGHT,
	CAM_UP,
	CAM_DOWN
};

class Camera
{
public:
	// Stores the main vectors of the camera
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

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	void updateShader(GLuint shaderProg);
	void calcOrientation();
	void calcView();
	void move(Camera_movement direction);
	void rotate(double xoffset, double yoffset, GLboolean constrainPitch = true);

};