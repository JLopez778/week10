#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameObject.hpp"

class Player : public GameObject {

public:
    Player();
    ~Player();

    void update();

    void setSpeed(float speed);
    float getSpeed();

    void handleCollision(std::shared_ptr<Collider> other);
private:
    float speed;
};

#endif