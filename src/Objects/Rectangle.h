#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Rectangle {
public:
    Rectangle(int x, int y, int width, int height);
    void applyShaders(const char *vertex_shader, const char *fragment_shader);
private:
    int x,y,width,height;
    GLuint VAO, VBO;
};