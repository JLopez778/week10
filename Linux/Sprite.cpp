#include "Sprite.hpp"

#include "GameObject.hpp"
#include "Texture.hpp"

Sprite::Sprite() : Component(gameObject)
{
    texture = nullptr;
}

Sprite::~Sprite()
{
    texture.reset();
    texture = nullptr;
}

void Sprite::setTexture(std::shared_ptr<Texture> newTexture)
{
    texture = newTexture;
}

std::shared_ptr<Texture> Sprite::getTexture()
{
    return texture;
}

