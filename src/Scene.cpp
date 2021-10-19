#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Models/Sphere.h"

Scene::Scene(Engine *e) : engine(e)
{
	const char* vertex_shader_path = "../src/Shaders/Vertex_shader2.shader";
	const char* fragment_shader_path = "../src/Shaders/Fragment_shader2.shader";
	shader = std::make_unique<Shader>(vertex_shader_path, fragment_shader_path);
	camera = std::make_unique<Camera>(e->getWindow()->getWidth(), e->getWindow()->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f));
	transform = std::make_unique<Transform>(1.0f);
	transform2 = std::make_unique<Transform>(-1.0f);
	model = std::make_unique<Model>(sphere, 2880 * (3+3));
	objects.push_back(std::make_unique<Object>(model.get(), shader.get(), transform.get()));
	objects.push_back(std::make_unique<Object>(model.get(), shader.get(), transform2.get()));
}

void Scene::update(float time)
{
	//printf("%f\n", time);
	camera->updateShader(shader->getShaderProgram());
	transform->changeRotation(transform->getRotation() + 0.1f);
	transform2->changeRotation(transform->getRotation() + 0.1f);
	for(auto& o : objects){	
		o->draw();
	}
}

Camera* Scene::getCamera(){
	return camera.get();
}