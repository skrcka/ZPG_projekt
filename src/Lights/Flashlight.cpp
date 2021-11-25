#include "Flashlight.h"

Flashlight::Flashlight() : SpotLight()
{
    on = true;
}

Flashlight::Flashlight(bool on) : SpotLight(), on(on)
{
}

void Flashlight::toggle()
{
    on = !on;
}

Flashlight::~Flashlight()
{
}

void Flashlight::updated(Camera *cam)
{
    direction = cam->getOrientation();
    position = cam->getPosition();
}

bool Flashlight::isOn(){
    return on;
}
