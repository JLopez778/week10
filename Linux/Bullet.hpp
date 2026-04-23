#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"

class Vector3f;
class Timer;

class Bullet : public GameObject {

public:
    Bullet();
    ~Bullet();

    void update();

    void setDamage(int damage);
    int getDamage();

    void setSpeed(float speed);
    float getSpeed();

    void spawn(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction);
    void despawn();

    void handleCollision(std::shared_ptr<Collider> other);

    static const float MAX_TTL;
private:
    int damage;
    float ttl;
    float speed;

    std::shared_ptr<Timer> timer;
};

#endif