#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
    Enemy();
    Enemy(Model *model, Shader *shader, Transform *transform);
    Enemy(Model *model, Shader *shader, Transform *transform, Texture *texture);
    void move();
    void addMovement(float x, float y, float z);
    void remMovement();

private:
    float t, delta;
    bool movementEnabled;
    std::vector<glm::vec3> path;
};
