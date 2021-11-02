#include "Model.h"

Model::Model(const float points[], int size, GLenum mode) : mode(mode), size(size){
	pointCount = size / 6;
	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  //generate the VAO
	glBindVertexArray(VAO);		  //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); // Jak nasekat pamet
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT))); // Jak nasekat pamet
}

int Model::getSize(){
	return size;
}

GLenum Model::getMode(){
	return mode;
}

GLuint Model::getVAO(){
	return VAO;
}

GLuint Model::getVBO(){
	return VBO;
}