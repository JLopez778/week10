#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <memory>
#include <string>

class Sprite;
class Transform;
class PhysicsComponent;
class Collider;

class GameObject {

public:
    GameObject();
    virtual ~GameObject();

    void setSprite(std::shared_ptr<Sprite> newSprite);
    std::shared_ptr<Sprite> getSprite();

    void setTransform(std::shared_ptr<Transform> newTransform);
    std::shared_ptr<Transform> getTransform();

    void setCollisionComponent(std::shared_ptr<Collider> newCollisionComponent);
    std::shared_ptr<Collider> getCollisionComponent();

    void setPhysicsComponent(std::shared_ptr<PhysicsComponent> newPhysicsComponent);
    std::shared_ptr<PhysicsComponent> getPhysicsComponent();

    void setName(std::string newName);
    std::string getName();

    void enable();
    void disable();

    bool isEnabled();

    virtual void update();

    virtual void handleCollision(std::shared_ptr<Collider> other) = 0;

protected:
    std::string name;
    std::shared_ptr<Sprite> sprite;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<PhysicsComponent> physicsComponent;
    std::shared_ptr<Collider> collider;
    bool enabled;
};

#endif