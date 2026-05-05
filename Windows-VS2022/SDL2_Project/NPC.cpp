#include "NPC.hpp"
#include "PhysicsComponent.hpp"
#include "Vector3f.hpp"
#include "Transform.hpp"
#include "Game.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "score.hpp"
#include "window.hpp"
#include "score.hpp"
 
#include <iostream> 

NPC::NPC() : GameObject()
{
    speed = 300.0f;
    
    hp = MAX_HP;
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

    if(other->getGameObject()->getName() == "Bullet")
    {
        std::shared_ptr<Bullet> bullet = std::static_pointer_cast<Bullet>(other->getGameObject());
       // takeDamage(bullet->getDamage());
        this->defeated = true;
    }
        
}

    void NPC::spawn() {}



int NPC::getDamage(){
    std::shared_ptr<GameObject> gameObject = Game::instance()->findGameObjectByName("player");

    std::shared_ptr<Player> player = std::static_pointer_cast<Player>(gameObject);
  
    // needs a method in player
//    player->getDamage();

    return 0;
}

void NPC::defeat() {
    defeated = true;
    std::shared_ptr<GameObject> player = Game::instance()->findGameObjectByName("player");
    std::static_pointer_cast<Player>(player)->getScore()->inreaseScore(10);
}

void NPC::move() {

}


void NPC::reset() {
    if (defeated == true) {
        float positionY = Window::WINDOW_HEIGHT / 2.0f;
        float positionX = Window::WINDOW_WIDTH / 2.0f;
    }

    
}



    



    





