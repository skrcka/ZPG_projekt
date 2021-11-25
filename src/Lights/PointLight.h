#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    PointLight(int number);
    PointLight(int number, glm::vec3 position);
    virtual ~PointLight();
    PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int number, glm::vec3 position);
    glm::vec3 getPosition();
    float getConstant();
    float getLinear();
    float getQuadratic();
    int getNumber();

protected:
    int number;
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
};
