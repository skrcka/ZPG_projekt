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

	const char *light_vertex_shader_path = "../src/Shaders/Vertex_shader_Light.glsl";
	const char *light_fragment_shader_path = "../src/Shaders/Fragment_shader_Light.glsl";

	const char *material_fragment_shader_path = "../src/Shaders/Fragment_shader_Light_Material.glsl";

	const char *lambert_vertex_shader_path = "../src/Shaders/Vertex_shader_Lambert.glsl";
	const char *lambert_fragment_shader_path = "../src/Shaders/Fragment_shader_Lambert.glsl";

	const char *phong_vertex_shader_path = "../src/Shaders/Vertex_shader_Phong.glsl";
	const char *phong_fragment_shader_path = "../src/Shaders/Fragment_shader_Phong.glsl";

	const char *plain_obj_path = "../src/Models/plane.obj";
	const char *house_path = "../src/Models/house.obj";
	const char *zombie_path = "../src/Models/zombie.obj";
	const char *teren_path = "../src/Models/teren.obj";

	shaders.insert({"const", std::make_unique<Shader>(const_vertex_shader_path, const_fragment_shader_path)});
	shaders.insert({"lambert", std::make_unique<Shader>(lambert_vertex_shader_path, lambert_fragment_shader_path)});
	shaders.insert({"phong", std::make_unique<Shader>(phong_vertex_shader_path, phong_fragment_shader_path)});
	shaders.insert({"const_texture", std::make_unique<Shader>(const_vertex_shader_path, texture_fragment_shader_path)});
	shaders.insert({"light", std::make_unique<Shader>(light_vertex_shader_path, light_fragment_shader_path)});
	shaders.insert({"material", std::make_unique<Shader>(light_vertex_shader_path, material_fragment_shader_path)});

	//light = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
	//shaders["phong"]->applyLight(*light.get());

	transforms.insert({"transform1", std::make_unique<Transform>()});
	transforms.insert({"transform2", std::make_unique<Transform>()});
	transforms.insert({"transform3", std::make_unique<Transform>()});
	transforms.insert({"transform4", std::make_unique<Transform>()});
	transforms.insert({"transformh", std::make_unique<Transform>()});
	transforms.insert({"transform5", std::make_unique<Transform>()});
	transforms.insert({"transform6", std::make_unique<Transform>()});
	transforms.insert({"transformg", std::make_unique<Transform>()});

	transforms.insert({"skyboxnegx", std::make_unique<Transform>()});
	transforms["skyboxnegx"]->rotate(glm::pi<float>(), .0, -glm::pi<float>() / 2);

	transforms.insert({"skyboxnegy", std::make_unique<Transform>()});
	transforms["skyboxnegy"]->rotate(.0, glm::pi<float>() / 2, .0);

	transforms.insert({"skyboxnegz", std::make_unique<Transform>()});
	transforms["skyboxnegz"]->rotate(glm::pi<float>() / 2, glm::pi<float>() / 2, .0);

	transforms.insert({"skyboxposx", std::make_unique<Transform>()});
	transforms["skyboxposx"]->rotate(.0, .0, glm::pi<float>() / 2);

	transforms.insert({"skyboxposy", std::make_unique<Transform>()});
	transforms["skyboxposy"]->rotate(glm::pi<float>(), -glm::pi<float>() / 2, .0);

	transforms.insert({"skyboxposz", std::make_unique<Transform>()});
	transforms["skyboxposz"]->rotate(-glm::pi<float>() / 2, -glm::pi<float>() / 2, .0);

	transforms["transform1"]->move(2.0f, 0, 0);
	transforms["transform2"]->move(-2.0f, 0, 0);
	transforms["transform3"]->move(0, 0, 2.0f);
	transforms["transform4"]->move(0, -1.0f, -2.0f);
	transforms["transformh"]->move(0, -1.0f, -2.0f);
	transforms["transform5"]->move(0, -0.7f, 0);
	transforms["transform6"]->move(2.5f, -0.7f, 0);
	transforms["transformg"]->move(0, -1.01f, 0);

	models.insert({"sphere", std::make_unique<Model>(sphere, 6, 2880, GL_TRIANGLES)});
	models.insert({"plain", std::make_unique<Model>(plain, 6, 6, GL_TRIANGLES)});
	models.insert({"suzi", std::make_unique<Model>(suziFlat, 6, 2904, GL_TRIANGLES)});
	models.insert({"suzi_smooth", std::make_unique<Model>(suziSmooth, 6, 2904, GL_TRIANGLES)});
	models.insert({"tree", std::make_unique<Model>(tree, 6, 92814, GL_TRIANGLES)});
	models.insert({"plain_uv", std::make_unique<Model>(plain_uv, 8, 6, GL_TRIANGLES)});
	models.insert({"plain_obj", std::make_unique<Model>(plain_obj_path)});
	models.insert({"house", std::make_unique<Model>(house_path)});
	models.insert({"zombie", std::make_unique<Model>(zombie_path)});
	models.insert({"teren", std::make_unique<Model>(teren_path)});

	textures.insert({"wood", std::make_unique<Texture>("../src/Textures/wood.jpg", textures.size())});
	textures.insert({"house", std::make_unique<Texture>("../src/Textures/house.png", textures.size())});
	textures.insert({"zombie", std::make_unique<Texture>("../src/Textures/zombie.png", textures.size())});
	textures.insert({"grass", std::make_unique<Texture>("../src/Textures/grass.png", textures.size())});
	textures.insert({"negx", std::make_unique<Texture>("../src/Textures/cubemap/negx.jpg", textures.size())});
	textures.insert({"negy", std::make_unique<Texture>("../src/Textures/cubemap/negy.jpg", textures.size())});
	textures.insert({"negz", std::make_unique<Texture>("../src/Textures/cubemap/negz.jpg", textures.size())});
	textures.insert({"posx", std::make_unique<Texture>("../src/Textures/cubemap/posx.jpg", textures.size())});
	textures.insert({"posy", std::make_unique<Texture>("../src/Textures/cubemap/posy.jpg", textures.size())});
	textures.insert({"posz", std::make_unique<Texture>("../src/Textures/cubemap/posz.jpg", textures.size())});

	// ambient(0.1f), diffuse(1.0f), specular(1.0f), shininess(30), intensity(1.0f)
	materials.insert({"material1", std::make_unique<Material>(0.1f, 1.0f, 1.0f, 60)});
}

Transform *AssetManager::getTransform(std::string name)
{
	return transforms[name].get();
}

Transform *AssetManager::getNewTransform(float x, float y, float z)
{
	std::unique_ptr<Transform> t = std::make_unique<Transform>();
	t->move(x, y, z);
	Transform *pt = t.get();
	gentransforms.push_back(std::move(t));
	return pt;
}

Model *AssetManager::getModel(std::string name)
{
	return models[name].get();
}

Shader *AssetManager::getShader(std::string name)
{
	return shaders[name].get();
}

Texture *AssetManager::getTexture(std::string name)
{
	return textures[name].get();
}

Material *AssetManager::getMaterial(std::string name){
	return materials[name].get();
}
