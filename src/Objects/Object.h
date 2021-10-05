#pragma once

#include "Shaders/Shader.h"

class Object {
public:
    virtual void applyShader(Shader* shader) = 0;
    virtual void draw() = 0;
    virtual ~Object() = default;
private:
    GLuint VAO, VBO;
    Shader* shader;
};