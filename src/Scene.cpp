#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Models/Rectangle.h"

Scene::Scene(Engine *e) : engine(e)
{
	shader = std::make_unique<Shader>(vertex_shader, fragment_shader);
	transform = std::make_unique<Transform>(1.0f);
	transform2 = std::make_unique<Transform>(-1.0f);
	model = std::make_unique<Rectangle>();
	objects.push_back(std::make_unique<Object>(model.get(), shader.get(), transform.get()));
	objects.push_back(std::make_unique<Object>(model.get(), shader.get(), transform2.get()));
}

void Scene::update(float time)
{
	//printf("%f\n", time);
	transform->changeRotation(transform->getRotation() + 0.1f);
	transform2->changeRotation(transform->getRotation() + 0.1f);
	for(auto& o : objects){
		//dynamic_cast<Rectangle*>(o.get())->rotation += 0.1;
		o->draw();
	}
}
