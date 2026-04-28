#ifndef NPC_HPP
#define NPC_HPP

#include <stdio.h>

#include "GameObject.hpp"

class Score;

class NPC : public GameObject {

public:
    NPC();
    ~NPC();

    void update();

    void setSpeed(float speed);
    float getSpeed();
    
    void reset();
    bool move(float Y, float X);
    void defeat();

    void ai();
    void handleCollision(std::shared_ptr<Collider> other);
    void takeDamage(int damage);
    int getDamage();

    static const int MAX_HP = 50;
private:
    float speed;
    int hp;
    int damage;
    bool defeated = false;
    bool resetPos = false;
    float positionY;
    float positionX;
    float movePosY = 5;
    float movePosX = 5;

};

#endif