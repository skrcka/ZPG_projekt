#include "Transform.h"

Transform::Transform() {
    Transform(.0f);
}

Transform::Transform(float rotation) : rotation(rotation) {
    M = glm::mat4(1.0f);
	M = glm::rotate(glm::mat4(1.0f),rotation,glm::vec3(0.0f, 1.0f, 0.0f));
}

void Transform::changeRotation(float rotation){
    this->rotation = rotation;
    M = glm::mat4(1.0f);
	M = glm::rotate(glm::mat4(1.0f),rotation,glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Transform::getMatrix(){
    return M;
}

float Transform::getRotation(){
    return rotation;
}