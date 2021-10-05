#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include "Object.h"

class Rectangle : public Object {
public:
    Rectangle(float rotation);
    void applyShaders(const char *vertex_shader, const char *fragment_shader);
    void draw();

    float rotation;
private:
    GLuint VAO, VBO, shaderProgram;
};