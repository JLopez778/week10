#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include <memory>
#include "Component.hpp"

class GameObject;
class Vector3f;

class PhysicsComponent : public Component {

public:
    PhysicsComponent();
    PhysicsComponent(std::shared_ptr<Vector3f> newVelocity, std::shared_ptr<GameObject> newGameObject);
    ~PhysicsComponent();

    void setVelocity(std::shared_ptr<Vector3f> newVelocity);
    std::shared_ptr<Vector3f> getVelocity();


private:
    std::shared_ptr<Vector3f> velocity;

};

#endif