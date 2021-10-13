#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include "Model.h"

class Rectangle : public Model {
public:
    Rectangle();
    GLuint getVAO();
    GLuint getVBO();

private:
    GLuint VAO, VBO;
};