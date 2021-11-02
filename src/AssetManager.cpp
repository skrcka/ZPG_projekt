#include <glm/ext.hpp>
#include "AssetManager.h"
#include "Models/Sphere.h"
#include "Models/Plain.h"
#include "Models/Suzi_flat.h"
#include "Models/Suzi_smooth.h"
#include "Models/Tree.h"
#include "Engine.h"

AssetManager::AssetManager(Engine *e)
{
	const char *const_vertex_shader_path = "../src/Shaders/Vertex_shader_Const.shader";
	const char *const_fragment_shader_path = "../src/Shaders/Fragment_shader_Const.shader";
	const char *lambert_vertex_shader_path = "../src/Shaders/Vertex_shader_Lambert.shader";
	const char *lambert_fragment_shader_path = "../src/Shaders/Fragment_shader_Lambert.shader";
	const char *phong_vertex_shader_path = "../src/Shaders/Vertex_shader_Phong.shader";
	const char *phong_fragment_shader_path = "../src/Shaders/Fragment_shader_Phong.shader";
	shaders.insert({"const", std::make_unique<Shader>(const_vertex_shader_path, const_fragment_shader_path)});
	shaders.insert({"lambert", std::make_unique<Shader>(lambert_vertex_shader_path, lambert_fragment_shader_path)});
	shaders.insert({"phong", std::make_unique<Shader>(phong_vertex_shader_path, phong_fragment_shader_path)});

	camera = std::make_unique<Camera>(e->getWindow()->getWidth(), e->getWindow()->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f), e->getWindow());
	camera->addListener(shaders["const"].get());
	camera->addListener(shaders["lambert"].get());
	camera->addListener(shaders["phong"].get());

	light = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
	shaders["phong"]->applyLight(*light.get());

	transforms.insert({"transform1", std::make_unique<Transform>()});
	transforms.insert({"transform2", std::make_unique<Transform>()});
	transforms.insert({"transform3", std::make_unique<Transform>()});
	transforms.insert({"transform4", std::make_unique<Transform>()});
	transforms.insert({"transform5", std::make_unique<Transform>()});
	transforms["transform1"]->move(2.0f, 0, 0);
	transforms["transform2"]->move(-2.0f, 0, 0);
	transforms["transform3"]->move(0, 0, 2.0f);
	transforms["transform4"]->move(0, 0, -2.0f);
	transforms["transform5"]->move(0, -1.0f, 0);

	models.insert({"sphere", std::make_unique<Model>(sphere, 2880 * (3 + 3), GL_TRIANGLES)});
	models.insert({"plain", std::make_unique<Model>(plain, 6 * 6, GL_TRIANGLES)});
	models.insert({"suzi", std::make_unique<Model>(suziFlat, 2904 * 6, GL_TRIANGLES)});
	models.insert({"suzi_smooth", std::make_unique<Model>(suziSmooth, 2904 * 6, GL_TRIANGLES)});
	models.insert({"tree", std::make_unique<Model>(tree, 92814 * 6, GL_TRIANGLES)});

	objects.push_back(std::make_unique<Object>(models["sphere"].get(), shaders["phong"].get(), transforms["transform1"].get()));
	objects.push_back(std::make_unique<Object>(models["sphere"].get(), shaders["const"].get(), transforms["transform2"].get()));
	objects.push_back(std::make_unique<Object>(models["suzi"].get(), shaders["lambert"].get(), transforms["transform3"].get()));
	objects.push_back(std::make_unique<Object>(models["suzi_smooth"].get(), shaders["phong"].get(), transforms["transform4"].get()));
	objects.push_back(std::make_unique<Object>(models["plain"].get(), shaders["lambert"].get(), transforms["transform5"].get()));
	objects.push_back(std::make_unique<Object>(models["tree"].get(), shaders["phong"].get(), transforms["transform5"].get()));
}

Camera *AssetManager::getCamera()
{
	return camera.get();
}

void AssetManager::drawObjects(){
	for (auto &o : objects)
	{
		camera->notify();
		o->draw();
	}
}

void AssetManager::update(float time){
	camera->move();
	drawObjects();
}

Transform* AssetManager::getTransform(std::string name){
	return transforms[name].get();
}