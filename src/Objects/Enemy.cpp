#include "Enemy.h"

Enemy::Enemy() : Object(), t(.0f), delta(0.01f), movementEnabled(false)
{
}
Enemy::Enemy(Model *model, Shader *shader, Transform *transform)
    : Object(model, shader, transform), t(.0f), delta(0.01f), movementEnabled(false)
{
}
Enemy::Enemy(Model *model, Shader *shader, Transform *transform, Texture *texture)
    : Object(model, shader, transform, texture), t(.0f), delta(0.01f), movementEnabled(false)
{
}

void Enemy::addMovement(float x, float y, float z)
{
    this->path.push_back(glm::vec3(x, y, z));
    movementEnabled = true;
}

void Enemy::remMovement()
{
    movementEnabled = false;
    this->path.clear();
}

int choose(int n, int k)
{
    if (k == 0)
        return 1;
    else
        return (n * choose(n - 1, k - 1)) / k;
}

void Enemy::move()
{
    if (!movementEnabled)
        return;

    int pointNo = this->path.size() - 1;
    glm::vec3 resPoint = glm::vec3(0.f);

    for (int i = 0; i <= pointNo; i++)
    {
        float coef = choose(pointNo, i) * pow(t, i) * pow((1 - t), pointNo - i);
        resPoint.x += this->path[i].x * coef;
        resPoint.y += this->path[i].y * coef;
        resPoint.z += this->path[i].z * coef;
    }
    if (t > 1.0f || t < 0.0f)
        delta *= -1;

    t += delta;
    
    this->transform->move(resPoint.x, resPoint.y, resPoint.z);
}
