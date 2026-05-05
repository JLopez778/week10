#ifndef NPC_HPP
#define NPC_HPP

#include <stdio.h>

#include "GameObject.hpp"

class Score;

class NPC : public GameObject {

public:
    NPC();
    ~NPC();

    void update() ;

    void setSpeed(float speed);
    float getSpeed();
    
    void reset();
    void move();
    void defeat();

    float getX();
    float getY();
    int getRadius();
    void ai();
    void handleCollision(std::shared_ptr<Collider> other);
    void spawn();
    void takeDamage(int damageDone, int damage);
    
    int getDamage();

    static const int MAX_HP = 50;

private:
    float speed;
    int hp = 0;
    bool hit = false;
    
    bool defeated = false;
    bool resetPos = false;
    float positionY;
    float positionX;
    float movePosY = 5;
    float movePosX = 5;
    float phaseAngle;
    float velocityX;
    float velocityY;
    float initSize;
    float initalPhase;
    float initialPhaseVelocity;

    
    

    

};

#endif