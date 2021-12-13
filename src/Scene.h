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
#include "AssetManager.h"
#include "Objects/Skybox.h"
#include "Objects/Enemy.h"
#include "Lights/Flashlight.h"
#include "Lights/DirectionalLight.h"

class Engine;

class Scene
{
public:
	Scene(Engine *engine);

	void update(float time);
	Camera *getCamera();
	Flashlight *getFlashlight();
	void addObjectOnPos(float x, float y, float z);
	void deleteObjectById(int id);

private:
	Engine *engine;
	std::unique_ptr<AssetManager> assets;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Skybox>> skybox;
	std::vector<std::unique_ptr<PointLight>> lights;
	std::unique_ptr<DirectionalLight> dirLight;
	std::unique_ptr<Flashlight> flashlight;
};
