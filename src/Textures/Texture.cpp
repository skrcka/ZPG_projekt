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

    int channels = ilGetInteger(IL_IMAGE_CHANNELS);
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    char *pixmap = new char[width * height * channels];
    
    unsigned int loadType;
    unsigned int type;
    switch (channels)
    {
    case 3:
        type = GL_RGB;
        loadType = GL_RGB;
        loadType = IL_RGB;
        break;
    case 4:
        type = GL_RGBA;
        loadType = IL_RGBA;
        break;
    default:
        type = -1;
        loadType = -1;
    }

    ilCopyPixels(0, 0, 0, width, height, 1, loadType, IL_UNSIGNED_BYTE, pixmap);

    glGenTextures(1, &texture_id);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D,    // Type of texture 1D, 2D, 3D
                 0,                // Pyramid level (for mip-mapping) - 0 is the top level
                 type,           // Internal colour format to convert to
                 width,            // Image width  i.e. 640
                 height,           // Image height i.e. 480
                 0,                // Border width in pixels (can either be 1 or 0)
                 type,           // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
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
