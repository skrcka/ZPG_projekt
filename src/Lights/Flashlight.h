#pragma once

#include "SpotLight.h"
#include "Camera.h"

class Flashlight : public SpotLight, public Observer<Camera>
{
public:
    Flashlight();
    Flashlight(bool on);
    virtual ~Flashlight();
    void updated(Camera *cam);
    void toggle();
    bool isOn();

private:
    bool on;
};
