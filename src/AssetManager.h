#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Transforms/Transform.h"
#include "Shaders/Shader.h"
#include "Models/Model.h"
#include "Camera.h"

class Engine;

class AssetManager {
public:
	AssetManager(Engine* e);
	AssetManager(AssetManager&) = delete;

	Shader* getShader(std::string name);
	Model* getModel(std::string name);
	glm::vec3 *getLight();
	Transform* getTransform(std::string name);

private:
	std::map<std::string, std::unique_ptr<Shader>> shaders;
	std::map<std::string, std::unique_ptr<Model>> models;
	std::unique_ptr<glm::vec3> light;
	std::map<std::string, std::unique_ptr<Transform>> transforms;
};
