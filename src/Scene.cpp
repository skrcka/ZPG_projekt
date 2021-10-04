#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"
#include "Objects/Rectangle.h"

Scene::Scene(Engine *e) : engine(e)
{
	objects.push_back(std::make_unique<Rectangle>(0,0,0,0));
	for(auto& o : objects){
		o->applyShaders(vertex_shader, fragment_shader);
	}
}

void Scene::update(float time)
{
	//printf("%f\n", time);

	//create and compile shaders

	for(auto& o : objects){
		o->draw();
	}
	 //mode,first,count
}
