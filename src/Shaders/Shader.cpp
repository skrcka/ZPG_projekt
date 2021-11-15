#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertex_shader_path, const char *fragment_shader_path) {
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
	glShaderSource(vertexShader, 1, (const GLchar **) &vertex_shader, &vlen);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **) &fragment_shader, &flen);
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

void Shader::applyTransform(glm::mat4 M){
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void Shader::applyLight(glm::vec3 lightPos){
	this->lightPos = lightPos;
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
}

void Shader::updated(Camera *cam){
	GLint idViewMat = glGetUniformLocation(shaderProgram, "viewMatrix");
	GLint idProjMat = glGetUniformLocation(shaderProgram, "projectionMatrix");
	GLint idCamPosition = glGetUniformLocation(shaderProgram, "cameraPos");

	glUniformMatrix4fv(idViewMat, 1, GL_FALSE, &cam->getView()[0][0]);
	glUniformMatrix4fv(idProjMat, 1, GL_FALSE, &cam->getProj()[0][0]);
	glUniform3fv(idCamPosition, 1, glm::value_ptr(cam->getPosition()));
}

void Shader::applyTexture(int index){
	glUniform1i(glGetUniformLocation(shaderProgram, "textureUnitID"), index);
}

glm::vec3 Shader::getLightPos(){
	return lightPos;
}

void Shader::useShader(){
    glUseProgram(shaderProgram);
}

GLuint Shader::getShaderProgram(){
    return shaderProgram;
}

Shader::~Shader(){
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgram);
}