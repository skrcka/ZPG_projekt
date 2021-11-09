#include "Texture.h"
#include <GL/glew.h>

Texture::Texture() {}

Texture::Texture(std::string path, int index) : index(index)
{
    cv::Mat image = cv::imread(path, 1);
    cv::flip(image, image, 0);

    glGenTextures(1, &texture_id);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D,    // Type of texture 1D, 2D, 3D
                 0,                // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,           // Internal colour format to convert to
                 image.cols,       // Image width  i.e. 640
                 image.rows,       // Image height i.e. 480
                 0,                // Border width in pixels (can either be 1 or 0)
                 GL_BGR,           // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE, // Image data type
                 image.ptr());     // The actual image data itself

    glGenerateMipmap(GL_TEXTURE_2D);
    printf("added texture to index: %d\n", index);
    //image.release();
}

int Texture::getIndex(){
    return index;
}
