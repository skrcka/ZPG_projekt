#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include "Camera.h"

class Shader {
public:
    Shader(const char *vertex_shader_path, const char *fragment_shader_path);
    ~Shader();
    void useShader();
    void applyTransform(glm::mat4 M);
    void applyLight(glm::vec3 lightPos);
    void applyCamera(Camera *cam);
    glm::vec3 getLightPos();

    GLuint getShaderProgram();
private:
    glm::vec3 lightPos;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
};