#include "BulletManager.hpp"

#include "Bullet.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp"
#include "GameObjectFactory.hpp"

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
         std::shared_ptr<Bullet> temp = *itt;
         temp = GameObjectFactory::instance()->createBullet();
         temp->disable();
    }

}

void BulletManager::addBullet(std::shared_ptr<Bullet> bullet)
{
    bullets.push_back(bullet);
}

bool BulletManager::removeBullet(std::shared_ptr<Bullet> bullet)
{
    bool deleted = false;
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        std::shared_ptr<Bullet> temp = *itt;
        if(temp == bullet)
        {
            bullets.erase(itt);
            // itt - now invalid as we've altered the vector!
            deleted = true;
            break;

            /* To erase all matching*/
            //itt = bullets.erase(itt);
        }
    }

    return deleted;
}

void BulletManager::spawnBullet(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction)
{
    std::shared_ptr<Bullet> bullet = this->nextFree();

    if(bullet != nullptr)
    {   
        bullet->spawn(position, direction);
    }

    // if no bullets just ignore?
}

std::shared_ptr<Bullet> BulletManager::nextFree()
{
    std::vector<std::shared_ptr<Bullet>>::iterator itt;
    for(itt = bullets.begin(); itt != bullets.end(); ++itt)
    {
        std::shared_ptr<Bullet> temp = *itt;
        if(temp->isEnabled() == false)
            return temp;
    }

    return nullptr;
}
