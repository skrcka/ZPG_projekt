#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
    this->direction = glm::vec3(.0f, -1.f, .0f);
}

DirectionalLight::DirectionalLight(glm::vec3 direction) : Light(), direction(direction)
{
}

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
    : Light(ambient, diffuse, specular), direction(direction)
{
}

DirectionalLight::~DirectionalLight(){}

glm::vec3 DirectionalLight::getDirection()
{
    return direction;
}
