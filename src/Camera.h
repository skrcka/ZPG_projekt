#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "Window.h"

class Camera {
public:
	Camera(Window &window);
	~Camera();

	void render();
	//Object *find(int id) override;

	const glm::mat4 getLookAt();
	glm::mat4 getPerspective() const;

	void rotateBy(double vert, double hor);
	void setRotation(float vert, float hor);

	void setZFar(float zFar);
	void setZNear(float zNear);

	void forward(float diff);

	void backward(float diff);

	void left(float diff);

	void right(float diff);

    void update(Window &camera);

	glm::vec3 getDirection();

protected:
	void transformed();

private:
	Window &window;

	glm::vec3 up;
	glm::vec3 position;
	glm::vec3 target;

	float v, h;
    float speed;
    float positionX, positionY;
	int width, height;
	float zFar, zNear;
};
