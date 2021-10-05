#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Objects/Rectangle.h"

Scene::Scene(Engine *e) : engine(e)
{
	objects.push_back(std::make_unique<Rectangle>(0));
	objects.push_back(std::make_unique<Rectangle>(-1.0f));
	objects.push_back(std::make_unique<Rectangle>(1.0f));
	for(auto& o : objects){
		o->applyShaders(vertex_shader, fragment_shader);
	}
}

void Scene::update(float time)
{
	//printf("%f\n", time);

	for(auto& o : objects){
		//dynamic_cast<Rectangle*>(o.get())->rotation += 0.1;
		o->draw();
	}
}
