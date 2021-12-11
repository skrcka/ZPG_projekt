#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include "Camera.h"
#include "Utils/Observer.h"
#include "Textures/Texture.h"
#include "Lights/Flashlight.h"
#include "Lights/DirectionalLight.h"
#include "Material.h"

class Shader : public Observer<Camera> {
public:
    Shader(const char *vertex_shader_path, const char *fragment_shader_path);
    ~Shader();
    void useShader();
    void applyTransform(glm::mat4 M);
    void updated(Camera *cam);
    void applyTexture(int index);
    void applyMaterial(Material* material);
    void applyLight(Light* light);
    void applyLight(DirectionalLight* light);
    void applyLight(PointLight* light);
    void applyLight(SpotLight* light);
    void applyLight(Flashlight* light);
    void applyLightCount(int count);
    glm::vec3 getLightPos();

    GLuint getShaderProgram();
private:
    glm::vec3 lightPos;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
};