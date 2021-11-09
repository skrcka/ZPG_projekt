#include "Object.h"

Object::Object()
{
}

Object::Object(Model *model, Shader *shader, Transform *transform)
 : model(model), shader(shader), transform(transform), texture(nullptr)
{
}

Object::Object(Model *model, Shader *shader, Transform *transform, Texture *texture)
	: model(model), shader(shader), transform(transform), texture(texture)
{
}

void Object::applyShader(Shader *shader)
{
	this->shader = shader;
}

void Object::applyTransform(Transform *transform)
{
	this->transform = transform;
}

void Object::applyModel(Model *model)
{
	this->model = model;
}

void Object::draw()
{
	this->shader->useShader();
	this->shader->applyTransform(transform->getMatrix());
	if (texture)
		this->shader->applyTexture(texture->getIndex());
	glBindVertexArray(model->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, model->getSize());
}

Transform *Object::getTransform()
{
	return transform;
}

Shader *Object::getShader()
{
	return shader;
}

Model *Object::getModel()
{
	return model;
}