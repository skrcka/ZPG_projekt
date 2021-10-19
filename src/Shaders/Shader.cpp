#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertex_shader_path, const char *fragment_shader_path) {
	std::ifstream file1(vertex_shader_path);
	if (!file1.is_open())
	{
		printf("Unable to open file %s", vertex_shader_path);
		//exit(1);
	}
	std::stringstream fileData1;
	fileData1 << file1.rdbuf();
	file1.close();
	std::string fileData1String = fileData1.str();
	int vlen = fileData1String.length();
	const char *vertex_shader = fileData1String.c_str();

	std::ifstream file2(fragment_shader_path);
	if (!file2.is_open())
	{
		printf("Unable to open file %s", fragment_shader_path);
		//exit(1);
	}
	std::stringstream fileData2;
	fileData2 << file2.rdbuf();
	file2.close();
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

void Shader::applyRotation(glm::mat4 M){
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void Shader::useShader(){
    glUseProgram(shaderProgram);
}

GLuint Shader::getShaderProgram(){
    return shaderProgram;
}

Shader::~Shader(){
	printf("ShaderLoader::deleteShader()\n");
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgram);
}