#include "Camera.h"

Camera::Camera(Window &window) :
		window(window),
		up(0.0f, 1.0f, 0.0f),
		target(0.0f),
		v(.0f),
		h(.0f),
		width(800),
		height(600),
		zFar(50.0f),
		zNear(0.1f),
        position(.0f),
        speed(10.0f),
        positionX(.0f),
        positionY(.0f) {
	update(window);
}

Camera::~Camera() {
}

const glm::mat4 Camera::getLookAt() {
	return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::getPerspective() const {
	return glm::perspective(45.0f, 1.0f * width / height, zNear, zFar);
}

void Camera::rotateBy(double vert, double hor) {
	if (vert == 0 && hor == 0) {
		return;
	}

	v += vert;
	h += hor;

	setRotation(v + vert, h + hor);
}

void Camera::setRotation(float vert, float hor) {
	v = vert;
	h = hor;

	target.x = cos(v) * sin(h);
	target.y = sin(v);
	target.z = cos(v) * cos(h);
}

void Camera::setZFar(float zFar) {
	this->zFar = zFar;
}

void Camera::setZNear(float zNear) {
	this->zNear = zNear;
}

void Camera::update(Window &camera) {
	width = camera.getWidth();
	height = camera.getHeight();
}

void Camera::forward(float diff) {
	//move(glm::normalize(target) * diff * speed);
}

void Camera::backward(float diff) {
	//move(-glm::normalize(target) * diff);
}

void Camera::left(float diff) {
	//move(-glm::normalize(glm::cross(target, up)) * diff);
}

void Camera::right(float diff) {
	//move(glm::normalize(glm::cross(target, up)) * diff);
}

glm::vec3 Camera::getDirection() {
	return target;
}

//void Camera::render(RenderContext &context) {}