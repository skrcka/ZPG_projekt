#include <glm/ext.hpp>
#include "AssetManager.h"
#include "Models/Sphere.h"
#include "Models/Plain.h"
#include "Models/Suzi_flat.h"
#include "Models/Suzi_smooth.h"
#include "Models/Tree.h"
#include "Models/Plain_uv.h"
#include "Engine.h"

AssetManager::AssetManager(Engine *e)
{
	const char *const_vertex_shader_path = "../src/Shaders/Vertex_shader_Const.glsl";
	const char *const_fragment_shader_path = "../src/Shaders/Fragment_shader_Const.glsl";
	const char *texture_fragment_shader_path = "../src/Shaders/Fragment_shader_Texture.glsl";
	const char *lambert_vertex_shader_path = "../src/Shaders/Vertex_shader_Lambert.glsl";
	const char *lambert_fragment_shader_path = "../src/Shaders/Fragment_shader_Lambert.glsl";
	const char *phong_vertex_shader_path = "../src/Shaders/Vertex_shader_Phong.glsl";
	const char *phong_fragment_shader_path = "../src/Shaders/Fragment_shader_Phong.glsl";
	shaders.insert({"const", std::make_unique<Shader>(const_vertex_shader_path, const_fragment_shader_path)});
	shaders.insert({"lambert", std::make_unique<Shader>(lambert_vertex_shader_path, lambert_fragment_shader_path)});
	shaders.insert({"phong", std::make_unique<Shader>(phong_vertex_shader_path, phong_fragment_shader_path)});
	shaders.insert({"const_texture", std::make_unique<Shader>(const_vertex_shader_path, texture_fragment_shader_path)});

	light = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
	shaders["phong"]->applyLight(*light.get());

	transforms.insert({"transform1", std::make_unique<Transform>()});
	transforms.insert({"transform2", std::make_unique<Transform>()});
	transforms.insert({"transform3", std::make_unique<Transform>()});
	transforms.insert({"transform4", std::make_unique<Transform>()});
	transforms.insert({"transform5", std::make_unique<Transform>()});

	transforms.insert({"skyboxnegx", std::make_unique<Transform>()});
	transforms["skyboxnegx"]->rotate(.0, .0, glm::pi<float>() / 2);

	transforms.insert({"skyboxnegy", std::make_unique<Transform>()});
	transforms["skyboxnegy"]->rotate(.0, glm::pi<float>() / 2, .0);
	
	transforms.insert({"skyboxnegz", std::make_unique<Transform>()});
	transforms["skyboxnegz"]->rotate(glm::pi<float>() / 2, glm::pi<float>() / 2, .0);
	
	transforms.insert({"skyboxposx", std::make_unique<Transform>()});
	transforms["skyboxposx"]->rotate(.0, .0, glm::pi<float>() / 2);

	transforms.insert({"skyboxposy", std::make_unique<Transform>()});
	transforms["skyboxposy"]->rotate(.0, glm::pi<float>() / 2, .0);
	
	transforms.insert({"skyboxposz", std::make_unique<Transform>()});
	transforms["skyboxposz"]->rotate(glm::pi<float>() / 2, glm::pi<float>() / 2, .0);

	transforms["transform1"]->move(2.0f, 0, 0);
	transforms["transform2"]->move(-2.0f, 0, 0);
	transforms["transform3"]->move(0, 0, 2.0f);
	transforms["transform4"]->move(0, 0, -2.0f);
	transforms["transform5"]->move(0, -1.0f, 0);
	transforms["transform5"]->rotate(glm::pi<float>()/2, glm::pi<float>()/2, .0);

	models.insert({"sphere", std::make_unique<Model>(sphere, 6, 2880, GL_TRIANGLES)});
	models.insert({"plain", std::make_unique<Model>(plain, 6, 6, GL_TRIANGLES)});
	models.insert({"suzi", std::make_unique<Model>(suziFlat, 6, 2904, GL_TRIANGLES)});
	models.insert({"suzi_smooth", std::make_unique<Model>(suziSmooth, 6, 2904, GL_TRIANGLES)});
	models.insert({"tree", std::make_unique<Model>(tree, 6, 92814, GL_TRIANGLES)});
	models.insert({"plain_uv", std::make_unique<Model>(plain_uv, 8, 6, GL_TRIANGLES)});

	textures.insert({"xd", std::make_unique<Texture>("../src/Textures/wood.jpg", textures.size())});
	textures.insert({"negx", std::make_unique<Texture>("../src/Textures/cubemap/negx.jpg", textures.size())});
	textures.insert({"negy", std::make_unique<Texture>("../src/Textures/cubemap/negy.jpg", textures.size())});
	textures.insert({"negz", std::make_unique<Texture>("../src/Textures/cubemap/negz.jpg", textures.size())});
	textures.insert({"posx", std::make_unique<Texture>("../src/Textures/cubemap/posx.jpg", textures.size())});
	textures.insert({"posy", std::make_unique<Texture>("../src/Textures/cubemap/posy.jpg", textures.size())});
	textures.insert({"posz", std::make_unique<Texture>("../src/Textures/cubemap/posz.jpg", textures.size())});
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

Texture* AssetManager::getTexture(std::string name){
	return textures[name].get();
}