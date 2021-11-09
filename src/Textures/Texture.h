#pragma once

#include <opencv2/opencv.hpp>
#include <memory>
#include <string>

class Texture{
public:
    Texture();
    explicit Texture(std::string path, int index);
    int getIndex();

private:
    unsigned int texture_id;
    int index;
};