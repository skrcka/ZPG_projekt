#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertex_shader_path, const char *fragment_shader_path)
{
	std::ifstream vertexShaderFile(vertex_shader_path);
	if (!vertexShaderFile.is_open())
	{
		printf("Unable to open file %s", vertex_shader_path);
		exit(1);
	}
	std::stringstream fileData1;
	fileData1 << vertexShaderFile.rdbuf();
	vertexShaderFile.close();
	std::string fileData1String = fileData1.str();
	int vlen = fileData1String.length();
	const char *vertex_shader = fileData1String.c_str();

	std::ifstream fragmentShaderFile(fragment_shader_path);
	if (!fragmentShaderFile.is_open())
	{
		printf("Unable to open file %s", fragment_shader_path);
		exit(1);
	}
	std::stringstream fileData2;
	fileData2 << fragmentShaderFile.rdbuf();
	fragmentShaderFile.close();
	std::string fileData2String = fileData2.str();
	int flen = fileData2String.length();
	const char *fragment_shader = fileData2String.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar **)&vertex_shader, &vlen);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragment_shader, &flen);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		throw(1);
	}
}

void Shader::applyTransform(glm::mat4 M)
{
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}
/*
void Shader::applyLight(glm::vec3 lightPos){
	this->lightPos = lightPos;
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
}
*/
void Shader::applyLight(Light *light)
{
	// Ambient
	glUniform3fv(glGetUniformLocation(shaderProgram, "ambient"), 1, glm::value_ptr(light->getAmbient()));
	// Diffuse
	glUniform3fv(glGetUniformLocation(shaderProgram, "diffuse"), 1, glm::value_ptr(light->getDiffuse()));
	// Specular
	glUniform3fv(glGetUniformLocation(shaderProgram, "specular"), 1, glm::value_ptr(light->getSpecular()));
}

void Shader::applyLight(DirectionalLight *light)
{
	// Ambient
	glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 1, glm::value_ptr(light->getAmbient()));
	// Diffuse
	glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 1, glm::value_ptr(light->getDiffuse()));
	// Specular
	glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.specular"), 1, glm::value_ptr(light->getSpecular()));
	// Direction
	glUniform3fv(glGetUniformLocation(shaderProgram, "dirLight.direction"), 1, glm::value_ptr(light->getDirection()));
}

void Shader::applyLight(PointLight *light)
{
	std::string locator = std::string("pointLights[") + std::to_string(light->getNumber()) + std::string("]");
	// Ambient
	glUniform3fv(glGetUniformLocation(shaderProgram, (locator + std::string(".ambient")).c_str()), 1, glm::value_ptr(light->getAmbient()));
	// Diffuse
	glUniform3fv(glGetUniformLocation(shaderProgram, (locator + std::string(".diffuse")).c_str()), 1, glm::value_ptr(light->getDiffuse()));
	// Specular
	glUniform3fv(glGetUniformLocation(shaderProgram, (locator + std::string(".specular")).c_str()), 1, glm::value_ptr(light->getSpecular()));
	// Position
	glUniform3fv(glGetUniformLocation(shaderProgram, (locator + std::string(".position")).c_str()), 1, glm::value_ptr(light->getPosition()));
	// Constant
	glUniform1f(glGetUniformLocation(shaderProgram, (locator + std::string(".constant")).c_str()), light->getConstant());
	// Linear
	glUniform1f(glGetUniformLocation(shaderProgram, (locator + std::string(".linear")).c_str()), light->getLinear());
	// Quadratic
	glUniform1f(glGetUniformLocation(shaderProgram, (locator + std::string(".quadratic")).c_str()), light->getQuadratic());
}

