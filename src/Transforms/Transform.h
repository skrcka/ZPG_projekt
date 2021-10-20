#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

enum Axis {
	X,
    Y,
    Z,
};

class Transform{
public:
    Transform();
    explicit Transform(float x, float y, float z, float rotationX, float rotationY, float rotationZ);
    void rotate(float rotationX, float rotationY, float rotationZ);
    void move(float x, float y, float z);
    glm::mat4 getMatrix();
    float getRotationX();
    float getRotationY();
    float getRotationZ();
    float getX();
    float getY();
    float getZ();

private:
    float x, y, z;
    float rotationX, rotationY, rotationZ;
    glm::mat4 M;
};