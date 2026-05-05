#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameObject.hpp"

class BulletManager;
class Score;

class Player : public GameObject {

public:
    Player();
    ~Player();

    void init(int maxBullets);

    void update();

    void setSpeed(float speed);
    float getSpeed();
    void  takeDamage( std::shared_ptr<Player>  damage);
    void death();

    void CooldownTimer();

    std::shared_ptr<Score> getScore();

    void handleCollision(std::shared_ptr<Collider> other);

    static const int MAX_HP = 100;
    static const int MAX_BULLETS = 10;
private:
    float speed;
    int hp;
    int lives = 5;
    bool playerDeath;
    std::shared_ptr<BulletManager> bulletManager;
    std::shared_ptr<Score> score;
};

#endif