#include "Rectangle.h"

Rectangle::Rectangle(){
	Rectangle(0);
}

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

void Rectangle::applyShader(Shader* shader)
{
	this->shader = shader;
}

void Rectangle::draw()
{
	this->shader->useShader();
	this->shader->applyRotation(rotation);
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}