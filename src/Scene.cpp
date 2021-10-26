#include <glm/ext.hpp>
#include "Scene.h"
#include "Engine.h"
#include "Models/Sphere.h"
#include "Models/Plain.h"
#include "Models/Suzi_flat.h"
#include "Models/Suzi_smooth.h"
#include "Models/Tree.h"

Scene::Scene(Engine *e) : engine(e)
{
	assets = std::make_unique<AssetManager>(e);
}

void Scene::update(float time)
{
	assets->getTransform("transform1")->rotate(assets->getTransform("transform1")->getRotationX() + 0.01, 0, 0);
	assets->getTransform("transform2")->rotate(assets->getTransform("transform2")->getRotationX() + 0.01, 0, 0);
	assets->update(time);
}

Camera *Scene::getCamera()
{
	return assets->getCamera();
}