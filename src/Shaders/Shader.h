#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Shader {
public:
    Shader(const char *vertex_shader_path, const char *fragment_shader_path);
    ~Shader();
    void useShader();
    void applyRotation(glm::mat4 M);

    GLuint getShaderProgram();
private:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
};