void Shader::applyLight(SpotLight *light)
{
	// spotLightOn
	glUniform1i(glGetUniformLocation(shaderProgram, "spotLightOn"), 1);
	// Ambient
	glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.ambient"), 1, glm::value_ptr(light->getAmbient()));
	// Diffuse
	glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.diffuse"), 1, glm::value_ptr(light->getDiffuse()));
	// Specular
	glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.specular"), 1, glm::value_ptr(light->getSpecular()));
	// Position
	glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.position"), 1, glm::value_ptr(light->getPosition()));
	// Position
	glUniform3fv(glGetUniformLocation(shaderProgram, "spotlight.direction"), 1, glm::value_ptr(light->getDirection()));
	// Constant
	glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.constant"), light->getConstant());
	// Linear
	glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.linear"), light->getLinear());
	// Quadratic
	glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.quadratic"), light->getQuadratic());
	// Cut off
	glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.cutOff"), light->getCutOff());
	// Outer cut off
	glUniform1f(glGetUniformLocation(shaderProgram, "spotlight.outerCutOff"), light->getOuterCutOff());
}

void Shader::applyLight(Flashlight *light)
{
	// spotLightOn
	glUniform1i(glGetUniformLocation(shaderProgram, "spotLightOn"), 1 ? light->isOn() : 0);
	// Ambient
	glUniform3fv(glGetUniformLocation(shaderProgram, "flashlight.ambient"), 1, glm::value_ptr(light->getAmbient()));
	// Diffuse
	glUniform3fv(glGetUniformLocation(shaderProgram, "flashlight.diffuse"), 1, glm::value_ptr(light->getDiffuse()));
	// Specular
	glUniform3fv(glGetUniformLocation(shaderProgram, "flashlight.specular"), 1, glm::value_ptr(light->getSpecular()));
	// Position
	glUniform3fv(glGetUniformLocation(shaderProgram, "flashlight.position"), 1, glm::value_ptr(light->getPosition()));
	// Position
	glUniform3fv(glGetUniformLocation(shaderProgram, "flashlight.direction"), 1, glm::value_ptr(light->getDirection()));
	// Constant
	glUniform1f(glGetUniformLocation(shaderProgram, "flashlight.constant"), light->getConstant());
	// Linear
	glUniform1f(glGetUniformLocation(shaderProgram, "flashlight.linear"), light->getLinear());
	// Quadratic
	glUniform1f(glGetUniformLocation(shaderProgram, "flashlight.quadratic"), light->getQuadratic());
	// Cut off
	glUniform1f(glGetUniformLocation(shaderProgram, "flashlight.cutOff"), light->getCutOff());
	// Outer cut off
	glUniform1f(glGetUniformLocation(shaderProgram, "flashlight.outerCutOff"), light->getOuterCutOff());
}

void Shader::applyLightCount(int count)
{
	glUniform1i(glGetUniformLocation(shaderProgram, "pointLightsCount"), count);
}

void Shader::updated(Camera *cam)
{
	GLint idViewMat = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint idProjMat = glGetUniformLocation(shaderProgram, "projectionMatrix");
	GLint idCamPosition = glGetUniformLocation(shaderProgram, "cameraPos");

	glUniformMatrix4fv(idViewMat, 1, GL_FALSE, &cam->getView()[0][0]);
	glUniformMatrix4fv(idProjMat, 1, GL_FALSE, &cam->getProj()[0][0]);
	glUniform3fv(idCamPosition, 1, glm::value_ptr(cam->getPosition()));
}

void Shader::applyTexture(int index)
{
	glUniform1i(glGetUniformLocation(shaderProgram, "textureUnitID"), index);
}

void Shader::applyMaterial(Material* material)
{
	glUniform1f(glGetUniformLocation(shaderProgram, "ambient_coef"), material->getAmbient());
	glUniform1f(glGetUniformLocation(shaderProgram, "diffuse_coef"), material->getDiffuse());
	glUniform1f(glGetUniformLocation(shaderProgram, "specular_coef"), material->getSpecular());
	glUniform1f(glGetUniformLocation(shaderProgram, "shininess"), material->getShininess());
	glUniform1f(glGetUniformLocation(shaderProgram, "normal_intensity"), material->getIntensity());
}

glm::vec3 Shader::getLightPos()
{
	return lightPos;
}

void Shader::useShader()
{
	glUseProgram(shaderProgram);
}

GLuint Shader::getShaderProgram()
{
	return shaderProgram;
}

Shader::~Shader()
{
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgram);
}