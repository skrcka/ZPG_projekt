#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Shader {
public:
    Shader(const char *vertex_shader, const char *fragment_shader);
    void useShader();
    void applyRotation(float rotation);

    GLuint getShaderProgram();
private:
    GLuint shaderProgram;
};