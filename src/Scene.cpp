#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Models/Rectangle.h"

Scene::Scene(Engine *e) : engine(e)
{
	shader = std::make_unique<Shader>(vertex_shader, fragment_shader);
	camera = std::make_unique<Camera>(e->getWindow()->getWidth(), e->getWindow()->getHeight(), glm::vec3(0.0f, 0.0f, 5.0f));
	transform = std::make_unique<Transform>(1.0f);
	transform2 = std::make_unique<Transform>(-1.0f);
	model = std::make_unique<Rectangle>();
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
		//dynamic_cast<Rectangle*>(o.get())->rotation += 0.1;
		o->draw();
	}
}

Camera* Scene::getCamera(){
	return camera.get();
}