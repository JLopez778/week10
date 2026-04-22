#include "Background.hpp"

Background::Background() : GameObject()
{
    name = "background";
}

Background::~Background()
{
}

void Background::handleCollision(std::shared_ptr<Collider> other)
{
}