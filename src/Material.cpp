#include "Material.h"

Material::Material()
	: ambient(0.1f), diffuse(1.0f), shininess(1.0f), intensity(1.0f)
{
}

Material::Material(float ambient, float diffuse, float specular, int shininess)
: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), intensity(-1.0f)
{
}

Material::Material(float ambient, float diffuse, float specular, int shininess, float intensity)
 : Material(ambient, diffuse, specular, shininess)
{
	this->intensity = intensity;
}

float Material::getAmbient()
{
	return ambient;
}

float Material::getDiffuse()
{
	return diffuse;
}

float Material::getSpecular()
{
	return specular;
}

int Material::getShininess()
{
	return shininess;
}

float Material::getIntensity()
{
	return intensity;
}
