#include "Light.h"

Light::Light()
{
    this->ambient = glm::vec3(.2f, .2f, .2f);
    this->diffuse = glm::vec3(1.f, 1.f, 1.f);
    this->specular = glm::vec3(1.f, 1.f, 1.f);
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : ambient(ambient), diffuse(diffuse), specular(specular)
{
}

Light::~Light(){}

glm::vec3 Light::getAmbient()
{
    return ambient;
}

glm::vec3 Light::getDiffuse()
{
    return diffuse;
}

glm::vec3 Light::getSpecular()
{
    return specular;
}
