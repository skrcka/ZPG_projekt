#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include <filesystem>

Scene::Scene(Engine *e) : engine(e)
{
	printf("%s", std::filesystem::current_path());
	shader = std::make_unique<Shader>("/home/skrcka/School/5_SEM/ZPG/1/src/Shaders/Vertex_shader.shader", "/home/skrcka/School/5_SEM/ZPG/1/src/Shaders/Fragment_shader.shader");
	camera = std::make_unique<Camera>(e->getWindow()->getWidth(), e->getWindow()->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f));
	transform = std::make_unique<Transform>(1.0f);
	transform2 = std::make_unique<Transform>(-1.0f);
	model = std::make_unique<Model>();
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