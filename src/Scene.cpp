#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Models/Sphere.h"
#include "Models/Plain.h"
#include "Models/Suzi_flat.h"
#include "Models/Suzi_smooth.h"
#include "Models/Tree.h"

Scene::Scene(Engine *e) : engine(e)
{
	assets = std::make_unique<AssetManager>(e);
	camera = std::make_unique<Camera>(e->getWindow()->getWidth(), e->getWindow()->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f), e->getWindow());
	camera->addListener(assets->getShader("const"));
	camera->addListener(assets->getShader("lambert"));
	camera->addListener(assets->getShader("phong"));

	objects.push_back(std::make_unique<Object>(assets->getModel("sphere"), assets->getShader("phong"), assets->getTransform("transform1")));
	objects.push_back(std::make_unique<Object>(assets->getModel("sphere"), assets->getShader("const"), assets->getTransform("transform2")));
	objects.push_back(std::make_unique<Object>(assets->getModel("suzi"), assets->getShader("lambert"), assets->getTransform("transform3")));
	objects.push_back(std::make_unique<Object>(assets->getModel("suzi_smooth"), assets->getShader("phong"), assets->getTransform("transform4")));
	objects.push_back(std::make_unique<Object>(assets->getModel("plain"), assets->getShader("lambert"), assets->getTransform("transform5")));
	objects.push_back(std::make_unique<Object>(assets->getModel("tree"), assets->getShader("phong"), assets->getTransform("transform5")));
}

void Scene::update(float time)
{
	camera->move();
	for (auto &o : objects)
	{
		camera->notify();
		o->getTransform()->rotate(o->getTransform()->getRotationX() + 0.01, 0, 0);
		o->draw();
	}
}

Camera *Scene::getCamera()
{
	return camera.get();
}