#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameObject.hpp"

class BulletManager;

class Player : public GameObject {

public:
    Player();
    ~Player();

    void init(int maxBullets);

    void update();

    void setSpeed(float speed);
    float getSpeed();
    void takeDamage(int damage);

    void handleCollision(std::shared_ptr<Collider> other);

    static const int MAX_HP = 100;
private:
    float speed;
    int hp;
    std::shared_ptr<BulletManager> bulletManager;
};

#endif