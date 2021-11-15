#include "Texture.h"
#include <GL/glew.h>
#include <IL/il.h>

Texture::Texture() {}

Texture::Texture(std::string path, int index) : index(index)
{
    ILboolean ilLoadImage(const char *filename);

    ILuint image = 0;
    ilGenImages(1, &image);
    ilBindImage(image);

    if (!ilLoadImage(path.c_str()))
    {
        printf("Cant open texture!\n");
    }

    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    char *pixmap = new char[width * height * 3];
    ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, pixmap);

    /*
    unsigned int typeSource;
    unsigned int typeTarget;

    switch (3)
    {
    case 3:
        typeSource = GL_RGB;
        typeTarget = GL_BGR;
        break;
    case 4:
        typeSource = GL_BGRA;
        typeTarget = GL_RGBA;
        break;
    }
    */

    glGenTextures(1, &texture_id);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D,    // Type of texture 1D, 2D, 3D
                 0,                // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,           // Internal colour format to convert to
                 width,            // Image width  i.e. 640
                 height,           // Image height i.e. 480
                 0,                // Border width in pixels (can either be 1 or 0)
                 GL_RGB,           // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE, // Image data type
                 pixmap);          // The actual image data itself

    glGenerateMipmap(GL_TEXTURE_2D);

    ilBindImage(0);
    ilDeleteImage(image);
    delete[] pixmap;
}

int Texture::getIndex()
{
    return index;
}
