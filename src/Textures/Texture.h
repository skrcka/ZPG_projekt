#pragma once

#include <memory>
#include <string>

enum TextureType{
    Texture_RGB,
    Texture_RGBA,
};

class Texture{
public:
    Texture();
    Texture(std::string path, int index);
    int getIndex();

private:
    unsigned int texture_id;
    int index;
};