#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"

class Background : public GameObject {

public:
    Background();
    ~Background();

    void handleCollision(std::shared_ptr<Collider> other);
private:

};

#endif