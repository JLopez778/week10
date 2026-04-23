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

    float angle = atan2f(mousePos->getY() - centre->getY(), mousePos->getX() - centre->getX());
    angle = angle / (M_PI / 180.0f); // convert to degrees
    this->getTransform()->setAngle(angle);

    // Firing

    if(InputManager::instance()->getFire() == true)
    {
        std::shared_ptr<Transform> transform = this->getTransform();
        
        std::shared_ptr<Vector3f> direction(new Vector3f(0.0f,1.0f,0.0f));
        direction->rotate2D(transform->getAngle());// + this->getSprite()->getTexture()->getAngleOffset());

        std::shared_ptr<Vector3f> position(new Vector3f(transform->getPosition()->getX(), transform->getPosition()->getY(), transform->getPosition()->getZ()));

        bulletManager->spawnBullet(position, direction);
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
}

void Player::takeDamage(int damage)
{
    hp -= damage;
}