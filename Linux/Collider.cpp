#include "Collider.hpp"

#include "GameObject.hpp"
#include "Texture.hpp"

Collider::Collider() : Component(gameObject)
{
    radius = 0.0f;
    resolution = false;
}

// C++ 2022 attribute initialisation
Collider::Collider(float radius, bool resolution, std::shared_ptr<GameObject> gameObject) : Component(gameObject), radius(radius), resolution(resolution)
{

}

Collider::~Collider()
{
    
}

void Collider::setRadius(float newRadius)
{
    radius = newRadius;
}

float Collider::getRadius()
{
    return radius;
}

void Collider::setResolution(bool flag)
{
    resolution = flag;
}

bool Collider::needsResolution()
{
    return resolution;
}
