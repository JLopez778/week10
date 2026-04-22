#include "Bullet.hpp"
#include "InputManager.hpp"
#include "PhysicsComponent.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "Collider.hpp"
#include "Timer.hpp"

#include <iostream>  

Bullet::Bullet() : GameObject()
{
    name = "Bullet";
    damage = 10;
    speed = 100;
    ttl = MAX_TTL;

    //cache timer
    timer = Timer::instance();
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
    float delta = timer->getDeltaTime();

    ttl -= delta;

}

void Bullet::setDamage(int damage)
{
    this->damage = damage;
}

int Bullet::getDamage()
{
    return damage;
}

void Bullet::setSpeed(float speed)
{
    this->speed = speed;
}

float Bullet::getSpeed()
{
    return speed;
}


void Bullet::spawn(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction)
{
    // TODO: might need to fix this - bullet will be inside of player?1
    this->getTransform()->setPosition(position);

    std::shared_ptr<Vector3f> velocity = this->getPhysicsComponent()->getVelocity();

    // set velocity to direction of player
    velocity->setX(direction->getX());
    velocity->setX(direction->getY());
    velocity->setX(direction->getZ());

    // make unit length
    velocity->normalise();

    // scale by speed for velocity vector
    velocity->scale(speed);

    this->getPhysicsComponent()->setVelocity(velocity);

    ttl = MAX_TTL;
}

void Bullet::despawn()
{
    this->disable();
    ttl = 0.0f;
}

void Bullet::handleCollision(std::shared_ptr<Collider> other)
{
    despawn();
}
