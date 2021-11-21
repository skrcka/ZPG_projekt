#pragma once

#include "Objects/Object.h"
#include "Utils/Observer.h"
#include "Camera.h"

enum Skypos
{
    negx,
    negy,
    negz,
    posx,
    posy,
    posz,
};

class Skybox : public Object, public Observer<Camera>
{
public:
    Skybox(Model *model, Shader *shader, Transform *transform, Texture *texture, Skypos pos);
    void draw();
    void updated(Camera *cam);
private:
    Skypos pos;
};