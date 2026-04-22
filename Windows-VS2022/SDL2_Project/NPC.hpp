#ifndef NPC_HPP
#define NPC_HPP


#include "GameObject.hpp"

class NPC : public GameObject {

public:
    NPC();
    ~NPC();

    void update();

    void setSpeed(float speed);
    float getSpeed();

    void ai();
    void handleCollision(std::shared_ptr<Collider> other);
private:
    float speed;
};

#endif