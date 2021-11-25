#include "SpotLight.h"

SpotLight::SpotLight() : PointLight(-1)
{
    direction = glm::vec3(.0, .0, .0);
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction)
    : PointLight(-1, position), direction(direction)
{
}

SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction)
    : PointLight(ambient, diffuse, specular, -1, position), direction(direction)
{
}

SpotLight::~SpotLight() {}

SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff)
    : PointLight(ambient, diffuse, specular, -1, position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff)
{
}

glm::vec3 SpotLight::getDirection()
{
    return direction;
}

float SpotLight::getCutOff(){
    return cutOff;
}

float SpotLight::getOuterCutOff(){
    return outerCutOff;
}
