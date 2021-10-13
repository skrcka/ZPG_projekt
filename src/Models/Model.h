#pragma once

class Model {
public:
    virtual ~Model() = default;
    virtual GLuint getVAO() = 0;
    virtual GLuint getVBO() = 0;

private:
    GLuint VAO, VBO;
};