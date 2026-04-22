#include "GameObject.hpp"

#include "Transform.hpp"
#include "Sprite.hpp"
#include "PhysicsComponent.hpp"
#include "Collider.hpp"

GameObject::GameObject()
{
    sprite = nullptr;
    transform = nullptr;
    enabled = false;
}

GameObject::~GameObject()
{
    sprite.reset();
    sprite = nullptr;

    transform.reset();
    transform = nullptr;
}

void GameObject::setSprite(std::shared_ptr<Sprite> newSprite)
{
    sprite = newSprite;
}

std::shared_ptr<Sprite> GameObject::getSprite()
{
    return sprite;
}

void GameObject::setTransform(std::shared_ptr<Transform> newTransform)
{
    transform = newTransform;
}

std::shared_ptr<Transform> GameObject::getTransform()
{
    return transform;
}

void GameObject::setPhysicsComponent(std::shared_ptr<PhysicsComponent> newPhysicsComponent)
{
    physicsComponent = newPhysicsComponent;
}

std::shared_ptr<PhysicsComponent> GameObject::getPhysicsComponent()
{
    return physicsComponent;
}



void GameObject::setCollisionComponent(std::shared_ptr<Collider> newCollider)
{
    collider = newCollider;
}

std::shared_ptr<Collider> GameObject::getCollisionComponent()
{
    return collider;
}

void GameObject::setName(std::string newName)
{
    name = newName;
}

std::string GameObject::getName()
{
    return name;
}

void GameObject::update()
{
    
}

void GameObject::enable()
{
    enabled = true;
}

void GameObject::disable()
{
    enabled = false;
}

bool GameObject::isEnabled()
{
   return enabled;
}