#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Transform.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "score.hpp"
#include "window.hpp"
 
#include <iostream> 

NPC::NPC() : GameObject()
{
    speed = 300.0f;
    damage = 20;
    hp = MAX_HP;
    name = "npc";
    
}

    

NPC::~NPC()
{
}

void NPC::update()
{
    if(hp > 0)
    {
      //  ai();
    }
    else
    {
        speed = 0.0f;
    }
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

    if(other->getGameObject()->getName() == "Bullet")
    {
        std::shared_ptr<Bullet> bullet = std::static_pointer_cast<Bullet>(other->getGameObject());
        takeDamage(bullet->getDamage());
    }
        
}

void NPC::takeDamage(int damageDone)
{
    hp -= damageDone;
}

int NPC::getDamage()
{
   return damage;
}

void NPC::defeat() {
    if (hp == 0) {

        bool defeated = true;
        float currentScore = Game::instance()->getScore()->getScore();
        currentScore += 1.0f;
        Game::instance()->getScore()->setScore(currentScore);
    }

}

void NPC::reset() {
    if (bool defeated = true) {
        float positionY = Window::WINDOW_HEIGHT / 2;
        float positionX = Window::WINDOW_WIDTH / 2;
    }

    
}

//bool NPC::move(float movePosY, float movePosX){

    //int positionY = positionY + movePosY;
    ///int positionX = positionX + movePosX;

    


    





