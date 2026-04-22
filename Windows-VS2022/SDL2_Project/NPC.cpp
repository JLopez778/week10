#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Transform.hpp"
#include "Game.hpp"
 
#include <iostream> 

NPC::NPC() : GameObject()
{
    speed = 300.0f;
    name = "npc";
}

NPC::~NPC()
{
}

void NPC::update()
{
    ai();
}

void NPC::setSpeed(float speed)
{
    this->speed = speed;
}

float NPC::getSpeed()
{
    return speed;
}

void NPC::ai()
{
    //brittle!
    std::shared_ptr<GameObject> player = Game::instance()->findGameObjectByName("player");

    if(player != nullptr)
    {
        std::shared_ptr<Vector3f> playerPos = player->getTransform()->getPosition();

        std::shared_ptr<Vector3f> myPosition = transform->getPosition();
        std::shared_ptr<Vector3f> toPlayer(new Vector3f(*playerPos));

        toPlayer->sub(*myPosition);
        toPlayer->normalise();
        toPlayer->scale(speed);

        physicsComponent->setVelocity(toPlayer);
    }
}

void NPC::handleCollision(std::shared_ptr<Collider> other)
{
    speed = 0.0f;
    std::cout << "NPC says: Ouch!" << std::endl;
}
