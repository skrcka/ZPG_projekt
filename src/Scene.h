#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"
#include "Factory.h"
#include "Objects/Object.h"
#include "Camera.h"

class Engine;

class Scene {
public:
	Scene(Engine* engine);

	void update(float time);
	Camera* getCamera();
private:
	Engine* engine;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Object>> objects;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Model> model;
	std::unique_ptr<Transform> transform;
	std::unique_ptr<Transform> transform2;
};
