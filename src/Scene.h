#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"
#include "Factory.h"

class Engine;

class Scene {
public:
	Scene(Engine* engine);

	void update(float time);
private:
	Engine* engine;
};
