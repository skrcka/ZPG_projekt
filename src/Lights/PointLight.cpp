#include "PointLight.h"

PointLight::PointLight() : Light()
{
    number = 0;
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

PointLight::PointLight(int number) : Light(), number(number)
{
    number = 0;
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

PointLight::PointLight(int number, glm::vec3 position) : Light(), number(number), position(position)
{
    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
}

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int number, glm::vec3 position)
    : Light(ambient, diffuse, specular), number(number), position(position)
{
    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
}

PointLight::~PointLight(){}

glm::vec3 PointLight::getPosition(){
    return position;
}

int PointLight::getNumber(){
    return number;
}

float PointLight::getConstant()
{
    return constant;
}

float PointLight::getLinear()
{
    return linear;
}

float PointLight::getQuadratic()
{
    return quadratic;
}
