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
	camera->addListener(assets->getShader("light"));

	flashlight = std::make_unique<DirectionalLight>();
	lights.push_back(std::make_unique<PointLight>(lights.size(), glm::vec3(0.0f, 0.0f, 0.0f)));

	// objects.push_back(std::make_unique<Object>(assets->getModel("sphere"), assets->getShader("phong"), assets->getTransform("transform1")));
	// objects.push_back(std::make_unique<Object>(assets->getModel("sphere"), assets->getShader("const"), assets->getTransform("transform2")));
	// objects.push_back(std::make_unique<Object>(assets->getModel("suzi"), assets->getShader("lambert"), assets->getTransform("transform3")));
	// objects.push_back(std::make_unique<Object>(assets->getModel("suzi_smooth"), assets->getShader("phong"), assets->getTransform("transform4")));
	// objects.push_back(std::make_unique<Object>(assets->getModel("plain"), assets->getShader("lambert"), assets->getTransform("transform5")));
	// objects.push_back(std::make_unique<Object>(assets->getModel("tree"), assets->getShader("phong"), assets->getTransform("transform5")));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxnegx"), assets->getTexture("negx"), Skypos::negx));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxnegy"), assets->getTexture("negy"), Skypos::negy));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxnegz"), assets->getTexture("negz"), Skypos::negz));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxposx"), assets->getTexture("posx"), Skypos::posx));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxposy"), assets->getTexture("posy"), Skypos::posy));
	skybox.push_back(std::make_unique<Skybox>(assets->getModel("plain_uv"), assets->getShader("const_texture"), assets->getTransform("skyboxposz"), assets->getTexture("posz"), Skypos::posz));
	for (auto &s : skybox)
		camera->addListener(s.get());

	objects.push_back(std::make_unique<Object>(assets->getModel("plain_uv"), assets->getShader("light"), assets->getTransform("transform5"), assets->getTexture("wood")));
}

void Scene::update(float time)
{
	camera->move();

	for (auto &s : skybox)
	{
		s->getShader()->useShader();
		camera->notify();
		s->draw();
	}

	for (auto &o : objects)
	{
		o->getShader()->useShader();
		camera->notify();
		for(auto &l : lights)
			assets->getShader("light")->applyLight(l.get());
		o->draw();
	}
	glUseProgram(0);
}

Camera *Scene::getCamera()
{
	return camera.get();
}