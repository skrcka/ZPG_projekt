#include "Objects/Skybox.h"

Skybox::Skybox(Model *model, Shader *shader, Transform *transform, Texture *texture, Skypos pos)
	: Object(model, shader, transform, texture), pos(pos)
{
}

void Skybox::draw()
{
	this->shader->applyTransform(transform->getMatrix());
	if (texture)
		this->shader->applyTexture(texture->getIndex());
	glBindVertexArray(model->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, model->getSize());

	glClear(GL_DEPTH_BUFFER_BIT);
}

void Skybox::updated(Camera *cam)
{
	glm::vec3 posVec = cam->getPosition();
	switch (pos)
	{
	case Skypos::negx:
		transform->move(posVec.x - 1.0, posVec.y, posVec.z);
		break;
	case Skypos::negy:
		transform->move(posVec.x, posVec.y - 1.0, posVec.z);
		break;
	case Skypos::negz:
		transform->move(posVec.x, posVec.y, posVec.z - 1.0);
		break;
	case Skypos::posx:
		transform->move(posVec.x + 1.0, posVec.y, posVec.z);
		break;
	case Skypos::posy:
		transform->move(posVec.x, posVec.y + 1.0, posVec.z);
		break;
	case Skypos::posz:
		transform->move(posVec.x, posVec.y, posVec.z + 1.0);
		break;
	default:
		break;
	}
	
}