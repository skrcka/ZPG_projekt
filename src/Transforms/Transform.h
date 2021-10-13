#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Transform{
public:
    Transform();
    explicit Transform(float rotation);
    void changeRotation(float rotation);
    glm::mat4 getMatrix();
    float getRotation();

private:
    float rotation;
    glm::mat4 M;
};