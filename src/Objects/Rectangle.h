#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include "Object.h"

class Rectangle : public Object {
public:
    Rectangle();
    Rectangle(float rotation);
    void applyShader(Shader* shader);
    void draw();

    float rotation;
private:
    GLuint VAO, VBO;
    Shader* shader;
};