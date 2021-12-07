#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
    Enemy();
    Enemy(Model *model, Shader *shader, Transform *transform);
    Enemy(Model *model, Shader *shader, Transform *transform, Texture *texture);
    void move();

private:
    float t, delta;
};
