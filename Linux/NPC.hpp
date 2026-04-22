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
    void takeDamage(int damage);
    int getDamage();

    static const int MAX_HP = 50;
private:
    float speed;
    int hp;
    int damage;
};

#endif