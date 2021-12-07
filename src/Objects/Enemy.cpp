#include "Enemy.h"

Enemy::Enemy() : Object(), t(0.5f), delta(0.01f) {
    
}
Enemy::Enemy(Model *model, Shader *shader, Transform *transform)
    : Object(model, shader, transform), t(0.5f), delta(0.01f)
{
}
Enemy::Enemy(Model *model, Shader *shader, Transform *transform, Texture *texture)
    : Object(model, shader, transform, texture), t(0.5f), delta(0.01f)
{
}

void Enemy::move()
{
    glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                            glm::vec4(3.0, -6.0, 3.0, 0),
                            glm::vec4(-3.0, 3.0, 0, 0),
                            glm::vec4(1, 0, 0, 0));
    glm::mat4x3 B = glm::mat4x3(glm::vec3(-1, 0, 0),
                                glm::vec3(0, 1, 0),
                                glm::vec3(0, -1, 0),
                                glm::vec3(1, 0, 0));

    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * A * glm::transpose(B);
    this->transform->move(p.x, p.y, p.z);

    if (t >= 1.0f || t <= 0.0f)
        delta *= -1;
    t += delta;
}
