#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

class Model {
public:
    Model(const float points[], int sizeRow, int rowCount, GLenum mode = GL_TRIANGLES);
    Model(const char* path);
    GLuint getVAO();
    GLuint getVBO();
    GLenum getMode();
    int getSize();

private:
    GLuint VAO, VBO;
    GLenum mode;
    int pointCount, sizeRow, rowCount;
};