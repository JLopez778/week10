#include "PhysicsComponent.hpp"

#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vector3f.hpp" 

PhysicsComponent::PhysicsComponent()
{
    velocity = nullptr;
}

PhysicsComponent::PhysicsComponent(std::shared_ptr<Vector3f> newVelocity, std::shared_ptr<GameObject> newGameObject) : Component(newGameObject)
{
    velocity = newVelocity;
}

PhysicsComponent::~PhysicsComponent()
{
    velocity.reset();
    velocity = nullptr;
}

void PhysicsComponent::setVelocity(std::shared_ptr<Vector3f> newVelocity)
{
    velocity = newVelocity;
}

std::shared_ptr<Vector3f> PhysicsComponent::getVelocity()
{
    return velocity;
}



