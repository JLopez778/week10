#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

#include <vector>
#include <memory>

class Bullet;
class Vector3f;

class BulletManager {

public:
    BulletManager();
    ~BulletManager();

    void init(int maxObjects);

    void spawnBullet(std::shared_ptr<Vector3f> position, std::shared_ptr<Vector3f> direction, float orientation);

private:
    int maxObjects;
    std::vector<std::shared_ptr<Bullet>> bullets;

    std::shared_ptr<Bullet> nextFree();
};

#endif