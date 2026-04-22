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

    void handleCollision(std::shared_ptr<Collider> other);

private:
    float speed;
    std::shared_ptr<BulletManager> bulletManager;
};

#endif