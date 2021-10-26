#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Model {
public:
    Model(const float points[], int size, GLenum mode = GL_TRIANGLES);
    GLuint getVAO();
    GLuint getVBO();
    GLenum getMode();
    int getSize();

private:
    GLuint VAO, VBO;
    GLenum mode;
    int pointCount, size;
};