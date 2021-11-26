#include "Model.h"
#include <vector>

Model::Model(const float points[], int sizeRow, int rowCount, GLenum mode)
	: mode(mode), sizeRow(sizeRow), rowCount(rowCount)
{
	// vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeRow * rowCount * sizeof(GLfloat), points, GL_STATIC_DRAW);

	// Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  // generate the VAO
	glBindVertexArray(VAO);		  // bind the VAO
	glEnableVertexAttribArray(0); // enable vertex attributes
	glEnableVertexAttribArray(1); // enable vertex attributes
	glEnableVertexAttribArray(2); // enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)0);					   // Jak nasekat pamet
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)(3 * sizeof(GL_FLOAT))); // Jak nasekat pamet
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)(6 * sizeof(GL_FLOAT))); // Jak nasekat pamet
}

Model::Model(const char *path)
	: mode(GL_TRIANGLES)
{
	int count = 0;
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate | aiProcess_OptimizeMeshes // slouèení malých plošek
								 | aiProcess_JoinIdenticalVertices				  // NUTNÉ jinak hodnì duplikuje
								 | aiProcess_Triangulate						  // prevod vsech ploch na trojuhelniky
								 | aiProcess_CalcTangentSpace;					  // vypocet tangenty, nutny pro spravne pouziti normalove mapy

	const aiScene *scene = importer.ReadFile(path, importOptions);
	std::vector<float> data;
	if (scene)
	{
		aiMesh *mesh = scene->mMeshes[0];
		count = mesh->mNumFaces * 3;
		rowCount = mesh->mNumFaces;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
	}

	// vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);

	// Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  // generate the VAO
	glBindVertexArray(VAO);		  // bind the VAO
	glEnableVertexAttribArray(0); // enable vertex attributes
	glEnableVertexAttribArray(1); // enable vertex attributes
	glEnableVertexAttribArray(2); // enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	sizeRow = 8;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeRow * sizeof(GL_FLOAT), (GLvoid *)0);					   // Jak nasekat pamet
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