#pragma once

#include "Shaders/Shader.h"
#include "Models/Model.h"
#include "Transforms/Transform.h"
#include "Textures/Texture.h"

class Object {
public:
    Object();
    Object(Model* model, Shader* shader, Transform* transform);
    Object(Model* model, Shader* shader, Transform* transform, Texture* texture);
    void applyShader(Shader* shader);
    void applyModel(Model* model);
    void applyTransform(Transform* transform);
    Transform* getTransform();
    Shader* getShader();
    Model* getModel();
    Texture* getTexture();
    virtual void draw();
protected:
    Model* model;
    Shader* shader;
    Transform* transform;
    Texture* texture;
};
