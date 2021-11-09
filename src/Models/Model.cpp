#include "Model.h"

Model::Model(const float points[], int sizeRow, int rowCount, GLenum mode)
	: mode(mode), sizeRow(sizeRow), rowCount(rowCount)
{
	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeRow * rowCount * sizeof(GLfloat), points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  //generate the VAO
	glBindVertexArray(VAO);		  //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glEnableVertexAttribArray(2); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)0);						 // Jak nasekat pamet
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GL_FLOAT))); // Jak nasekat pamet
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)(6 * sizeof(GL_FLOAT))); // Jak nasekat pamet
}

int Model::getSize()
{
	return sizeRow * rowCount;
}

GLenum Model::getMode()
{
	return mode;
}

GLuint Model::getVAO()
{
	return VAO;
}

GLuint Model::getVBO()
{
	return VBO;
}