#include "Component.hpp"

Component::Component()
{
    gameObject = nullptr;
}

Component::Component(std::shared_ptr<GameObject> newGameObject)
{
    gameObject = newGameObject;
}

Component::~Component()
{
    gameObject.reset();
    gameObject = nullptr;
}

void Component::setGameObject(std::shared_ptr<GameObject> newGameObject)
{
    gameObject = newGameObject;
}

std::shared_ptr<GameObject> Component::getGameObject()
{
    return gameObject;
}
