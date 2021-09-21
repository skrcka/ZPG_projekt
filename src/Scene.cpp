#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Shaders/Fragment_shader.h"
#include "Shaders/Vertex_shader.h"

Scene::Scene(Engine *e) : engine(e)
{
}

void Scene::update(float time)
{
	//printf("%f\n", time);

	//create and compile shaders

	std::unique_ptr<Rectangle> rec = std::make_unique<Rectangle>(1,1,1,1);
	rec->applyShaders(vertex_shader, fragment_shader);
	rec->draw();
	 //mode,first,count
}
