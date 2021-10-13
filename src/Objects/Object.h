#pragma once

#include "Shaders/Shader.h"
#include "Models/Model.h"
#include "Transforms/Transform.h"

class Object {
public:
    Object();
    Object(Model* model, Shader* shader, Transform* transform);
    void applyShader(Shader* shader);
    void applyModel(Model* model);
    void applyTransform(Transform* transform);
    void draw();
private:
    Model* model;
    Shader* shader;
    Transform* transform;
};