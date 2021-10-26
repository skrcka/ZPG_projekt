#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "Objects/Object.h"
#include "Camera.h"

class Engine;

enum ShaderType {
	Const,
	Lambert,
	Phong,
};

class AssetManager {
public:
	AssetManager(Engine* e);
	AssetManager(AssetManager&) = delete;

	Camera* getCamera();
	Object* getObject(std::string name);
	Shader* getShader(std::string name);
	Model* getModel(std::string name);
	glm::vec3 *getLight();
	Transform* getTransform(std::string name);

	void drawObjects();
	void update(float time);

private:
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Object>> objects;
	std::map<std::string, std::unique_ptr<Shader>> shaders;
	std::map<std::string, std::unique_ptr<Model>> models;
	std::unique_ptr<glm::vec3> light;
	std::map<std::string, std::unique_ptr<Transform>> transforms;
};
