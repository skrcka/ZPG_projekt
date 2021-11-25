#pragma once

#include "PointLight.h"

class SpotLight : public PointLight
{
public:
    SpotLight();
    SpotLight(glm::vec3 position, glm::vec3 direction);
    virtual ~SpotLight();
    SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction);
    SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, float  cutOff, float outerCutOff);
    glm::vec3 getDirection();
    float getCutOff();
    float getOuterCutOff();

protected:
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;
};
