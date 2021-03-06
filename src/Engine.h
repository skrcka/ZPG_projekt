#pragma once

#include <stdexcept>
#include "Utils/utils.h"
#include <glm/vec4.hpp>
#include <memory>
#include "Utils/Singleton.h"
#include "Input/KeyListener.h"
#include "Input/MouseListener.h"
#include "Window.h"
#include "Scene.h"

class Engine : public KeyListener, public MouseListener {
public:
	void startRendering();

	virtual void onKey(int key, int scancode, int action, int mods) override;
	virtual void onMove(double x, double y) override;
	virtual void onClick(int button, int action, double x, double y);
	virtual void onResize(int w, int h);

	Window* getWindow();

	//Scene *getScene();

	Engine();
protected:
	
	friend Singleton<Engine>;

private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Scene> scene;
	std::vector<MouseListener*> mouse;
	std::vector<KeyListener*> keyboard;
};
