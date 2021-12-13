#include "Object.h"

Object::Object()
	: id(0), model(nullptr), shader(nullptr), transform(nullptr), texture(nullptr), material(nullptr)
{
}

Object::Object(Model *model, Shader *shader, Transform *transform)
	: id(0), model(model), shader(shader), transform(transform), texture(nullptr), material(nullptr)
{
}

Object::Object(Model *model, Shader *shader, Transform *transform, Texture *texture)
	: id(0), model(model), shader(shader), transform(transform), texture(texture), material(nullptr)
{
}

Object::Object(Model *model, Shader *shader, Transform *transform, Texture *texture, Material *material)
	: id(0), model(model), shader(shader), transform(transform), texture(texture), material(material)
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
	this->shader->applyTransform(transform->getMatrix());
	if (texture)
		this->shader->applyTexture(texture->getIndex());
	if (material)
		this->shader->applyMaterial(material);
	glBindVertexArray(model->getVAO());

	glDrawArrays(GL_TRIANGLES, 0, model->getSize());
}

void Object::addId(int id)
{
	this->id = id;
}

int Object::getId()
{
	return id;
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