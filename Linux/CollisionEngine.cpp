#include "CollisionEngine.hpp"
 
#include "Collider.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp" 

#include <iostream>

CollisionEngine::CollisionEngine()
{
    maxObjects = 0;
}

CollisionEngine::~CollisionEngine()
{
    std::vector<std::shared_ptr<Collider>>::iterator itt;
    for(itt = colliders.begin(); itt != colliders.end(); ++itt)
    {
        (*itt).reset(); // call reset on the shared pointer!
    }
    
    colliders.clear();
}

void CollisionEngine::init(int maxObjects)
{
    colliders.resize(maxObjects);
}

void CollisionEngine::addCollider(std::shared_ptr<Collider> body)
{
    bool added = false;
    std::vector<std::shared_ptr<Collider>>::iterator itt;
    for(itt = colliders.begin(); itt != colliders.end(); ++itt)
    {
        if(*itt == nullptr)
        {
            *itt = body;
            added = true;
            break;
        }
    }

    if(added == false)
        std::cout << "Ran out of pre-allocated collider components" << std::endl;
}

bool CollisionEngine::removeCollider(std::shared_ptr<Collider> body)
{
    bool deleted = false;
    std::vector<std::shared_ptr<Collider>>::iterator itt;
    for(itt = colliders.begin(); itt != colliders.end(); ++itt)
    {
        std::shared_ptr<Collider> temp = *itt;
        if(temp == body)
        {
            colliders.erase(itt);
            // itt - now invalid as we've altered the vector!
            deleted = true;
            break;

            /* To erase all matching*/
            //itt = sprites.erase(itt);
        }
    }

    return deleted;
}

void CollisionEngine::check()
{
    std::shared_ptr<Collider> colliderOne;

    std::vector<std::shared_ptr<Collider>>::iterator itt;

    for(itt = colliders.begin(); itt != colliders.end(); ++itt)
    {
        colliderOne = *itt;

        if(colliderOne == nullptr)
            continue;

        if(colliderOne->getGameObject()->isEnabled() == false)
            continue;

        std::shared_ptr<Collider> colliderTwo;

        std::vector<std::shared_ptr<Collider>>::iterator itt2;

        for(itt2 = colliders.begin(); itt2 != colliders.end(); ++itt2)
        {
            colliderTwo = *itt2;

            if(colliderTwo == nullptr)
                continue;

            if(colliderTwo->getGameObject()->isEnabled() == false)
                continue;

            // Check we're not comparing to ourself!

            if(colliderOne == colliderTwo)
                continue;

            // Collision check
            if(collide(colliderOne, colliderTwo) == true)
            {

                // handle collisions 
                handleCollision(colliderOne, colliderTwo);
            }
        } 
    }
}

bool CollisionEngine::collide(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
    std::shared_ptr<Vector3f> posA;
    std::shared_ptr<Vector3f> posB;
    std::shared_ptr<Vector3f> s;

    float radA;
    float radB;

    posA = a->getGameObject()->getTransform()->getPosition();
    posB = b->getGameObject()->getTransform()->getPosition();
    
    radA = a->getRadius();
    radB = b->getRadius();

    s.reset(new Vector3f(posA->getX(), posA->getY(), posA->getZ()));
    s->sub(*posB.get());

    float sLength = s->getLength();

    if(sLength < (radA + radB))
    {
        return true;
    }
    else
    {
        return false;
    }

}

void CollisionEngine::handleCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
    bool resolve = a->needsResolution() && b->needsResolution();

    if(resolve == true)
    {
        resolveCollision(a,b);
    }

    // inform objects

    a->getGameObject()->handleCollision(b);
    b->getGameObject()->handleCollision(a);
}

void CollisionEngine::resolveCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b)
{
    float touchingDistance;
    float actualDistance;

    std::shared_ptr<Vector3f> posA;
    std::shared_ptr<Vector3f> posB;

    posA = a->getGameObject()->getTransform()->getPosition();
    posB = b->getGameObject()->getTransform()->getPosition();
    // get vector between a and b. 

    Vector3f delta(*posB.get());
    delta.sub(*posA.get());

    // calculate actual distance
    actualDistance = delta.getLength();

    // make this a direction
    delta.normalise();

    // calculate the touching distance
    touchingDistance = a->getRadius() + b->getRadius();

    // scale the correction
    delta.scale((touchingDistance-actualDistance)/2.0f);

    // fix this for a
    posA->sub(delta);

    // fix this for b
    posB->add(delta);
}
