#include "Transform.h"

Transform::Transform() : x(.0f), y(.0f), z(.0f), rotationX(0), rotationY(0), rotationZ(0)
{
    M = glm::mat4(1.0f);
}

Transform::Transform(float x, float y, float z, float rotationX, float rotationY, float rotationZ)
{
    M = glm::mat4(1.0f);
    moveBy(x, y, z);
    rotate(rotationX, rotationY, rotationZ);
}

void Transform::rotateBy(float rotationX, float rotationY, float rotationZ)
{
    this->rotationX += rotationX;
    this->rotationY += rotationY;
    this->rotationZ += rotationZ;
    M = glm::rotate(M, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, rotationZ, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Transform::rotate(float rotationX, float rotationY, float rotationZ)
{
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;
    rotateBy(rotationX, rotationY, rotationZ);
}

void Transform::move(float x, float y, float z)
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    M = glm::mat4(1.0f);
    moveBy(x, y, z);
    rotate(rotationX, rotationY, rotationZ);
}

void Transform::moveBy(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
    M = glm::translate(M, glm::vec3(this->x, this->y, this->z));
}

glm::mat4 Transform::getMatrix()
{
    return M;
}

float Transform::getRotationX()
{
    return rotationX;
}

float Transform::getRotationY()
{
    return rotationY;
}

float Transform::getRotationZ()
{
    return rotationZ;
}

float Transform::getX()
{
    return x;
}

float Transform::getY()
{
    return y;
}

float Transform::getZ()
{
    return z;
}