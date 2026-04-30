#include "Player.hpp"
#include "InputManager.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "BulletManager.hpp"
#include "Transform.hpp"
#include "NPC.hpp"

#include "Sprite.hpp"
#include "Texture.hpp"

#include <iostream>  

Player::Player() : GameObject()
{
    speed = 500.0f;
    name = "player";
    bulletManager = nullptr;
}

Player::~Player()
{
    bulletManager.reset();
}

void Player::update()
{
    if(hp < 0)
    {
        // TODO: game logic
        this->disable();
    }

    // Movement. 

    float horizontal = InputManager::instance()->getHorizontalInput();
    float vertical = InputManager::instance()->getVerticalInput();

    std::shared_ptr<Vector3f> velocity = physicsComponent->getVelocity();

    velocity->setX(horizontal);
    velocity->setY(vertical);

    // normalise or diagonals are faster. 

    // scale by speed.
    velocity->scale(speed);

    // No need to do a set - accessing the velocity directly :-P

    // Rotation

    std::shared_ptr<Vector3f> mousePos = InputManager::instance()->getMousePosition();
    std::shared_ptr<Vector3f> centre = transform->getPosition();

    float angleRads = atan2f(mousePos->getY() - centre->getY(), mousePos->getX() - centre->getX());
    float angleDegrees = angleRads * (180.0f/M_PI); // convert to degrees
    this->getTransform()->setAngle(angleDegrees);

    // Firing

    if(InputManager::instance()->getFire() == true)
    {
        std::shared_ptr<Vector3f> direction(new Vector3f(0.0f,-1.0f,0.0f));
        float rotation = angleRads + (this->getSprite()->getTexture()->getAngleOffset() * (M_PI/180.0f));
        direction->rotate2D(rotation);

        std::cout << "direction:" << direction->getX() << "," << direction->getY() << std::endl;
        std::cout << "angle:" << angleRads << std::endl;

        std::shared_ptr<Vector3f> position(new Vector3f(transform->getPosition()->getX(), transform->getPosition()->getY(), transform->getPosition()->getZ()));

        Vector3f offset(*(direction.get()));
        offset.scale(64);
        position->add(offset);

        bulletManager->spawnBullet(position, direction, rotation * (180.0f/M_PI));

    }
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}

float Player::getSpeed()
{
    return speed;
}

void Player::handleCollision(std::shared_ptr<Collider> other)
{
    std::cout << "Player says: Ouch!" << std::endl;

    if(other->getGameObject()->getName() == "NPC")
    {
        std::shared_ptr<NPC> npc = std::static_pointer_cast<NPC>(other->getGameObject());
        takeDamage(npc->getDamage());
    }
        
}

void Player::init(int maxBullets)
{
    bulletManager.reset(new BulletManager());
    bulletManager->init(MAX_BULLETS);
}

void Player::takeDamage(int damage)
{
    hp -= damage;
}

void Player::death() {
    if (hp == 0) {
        if (lives > 0) {
            std::shared_ptr<Vector3f> pos = this->getTransform()->getPosition();


            this->getTransform()->setPosition(0);
        }
    }
}

void Player::CooldownTimer() {
    
}