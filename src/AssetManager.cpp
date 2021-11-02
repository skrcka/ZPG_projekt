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
	const char *const_vertex_shader_path = "../src/Shaders/Vertex_shader_Const.glsl";
	const char *const_fragment_shader_path = "../src/Shaders/Fragment_shader_Const.glsl";
	const char *lambert_vertex_shader_path = "../src/Shaders/Vertex_shader_Lambert.glsl";
	const char *lambert_fragment_shader_path = "../src/Shaders/Fragment_shader_Lambert.glsl";
	const char *phong_vertex_shader_path = "../src/Shaders/Vertex_shader_Phong.glsl";
	const char *phong_fragment_shader_path = "../src/Shaders/Fragment_shader_Phong.glsl";
	shaders.insert({"const", std::make_unique<Shader>(const_vertex_shader_path, const_fragment_shader_path)});
	shaders.insert({"lambert", std::make_unique<Shader>(lambert_vertex_shader_path, lambert_fragment_shader_path)});
	shaders.insert({"phong", std::make_unique<Shader>(phong_vertex_shader_path, phong_fragment_shader_path)});

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
}

Transform* AssetManager::getTransform(std::string name){
	return transforms[name].get();
}

Model* AssetManager::getModel(std::string name){
	return models[name].get();
}

Shader* AssetManager::getShader(std::string name){
	return shaders[name].get();
}