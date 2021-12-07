#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
    Enemy();
    Enemy(Model *model, Shader *shader, Transform *transform);
    Enemy(Model *model, Shader *shader, Transform *transform, Texture *texture);
    void move();
    void addMovement(glm::mat4x3 points);
    void remMovement();

private:
    float t, delta;
    bool movementEnabled;
    glm::mat4x3 points;
};
