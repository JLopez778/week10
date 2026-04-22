#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <memory>
#include "Component.hpp"

class Collider : public Component {

public:
    Collider();
    Collider(float radius, bool resolution, std::shared_ptr<GameObject> gameObject);
    ~Collider();

    void setRadius(float newRadius);
    float getRadius();

    void setResolution(bool flag);
    bool needsResolution();
    
private:
  float radius;
  bool resolution;

};

#endif