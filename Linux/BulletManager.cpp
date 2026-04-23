#include "BulletManager.hpp"

#include "Bullet.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "GameObjectFactory.hpp"

#include <iostream>

BulletManager::BulletManager()
{
    maxObjects = 0;
}

BulletManager::~BulletManager()
{
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }
    
    bullets.clear();
}

void BulletManager::init(int maxObjects)
{
    bullets.resize(maxObjects);

    // create bullets - using factory
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
         //std::shared_ptr<Bullet> temp = *itt;
         (*itt) = GameObjectFactory::instance()->createBullet();
         (*itt)->disable();
    }

}

void BulletManager::spawnBullet(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation)
{
    std::shared_ptr<Bullet> bullet = this->nextFree();

    if(bullet != nullptr)
    {   
        bullet->spawn(position, direction, orientation);
        std::cout << "Bullet manager spawning" << std::endl;
    }
    else 
    {
        std::cout << "Bullet manager has no bullets" << std::endl;
    }

    // if no bullets just ignore?
}

std::shared_ptr<Bullet> BulletManager::nextFree()
{
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        //std::shared_ptr<Bullet> temp = *itt;
        if((*itt)->isEnabled() == false)
            return (*itt);
    }

    return nullptr;
}
