#ifndef COLLISION_ENGINE_HPP
#define COLLISION_ENGINE_HPP

#include <vector>
#include <memory>

class Collider;

class CollisionEngine {

public:
    CollisionEngine();
    ~CollisionEngine();

    void init(int maxObjects);


    void addCollider(std::shared_ptr<Collider> collider);
    bool removeCollider(std::shared_ptr<Collider> collider);

    void check();
    bool collide(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);
    void handleCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);
    void resolveCollision(std::shared_ptr<Collider> a, std::shared_ptr<Collider> b);

private:
    int maxObjects;
    std::vector<std::shared_ptr<Collider>> colliders;
    
};

#endif