#include "Rectangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Rectangle::Rectangle(float rotation) : rotation(rotation)
{
	const float points[4][2][4] = {
		{{-.5f, -.5f, .5f, 1}, {0.5, 1, 0, 1}},
		{{-.5f, .5f, .5f, 1}, {1, 0, 0, 1}},
		{{.5f, -.5f, .5f, 1}, {0, 1, 0, 1}},
		{{.5f, .5f, .5f, 1}, {0, 0, 0, 1}},
	};
	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  //generate the VAO
	glBindVertexArray(VAO);		  //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(points[0]), (GLvoid*)0); // Jak nasekat pamet
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(points[0]), (GLvoid*)(4*sizeof(GL_FLOAT))); // Jak nasekat pamet
}

void Rectangle::applyShaders(const char *vertex_shader, const char *fragment_shader)
{
	//rotation
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(glm::mat4(1.0f),rotation,glm::vec3(0.0f, 1.0f, 0.0f));

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
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
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void Rectangle::draw()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}