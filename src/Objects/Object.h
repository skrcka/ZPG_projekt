#pragma once

class Object {
public:
    virtual void applyShaders(const char *vertex_shader, const char *fragment_shader) = 0;
    virtual void draw() = 0;
    virtual ~Object() = default;
private:
    GLuint VAO, VBO;
};