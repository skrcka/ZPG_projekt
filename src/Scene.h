#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>
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
	std::map<std::string, std::unique_ptr<Shader>> shaders;
	std::map<std::string, std::unique_ptr<Model>> models;
	std::unique_ptr<glm::vec3> light;
	std::map<std::string, std::unique_ptr<Transform>> transforms;
};
