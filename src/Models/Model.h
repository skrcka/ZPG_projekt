#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Model {
public:
    Model();
    GLuint getVAO();
    GLuint getVBO();

private:
    GLuint VAO, VBO;
};