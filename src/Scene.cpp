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

	dirLight = std::make_unique<DirectionalLight>();
	lights.push_back(std::make_unique<PointLight>(lights.size(), glm::vec3(.0, -2.0f, .0)));

	flashlight = std::make_unique<Flashlight>();
	camera->addListener(flashlight.get());

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

	objects.push_back(std::make_unique<Object>(assets->getModel("teren"), assets->getShader("light"), assets->getTransform("transformg"), assets->getTexture("grass")));
	objects[0]->addId(1);
	objects.push_back(std::make_unique<Object>(assets->getModel("plain_obj"), assets->getShader("material"), assets->getTransform("transform5"), assets->getTexture("wood"), assets->getMaterial("material1")));
	objects.push_back(std::make_unique<Object>(assets->getModel("plain_obj"), assets->getShader("light"), assets->getTransform("transform6"), assets->getTexture("wood")));
	objects.push_back(std::make_unique<Object>(assets->getModel("house"), assets->getShader("light"), assets->getTransform("transformh"), assets->getTexture("house")));

	enemies.push_back(std::make_unique<Enemy>(assets->getModel("zombie"), assets->getShader("light"), assets->getTransform("transform4"), assets->getTexture("zombie")));
	enemies[0]->addMovement(-5, -1, 10);
	enemies[0]->addMovement(-1, 1, 10);
	enemies[0]->addMovement(3, -1, 10);
	enemies[0]->addMovement(5, -1, 10);
}

void Scene::deleteObjectById(int id)
{
	for (int i = 0; i < objects.size(); i++)
		if (objects[i]->getId() == id)
		{
			objects.erase(objects.begin() + i);
			break;
		}
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
		for (auto &l : lights)
			assets->getShader("light")->applyLight(l.get());
		assets->getShader("light")->applyLightCount(lights.size());
		assets->getShader("light")->applyLight(dirLight.get());
		assets->getShader("light")->applyLight(flashlight.get());
		glStencilFunc(GL_ALWAYS, o->getId(), 0xFF);
		o->draw();
	}

	for (auto &e : enemies)
	{
		e->getShader()->useShader();
		camera->notify();
		for (auto &l : lights)
			assets->getShader("light")->applyLight(l.get());
		assets->getShader("light")->applyLightCount(lights.size());
		assets->getShader("light")->applyLight(dirLight.get());
		assets->getShader("light")->applyLight(flashlight.get());
		e->move();

		glm::vec3 enemPos = glm::vec3(e->getTransform()->getX(), e->getTransform()->getY(), e->getTransform()->getZ());
		glm::vec3 camPos = camera->getPosition();
		if(glm::distance(enemPos, camPos) < 1.5)
			exit(0);
		e->draw();
	}
	glUseProgram(0);
}

Camera *Scene::getCamera()
{
	return camera.get();
}

Flashlight *Scene::getFlashlight()
{
	return flashlight.get();
}

void Scene::addObjectOnPos(float x, float y, float z)
{
	Transform *t = assets->getNewTransform(x, y, z);
	objects.push_back(std::make_unique<Object>(assets->getModel("tree"), assets->getShader("phong"), t));
	objects[objects.size()-1]->addId(objects.size());
}
