#include "Objects/Skybox.h"

void Skybox::draw(){
    this->shader->useShader();
	this->shader->applyTransform(transform->getMatrix());
	if (texture)
		this->shader->applyTexture(texture->getIndex());
	glBindVertexArray(model->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, model->getSize());
}