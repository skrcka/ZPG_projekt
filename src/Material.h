#pragma once
#include <glm/ext/vector_float4.hpp>

class Material
{
public:
	Material();
	Material(float ambient, float diffuse, float specular, int shininess);
	Material(float ambient, float diffuse, float specular, int shininess, float intensity);
	float getAmbient();
	float getDiffuse();
	float getSpecular();
	int getShininess();
	float getIntensity();
private:
	float ambient;
	float diffuse;
	float specular;
	int shininess;
	float intensity;
};

